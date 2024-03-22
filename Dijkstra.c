#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void imprimeGrafo(int *inicioVertice, int *vizinhosVertice, double *pesosArestas, int quantidadeVertices){
	
	int i, j;
	
	for(i=0; i<quantidadeVertices; i++){
		
		printf("\n%d\n\t", i);
		
		for(j=inicioVertice[i]; j < inicioVertice[i+1]; j++){
			
			printf("[%d]%lf ", vizinhosVertice[j], pesosArestas[j]);
			
		}
		
	}
	
}

void importaArquivo(int *inicioVertice, int *vizinhosVertice, uint8_t* visitados, double *pesosArestas, int quantidadeArestas) {

	int i;
	int inicio = 0;
	int vertice;
	int vizinho;
	int verticeAnterior=-1;
	int valor;
	


	FILE* file;
	file = fopen("problema.txt", "r");

	for (i = 0; i < quantidadeArestas; i++) {
		
		fscanf(file, "%d", &vertice);
		fscanf(file, "%d", &vizinho);
		fscanf(file, "%d", &valor);
		
		if(verticeAnterior!=vertice){
		
			inicioVertice[vertice] = inicio;
			visitados[vertice] = 0;
			verticeAnterior = vertice;
			
		}
		
		vizinhosVertice[inicio] = vizinho;
       	pesosArestas[inicio] = (double)valor;
       	
       	inicio++;

	}
	
	inicioVertice[vertice+1] = inicio;
	visitados[0] = 1;

	fclose(file);

}


/*void populaInformacoesGrafo(int *inicioVertice, int *vizinhosVertice, uint8_t* visitados, double *pesosArestas){

    inicioVertice[0] = 0;
    visitados[0] = 1;
    vizinhosVertice[0] = 1;
    vizinhosVertice[1] = 2;
    pesosArestas[0] = 4.0;
    pesosArestas[1] = 2.0;
    

    inicioVertice[1] = 2;
    visitados[1] = 0;
    vizinhosVertice[2] = 0;
    vizinhosVertice[3] = 2;
    vizinhosVertice[4] = 3;
    pesosArestas[2] = 4.0;
    pesosArestas[3] = 1.0;
    pesosArestas[4] = 5.0;

    inicioVertice[2] = 5;
    visitados[2] = 0;
    vizinhosVertice[5] = 0;
    vizinhosVertice[6] = 1;
    vizinhosVertice[7] = 3;
    vizinhosVertice[8] = 4;
    pesosArestas[5] = 2.0;
    pesosArestas[6] = 1.0;
    pesosArestas[7] = 8.0;
    pesosArestas[8] = 10.0;


    inicioVertice[3] = 9;
    visitados[3] = 0;
    vizinhosVertice[9] = 1;
    vizinhosVertice[10] = 2;
    vizinhosVertice[11] = 4;
    vizinhosVertice[12] = 5;
    pesosArestas[9] = 5.0;
    pesosArestas[10] = 8.0;
    pesosArestas[11] = 2.0;
    pesosArestas[12] = 6.0;

    inicioVertice[4] = 13;
    visitados[4] = 0;
    vizinhosVertice[13] = 2;
    vizinhosVertice[14] = 3;
    vizinhosVertice[15] = 5;
    pesosArestas[13] = 10.0;
    pesosArestas[14] = 2.0;
    pesosArestas[15] = 2.0;

    inicioVertice[5] = 16;
    visitados[5] = 0;
    vizinhosVertice[16] = 3;
    vizinhosVertice[17] = 4;
    pesosArestas[16] = 6.0;
    pesosArestas[17] = 2.0;

    inicioVertice[6] = 18;

}

*/

void imprimeResultado(int *rotulo, int quantidadeVertice){

	
	int *caminho = (int*)malloc(quantidadeVertice*sizeof(int));
	int i, j=quantidadeVertice-2;
	
	i = quantidadeVertice-1;
	
	caminho[quantidadeVertice-1] = quantidadeVertice-1;
	
	while(rotulo[i]> -1){
		
		caminho[j] = rotulo[i];
		i = caminho[j];
		j--;
		
	}
	
	
	for(i=j+1; i<quantidadeVertice; i++){
		
		printf("%d ", caminho[i]);
		
	}
	
	free(caminho);
	
}

