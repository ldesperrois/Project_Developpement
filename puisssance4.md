

### Les entêtes de fonctions et procédure(document à ouvrir avec Visual Studio en .md)

----
- fonction Initgrille();
- procedure AfficheGrille(entE/sortE  grille : t_grille );
- prcédure victoire(entF/sortF V : booleen,entF j :entier);
- fonction grilleremplie(entF/sortF egalite : booleen,entF grille : t_grille);
- procedure placementjoueur(entF/sortF grille : t_grille , entF joueur1 : entier);
- fonction changement(entF/sortF joueur : entier);

----


### Les entêtes des fonctions ou procèdures interne aux fonctions principales
- fonction verif_victoire(entF joueur : entier,entF grille : t_grille) délivre un booléen ;                              
- fonction possibilite_de_jouer(entF grille) délivre un booleen ;         
- fonction verif_saisie(entF saisie :entier) délivre un booleen;                        
- 

- - - -



### Décalaration d'un type tableau 


type t_grille : tableau [1..7][1..6] d'entier;             


-----
### le programme principal


debut

    joueur: entier;                                        /initialisation du booléen pour la victoire et de la variable du joueur
    Victoire : booleen ; 
    grille : t_grille;                                      / la grille du jeu est de type t_grille
    joueur:=1;                                             / numéro du joueur 
    grille=Initgrille();
    Affichegrille(entE/sortE grille);
    Victoire:=0; 
    tant que(Victoire==0) faire
        placementjoueur(entE/sortE grille, entE joueur); 
        si (victoire(entE/sortE Victoire,entE joueur)) == 1 alors
            Victoire:=1;
            AfficheResultat(ent joueur);
        sinon
            si (grilleremplie==1) alors
                Affichegrille(entE/sortE Grille);
                ecrireEcran("il y a égalité ");
                Victoire:=1;
            sinon
                Affichegrille(entE/sortE grille); 
                joueur=changement(entE/sortE joueur);
            fin si
        fin si
    fin faire

fin

|-------explication des différentes procédures/fonctions -----------------|


`fonction InitGrille() délivre un t_grille;`

/fonction  qui créer une grille et la retourne 

|------------------------------------------------|

`procedure AfficheGrille(sortF/entF grille:t_grille)`

/procédure qui prend en entré une grille et affiche avec chaque changement  la grille de jeu lorsque des modification ont été faites par d'autre fonctions sur celle-ci

|------------------------------------------------|

`procedure placementjoueur(entF/sortF grille:t_grille ,entF joueur:entier)`

/procédure qui va positionner le joueur sur la grille en effectuant des modifications sur celle-ci et va débloquer les cases alentour qui permettront de joueur     
|------------------------------------------------|

`fonction verif_victoire(entF joueur : entier , entF grille :t_grille) délivre un booléen`

/ fonction qui en fonction du joueur rentré va vérifie si celui- ci  en parcourant toute la grille a gagné en retournant vraix ou faux avec un booléen .

|------------------------------------------------|

`fonction grilleremplie(  entF grille : t_grille) délivre un booléen`

/ fonction qui vérifie que la grille est remplie en retournant vraix ou faux.

|-------------------------------------------------|

`fonction Changement(entF joueur : entier) délivre un entier;`

/elle va switcher de joueur en redéfinissant soit le joueur par 1 ou 2.

|-------------------------------------------------|

`procedure Victoire(entF/sortF V :booleen , entF j :entier);`

/ procédure qui donne la victoire à un  des deux joueurs si l'un des deux a gagné en définissant un boléen par vraix ou faux.   

|------------------------------------------------|

`fonction verif_saisie(entF saisie:entier) délivre un booléen;`

/vérifie que la saisie du placement d'un pion est correcte en retournant vraix ou faux avec un booléen .

|------------------------------------------------|

`fonction possibilite_de_joueur(entF_grille) délivre un booléen ; `

/ fonction qui va vérifier que le joueur peut joueur à cet endroit en retournant un boléen  


