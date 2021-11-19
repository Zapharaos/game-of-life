/*!
 * \file grille.h
 * \brief Fonctions liée aux grilles
 * \version 5.0
 * \date 31 mars 2020
*/
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*!
 * \struct grille
 * \brief Création d'une grille de "nbl" lignes et "nbc" colonnes
*/
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/*!
 * \brief Alloue une grille "g" de taille "L" * "C", et initialise toutes les cellules à "morte"
 * \param [in] l  Nombre de lignes à allouer dans la grille
 * \param [in] c Nombre de colonnes à allouer dans la grille
 * \param [out] g Pointeur sur la grille à allouer
*/
void alloue_grille (int l, int c, grille* g);

/*!
 * \brief Libère une grille
 * \param [in] g Pointeur sur la grille à libérer
*/
void libere_grille (grille* g);

/*!
 * \brief Alloue et initalise la grille "g" à partir d'un fichier "filename"
 * \param [in] filename Nom du fichier où se trouve la grille à initialiser
 * \param [out] g Grille à initialiser
*/
void init_grille_from_file (char * filename, grille* g);

/*!
 * \brief Rend la cellule ( i , j ) de la grille g vivante (=1)
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [out] g Grille
 * \return g [ i ][ j ] = 1
*/
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/*!
 * \brief Rend la cellule  ( i , j ) de la grille g morte (=0)
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [out] g Grille
 * \return g [ i ][ j ] = 0
*/
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/*!
 * \brief Rend la cellule (i,j) de la grille g non viable (= -1)
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [out] g Grille
 * \return g [ i ][ j ] = -1
*/
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

/*!
 * \brief Teste si la cellule ( i , j ) de la grille g est vivante
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [out] g Grille
 * \return 1 si vivante, 0 sinon
*/
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

/*!
 * \brief Teste si la cellule ( i , j ) de la grille g est non viable
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [out] g Grille
 * \return 1 si non viable, 0 sinon
*/
static inline int est_non_viable(int i, int j, grille g){return g.cellules[i][j] == -1;}

/*!
 * \brief Recopie gs dans gd
 * \param [in] gs Grille à copier
 * \param [in] gd Grille contenant la copie
*/
void copie_grille (grille gs, grille gd);

/*!
 * \brief Test si les deux grilles sont les mêmes
 * \param [in] g Grille 1 à comparer
 * \param [in] g_bis Grille 2 à comparer
 * \return 1 si elle sont égales, sinon 0
 */
int egale_grille(grille g, grille g_bis);

/*!
 * \brief Test si la grille est vide
 * \param [in] g Grille à tester
 * \return 1 si elle est vide, sinon 0
*/
int grille_vide(grille g);

#endif
