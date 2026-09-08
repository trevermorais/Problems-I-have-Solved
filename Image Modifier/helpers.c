#include "bmp.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float red = 0.0, green = 0.0, blue = 0.0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            int upd = round((red + green + blue) / 3.0);

            image[i][j].rgbtRed = upd;
            image[i][j].rgbtGreen = upd;
            image[i][j].rgbtBlue = upd;
        }
    }
}
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue));
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            int sepiaGreen = round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue));
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            int sepiaBlue = round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue));
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int opp = width - 1 - j;
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][opp];
            image[i][opp] = temp;
        }
    }
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float total_red = 0, total_green = 0, total_blue = 0;
            float counter = 0.00;

            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int neighbor_row = i + r;
                    int neighbor_col = j + c;

                    if (neighbor_row < 0 || neighbor_row >= height || neighbor_col < 0 || neighbor_col >= width)
                    {
                        continue;
                    }

                    total_red += copy[neighbor_row][neighbor_col].rgbtRed;
                    total_green += copy[neighbor_row][neighbor_col].rgbtGreen;
                    total_blue += copy[neighbor_row][neighbor_col].rgbtBlue;
                    counter++;
                }
            }

            image[i][j].rgbtRed = round(total_red / counter);
            image[i][j].rgbtGreen = round(total_green / counter);
            image[i][j].rgbtBlue = round(total_blue / counter);
        }
    }
}
