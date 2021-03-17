#include <stdio.h>
#include <cs50.h>


void build_tower(int n);
void spaces(int n);
void layers(int n);
int get_height(void);


int main(void)
{
    // Query user for height of mario tower
    int num_layers = get_height();

    // Build the tower up to the height requested by user
    build_tower(num_layers);
}


// Create a function that requires the positive, integer input of the user
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

// Create a function that builds each row of the tower, laying down the appropriate
// number of empty spaces, followed by the block pattern at the center of the layer,
// and finally by more empty spaces
void build_tower(int n)
{
    // Init the variable that will count the number of spaces needed at each row,
    // starting with printing the top row of the tower and decreasing #spaces with
    // each row
    int h = n - 1;

    // Iterate through the number of layers
    for (int i = 1; i < n + 1; i++)
    {
        spaces(h);
        layers(i);

        // Update the counter for the spaces and then \n for a new row
        h--;
        printf("\n");
    }
}

// Function that prints a number of spaces n
void spaces(n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// Function that prints the tower pattern for the row that is currently
// being printed (the pattern is n*#, 2*_, n*#)
void layers(n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}