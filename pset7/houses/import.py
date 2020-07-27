# TODO
import cs50
import csv
import sys

if(len(sys.argv) < 2):
    print("Usage: python import.py characters.csv")
    sys.exit(1)

db = cs50.SQL("sqlite:///students.db")

with open(sys.argv[1], "r") as students:

    reader = csv.DictReader(students)

    for row in reader:
        names = row["name"].split()
        if len(names) == 2:
            first = names[0]
            middle = "NULL"
            last = names[1]
        else:
            print(names)
            first = names[0]
            middle = names[1]
            last = names[2]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", first, middle, last, row["house"], int(row["birth"]))