#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef struct {

	int distancia;
	int destino;

}Aresta;

typedef struct noAresta {

	Aresta aresta;
	struct noAresta* proximo;

}NoAresta;

Aresta preencherAresta(int destino, int distancia){
	
	Aresta aresta;
	
	aresta.destino = destino;
	aresta.distancia = distancia;
	
	return aresta;
	
}

void criaAresta(NoAresta *arestas[], int origem, int destino, int distancia){
	
	NoAresta* novo = (NoAresta*) malloc(sizeof(NoAresta));
	
	if(novo){
		
		novo->aresta = preencherAresta(destino, distancia);
		novo->proximo = arestas[origem];
		arestas[origem] = novo;
		
		
	}else{
		
		printf("\nNao foi possivel alocar memoria para criar Aresta e Aresta Par\n");
		system("pause");
		
	}
	
	
}


void importaArquivo(int **inicioVertice, int **vizinhosVertice, uint8_t **visitados, double **pesosArestas, int *quantidadeVertices, int *quantidadeArestas) {

	int vertice, posicao;
	NoAresta *arestaAnterior, *arestaAtual;
	
	char *valor;
	
	char *valor1;
	
	char *valor2;	
	
	char *espaco = (char*)malloc(100 * sizeof(char));

	fgets(espaco, 100, stdin);
	
	while (espaco[0] != 'p') {
		
		fgets(espaco, 100, stdin);
	
	}

	valor = strtok(espaco, " ");
	valor = strtok(NULL, " ");
	valor = strtok(NULL, " ");
	
	*quantidadeVertices = atoi(valor);
	
	//NoAresta* arestas[(*quantidadeVertices)];
	
	NoAresta** arestas = (NoAresta**)malloc((*quantidadeVertices) * sizeof(NoAresta*));;
	
	*inicioVertice = malloc(((*quantidadeVertices)+1) * sizeof(int));
	
	*visitados = malloc(((*quantidadeVertices)+1) * sizeof(uint8_t));
	
	for(vertice=0; vertice<(*quantidadeVertices);  vertice++){
		
		arestas[vertice] = NULL;
		(*visitados)[vertice] = 0;
	}

	valor = strtok(NULL, " ");
	
	*quantidadeArestas = atoi(valor);
	
	*vizinhosVertice = malloc(((*quantidadeArestas)+1) * sizeof(int));
	*pesosArestas = malloc(((*quantidadeArestas)+1) * sizeof(double));
	
	while (espaco[0] != 'a') {
		
		fgets(espaco, 100, stdin);
	
	}
	
	while (!feof(stdin) && espaco[0] == 'a') {
		
		valor = strtok(espaco, " ");
		valor = strtok(NULL, " ");
		valor1 = strtok(NULL, " ");
		valor2 = strtok(NULL, " ");
			
		criaAresta(arestas, atoi(valor)-1, atoi(valor1)-1, atoi(valor2));
	
		fgets(espaco, 100, stdin);
	
	}
	
	posicao = 0;
	
	for(vertice=0; vertice<(*quantidadeVertices); vertice++){
		
		(*inicioVertice)[vertice] = posicao;
		
		arestaAtual = arestas[vertice];
		
		while(arestaAtual){
			
			(*vizinhosVertice)[posicao] = arestaAtual->aresta.destino;
			(*pesosArestas)[posicao] = (double)arestaAtual->aresta.distancia;
			posicao++;
			
			arestaAnterior = arestaAtual;
			arestaAtual = arestaAtual->proximo;
			free(arestaAnterior);
			
		}
		
	}

	(*inicioVertice)[vertice] = posicao;
		
}


void insereItemNumaPosicaoHeap(double *arvoreHeap, int *localizacaoVerticeNaHeap, int *indiceVerticeNaHeap, int indiceDoItem, int posicao, double valor){
	
	arvoreHeap[posicao]= valor;
	localizacaoVerticeNaHeap[indiceDoItem] = posicao;
	indiceVerticeNaHeap[posicao] = indiceDoItem;
	
}

void inverteItemDePosicaoNaHeap(double *arvoreHeap, int *localizacaoVerticeNaHeap, int *indiceVerticeNaHeap, int indiceDoItemA, int posicaoA, double valorA, int indiceDoItemB, int posicaoB, double valorB){

	insereItemNumaPosicaoHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, indiceDoItemA, posicaoB, valorA);
	insereItemNumaPosicaoHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, indiceDoItemB, posicaoA, valorB);
	
}

