-- list the 5 highest rated movies starring chadwick boseman (high to low)

SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON  movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = "Chadwick Boseman"
ORDER BY ratings.rating DESC LIMIT 5;