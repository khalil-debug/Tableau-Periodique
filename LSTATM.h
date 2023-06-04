#ifndef LSTATM_H_INCLUDED
#define LSTATM_H_INCLUDED
#define longMax 150

#include "ELTPRIM.h"

typedef struct structNoeud
{
    element_atm info;
    struct structNoeud * suivant;
} structNoeud, * NOEUD;

typedef struct
{
    NOEUD tete;
    int lg;
} laStruct,*liste_atm;

#endif // LSTATM_H_INCLUDED
