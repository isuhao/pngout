
#define WIDTH 		640
#define HEIGHT		480
#define NUM_PIXELS	(WIDTH*HEIGHT)
#define IMAGE_SIZE	(NUM_PIXELS*3)

// for array of green values
#define XVAL_A(idx)	((idx)%WIDTH +1)
#define YVAL_A(idx)	(HEIGHT - ((idx)/WIDTH))

// for image with width of 3
#define XVAL_I(idx)	((idx/3)%WIDTH +1)
#define YVAL_I(idx)	(HEIGHT - ((idx/3)/WIDTH))

#define BYTE_TO_INT_COLOR(col)		(int)(col*(65536/256))

struct image {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[640 * 480 * 3 + 1];
}; 

void subtraction_filter_green(unsigned char *out, unsigned char *left, unsigned char *right);
void subtraction_green_filter(unsigned char *out, struct image* left, struct image* right);
void green_filter(struct image* img, unsigned char *arr);
void save_green_arr(unsigned char *arr, char* filename);