#ifndef LSTPRIM_H_INCLUDED
#define LSTPRIM_H_INCLUDED
#include "LSTSDD.h"

liste_atm listeCreer(void);
void listeDetruire(liste_atm );
int inserer(liste_atm, element_atm, int );
int supprimer (liste_atm,int );
element_atm recuperer(liste_atm, int );
liste_atm listeCopier(liste_atm );
int listeComparer(liste_atm,liste_atm );
void listeAfficher(liste_atm );
int estVide(liste_atm );
int estSaturee(liste_atm );
int listeTaille(liste_atm );
NOEUD noeudCreer(element_atm );
void noeudDetruire(NOEUD );
int listeExiste(liste_atm, element_atm);

#endif // LSTPRIM_H_INCLUDED
