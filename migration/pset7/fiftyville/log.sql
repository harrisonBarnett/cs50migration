-- Keep a log of any SQL queries you execute as you solve the mystery.

-- theft took place july 28, 2020 (7, 28, 2020)
-- theft took place on chamberlain street

-- query a list of crime reports from 7/28/2020
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28;
-- theft of cs50 duck occurred at 10:15 a.m. at the courthouse

-- check courthouse_security_logs on 7/28/2020 at 10:15 a.m.
SELECT * FROM courthouse_security_logs WHERE 
(year = 2020 AND month = 7 AND day = 28) AND
(hour = 10 AND minute = 15);

-- cross reference people with license plates entering/exiting courthouse
SELECT * FROM interviews WHERE name IN
(SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 28))) AND
(year = 2020 AND month = 7 AND day = 28);
-- maybe nothing is here??

-- check ATM transactions on 7/28/2020
SELECT * FROM atm_transactions WHERE (year = 2020 AND month = 7 AND day = 28) AND
atm_location LIKE "Chamberlain%";
-- no transactions took place at the courthouse i guess

-- check transcripts for mention of courthouse?
SELECT * FROM interviews WHERE name IN
(SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 28))) AND
transcript LIKE "%courthouse%";



-- list of people who were at the courthouse on 7/28/2020
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 28));

-- list of people who were at the courthouse AND on a flight on 7/28/2020
-- cross references license plates from courthouse with passports
-- who flew out of Fiftyville
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 29) AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE (year = 2020 AND month = 7 AND day = 28) AND
origin_airport_id IN(SELECT id FROM airports WHERE(city = "Fiftyville")))));




-- list of people who were interviewed after the theft
SELECT * FROM interviews WHERE year = 2020 AND month = 7 AND day = 28 AND
transcript LIKE "%courthouse%";
-- theft occured roughly 10 minutes before thief left the parking lot
-- thief used an ATM on fifer street earlier this morning
-- thief made a <1 min phone call
---- taking the earliest flight out of fiftyville tomorrow (7/29/2020)
---- the other person on the phone bought the ticket

-- list of people who left the courthouse after 10:15 a.m.
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 28) AND 
(hour >= 10) AND activity = "exit");

-- list of people who used the ATM on Fifer this morning
-- cross-referenced with above
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE 
atm_location LIKE "%Fifer%" AND (year = 2020 AND month = 7 AND day = 28))) AND license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 28) AND 
(hour >= 10) AND activity = "exit");

-- list of flights out of fiftyville the day after the theft
SELECT * FROM flights WHERE
year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE(city = "Fiftyville")) ORDER BY hour DESC;
-- one of the interviews mentioned the thief would take the earliest flight out 
-- of fiftyville the next day, which is at 8:20 a.m.

-- list passengers on the 8:20 a.m., 7/29/2020 flight out of fiftyville
-- cross reference passengers.flight_id to flights.id
SELECT name FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE
year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE(city = "Fiftyville"))));

-- cross reference above with people who used the ATM and were at the courthouse on 7/28
SELECT name FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE
year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN
(SELECT id FROM airports WHERE(city = "Fiftyville")))) AND id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE 
atm_location = "Fifer Street" AND (year = 2020 AND month = 7 AND day = 28) AND transaction_type = "withdraw")) AND license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 28) AND 
(hour = 10 AND minute <= 25 AND minute >= 15) AND activity = "exit");
-- we are narrowed down to danielle, russell and ernest

-- list phone calls from the people above
SELECT name FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE
(year = 2020 AND month = 7 AND day = 29) AND
(hour = 8 AND minute = 20) AND origin_airport_id IN
(SELECT id FROM airports WHERE(city = "Fiftyville")))) AND id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE 
atm_location = "Fifer Street" AND (year = 2020 AND month = 7 AND day = 28) AND transaction_type = "withdraw")) AND license_plate IN
(SELECT license_plate FROM courthouse_security_logs WHERE
(year = 2020 AND month = 7 AND day = 28) AND 
(hour = 10 AND minute <= 25 AND minute >= 15) AND activity = "exit") AND phone_number IN
(SELECT caller FROM phone_calls WHERE (year = 2020 AND month = 7 AND day = 28) AND duration <= 60);
-- we are narrowed down to Ernest

SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE caller IN
(SELECT phone_number FROM people WHERE name = "Ernest") AND
(year = 2020 AND month = 7 AND day = 28) AND duration <= 60);
-- yields Berthold

SELECT city FROM airports WHERE id IN
(SELECT destination_airport_id FROM flights WHERE
(year = 2020 AND month = 7 AND day = 29) AND
(hour = 8 AND minute = 20));
-- yields London