SELECT count(DISTINCT name) FROM people
WHERE people.id in
(SELECT DISTINCT person_id FROM stars JOIN
movies on stars.movie_id = movies.id WHERE
year = 2004) ORDER BY birth;

