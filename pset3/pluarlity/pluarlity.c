#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void mergeSort(candidate arr[], int left_index, int right_index);
void merge(candidate arr[], int left_index, int middle_index, int right_index);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(name, candidates[i].name) == 0){
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    mergeSort(candidates, 0, candidate_count-1);
    int max_votes = 0;
    for(int i=candidate_count-1; i>=0; i--){
        candidate c = candidates[i];
        if(c.votes >= max_votes){
            max_votes = c.votes;
            printf("%s\n", c.name);
        } else {
            return;
        }
    }
    return;
}

void mergeSort(candidate arr[], int left_index, int right_index){
    if (left_index < right_index){
        int middle_index = left_index + (right_index - left_index)/2;

        mergeSort(arr, left_index, middle_index);
        mergeSort(arr, middle_index+1, right_index);

        merge(arr, left_index, middle_index, right_index);
    }
}

void merge(candidate arr[], int left_index, int middle_index, int right_index){

    int left_arr_size = middle_index - left_index + 1;
    int right_arr_size = right_index - middle_index;

    // Create temp arrays for left and right
    candidate left_arr [left_arr_size];
    candidate right_arr [right_arr_size];

    for (int i=0; i<left_arr_size; i++){
        left_arr[i] = arr[left_index+i];
    }

    for (int i=0; i<right_arr_size; i++){
        right_arr[i] = arr[middle_index+i+1];
    }

    int left_arr_index = 0;
    int right_arr_index = 0;
    int merged_arr_index = left_index;

    while(left_arr_index < left_arr_size && right_arr_index < right_arr_size){
        if(left_arr[left_arr_index].votes < right_arr[right_arr_index].votes){
            arr[merged_arr_index] = left_arr[left_arr_index];
            left_arr_index++;
        } else {
            arr[merged_arr_index] = right_arr[right_arr_index];
            right_arr_index++;
        }
        merged_arr_index++;
    }

    while(left_arr_index < left_arr_size){
        arr[merged_arr_index] = left_arr[left_arr_index];
        left_arr_index++;
        merged_arr_index++;
    }

     while(right_arr_index < right_arr_size){
        arr[merged_arr_index] = right_arr[right_arr_index];
        right_arr_index++;
        merged_arr_index++;
    }
}

