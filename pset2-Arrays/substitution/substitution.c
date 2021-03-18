#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


bool check_key(string key);


int main(int argc, string argv[])
{
    // Check for command line argument
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    
    // Check the quality of the key
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (check_key(argv[1]))
    {
        printf("Key invalid\n");
        return 1;
    }
    
    
    string key = argv[1];
    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    // Convert the key into all lowercases and save to an array key_array
    int key_lower[26];
    for (int i = 0; i < 26; i++)
    {
        key_lower[i] = tolower(key[i]);
    }

    // Iterate through the plaintext user input and print the cipher
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Make variable for the current character being ciphered
        int c = text[i];

        // If lowercase
        if ((96 < c) && (c < 123))
        {
            char cipher = key_lower[c - 97];
            printf("%c", cipher);
        }
        // If uppercase
        else if ((64 < c) && (c < 91))
        {
            char cipher = key_lower[c - 65];
            printf("%c", toupper(cipher));
        }
        else
        {
            printf("%c", c);
        }
    }
    
    printf("\n");

}


bool check_key(string key)
{
    bool check;
    
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        int c = key[i];
        
        
        if (((96 < c) && (c < 123)) || ((64 < c) && (c < 91)))
        {
            check = 0;
        }
        else
        {
            check = 1;
        }
    }
    
    return check;
}
