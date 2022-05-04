SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
-- find instances of movies that star either depp or HBC
WHERE people.name IN("Johnny Depp", "Helena Bonham Carter")
-- group duplicate instances of titles
GROUP BY movies.title
-- groups of size 2 imply that depp/HBC both starred in the movie
HAVING COUNT(movies.title) = 2;