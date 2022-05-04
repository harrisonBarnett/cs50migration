import sys
import csv


def main():
    # check argument length
    if len(sys.argv) != 3:
        print("invalid argument: dna.py [STR.csv] [DNA.txt]")
        exit(0)

    database = [] # [{name, STR, etc}, {etc}]
    STRs = [] # STRs pulled from header of csv
    counts = dict() # counts of consecutive STRs in sequence.txt

    with open(sys.argv[1], "r") as csv_file:
        csv_reader = csv.DictReader(csv_file)
        # populate database with dicts consisting of persons/STR counts
        for row in csv_reader:
            database.append(row)
        # pull headers into temp list from top row of csv
        headers = csv_reader.fieldnames
        headers.remove(headers[0]) # remove name field to isolate STRS
        # populate STRs list and counts dict
        for h in headers:
            STRs.append(h)
            # initializing the count of each STR to 0
            counts.update({h: 0})

    # open txt file
    DNA = ""
    with open(sys.argv[2], "r") as f:
        DNA = f.read()

    # implement function to count number of consecutive occurences of a given STR
    # takes a long DNA string and an STR segment as args
    def STR_counter(string, segment):
        supercount = 0
        # length of each STR for indexing purposes
        j = len(segment)
        for i in range(0, len(string)):
            subcount = 0
            # the slice of string the length of j is compared to the STR
            # if it matches, the index is incremented j times
            while string[i: i + j] == segment:
                subcount += 1
                i += j
            # pass subcount to supercount once matching terminates
            if subcount > supercount:
                supercount = subcount
        return supercount

    # iterate thru STRs to perform the counting function above
    for STR in STRs:
        tmp = STR_counter(DNA, STR)
        # update the STR value in counts
        counts.update({STR: tmp})

    # iterate thru database to compare the STR counts from the long DNA string
    # per each person's STR counts
    for name in database:
        matches = 0

        for STR in STRs:
            if int(name[STR]) != counts[STR]:
                continue
            matches += 1

        if matches == len(STRs):
            print(name['name'])
            exit(1)

    # if we go thru the entire program with no exits, we print No match
    print("No match")


if __name__ == "__main__":
    main()

# references:
# https://thispointer.com/python-read-csv-into-a-list-of-lists-or-tuples-or-dictionaries-import-csv-to-list/
# user AzyCrw4282 at https://stackoverflow.com/questions/61131768/how-to-count-consecutive-substring-in-a-string-in-python-3
# and of course lots of python docs