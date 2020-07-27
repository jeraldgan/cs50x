#include <stdio.h>
#include <cs50.h>
#include <math.h>

void process_card_number(long credit_card_number);
void check_company(int digits, int array[]);
int calculate_luhn_algorithm(int digits[], long number_of_digits);

int main(void)
{
    long c;

    c = get_long("Card No.: ");

    process_card_number(c);

}

void process_card_number(long credit_card_number){

    long number_of_digits = log10(credit_card_number) + 1;
    int digits[number_of_digits];
    for (int i = number_of_digits-1; i >= 0; i--) {
        digits[i] = credit_card_number % 10;
        credit_card_number = credit_card_number / 10;
    }

    int sum = calculate_luhn_algorithm(digits, number_of_digits);

    printf("%i\n", sum);

    if(sum % 10 == 0){
        check_company(number_of_digits, digits);
    } else {
        printf("INVALID\n");
    }

}

int calculate_luhn_algorithm(int digits[], long number_of_digits){
    int sum = 0;
    int steps = 0;

    for (int i = number_of_digits-2; i >= 0; i--){
        int number = digits[i];
        if (steps % 2 == 0){
            number *= 2;
            while (number != 0) {
                sum += (number % 10);
                number /= 10;
            }
         } else {
            sum += number;
        }
        steps++;
    }
    sum += digits[number_of_digits-1];
    return sum;
}



void check_company(int digits, int array[])
{
    if (digits == 15 && array[0] == 3 && (array[1] == 4 || array[1] == 7))
    {
        printf("AMEX\n");
    }
    else if (digits == 16 && array[0] == 5 && (array[1] == 1 || array[1] == 2 || array[1] == 3 || array[1] == 4 || array[1] == 5))
    {
        printf("MASTERCARD\n");
    }
    else if ((digits == 13 || digits == 16) && array[0] == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}