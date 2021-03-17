#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int blue;
    int green;

    // Iterate through all RGBTRIPLEs and average the values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = (int) round((red + blue + green) / 3.0);
            image[i][j].rgbtBlue = (int) round((red + blue + green) / 3.0);
            image[i][j].rgbtGreen = (int) round((red + blue + green) / 3.0);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap_dummy;
    int opposite;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half = width / 2; j < half; j++)
        {
            opposite = width - j - 1;
            swap_dummy = image[i][j];
            image[i][j] = image[i][opposite];
            image[i][opposite] = swap_dummy;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    double r_tot = 0;
    double b_tot = 0;
    double g_tot = 0;
    int pixel_count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r_tot = 0;
            b_tot = 0;
            g_tot = 0;
            pixel_count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Check that we are looking in a valid index
                    if ((i + di >= 0) && (i + di < height) && (j + dj >= 0) && (j + dj < width))
                    {
                        pixel_count++;
                        r_tot += image_copy[i + di][j + dj].rgbtRed;
                        b_tot += image_copy[i + di][j + dj].rgbtBlue;
                        g_tot += image_copy[i + di][j + dj].rgbtGreen;
                    }

                }
            }

            image[i][j].rgbtRed = (int) round(r_tot / pixel_count);
            image[i][j].rgbtBlue = (int) round(b_tot / pixel_count);
            image[i][j].rgbtGreen = (int) round(g_tot / pixel_count);
        }
    }
}





// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    double Gxy[3];
    
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    double xr_tot, xb_tot, xg_tot;
    double yr_tot, yb_tot, yg_tot;
    double Gxyr, Gxyb, Gxyg;
    int pixel_count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            xr_tot = 0;
            xb_tot = 0;
            xg_tot = 0;
            yr_tot = 0;
            yb_tot = 0;
            yg_tot = 0;
            int gx, gy;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Check that we are looking in a valid index
                    if ((i + di >= 0) && (i + di < height) && (j + dj >= 0) && (j + dj < width))
                    {
                        gx = Gx[di + 1][dj + 1];
                        gy = Gy[di + 1][dj + 1];
                        xr_tot += image_copy[i + di][j + dj].rgbtRed * gx;
                        xb_tot += image_copy[i + di][j + dj].rgbtBlue * gx;
                        xg_tot += image_copy[i + di][j + dj].rgbtGreen * gx;
                        yr_tot += image_copy[i + di][j + dj].rgbtRed * gy;
                        yb_tot += image_copy[i + di][j + dj].rgbtBlue * gy;
                        yg_tot += image_copy[i + di][j + dj].rgbtGreen * gy;
                    }
                }
            }
            
            Gxy[0] = sqrt(xr_tot * xr_tot + yr_tot * yr_tot);
            Gxy[1] = sqrt(xb_tot * xb_tot + yb_tot * yb_tot);
            Gxy[2] = sqrt(xg_tot * xg_tot + yg_tot * yg_tot);
            
            for (int a = 0; a < 3; a++)
            {
                if (Gxy[a] > 255)
                {
                    Gxy[a] = 255;
                }
            }

            image[i][j].rgbtRed = (int) round(Gxy[0]);
            image[i][j].rgbtBlue = (int) round(Gxy[1]);
            image[i][j].rgbtGreen = (int) round(Gxy[2]);
        }
    }
}
