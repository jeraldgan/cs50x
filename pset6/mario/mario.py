from cs50 import get_int

def main():
    while True:
        n = get_int("Height: ")
        if not (n < 1 or n > 8):
            break

    for i in range(1,n+1):
        print_items(n - i, " ")
        print_items(i, "#")
        print_items(2, " ")
        print_items(i, "#")
        print()

def print_items(number_of_times, item):
    for i in range(number_of_times):
        print(item, end="")

main()