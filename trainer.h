#ifndef TRAINER_H
#define TRAINER_H

#include "mlp.h"

//Treina uma rede neural através dos dados foneecidos
void trainer(layer* l,T* data,T* exp_value,T error, T taxa, int max_interation);

//Calcula o erro relativo da útima camada
void deltaLastLayer(layer *l,T* exp_value,T* d_out);

//Calcula o erro das camadas anteriores
void deltaHidenLayer(layer* l,T* d_in,T* d_out);

//Atualiza a matriz de erro de uma dada camada
void weightUpdade(layer* l,T* erro,T taxa);

//Calcula o erro médio da última camada
T averageError(layer* l, T* exp_value);

#endif
