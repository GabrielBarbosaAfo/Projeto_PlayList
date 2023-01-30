#include "pessoa.h"

int myPlay(){
    lista l = criaLista();
    
    listaInserePessoaAmigo(l,"amizade.txt");
    listaInserePlayList(l,"playList.txt");
    carregaMusicaPlayList(l);
    printaLista(l);
    refatoraPlayLists(l);
    printf("\nRefatorando\n");
    printaLista(l);
    guardaPlayListRefatorada(l);
    calculaSimilaridade(l);
    mergerPlayList(l);
    printf("\nMerge:\n");
    printaLista(l);
    geraArquivo(l);

    desalocaMemorialAll(l);
    return EXIT_SUCCESS;
}

int main(){
    return myPlay();
}

