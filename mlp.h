#ifndef MLP_H
#define MLP_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef double T;

struct pl{

	// x : input
	// y : output
	// l : x * W	
	T*	y;
	T* l;

	//W : weight
	T** W;

	//Pointers to adjacent layers
	struct pl* nxt_layer;
	struct pl* prv_layer; 

	//No of nodes and inputs
	int n_nodes,n_inputs;

	

};

typedef struct pl layer;

//Evaluate Layer
void layerEval(layer* l,T* input);

//Layer initialization
int layerInit(layer* l,int n_inputs,int n_layers);

//Layer connection
int layerConn(layer* l1, layer* l2);

//Aplica a função de saída ReLU
void relu(layer* l);

T reluDiff(T in);

//
void forwardPropagation(layer* l);

void HadamardProduct(T* x, T** W,T* y,int n_inputs,int n_nodes);

//Inicializa os pesos da rede com valores aleatórios
void weightRandInit(layer* l);

#endif
