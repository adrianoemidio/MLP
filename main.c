#include "mlp.h"
#include "trainer.h"
#include "files.h"

int main()
{
	
	//Nnúmeros de layers
	int n;
	int n_nos,n_in;

	unsigned char** img;
	
	int size_x, size_y;
	
	//Lê a imagem
	img = readBitMap("gray.bmp",&size_x,&size_y);
	
	printf("x:%d y:%d\n",size_x,size_y);
	
	//Imprime a imagem
	/*for(int i = 0; i < size_x; i++)
	{
		for(int j = 0; j < size_y; j++)
			printf("%d ",img[i][j]);
	
		printf("\n");
	}*/
			
	return 0;
	
	printf("Insira o No de Layers:\n");
	
	//Aloca a memória para o No de layers
	layer* rede = (layer*)malloc(n*sizeof(layer*));

	//Inicia o primeiro Layer
	printf("Digite o No de neuronios no %1o layer:\n");
	scanf("%d",&n_nos);
	printf("Digite o numero de entrada para o  1o nodo:\n");
	scanf("%d",&n_in);
	//Inicializa o nodo
	layerInit(&rede[0],n_in,n_nos);
	

	//inicializa os outros layers
	for(int i = 1; i < n; i++)
	{
		
		//Conecta os layers
		layerConn(&rede[i-1],&rede[i]);
		
		int new_no; 
		
		printf("Digite o No de neuronios no %do layer:\n",(i+1));
		scanf("%d",&new_no);
		//Inicializa o nodo
		layerInit(&rede[i],n_nos,new_no);
		
		n_nos = new_no;				
		
		
	}
	
	


/*	for(int i=0;i<2;i++)
		for(int j=0; j<3; j++)
			scanf("%lf",&teste.W[i][j]);




	//printf("Vc digitou:\n");

	for(int i=0;i < teste.n_inputs;i++)
	{
		for(int j=0; j < teste.n_nodes; j++)
			printf("%lf ",teste.W[i][j]);

		printf("\n");

	}*/
}
