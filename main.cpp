//Nadiana Kelly Nogueira Mendes - 475557
#include <iostream>
#include <ctime>
#include <cstdlib>

using std::clock; using std::clock_t;
using namespace std;

//FUNÇÃO PARA O USO DO HEAPSORT
//essa função estrutura os elementos em forma de "arvore"
template<typename T>
void criacaoHeap (T *vetor, int inicio, int fim){
  int aux = vetor[inicio];//pai
  int j  = inicio*2+1;//filho
  while (j<= fim){
    if(j<fim){
      if(vetor[j]<vetor[j+1]){//se pai tem dois filhos procura o maior
        j = j+1;
      }
    }
    if(aux < vetor[j]){//se filho>pai, filho se torna pai
      vetor[inicio] = vetor[j];
      inicio=j;
      j = 2*inicio+1;
    }else{
      j=fim+1;
    }
  }
  vetor[inicio] = aux; // o antigo pai vai se torna o ultimo filho analisado
}

//FUNÇÃO HEAPSORT
template<typename T>
void heapSort(T *vetor, int n){
  int i, aux;
  for(i= n/2; i>=0; i--) { //cria heap apartir dos dados
    criacaoHeap(vetor, i, n-1);
  }
  for (i = n-1; i>=1; i--){
    aux = vetor[0]; //pega o maior elemento e coloca na sua posição
    vetor[0] = vetor[i];
    vetor[i] = aux;
    criacaoHeap(vetor,0,i-1); //reconstroi o heap
  }
}

//FUNÇÃO PIVÔ FIXO (PARA USO DA FUNÇÃO QUICKSORT PF)
int pivo (int inicio){
  return inicio;
}

//FUNÇÃO PIVÔ ALEATÓRIO (PARA USO DA FUNÇÃO QUICKSORT ALET)
int pivotAleatorio (int inicio, int fim){
  return inicio + (rand() % (fim-inicio+1));
}

//FUNÇÃO DE PARTICIONAMENTO (PARA USO DO QUICKSORT COM PIVO FIXO)
template<typename T>
int particione(T *vetor, int inicio, int fim) {
	int esquerda, direita, pivot, aux;
	esquerda = inicio;
	direita  = fim;
	pivot = vetor[pivo(inicio)]; //pivo fixo
	while(esquerda<direita){
		while(vetor[esquerda]<= pivot) { //avaça para a esquerda
		  esquerda = esquerda+1;
		}
		while(vetor[direita]> pivot) { //recua para a direita
		  direita = direita-1;
		}
		if(esquerda<direita) { //se isso ocorrer troca esquerda e direita
		  aux = vetor[esquerda];
		  vetor[esquerda] = vetor[direita];
		  vetor[direita] = aux;
		}
	}
	vetor[inicio] = vetor[direita];
	vetor[direita] = pivot;
	return direita;
}

//FUNÇÃO QUICKSORT (COM USO DO PIVÔ FIXO)
template<typename T>
void quickSortPF(T *vetor, int inicio, int fim){
  int pivot;
  if(fim>inicio){
    pivot =particione(vetor, inicio, fim);
    //reparte o vetor em duas partições
    quickSortPF(vetor, inicio, pivot-1);
    quickSortPF(vetor, pivot+1, fim);
  }
}


//FUNÇÃO PARA O QUICKSORT (COM USO DO PIVÔ ALEATÓRIO)
template<typename T>
int particione_aleatorio(T *vetor, int inicio, int fim) {
	int esquerda, direita, pivot, aux;
	esquerda = inicio;
	direita  = fim;
	pivot = pivotAleatorio(inicio, fim); // pivo é um indice aleatorio
	aux = vetor[pivot]; //trocando o valor de inicio com o pivo
	vetor[pivot]  = vetor[inicio];
	vetor[inicio] = aux;
	pivot = vetor[inicio];

	while(esquerda<direita){
		while(vetor[esquerda]<= pivot) {
		  esquerda = esquerda+1; //avaça a esquerda
		}
		while(vetor[direita]> pivot) {
		  direita = direita-1; ///recua a direita
		}
		if(esquerda<direita) {
		  aux = vetor[esquerda];//troca esquerda e direita
		  vetor[esquerda] = vetor[direita];
		  vetor[direita] = aux;
		}
	}
	vetor[inicio] = vetor[direita];
	vetor[direita] = pivot;
	return direita;
}

