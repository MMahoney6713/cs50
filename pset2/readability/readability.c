#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


bool is_letter(char c);
bool is_sentence(char c);
bool is_word(char c);
int calc_cl(float letter_count, float word_count, float sent_count);


int main(void)
{

    string text = get_string("Text: ");

    int letter_count = 0;
    int word_count = 1;
    int sent_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Check if it is a letter, add to count of letters
        if (is_letter(text[i]))
        {
            letter_count++;
        }

        // Check if it is an end of a word, add to count of words
        if (is_word(text[i]))
        {
            word_count++;
        }

        // Check if end of sentence, add to count of sentences
        if (is_sentence(text[i]))
        {
            sent_count++;
        }
    }

    int cl_index = calc_cl(letter_count, word_count, sent_count);

    if (cl_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cl_index < 16)
    {
        printf("Grade %i\n", cl_index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}



bool is_letter(char c)
{
    if ((c > 64 && c < 91) || (c > 96 && c < 123))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


bool is_sentence(char c)
{
    //      !            .            ?
    if ((c == 33) || (c == 46) || (c == 63))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


bool is_word(char c)
{
    //    ' '
    if (c == 32)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int calc_cl(float letter_count, float word_count, float sent_count)
{
    float L = letter_count * 100 / word_count;
    float S = sent_count * 100 / word_count;
    int cl_index = round(0.0588 * L - 0.296 * S - 15.8);
    return cl_index;
}