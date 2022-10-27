#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((double)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[width];

    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1, k = 0; k < width; j--, k++)
        {
            temp[k] = image[i][j];
        }
        for (int n = 0; n < width; n++)
        {
            image[i][n] = temp[n];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*buffer)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int n = 0; n < height; n++)
    {
        for (int m = 0; m < width; m++)
        {
            buffer[n][m] = image[n][m];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((double)(buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed
                                             + buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 4);

                image[i][j].rgbtGreen = round((double)(buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen
                                               + buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 4);

                image[i][j].rgbtBlue = round((double)(buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue
                                              + buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 4);
            }
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((double)(buffer[i][j].rgbtRed + buffer[i][j - 1].rgbtRed
                                             + buffer[i + 1][j].rgbtRed + buffer[i + 1][j - 1].rgbtRed) / 4);

                image[i][j].rgbtGreen = round((double)(buffer[i][j].rgbtGreen + buffer[i][j - 1].rgbtGreen
                                               + buffer[i + 1][j].rgbtGreen + buffer[i + 1][j - 1].rgbtGreen) / 4);

                image[i][j].rgbtBlue = round((double)(buffer[i][j].rgbtBlue + buffer[i][j - 1].rgbtBlue
                                              + buffer[i + 1][j].rgbtBlue + buffer[i + 1][j - 1].rgbtBlue) / 4);
            }
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((double)(buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed
                                             + buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed) / 4);

                image[i][j].rgbtGreen = round((double)(buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen
                                               + buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen) / 4);

                image[i][j].rgbtBlue = round((double)(buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue
                                              + buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue) / 4);
            }
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((double)(buffer[i][j].rgbtRed + buffer[i][j - 1].rgbtRed
                                             + buffer[i - 1][j].rgbtRed + buffer[i - 1][j - 1].rgbtRed) / 4);

                image[i][j].rgbtGreen = round((double)(buffer[i][j].rgbtGreen + buffer[i][j - 1].rgbtGreen
                                               + buffer[i - 1][j].rgbtGreen + buffer[i - 1][j - 1].rgbtGreen) / 4);

                image[i][j].rgbtBlue = round((double)(buffer[i][j].rgbtBlue + buffer[i][j - 1].rgbtBlue
                                              + buffer[i - 1][j].rgbtBlue + buffer[i - 1][j - 1].rgbtBlue) / 4);
            }
            else if (i == 0)
            {
                image[i][j].rgbtRed = round((double)(buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed
                                             + buffer[i][j + 1].rgbtRed + buffer[i + 1][j - 1].rgbtRed
                                             + buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 6);

                image[i][j].rgbtGreen = round((double)(buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen
                                               + buffer[i][j + 1].rgbtGreen + buffer[i + 1][j - 1].rgbtGreen
                                               + buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 6);

                image[i][j].rgbtBlue = round((double)(buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue
                                              + buffer[i][j + 1].rgbtBlue + buffer[i + 1][j - 1].rgbtBlue
                                              + buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 6);
            }
            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round((double)(buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed
                                             + buffer[i][j + 1].rgbtRed + buffer[i - 1][j - 1].rgbtRed
                                             + buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed) / 6);

                image[i][j].rgbtGreen = round((double)(buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen
                                               + buffer[i][j + 1].rgbtGreen + buffer[i - 1][j - 1].rgbtGreen
                                               + buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen) / 6);

                image[i][j].rgbtBlue = round((double)(buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue
                                              + buffer[i][j + 1].rgbtBlue + buffer[i - 1][j - 1].rgbtBlue
                                              + buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue) / 6);
            }
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((double)(buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed
                                             + buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed
                                             + buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 6);

                image[i][j].rgbtGreen = round((double)(buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen
                                               + buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen
                                               + buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 6);

                image[i][j].rgbtBlue = round((double)(buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue
                                              + buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue
                                              + buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 6);
            }
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round((double)(buffer[i - 1][j - 1].rgbtRed + buffer[i - 1][j].rgbtRed
                                             + buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed
                                             + buffer[i + 1][j - 1].rgbtRed + buffer[i + 1][j].rgbtRed) / 6);

                image[i][j].rgbtGreen = round((double)(buffer[i - 1][j - 1].rgbtGreen + buffer[i - 1][j].rgbtGreen
                                               + buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen
                                               + buffer[i + 1][j - 1].rgbtGreen + buffer[i + 1][j].rgbtGreen) / 6);

                image[i][j].rgbtBlue = round((double)(buffer[i - 1][j - 1].rgbtBlue + buffer[i - 1][j].rgbtBlue
                                              + buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue
                                              + buffer[i + 1][j - 1].rgbtBlue + buffer[i + 1][j].rgbtBlue) / 6);
            }
            else
            {
                image[i][j].rgbtRed = round((double)(buffer[i - 1][j - 1].rgbtRed + buffer[i - 1][j].rgbtRed + buffer[i - 1][j + 1].rgbtRed
                                             + buffer[i][j - 1].rgbtRed + buffer[i][j].rgbtRed + buffer[i][j + 1].rgbtRed
                                             + buffer[i + 1][j - 1].rgbtRed + buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed) / 9);

                image[i][j].rgbtGreen = round((double)(buffer[i - 1][j - 1].rgbtGreen + buffer[i - 1][j].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen
                                               + buffer[i][j - 1].rgbtGreen + buffer[i][j].rgbtGreen + buffer[i][j + 1].rgbtGreen
                                               + buffer[i + 1][j - 1].rgbtGreen + buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen) / 9);

                image[i][j].rgbtBlue = round((double)(buffer[i - 1][j - 1].rgbtBlue + buffer[i - 1][j].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue
                                              + buffer[i][j - 1].rgbtBlue + buffer[i][j].rgbtBlue + buffer[i][j + 1].rgbtBlue
                                              + buffer[i + 1][j - 1].rgbtBlue + buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue) / 9);
            }
        }
    }

    free(buffer);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*buffer)[width] = calloc(height, (width) * sizeof(RGBTRIPLE));

    long gx;
    long gy;
    double value;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j].rgbtRed = image[i][j].rgbtRed;
            buffer[i][j].rgbtGreen = image[i][j].rgbtGreen;
            buffer[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                gx = 2 * buffer[i][j + 1].rgbtRed + buffer[i + 1][j + 1].rgbtRed;
                gy = 2 * buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = value;
                }

                gx = 2 * buffer[i][j + 1].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;
                gy = 2 * buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = 2 * buffer[i][j + 1].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;
                gy = 2 * buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else if (i == 0 && j == width - 1)
            {
                gx = -2 * buffer[i][j - 1].rgbtRed - buffer[i + 1][j - 1].rgbtRed;
                gy = 2 * buffer[i + 1][j].rgbtRed + buffer[i + 1][j - 1].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = -2 * buffer[i][j - 1].rgbtGreen - buffer[i + 1][j - 1].rgbtGreen;
                gy = 2 * buffer[i + 1][j].rgbtGreen + buffer[i + 1][j - 1].rgbtGreen;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = -2 * buffer[i][j - 1].rgbtBlue - buffer[i + 1][j - 1].rgbtBlue;
                gy = 2 * buffer[i + 1][j].rgbtBlue + buffer[i + 1][j - 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else if (i == height - 1 && j == 0)
            {
                gx = 2 * buffer[i][j + 1].rgbtRed + buffer[i - 1][j + 1].rgbtRed;
                gy = -2 * buffer[i - 1][j].rgbtRed - buffer[i - 1][j + 1].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = 2 * buffer[i][j + 1].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen;
                gy = -2 * buffer[i - 1][j].rgbtGreen - buffer[i - 1][j + 1].rgbtGreen;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = 2 * buffer[i][j + 1].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue;
                gy = -2 * buffer[i - 1][j].rgbtBlue - buffer[i - 1][j + 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else if (i == height - 1 && j == width - 1)
            {
                gx = -2 * buffer[i][j - 1].rgbtRed - buffer[i - 1][j - 1].rgbtRed;
                gy = -2 * buffer[i - 1][j].rgbtRed - buffer[i - 1][j - 1].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = -2 * buffer[i][j - 1].rgbtGreen - buffer[i - 1][j - 1].rgbtGreen;
                gy = -2 * buffer[i - 1][j].rgbtGreen - buffer[i - 1][j - 1].rgbtGreen;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = -2 * buffer[i][j - 1].rgbtBlue - buffer[i - 1][j - 1].rgbtBlue;
                gy = -2 * buffer[i - 1][j].rgbtBlue - buffer[i - 1][j - 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else if (i == 0)
            {
                gx = -2 * buffer[i][j - 1].rgbtRed + 2 * buffer[i][j + 1].rgbtRed - buffer[i + 1][j - 1].rgbtRed + buffer[i + 1][j + 1].rgbtRed;
                gy = buffer[i + 1][j - 1].rgbtRed + 2 * buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = -2 * buffer[i][j - 1].rgbtGreen + 2 * buffer[i][j + 1].rgbtGreen - buffer[i + 1][j - 1].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;
                gy = buffer[i + 1][j - 1].rgbtGreen + 2 * buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = -2 * buffer[i][j - 1].rgbtBlue + 2 * buffer[i][j + 1].rgbtBlue - buffer[i + 1][j - 1].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;
                gy = buffer[i + 1][j - 1].rgbtBlue + 2 * buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else if (i == height - 1)
            {
                gx = -1 * buffer[i - 1][j - 1].rgbtRed + buffer[i - 1][j + 1].rgbtRed - 2 * buffer[i][j - 1].rgbtRed + 2 * buffer[i][j + 1].rgbtRed;
                gy = -1 * buffer[i - 1][j - 1].rgbtRed - 2 * buffer[i - 1][j].rgbtRed - buffer[i - 1][j + 1].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = -1 * buffer[i - 1][j - 1].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen - 2 * buffer[i][j - 1].rgbtGreen + 2 * buffer[i][j + 1].rgbtGreen;
                gy = -1 * buffer[i - 1][j - 1].rgbtGreen - 2 * buffer[i - 1][j].rgbtGreen - buffer[i - 1][j + 1].rgbtGreen;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = -1 * buffer[i - 1][j - 1].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue - 2 * buffer[i][j - 1].rgbtBlue + 2 * buffer[i][j + 1].rgbtBlue;
                gy = -1 * buffer[i - 1][j - 1].rgbtBlue - 2 * buffer[i - 1][j].rgbtBlue - buffer[i - 1][j + 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else if (j == 0)
            {
                gx = buffer[i - 1][j + 1].rgbtRed + 2 * buffer[i][j + 1].rgbtRed + buffer[i + 1][j + 1].rgbtRed;
                gy = -2 * buffer[i - 1][j].rgbtRed - buffer[i - 1][j + 1].rgbtRed + 2 * buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = buffer[i - 1][j + 1].rgbtGreen + 2 * buffer[i][j + 1].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;
                gy = -2 * buffer[i - 1][j].rgbtGreen - buffer[i - 1][j + 1].rgbtGreen + 2 * buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = buffer[i - 1][j + 1].rgbtBlue + 2 * buffer[i][j + 1].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;
                gy = -2 * buffer[i - 1][j].rgbtBlue - buffer[i - 1][j + 1].rgbtBlue + 2 * buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else if (j == width - 1)
            {
                gx = -1 * buffer[i - 1][j - 1].rgbtRed - 2 * buffer[i][j - 1].rgbtRed - buffer[i + 1][j - 1].rgbtRed;
                gy = -1 * buffer[i - 1][j - 1].rgbtRed - 2 * buffer[i - 1][j].rgbtRed + buffer[i + 1][j - 1].rgbtRed + 2 * buffer[i + 1][j].rgbtRed;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = -1 * buffer[i - 1][j - 1].rgbtGreen - 2 * buffer[i][j - 1].rgbtGreen - buffer[i + 1][j - 1].rgbtGreen;
                gy = -1 * buffer[i - 1][j - 1].rgbtGreen - 2 * buffer[i - 1][j].rgbtGreen + buffer[i + 1][j - 1].rgbtGreen + 2 * buffer[i + 1][j].rgbtGreen;

                value = sqrt((gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = -1 * buffer[i - 1][j - 1].rgbtBlue - 2 * buffer[i][j - 1].rgbtBlue - buffer[i + 1][j - 1].rgbtBlue;
                gy = -1 * buffer[i - 1][j - 1].rgbtBlue - 2 * buffer[i - 1][j].rgbtBlue + buffer[i + 1][j - 1].rgbtBlue + 2 * buffer[i + 1][j].rgbtBlue;

                value = sqrt((gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
            else
            {
                gx = -1 * buffer[i - 1][j - 1].rgbtRed + buffer[i - 1][j + 1].rgbtRed - 2 * buffer[i][j - 1].rgbtRed + 2 * buffer[i][j + 1].rgbtRed - buffer[i + 1][j - 1].rgbtRed + buffer[i + 1][j + 1].rgbtRed;
                gy = -1 * buffer[i - 1][j - 1].rgbtRed - 2 * buffer[i - 1][j].rgbtRed - buffer[i - 1][j + 1].rgbtRed + buffer[i + 1][j - 1].rgbtRed + 2 * buffer[i + 1][j].rgbtRed + buffer[i + 1][j + 1].rgbtRed;

                value = sqrt((gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = round(value);
                }

                gx = -1 * buffer[i - 1][j - 1].rgbtGreen + buffer[i - 1][j + 1].rgbtGreen - 2 * buffer[i][j - 1].rgbtGreen + 2 * buffer[i][j + 1].rgbtGreen - buffer[i + 1][j - 1].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;
                gy = -1 * buffer[i - 1][j - 1].rgbtGreen - 2 * buffer[i - 1][j].rgbtGreen - buffer[i - 1][j + 1].rgbtGreen + buffer[i + 1][j - 1].rgbtGreen + 2 * buffer[i + 1][j].rgbtGreen + buffer[i + 1][j + 1].rgbtGreen;

                value = sqrt((gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = round(value);
                }

                gx = -1 * buffer[i - 1][j - 1].rgbtBlue + buffer[i - 1][j + 1].rgbtBlue - 2 * buffer[i][j - 1].rgbtBlue + 2 * buffer[i][j + 1].rgbtBlue - buffer[i + 1][j - 1].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;
                gy = -1 * buffer[i - 1][j - 1].rgbtBlue - 2 * buffer[i - 1][j].rgbtBlue - buffer[i - 1][j + 1].rgbtBlue + buffer[i + 1][j - 1].rgbtBlue + 2 * buffer[i + 1][j].rgbtBlue + buffer[i + 1][j + 1].rgbtBlue;

                value = sqrt((double)(gx * gx) + (gy * gy));

                if (value > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = round(value);
                }
            }
        }
    }
    free(buffer);
    return;
}