//FUNÇÃO QUICKSORT (COM USO DO PIVÔ ALEATÓRIO)
template<typename T>
void quickSortALET(T *vetor, int inicio, int fim){
  int pivot;
  if(fim>inicio){
    pivot =particione_aleatorio(vetor, inicio, fim);
    //reparte o vetor em duas partições
    quickSortPF(vetor, inicio, pivot-1);
    quickSortPF(vetor, pivot+1, fim);
  }
}

//FUNÇÃO PARA CALCULAR LOG DE N (PARA USO DA FUNÇÃO INTROSORT)
int log(int n){
  int contador=0;
  while(n!=1){
    n = n >> 1;
    contador = contador+1;
  }
  return contador;
}

//FUNÇÃO INSERTIONSORT
template<typename T>
void insertionSort(T *vetor, int n) {
	int i, j, tmp;
  for(i = 1; i < n; i++){
  tmp = vetor[i];
  for(j = i-1; j >= 0 && tmp < vetor[j]; j--){
   vetor[j+1] = vetor[j];
  }
  vetor[j+1] = tmp;
 }
}

//FUNÇÃO INTROSORT (SEM O USO DO INSERTION SORT)
template<typename T>
void introSortSemInsert(T *vetor, int inicio, int fim, int altura) {
	if(fim-inicio+1 <= 1) //caso para sair
		return;
	int pivo;
	if(altura == 0){
		heapSort(vetor+inicio, fim-inicio+1);
	}else{
    //mesma coisa do quicksort
		pivo = particione(vetor, inicio, fim);
		introSortSemInsert(vetor, inicio, pivo-1, altura-1);
		introSortSemInsert(vetor, pivo+1, fim, altura -1);
	}
}

//FUNÇÃO INTROSORT (COM O USO DO INSERTION SORT)
template<typename T>
void introSortComInsert(T *vetor, int inicio, int fim, int altura) {
	if(fim-inicio+1 <= 1) //caso para sair
		return;
	int pivo;
	if(fim-inicio+1 < 12) { 
		insertionSort(vetor+inicio, fim-inicio+1);
	}else if(altura == 0){
		heapSort(vetor+inicio, fim-inicio+1);
	}else{
    //mesma coisa do quicksort
		pivo = particione(vetor, inicio, fim);
		introSortComInsert(vetor, inicio, pivo-1, altura-1);
		introSortComInsert(vetor, pivo+1, fim, altura -1);
	}
}

//FUNÇÃO PARA INSTÂNCIA ALEATÓRIA
template<typename T>
void instanciaAlet (T *vetor, int valores, int n){
  int i,x;
  for(i = 0; i<n; i++){
    x = rand() % (valores+1);
    vetor[i] = x;
  }
}

template<typename T>
//FUNÇÃO PARA INSTÂNCIA DE ORDEM CRESCENTE
void instanciaOrdCresc(T *vetor, int n){
  int i;
  for(i = 0; i<n; i++){
    vetor[i] = i;
  }
}

//FUNÇÃO PARA INSTÂNCIA DE ORDEM DECRESCENTE
template<typename T>
void instanciaOrdDecres(T *vetor, int n){
  int i,k = 0;
  for(i = n; i>=1; i--){
    vetor[k] = i;
    k = k+1;
  }
}

//FUNÇÃO PARA INSTÂNCIA DE PIOR CASO
//uma das escolhas possíveis é já pegar um vetor ordenado e o pivô se encontrar em uma das pontas, ou seja, no inicio ou fim do vetor. A minha função de pivô fixo pega o pivô como sendo o valor de inicio do vetor.
template <typename T>
bool gerar_pior_caso(T *vetor, int n){
  int k = rand() % (n);
  int i,aux =  0;
  for(i = 0; i<n; i++){
    vetor[i] = (k+aux);
    aux+=1;
  }
  return true;
}

//FUNÇÃO QUE VERIFICA A ORDENAÇÃO DO VETOR
bool ordenado(int *vetor, int n) {
  int k;
	for(k = 0; k < n-1; k++) {
		if(vetor[k] > vetor[k+1])
			return false;
	}
	return true;
}

