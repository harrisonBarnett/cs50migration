-- list top five longest songs in songs.db, descending
SELECT name FROM songs ORDER BY(duration_ms) DESC LIMIT 5;