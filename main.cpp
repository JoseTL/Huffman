/*
 Trabalho Prático de Algoritmo e Estrutura de Dados III - AEDSIII do ano letivo 2019/2
sobre Algoritmo Huffman
 * Aplicação em C
 
 Author: José Maria Pinto
 Matrícula: 20151016029
 
 */
    #include <iostream>
    #include <cstdlib>

    using namespace std;
    //calculando a altura da árvore Huffman
    #define ARVORE_MAXIMO 100 //definindo o tamanho da árvore
    //nó da árvore Huffman
    struct NoMinimadaPilha {
      char entrada; //Um das caracteres de entrada
      unsigned frequencia; // Frequência de caractere
      struct NoMinimadaPilha *esq, *dir; //Filho esquerdo e direito deste nó
    };
    
    // Uma pilha mínima: coleção de
    // nós da Pilha Minima (ou árvore de Huffman)
    struct PilhaMinima {
      unsigned size; // Tamanho atual da pilha mínima
      unsigned capacitcidade; // capacidade da pilha mínima
      struct NoMinimadaPilha **array; // Encaminhamento de ponteiros de nó da pilhaminima
    };
    
    // Uma função utilitária aloca um novo
    // nó de pilha mínimo com o caractere especificado
    // e frequência de caractere
    struct NoMinimadaPilha *newNo(char entrada, unsigned frequencia) {
      struct NoMinimadaPilha *temp = (struct NoMinimadaPilha *)malloc(sizeof(struct NoMinimadaPilha));
      temp->esq = temp->dir = NULL;
      temp->entrada = entrada;
      temp->frequencia = frequencia;
      return temp;
    }
    
    // Uma função utilitária para criar
