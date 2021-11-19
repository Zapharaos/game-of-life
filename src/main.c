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

	grille g, gc;
    char path[20] = "grilles/grille";
    strcat(path, argv[1]);
    strcat( path, ".txt");
    init_grille_from_file(path,&g);
	alloue_grille (g.nbl, g.nbc, &gc);
    
    #if CAIRO
        sfc = cairo_create_x11_surface(670, 700);
        debut_jeu(&g, &gc);
        cairo_close_x11_surface();
    
    #else
        affiche_grille(g, 1, 1, 1, 0, 0);
        debut_jeu(&g, &gc);
    
    #endif

	libere_grille(&g);
	libere_grille(&gc);
    
	return 0;
}
