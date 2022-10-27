-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get crime scene reports
SELECT description
  FROM crime_scene_reports
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND street LIKE 'Humphrey Street';

-- Interviews
SELECT transcript
  FROM interviews
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND transcript LIKE '%bakery%';

-- Licence plate
SELECT license_plate
  FROM bakery_security_logs
 WHERE activity = 'exit'
   AND day = 28
   AND month = 7
   AND year = 2021
   AND hour = 10
   AND minute BETWEEN 20 AND 30;

-- Account number
SELECT account_number
  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND atm_location LIKE '%Leggett%'
   AND transaction_type LIKE 'withdraw%';

-- Phone number of thief and acc
SELECT caller, receiver
  FROM phone_calls
 WHERE duration < 60
   AND day = 28
   AND month = 7
   AND year = 2021;

-- Destination city name
SELECT city
  FROM airports
 WHERE id IN
    (SELECT destination_airport_id
       FROM flights
      WHERE day = 29
        AND month = 7
        AND year = 2021
        AND origin_airport_id IN
            (SELECT id
               FROM airports
              WHERE city = 'Fiftyville')
      ORDER BY hour, minute ASC
      LIMIT 1);

-- Get passport number of thief
SELECT passport_number
  FROM passengers
 WHERE flight_id IN
    (SELECT id
       FROM flights
      WHERE day = 29
        AND month = 7
        AND year = 2021
        AND origin_airport_id IN
            (SELECT id
               FROM airports
              WHERE city = 'Fiftyville')
      ORDER BY hour, minute ASC
      LIMIT 1);

-- Get thief name by license plate, phone number, account number and passport number
SELECT name, phone_number
  FROM people
 WHERE license_plate IN
    (SELECT license_plate
       FROM bakery_security_logs
      WHERE activity = 'exit'
        AND day = 28
        AND month = 7
        AND year = 2021
        AND hour = 10
        AND minute BETWEEN 15 AND 30)
   AND phone_number IN
    (SELECT caller
      FROM phone_calls
     WHERE duration < 60
       AND day = 28
       AND month = 7
       AND year = 2021)
   AND passport_number IN
    (SELECT passport_number
       FROM passengers
      WHERE flight_id IN
        (SELECT id
           FROM flights
          WHERE day = 29
            AND month = 7
            AND year = 2021
            AND origin_airport_id IN
                (SELECT id
                   FROM airports
                  WHERE city = 'Fiftyville')
      ORDER BY hour, minute ASC
      LIMIT 1))
   AND id IN
    (SELECT person_id
       FROM bank_accounts
      WHERE account_number IN
        (SELECT account_number
           FROM atm_transactions
          WHERE day = 28
            AND month = 7
            AND year = 2021
            AND atm_location LIKE '%Leggett%'
            AND transaction_type LIKE 'withdraw%'));


-- Get accomplice by phone number
SELECT name
  FROM people
 WHERE phone_number IN
    (SELECT receiver
       FROM phone_calls
      WHERE duration < 60
        AND day = 28
        AND month = 7
        AND year = 2021
        AND caller = '(367) 555-5533');