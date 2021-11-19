#include <string.h>
#include <stdio.h>

#include "../include/grille.h"
#include "../include/io.h"
#include "../include/jeu.h"

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
    char path[20] = "grilles/grille";
    strcat(path, argv[1]);
    strcat( path, ".txt");
    init_grille_from_file(path,&g);
	alloue_grille (g.nbl, g.nbc, &gc);
    
	affiche_grille(g, 1, 1, 1);
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
