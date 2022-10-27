let dark;

function load()
{
    console.log("loading background");
    if (dark == true)
    {
        console.log("Dark theme")
        $("body").css("background-color", "#000000");
        $(".txt").css("color", "#ffffff");
        $("button.bg").html("☀️");
        $("#navigation").attr("class", "navbar navbar-light bg-dark");
        $("hr").css("background-color", "grey");
    }
    else
    {
        console.log("Light theme")
        $("body").css("background-color", "#ffffff");
        $(".txt").css("color", "#000000");
        $("button.bg").html("🌑");
        $("#navigation").attr("class", "navbar navbar-light bg-light");
        $("hr").css("background-color", "#000000");
    }
}

function change_bg()
{
    if (dark == true)
    {
        console.log("Light theme")
        $("body").css("background-color", "#ffffff");
        $(".txt").css("color", "#000000");
        $("button.bg").html("🌑");
        $("#navigation").attr("class", "navbar navbar-light bg-light");
        $("hr").css("background-color", "grey");
        localStorage.setItem("dark", false);
        dark = false;
    }
    else
    {
        console.log("Dark theme")
        $("body").css("background-color", "#000000");
        $(".txt").css("color", "#ffffff");
        $("button.bg").html("☀️");
        $("#navigation").attr("class", "navbar navbar-light bg-dark");
        $("hr").css("background-color", "#ffffff");
        localStorage.setItem("dark", true);
        dark = true;
    }

    console.log("localStorage dark: " + localStorage.getItem("dark"));
}

$("document").ready(function() {
    console.log("localStorage.dark = " + localStorage.getItem("dark"));
    if (localStorage.getItem("dark") != "null")
    {
        dark = localStorage.getItem("dark");
    }
    else
    {
        localStorage.setItem("dark", false);
        dark = localStorage.getItem("dark");
    }

    load();
});