int siftUpItem(double *arvoreHeap, int *localizacaoVerticeNaHeap, int *indiceVerticeNaHeap, int posicaoItemNaHeap){
	
	int sift = 0;
	
	int pai = (posicaoItemNaHeap -1)>>1;
	
	while(posicaoItemNaHeap > 0 && arvoreHeap[pai]>arvoreHeap[posicaoItemNaHeap]){
		
		inverteItemDePosicaoNaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, indiceVerticeNaHeap[posicaoItemNaHeap], posicaoItemNaHeap, arvoreHeap[posicaoItemNaHeap], indiceVerticeNaHeap[pai], pai, arvoreHeap[pai]);
		
		posicaoItemNaHeap = pai;
		
		pai = (posicaoItemNaHeap -1)>>1;
		
		sift++;
		
	}
	
	return sift;
	
}

int siftDownItem(double *arvoreHeap, int *localizacaoVerticeNaHeap, int *indiceVerticeNaHeap, int posicaoItemNaHeap, int quantidadeItensNaHeap){

	int sift=0;
	
	int filho;
	
	if((2*posicaoItemNaHeap)+2 < quantidadeItensNaHeap && arvoreHeap[(2*posicaoItemNaHeap)+2] < arvoreHeap[(2*posicaoItemNaHeap)+1]){
		
		filho = (2*posicaoItemNaHeap)+2;
		
	}else{
		
		filho = (2*posicaoItemNaHeap)+1;
		
	}
	
	while(filho < quantidadeItensNaHeap && arvoreHeap[filho]<arvoreHeap[posicaoItemNaHeap]){
		
		inverteItemDePosicaoNaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, indiceVerticeNaHeap[posicaoItemNaHeap], posicaoItemNaHeap, arvoreHeap[posicaoItemNaHeap], indiceVerticeNaHeap[filho], filho, arvoreHeap[filho]);
		
		posicaoItemNaHeap = filho;
		
		if((2*posicaoItemNaHeap)+2 < quantidadeItensNaHeap && arvoreHeap[(2*posicaoItemNaHeap)+2] < arvoreHeap[(2*posicaoItemNaHeap)+1]){
		
			filho = (2*posicaoItemNaHeap)+2;		
		
		}else{
		
			filho = (2*posicaoItemNaHeap)+1;
		
		}
		
		sift++;
		
	}
	
	return sift;
	
}


int insereItemNaHeap(double *arvoreHeap, int *localizacaoVerticeNaHeap, int *indiceVerticeNaHeap, int indiceDoItem, int quantidadeItensNaHeap, double valor){
	
	insereItemNumaPosicaoHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, indiceDoItem, quantidadeItensNaHeap, valor);
	
	int sift = siftUpItem(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, quantidadeItensNaHeap);
	
	return sift;
	
}

int atualizaHeap(double *arvoreHeap, int *localizacaoVerticeNaHeap, int *indiceVerticeNaHeap, int indiceDoItem, double valor){
	
	arvoreHeap[localizacaoVerticeNaHeap[indiceDoItem]] = valor;
	
	int sift = siftUpItem(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, localizacaoVerticeNaHeap[indiceDoItem]);
	
	return sift;
	
}


int deletaPrimeiroItemNaHeap(double *arvoreHeap, int *localizacaoVerticeNaHeap, int *indiceVerticeNaHeap, int quantidadeItensNaHeap){
	
	int sift =0;
	
	if(quantidadeItensNaHeap>0){
	
		insereItemNumaPosicaoHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, indiceVerticeNaHeap[quantidadeItensNaHeap-1], 0, arvoreHeap[quantidadeItensNaHeap-1]);
	
		sift = siftDownItem(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, 0, quantidadeItensNaHeap-1);
	
	}
	
	return sift;
	
}

