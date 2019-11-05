#include "trainer.h"


//Treina uma rede neural através dos dados foneecidos
void trainer(layer* l,T* data,T* exp_value,T error, T taxa, int max_interation)
{
	
	//Novo erro
	T new_error = error + 1;
	
	//variável para contar o No de interações
	int count = 0;
	
	
	//variavel temporária
	layer* temp;
	
	//Percorre todos os layer, colocarndo valor aleatório nos pesos
	while(temp != NULL)
	{
		//Cola um valor aleatório nos pesos
		weightRandInit(temp);
		
		//decrementa o layer
		temp = temp->prv_layer;
	}
	
	
	//Calucula até um limite ou até encontar o erro
	while((new_error > error) && ( count < max_interation))
	{
		
		//Propaga o sinal para "Frente"
		//Calcula o primeiro Layer
		layerEval(temp,data);
		//Calcula todas as camadas escondidas
		forwardPropagation(temp);
		
		//Calcula o erro relativo
		new_error =  averageError(l,exp_value);
		
		//Se o erro for menor que o desejado, atualiza os pesos
		if(new_error > error)
			weightUpdade(l,exp_value,taxa);
		
		//Incrementa o contador do No de interações
		count++;
	}
	
	
}


//Calcula o erro relativo da útima camada
void deltaLastLayer(layer *l,T* exp_value,T* d_out)
{
	for(int i = 0; i < l->n_nodes; i++)
		d_out[i] = (exp_value[i] - l->y[i])*(reluDiff(l->l[i]));
}

//Calcula o erro das camadas anteriores
void deltaHidenLayer(layer* l,T* d_in,T* d_out)
{

	
	//Calcula o erro para todos os nodos
	for(int i = 0;i < l->n_nodes; i++)
	{
		//Variável que acumula o resulatdo da soma
		T acc = 0;
		
		//Efetua o produto dos erros pelos pesos da camada anterior
		for(int j = 0; i < l->nxt_layer->n_inputs; l++)
			acc += (d_in[j] * l->nxt_layer->nxt_layer->W[j][i]);
			
		d_out[i] = (acc * -1)* reluDiff(l->l[i]);

		
	}
}

//Atualiza a matriz de peso de uma dada camada
void weightUpdade(layer* l,T* exp_value,T taxa)
{
	
	//variavel para armazenar o erro
	T* d_in;
	T* d_out;
	
	//Percorre a rede até o primeiro nodo
	while(l != NULL)
	{

		//Caso seja o útimo layer
		if(l->nxt_layer == NULL)
			//Atualiza o último layer
			deltaLastLayer(l,exp_value,d_out);
		else	
		{
			//Acessa o próximo layer
			l = l->prv_layer;
		
			//Propaga o sinal do layer anterior para o próximo
			deltaHidenLayer(l,d_in,d_out);
		
		
		}
		
		//Percorre todos os nodos da camada e atualiza os pesos de todas as entradas
		for(int  i = 0; i < l->n_nodes; i++)
			for(int j = 0; j < l->n_inputs; j ++)
				l->W[j][i] = l->W[j][i] + (taxa * d_out[i] * l->prv_layer->y[j]);
		
		
		//O ponteiro de entrada agora é o de sáida
		d_in = d_out;
		d_out = NULL;
		
		//Vai para o nodo anterior
		l = l->prv_layer;
	}
	
}

//Calcula o erro médio da última camada
T averageError(layer* l, T* exp_value)
{
	T avg = 0;
	
	for(int i = 0; i < l->n_nodes; i++)
		avg += pow((exp_value[i] - l->y[i]),2);
		
	return (avg/2);
	
}
