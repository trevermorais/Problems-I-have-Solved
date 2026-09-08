import csv
import sys


def longest_match(sequence, subsequence):

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):

        count = 0

        while True:

            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1

            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


def main():

    if len(sys.argv) != 3:
        print("Error: Please provide exactly 3 arguments!")
        print("Usage: python script.py <csv_file> <str_counts>")
        sys.exit(1)

    csvfile = sys.argv[1]
    strcounts = sys.argv[2]

    rows = []

    with open(csvfile, "r") as file:
        reader = csv.DictReader(file)
        str_list = reader.fieldnames[1:]
        for row in reader:
            rows.append(row)

    with open(strcounts, "r") as seq_file:
        dna_seq = seq_file.read()

    dna_count = {}
    for str_name in str_list:
        dna_count[str_name] = longest_match(dna_seq, str_name)

    for person in rows:
        match = True

        for i in str_list:
            if person[i] != str(dna_count[i]):
                match = False
                break

        if match == True:
            print(person["name"])
            sys.exit(0)

    print("No match")


main()
