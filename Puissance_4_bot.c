#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// les constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define VIDE ' '
#define INCONNU ' '

const int VA_GAGNER1 = 1;
const int VA_GAGNER2 = 2;
const int VA_GAGNER3 = 3;
const int VA_GAGNER4 = 4;
const float COEFF_0 = 0.5;
const float COEFF_1 = 1.0 ;
const float COEFF_1bis = 1.5;
const float COEFF_2  = 2.0;
const float COEFF_2bis  =2.5;
const float COEFF_3 = 3.0;
const float COEFF_3bis = 3.5;
const float COEFF_4 = 4.0 ; 

// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];
typedef float tableau[NB_COLONNES];
typedef Grille t[10];
// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void jouer(Grille laGrille, char pion, int * ligne, int * colonne);
int choisirColonne(Grille laGrille, char pion);
int chosirColonneStrategie1(Grille g,char PION);
bool estVainqueur(Grille LaGrille,int lig ,int colonne);
void faireJouerA(Grille g ,char PION , int *ligne ,int *colonne);
void faireJouerB(Grille g ,char PION,int *ligne,int *colonne);
void finDePartie(char PION);
int ChoisirColonneStrategie2(Grille g ,char PION);
int choisirColonneStrategie4(Grille g,char PION);
// Programme principal. C'est le pion A qui commence Ã  jouer
int main()
{
    Grille laGrille;
    char vainqueur=INCONNU;
    int ligne, colonne;
    vainqueur=INCONNU;
    initGrille(laGrille);
    afficher(laGrille, PION_A);
    while (vainqueur==INCONNU && !grillePleine(laGrille)){
        faireJouerA(laGrille,PION_A, &ligne, &colonne);
        afficher(laGrille, PION_B);  
        if (estVainqueur(laGrille, ligne, colonne) ){
            vainqueur = PION_A;
            
        } else if (!grillePleine(laGrille)){
            faireJouerB(laGrille,PION_B,&ligne,&colonne);
            afficher(laGrille, PION_A);
            if (estVainqueur(laGrille, ligne, colonne) ){
                vainqueur = PION_B;
                
            }
        }
        
    }
    
    system(EXIT_SUCCESS);
}


void initGrille(Grille laGrille){
    int l, c;
    for (l=0 ; l<NB_LIGNES ; l++){
        for (c=0 ; c<NB_COLONNES ; c++){
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion){
    int l, c;
    
    printf("\t");
    printf("  %c\n", pion);
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("----");
    }
    printf("-\n");
    for (l=0 ; l<NB_LIGNES ; l++){
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("----");
        }
        printf("-\n");
    }
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
            printf("  %d ",c);
    }
    printf("\n\n");

}

bool grillePleine(Grille laGrille){
    bool pleine = true;
    int c = 0;
    while (pleine && c<NB_COLONNES){
        if (laGrille[0][c] == VIDE){
            pleine = false;
        }
        c++;
    }
    return pleine;
}



int choisirColonne(Grille laGrille, char pion){
    int col;

    do{
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col<0 ||col>6);
    return col;
}

int chercherLigne(Grille laGrille, int col){
    int ligne = -1;

    while (ligne<NB_LIGNES-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col){
    // consiste Ã  regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j>=0 && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        return true;
    }
    return false;
}

void finDePartie(char vainqueur){
    if (vainqueur != INCONNU){
        printf("Joueur %c vainqueur\n", vainqueur);
    } else {
        printf("MATCH NUL");
    }
}
int ChoisirColonneStrategie2(Grille g ,char PION){
    int min,col;
    min=-1;
    col=0;
    for(int i=0 ;i<NB_COLONNES;i++){
        if(chercherLigne(g,i)>min){
            col=i;
            min=chercherLigne(g,i);
        }
    }
    return col;
}



