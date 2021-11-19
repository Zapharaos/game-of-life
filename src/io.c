#include "io.h"

#include <string.h>

#if CAIRO

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <cairo.h>
#include <cairo-xlib.h>

#define X 100
#define Y 80
#define WIDTH 450
#define BORDER 2

extern cairo_surface_t *sfc;
XClassHint *classHint;

extern cairo_surface_t *cairo_create_x11_surface(int x, int y) {
    Display *dpy;
    Window win;
    Window rootwin;
    int scr;
    
    if ((dpy = XOpenDisplay(NULL)) == NULL) {
        fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
    }
    
    scr = DefaultScreen(dpy);
    rootwin = RootWindow(dpy, scr);

    win = XCreateSimpleWindow(dpy, rootwin, 1, 1, x, y, 0, 0, 0);

    XStoreName(dpy, win, "Jeu de la vie - Niveau 5");
    
    XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
    XMapWindow(dpy, win);

    sfc = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, scr), x, y);
    cairo_xlib_surface_set_size(sfc, x, y);

    return sfc;
}

extern void cairo_close_x11_surface() {
    Display *dpy = cairo_xlib_surface_get_display(sfc);
    cairo_surface_destroy(sfc);
    XCloseDisplay(dpy);
}

void affiche_trait (int c, int height, float line){
    cairo_t *cr;
    cr = cairo_create(sfc);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, BORDER);

    cairo_move_to(cr, X, Y + (height * line));

    int i;
    for (i = 0; i < c; ++i){
        cairo_line_to(cr, X + WIDTH, Y + (height * line));
        cairo_move_to(cr, X, Y + (height * line));
    }
    
    cairo_stroke(cr);
    cairo_destroy(cr);
}

void affiche_ligne (int c, int* ligne, int aging, int height, float line){
    int i;
    char buffer[255];
    float column = (float) WIDTH / (float) c;

    cairo_t *cr, *crcells;
    cr = cairo_create(sfc);
    crcells = cairo_create(sfc);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_source_rgb(crcells, 0, 0, 0);
    cairo_set_line_width(cr, BORDER);

    cairo_move_to(cr, X, Y + (height * line));

    for (i=0; i<c; ++i){

        if (ligne[i] == 0){
            cairo_line_to(cr, X + i * column, Y + (height * line) + line);
            cairo_move_to(cr, X + ((i+1) * column), Y + (height * line));
            cairo_line_to(cr, X + ((i+1) * column), Y + (height * line) + line);
        } else if (ligne[i] == -1){
            cairo_line_to(cr, X + i * column, Y + (height * line) + line);
            cairo_line_to(cr, X + ((i+1) * column), Y + (height * line));
            cairo_line_to(cr, X + ((i+1) * column), Y + (height * line) + line);
            
            cairo_line_to(cr, X + i * column, Y + (height * line) + line);
            cairo_move_to(cr, X + ((i) * column), Y + (height * line));
            cairo_line_to(cr, X + ((i+1) * column), Y + (height * line) + line);
            cairo_line_to(cr, X + ((i+1) * column), Y + (height * line));
        } else{
            cairo_line_to(cr, X + i * column, Y + (height * line) + line);
            cairo_move_to(cr, X + ((i-1) * column), Y + (height * line));
            cairo_rectangle(crcells, X + i * column, Y + (height * line), column + 1, line);
            cairo_fill(crcells);

        if (aging){
            sprintf(buffer, "%d", ligne[i]);
            cairo_move_to(cr, X + ((i) * column + 4) + column/3, Y + (height * line) + line*2/3);
            cairo_set_source_rgb (cr, 255, 255, 255);
            cairo_set_font_size(cr, 15);
            cairo_show_text(cr, buffer);
            cairo_set_source_rgb(cr, 0, 0, 0);
            }
               
            cairo_move_to(cr, X + ((i+1) * column), Y + (height * line));
            }
    }
    
    cairo_fill(crcells);
    cairo_stroke(cr);
    cairo_destroy(cr);
    cairo_destroy(crcells);
    
    return;
}

