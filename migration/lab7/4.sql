-- list song titles from songs.db with danceability, energy and valence > 0.75
SELECT name FROM songs WHERE(danceability>0.75 AND energy>0.75 AND valence>0.75);