// uma pilha mínima da capacidade fornecida
    struct PilhaMinima *criarPilhaMinima(unsigned capacidade) { 
      struct PilhaMinima *Pilhaminima = (struct PilhaMinima *)malloc(sizeof(struct PilhaMinima));
      Pilhaminima->size = 0; // tamanho atual é 0
      Pilhaminima->capacitcidade = capacidade;
      Pilhaminima->array = (struct NoMinimadaPilha **)malloc(Pilhaminima->capacitcidade * sizeof(struct NoMinimadaPilha *));
      return Pilhaminima;
    }
    
    // Uma função utilitária para troca dois nós de pilha mínima
    void swapNoMinimadaPilha(struct NoMinimadaPilha **a, struct NoMinimadaPilha **b) {
      struct NoMinimadaPilha *t = *a;
      *a = *b;
      *b = t;
    }
    
    // A função pilhaminima padrão.
    void pilhaminima(struct PilhaMinima *Pilhaminima, int idx) {
      int menor = idx; 
      int esq = 2 * idx + 1;
      int dir = 2 * idx + 2;
      if (esq < Pilhaminima->size && Pilhaminima->array[esq]->frequencia < Pilhaminima->array[menor]->frequencia)
        menor = esq;
      if (dir < Pilhaminima->size && Pilhaminima->array[dir]->frequencia < Pilhaminima->array[menor]->frequencia)
        menor = dir;
      if (menor != idx) {
        swapNoMinimadaPilha(&Pilhaminima->array[menor],
                &Pilhaminima->array[idx]);
        pilhaminima(Pilhaminima, menor);
      }
    }
    
    // Uma função utilitária para verificar
    // se o tamanho da pilha for 1 ou não

    int tamanho(struct PilhaMinima *Pilhaminima){
      return (Pilhaminima->size == 1);
    }
    
    // Uma função padrão para extrair
    // nó de valor mínimo da pilha
    struct NoMinimadaPilha *extraiMin(struct PilhaMinima *Pilhaminima) {
      struct NoMinimadaPilha *temp = Pilhaminima->array[0];
      Pilhaminima->array[0] = Pilhaminima->array[Pilhaminima->size - 1];
      --Pilhaminima->size;
      pilhaminima(Pilhaminima, 0);
      return temp;
    }
    
    // Uma função utilitária para inserir
    // um novo nó para pilha minima
    void inserirPilhaMinima(struct PilhaMinima *Pilhaminima, struct NoMinimadaPilha *noMinimadaPilha) {
      ++Pilhaminima->size;
      int i = Pilhaminima->size - 1;
      while (i && noMinimadaPilha->frequencia < Pilhaminima->array[(i - 1) / 2]->frequencia){
        Pilhaminima->array[i] = Pilhaminima->array[(i - 1) / 2];
        i = (i - 1) / 2;
      }
      
      Pilhaminima->array[i] = noMinimadaPilha;
    }
    
    // Uma função padrão para criar pilha minima
    void criarPilhaMinima(struct PilhaMinima *Pilhaminima) {
      int n = Pilhaminima->size - 1;
      int i;
      for (i = (n - 1) / 2; i >= 0; --i)
        pilhaminima(Pilhaminima, i);
    }
    
    // Uma função utilitária para imprimir uma matriz de tamanho n
    void printArr(int arr[], int n) {
      int i;
      for (i = 0; i < n; ++i)
        cout <<arr[i];
      cout << "\n";
    }
    // Função utilitária para verificar se este nó é folha
    int efolha(struct NoMinimadaPilha *raiz) {
      return !(raiz->esq) && !(raiz->dir);
    }
    
    // Cria uma pilha mínima de capacidade
    // igual ao tamanho e insere todos os caracteres de
    // entrada [] na pilha mínima. Inicialmente tamanho de
    // pilha mínima é igual à capacidade
    struct PilhaMinima *criareconstruirPilhaMinima(char entrada[], int frequencia[], int size) {
      struct PilhaMinima *Pilhaminima = criarPilhaMinima(size);
      for (int i = 0; i < size; ++i)
        Pilhaminima->array[i] = newNo(entrada[i], frequencia[i]);
      Pilhaminima->size = size;
      criarPilhaMinima(Pilhaminima);
      return Pilhaminima;
    }
    
    // A principal função que constrói a árvore Huffman
    struct NoMinimadaPilha *construirArvoreHuffman(char entrada[], int frequencia[], int size) {
      struct NoMinimadaPilha *esq, *dir, *topo;
     // Etapa 1: crie uma pilha mínima de capacidade
    // igual ao tamanho. Inicialmente, existem
    // modos iguais ao tamanho.
      struct PilhaMinima *Pilhaminima = criareconstruirPilhaMinima(entrada, frequencia, size);
      // Repete enquanto o tamanho da pilha não se torna 1
      while (!tamanho(Pilhaminima)) {
      // Etapa 2: Extrai os dois mínimos
      // itens de freq do pilha minima
        esq = extraiMin(Pilhaminima);
        dir = extraiMin(Pilhaminima);
        // Etapa 3: crie um novo nó interno
        //  com frequência igual ao
        // soma das frequências dos dois nós.
        // Torna os dois nós extraídos como
        // filhos esquerdo e direito deste novo nó.
        // Adicione este nó ao pilha minima
        // '$' é um valor especial para nós internos, não usado

        topo = newNo('$', esq->frequencia + dir->frequencia);
        topo->esq = esq;
        topo->dir = dir;
        inserirPilhaMinima(Pilhaminima, topo);
      }
      // Etapa 4: o nó restante é o
     // nó raiz e a árvore está completa.
      return extraiMin(Pilhaminima);
    }
    
    // Imprime códigos huffman da raiz da árvore Huffman.
    // Usa arr [] para armazenar códigos
    void printCodes(struct NoMinimadaPilha *raiz, int arr[], int topo) {
       // Atribua 0 à borda esquerda e retorne
      if (raiz->esq) {
        arr[topo] = 0;
        printCodes(raiz->esq, arr, topo + 1);
      }
      
      // Atribua 1 à borda direita e volte a
      if (raiz->dir) {
        arr[topo] = 1;
        printCodes(raiz->dir, arr, topo + 1);
      }
      
      // Se este for um nó folha, então
      // contém uma das entradas
      // caracteres, imprime o caractere
      // e seu código de arr []
      if (efolha(raiz)) {
        cout << raiz->entrada << "  | ";
        printArr(arr, topo);
      }
    }
    
    // A principal função que cria um
// Árvore de Huffman e codificaçãode impressão atravessando
// a árvore Huffman construída
    void Codificacao(char entrada[], int frequencia[], int size){
        // Construir árvore Huffman
      struct NoMinimadaPilha *raiz = construirArvoreHuffman(entrada, frequencia, size);
      // Imprima códigos Huffman usando
    // a árvore Huffman construída acima
      int arr[ARVORE_MAXIMO], topo = 0;
      printCodes(raiz, arr, topo);
    }
    
    // main  para testar as funções acima
    int main(){
        //TATAMALUTOOMATE  em portugues " se morde até morte"
      char arr[] =         {'E', 'L', 'M', 'O', 'A', 'T'};
      int frequencia[] =   { 1 ,  1,    2,  3,   4,   4 };
      int size = sizeof(arr) / sizeof(arr[0]);
      cout << "Caracteres | Código Huffman " << endl;
      cout << "\n----------------------\n"<<endl;
      Codificacao(arr, frequencia, size);
    }

