#include "pessoa.h"

//cria a lista para pessoas
lista criaLista(){
    lista l=(lista)malloc(sizeof(struct TLista));
    if(l){
        l->primeira=NULL;
        l->ultima=NULL;
        l->tamanho=0;
    }
    return l;
}

//Cria a lista pessoas
TPessoa criaPessoa(char nome[]){
    TPessoa p=(TPessoa)malloc(sizeof(struct pessoa));
    if(p){
        p->next = NULL;
        p->numeroAmigos = 0;
        p->amigoPrimeiro = NULL;
        p->amigoUltimo = NULL;
        strcpy(p->nome,nome);
    }
    return p;
}

//Insere na lista de pessoas
void insereFim(lista l,TPessoa p){
    if(l->primeira==NULL){
        l->primeira = p;
    }
    else{
        l->ultima->next = p;
    }
    l->ultima = p;
    (l->tamanho)++;
}

//Pesquisa a pessoa e se encontrar retorna uma variavel TPesssoa, se não retorna o TPessoa NULL
TPessoa pesquisaPessoa(lista l, char nome[]){
    TPessoa p;
    p = l->primeira;
    while(p){
        if(strcmp(p->nome,nome)==0)
            return p;
        else
            p = p->next;
    }
    return (TPessoa)NULL;
}

//Cria a lista de Amigos do TPessoa
TAmigos criaAmigo(TPessoa p){
    TAmigos amig = (TAmigos)malloc(sizeof(struct amigos));
    if(amig){
        amig->eu = p;
        amig->proximoAmigo = NULL;
    }
    return amig;
}

//Insere um amigo na lista TAmigos
void insereAmigo(TPessoa p, TAmigos amig){
    if(p->amigoPrimeiro==NULL){
        p->amigoPrimeiro = amig;
    }
    else{
        p->amigoUltimo->proximoAmigo = amig;
    }
    p->amigoUltimo = amig;
    amig->proximoAmigo = NULL;
    (p->numeroAmigos)++;
}

//Cria a lista de playList
TPlayList criaPlayList(char *playList){
    TPlayList pl = (TPlayList)malloc(sizeof(struct playList));
    if(pl){
        pl->nextPL = NULL;
        pl->primeiraMusica = NULL;
        pl->ultimaMusica = NULL;
        pl->quantidadeMusica = 0;
        strncpy(pl->nomePlayList,playList,TAM_PLAYLIST);    
    }
    return pl;
}

//Cria a lista de Musicas
TMusica criaMusica(char *musica,char *banda){
    TMusica music = (TMusica)malloc(sizeof(struct musica));
    if(music){
        music->nextMusica = NULL;
        strncpy(music->nomeMusica,musica,TAM_MUSICA);
        strncpy(music->banda,banda,TAM_BANDA);
    }
    return music;
}

//Insere a musica na lista de musicas
void insereMusica(TPlayList pl, TMusica music){
    if(pl->primeiraMusica == NULL)
        pl->primeiraMusica = music;
    else
        pl->ultimaMusica->nextMusica = music;
    pl->ultimaMusica = music;
    music->nextMusica = NULL;
    (pl->quantidadeMusica)++;
}

//Insere a playlist na lista de de playlists
void inserePlayList(TPessoa p,TPlayList pl){
    if(p->playLPrimeiro == NULL)
        p->playLPrimeiro = pl;
    else
        p->playLUltimo->nextPL = pl;
    p->playLUltimo = pl;
    pl->nextPL = NULL;
    (p->tamPlayLists)++;
}

void printaLista(lista l){
    TPessoa p = l->primeira;
    TAmigos amig;
    TPlayList pl;
    TMusica music;
    while(p){
        printf("Pessoa:\n%s\n",p->nome);
        if(p->amigoPrimeiro){
            amig = p->amigoPrimeiro;
            printf("\tAmigos:\n");
            while(amig){
                printf("\t%s\n",amig->eu->nome);
                amig = amig->proximoAmigo;
            }
        }
        if(p->playLPrimeiro){
            printf("\t\tPlaylist\n");
            pl = p->playLPrimeiro;
            while(pl){
                printf("\t\t%s\n",pl->nomePlayList);
                if(pl->primeiraMusica){
                    music = pl->primeiraMusica;
                    printf("\t\t\tMusicas:\n");
                    while(music){
                        printf("\t\t\t%s - %s\n",music->banda,music->nomeMusica);
                        music = music->nextMusica;
                    }
                }
                pl = pl->nextPL;
            }
        }
        p = p->next;
    }
}

