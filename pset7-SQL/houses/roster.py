import csv
import cs50
from sys import argv, exit

if len(argv) != 2:
    print('Usage: ')
    exit(1)

db = cs50.SQL("sqlite:///students.db")

lists = db.execute("SELECT first, middle, last, birth FROM students WHERE house == ? ORDER BY last ASC, first ASC", argv[1])

#print(lists[1]['first'])

for rows in lists:
    if rows['middle'] == None:
        print(f"{rows['first']} {rows['last']}, born {rows['birth']}")
    else:
        print(f"{rows['first']} {rows['middle']} {rows['last']}, born {rows['birth']}")