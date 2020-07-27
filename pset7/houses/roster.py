# TODO
import cs50
import csv
import sys

if(len(sys.argv) < 2):
    print("Usage: python import.py house")
    sys.exit(1)

db = cs50.SQL("sqlite:///students.db")

students = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC", sys.argv[1])

for student in students:
    if student["middle"] == "NULL":
        print(f'{student["first"]} {student["last"]}, born {student["birth"]}')
    else:
        print(f'{student["first"]} {student["middle"]} {student["last"]}, born {student["birth"]}')