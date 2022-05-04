-- list the names of all directors of moives with a rating >= 9.0
SELECT DISTINCT(name) FROM people
-- cross reference directors <> people by people.id <> directors.person_id
JOIN directors ON people.id = directors.person_id
-- cross reference movies <> directors by directors.movie_id <> movies.id
JOIN movies ON directors.movie_id = movies.id
-- cross reference ratings <> movies by movies.id <> ratings.movie_id
JOIN ratings ON movies.id = ratings.movie_id

WHERE ratings.rating >= 9.0;