-- list names of all people starring in toy story
SELECT name FROM people
-- cross reference stars with name comparing people.id to stars.person_id
JOIN stars ON people.id = stars.person_id
-- cross reference movies to all above comparing stars.moive_id to movies.id
JOIN movies ON stars.movie_id = movies.id
-- can now reference movies to name to suss out "Toy Story"
WHERE movies.title = "Toy Story";