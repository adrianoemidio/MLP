#include "mlp.h"


//Layer initialization
int layerInit(layer* l, int n_inputs,int n_nodes)
{
	
	//Define o No de nodos e No de entrada de cada nodo
	l->n_inputs = n_inputs;
	l->n_nodes = n_nodes;

	//Inicia o layer não conectado
	l->nxt_layer = NULL;
	l->prv_layer = NULL;

	//Aloca espaço para a matrix de pesos
	l->W = (T**)malloc(l->n_inputs * sizeof(T*));

	if(l->W == NULL)
		return 0;

	for(int i=0; i < l->n_nodes; i++)
		l->W[i] = (T*)malloc(l->n_nodes * sizeof(T*));
		
		
	//Aloca espaço para o vetor intermediário
	l->l = (T*)malloc(l->n_nodes * sizeof(T*));
	
	if(l->l == NULL)
		return 0;
		
	//Aloca o espaço para o vetor de saída
	l->y = (T*)malloc(l->n_nodes * sizeof(T*));
	
	if(l->y == NULL)
		return 0;


	return 1;

}

//Calucula a saida do layer
void layerEval(layer* l, T* input)
{
	//Multiplca o peso pelas entradas
	HadamardProduct(input,l->W,l->l,l->n_inputs,l->n_nodes);
	
	//Aplica a função de saída
	relu(l);
	
}

//Conecta um layer no outro
int layerConn(layer* l1, layer* l2)
{
	//Conecta o layer 1 ao layer 2
	l1->nxt_layer = l2;
	
	//Conecta o layer 2 ao layer 1
	l2->prv_layer = l1;

	return 0;
}

//Aplica a função de saída ReLU
void relu(layer* l)
{
	//Aplica a função a saida à todos os nodos
	for(int i = 0; i < l->n_nodes; i++)
	{
		if(l->l > 0)
			l->y = l->l;
		else
			l->y = 0;
		
	}
	
}

//Função de saída diferenciada
T reluDiff(T in)
{
	if(in > 0)
		return 1;
	
	return 0;
	
}

//Propaga o sinal para frente em toda a rede
void forwardPropagation(layer* l)
{
	
	//Percorre a rede até o último nodo
	while(l->nxt_layer != NULL)
	{
		//Acessa o próximo layer
		l = l->nxt_layer;
		
		//Propaga o sinal do layer anterior para o próximo
		layerEval(l,l->prv_layer->y);
		
		
	}
	
	
}

//Calcula o produto de Hadamard
void HadamardProduct(T* x, T** W, T* y,int n_inputs,int n_nodes)
{

	//Calcula o produto para todos os nodos
	for(int  i = 0; i < n_nodes; i++)
	{
		y[i] = 0;
		
		//Calcula o resultado para cada entrada em um nodo específico
		for(int j = 0; j < n_inputs; j++)
		{
			y[i] += (x[j] * W[j][i] );
			
		}
	}

}

//Inicializa os pesos da rede com valores aleatórios
void weightRandInit(layer* l)
{
	srand(time(NULL));
	
	long n = (long)RAND_MAX;
	
	n++;
	
	for(int i=0; i < l->n_inputs; i++)
		for(int j=0; j < l->n_nodes; j++)
		{
			l->W[i][j] = (T)((-1) + (rand() / (double)(n) * (1 - (-1) + 1)));
		}

	
}
