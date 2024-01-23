#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho {
    char nome[30];
    char rel[30];
    struct vizinho *prox;
} TVizinho;

typedef struct vertice {
    char nome[30];
    TVizinho *vizinho;
    struct vertice *prox;
} TVertice;



TVertice *insere_vertice(TVertice *g, char *nome) {
    TVertice *vertice = (TVertice *) malloc(sizeof(TVertice));
    strcpy(vertice->nome, nome);
    vertice->prox = g;
    vertice->vizinho = NULL;
    return vertice;
}

TVertice *busca_vertice(TVertice *vertice, char *nome) {
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0)) {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome) {
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0)) {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

TVizinho *busca_relacao(TVertice *vertice, char *nome) {
    TVizinho* vizinho = vertice->vizinho;
    while ((vizinho != NULL) && (strcmp(vizinho->rel, nome) != 0)) {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

TVizinho *busca_aresta(TVertice *g, char *nome_origem, char *nome_destino, char *predicado){
    TVertice* h = busca_vertice(g,nome_origem);
    TVizinho* vizinho = h->vizinho;
    if(h!=NULL){
        while (vizinho != NULL){
            if((strcmp(vizinho->nome, nome_destino) == 0)&&(strcmp(vizinho->rel,predicado)==0)){
                return vizinho;
            }
            vizinho = vizinho->prox;
        }
    }
    return vizinho;
}

void insere_aresta(TVertice *g, char *nome_origem, char *nome_destino, char *predicado) {
    TVertice *vertice = busca_vertice(g, nome_origem);
    TVizinho *vizinho = (TVizinho *) malloc(sizeof(TVizinho));
    strcpy(vizinho->nome, nome_destino);
    strcpy(vizinho->rel, predicado);
    vizinho->prox = vertice->vizinho;
    vertice->vizinho = vizinho;
}

void imprime(TVertice *vertice) {
    while (vertice != NULL) {
        printf("Entidade: %s\n", vertice->nome);
        TVizinho *vizinho = vertice->vizinho;
        while (vizinho != NULL) {
            printf("%s ", vizinho->rel);
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
            printf("\n");
        }
        printf("\n");
        vertice = vertice->prox;
    }
}




void libera_vizinho(TVizinho *vizinho) {
    if (vizinho != NULL) {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TVertice *vertice) {
    if (vertice != NULL) {
        libera_vizinho(vertice->vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}

void pergunta(TVertice *vertice, char *nome, char* predi){
    if(nome==NULL && predi==NULL){
        printf("Impossivel realizar a busca");
    }
    if(nome==NULL){
        printf("\nNULL, %s: \n",predi);
        if(busca_vertice(vertice,predi)==NULL){
            TVizinho* g;
            while (vertice != NULL) {
                g=vertice->vizinho;
                while (g != NULL) {
                    if (strcmp(g->rel,predi)==0){
                        printf("%s %s %s\n",vertice->nome,predi,g->nome);
                    }
                    g = g->prox;
                    }
               vertice = vertice->prox;
            }
        }else{
            TVizinho* p = NULL;
            while(vertice!=NULL){
                p = busca_vizinho(vertice->vizinho,predi);
                if(p!=NULL){
                    printf("%s ",vertice->nome);
                    printf("%s %s\n",p->rel,predi);
                }
                vertice=vertice->prox;
            }

        }
    }else if (predi==NULL){
        printf("\n%s, NULL: \n",nome);
        TVertice* h = busca_vertice(vertice,nome);
        if(h==NULL){
            TVizinho* g;
            while (vertice != NULL) {
                g=vertice->vizinho;
                while (g != NULL) {
                    if (strcmp(g->rel,nome)==0){
                        printf("%s %s %s\n",vertice->nome,nome,g->nome);
                    }
                    g = g->prox;
                    }
               vertice = vertice->prox;
            }
        }else{
            TVizinho* g = h->vizinho;
            while(g!=NULL){
                printf("%s %s %s\n",nome,g->rel,g->nome);
                g = g->prox;
            }
        }
    }else{
        printf("\n%s, %s: \n",nome,predi);
        TVertice* h = busca_vertice(vertice,nome);
        if(h!=NULL){
            TVizinho* g = h->vizinho;
            while(g!=NULL){
                if(strcmp(g->rel,predi)==0){
                    printf("%s %s %s \n",nome,predi,g->nome);
                }
                g = g->prox;
            }
        }else{
            TVizinho* g;
            while(vertice!=NULL){
                g = vertice->vizinho;
                while(g!=NULL){
                    if((strcmp(g->rel,nome)==0)&&(strcmp(g->nome,predi)==0)){
                        printf("%s %s %s\n",vertice->nome,nome,predi);
                    }
                    g = g->prox;
                }
                vertice = vertice->prox;
            }
        }
    }
}

void verifica(TVertice *vertice, char *nome, char* predi, char* nome2){
    printf("\n%s %s %s: \n",nome,predi,nome2);
    int a = verdadeiro(vertice,nome,predi,nome2);
    if(a==0){
        printf("Verdadeiro\n");
    }else{
        printf("Falso\n");
    }
}

int verdadeiro(TVertice *vertice, char *nome, char* predi, char* nome2){
    TVertice* h = busca_vertice(vertice,nome);
    if(h!=NULL){
       TVizinho* g = h->vizinho;
       while(g!=NULL){
        if((strcmp(g->rel,predi))==0&&(strcmp(g->nome,nome2)==0)){
            return 0;
        }
        g = g->prox;
       }
    }
    return 1;
}


void regras(TVertice *vertice){
    TVizinho* vizinho;
    while(vertice!=NULL){
        vizinho = vertice->vizinho;
        while(vizinho!=NULL){
            if((strcmp(vizinho->rel,"casou")==0)||(strcmp(vizinho->rel,"perdoou")==0)||(strcmp(vizinho->rel,"amante")==0)){
                if(busca_aresta(vertice,vertice->nome,vizinho->nome,"aliado")==NULL){
                    insere_aresta(vertice,vertice->nome,vizinho->nome,"aliado");
                }
            }
            vizinho = vizinho->prox;
        }
        vertice = vertice->prox;
    }
    /*int ctr = 0;
    while(vertice!=NULL){
        ctr = 0;
        TVizinho* vizinho = vertice->vizinho;
        if(vizinho==NULL){
            ctr++;
        }
        while ((vizinho != NULL)){
            if(strcmp(vizinho->nome, "Dragao") == 0){
                ctr++;
            }
            vizinho = vizinho->prox;
        }
        if((ctr==0)){
            printf("ALA %s",vertice->nome);
            insere_aresta(vertice,vertice->nome,"Humano","animal");
        }
        vertice = vertice->prox;
    }
    //return vertice;*/
}//backward_chaining(g,"Dany","amigo","Jorah");


int forward_chaining(TVertice *vertice, TVertice *h, char *nome1, char *predi, char *nome2, char *fixo, char *fixo2){
    int a;
    if(strcmp("ancestral",predi)==0){
        h = busca_vertice(vertice, nome1);
        TVizinho* g = h->vizinho;
        if(verdadeiro(vertice,nome1,predi,nome2)==0){
            return 0;
        }else if(verdadeiro(vertice,nome1,"gerou",nome2)==0){
            if(busca_aresta(vertice,fixo,fixo2,predi)==NULL){
                insere_aresta(vertice,fixo,fixo2,predi);
            }
            return 0;
        }else if(busca_relacao(h,"gerou")==NULL){
            return 1;
        }else{
            while(g!=NULL){
                if(strcmp(g->rel,"gerou")==0){
                    a = forward_chaining(vertice, h, g->nome, predi, nome2, fixo ,fixo2);
                    if (a==0){
                        if(busca_aresta(vertice,fixo,fixo2,predi)==NULL){
                            insere_aresta(vertice,fixo,fixo2,predi);
                        }
                        return 0;
                    }
                }
                g = g->prox;
            }
        }
    }else if(strcmp("descendente",predi)==0){
        h = busca_vertice(vertice, nome2);
        TVizinho* g = h->vizinho;
        if(verdadeiro(vertice,nome1,predi,nome2)==0){
            return 0;
        }else if(verdadeiro(vertice,nome2,"gerou",nome1)==0){
            if(busca_aresta(vertice,fixo,fixo2,predi)==NULL){
                insere_aresta(vertice,fixo,fixo2,predi);
            }
            return 0;
        }else if(busca_relacao(h,"gerou")==NULL){
            return 1;
        }else{
            while(g!=NULL){
                if(strcmp(g->rel,"gerou")==0){
                    a = forward_chaining(vertice, h, nome1, predi, g->nome, fixo,fixo2);
                    if (a==0){
                        if(busca_aresta(vertice,fixo,fixo2,predi)==NULL){
                            insere_aresta(vertice,fixo,fixo2,predi);
                        }
                        return 0;
                    }
                }
                g = g->prox;
            }
        }
    }
    return 1;
}

int backward_chaining(TVertice *vertice, char *nome1, char *predi, char *nome2){
    if (verdadeiro(vertice,nome1,predi,nome2)==0){
        return 0;
    }else{
        TVizinho* g;
        TVertice* h = vertice;
        char a[30];
        char m[10][30];
        TVertice* l = vertice;
        TVizinho* lv;
        int i = 0;
        int ctr;
        while(l!=NULL){
                lv = l->vizinho;
                while(lv!=NULL){
                    if((strcmp(lv->rel,"apelido")==0)&&(strcmp(lv->nome,nome2)==0)){
                        strcpy(m[i],l->nome);
                        i++;
                    }
                    lv = lv->prox;
                }
                l = l->prox;
            }
        strcpy(m[i],nome2);
        i++;
            while(vertice!=NULL){
                g = vertice->vizinho;
                while(g!=NULL){
                    ctr = 0;
                    while(ctr<i){
                        if((strcmp(g->rel,predi)==0)&&(strcmp(g->nome,m[0])==0)){
                            //printf("%s",vertice->nome);
                            strcpy(a,vertice->nome);
                            if(verdadeiro(h,a,"apelido",nome1)==0){
                                insere_aresta(h, nome1, nome2, predi);
                                insere_aresta(h, nome2, nome1, predi);
                                return 0;
                            }
                        }
                    ctr++;
                    }

                    g = g->prox;
                }
                vertice = vertice->prox;
            }
    }
    return 1;
}

/*
int backward_chaining(TVertice *vertice, char *nome1, char *predi, char *nome2){
    if (verdadeiro(vertice,nome1,predi,nome2)==0){
        return 0;
    }else{
        TVizinho* g; //nome1 = dany , predi = amigo , nome2 = mormont;
        TVertice* h = vertice;
        char a[30];
            while(vertice!=NULL){
                g = vertice->vizinho;
                while(g!=NULL){
                    if((strcmp(g->rel,predi)==0)&&(strcmp(g->nome,nome2)==0)){
                        strcpy(a,vertice->nome);
                        if(verdadeiro(h,a,"apelido",nome1)==0){
                            insere_aresta(h, nome1, nome2, predi);
                            insere_aresta(h, nome2, nome1, predi);
                            return 0;
                        }
                    }
                    g = g->prox;
                }
                vertice = vertice->prox;
            }
    }
    return 1;
}*/

void verifica_backward(TVertice *vertice, char *nome, char* predi, char* nome2){
    printf("\n%s %s %s: \n",nome,predi,nome2);
    int a = backward_chaining(vertice,nome,predi,nome2);
    if(a==0){
        printf("Verdadeiro\n");
    }else{
        printf("Falso\n");
    }
}

void verifica_forward(TVertice *vertice,TVertice *h, char *nome, char* predi, char* nome2){
    printf("\n%s %s %s: \n",nome,predi,nome2);
    int a = forward_chaining(vertice,h,nome,predi,nome2,nome,nome2);
    if(a==0){
        printf("Verdadeiro\n");
    }else{
        printf("Falso\n");
    }
}

int main() {
    TVertice *p;
    TVertice *g = NULL;
    g = insere_vertice(g, "Aegon5");
    g = insere_vertice(g, "Maekar1");
    g = insere_vertice(g, "Daeron");
    g = insere_vertice(g, "Aerion");
    g = insere_vertice(g, "Aemon");
    g = insere_vertice(g, "Aegon");
    g = insere_vertice(g, "Duncan");
    g = insere_vertice(g, "Jaehaerys2");
    g = insere_vertice(g, "Daeron2");
    g = insere_vertice(g, "Ormund");
    g = insere_vertice(g, "Aerys2");
    g = insere_vertice(g, "Steffon");
    g = insere_vertice(g, "Rhaegar");
    g = insere_vertice(g, "Viserys");
    g = insere_vertice(g, "Robert1");
    g = insere_vertice(g, "Stannis1");
    g = insere_vertice(g, "Renly");
    g = insere_vertice(g, "Rhaego");
    g = insere_vertice(g, "Illyrio");
    g = insere_vertice(g, "Daario");
    g = insere_vertice(g, "Barristan");
    g = insere_vertice(g, "Jhaqo");
    g = insere_vertice(g, "Hizdahr");
    g = insere_vertice(g, "Aegon");
    g = insere_vertice(g, "Drogo");
    g = insere_vertice(g, "Jorah");
    g = insere_vertice(g, "Masculino");
    g = insere_vertice(g, "Dyanna");
    g = insere_vertice(g, "Rhae");
    g = insere_vertice(g, "Daella");
    g = insere_vertice(g, "Shaera");
    g = insere_vertice(g, "Rhaelle");
    g = insere_vertice(g, "Rhaella");
    g = insere_vertice(g, "Cassana");
    g = insere_vertice(g, "Elia");
    g = insere_vertice(g, "Rhaenys");
    g = insere_vertice(g, "Maegi");
    g = insere_vertice(g, "Betha");
    g = insere_vertice(g, "Daenerys1");
    g = insere_vertice(g, "Drogon");
    g = insere_vertice(g, "Viserion");
    g = insere_vertice(g, "Rhaegal");
    g = insere_vertice(g, "Humano");
    g = insere_vertice(g, "Dragao");
    g = insere_vertice(g, "A Nascida da Tormenta");
    g = insere_vertice(g, "A Nao Queimada");
    g = insere_vertice(g, "A Quebradora de Correntes");
    g = insere_vertice(g, "A Mae de Dragoes");
    g = insere_vertice(g, "A Rainha Dragao");
    g = insere_vertice(g, "Khaleesi");
    g = insere_vertice(g, "Mhysa");
    g = insere_vertice(g, "Dany");
    g = insere_vertice(g, "O Rei Pedinte");
    g = insere_vertice(g, "Arstan Barba Branca");
    g = insere_vertice(g, "Mormont");
    g = insere_vertice(g, "Navio1");
    g = insere_vertice(g, "Navio2");
    g = insere_vertice(g, "Navio3");
    g = insere_vertice(g, "Bela");
    g = insere_vertice(g, "Forte");
    g = insere_vertice(g, "Dura");
    g = insere_vertice(g, "Impiedosa com inimigos");
    g = insere_vertice(g, "Jovem");
    g = insere_vertice(g, "Timida");
    g = insere_vertice(g, "Humilde");
    g = insere_vertice(g, "Guerreiro");
    g = insere_vertice(g, "Mercenario");
    g = insere_vertice(g, "Nobre");
    g = insere_vertice(g, "Cabelo loiro platinado");
    g = insere_vertice(g, "Olho violeta");
    g = insere_vertice(g, "Exercito");
    g = insere_vertice(g, "Confiante");
    g = insere_vertice(g, "Altamente treinados");
    g = insere_vertice(g, "Imaculados");
    g = insere_vertice(g, "Khalasar");
    g = insere_vertice(g, "Targaryen");
    g = insere_vertice(g, "Baratheon");
    g = insere_vertice(g, "Mormont");
    g = insere_vertice(g, "Selmy");
    g = insere_vertice(g, "Pira");
    g = insere_vertice(g, "Dothraki");
    g = insere_vertice(g, "Baia dos Escravos");
    g = insere_vertice(g, "Yunkai");
    g = insere_vertice(g, "Pentos");
    g = insere_vertice(g, "Braavos");
    g = insere_vertice(g, "Deserto Vermelho");
    g = insere_vertice(g, "Qarth");
    g = insere_vertice(g, "Casa dos Imortais");
    g = insere_vertice(g, "Baia dos Escravos");
    g = insere_vertice(g, "Yunkai");
    g = insere_vertice(g, "Mar Dothraki");
    g = insere_vertice(g, "Meereen");
    g = insere_vertice(g, "Astapor");
    g = insere_vertice(g, "Morto");
    g = insere_vertice(g, "Ferido");
    g = insere_vertice(g, "Pedra do Dragao");
    g = insere_vertice(g, "Sete Reinos");
    g = insere_vertice(g, "Magos");
    g = insere_vertice(g, "Crianca");
    g = insere_vertice(g, "Pedra do Dragao");
    g = insere_vertice(g, "Retomar os Sete Reinos");
    g = insere_vertice(g, "Acabar com a escravidao");
    g = insere_vertice(g, "Aprisionar Daenerys1 e Drogon");
    g = insere_vertice(g, "Voltar comercio escravo");
    g = insere_vertice(g, "Curar Drogo");
    g = insere_vertice(g, "Casar Daenerys1 com Drogo");
    g = insere_vertice(g, "Comprar um exercito");
    g = insere_vertice(g, "Aprisionar Drogon");
    g = insere_vertice(g, "Aprisionar Rhaegal");
    g = insere_vertice(g, "Aprisionar Viserion");
    g = insere_vertice(g, "Parar com assassinatos");
    g = insere_vertice(g, "Matar Jhaqo");
    g = insere_vertice(g, "Ganhar sabedoria dos Magos");
    g = insere_vertice(g, "Levar Daenerys1 para Pentos");
    g = insere_vertice(g, "Assassinar Daenerys1");
    g = insere_vertice(g, "Capturar Meereen");
    g = insere_vertice(g, "Ovos de Dragao");
    g = insere_vertice(g, "Cometa");
    g = insere_vertice(g, "Princesa");
    g = insere_vertice(g, "Rainha");
    g = insere_vertice(g, "Khal");
    g = insere_vertice(g, "Cavaleiro");
    g = insere_vertice(g, "Yunkish");
    g = insere_vertice(g, "Escravos");
    g = insere_vertice(g, "Cidades Livres");

    insere_aresta(g, "Aegon", "Masculino","sexo");
    insere_aresta(g, "Aegon5", "Masculino","sexo");
    insere_aresta(g, "Maekar1", "Masculino","sexo");
    insere_aresta(g, "Daeron", "Masculino","sexo");
    insere_aresta(g, "Aerion", "Masculino","sexo");
    insere_aresta(g, "Aemon", "Masculino","sexo");
    insere_aresta(g, "Aegon", "Masculino","sexo");
    insere_aresta(g, "Duncan", "Masculino","sexo");
    insere_aresta(g, "Jaehaerys2", "Masculino","sexo");
    insere_aresta(g, "Daeron2", "Masculino","sexo");
    insere_aresta(g, "Ormund", "Masculino","sexo");
    insere_aresta(g, "Aerys2", "Masculino","sexo");
    insere_aresta(g, "Steffon", "Masculino","sexo");
    insere_aresta(g, "Rhaegar", "Masculino","sexo");
    insere_aresta(g, "Viserys", "Masculino","sexo");
    insere_aresta(g, "Robert1", "Masculino","sexo");
    insere_aresta(g, "Stannis1", "Masculino","sexo");
    insere_aresta(g, "Renly", "Masculino","sexo");
    insere_aresta(g, "Drogo", "Masculino","sexo");
    insere_aresta(g, "Rhaego", "Masculino","sexo");
    insere_aresta(g, "Illyrio", "Masculino","sexo");
    insere_aresta(g, "Daario", "Masculino","sexo");
    insere_aresta(g, "Barristan", "Masculino","sexo");
    insere_aresta(g, "Jhaqo", "Masculino","sexo");
    insere_aresta(g, "Hizdahr", "Masculino","sexo");
    insere_aresta(g, "Jorah", "Masculino","sexo");

    insere_aresta(g, "Dyanna", "Feminino","sexo");
    insere_aresta(g, "Rhae", "Feminino","sexo");
    insere_aresta(g, "Daella", "Feminino","sexo");
    insere_aresta(g, "Shaera", "Feminino","sexo");
    insere_aresta(g, "Rhaelle", "Feminino","sexo");
    insere_aresta(g, "Rhaella", "Feminino","sexo");
    insere_aresta(g, "Cassana", "Feminino","sexo");
    insere_aresta(g, "Elia", "Feminino","sexo");
    insere_aresta(g, "Daenerys1", "Feminino","sexo");
    insere_aresta(g, "Rhaenys", "Feminino","sexo");
    insere_aresta(g, "Maegi", "Feminino","sexo");
    insere_aresta(g, "Betha", "Feminino","sexo");

    insere_aresta(g, "Maekar1", "Daeron","gerou");
    insere_aresta(g, "Maekar1", "Daeron","ancestral");
    insere_aresta(g, "Maekar1", "Aerion","gerou");
    insere_aresta(g, "Maekar1", "Aerion","ancestral");
    insere_aresta(g, "Maekar1", "Aemon","gerou");
    insere_aresta(g, "Maekar1", "Aemon","ancestral");
    insere_aresta(g, "Maekar1", "Aegon5","gerou");
    insere_aresta(g, "Maekar1", "Aegon5","ancestral");
    insere_aresta(g, "Maekar1", "Rhae","gerou");
    insere_aresta(g, "Maekar1", "Rhae","ancestral");
    insere_aresta(g, "Maekar1", "Daella","gerou");
    insere_aresta(g, "Maekar1", "Daella","ancestral");
    insere_aresta(g, "Dyanna", "Daeron","gerou");
    insere_aresta(g, "Dyanna", "Daeron","ancestral");
    insere_aresta(g, "Dyanna", "Aerion","gerou");
    insere_aresta(g, "Dyanna", "Aerion","ancestral");
    insere_aresta(g, "Dyanna", "Aemon","gerou");
    insere_aresta(g, "Dyanna", "Aemon","ancestral");
    insere_aresta(g, "Dyanna", "Aegon","gerou");
    insere_aresta(g, "Dyanna", "Aegon","ancestral");
    insere_aresta(g, "Dyanna", "Rhae","gerou");
    insere_aresta(g, "Dyanna", "Rhae","ancestral");
    insere_aresta(g, "Dyanna", "Daella","gerou");
    insere_aresta(g, "Dyanna", "Daella","ancestral");
    insere_aresta(g, "Aegon5", "Duncan","gerou");
    insere_aresta(g, "Aegon5", "Duncan","ancestral");
    insere_aresta(g, "Aegon5", "Jaehaerys2","gerou");
    insere_aresta(g, "Aegon5", "Jaehaerys2","ancestral");
    insere_aresta(g, "Aegon5", "Shaera","gerou");
    insere_aresta(g, "Aegon5", "Shaera","ancestral");
    insere_aresta(g, "Aegon5", "Daeron2","gerou");
    insere_aresta(g, "Aegon5", "Daeron2","ancestral");
    insere_aresta(g, "Aegon5", "Rhaelle","gerou");
    insere_aresta(g, "Aegon5", "Rhaelle","ancestral");
    insere_aresta(g, "Betha", "Duncan","gerou");
    insere_aresta(g, "Betha", "Duncan","ancestral");
    insere_aresta(g, "Betha", "Jaehaerys2","gerou");
    insere_aresta(g, "Betha", "Jaehaerys2","ancestral");
    insere_aresta(g, "Betha", "Shaera","gerou");
    insere_aresta(g, "Betha", "Shaera","ancestral");
    insere_aresta(g, "Betha", "Daeron2","gerou");
    insere_aresta(g, "Betha", "Daeron2","ancestral");
    insere_aresta(g, "Betha", "Rhaelle","gerou");
    insere_aresta(g, "Betha", "Rhaelle","ancestral");
    insere_aresta(g, "Rhaelle", "Steffon","gerou");
    insere_aresta(g, "Rhaelle", "Steffon","ancestral");
    insere_aresta(g, "Ormund", "Steffon","gerou");
    insere_aresta(g, "Ormund", "Steffon","ancestral");
    insere_aresta(g, "Steffon", "Robert1","gerou");
    insere_aresta(g, "Steffon", "Robert1","ancestral");
    insere_aresta(g, "Steffon", "Stannis1","gerou");
    insere_aresta(g, "Steffon", "Stannis1","ancestral");
    insere_aresta(g, "Steffon", "Renly","gerou");
    insere_aresta(g, "Steffon", "Renly","ancestral");
    insere_aresta(g, "Cassana", "Robert1","gerou");
    insere_aresta(g, "Cassana", "Robert1","ancestral");
    insere_aresta(g, "Cassana", "Stannis1","gerou");
    insere_aresta(g, "Cassana", "Stannis1","ancestral");
    insere_aresta(g, "Cassana", "Renly","gerou");
    insere_aresta(g, "Cassana", "Renly","ancestral");
    insere_aresta(g, "Jaehaerys2", "Aerys2","gerou");
    insere_aresta(g, "Jaehaerys2", "Aerys2","ancestral");
    insere_aresta(g, "Jaehaerys2", "Rhaella","gerou");
    insere_aresta(g, "Jaehaerys2", "Rhaella","ancestral");
    insere_aresta(g, "Shaera", "Aerys2","gerou");
    insere_aresta(g, "Shaera", "Aerys2","ancestral");
    insere_aresta(g, "Shaera", "Rhaella","gerou");
    insere_aresta(g, "Shaera", "Rhaella","ancestral");
    insere_aresta(g, "Aerys2", "Rhaegar","gerou");
    insere_aresta(g, "Aerys2", "Rhaegar","ancestral");
    insere_aresta(g, "Aerys2", "Viserys","gerou");
    insere_aresta(g, "Aerys2", "Viserys","ancestral");
    insere_aresta(g, "Aerys2", "Daenerys1","gerou");
    insere_aresta(g, "Aerys2", "Daenerys1","ancestral");
    insere_aresta(g, "Rhaella", "Rhaegar","gerou");
    insere_aresta(g, "Rhaella", "Rhaegar","ancestral");
    insere_aresta(g, "Rhaella", "Viserys","gerou");
    insere_aresta(g, "Rhaella", "Viserys","ancestral");
    insere_aresta(g, "Rhaella", "Daenerys1","gerou");
    insere_aresta(g, "Rhaella", "Daenerys1","ancestral");
    insere_aresta(g, "Rhaegar", "Rhaenys","gerou");
    insere_aresta(g, "Rhaegar", "Rhaenys","ancestral");
    insere_aresta(g, "Rhaegar", "Aegon","gerou");
    insere_aresta(g, "Rhaegar", "Aegon","ancestral");
    insere_aresta(g, "Elia", "Rhaenys","gerou");
    insere_aresta(g, "Elia", "Rhaenys","ancestral");
    insere_aresta(g, "Elia", "Aegon","gerou");
    insere_aresta(g, "Elia", "Aegon","ancestral");
    insere_aresta(g, "Daenerys1", "Rhaego","gerou");
    insere_aresta(g, "Daenerys1", "Rhaego","ancestral");
    insere_aresta(g, "Drogo", "Rhaego","gerou");
    insere_aresta(g, "Drogo", "Rhaego","ancestral");

    insere_aresta(g, "Daario", "Daenerys1","amante");
    insere_aresta(g, "Daenerys1", "Daario","amante");
    insere_aresta(g, "Viserys", "Daenerys1","ameacou");
    insere_aresta(g, "Daenerys1", "Jorah","amigo");
    insere_aresta(g, "Jorah", "Daenerys1","amigo");
    insere_aresta(g, "Drogon", "Dragao","animal");
    insere_aresta(g, "Viserion", "Dragao","animal");
    insere_aresta(g, "Rhaegal", "Dragao","animal");
    insere_aresta(g, "Barristan", "Daenerys1", "traiu");

    insere_aresta(g, "Daenerys1", "A Nascida da Tormenta", "apelido");
    insere_aresta(g, "Daenerys1", "A Nao Queimada", "apelido");
    insere_aresta(g, "Daenerys1", "A Quebradora de Correntes", "apelido");
    insere_aresta(g, "Daenerys1", "A Mae de Dragoes", "apelido");
    insere_aresta(g, "Daenerys1", "A Rainha Dragao", "apelido");
    insere_aresta(g, "Daenerys1", "Khaleesi", "apelido");
    insere_aresta(g, "Daenerys1", "Mhysa", "apelido");
    insere_aresta(g, "Daenerys1", "Dany", "apelido");
    insere_aresta(g, "Jorah", "Mormont", "apelido");
    insere_aresta(g, "Barristan", "Arstan Barba Branca", "apelido");

    insere_aresta(g, "Daenerys1", "Bela", "caracteristica");
    insere_aresta(g, "Daenerys1", "Princesa", "caracteristica");
    insere_aresta(g, "Daenerys1", "Forte", "caracteristica");
    insere_aresta(g, "Daenerys1", "Dura", "caracteristica");
    insere_aresta(g, "Daenerys1", "Impiedosa com inimigos", "caracteristica");
    insere_aresta(g, "Daenerys1", "Jovem", "caracteristica");
    insere_aresta(g, "Daenerys1", "Timida", "caracteristica");
    insere_aresta(g, "Daenerys1", "Humilde", "caracteristica");
    insere_aresta(g, "Drogo", "Guerreiro", "caracteristica");
    insere_aresta(g, "Daario", "Mercenario", "caracteristica");
    insere_aresta(g, "Hizdahr", "Nobre", "caracteristica");
    insere_aresta(g, "Daenerys1", "Cabelo loiro platinado", "caracteristica");
    insere_aresta(g, "Daenerys1", "Olho violeta", "caracteristica");
    insere_aresta(g, "Imaculados", "Exercito", "caracteristica");
    insere_aresta(g, "Khalasar", "Exercito", "caracteristica");
    insere_aresta(g, "Daenerys1", "Confiante", "caracteristica");
    insere_aresta(g, "Jorah", "Confiavel", "caracteristica");
    insere_aresta(g, "Imaculados", "Altamente treinados", "caracteristica");

    insere_aresta(g, "Daenerys1", "Targaryen", "casa");
    insere_aresta(g, "Robert1", "Baratheon", "casa");
    insere_aresta(g, "Jorah", "Mormont", "casa");
    insere_aresta(g, "Viserys", "Targaryen", "casa");
    insere_aresta(g, "Maekar1", "Targaryen", "casa");
    insere_aresta(g, "Ormund", "Baratheon", "casa");
    insere_aresta(g, "Barristan", "Selmy", "casa");

    insere_aresta(g, "Daenerys1", "Drogo", "casou");
    insere_aresta(g, "Daenerys1", "Hizdahr", "casou");

    insere_aresta(g, "Pira", "Drogon", "chocou");
    insere_aresta(g, "Pira", "Viserion", "chocou");
    insere_aresta(g, "Pira", "Rhaegal", "chocou");

    insere_aresta(g, "Drogo", "Dothraki", "cla");

    insere_aresta(g, "Drogo", "Khalasar", "comandou");
    insere_aresta(g, "Daenerys1", "Khalasar", "comandou");
    insere_aresta(g, "Daenerys1", "Imaculados", "comandou");

    insere_aresta(g, "Daenerys1", "Baia dos Escravos", "conquistou");
    insere_aresta(g, "Daenerys1", "Yunkai", "conquistou");

    insere_aresta(g, "Illyrio", "Daenerys1", "convidou");
    insere_aresta(g, "Illyrio", "Viserys", "convidou");

    insere_aresta(g, "Daenerys1", "Drogon", "dono");
    insere_aresta(g, "Daenerys1", "Viserion", "dono");
    insere_aresta(g, "Daenerys1", "Rhaegal", "dono");

    insere_aresta(g, "Illyrio", "Navio1", "emprestou");
    insere_aresta(g, "Illyrio", "Navio2", "emprestou");
    insere_aresta(g, "Illyrio", "Navio3", "emprestou");

    insere_aresta(g, "Daenerys1", "Navio1", "recebeu");
    insere_aresta(g, "Daenerys1", "Navio2", "recebeu");
    insere_aresta(g, "Daenerys1", "Navio3", "recebeu");

    insere_aresta(g, "Drogo", "Daenerys1", "engravidou");

    insere_aresta(g, "Jorah", "Daenerys1", "espionava");
    insere_aresta(g, "Daenerys1", "Pentos", "esteve");
    insere_aresta(g, "Viserys", "Pentos", "esteve");
    insere_aresta(g, "Illyrio", "Pentos", "esteve");
    insere_aresta(g, "Daenerys1", "Braavos", "esteve");
    insere_aresta(g, "Viserys", "Braavos", "esteve");
    insere_aresta(g, "Daenerys1", "Deserto Vermelho", "esteve");
    insere_aresta(g, "Daenerys1", "Qarth", "esteve");
    insere_aresta(g, "Daenerys1", "Casa dos Imortais", "esteve");
    insere_aresta(g, "Daenerys1", "Baia dos Escravos", "esteve");
    insere_aresta(g, "Daenerys1", "Yunkai", "esteve");
    insere_aresta(g, "Daenerys1", "Mar Dothraki", "esteve");
    insere_aresta(g, "Drogon", "Mar Dothraki", "esteve");
    insere_aresta(g, "Daenerys1", "Meereen", "esteve");
    insere_aresta(g, "Drogon", "Meereen", "esteve");
    insere_aresta(g, "Khalasar", "Qarth", "esteve");
    insere_aresta(g, "Daenerys1", "Astapor", "esteve");
    insere_aresta(g, "Cometa", "Deserto Vermelho", "esteve");

    insere_aresta(g, "Rhaella", "Morto", "ficou");
    insere_aresta(g, "Drogo", "Ferido", "ficou");

    insere_aresta(g, "Robert1", "Pedra do Dragao", "governou");
    insere_aresta(g, "Targaryen", "Sete Reinos", "governou");

    insere_aresta(g, "Daenerys1", "Escravos", "libertou");

    insere_aresta(g, "Daenerys1", "Drogo", "matou");
    insere_aresta(g, "Drogo", "Viserys", "matou");
    insere_aresta(g, "Maegi", "Rhaego", "matou");
    insere_aresta(g, "Drogon", "Magos", "matou");
    insere_aresta(g, "Drogon", "Crianca", "matou");
    insere_aresta(g, "Daenerys1", "Maegi", "matou");

    insere_aresta(g, "Daenerys1", "Pedra do Dragao", "nasceu");

    insere_aresta(g, "Daenerys1", "Retomar os Sete Reinos", "objetivo");
    insere_aresta(g, "Viserys", "Retomar os Sete Reinos", "objetivo");
    insere_aresta(g, "Daenerys1", "Acabar com a escravidao", "objetivo");
    insere_aresta(g, "Magos", "Aprisionar Daenerys1 e Drogon", "objetivo");
    insere_aresta(g, "Cidades Livres", "Voltar comercio escravo", "objetivo");
    insere_aresta(g, "Daenerys1", "Curar Drogo", "objetivo");
    insere_aresta(g, "Viserys", "Casar Daenerys1 com Drogo", "objetivo");
    insere_aresta(g, "Viserys", "Comprar um exercito", "objetivo");
    insere_aresta(g, "Daenerys1", "Aprisionar Drogon", "objetivo");
    insere_aresta(g, "Daenerys1", "Aprisionar Rhaegal", "objetivo");
    insere_aresta(g, "Daenerys1", "Aprisionar Viserion", "objetivo");
    insere_aresta(g, "Hizdahr", "Parar com assassinatos", "objetivo");
    insere_aresta(g, "Daenerys1", "Matar Jhaqo", "objetivo");
    insere_aresta(g, "Daenerys1", "Ganhar sabedoria dos Magos", "objetivo");
    insere_aresta(g, "Illyrio", "Levar Daenerys1 para Pentos", "objetivo");
    insere_aresta(g, "Robert1", "Assassinar Daenerys1", "objetivo");
    insere_aresta(g, "Daenerys1", "Capturar Meereen", "objetivo");

    insere_aresta(g, "Daenerys1", "Barristan", "perdoou");

    insere_aresta(g, "Daenerys1", "Rhaegal", "prendeu");
    insere_aresta(g, "Daenerys1", "Viserion", "prendeu");

    insere_aresta(g, "Illyrio", "Daenerys1", "presenteou");

    insere_aresta(g, "Daenerys1", "Ovos de dragao", "recebeu");

    insere_aresta(g, "Cidades Livres", "Daenerys1", "protestou");

    insere_aresta(g, "Daenerys1", "Drogo", "queimou");
    insere_aresta(g, "Daenerys1", "Maegi", "queimou");
    insere_aresta(g, "Daenerys1", "Ovos de dragao", "queimou");

    insere_aresta(g, "Daenerys1", "Drogon", "recuperou");

    insere_aresta(g, "Arstan Barba Branca", "Daenerys1", "salvou");

    insere_aresta(g, "Daenerys1", "Cometa", "seguiu");

    insere_aresta(g, "Barristan", "Illyrio", "serviu");
    insere_aresta(g, "Barristan", "Robert1", "serviu");
    insere_aresta(g, "Jorah", "Robert1", "serviu");
    insere_aresta(g, "Jorah", "Daenerys1", "serviu");
    insere_aresta(g, "Barristan", "Daenerys1", "serviu");
    insere_aresta(g, "Imaculados", "Daenerys1", "serviu");
    insere_aresta(g, "Khalasar", "Daenerys1", "serviu");
    insere_aresta(g, "Daario", "Daenerys1", "serviu");

    insere_aresta(g, "Daenerys1", "Princesa", "titulo");
    insere_aresta(g, "Daenerys1", "Rainha", "titulo");
    insere_aresta(g, "Daenerys1", "Khaleesi", "titulo");
    insere_aresta(g, "Drogo", "Khal", "titulo");
    insere_aresta(g, "Jorah", "Cavaleiro", "titulo");
    insere_aresta(g, "Barristan", "Cavaleiro", "titulo");

    insere_aresta(g, "Barristan", "Aerys2", "traiu");
    insere_aresta(g, "Daario", "Yunkish", "traiu");

    insere_aresta(g, "Daenerys1", "Drogon", "trocou");

    insere_aresta(g, "Daenerys1", "Imaculados", "recebeu");

    regras(g);
    imprime(g);

    pergunta(g,NULL,"Daenerys1");
    pergunta(g,"Daenerys1","caracteristica");
    pergunta(g,"traiu",NULL);
    pergunta(g,"Drogo",NULL);
    /*verifica(g,"Daenerys1","apelido","Dany");
    verifica(g,"Daenerys1","amigo","Jorah");
    verifica(g,"Dany","amigo","Jorah");
    verifica_backward(g,"Dany","amigo","Jorah");
    verifica(g,"Dany","amigo","Jorah");

    verifica(g,"Arstan Barba Branca","traiu","Dany");
    //verifica_backward(g,"Dany","amigo","Mormont");
    //verifica(g,"Dany","amigo","Mormont");
    verifica_backward(g,"Arstan Barba Branca","traiu","Dany");
    verifica(g,"Arstan Barba Branca","traiu","Dany");*/


    verifica_forward(g,g,"Drogo","ancestral","Daenerys1");
    verifica_forward(g,g,"Betha","ancestral","Viserys");
    verifica_forward(g,g,"Renly","descendente","Maekar1");
    verifica_forward(g,g,"Rhaegar","descendente","Ormund");

    pergunta(g,"Betha","ancestral");
    pergunta(g,"Renly","descendente");

    libera_vertice(g);
}
