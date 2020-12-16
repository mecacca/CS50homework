#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtBlue = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get old and new RGB values
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int nr = round(.393 * r +  .769 * g + .189 * b);
            int ng = round(.349 * r + .686 * g + .168 * b);
            int nb = round(.272 * r + .534 * g + .131 * b);

            //set the new RGB values
            if (nr > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = nr;
            }

            if (ng > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = ng;
            }

            if (nb > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = nb;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int or = image[i][j].rgbtRed;
            int og = image[i][j].rgbtGreen;
            int ob = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            image[i][width - (j + 1)].rgbtRed = or;
            image[i][width - (j + 1)].rgbtGreen = og;
            image[i][width - (j + 1)].rgbtBlue = ob;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a temporary canvas to draw pixels on
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            float counter = 0.0;

            for (int v = -1; v < 2; v++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if (i + v < 0 || i + v > height - 1  || j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }

                    sumR += image[i + v][j + w].rgbtRed;
                    sumG += image[i + v][j + w].rgbtGreen;
                    sumB += image[i + v][j + w].rgbtBlue;

                    counter++;
                }
            }

            temp[i][j].rgbtRed = round(sumR / counter);
            temp[i][j].rgbtGreen = round(sumG / counter);
            temp[i][j].rgbtBlue = round(sumB / counter);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue =  temp[i][j].rgbtBlue;
        }
    }

    return;
}