void saveFile(int problema, int verticeInicio, int verticeFim, int distanciaPercorrida, int tempo, int insert, int update, int Delete, int siftInserte, int siftUpdate, int siftDelete,  double rSiftInserte, double rSiftUpdate, double rSiftDelete) {

	FILE* pont_arqu;

	pont_arqu = fopen("resultado.csv", "a");

	fprintf(pont_arqu, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%.2f;%.2f;%.2f;\n", problema, verticeInicio, verticeFim, distanciaPercorrida, tempo, insert, update, Delete, siftInserte, siftUpdate, siftDelete, rSiftInserte, rSiftUpdate, rSiftDelete);


	fclose(pont_arqu);

}

void resetaInformacoesProblemaAnterior(uint8_t* visitados, int *rotulo, int quantidadeVertices){

	int i;
	
	for(i=0; i<quantidadeVertices; i++){
		
		rotulo[i]= -1;
		visitados[i] = 0;
		
	}	
	
}

int main(int argc, char** argv){

	char *arquivo = (char*)malloc(100 * sizeof(char));

	int verticeInicio = atoi(argv[1]) - 1;

	int verticeFim = atoi(argv[2]) - 1;	

	int j;
	
	int* inicioVertice;
	uint8_t* visitados;
    int* rotulo;
    int* vizinhosVertice;
    double* pesosArestas;

	double * arvoreHeap;
    int  *localizacaoVerticeNaHeap;
    int  *indiceVerticeNaHeap;

    int i, vertice, distanciaFinal, quantidadeVertices, quantidadeArestas, totalTime;
    double distanciaTotal;
    
	int temp, insert=0, update=0, Delete=0;
	int siftInserte=0, siftUpdate=0, siftDelete=0;

	double rSiftInserte=0.0, rSiftUpdate=0.0, rSiftDelete=0.0, logN;
			
	importaArquivo(&inicioVertice, &vizinhosVertice, &visitados, &pesosArestas, &quantidadeVertices, &quantidadeArestas);
	
	arvoreHeap = (double *)malloc((quantidadeVertices-1)*sizeof(double));
    localizacaoVerticeNaHeap = (int *)malloc((quantidadeVertices-1)*sizeof(int));
    indiceVerticeNaHeap = (int *)malloc((quantidadeVertices-1)*sizeof(int));
    rotulo = (int*)malloc((quantidadeVertices)*sizeof(int));

	int inicio = time(NULL);

	distanciaFinal= -1;
	
	int quantidadeItensNaHeap = 1;
    int indiceRotulo = -1;

	arvoreHeap[0] = 0.0;
    localizacaoVerticeNaHeap[verticeInicio] = 0;
    indiceVerticeNaHeap[0] = verticeInicio;
    rotulo[verticeInicio] = -1;
	
    while(quantidadeItensNaHeap>0){
    	
    	distanciaTotal = arvoreHeap[0];
		vertice = indiceVerticeNaHeap[0];
		indiceRotulo = vertice;
		visitados[vertice] = 2;
		
		if(vertice == verticeFim){
		
			distanciaFinal = (int) distanciaTotal;
				
			goto QUIT;
			
		}
		
		temp = deletaPrimeiroItemNaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, quantidadeItensNaHeap);
    	siftDelete =  siftDelete + temp;
    	logN = (log(((double)quantidadeItensNaHeap))/log(2.0));
		if (logN>0) rSiftDelete = rSiftDelete + temp/logN;
		
		quantidadeItensNaHeap--;
	    Delete++;
    	
    	for(i=inicioVertice[vertice]; i<inicioVertice[vertice+1]; i++){
    		
    		if(visitados[vizinhosVertice[i]]==1){
    		
				if(arvoreHeap[localizacaoVerticeNaHeap[vizinhosVertice[i]]]> distanciaTotal + pesosArestas[i]){
					
					temp = atualizaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, vizinhosVertice[i], distanciaTotal + pesosArestas[i]);
					logN = (log(((double)quantidadeItensNaHeap))/log(2.0));
					rSiftUpdate = rSiftUpdate + temp/logN;
					siftUpdate = siftUpdate + temp;
					rotulo[vizinhosVertice[i]] = vertice;
					update++;
					
				}
				
			}else if(visitados[vizinhosVertice[i]]==0){
							
				temp = insereItemNaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, vizinhosVertice[i], quantidadeItensNaHeap, distanciaTotal + pesosArestas[i]);
				logN = (log(((double)quantidadeItensNaHeap))/log(2.0));
				if (logN>0) rSiftInserte = rSiftInserte + temp/logN;
				siftInserte = siftInserte + temp;
				
				rotulo[vizinhosVertice[i]] = vertice;
				quantidadeItensNaHeap++;
				visitados[vizinhosVertice[i]] = 1.0;
				insert++;
				
			}
    		
		} 	
    	
	}
	
	QUIT:
	
	totalTime = time(NULL) - inicio;
	
	rSiftInserte = rSiftInserte / ((double)insert);
	rSiftDelete = rSiftDelete / ((double)Delete);
	rSiftUpdate = rSiftUpdate / ((double)update);

	//saveFile(opcao, verticeInicio, verticeFim, distanciaFinal, totalTime, insert, update, Delete, siftInserte, siftUpdate, siftDelete,  rSiftInserte, rSiftUpdate, rSiftDelete);


	free(inicioVertice);
	free(visitados);
    free(rotulo);
    free(vizinhosVertice);
    free(pesosArestas);
    free(arvoreHeap);
    free(localizacaoVerticeNaHeap);
    free(indiceVerticeNaHeap);


	fprintf(stdout, "%d", distanciaFinal);
    
    return 0;

}
