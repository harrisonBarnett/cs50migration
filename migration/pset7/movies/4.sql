-- return the number of movies w/IMDB rating of 10.0
SELECT COUNT(title) FROM movies WHERE id IN(SELECT movie_id FROM ratings WHERE(rating = 10.0));