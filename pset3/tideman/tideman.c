// Incomplete code!!!

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergeSort(pair arr[], int left_index, int right_index);
void merge(pair arr[], int left_index, int middle_index, int right_index);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for(int i=0; i<candidate_count; i++){
        if(strcmp(name, candidates[i]) == 0){
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int i=0; i<candidate_count-1; i++){
        if(preferences[ranks[i]][ranks[i+1]]!=0){
            preferences[ranks[i]][ranks[i+1]] = 0;
        }
        preferences[ranks[i]][ranks[i+1]]++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int pairs_index = 0;
    for(int i=0; i<candidate_count-1; i++){
        for(int j=i+1; j<candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pairs_index].winner = i;
                pairs[pairs_index].loser = j;
            } else {
                pairs[pairs_index].loser = i;
                pairs[pairs_index].winner = j;
            }
            pairs_index++;
        }
    }

    pair_count = pairs_index;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    mergeSort(pairs, 0, pair_count-1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    bool incoming_edge_check = false;
    bool outgoing_edge_check = false;
    for(int i=0; i<pair_count; i++){
        if(i == pair_count -1){
            int incoming = pairs[i].winner;
            int outgoing = pairs[i].loser;

            for(int j=0; j<pair_count; j++){
                if(incoming != j){
                    if(locked[j][incoming]){
                        incoming_edge_check = true;
                    }
                }

                if(outgoing != j){
                    if(locked[outgoing][j]){
                        outgoing_edge_check = true;
                    }
                }
            }

            if(!(incoming_edge_check && outgoing_edge_check)){
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        } else {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int losers[candidate_count];
    int least_count = 0;
    int winner = 0;

    for(int i=0; i<candidate_count; i++){
        losers[i] = 0;
    }

    for(int i=0; i<candidate_count; i++){
        for(int j=0; j<candidate_count; j++){
            if(i!=j){
                if(locked[i][j]){
                    losers[j] += 1;
                }
            }
        }
    }


    for(int i=0; i<candidate_count; i++){
        if(losers[i] <= least_count){
            least_count = losers[i];
            winner = i;
        }
    }

    printf("%s\n", candidates[winner]);

    return;
}

void mergeSort(pair arr[], int left_index, int right_index){
    if (left_index < right_index){
        int middle_index = left_index + (right_index - left_index)/2;

        mergeSort(arr, left_index, middle_index);
        mergeSort(arr, middle_index+1, right_index);

        merge(arr, left_index, middle_index, right_index);
    }
}

void merge(pair arr[], int left_index, int middle_index, int right_index){

    int left_arr_size = middle_index - left_index + 1;
    int right_arr_size = right_index - middle_index;

    // Create temp arrays for left and right
    pair left_arr [left_arr_size];
    pair right_arr [right_arr_size];

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
        if(preferences[left_arr[left_arr_index].winner][left_arr[left_arr_index].loser] > preferences[right_arr[right_arr_index].winner][right_arr[right_arr_index].loser]){
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

