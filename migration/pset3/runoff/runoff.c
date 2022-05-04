#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// this is a 2D array where the voter is the row and the rank is the column
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
            else 
            {
                vote(i, j, name); // added this to make sure i was using the function. that's confusing!!
            }
        }
        

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    
    for (int i = 0; i < candidate_count; i++) // find candidate at position i in the candidates array
    {
        if (strcmp(candidates[i].name, name) == 0) // if the candidate at position i's name matches the input, 
        {
            preferences[voter][rank] = i; // the candidate at position i is assigned to the rank "column" of the voter "row" of preferences 2D arr
            return true;
        }
    }
    
    
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++) // for each voter
    {
        for (int j = 0; j < candidate_count; j++) // and each candidate
        {
            if (candidates[preferences[i][j]].eliminated == false) // as long as the candidate in the voter/candidate "cell" is NOT eliminated
            {
                candidates[preferences[i][j]].votes++; // increase their vote by one
                break; // kill the loop and go to the next "column" j AKA candidate
            }
        }
    }
    
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i ++) 
    {
        if (candidates[i].votes > voter_count / 2) // easy peasy, if a candidate has over half the total votes, they're the winner
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = candidates[0].votes; // baseline
    for (int i = 0; i < candidate_count; i++) // for each candidate
    {
        if (candidates[i].eliminated == true) // kill the loop if candidate is eliminated
        {
            continue;
        }
        
        if (candidates[i].votes < min) // if candidate at index i < the baseline
        {
            min = candidates[i].votes; // then the baseline might as well be the candidate at index i
        }
    }
    
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // so this is probably a really ratchet way to do it, but i made some bean counters
    int tieCondition = 0;
    int remainingCandidates = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            continue; // kill the loop if the candidate is eliminated
        }
        else
        {
            if (candidates[i].votes == min)
            {
                tieCondition++;
            }
            remainingCandidates++;
        }
    }
    if (tieCondition == remainingCandidates) // compare candidates with the min vote with the total number of non-eliminated candidates
    {
        return true; // if they are equal, then it stands to reason that they are all tied with one another
    }
    
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min) 
        {
            candidates[i].eliminated = true; // any candidates with votes == find_min get bool eliminated changed to TRUE
        }
    }
    
    return;
}
