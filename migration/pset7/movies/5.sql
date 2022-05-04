-- list release year of all harry potter movies chronologically 
SELECT title, year FROM movies WHERE(title LIKE "Harry Potter%") ORDER BY(year);