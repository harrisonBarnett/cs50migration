#include "helpers.h"
#include <math.h>
#include <stddef.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) // iterate thru height
	{
		for (int w = 0; w < width; w++) // iterate thru width
		{
			int tempBlue = image[h][w].rgbtBlue; // create temporary rgb values
			int tempGreen = image[h][w].rgbtGreen;
			int tempRed = image[h][w].rgbtRed;

			int grayScale = round((tempBlue + tempGreen + tempRed) / 3.0); // take avg of all rgb values

			image[h][w].rgbtBlue = image[h][w].rgbtGreen = image[h][w].rgbtRed = grayScale; // set rgb values to the avg to achieve grayscale
		}

	}

    return;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) // iterate thru height
	{
		for (int w = 0; w < width; w++) // iterate thru width
		{
			int blue = image[h][w].rgbtBlue; // create temp rgb values
			int green = image[h][w].rgbtGreen;
			int red = image[h][w].rgbtRed;

			int sBlue = round(.272 * red + .534 * green + .131 * blue); // algos for creating sepia tone for each rgb value
			int sGreen = round(.349 * red + .686 * green + .168 * blue);
			int sRed = round(.393 * red + .769 * green + .189 * blue);

			if(sBlue > 255) // make sure no rgb value lies outside of max value of 255
			{
				sBlue = 255;
			}
			if(sGreen > 255)
			{
				sGreen = 255;
			}
			if(sRed > 255)
			{
				sRed = 255;
			}

			image[h][w].rgbtBlue = sBlue; // pass new values into the pixel located at [h][w]
			image[h][w].rgbtGreen = sGreen;
			image[h][w].rgbtRed = sRed;

		}
	}
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h ++) // iterate thru height
	{
		for (int w = 0; w < width / 2; w++) // iterate thru midline of width
		{
			RGBTRIPLE temp = image[h][w]; // make temporary pixel of [h][w]

			image[h][w] = image[h][(width - 1) - w]; // pass "opposite" pixel into [h][w]
			image[h][(width - w) - 1] = temp; // pass temp pixel into "opposite" pixel

			// the above operations do the work of manipulating the image in half the time
			// as two swaps occurs for every one iteration
		}
	}

    return;
}


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // create a new copy of the file
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			temp[h][w] = image[h][w];
		}
	}

	for (int h = 0; h < height; h++) // iterate thru height
	{
		for (int w = 0; w < width; w++) // iterate thru width
		{
			float counter = 0; // set counters/sums
			int bAvg = 0;
			int gAvg = 0;
			int rAvg = 0;

			for (int hh = -1; hh < 2; hh++) // we "create" a "box" of +-1 pixel around [h][w]
			{
				for (int ww = -1; ww < 2; ww++)
				{
					if(hh + h < 0 || hh + h >= height) // check to see if pixel lies outside the image's memory
					{
					    continue;
					}
					if(ww + w < 0 || ww + w >= width)
					{
					    continue;
					}
						bAvg += temp[hh + h][ww + w].rgbtBlue; // update sums
						gAvg += temp[hh + h][ww + w].rgbtGreen;
						rAvg += temp[hh + h][ww + w].rgbtRed;
						counter++;



				}
			}

			image[h][w].rgbtBlue = round(bAvg / counter); // update original image's pixels at [h][w]
			image[h][w].rgbtGreen = round(gAvg / counter);
			image[h][w].rgbtRed = round(rAvg / counter);

			// we use a temporary file in this function as we would be blurring an already blurred image
			// unless we pull value from a controlled image
		}
	}
    return;
}

