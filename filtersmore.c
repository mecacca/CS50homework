#include "helpers.h"
#include <math.h>

// "helpers.h" is not included in this respository

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tempR = image[i][j].rgbtRed;
            int tempG = image[i][j].rgbtGreen;
            int tempB = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tempR;
            image[i][width - j - 1].rgbtGreen = tempG;
            image[i][width - j - 1].rgbtBlue = tempB;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //get a temp canvas to draw on
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            float count = 0.0;

            for (int ni = -1; ni < 2; ni++)
            {
                for (int nj = -1; nj < 2; nj++)
                {
                    if (i + ni < 0 || i + ni > height - 1 || j + nj < 0 || j + nj > width - 1)
                    {
                        continue;
                    }

                    sumRed += image[i + ni][j + nj].rgbtRed;
                    sumGreen += image[i + ni][j + nj].rgbtGreen;
                    sumBlue += image[i + ni][j + nj].rgbtBlue;

                    count++;
                }
            }

            temp[i][j].rgbtRed = round(sumRed / count);
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtBlue = round(sumBlue / count);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int nrx = 0, ngx = 0, nbx = 0, nry = 0, ngy = 0, nby = 0;


            // get reade for Gx
            for (int ni = -1; ni < 2; ni++)
            {
                for (int nj = -1; nj < 2; nj++)
                {
                    //throw out of boudary if invalid
                    if (i + ni < 0 || i + ni > height - 1 || j + nj < 0 || j + nj > width - 1)
                    {
                        continue;
                    }

                    else
                    {
                        if ((ni == -1  && nj == -1) || (ni == 1 && nj == -1))
                        {
                            nrx += (-1) * image[i + ni][j + nj].rgbtRed;
                            ngx += (-1) * image[i + ni][j + nj].rgbtGreen;
                            nbx += (-1) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if ((ni == -1 && nj == 1) || (ni == 1 && nj == 1))
                        {
                            nrx += (1) * image[i + ni][j + nj].rgbtRed;
                            ngx += (1) * image[i + ni][j + nj].rgbtGreen;
                            nbx += (1) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if ((nj == 0 && ni == -1) || (nj == 0 && ni == 0) || (nj == 0 && ni == 1))
                        {
                            nrx += (0) * image[i + ni][j + nj].rgbtRed;
                            ngx += (0) * image[i + ni][j + nj].rgbtGreen;
                            nbx += (0) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if (ni == 0 && nj == -1)
                        {
                            nrx += (-2) * image[i + ni][j + nj].rgbtRed;
                            ngx += (-2) * image[i + ni][j + nj].rgbtGreen;
                            nbx += (-2) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if (ni == 0 && nj == 1)
                        {
                            nrx += (2) * image[i + ni][j + nj].rgbtRed;
                            ngx += (2) * image[i + ni][j + nj].rgbtGreen;
                            nbx += (2) * image[i + ni][j + nj].rgbtBlue;
                        }
                    }

                }
            }


            //get ready for Gy
            for (int ni = -1; ni < 2; ni++)
            {
                for (int nj = -1; nj < 2; nj++)
                {
                    //throw out of boudary if invalid
                    if (i + ni < 0 || i + ni > height - 1 || j + nj < 0 || j + nj > width - 1)
                    {
                        continue;
                    }

                    else
                    {
                        if ((ni == -1 && nj == 1) || (ni == -1 && nj == -1))
                        {
                            nry += (-1) * image[i + ni][j + nj].rgbtRed;
                            ngy += (-1) * image[i + ni][j + nj].rgbtGreen;
                            nby += (-1) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if ((ni == 1 && nj == 1) || (ni == 1 && nj == -1))
                        {
                            nry += (1) * image[i + ni][j + nj].rgbtRed;
                            ngy += (1) * image[i + ni][j + nj].rgbtGreen;
                            nby += (1) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if ((ni == 0 && nj == -1) || (ni == 0 && nj == 0) || (ni == 0 && nj == 1))
                        {
                            nry += (0) * image[i + ni][j + nj].rgbtRed;
                            ngy += (0) * image[i + ni][j + nj].rgbtGreen;
                            nby += (0) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if (ni == -1 && nj == 0)
                        {
                            nry += (-2) * image[i + ni][j + nj].rgbtRed;
                            ngy += (-2) * image[i + ni][j + nj].rgbtGreen;
                            nby += (-2) * image[i + ni][j + nj].rgbtBlue;
                        }
                        else if (ni == 1 && nj == 0)
                        {
                            nry += (2) * image[i + ni][j + nj].rgbtRed;
                            ngy += (2) * image[i + ni][j + nj].rgbtGreen;
                            nby += (2) * image[i + ni][j + nj].rgbtBlue;
                        }
                    }

                }
            }

            // get final rgb vlaues from valid pixles
            float fr = sqrt(nrx * nrx + nry * nry);
            float fg = sqrt(ngx * ngx + ngy * ngy);
            float fb = sqrt(nbx * nbx + nby * nby);

            //throw out of boundary if exceed 255
            if (fr > 255)
            {
                fr = 255;
            }

            if (fg > 255)
            {
                fg = 255;
            }

            if (fb > 255)
            {
                fb = 255;
            }

            //paint on temp canvas
            temp[i][j].rgbtRed = round(fr);
            temp[i][j].rgbtGreen = round(fg);
            temp[i][j].rgbtBlue = round(fb);

        }
    }

    //paint back to image
    for (int ie = 0; ie < height; ie++)
    {
        for (int je = 0; je < width; je++)
        {

            image[ie][je].rgbtRed = temp[ie][je].rgbtRed;
            image[ie][je].rgbtGreen = temp[ie][je].rgbtGreen;
            image[ie][je].rgbtBlue = temp[ie][je].rgbtBlue;
        }
    }

    return;
}
