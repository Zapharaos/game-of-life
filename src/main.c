#include <string.h>
#include <stdio.h>

#include "grille.h"
#include "jeu.h"
#include "io.h"


#if CAIRO
cairo_surface_t *sfc;
#endif


int main (int argc, char ** argv) {

	if (argc != 2 )
	{
		printf("usage : ./bin/main <numero>");
		return 1;
	}

    /* Simplification des paramètres : juste un numéro */
    char path[20] = "grilles/grille";
    strcat(path, argv[1]);
    strcat( path, ".txt");
    
    /* Conversion en un entier */
    int check = atoi(argv[1]);
    
    /* Si le fichier existe : */
    if ( check > 0 && check < 9) {
        
        /* Création des variables */
        grille g, gc;
        init_grille_from_file(path,&g);
        alloue_grille (g.nbl, g.nbc, &gc);
        
        /* Création de la fenetre en mode graphique */
        #if CAIRO
        
            sfc = cairo_create_x11_surface(670, 750);
            debut_jeu(&g, &gc);
            cairo_close_x11_surface();
        
        /* Création de la fenetre dans le terminal */
        #else
        
            affiche_grille(g, 1, 1, 1, 0, 0);
            debut_jeu(&g, &gc);
        
        #endif
        
        /* Libération des grilles à la fin du jeu */
        libere_grille(&g);
        libere_grille(&gc);
        
    /* Si le fichier n'existe pas : */
    } else {
        printf("Ce fichier n'existe pas !\n");
    }
    
	return 0;
}
