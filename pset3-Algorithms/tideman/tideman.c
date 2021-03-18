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

    for (int i = 0; i < candidate_count; i++)
    {
        printf("%i %i %i %i\n", preferences[i][0], preferences[i][1], preferences[i][2], preferences[i][3]);
    }

    add_pairs();
    printf("Pair count is %i\n", pair_count);
    sort_pairs();
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair winner is %i\n", pairs[i].winner);
        printf("Pair loser is %i\n", pairs[i].loser);
    }
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check that vote is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update ranks[rank] with the index of the candidate in that preference
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int n = candidate_count - 1;
        while (n > i)
        {
            preferences[ranks[i]][ranks[n]] ++;
            n--;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int n = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[n].winner = i;
                pairs[n].loser = j;
                printf("Winner is %i\n", pairs[n].winner);
                printf("Loser is %i\n", pairs[n].loser);
                pair_count++;
                n++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[n].winner = j;
                pairs[n].loser = i;
                printf("Winner is %i\n", pairs[n].winner);
                printf("Loser is %i\n", pairs[n].loser);
                pair_count++;
                n++;
            }
            else
            {
                printf("I'm crazy!");
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int largest = 0;
    int largest_index = 0;
    int largest_pair_winner;
    int largest_pair_loser;

    // Iterate through the number of times to ensure full sorting
    for (int i = 0; i < pair_count; i++)
    {
        // Find the strength for the current index in iteration, set it to largest
        int winner_value = preferences[pairs[i].winner][pairs[i].loser];
        int loser_value = preferences[pairs[i].loser][pairs[i].winner];
        int current_strength = winner_value - loser_value;
        largest = current_strength;
        largest_index = i;

        // Iterate and check each item with the next item
        for (int j = i + 1; j < pair_count; j++)
        {

            // Find the strength of the next index in iteration, check if greater than current
            winner_value = preferences[pairs[j].winner][pairs[j].loser];
            loser_value = preferences[pairs[j].winner][pairs[j].loser];
            int next_strength = winner_value - loser_value;
            if (next_strength > largest)
            {
                // Set to new largest
                largest = next_strength;
                largest_index = j;
            }
        }

        // At the end of iterating through to find the largest, bring the largest
        // pair to the ith index
        if (largest_index > i)
        {
            largest_pair_winner = pairs[largest_index].winner;
            largest_pair_loser = pairs[largest_index].loser;
            // Move item in front of search to the index where largest was
            pairs[largest_index].winner = pairs[i].winner;
            pairs[largest_index].loser = pairs[i].loser;
            // Now move largest to the front
            pairs[i].winner = largest_pair_winner;
            pairs[i].loser = largest_pair_loser;
        }

    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Initialize a vector that keeps track of how many columns have something in them
    int columns_used[candidate_count];
    int column_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        columns_used[i] = 0;
    }
    
    // Iterate through each pair (now sorted) and add True in corresponding 
    // Locked table location. If sum of columns_used is candidate_count - 1, then
    // we have reached a scenario where any more locks would create a loop
    for (int i = 0; i < pair_count; i++)
    {
        // Count the sum of columns used so far
        for (int j = 0; j < candidate_count; j++)
        {
            column_count += columns_used[j];
        }
        
        // As long as we're not at the end of columns, continue
        if (column_count == candidate_count - 1)
        {
            return;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true; 
            columns_used[pairs[i].winner] = 1;
        }
        
    }
    
}

// Print the winner of the election
void print_winner(void)
{
    bool is_winner = false;
    int sum;
    
    // Cycle through locked table for all truths. 
    for (int j = 0; j < candidate_count; j++)
    {
        sum = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            sum += (int) locked[i][j];
        }
        
        if (sum == 0)
        {
            printf("%s\n", candidates[j]);
            return;
        }
    }
}

