#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Check usage\n");
        return 1;
    }
    
    // Open memory card
    FILE *file = fopen("card.raw", "r");
    if (!file)
    {
        printf("Cannot open the file\n");
        return 1;
    }
    
    int end_of_card = 0;
    int jpeg_number = 0;
    char *current_jpeg_name = malloc(8);
    
    unsigned char bytes[512];
    int num_items = fread(bytes, 1, 512, file);
    
    
    // Move to the start of the file where first image is located
    while (!(bytes[0] == 0xff && bytes[1] == 0xd8 && 
             bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0))
    {
        fread(bytes, 1, 512, file);
    }
    
    // Create a new file in preparation for storing information into it
    sprintf(current_jpeg_name, "%03i.jpg", jpeg_number);
    FILE *new_jpeg = fopen(current_jpeg_name, "w");
    fwrite(bytes, 1, 512, new_jpeg);
    
    // Iterate through all of card, adding to new jpegs, until end of card
    while (!end_of_card)
    {
        // Read 512 bytes
        num_items = fread(bytes, 1, 512, file);
        
        // Check if this next chunk of bytes is a new jpeg
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && 
            bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            // Close previous jpeg file, and open a new one
            fclose(new_jpeg);
            jpeg_number++;
            sprintf(current_jpeg_name, "%03i.jpg", jpeg_number);
            new_jpeg = fopen(current_jpeg_name, "w");
            fwrite(bytes, 1, 512, new_jpeg);
        }
        else
        {
            fwrite(bytes, 1, 512, new_jpeg);
        }
        
        // End of card condition
        if (num_items < 512)
        {
            end_of_card = 1;
            fwrite(bytes, 1, num_items, new_jpeg);
            fclose(new_jpeg);
        }
    }
    
    
    free(current_jpeg_name);
    fclose(file);
}