//Função para ler as pessoas e os amigos das mesma no aquivo txt
int listaInserePessoaAmigo(lista l,char *amizade){
    FILE * arquivo = fopen(amizade,"r+");
    TPessoa p, p2;
    TAmigos amig, amig2;
    char linha[TAM_LINHA];
    char *nome,*nome2;
    if(!arquivo)
        return -1;
    fgets(linha,TAM_LINHA,arquivo);
    nome = strtok(linha,";");
    while(nome){
        p = criaPessoa(nome);
        nome = strtok(NULL,";\n\r ");
        insereFim(l,p);
    }
    while(fgets(linha,TAM_LINHA,arquivo)){
        nome = strtok(linha,";");
        p = pesquisaPessoa(l,nome);
        if(p == NULL)
            return -2;
        nome2 = strtok(NULL,"\n\r ");
        p2 = pesquisaPessoa(l,nome2);
        if(p2 == NULL)
            return -2;
        amig = criaAmigo(p);
        amig2 = criaAmigo(p2);
        insereAmigo(p,amig2);
        insereAmigo(p2,amig);
    }
    fclose(arquivo);
    return 1;
}

//Função para ler as playlists do aquivo txt
int listaInserePlayList(lista l, char *playListTXT){
    FILE * arquivo = fopen(playListTXT,"r+");
    TPlayList pl;
    TPessoa p;
    char linha[TAM_LINHA], *buffer;
    int qtdplayList;
    if(!arquivo)
        return -1;
    while(fgets(linha, TAM_LINHA, arquivo)){
        buffer = strtok(linha, ";");
        if(!(p = pesquisaPessoa(l,buffer)))
            return -2;
        buffer = strtok(NULL, ";");
        qtdplayList = atoi(buffer);
        for(int i = 0; i < qtdplayList; i++){
            buffer = strtok(NULL,";\n\r ");
            pl = criaPlayList(buffer);
            inserePlayList(p,pl);
        }
    }
    fclose(arquivo);
    return 1;
}

//Função para ler as musicas do aquivo txt 
int carregaMusicaPlayList(lista l){
    TPessoa p;
    TPlayList pl;
    TMusica music;
    FILE *arquivo;
    char linha[TAM_LINHA], *buffer,banda[TAM_BANDA];
    p = l->primeira;
    while(p){
        pl = p->playLPrimeiro;
        while(pl){
            arquivo = fopen(pl->nomePlayList,"r");
            if(!arquivo)
                return -1;
            while(fgets(linha,TAM_LINHA,arquivo)){
                buffer = strtok(linha,"-");
                strncpy(banda,buffer,TAM_BANDA);
                buffer = strtok(NULL,"\n\r");
                music = criaMusica(buffer,banda);
                insereMusica(pl,music);  
            }
            fclose(arquivo);
            pl = pl->nextPL;
        }
        p = p->next;
    }
    return 1;
}

//Pesquisa uma playlist na lista playlista caso haja playlists iguais retorna o ponteiro pl da struct TPlayList caso não ache retorna NULL 
TPlayList pesquisaPlayListaNome(TPessoa p,char *nomePlayList){
    TPlayList pl;
    if(!p->playLPrimeiro)
        return NULL;
    pl = p->playLPrimeiro;
    while(pl){
        if(!strcmp(pl->nomePlayList,nomePlayList)){
            return pl;
        }
        pl = pl->nextPL;
    }
    return NULL;
}

//recorta a musica da playlist para adicionar as memas na banda
TMusica recortaMusicaPlayList(TPlayList pl, char *nomeBanda){
    TMusica music,musicAux;
    if(!pl->primeiraMusica)
        return NULL;
    music = pl->primeiraMusica;
    while(music){
        if(!strcmp(music->banda,nomeBanda)){
            if(music == pl->primeiraMusica)
                pl->primeiraMusica = music->nextMusica;
            else if(music == pl->ultimaMusica)
                pl->ultimaMusica = musicAux;
            else
                musicAux->nextMusica = music->nextMusica;
            pl->quantidadeMusica--;
            return music;
        }
        musicAux = music;
        music = music->nextMusica;
    }
    return NULL;
}

