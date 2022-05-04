-- return average energy of songs by Drake
SELECT AVG(energy) FROM songs WHERE artist_id IN(SELECT id FROM artists WHERE name = "Drake");