void imprimeRelatorio(int insert, int update, int Delete, int siftInserte, int siftUpdate, int siftDelete, int quantidadeVertices, int quantidadeArestas){
	
	printf("\n\nQUANTIDADE VERTICES %d", quantidadeVertices);
	printf("\nQUANTIDADE  ARESTAS %d", quantidadeArestas);
	
	printf("\n\n|OPERACAO\t|QTD\t|QTD SIFT\t|");
	printf("\n_________________________________________");
	printf("\n|INSERT\t\t|%d\t|%d\t\t|", insert, siftInserte);
	printf("\n|UPDATE\t\t|%d\t|%d\t\t|", update, siftUpdate);
	printf("\n|DELETE\t\t|%d\t|%d\t\t|", Delete, siftDelete);
	printf("\n_________________________________________");
	printf("\n|TOTAL\t\t|%d\t|%d\t\t|\n", insert+update+Delete, siftInserte+siftUpdate+siftDelete);
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

int main(){

    int i, vertice, distanciaTotal, distanciaFinal, quantidadeVertices = 264346, quantidadeArestas = 733846;
    int* inicioVertice = (int *)malloc((quantidadeVertices+1)*sizeof(int));
    uint8_t* visitados = (uint8_t *)calloc(quantidadeVertices, sizeof(uint8_t));
    int* rotulo = (int*)malloc((quantidadeVertices)*sizeof(int));
    int* vizinhosVertice = (int *)malloc(quantidadeArestas*2*sizeof(int));
    double* pesosArestas = (double *)malloc(quantidadeArestas*2*sizeof(double));
    int quantidadeItensNaHeap = 1;
    int indiceRotulo = -1;

    double * arvoreHeap = (double *)malloc((quantidadeVertices-1)*sizeof(double));
    int  *localizacaoVerticeNaHeap = (int *)malloc((quantidadeVertices-1)*sizeof(int));
    int  *indiceVerticeNaHeap = (int *)malloc((quantidadeVertices-1)*sizeof(int));

	int temp, insert=0, update=0, Delete=0;
	int siftInserte=0, siftUpdate=0, siftDelete=0;

    //populaInformacoesGrafo(inicioVertice, vizinhosVertice, visitados, pesosArestas);

	importaArquivo(inicioVertice, vizinhosVertice, visitados, pesosArestas, quantidadeArestas);

	//imprimeGrafo(inicioVertice, vizinhosVertice, pesosArestas, quantidadeVertices);

	arvoreHeap[0] = 0.0;
    localizacaoVerticeNaHeap[0] = 0;
    indiceVerticeNaHeap[0] = 0;
    rotulo[0] = -1;
	
    while(quantidadeItensNaHeap>0){
    	
    	distanciaTotal = arvoreHeap[0];
		vertice = indiceVerticeNaHeap[0];
		indiceRotulo = vertice;
		visitados[vertice] = 2;
		
		if(vertice == quantidadeVertices-1) distanciaFinal = distanciaTotal;
		
		temp = deletaPrimeiroItemNaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, quantidadeItensNaHeap);
    	siftDelete =  siftDelete + temp;
		quantidadeItensNaHeap--;
    	Delete++;
    	
    	//printf("\nUsado vertice: %d\n", vertice); system("pause");
    	
    	// percorre vizinhos do vertice
    	for(i=inicioVertice[vertice]; i<inicioVertice[vertice+1]; i++){
    		
    		if(visitados[vizinhosVertice[i]]==1){
    			
    			//printf("\nvertice %d visitado\n", vizinhosVertice[i]); system("pause");
    		
				if(arvoreHeap[localizacaoVerticeNaHeap[vizinhosVertice[i]]]> distanciaTotal + pesosArestas[i]){
					
					temp = atualizaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, vizinhosVertice[i], distanciaTotal + pesosArestas[i]);
					siftUpdate = siftUpdate + temp;
					rotulo[vizinhosVertice[i]] = vertice;
					update++;
					
				}
				
			}else if(visitados[vizinhosVertice[i]]==0){
				
				//printf("\nvertice %d NAO visitado\n", vizinhosVertice[i]);system("pause");
				
				temp = insereItemNaHeap(arvoreHeap, localizacaoVerticeNaHeap, indiceVerticeNaHeap, vizinhosVertice[i], quantidadeItensNaHeap, distanciaTotal + pesosArestas[i]);
				siftInserte = siftInserte + temp;
				
				rotulo[vizinhosVertice[i]] = vertice;
				quantidadeItensNaHeap++;
				visitados[vizinhosVertice[i]] = 1.0;
				insert++;
				
			}
    		
		} 	
    	
	}
	
	printf("\nDistancia Percorrida: %d\n", distanciaFinal);
	
	//imprimeResultado(rotulo, quantidadeVertices);
	
	imprimeRelatorio(insert, update, Delete, siftInserte, siftUpdate, siftDelete, quantidadeVertices, quantidadeArestas);

	free(inicioVertice);
	free(visitados);
    free(rotulo);
    free(vizinhosVertice);
    free(pesosArestas);
    free(arvoreHeap);
    free(localizacaoVerticeNaHeap);
    free(indiceVerticeNaHeap);
    
    return 0;
}