//Refatorora a nova playlist colocando as musicas com sua devidas bandas
void refatoraPlayLists(lista l){
    TPlayList pl,plAux;
    TPessoa p;
    TMusica music, musicAux;
    char nomeBanda[TAM_BANDA];
    p = l->primeira;
    while(p){
        plAux = p->playLPrimeiro;
        p->playLPrimeiro = NULL;
        p->playLUltimo = NULL;
        p->tamPlayLists = 0;
        while(plAux){
            music = plAux->primeiraMusica;
            while(music){
                strcpy(nomeBanda,music->banda);
                if(!pesquisaPlayListaNome(p,nomeBanda)){
                    pl = criaPlayList(nomeBanda);
                    inserePlayList(p,pl);
                    while((musicAux = recortaMusicaPlayList(plAux,nomeBanda))){
                        insereMusica(pl,musicAux);   
                    }
                }
                music = plAux->primeiraMusica;
            }
            plAux = plAux->nextPL;
        }
        p = p->next;
    }
    //lembrar de destruir a playlist!!!(plAux)
}

//Retira Espaco do vetor
void retiraEspaco(char *vetor){
    if(vetor[strlen(vetor)-1] == ' '){
        vetor[strlen(vetor)-1] = '\0'; 
    }
}

//Printa a playlist refatorada em um arquivo txt
int guardaPlayListRefatorada(lista l){
    TPlayList pl;
    TPessoa p;
    char nomePlayList[TAM_PLAYLIST];
    FILE *arquivo;
    if(!l)
        return 0;
    arquivo = fopen("playlist-refatorada.txt","w");
    if(!arquivo)
        return -1;
    p = l->primeira;
    while(p){
        fprintf(arquivo,"%s;%d",p->nome,p->tamPlayLists);
        pl = p->playLPrimeiro;
        while(pl){
            strcpy(nomePlayList,pl->nomePlayList);
            retiraEspaco(nomePlayList);
            fprintf(arquivo,";%s",nomePlayList);
            pl = pl->nextPL;
        }
        fprintf(arquivo,"\n");
        p = p->next;
    }
    fclose(arquivo);
    return 1;
}

//calcula a quantidade de musicas que os amigos tem iguais entre si
int calculaSimilaridade(lista l){
    TPessoa pPessoa,pAmigo,pCursor;
    TPlayList plPessoa,plAmigo;
    TAmigos amig;
    TMusica musicPessoa, musicAmigo;
    int verificaPessoa = 0;
    int qtdSimilaridade = 0;
    FILE *arquivo = fopen("similaridades.txt","w");
    if(!arquivo)
        return 0;
    pPessoa = l->primeira;
    while(pPessoa){
        amig = pPessoa->amigoPrimeiro;
        while(amig){
            pAmigo = amig->eu;
            pCursor = l->primeira;
            while(pCursor){
                if(pCursor == pPessoa || pCursor == pAmigo){
                    if(pCursor == pAmigo){
                        amig = amig->proximoAmigo;
                        verificaPessoa = 1;
                        break;
                    }
                    else{
                        verificaPessoa = 0;
                        break;
                    }
                }
                pCursor = pCursor->next;
            }
            if(verificaPessoa == 1){
                verificaPessoa = 0;
                continue;
            }
            plPessoa = pPessoa->playLPrimeiro;
            while(plPessoa){
                plAmigo = pesquisaPlayListaNome(pAmigo,plPessoa->nomePlayList);
                if(plAmigo){
                    musicPessoa = plPessoa->primeiraMusica;
                    while(musicPessoa){
                        musicAmigo = plAmigo->primeiraMusica;
                        while(musicAmigo){
                            if(strcmp(musicPessoa->nomeMusica,musicAmigo->nomeMusica) == 0){
                                qtdSimilaridade++;
                            }
                            musicAmigo = musicAmigo->nextMusica;
                        }
                        musicPessoa = musicPessoa->nextMusica;
                    }
                }
                plPessoa = plPessoa->nextPL;
            }
            fprintf(arquivo,"%s;%s;%d\n",pPessoa->nome,pAmigo->nome,qtdSimilaridade);
            qtdSimilaridade = 0;
            amig = amig->proximoAmigo;
        }
        pPessoa = pPessoa->next;
    }
    fclose(arquivo);
    return 1;
}

