SELECT title from movies JOIN
ratings ON ratings.movie_id = movies.id JOIN
stars ON ratings.movie_id = stars.movie_id JOIN
people on stars.person_id = people.id WHERE
name = "Chadwick Boseman" ORDER BY rating limit 5;