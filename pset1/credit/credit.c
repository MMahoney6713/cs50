#include <stdio.h>
#include <cs50.h>
#include <math.h>

long get_number(void);
void check_card(long n);
int sum_digits(int n);


int main(void)
{
    // Query user for height of mario tower
    long card_number = get_number();
    check_card(card_number);

}


// Create a function that requires the positive, 'long' input of the user
long get_number(void)
{
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 1);
    return n;
}

void check_card(long n)
{
    int digit_count = 1;
    int digit = 0;
    long power = 0;
    int prev_digit = 0;
    int prev_prev_digit = 0;
    long prev_power = 1;
    int step1_count = 0;
    int step2_count = 0;
    int temp_digit = 0;

    do
    {
        // Determine the nth power based on which digit is currently being checked,
        // and then perform the operation to determine the digit.
        power = pow(10, digit_count);
        digit = ((n % power) - prev_digit) / prev_power;
        //printf("Current Digit is %i\n",digit);


        // If digit_count % 2 = 0 then we are on an "even" digit, add to luhn's step 1 count
        if (digit_count % 2 == 0)
        {
            // Multiply the digit by two
            temp_digit = digit * 2;
            //printf("temp digit is %i\n", temp_digit);

            // If digit is greater than 9 than it has two digits, must be added together
            if (temp_digit > 9)
            {
                step1_count += sum_digits(temp_digit);
            }
            else
            {
                step1_count += temp_digit;
            }
        }
        // If digit_count % 2 = 1 then we are on an "odd" digit, add to luhn's step 2 count
        else
        {
            step2_count += digit;
        }


        // Increase the digit count and save information on the previous digit/power
        // for calculating the next digit in the card
        digit_count++;
        prev_prev_digit = prev_digit;
        prev_digit = digit;
        prev_power = power;


        //printf("Step 1 count: %i\n", step1_count);
        //printf("Step 2 count: %i\n", step2_count);




    }
    while ((n % power) < n);

    int luhns_sum = step1_count + step2_count;
    int last_luhns_digit = luhns_sum % 10;
    //printf("%i", last_luhns_digit);
    // If luhn's passes and if length acceptable, works!
    if (last_luhns_digit == 0)
    {
        
        int card_length = digit_count - 1;
        int sec_dig = prev_prev_digit;
        
        //printf("Digit is%i\n", digit);
        //printf("Previous digit is %i\n", sec_dig);
        //printf("Digit Count is%i\n", digit_count);
        

        if (digit == 4 && (card_length == 13 || card_length == 16))
        {
            printf("VISA\n");
        }
        else if (digit == 5 && sec_dig < 6 && sec_dig > 0 && card_length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (digit == 3 && (sec_dig == 4 || sec_dig == 7) && card_length == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


int sum_digits(int n)
{
    int power;
    int sum = 0;
    int prev_digit = 0;
    int prev_power = 1;

    for (int i = 1; i < 3; i++)
    {
        power = pow(10, i);
        int digit = ((n % power) - prev_digit) / prev_power;
        prev_power = power;
        sum += digit;
    }
    return sum;
    //printf("sum from sum_digits is %i\n", sum);
}