void affiche_grille (grille g, int timer, int cycle, int aging, int swing, int count){
    int i, l=g.nbl, c=g.nbc;

    char strTimer[255], strCycle[255], strAging[255], strSwing[255];
    
    sprintf(strTimer, "Timer : %d", timer);
    sprintf(strCycle, cycle ? " Cycle : ON" : "Cycle : OFF");
    sprintf(strAging, aging ? " Aging : ON" : "Aging : OFF");

    cairo_t *cr;
    cr = cairo_create(sfc);
    
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_font_size(cr, 18);
    
    cairo_move_to(cr, 160, 40);
    cairo_show_text(cr, strTimer);
    cairo_move_to(cr, 270, 40);
    cairo_show_text(cr, strCycle);
    cairo_move_to(cr, 390, 40);
    cairo_show_text(cr, strAging);
    
    cairo_move_to(cr, 160, 65);
    cairo_show_text(cr, "Oscillant : ");
    cairo_move_to(cr, 260, 65);
    if (swing>=1){
        cairo_set_source_rgb(cr, 0, 255, 0);
        cairo_show_text(cr, "YES");
    } else {
        cairo_set_source_rgb(cr, 255, 0, 0);
        cairo_show_text(cr, "NO");
    }
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    
    if (count >=1 ) {
        sprintf(strSwing, "Periode : %d TO %d", swing, count);
        cairo_move_to(cr, 340, 65);
        cairo_show_text(cr, strSwing);
    }

    cairo_move_to(cr, 140, 580);
    cairo_show_text(cr, "Left click = Evolve");
    cairo_move_to(cr, 360, 580);
    cairo_show_text(cr, "Right click = Exit");
    
    cairo_move_to(cr, 140, 610);
    cairo_show_text(cr, "n = Switch file");
    cairo_move_to(cr, 360, 610);
    cairo_show_text(cr, "c = Switch cycle");
    
    cairo_move_to(cr, 140, 640);
    cairo_show_text(cr, "v = Switch aging");
    cairo_move_to(cr, 360, 640);
    cairo_show_text(cr, "o = Test oscillant");

    cairo_destroy(cr);

    int height = 0;
    float line = (float) WIDTH/ (float) g.nbl;
    affiche_trait(c, height, line);
    for (i=0; i<l; ++i){
        affiche_ligne(c, g.cellules[i], aging, height, line);
        affiche_trait(c, ++height, line);
    }
    return;
}

void efface_grille(){
    cairo_t *cr;
    cr = cairo_create(sfc);
    cairo_set_source_rgb (cr, 255, 255, 255);
    cairo_paint(cr);
    cairo_destroy(cr);
}

void debut_jeu(grille *g, grille *gc){
    int timer = 1;
    int cycle = 1;
    int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;
    int aging = 1;
    int swing = 0;
    int count = 0;
    
    XEvent e;
    efface_grille();
    affiche_grille(*g, timer, cycle, aging, swing, count);
    int refresh = 3;
    
    while(1){
        XNextEvent(cairo_xlib_surface_get_display(sfc), &e);
        
        if (refresh == 3 ) {
            refresh--;
        } else if (e.type==Expose && e.xexpose.count<1) {
            affiche_grille(*g, timer, cycle, aging, swing, count);
        }
        else if (e.type == KeyPress){
            if (e.xkey.keycode == XKeysymToKeycode (cairo_xlib_surface_get_display(sfc), XK_Return)) {
                // Touche entrée
                refresh = 2;
            }
            else if (e.xkey.keycode == XKeysymToKeycode (cairo_xlib_surface_get_display(sfc),'q')) {
                // Touche q
                printf("=== Fin du programme ===\n");
                return;
            }
            else if (e.xkey.keycode == XKeysymToKeycode (cairo_xlib_surface_get_display(sfc),'n')){
                // Touche n

                libere_grille(g);
                libere_grille(gc);
                
                char path[20] = "grilles/grille";
                char nb[1];

                printf("Numero: ");
                scanf("%s", nb);
                
                strcat(path, nb);
                strcat(path, ".txt");
                
                init_grille_from_file(path, g);
                alloue_grille(g->nbl, g->nbc, gc);
                
                timer = 1;
                cycle = 1;
                compte_voisins_vivants = compte_voisins_vivants_cyclique;
                aging = 1;
                swing = 0;
                count = 0;
                
                refresh = 1;
            }
            else {
                if (e.xkey.keycode == XKeysymToKeycode (cairo_xlib_surface_get_display(sfc),'c')){
                    // Touche c
                    if (cycle == 0){
                        cycle = 1;
                        compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
                    } else{
                        cycle = 0;
                        compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
                    }
                }
                else if (e.xkey.keycode == XKeysymToKeycode (cairo_xlib_surface_get_display(sfc),'v')){
                    // Touche v
                    aging = !aging;
                }
                else if (e.xkey.keycode == XKeysymToKeycode (cairo_xlib_surface_get_display(sfc),'o')){
                    // Touche o
                
                    grille t1, t2;
                    alloue_grille(g->nbl, g->nbc, &t1);
                    copie_grille(*g, t1);
                    alloue_grille(g->nbl, g->nbc, &t2);
                    
                    int resultat, j, i = 0;
                    
                    while (i < 100){
                        j = i;
                        copie_grille(t1, t2);
                        if (!grille_vide(t1)) {
                            while (j < 100){
                                swing = 0; count = 0;
                                resultat = egale_grille(t1, t2);
                                if (i==j) {
                                    evolue(&t2,gc,&j,compte_voisins_vivants,aging);
                                } else if (resultat){
                                    swing = timer + i;
                                    count = timer + j;
                                    i = 100;
                                    j = 100;
                                } else{
                                    evolue(&t2,gc,&j,compte_voisins_vivants,aging);
                                }
                            }
                        }
                        evolue(&t1,gc,&i,compte_voisins_vivants,aging);
                    }
                    
                    libere_grille(&t1);
                    libere_grille(&t2);
                }
                refresh = 1;
            }
        }
        else if (e.type == ButtonPress){
             if (e.xbutton.button == 1){
                 // Clic gauche (fait évoluer le jeu)
                     refresh = 2;
             }
             else if (e.xbutton.button == 3){
                 // Clic droit (quitte le jeu)
                 printf("=== Fin du programme ===\n");
                 return;
             }
        }
        else {
            efface_grille();
            affiche_grille(*g, timer, cycle, aging, swing, count);
        }
        
        if (refresh == 2) {
            evolue(g,gc,&timer,compte_voisins_vivants,aging);
            refresh--;
        }
        
        if (refresh == 1) {
            efface_grille();
            affiche_grille(*g, timer, cycle, aging, swing, count);
            refresh = 0;
        }
    }
    return;
}

