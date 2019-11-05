#ifndef FILES_H
#define FILES_H

#include "mlp.h"

typedef char* string;


typedef struct
{
	int signature;
	int file_size;
	int p_array_offset;
	int header_size;
	int width;
	int height;
	int bits_px;
	int img_size;
	
}bmp_h;

//Le o arquivo BMP especificado pelo f_name
unsigned char** readBitMap(string f_name,int* size_x, int* size_y);


#endif
