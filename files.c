#include "files.h"

//Le o arquivo BMP especificado pelo f_name
unsigned char** readBitMap(string f_name,int* size_x, int* size_y)
{
	//Cabeçallho dos arquivos bmp
	unsigned char bmp_header[54];
	
	//Ponteiro para o arquivo
	FILE* f = fopen(f_name,"rb");
	
	//Le o cabeçalho do arquivo
	fread(bmp_header,1,54,f);
	
	//Crian um novo cabeçalho
	bmp_h head;
		
	//A altura e o tamanho da imagem
	head.width = bmp_header[18] + ( ((int)bmp_header[19]) << 8) + ( ((int)bmp_header[20]) << 16) + ( ((int)bmp_header[21]) << 24);
    head.height = bmp_header[22] + ( ((int)bmp_header[23]) << 8) + ( ((int)bmp_header[24]) << 16) + ( ((int)bmp_header[25]) << 24);

	
	//Alinha as linhas de 4 em 4 bytes
    int line_size = (head.width / 8 + (head.width / 8) % 4);
    int file_size = line_size * head.height;
    
	
	//Le o tamanho do vetor imagem    
    head.img_size = bmp_header[0x22] + (((int)bmp_header[0x23]) << 8) + ( ((int)bmp_header[0x24]) << 16) + ( ((int)bmp_header[0x25]) << 24);
    
    //Le o endereço que inicia o bitmap 
    head.p_array_offset = bmp_header[0x0A] + ( ((int)bmp_header[0x0B]) << 8) + ( ((int)bmp_header[0x0C]) << 16) + ( ((int)bmp_header[0x0D]) << 24);

	//Aloca a memória para imagem
	unsigned char** out;
	
	out = (unsigned char**)malloc(head.width * sizeof(unsigned char*));

	for(int i=0; i < head.width; i++)
		out[i] = (unsigned char*)malloc(head.height * sizeof(unsigned char*));
    
    
    //Aloca memória para data
    unsigned char* data = malloc(head.img_size);
        

	//Pula para imagem
	fseek(f,head.p_array_offset,SEEK_SET);

    //le o arquivo
    fread(data,1,head.img_size,f);


    //Lê todos os bits
    for(int i = (head.p_array_offset + head.img_size); i >= head.p_array_offset; i--)
	{
		int c = ((head.p_array_offset + head.img_size) - i);
		int h = c/28;
		
		if(c > ((h*28)+2))
			out[(24-((c%28)-3))][h] = data[c] ? 0x01:0x00;
		
			//printf("data:%d\n x:%d y:%d\n",c,(24-((c%28)-3)),h);
			
			
	}
   
   
   	//Imprime a imagem
	for(int i = 0; i < head.width; i++)
	{
		for(int j = 0; j < head.height; j++)
			printf("%d ",out[j][i]);
	
		printf("\n");
	}
	
	//Libera a memória utilizada pela imagem
    free(data);
    //Retorna os tamanho da imagem
    *(size_x) = head.width; 
    *(size_y) = head.height;
    
    return out;
	
}
