#include <string.h>
#include "../include/io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne, int aging){
	int i;
    for (i=0; i<c; ++i)
            if (ligne[i] == 0 ) printf ("|   ");
            else if (ligne[i] == -1) printf ("| X ");
            else printf ("| %d ", aging ? ligne[i] : 0);
	printf("|\n");
	return;
}

void affiche_grille (grille g, int timer, int cycle, int aging){
	int i, l=g.nbl, c=g.nbc;
	
    // affichage du timer :
    printf("%d | ", timer);
    
    // affichage du statut du mode cycle
    if (cycle) {
        printf(" Cycle : ON | ");
    } else {
        printf(" Cycle : OFF | ");
    }
     // affichage du statut du mode vieillisement
    if (aging) {
        printf(" Aging : ON | ");
    } else {
        printf(" Aging : OFF | ");
    }
    
    printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], aging);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5);
}

void debut_jeu(grille *g, grille *gc){
    // déclare les variables
    int timer = 1;
    int cycle = 1;
    int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;
    int aging = 1;
    
    int jump = 0;
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{   // touche "entree" pour évoluer
                if (jump) {
                    jump = 0;
                 } else {
                    evolue(g,gc, &timer, compte_voisins_vivants, aging);
                    efface_grille(*g);
                    affiche_grille(*g, timer, cycle, aging);
                 }
				break;
			}
            case 'n' :
            {   // touche "n" pour entrer le nom d'une nouvelle grille
                
                // libère les anciennes grilles
                libere_grille(g);
                libere_grille(gc);
                
                // prépare le chemin pour l'utilisateur
                char path[20] = "grilles/grille";
                char nb[1];
                printf("Numero de la nouvelle grille a charger : ");
                scanf("%s", nb);
                strcat( path, nb);
                strcat( path, ".txt");
                
                // chargement de la nouvelle grille
                timer = 1;
                init_grille_from_file(path, g);
                alloue_grille((*g).nbl, (*g).nbc, gc);
                affiche_grille(*g, timer, cycle, aging);
                jump = 1;
                break;
            }
            case 'c' :
            {   // touche "c" pour activer/désactiver le mode cyclique
                if (cycle){
                    cycle = 0;
                    compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
                } else{
                    cycle = 1;
                    compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
                }
                break;
            }
            case 'v' :
            {   // touche "v" pour activer/désactiver le vieillisement
                aging = !aging;
                break;
            }
                
			default : 
			{   // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
