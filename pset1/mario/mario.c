#include <stdio.h>
#include <cs50.h>

void print_items(int, string);

// Ask for input (the number of pyramids)
// Print the pyramids using certain logic
int main(void)
{
    int n;
    do

    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 1; i <= n; i++)

    {
        print_items(n - i, " ");
        print_items(i, "#");
        print_items(2, " ");
        print_items(i, "#");
        printf("\n");
    }
}

// Prints the number of items using a for loop
void print_items(int n, string item)

{
    for (int i = 1; i <= n; i++)

    {
        printf("%s", item);
    }
}