//FUNÇÃO PARA CALCULAR O TEMPO DO HEAPSORT
template <typename T>
double tempoHS (T *vetor, int n){
  clock_t tempo_inicio_HS, tempo_final_HS;
  double tempo_total_HS;

  tempo_inicio_HS = clock();
  heapSort(vetor,n);
  tempo_final_HS = clock();

  tempo_total_HS = (tempo_final_HS - tempo_inicio_HS) /  (double) CLOCKS_PER_SEC;
  return  tempo_total_HS ;
}

//FUNÇÃO PARA CALCULAR O TEMPO DO QUICKSORT (com pivo fixo)
template <typename T>
double tempoQuicksortQPF (T *vetor, int n){
  clock_t tempo_inicio_QPF, tempo_final_QPF; 
  double tempo_total_QPF; 

  tempo_inicio_QPF = clock();
  quickSortPF(vetor, 0, n-1);
  tempo_final_QPF = clock();

  tempo_total_QPF =(tempo_final_QPF - tempo_inicio_QPF) /  (double)CLOCKS_PER_SEC;
  return  tempo_total_QPF ;
}


//FUNÇÃO PARA CALCULAR O TEMPO DO QUICKSORT (COM PIVO ALEATORIO)
template <typename T>
double tempoQuicksortALET(T *vetor, int n){
  clock_t tempo_inicio_ALET, tempo_final_ALET; 
  double tempo_total_ALET; 

  tempo_inicio_ALET = clock();
  quickSortALET(vetor, 0, n-1);
  tempo_final_ALET = clock();

  tempo_total_ALET =(tempo_final_ALET - tempo_inicio_ALET) /  (double)CLOCKS_PER_SEC;
  return  tempo_total_ALET;
}

//FUNÇÃO PARA CALCULAR O TEMPO DO INTROSORT (SEM INSERTION)
template <typename T>
double tempoISI (T *vetor, int n){
  clock_t tempo_inicio_ISI, tempo_final_ISI; 
  double tempo_total_ISI; 

  int altura = 2*log(n);

  tempo_inicio_ISI = clock();
  introSortSemInsert(vetor,0, n-1,altura);
  tempo_final_ISI = clock();

  tempo_total_ISI = (tempo_final_ISI - tempo_inicio_ISI) / (double)CLOCKS_PER_SEC;
  
  return  tempo_total_ISI ;
}

//FUNÇÃO PARA CALCULAR O TEMPO DO INTROSORT (COM INSERTION)
template <typename T>
double tempoICI (T *vetor, int n){
  clock_t tempo_inicio_ICI, tempo_final_ICI; 
  double tempo_total_ICI; 

  int altura = 2*log(n);

  tempo_inicio_ICI = clock();
  introSortComInsert(vetor, 0, n-1, altura);
  tempo_final_ICI = clock();

  tempo_total_ICI = (tempo_final_ICI - tempo_inicio_ICI) / (double)CLOCKS_PER_SEC;
  
  return  tempo_total_ICI ;
}

