-- list names of songs featuring other artist (i.e. the titles contain "feat.")
SELECT name FROM songs WHERE name LIKE "%feat.%";