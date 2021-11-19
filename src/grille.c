#include "grille.h"

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0, viable=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
    
    fscanf(pfile, "%d", & viable);
    for (n=0; n< viable; ++n){
        fscanf(pfile, "%d", & i);
        fscanf(pfile, "%d", & j);
        set_non_viable(i,j,*g);
    }
	
	fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

void alloue_grille (int l, int c, grille* g){
    g->nbl = l;
    g->nbc = c;
    
    g->cellules = (int**) malloc(l * sizeof(int*));
    
    for (int i=0; i < l; i++) {
        g->cellules[i] = (int*) malloc(c * sizeof(int));
        for (int j=0; j < c; j++) {
            set_morte( i, j, *g);
        }
    }
}

void libere_grille (grille* g){
    int l = g->nbl;
    
    for (int i=0; i < l; i++){
        free (g->cellules[i]);
    }
    free(g->cellules);
}

// si les deux grilles sont les mêmes, return 1, else 0
int egale_grille(grille g, grille g_bis){
    int i, j, swing = 0;
    for (i = 0; i < g.nbl; i++) {
        for (j = 0; j < g.nbc; j++) {
            if (g.cellules[i][j] == g_bis.cellules[i][j]) {
                swing = 1;
            }
            else {
                swing = 0;
                return swing;
            }
        }
    }
    return swing;
}

// si la grille est vide, return 1, else 0
int grille_vide(grille g) {
    int i, j, vide = 1 ;
    for (i = 0; i < g.nbl; i++) {
        for (j = 0; j < g.nbc; j++) {
            if ((g.cellules[i][j]) > 0) {
                vide = 0;
                return vide;
            }
        }
    }
    return vide;
}

