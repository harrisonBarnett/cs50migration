-- remove dupes with DISTINCT
SELECT DISTINCT(name) FROM people
-- cross reference stars to people (people.id <> stars.person_id)
JOIN stars ON people.id = stars.person_id
-- cross reference movies to stars (stars.movie_id <> movies.id)
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = "2004"
ORDER BY (people.birth);


