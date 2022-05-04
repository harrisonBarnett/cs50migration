-- list all movies released >= 2018 in alphabetical order
SELECT title FROM movies WHERE(year >= 2018) ORDER BY UPPER(title);