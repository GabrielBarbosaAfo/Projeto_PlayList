#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LINHA 1024
#define TAM_PLAYLIST 50
#define TAM_MUSICA 50
#define TAM_BANDA 50
#define TAM_PESSOA 50

typedef struct TLista *lista;
typedef struct pessoa *TPessoa;
typedef struct amigos *TAmigos;
typedef struct playList *TPlayList;
typedef struct musica *TMusica;

struct pessoa{
    char nome[TAM_PESSOA];
    TPessoa next;

    //Lista amigos
    TAmigos amigoPrimeiro;
    TAmigos amigoUltimo;
    int numeroAmigos;

    //ListaPlayList
    TPlayList playLPrimeiro;
    TPlayList playLUltimo;
    int tamPlayLists;

};

struct TLista{
    TPessoa primeira;
    TPessoa ultima;
    int tamanho;
};

struct amigos{
    TAmigos proximoAmigo;
    TPessoa eu;
};

struct playList{
    char nomePlayList[TAM_PLAYLIST];
    TPlayList nextPL;

     //Lista Musicas
    TMusica primeiraMusica;
    TMusica ultimaMusica;
    int quantidadeMusica;
};

struct musica{
    char nomeMusica[TAM_MUSICA], banda[TAM_BANDA];
    TMusica nextMusica;
};

//Funç]oes para criar as listas
lista criaLista();
TPlayList criaPlayList(char *playList);
TAmigos criaAmigo(TPessoa);
TPessoa criaPessoa(char nome[]);
TMusica criaMusica(char *musica,char *banda);

//Funções de pesquisa
TPessoa pesquisaPessoa(lista l, char nome[]);
TPlayList pesquisaPlayListaNome(TPessoa p,char *nomePlayList);

TMusica recortaMusicaPlayList(TPlayList pl, char *nomeBanda);

//Funções auxiliares
void retiraEspaco(char *vetor);
void printaLista(lista l);

//Funções para inserir na playlist
int listaInserePessoaAmigo(lista l, char *amizade);
int listaInserePlayList(lista l, char *playListTXT);
void insereFim(lista l,TPessoa p);
void insereAmigo(TPessoa, TAmigos);
void inserePlayList(TPessoa p,TPlayList pl);

int carregaMusicaPlayList(lista l);

void refatoraPlayLists(lista l);
int guardaPlayListRefatorada(lista l);
int calculaSimilaridade(lista l);
int mergerPlayList(lista l);
int geraArquivo(lista l);

//Desaloca Memoria de todas as structs
void desalocaMemorialAll(lista);

