import csv
from sys import argv, exit

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

sequences = open(argv[2], "r")
sequences_txt = sequences.read()

# Open the csv data and determine what are the keys that we will be using
with open(argv[1], "r") as data:
    reader = csv.reader(data)
    for row in reader:
        keys = row[1:]
        break

    str_max = [0 for key in keys]
    str_count = [0 for key in keys]
    # Now that we have keys, iterate through the sequence file to (end - 4)
    for key_index in range(len(keys)):
        for s_index in range(len(sequences_txt) - len(keys[key_index])):

            # Reset the str counter for the key before entering while loop
            str_count[key_index] = 0
            # While there is a string match, continue through and adding to the count so 
            # long as we see the key in sequence
            while keys[key_index] == sequences_txt[s_index:s_index + len(keys[key_index])]:
                str_count[key_index] += 1
                s_index += len(keys[key_index])
                #print(sequences_txt[s_index:s_index + len(keys[key_index])])
            
            # If this string of STR was the longest, add to the max counter array    
            if str_count[key_index] > str_max[key_index]:
                str_max[key_index] = str_count[key_index]
            
    #print(str_max)
    culprit = 0
    key_values = [0 for key in keys]
    # Now compare the rest of the rows for a row that matches str_max
    for row in reader:
        key_values_str = row[1:]
        for item in range(len(key_values)):
            key_values[item] = int(key_values_str[item])
            #print(int(key_values[item]))
        #print(key_values)
        
        if key_values == str_max:
            culprit = row[0]
            

if culprit == 0:
    print("No match")
else:
    print(culprit)

