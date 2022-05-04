import sys
import csv

# check argument length
if len(sys.argv) != 3:
    print("invalid arguments")
    exit(0)

database = [] # [{name, STR, etc}, {etc}]
STRs = [] # STRs pulled from header of csv
counts = dict() # counts of consecutive STR in sequence.txt

# open csv file
with open(sys.argv[1], "r") as csv_file:
    csv_reader = csv.DictReader(csv_file)
    # populate database with dicts consisting of persons/STR counts
    for row in csv_reader:
        database.append(row)
    # pull headers into temp list from top row of csv
    headers = csv_reader.fieldnames
    headers.remove(headers[0])
    # populate STRs list and counts dict
    for h in headers:
        STRs.append(h)
        # initializing the count of each STR to 0
        counts.update({h: 0})

# open txt file
DNA_string = ""
with open(sys.argv[2], "r") as txt:
    DNA_string = txt.read()

# takes a long DNA string and an STR as args
def STR_counter(string, segment):
    supercount = 0
    # length of each STR for indexing purposes
    j = len(segment)
    
    # iterate thru the DNA string one index at a time
    for i in range(0, len(string)):
        subcount = 0
        # the slice of string the length of j is compared to the STR
        # if it matches, the index is incremented j times
        while string(i: i + j) == segment:
            subcount += 1
            i += j
        if subcount > supercount:
            supercount = subcount
    return supercount

# iterate thru STRs to perform counter function above
for STR in STRs:
    tmp = STR_counter(DNA, STR)
    # update the STR value in counts
    counts.get(STR) = tmp

for name in database:
    matches = 0
    
    for STR in STRs:
        if int(name[STR]) != counts[STR]:
            continue
        matches += 1
    
    if matches == len(STRs):
        print(name['name'])
        exit(1)
        
        


    



    