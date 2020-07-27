from cs50 import get_string

def main():
    input = get_string("Text:  ")

    grade = round(calculate(input))

    if(grade < 1):
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade", grade)

def calculate(input):
    counts = {
        "letters": 0,
        "words": 0,
        "sentences":0
    }

    for character in input:
        if character.isalpha():
            counts["letters"] += 1
        elif character == " ":
            counts["words"] += 1
        elif character == "." or character == "!" or character == "?":
            counts["sentences"] += 1

    counts["words"] += 1

    return 0.0588 * (counts["letters"]/counts["words"])*100 - 0.296 * (counts["sentences"]/counts["words"])*100 - 15.8

main()