#else

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

void affiche_grille (grille g, int timer, int cycle, int aging, int swing, int count){
    int i, l=g.nbl, c=g.nbc;
    
    // affichage du timer :
    printf("Timer = %d | ", timer);
    // affichage du statut du mode cycle
    if (cycle) printf("Cycle : ON | "); else printf("Cycle : OFF | ");
     // affichage du statut du mode vieillisement
    if (aging) printf("Aging : ON | "); else printf("Aging : OFF | ");
    // affichage du statut du mode oscillant
    printf("\nOscillant : ");
    // si oscillant : affichaque de la période
    if (swing >=1 ) printf("YES |"); else printf("NO  |");
    if (count >=1 ) printf(" Periode : %d TO %d             ", swing, count); else printf("                           ");
    
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
    printf("\n\e[%dA",g.nbl*2 + 6);
}

void debut_jeu(grille *g, grille *gc){
    // déclare les variables
    int timer = 1;
    int cycle = 1;
    int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;
    int aging = 1;
    int swing = 0;
    int count = 0;
    
    char c = getchar();
    while (c != 'q') // touche 'q' pour quitter
    {
        switch (c) {
            case '\n' :
            {   // touche "entree" pour évoluer
                evolue(g,gc, &timer, compte_voisins_vivants, aging);
                efface_grille(*g);
                affiche_grille(*g, timer, cycle, aging, swing, count);
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
                printf("Numero a charger : ");
                scanf("%s", nb);
                strcat( path, nb);
                strcat( path, ".txt");
                
                printf ("\n\n");
                printf("\n\e[%dA", 2);
                
                // chargement de la nouvelle grille
                init_grille_from_file(path, g);
                alloue_grille(g->nbl, g->nbc, gc);
                
                timer = 0;
                cycle = 1;
                compte_voisins_vivants = compte_voisins_vivants_cyclique;
                aging = 1;
                swing = 0;
                count = 0;
                
                affiche_grille(*g, 0, 1, 1, 0, 0);
                
                printf("\n");
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
            case 'o' :
            {   // Touche "o" pour tester l'oscillation

                grille t1, t2;
                alloue_grille(g->nbl, g->nbc, &t1);
                copie_grille(*g, t1);
                alloue_grille(g->nbl, g->nbc, &t2);
                
                int resultat, j, i = 0;
                
                while (i < 100){
                    j = i;
                    copie_grille(t1, t2);
                    if (!grille_vide(t1)) {
                        while (j < 100){
                            swing = 0; count = 0;
                            resultat = egale_grille(t1, t2);
                            if (i==j) {
                                evolue(&t2,gc,&j,compte_voisins_vivants,aging);
                            } else if (resultat){
                                swing = timer + i;
                                count = timer + j;
                                i = 100;
                                j = 100;
                            } else{
                                evolue(&t2,gc,&j,compte_voisins_vivants,aging);
                            }
                        }
                    }
                    evolue(&t1,gc,&i,compte_voisins_vivants,aging);
                }
                
                printf("\n\e[%dA", 1);
                libere_grille(&t1);
                libere_grille(&t2);
                
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

#endif
