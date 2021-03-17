import csv
import cs50
from sys import argv, exit

if len(argv) != 2:
    print('Usage: ')
    exit(1)

#open(f"students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as characters:
    reader = csv.DictReader(characters)
    for row in reader:
        name = row["name"].split(" ")
        if len(name) == 2:
            first, last = name
            middle = None
        else:
            first, middle, last = name
        house = row["house"]
        birth = row["birth"]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", first, middle, last, house, birth)
