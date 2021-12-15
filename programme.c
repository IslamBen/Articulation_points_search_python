#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

struct Typegraphe{
    struct Typenoeud* prem;
    struct Typenoeud* dernier;
    struct Typelistearete* aretes;
    int nbr;
    int nbarete;
};

struct Typenoeud
{
    int valNoeud;
    int degre;
    char label[5];
    bool v;
    struct Typenoeud* suivant;
};

struct Typelistearete {
    struct Typenoeud* noeud1;
    struct Typenoeud* noeud2;
    struct Typelistearete* suivant;
};


struct Typegraphe* creerGraphe(){
    struct Typegraphe* mongraphe= (struct Typegraphe*)malloc(sizeof(struct Typegraphe));
    mongraphe->dernier=NULL;
    mongraphe->prem=NULL;
    mongraphe->aretes=NULL;
    mongraphe->nbarete=0;
    mongraphe->nbr=0;
    return mongraphe;
}

struct Typenoeud* ajouterNoeud(struct Typegraphe* graphe,int valeur,char *label){
    struct Typenoeud* noeud=(struct Typenoeud*)malloc(sizeof(struct Typenoeud));
    noeud->valNoeud=valeur;
    noeud->suivant=NULL;
    noeud->v=false;
    strcpy(noeud->label,label);
    if(graphe->nbr==0){
        graphe->prem=noeud;
        graphe->dernier=noeud;
    }else{
        struct Typenoeud* dernierNoeud;
        dernierNoeud=graphe->dernier;
        dernierNoeud->suivant=noeud;
        graphe->dernier=noeud;
    }
    graphe->nbr++;
    return noeud;
}

bool areteExiste(struct Typenoeud* noeud1,struct Typenoeud* noeud2,struct Typelistearete* aretes){
    bool existe=false;
    bool fin=false;
    struct Typelistearete* ptrListe=aretes;
    while(ptrListe!=NULL && !fin){
        if((ptrListe->noeud1==noeud1 && ptrListe->noeud2==noeud2) || (ptrListe->noeud2==noeud2 && ptrListe->noeud1==noeud1)){
            existe=true;
            fin=true;
        }
        ptrListe=ptrListe->suivant;
    }
    return existe;
}

struct Typelistearete* ajouterArete(struct Typegraphe* graphe,struct Typenoeud* noeud1,struct Typenoeud* noeud2){
    if(areteExiste(noeud1,noeud2,graphe->aretes)){
        exit(EXIT_SUCCESS);
    }else{
        struct Typelistearete* arete=(struct Typelistearete*)malloc(sizeof(struct Typelistearete));
        arete->noeud1=noeud1;
        arete->noeud2=noeud2;
        arete->suivant=NULL;
        struct Typelistearete* ptr =  graphe->aretes;
        if(ptr==NULL){
            graphe->aretes=arete;
        }else{
            while(ptr->suivant!=NULL){
                ptr=ptr->suivant;
            }
            ptr->suivant=arete;
        }
        graphe->nbarete++;
        noeud1->degre++;
        noeud2->degre++;
        return arete;
    }
}

void afficherNoeuds(struct Typegraphe* graphe){
    struct Typenoeud* ptr = graphe->prem;
    if(graphe->nbr==0){
        printf("LE GRAPHE EST VIDE\n");
    }else{
        printf("LA LISTE DES NOEUDS:\t");
        while(ptr!=NULL){
            printf("%s\t",ptr->label);
            ptr=ptr->suivant;
        }
    }
    printf("\n\n");
}

void afficherAretes(struct Typegraphe* graphe){
    struct Typelistearete* aretes = graphe->aretes;
    if(aretes==NULL){
        printf("LE GRAPHE NE CONTIENT AUCUN ARETE\n");
    }else{
        printf("LA LISTE DES ARETES\n");
        int i=1;
        while(aretes!=NULL){

            printf("\t\t\t ARETE %d : %s ET %s \n",i,aretes->noeud1->label,aretes->noeud2->label);
            aretes=aretes->suivant;
            i++;
        }
    }
    printf("\n");
}

void afficherGraphe(struct Typegraphe* graphe){
    afficherNoeuds(graphe);
    afficherAretes(graphe);
}

struct Typenoeud* adjacent(struct Typegraphe* graphe,struct Typenoeud* noeud,int i){
    struct Typelistearete* aretes = graphe->aretes;
    bool fin=false;
    int cmp=0;
    struct Typenoeud* resultat=NULL;
    if(aretes==NULL || graphe->nbarete==0){
        return NULL;
    } else{
        while(aretes!=NULL && !fin){
            if(aretes->noeud1==noeud || aretes->noeud2==noeud){
                cmp++;
                if(cmp==i){
                    fin=true;
                    if(aretes->noeud1==noeud){
                        resultat= aretes->noeud2;
                    }else{
                        resultat = aretes->noeud1;
                    }
                }
            }
            aretes=aretes->suivant;
        }
        return resultat;
    }
}

struct Typenoeud* noeudGraphe(struct Typegraphe* graphe,int i){
    bool fin=false;
    int cpt=0;
    if(graphe->nbr<i){
        return NULL;
    }else{
        struct Typenoeud* noeud = graphe->prem;
        while(noeud!=NULL && !fin){
            cpt++;
            if(cpt==i){
                fin=true;
            }else{
                noeud=noeud->suivant;
            }
        }
        return noeud;
    }
}

void dfs(struct Typegraphe* graphe,struct Typenoeud* noeud){
    noeud->v=true;
    printf("visited %s",noeud->label);
    struct Typenoeud* adj;
    int i;
    for (i=1;i<=noeud->degre;i++){
        adj= adjacent(graphe,noeud,i);
        if(adj->v==false){
            dfs(graphe,adj);
        }
    }
}

void retablir(struct Typegraphe* graphe){
    struct Typenoeud* ptr;
    while(ptr!=NULL){
        ptr->v=false;
        ptr=ptr->suivant;
    }
}
/*Dfs(v):
Mark(v) := "visité"
Pour i:=1, Degre(v)
Si Mark(Adjacent(v, i)) = " non visité"
Dfs(Adjacent(v, i))
Fsi
Finpour*/

int main(){
    struct Typegraphe* graphe=creerGraphe();
    struct Typenoeud* n1=ajouterNoeud(graphe,10,"N1");
    struct Typenoeud* n2=ajouterNoeud(graphe,10,"N2");
    struct Typenoeud* n3=ajouterNoeud(graphe,10,"N3");
    struct Typelistearete* a1=ajouterArete(graphe,n1,n3);
    struct Typelistearete* a2=ajouterArete(graphe,n1,n2);
    struct Typelistearete* a3=ajouterArete(graphe,n2,n3);
    struct Typenoeud* res=noeudGraphe(graphe,4);
    struct Typenoeud* noeud;
    dfs(graphe,graphe->prem);
    retablir(graphe);
    dfs(graphe,graphe->prem);
    
}