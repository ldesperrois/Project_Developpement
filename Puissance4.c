
//---------- Les commentaires que vous voyez ne sont pas les commentaires définitifs---------//
//----------Desperrois Lucas, Etudiant en 1ère année de BUT Informatique--------------------//
//----------Programme Puissance4.c --------------------------------------------------------//
//----------Appel des bibliothèsques------------------------------------------------------//


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
//------------------------------------------------------------------//
//-----------------Déclaration des Constantes-----------------------//

const char PION_A ='X';
const char PION_B = 'O';
const char VIDE = ' ';
const char INCONNU = ' ';
#define NBLIG 6
#define NBCOL 7 
const int COLONNE_DEBUT =4;
const char GAUCHE ='q';
const char DROITE ='d';
//-----------------------------------------------------------------------------//
//----------------Déclaration des Fonctions et Procédures et de type----------//

typedef char t_grille [NBLIG][NBCOL];

void initGrille(t_grille);
void afficher(t_grille,char,int);
void jouer(t_grille,char,int*,int*);
void finDePartie(char);

bool grillepleine(t_grille);
int choisirColonne(t_grille,char,int);
int trouverLigne(t_grille,int);
bool estVainqueur(t_grille,int,int);

//----------------------------------------------------------------//
//------------------------Programme Principal pour le jeu---------//
int main(){
    t_grille g;
    int colonne,ligne;
    char vainqueur;
    initGrille(g);
    vainqueur=INCONNU;
    afficher(g,PION_A,COLONNE_DEBUT);

    while((vainqueur==INCONNU)&((grillepleine(g))==0)){
        jouer(g,PION_A,&colonne,&ligne);
        printf("%d ",ligne);
        printf("\n");
        afficher(g,PION_B,COLONNE_DEBUT);
        if((estVainqueur(g,colonne,ligne))==1){
            vainqueur=PION_A;
        }
        else if((grillepleine(g))==0){
            jouer(g,PION_B,&colonne,&ligne);
            afficher(g,PION_A,COLONNE_DEBUT);
            if((estVainqueur(g,colonne,ligne))==1){
                vainqueur=PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    return EXIT_SUCCESS;
}

//------------------------------------------------------------//
//-----------Initialisation de La grille de jeu---------------//
void initGrille(t_grille g){
    for(int i=0;i<NBLIG;i++){
        for(int j=0;j<NBCOL;j++){                           //parcours entier du tableau à deux dimenssions pour initialiser chaque case par un caractère vide
            g[i][j]=VIDE;

        }
    }
}
//--------------------------------------------------------------//
//-----------------------Procedure d'affichage-----------------//
void afficher(t_grille g,char PION,int DEB){
    system("clear");                                        //terminal effacé à chaque affichage pour un affichage clair//
    int premiereligne;      
    premiereligne=1;
    
    printf("  ");
    while((premiereligne<DEB)){                             //affichage du pion Au dessus de la grille//
        printf("    ");
        premiereligne++;
    } 
    printf("%c",PION);
    printf("\n");
    for(int a=0;a<NBLIG;a++){                               // on effectue le motif d'une ligne 6 fois//
        printf(" ");
        for(int i=0;i<NBCOL;i++){                           // on affiche les barres du dessus de chaque ligne//
            printf("---");
            printf(" ");
        }
        printf("\n");
        for(int j=0;j<NBCOL;j++){                           //on affiche les valeurs de la grille séparé par des "|""
            printf("|");
            printf(" ");
            printf("%c",g[a][j]);
            printf(" ");
            
        }
        printf("|");
        printf("\n");
   }
   printf(" ");
   for(int b=0;b<NBCOL;b++){
        printf("---");
        printf(" ");
   }
   printf("\n");
   printf("  ");
   for(int chiffrecolonne=1;chiffrecolonne<=NBCOL;chiffrecolonne++){        //affichage des nombres sous la grille, fidèle à ma maquette
        printf("%d",chiffrecolonne);
        printf("   ");
   }
   printf("\n");
}
//-------------------------------------------------------------------//
//---------------------Choix de la colonne--------------------------//
int choisirColonne(t_grille g,char PION,int colonne){
    char rep;
    printf("Décalez vous de colonne avec q pour la gauche et d pour la droite\n");
    scanf("%c",&rep);
    while(VIDE!=rep){                                                       // tant que le joueur ne rentre pas espace on demande la colonne
        if(rep==GAUCHE){
            colonne=colonne-1;
            if(colonne==0){
                colonne=7;                                                  // si le joueur en choississant de décaler sont pions trois à droite il revient à gauche 
            }
        }

        if(rep==DROITE){
            colonne=colonne+1;
            if(colonne==8){
                colonne=1;                                                  // inverssement mais si le joueur va trop à gauche le piont revient à droite
            }
        }
        afficher(g,PION,colonne);
        printf("Décalez vous de colonne avec q pour la gauche et d pour la droite\n");
        scanf("%c",&rep);

        
    
    }
    return colonne-1;
}
//-------------------------------------------------------------------//
//------------------Fonction qui trouve la ligne où joueur-----------//  


int trouverLigne(t_grille g,int colonne){
    int j=-1;
    
    while((j<NBLIG-1)&&(g[j+1][colonne]==VIDE)){               //vérifie à quelle case on placera le pion (si la colonne à une case libre au minimum )
         
        j=j+1;
    }
    if(j==-1){
        printf("erreur ligne complète il faut jouer dans une autre colonne");
        printf("\n");
        sleep(1);
    }
    return j;
}
//--------------------------------------------------------------------//
//--------Fonction qui vérifie si la grille est pleine---------------//
bool grillepleine(t_grille g){
    int j,i;
    bool plein;
    plein=true;
    i=0;
    j=0;
    while((i<NBLIG)&&(plein==true)){
        j=0;
        while((j<=NBLIG)&&(plein==true)){
            
            if(g[i][j]==VIDE){
                plein=false;
            }
            else{
                j=j+1;
            }
            
        }
        i=i+1;
       
    }
    
    return plein;
}
//----------------------------------------------------------------------//
//---------------Fonction qui vérifie si le joueur a gagné--------------//
void jouer(t_grille g ,char PION ,int *colonne,int *ligne){
         do{
            *colonne=choisirColonne(g,PION,COLONNE_DEBUT);
            *ligne=trouverLigne(g,*colonne);
            
         } 
         while((*ligne==-1));
         g[*ligne][*colonne]=PION;
    }

bool estVainqueur(t_grille g ,int col ,int lig){
    bool winner;
    char PION;
    PION=g[lig][col];
    
    int i,j,compteur;
    i=lig;
    j=col;
    compteur=1;
    //verification de la ligne droite
    while((g[i][j+1]==PION)&&(j<NBLIG)&&(winner==false)){
        
            j=j+1;
            compteur=compteur+1;
            if(compteur==4){
                winner=true;
            }
    }
    i=lig;
    j=col;
    
   
    //verification de la lignee gauche
    while((g[i][j-1]==PION)&&(j>0)&&(winner==false)){
        j=j-1;
        
        compteur=compteur+1;
        if(compteur==4){
            winner=true;
        }
    }
    i=lig;
    j=col;
    compteur=1;
    
    //verification de la ligne du bas 
    while((g[i+1][j]==PION)&&(i<NBLIG)&&(winner==false)){
        i=i+1;
        compteur=compteur+1;
        if(compteur==4){
            winner=true;
        }
    }
    i=lig;
    j=col;
    compteur=1;
    //verification de la diagonale du bas droite
    while((g[i+1][j+1]==PION)&&(i<NBLIG-1)&&(j<NBLIG)&&(winner==false)){
        i=i+1;
        j=j+1;
        compteur=compteur+1;
        if(compteur==4){
            winner=true;
        }
    }
    i=lig;
    j=col;
    //diagonale du haut à gauche
    while((g[i-1][j-1]==PION)&&(i>0)&&(j>0)&&(winner==false)){
        i=i-1;
        j=j-1;
        compteur=compteur+1;
        if(compteur==4){
            winner=true;
        }
    }
    i=lig;
    j=col;
    compteur=1;
    //diagonale du bas gauche
    while((g[i+1][j-1]==PION)&&(i<NBLIG-1)&&(j>0)&&(winner==false)){
        j=j-1;
        i=i+1;
        compteur=compteur+1;
        if(compteur==4){
            winner=true;
        }
    }
    i=lig;
    j=col;
    //diagonale du haut à droite
    while((g[i-1][j+1]==PION)&&(i>0)&&(j<NBLIG)&&(winner==false)){
        i=i-1;
        j=j+1;
        compteur=compteur+1;
        if(compteur==4){
            winner=true;
        }
    }
    return winner;
}
//---------------------------------------------------------//
//-----------------Procédure qui affiche le résultat de fin de partie-----//
void finDePartie(char PION){
    if(PION==PION_A){
        printf("Le vainqueur de la partie est %c (joueur 1) ",PION);
    }
    else if(PION==PION_B){
        printf("le vainqueur de la partie est %c (joueur 2) ",PION);
    }
    else{
        printf("il n'y a pas de vainqueurs");
    }
}

//---------------------------------------------------------------------//