// Faz a união das musicas dos amigos caso tenha playlist e musicas iguais
int mergerPlayList(lista l){
    TPessoa pPessoa,pAmigo;
    TPlayList plPessoa,plAmigo;
    TAmigos amig;
    TMusica musicPessoa, musicAmigo, musicNovaGuardar;
    int achouMusicaPlayList, atualizacaoPlayListAmig = 0;
    pPessoa = l->primeira;
    do{
        atualizacaoPlayListAmig = 0;
        while(pPessoa){
            amig = pPessoa->amigoPrimeiro;
            while(amig){
                pAmigo = amig->eu;
                plPessoa = pPessoa->playLPrimeiro;
                while(plPessoa){
                    plAmigo = pesquisaPlayListaNome(pAmigo,plPessoa->nomePlayList);
                    if(plAmigo){
                        musicPessoa = plPessoa->primeiraMusica;
                        while(musicPessoa){
                            achouMusicaPlayList = 0;
                            musicAmigo = plAmigo->primeiraMusica;
                            while(musicAmigo){
                                if(strcmp(musicPessoa->nomeMusica,musicAmigo->nomeMusica) == 0){
                                    achouMusicaPlayList = 1;
                                    break;
                                }
                                musicAmigo = musicAmigo->nextMusica;
                            }
                            if(achouMusicaPlayList == 1)
                                achouMusicaPlayList = 0;
                            else{
                                atualizacaoPlayListAmig = 1;
                                musicNovaGuardar = criaMusica(musicPessoa->nomeMusica,musicPessoa->banda);
                                insereMusica(plAmigo,musicNovaGuardar);
                            }
                            musicPessoa = musicPessoa->nextMusica;
                        }
                    }
                    plPessoa = plPessoa->nextPL;
                }
                amig = amig->proximoAmigo;
            }
            pPessoa = pPessoa->next;
        }
    }while(atualizacaoPlayListAmig == 1);
    return 1;
}

//Gera o arquivo com as musicas e as playlist das pessoas com os amigos
int geraArquivo(lista l){
    TPessoa p;
    TPlayList pl;
    TMusica music;
    FILE *arquivo;
    char comandoCriaPasta[TAM_PESSOA+6], guardarCaminhaPlayList[TAM_PLAYLIST+TAM_PESSOA+5];
    p = l->primeira;
    while(p){
        sprintf(comandoCriaPasta,"mkdir %s",p->nome);
        system(comandoCriaPasta);
        pl = p->playLPrimeiro;
        while(pl){
            sprintf(guardarCaminhaPlayList,"%s/%s.txt",p->nome,pl->nomePlayList);
            retiraEspaco(guardarCaminhaPlayList);
            arquivo = fopen(guardarCaminhaPlayList,"w");
            if(!arquivo)
                return 0;
            music = pl->primeiraMusica;
            while(music){
                fprintf(arquivo,"%s-%s\n",music->banda,music->nomeMusica);
                music = music->nextMusica;
            }
            fclose(arquivo);
            pl = pl->nextPL;
        }
        p = p->next;
    }
    return 1;
}

//desaloca memoria da lista
void desalocaMemorialAll(lista l){
    TPessoa p, pAjuda;
    TPlayList pl, plAjuda;
    TAmigos amig, amigAjuda;
    TMusica music, musicAjuda;
    p = l->primeira;
    while(p){
        amig = p->amigoPrimeiro;
        while(amig){
            amigAjuda = amig->proximoAmigo;
            free(amig);
            amig = amigAjuda;
        }
        pl = p->playLPrimeiro;
        while(pl){
            music = pl->primeiraMusica;
            while(music){
                musicAjuda = music->nextMusica;
                free(music);
                music = musicAjuda;
            }
            plAjuda = pl->nextPL;
            free(pl);
            pl = plAjuda;
        }
        pAjuda = p->next;
        free(p);
        p = pAjuda;
    }
    free(l);
}