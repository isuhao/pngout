/*
 Simple program for robot image data as png
*/
#include <pngwriter.h>
#include <stdio.h>
#include "images.h"
#include "point.h"

#define POINT_BUFFER_LENGTH		200
#define MAX_COLUMNS				30
#define RADIUS					5

extern struct image no_dots_image;
extern struct image dots_image;

void png_image(struct image *img, char* filename)
{
	pngwriter image(640, 480, 1.0, filename); 

	for( int i = 0; i < IMAGE_SIZE; i+=3 )
	{
		image.plot(XVAL_I(i), YVAL_I(i), BYTE_TO_INT_COLOR(img->pixel_data[i]), 
			BYTE_TO_INT_COLOR(img->pixel_data[i+1]), BYTE_TO_INT_COLOR(img->pixel_data[i+2]));
	}

	image.close();
}

void png_image_cir(struct image *img, char* filename, int num_centers, int (*centers)[2])
{
	pngwriter image(640, 480, 1.0, filename); 

	for( int i = 0; i < IMAGE_SIZE; i+=3 )
	{
		image.plot(XVAL_I(i), YVAL_I(i), BYTE_TO_INT_COLOR(img->pixel_data[i]), 
			BYTE_TO_INT_COLOR(img->pixel_data[i+1]), BYTE_TO_INT_COLOR(img->pixel_data[i+2]));
	}

	for(int i = 0; i < num_centers; i++)
	{
		int x = centers[i][0] + 1;
		int y = HEIGHT - (centers[i][1] + 1);
		image.circle(x, y, RADIUS, 1.0, 0.0, 0.0);
	}

	image.close();
}

void png_green_arr_cir(unsigned char* arr, char* filename, int num_centers, int (*centers)[2])
{
	pngwriter image(640, 480, 1.0, filename); 

	for( int i = 0; i < NUM_PIXELS; i++ )
	{
		image.plot(XVAL_A(i), YVAL_A(i), 0, 
			BYTE_TO_INT_COLOR(*(arr++)), 0);
	}

	for(int i = 0; i < num_centers; i++)
	{
		int x = centers[i][0] + 1;
		int y = HEIGHT - (centers[i][1] + 1);
		image.circle(x, y, RADIUS, 1.0, 0.0, 0.0);
	}

	image.close();
}

int main() 
{
	unsigned char working_green[NUM_PIXELS];
	int center_points[POINT_BUFFER_LENGTH][2];
	int num_points = 0;
	int num_columns = 0;
	int col_idx[MAX_COLUMNS];

	subtraction_green_filter(working_green, &dots_image, &no_dots_image);

	num_points = point_finder(working_green, center_points, POINT_BUFFER_LENGTH);

	num_columns = sort_by_col(center_points, num_points, col_idx, MAX_COLUMNS);

	png_green_arr_cir(working_green, "working.png", num_points, center_points);
	png_image(&dots_image, "dots.png");
	png_image_cir(&dots_image, "dots_cir.png", num_points, center_points);
	png_image_cir(&no_dots_image, "no_dots_cir.png", num_points, center_points);

	return 0; 
}