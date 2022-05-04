-- list names of songs in songs.db by Post Malone
SELECT name FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = "Post Malone");