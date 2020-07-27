#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

float calculate(string input);

int main (void){
    string input = get_string("Text:  ");

    int grade = (int) roundf(calculate(input));

    if (grade < 1){
        printf("Before Grade 1");
    } else if (grade > 16){
        printf("Grade 16+");
    } else {
        printf("Grade %i", grade);
    }
    printf("\n");
}

float calculate(string input){
    float counts[3];

    counts[0] = 0;
    counts[1] = 0;
    counts[2] = 0;

    for(int i=0; i<strlen(input); i++){
        if(isalpha(input[i])){
            counts[0]++;
        } else if (isspace(input[i])){
            counts[1]++;
        } else if (input[i] == '.' || input[i] == '!' || input[i] == '?'){
            counts[2]++;
        }
    }

    counts[1]++;

    return 0.0588 * (counts[0]/counts[1])*100 - 0.296 * (counts[2]/counts[1])*100 - 15.8;
}