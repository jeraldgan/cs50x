import csv
from cs50 import get_string
from sys import argv, exit

def main():
    if(len(argv) < 3):
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    with open(argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        database = list(reader)

    with open(argv[2], newline='') as textfile:
        sequence = textfile.readline()

    different_sequences = get_different_sequences(database)

    repeated_subsequence_count = match_sequences(different_sequences, sequence)

    print(find_the_match(repeated_subsequence_count, database, len(different_sequences)))

def get_different_sequences(database):
    # Retrieve the dna sequences that everyone has
    different_sequences = list(database[0].keys())
    different_sequences.remove("name")

    return different_sequences

def match_sequences(different_sequences, sequence):
    repeated_subsequence_count = {}

    # Loop through the different subsequence present in the data.csv
    for sub_sequence in different_sequences:
        repeated_subsequence_count[sub_sequence] = 0
        current_position = 0

        # Loop through the sequence given to find matches
        while current_position < len(sequence):

            if sub_sequence[0] == sequence[current_position]:

                sub_sequence_match_count = 0
                previous_position = current_position
                next_position = previous_position+len(sub_sequence)


                if next_position > len(sequence):
                    current_position += 1
                    continue

                # Once the first letter of subsequence matches, find the number of recurring matches of subsequence
                while sub_sequence == sequence[previous_position:next_position]:
                    if next_position > len(sequence):
                        break

                    sub_sequence_match_count += 1
                    previous_position = next_position
                    next_position += len(sub_sequence)

                if sub_sequence_match_count > repeated_subsequence_count[sub_sequence]:
                    repeated_subsequence_count[sub_sequence] = sub_sequence_match_count

                if sub_sequence_match_count > 0:
                    current_position = next_position
                else:
                    current_position += 1
            else:
                current_position += 1

    return repeated_subsequence_count

def find_the_match(repeated_subsequence_count, database, number_of_subsequence):
    for row in database:

        match_count = 0

        for sub_sequence, number_of_matches in repeated_subsequence_count.items():
            if int(row[sub_sequence]) == number_of_matches:
                match_count += 1

        if match_count == number_of_subsequence:
            return row["name"]

    return "No match"

main()