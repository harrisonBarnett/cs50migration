-- list movies and their ratings released in 2010, descending
-- order movies w/same rating alphabetically by tile
SELECT movies.title, ratings.rating -- display title followed by rating
FROM  movies 
INNER JOIN ratings ON movies.id = ratings.movie_id -- join ratings/movies via movie_id
WHERE year = 2010 
ORDER BY rating DESC, title; -- ORDER BY can take multiple args from both tables