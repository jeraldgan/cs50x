SELECT title from movies JOIN
stars ON movies.id = stars.movie_id JOIN
people on stars.person_id = people.id
WHERE name="Johnny Depp" or name = "Helena Bonham Carter"
GROUP BY title
HAVING count(title)=2;