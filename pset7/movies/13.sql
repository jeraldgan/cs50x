SELECT DISTINCT name from people JOIN
stars on people.id = stars.person_id
WHERE movie_id in (SELECT movie_id FROM people JOIN
stars ON people.id = stars.person_id JOIN
movies ON stars.movie_id = movies.id
WHERE name = "Kevin Bacon" and birth = 1958)
AND name not in ("Kevin Bacon");