int va_gagner(Grille laGrille, int lig, int col){
    // consiste à voir si l'ordinnateur pourrait gagner si un lignement de 3 est présent.
    char lePion;
    lePion = laGrille[lig][col];
    int cpt,i,j,winner;
    winner=0;
    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    
    
    while (i<NB_LIGNES && laGrille[i][col]==lePion && winner<=0){
        cpt++;
        i++;
    }
    if (cpt>=3){
        winner=1;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion && winner<=0){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion && winner<=0){
        cpt++;
        j++;
    }
    if (cpt>=3 ){
        winner=2;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    
    while (j>=0 && i>=0 && laGrille[i][j]==lePion && winner<=0){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion && winner<=0){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=3 ){
        winner=3;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion && winner<=0){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    
    while (i<NB_LIGNES && j>=0 && laGrille[i][j]==lePion && winner<=0){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=3 ){
        winner=4;
    }
    return winner;

}


int va_gagner_2(Grille laGrille, int lig, int col){
    // consiste à voir si l'ordinnateur pourrait gagner si un lignement de 2 est présent.
    char lePion;
    
    lePion = laGrille[lig][col];
    int cpt,i,j,winner;
    winner=0;
    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    
    
    while (i<NB_LIGNES && laGrille[i][col]==lePion  && winner<=0){
        cpt++;
        i++;
    }
    if (cpt>=2){
        winner=1;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion && winner<=0){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion  && winner<=0 ){
        cpt++;
        j++;
    }
    if (cpt>=2 ){
        winner=2;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    
    while (j>=0 && i>=0 && laGrille[i][j]==lePion && winner<=0 ){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion && winner<=0 ){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=2 ){
        winner=3;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion && winner<=0){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    
    while (i<NB_LIGNES && j>=0 && laGrille[i][j]==lePion && winner<=0 ){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=2 ){
        winner=4;
    }
    return winner;
}



void poser_pion(Grille g,int lig,int col,int *ligne,int *colonne,int deux_ou_trois){  
    char PION;
    int sens,tmp1,tmp2;
    int i;
    int j;
    tmp1=*ligne;
    tmp2=*colonne;
    PION=g[lig][col];
    i=lig;
    j=col;
    if(deux_ou_trois==0){
        sens=va_gagner(g,lig,col);
    }
    else{
        sens=va_gagner_2(g,lig,col);
    }
    if(sens==VA_GAGNER1){
        if(i-1>=0 && g[i-1][j]==VIDE){
            *ligne=i-1;
            *colonne=col;
        }
    }
    
    else if(sens==VA_GAGNER2){
        while(j<6 && g[i][j]==PION  ){
            j=j+1;
        }
        
        
        if(g[i][j]==VIDE && chercherLigne(g,j)==i){
            *ligne=i;
            *colonne=j;
            
        }
        j=col;
        
        while(j>0 && g[i][j]==PION && *ligne ==tmp1 && *colonne==tmp2 ){
            j=j-1;
        }
        
        if(g[i][j]==VIDE && chercherLigne(g,j)==i){
            *ligne=i;
            *colonne=j;
        }
        
    }
    else if(sens==VA_GAGNER4){
       while(i>0 && j<NB_LIGNES && g[i][j]==PION && *ligne==tmp1 && *colonne==tmp2){
            i=i-1;
            j=j+1;
       }
       if(g[i][j]==VIDE && chercherLigne(g,j)==i){
        *ligne=i;
        *colonne=j;
       }

       i=lig;
       j=col;
    
       while(i<5 && j>0 && g[i][j]==PION && *ligne==tmp1 && *colonne==tmp2){
            i=i+1;
            j=j-1;
            
       }

       if(g[i][j]==VIDE && chercherLigne(g,j)==i){
            *ligne=i;
            *colonne=j;
       }
    
    }

    else if(sens==VA_GAGNER3){
        
        while(i>0 && j>0 && g[i][j]==PION && *ligne==tmp1 && *colonne==tmp2){
            i=i-1;
            j=j-1;
        }
        if(g[i][j]==VIDE && chercherLigne(g,j)==i){
            *ligne=i;
            *colonne=j;
        }
        i=lig;
        j=col;

        while(i<5 && j<6 && g[i][j]==PION && *ligne==tmp1 && *colonne==tmp2){
            i=i+1;
            j=j+1;
        }
        if(g[i][j]==VIDE && chercherLigne(g,j)==i){
            *ligne=i;
            *colonne=j;
        }
    }
} 
void copie_grille(Grille g,Grille g_c){
    initGrille(g_c);
    for(int i=0;i<NB_LIGNES;i++){
        for(int j=0;j<NB_COLONNES;j++){
            g_c[i][j]=g[i][j];
        }
    }
}


float pourrait_gagner(Grille laGrille,int lig,int col){ 
    char lePion = laGrille[lig][col];
    int cpt,i,j,res;
    int possibilite_de_gagner = 1;
    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && (laGrille[i][col]==lePion|| laGrille[i][col]==VIDE )){
        cpt++;
        i++;
    }
    if (cpt>=4){
        possibilite_de_gagner= possibilite_de_gagner+1;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && (laGrille[lig][j]==lePion || laGrille[lig][j]==VIDE)){
        cpt++;
        j--;
    }
    if(cpt>=4){
        possibilite_de_gagner = possibilite_de_gagner + 1;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<NB_COLONNES && (laGrille[lig][j]==lePion || laGrille[lig][j]==VIDE)){
        cpt++;
        j++;
    }
    if (cpt>=4 ){
        possibilite_de_gagner = possibilite_de_gagner + 1;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && (laGrille[i][j]==lePion || laGrille[i][j]==VIDE)){
        cpt++;
        i--;
        j--;
    }
    if(cpt>=4){
        possibilite_de_gagner = possibilite_de_gagner + 1;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && (laGrille[i][j]==lePion || laGrille[i][j]==lePion)){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        possibilite_de_gagner = possibilite_de_gagner + 1;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && (laGrille[i][j]==lePion || laGrille[i][j]==VIDE)){
        cpt++;
        i--;
        j++;
    }
    if(cpt>=4){
        possibilite_de_gagner = possibilite_de_gagner +1 ;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j>=0 && (laGrille[i][j]==lePion || laGrille[i][j]==VIDE)){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        possibilite_de_gagner = possibilite_de_gagner + 1 ;
    }
    
    switch(possibilite_de_gagner){
        case 1 : res=COEFF_1;break;
        case 2 : res=COEFF_1bis;break;
        case 3 : res=COEFF_2;break;
        case 4 : res=COEFF_2bis;break;
        case 5 : res=COEFF_3;break;
        case 6 : res=COEFF_3bis;break;
        case 7 : res=COEFF_4;break;
        default : res=COEFF_0;
    }

    return res;
}

void empeche_victoire(Grille g ,int col,float tab[7],char PION){ // procédure qui permet d'empêcher l'ordinnateur de poser un pion qui ferait gagné l'adversaire
    int lig;
    
    int tmp1,tmp2;
    lig=chercherLigne(g,col);
    if(lig!=-1){
    tmp1=lig;
    tmp2=col;
    int compteur=0;
    
    if(lig-1>=0){
        lig=lig-1;
        tmp1=lig;
    }
    if (g[lig][col]!=PION){
        while(compteur<3 && g[lig-1][col+1]!=PION  && g[lig-1][col+1]!=VIDE  && lig>=1 && col<=5){
            compteur=compteur+1;
            lig=lig-1;
            col=col+1;
            }
        lig=tmp1;
        col=tmp2;
        while(compteur<3 && g[lig+1][col-1]!=PION && g[lig+1][col-1]!=VIDE && lig<=4 && col>=1 ){
            compteur=compteur+1;
            lig=lig+1;
            col=col-1;

            }
        lig=tmp1;
        col=tmp2;
        if(compteur>=3){
            tab[col]=tab[col]*-1;

            }
        lig=tmp1;
        col=tmp2;
        compteur=0;
        while(compteur<3 && g[lig+1][col+1]!=PION && g[lig+1][col+1]!=VIDE && lig<=4 && col<=5){
             compteur=compteur+1;
             lig=lig+1;
             col=col+1;
            }
        while(compteur<3 && g[lig-1][col-1]!=PION && g[lig-1][col-1]!=VIDE && lig>=1 && col>=1){
            compteur=compteur+1;
            lig=lig-1;
            col=col-1;
            }
        if(compteur>=3){
            tab[col]=tab[col]*-1;
        }
        
        }

    }
}
    



int recherche_max(float tab[7]){
    float maxi = tab[0];
    int ind=0;
    for(int i=0;i<=6;i++){
        if(tab[i]!=-1 && maxi<tab[i]){
            maxi=tab[i];
            ind=i;
        }
    }
    return ind;
}
int  strategie_2(Grille g,char PION){
    int ligne=1;
    float res;
    float mul = 2;
    int lig;
    int colonne=-1;
    Grille g2;
    
    float tab[7]={1,1,1,1,1,1,1};
    int i=0;
    copie_grille(g,g2);
    
    for(int c=0;c<NB_LIGNES;c++){
            for(int d=0;d<NB_COLONNES;d++){
                if(g[c][d]==PION && va_gagner(g,c,d)>0){
                    poser_pion(g,c,d,&ligne,&colonne,false);
                }

            }
        }
    
    if(ligne==-1 || colonne==-1){
        for(int a=0;a<NB_LIGNES;a++){
            for(int b=0;b<NB_COLONNES;b++){
                if(g[a][b]!=PION && g[a][b]!=VIDE && va_gagner(g,a,b)>0){
                    poser_pion(g,a,b,&ligne,&colonne,false);
                    
                }
                
            }
        }
    }
    
    if(ligne==-1 || colonne==-1){
       
    for(int lig=0;lig<NB_LIGNES;lig++){
            for(int i=0;i<NB_COLONNES;i++){
                if(chercherLigne(g,i)!=-1){
                if(g[lig][i]==PION ){
                    if(va_gagner_2(g,lig,i)>0){
                            poser_pion(g2,lig,i,&ligne,&colonne,true);
                            if(colonne!=-1){
                            tab[colonne] = tab[colonne] * COEFF_3bis ;  //calcul si deux des pions sont alignés
                            copie_grille(g,g2);
                            }
                        }
                    }
                }   
            }
        }
    
    for(int lig=0;lig<NB_LIGNES;lig++){
        for(int i=0;i<NB_COLONNES;i++){
            
            if(g[lig][i]!=PION && g[lig][i]!=VIDE){
                
                if(va_gagner_2(g,lig,i)>0){
                    
                    poser_pion(g2,lig,i,&ligne,&colonne,true);
                    printf("%d %d fdp\n\n",ligne,colonne);
                    if(colonne!=-1){
                    tab[colonne]=tab[colonne]*COEFF_4;
                    copie_grille(g,g2);
                    }
                } 
            }
        }
    }
    i=0;
    while(i<=6){
        lig=chercherLigne(g,i);
        if(lig==-1){
            tab[i]=-1;
        }
        else{
            res=pourrait_gagner(g,lig,i);
            tab[i]=tab[i]*res;
        }
        i=i+1;
    }
        
    i=0;
    while(i<=6){
        empeche_victoire(g,i,tab,PION);
        i=i+1;

    }
    i=0;
    tab[i]=tab[i]*1;
    for(int t=1;t<=COEFF_3;t++){
    if(tab[t]!=-1){
        tab[t]=tab[t]*mul;
        mul=mul+1;
        }
    }
    for(int o=4;o<NB_LIGNES;o++){
        if(tab[o]!=-1){
        mul=mul-1;
        tab[o]=tab[o]*mul;
        }
    }
    tab[6]=tab[6]*1;
    
    colonne=recherche_max(tab);
    
    for(int parcour=0;parcour<NB_COLONNES;parcour++){
        printf(" %f ",tab[parcour]);
        }
    } 
    return colonne;
    printf("col : %d",colonne);
}




void faireJouerA(Grille g ,char PION , int *ligne ,int *colonne){
    
    *ligne = -1;
    do {
        *colonne = choisirColonne(g, PION);
        *ligne = chercherLigne(g, *colonne);
    }while (*ligne==-1);
    g[*ligne][*colonne] = PION;
}



void faireJouerB(Grille g ,char PION,int *ligne,int *colonne){
    
    *colonne=strategie_2(g,PION);
    *ligne=chercherLigne(g,*colonne);
    g[*ligne][*colonne]=PION;
}