int main(int argc, char *argv[]) {
	srand(time(NULL)); //para as instancias aleatorias
	int valores = 1000; //os numeros sorteados vai ser até esse (para instancia aletoria)
	int n; //tamanho do vetor 
	int i,j; //indices de for
	char resp; // recebe o tipo de instância que será feita (A -  (aleatória), C - (ordem crescente), D - (ordem decrescente), e P - (pior caso))
	int numInst; // recebe o numero de instancias

  cout <<"\nTipo de instancia: ";
  cin >> resp; 
  cout <<"\nTamanho do vetor: " ;
  cin >> n; 
  cout <<"\nNumero de instancias: ";
  cin >> numInst; 
  
  int *vetor = new  int[n];// vetor que receberá a instância escolhida
	int *vetorOrd = new int[n]; //vetor que guarda as instancia não ordenadas
	double tempo_total_HS = 0; //tempo final do heapSort
	double tempo_total_QPF = 0; //tempo final do Quicksort pivo fixo
	double tempo_total_ISI = 0; //tempo final do  intr.Sor sem Insert.
	double tempo_total_ICI = 0; //variaveis intr.Sor com Insert.
 	double tempo_total_QALET = 0; //tempo final do Quicksort pivo alet.


	switch (resp){
		case('A'): {
			for(i=0;i<numInst;i++){
					instanciaAlet(vetor, valores, n); 
				  for(j=0;j<n;j++){
					  vetorOrd[j] = vetor[j];
				  }
				  tempo_total_HS += tempoHS(vetor, n);
          if(ordenado(vetor, n) ==0){
            cout<<"\nErro: vetor não ordenado!\n";
          }
				  for(j=0;j<n;j++){
					  vetor[j] = vetorOrd[j];
				  }
				  tempo_total_QPF += tempoQuicksortQPF(vetor, n);
          if(ordenado(vetor, n) ==0){
            cout<<"\nErro: vetor não ordenado!\n";
          }
				  for(j=0;j<n;j++){
					  vetor[j] = vetorOrd[j];
				  }
				  tempo_total_ISI += tempoISI(vetor, n);
          if(ordenado(vetor, n) ==0){
            cout<<"\nErro: vetor não ordenado!\n";
          }
				  for(j=0;j<n;j++){
					  vetor[j] = vetorOrd[j];
				  }
				  tempo_total_ICI += tempoICI(vetor, n);

			    if(ordenado(vetor, n) ==0){
				    cout<<"\nErro: vetor não ordenado!\n";
          }
				  for(j=0;j<n;j++){
					  vetor[j] = vetorOrd[j];
				  }
				  tempo_total_QALET += tempoQuicksortALET(vetor, n);
          if(ordenado(vetor, n) ==0){
            cout<<"\nErro: vetor não ordenado!\n";
          }
			}
		break;
		}
		case('C'):
		  for(i=0;i<numInst;i++){
			  instanciaOrdCresc(vetor,n); //criando instancia
			  for(j=0;j<n;j++){
			    vetorOrd[j] = vetor[j];
			  }
				tempo_total_HS += tempoHS(vetor, n); 
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
			    vetor[j] = vetorOrd[j];
			  }
				tempo_total_QPF += tempoQuicksortQPF(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
				  vetor[j] = vetorOrd[j];
			  }
				tempo_total_ISI += tempoISI(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
				  vetor[j] = vetorOrd[j];
			  }
				tempo_total_ICI += tempoICI(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
        for(j=0;j<n;j++){
			    vetor[j] = vetorOrd[j];
			  }
        tempo_total_QALET += tempoQuicksortALET(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
      
		  }
		break;
	  case('D'):
		  for(i=0;i<numInst;i++){
		    instanciaOrdDecres(vetor,n); //criando instancia
			  for(j=0;j<n;j++){
			    vetorOrd[j] = vetor[j];
			  }
			  tempo_total_HS += tempoHS(vetor, n); 
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
			    vetor[j] = vetorOrd[j];
			  }
			  tempo_total_QPF += tempoQuicksortQPF(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
				  vetor[j] = vetorOrd[j];
			  }
			  tempo_total_ISI += tempoISI(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
				  vetor[j] = vetorOrd[j];
			  }
			  tempo_total_ICI += tempoICI(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
     	  for(j=0;j<n;j++){
			    vetor[j] = vetorOrd[j];
		    }
        tempo_total_QALET += tempoQuicksortALET(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
		  }      
	  break;
	  case('P'):
		  for(i = 0;i<numInst;i++){
		    gerar_pior_caso(vetor, n); //criando instância
			  for(j=0;j<n;j++){
			    vetorOrd[j] = vetor[j];
			  }
				tempo_total_HS += tempoHS(vetor, n); 
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
			    vetor[j] = vetorOrd[j];
			  }
				tempo_total_QPF += tempoQuicksortQPF(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
				  vetor[j] = vetorOrd[j];
			  }
				tempo_total_ISI += tempoISI(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
			  for(j=0;j<n;j++){
				  vetor[j] = vetorOrd[j];
			  }
				tempo_total_ICI += tempoICI(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
        for(j=0;j<n;j++){
			    vetor[j] = vetorOrd[j];
			  }
        tempo_total_QALET += tempoQuicksortALET(vetor, n);
        if(ordenado(vetor, n) ==0){
          cout<<"\nErro: vetor não ordenado!\n";
        }
		  }
	  break;
	}

	cout << "\nHeapSort: " << tempo_total_HS;
	cout << "\nQuickSort (com pivo fixo): "<< tempo_total_QPF;
  cout << "\nQuickSort (com pivo aleatorio): "<< tempo_total_QALET;
	cout << "\nIntroSort (sem InsertionSort): "<< tempo_total_ISI;
	cout << "\nIntroSort (com InsertionSort): "<< tempo_total_ICI;
}