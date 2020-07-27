#include "helpers.h"
#include <math.h>
#include <stdio.h>

float roundTo255(float current_value);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            RGBTRIPLE color = image[i][j];
            BYTE average = round((color.rgbtBlue + color.rgbtGreen + color.rgbtRed)/3.0);
            color.rgbtBlue = average;
            color.rgbtGreen = average;
            color.rgbtRed = average;
            image[i][j] = *&color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            RGBTRIPLE color = image[i][j];
            color.rgbtRed = roundTo255(.393 * image[i][j].rgbtRed  + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            color.rgbtGreen = roundTo255(.349 * image[i][j].rgbtRed  + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            color.rgbtBlue = roundTo255(.272 * image[i][j].rgbtRed  + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j] = *&color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int top_half_width_range = width/2;
    for (int i=0; i<top_half_width_range; i++)
    {
        for (int j=0; j<height; j++)
        {
            RGBTRIPLE tmp = image[j][i];
            image[j][i] = image[j][width-i-1];
            image[j][width-i-1] = tmp;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE duplicate_image[height][width];
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            duplicate_image[i][j]= image[i][j];
            duplicate_image[i][j] = image[i][j];
            duplicate_image[i][j] = image[i][j];
        }
    }

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            float total[3] = {0,0,0};

            float number_of_pixels = 0;

            for(int k=i-1; k<=(i+1); k++)
            {
                for(int l=j-1; l<=(j+1); l++)
                {
                    if (!(k < 0 || l < 0 || k >= height || l >= width))
                    {
                        total[0] += duplicate_image[k][l].rgbtRed;
                        total[1] += duplicate_image[k][l].rgbtGreen;
                        total[2] += duplicate_image[k][l].rgbtBlue;
                        number_of_pixels++;
                    }
                }
            }
            image[i][j].rgbtRed = round(total[0]/number_of_pixels);
            image[i][j].rgbtGreen = round(total[1]/number_of_pixels);
            image[i][j].rgbtBlue = round(total[2]/number_of_pixels);
        }
    }
    return;
}

float roundTo255(float current_value)
{
    if(current_value > 255)
    {
        return 255;
    }
    else
    {
        return round(current_value);
    }
}