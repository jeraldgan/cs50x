from cs50 import get_string

def main():
    credit_card_number = get_string("Card No.: ")

    process_card_number(credit_card_number)

def process_card_number(credit_card_number):
    sum = 0
    steps = 0
    for index in range(len(credit_card_number)-2, -1, -1):
        number = int(credit_card_number[index])
        if (steps % 2 == 0):
            number *= 2;
            number = str(number)
            for num in number:
                sum += int(num)
        else:
            sum += number;

        steps+=1

    sum += int(credit_card_number[-1])

    if(sum % 10 == 0):
        check_company(credit_card_number)
    else:
        print("INVALID\n")

def check_company(credit_card_number):
    digits = len(credit_card_number)
    if (digits == 15 and credit_card_number[0] == "3" and (credit_card_number[1] == "4" or credit_card_number[1] == "7")):
        print("AMEX\n")
    elif (digits == 16 and credit_card_number[0] == "5" and (credit_card_number[1] == "1" or credit_card_number[1] == "2" or credit_card_number[1] == "3" or credit_card_number[1] == "4" or credit_card_number[1] == "5")):
        print("MASTERCARD\n")
    elif ((digits == 13 or digits == 16) and credit_card_number[0] == "4"):
        print("VISA\n")
    else:
        print("INVALID\n")

main()
