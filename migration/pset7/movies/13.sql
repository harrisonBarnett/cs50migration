-- list names of all people who starred in a movie with kevin bacon

-- lists all people in the list of people 
-- referenced by person_id in the list of movies starring kevin bacon
-- EXCEPT kevin bacon
SELECT (name) FROM people WHERE name IS NOT 'Kevin Bacon' and id IN
-- list of people who are referenced by person_id in the list of movies starring kevin bacon
(SELECT person_id FROM stars WHERE movie_id IN
-- list of movies starring kevin bacon
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name IS 'Kevin Bacon' and BIRTH = 1958)));
