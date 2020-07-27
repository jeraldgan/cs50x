#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void substitute(string plain_text, string substitution_key);
int isinvalidkey(string key);

int main(int argc, string argv[]){
    if(argc != 2){
        printf("Usage: ./substitution key \n");
        return 1;
    } else if (strlen(argv[1]) != 26){
        printf("Key must contain 26 characters. \n");
        return 1;
    } else {
        if(isinvalidkey(argv[1]) == 1){
            printf("Usage: ./substitution key \n");
            return 1;
        }
    }

    string plain_text = get_string("plaintext:   ");

    printf("ciphertext: ");
    substitute(plain_text, argv[1]);
    printf("\n");
}

void substitute(string plain_text, string substitution_key){
    string ciphertext = "";
    for(int i=0; i<strlen(plain_text); i++){
        char current_char = plain_text[i];

        if(isalpha(current_char)){
            if(isupper(current_char)){
                int difference = toupper(current_char) - 'A';
                printf("%c", toupper(substitution_key[difference]));
            } else {
                int difference = toupper(current_char) - 'A';
                printf("%c", tolower(substitution_key[difference]));
            }
        } else {
            printf("%c", current_char);
        }
    }
}

int isinvalidkey(string key){
    char alphabets[26];

    for(int i=0; i<strlen(key); i++){
        char current_char = key[i];

        if(isalpha(current_char)){
            int difference = toupper(current_char) - 'A';

            if(current_char==alphabets[difference]){
                return 1;
            } else {
                alphabets[difference] = current_char;
            }

        } else {
            return 1;
        }
    }
    return 0;
}