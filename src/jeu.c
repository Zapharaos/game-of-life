#include "jeu.h"

// calcul des voisins en cyclique
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

// calcul des voisins en non cyclique
int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
   int v = 0, l=g.nbl, c = g.nbc;

   v+= (i-1 >= 0 && j-1 >= 0) ? est_vivante(i-1,j-1,g) : 0;
   v+= (i-1 >= 0) ? est_vivante(i-1,j,g) : 0;
   v+= (i-1 >= 0 && j+1 < c) ? est_vivante(i-1,j+1,g) : 0;
   v+= (j-1 >= 0) ? est_vivante(i,j-1,g) : 0;
   v+= (j+1 < c) ? est_vivante(i,j+1,g) : 0;
   v+= (i+1 < l && j-1 >= 0) ? est_vivante(i+1,j-1,g) : 0;
   v+= (i+1 < l) ? est_vivante(i+1,j,g) : 0;
   v+= (i+1 < l && j+1 < c) ? est_vivante(i+1,j+1,g) : 0;

   return v;
}

// evolution de la grille
void evolue (grille *g, grille *gc, int *timer, int (*compte_voisins_vivants) (int, int, grille), int aging){
    
    (*timer)++;
	copie_grille (*g,*gc);
	int i,j,v, l = g->nbl, c = g->nbc;
    
	for (i=0; i<l; i++) {
		for (j=0; j<c; ++j) { // evolution d'une cellule viable
            if (!est_non_viable(i,j,*g)){
                v = compte_voisins_vivants (i, j, *gc);
                
                if (est_vivante(i,j,*g)) { // evolution d'une cellule vivante
                    if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
                    else if (aging) g->cellules[i][j]++;
                    else g->cellules[i][j] = 1;
                    
                    // mort d'une cellule
                    if (aging && g->cellules[i][j] > 8) set_morte(i,j,*g);
                }
                else { // evolution d'une cellule morte
                    if ( v==3 ) set_vivante(i,j,*g);
                }
            }
		}
	}
	return;
}
