import os
from datetime import date

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    db.execute("DELETE FROM total_shares WHERE shares = 0")

    stocks = db.execute("SELECT symbol, shares FROM total_shares WHERE user_id = ?", session["user_id"])
    user = db.execute("SELECT * FROM users WHERE id = ?;", session["user_id"])[0]

    total = 0
    for i in range(len(stocks)):
        current = lookup(stocks[i]["symbol"])
        price = current["price"]
        name = current["name"]

        stocks[i]["price"] = price
        stocks[i]["name"] = name
        stocks[i]["total"] = int(stocks[i]["shares"]) * price

        total += stocks[i]["total"]

    return render_template("index.html", socks=stocks, cash=user["cash"], total_money=user["cash"] + total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        shares = request.form.get("shares")
        try:
            shares = float(shares)
        except:
            return apology("enter a number")

        symbol = request.form.get("symbol").upper()

        if not symbol:
            return apology("must enter a symbol")

        if not shares or int(shares * 10) % 10 != 0 or shares < 1:
            return apology("must enter valid number")

        shares = int(shares)

        stock = lookup(symbol)
        if not stock:
            return apology("Enter a valid symbol")

        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]

        if user["cash"] < stock["price"] * shares:
            return apology("Not enough cash")

        today = date.today()

        db.execute("INSERT INTO transactions (user_id, transaction_type, date, symbol, shares, transaction_price) VALUES (?, 'BUY', ?, ?, ?, ?)",
                   session["user_id"], date.isoformat(today), symbol, shares, stock["price"])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user["cash"] - stock["price"] * shares, session["user_id"])

        if not db.execute("SELECT * FROM total_shares WHERE user_id = ? AND symbol = ?", session["user_id"], symbol):
            db.execute("INSERT INTO total_shares (user_id, symbol, shares) VALUES (?, ?, ?)", session["user_id"], symbol, shares)

        else:
            current_shares = int(db.execute("SELECT shares FROM total_shares WHERE user_id = ? AND symbol = ?",
                                            session["user_id"], symbol)[0]["shares"])
            db.execute("UPDATE total_shares SET shares = ? WHERE user_id = ? AND symbol = ?",
                       current_shares + shares, session["user_id"], symbol)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transa = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY date", session["user_id"])
    return render_template("history.html", transactions=transa)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Check a non empty symbol
        if not request.form.get("symbol"):
            return apology("must enter a symbol")

        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Enter a valid symbol")

        return render_template("quoted.html", info=stock, symbol=request.form.get("symbol"))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Get valid usernames and passwords
        if not request.form.get("username"):
            return apology("Must register username")
        if not request.form.get("password"):
            return apology("Must register password")

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords must match")

        # Check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username").lower())
        if len(rows) != 0:
            return apology("Username already exists")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
            "username").lower(), generate_password_hash(request.form.get("password")))

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]
        stocks = db.execute("SELECT symbol, shares FROM total_shares WHERE user_id = ?", session["user_id"])

        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("Must enter a symbol")

        symbol_found = False
        shares_owned = -1
        for i in stocks:
            if i["symbol"].upper() == symbol:
                symbol_found = True
                shares_owned = int(i["shares"])

        if not symbol_found:
            return apology("You do not own any shares with that symbol")

        if not shares or shares < 1:
            return apology("must enter a valid number")

        if shares_owned < shares:
            return apology("You do not own that many shares")

        stock = lookup(symbol)

        today = date.today()

        db.execute("INSERT INTO transactions (user_id, transaction_type, date, symbol, shares, transaction_price) VALUES (?, 'SELL', ?, ?, ?, ?)",
                   session["user_id"], date.isoformat(today), symbol, shares, stock["price"])

        db.execute("UPDATE users SET cash = ? WHERE id = ?", user["cash"] + stock["price"] * shares, session["user_id"])

        db.execute("UPDATE total_shares SET shares = ? WHERE user_id = ? AND symbol = ?",
                   shares_owned - shares, session["user_id"], symbol)

        return redirect("/")

    else:
        socks = db.execute("SELECT symbol FROM total_shares WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", owned=socks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
