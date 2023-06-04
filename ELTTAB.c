#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include "TABPRIM.h"

element_tab tabCreer (void)
{
    element_tab taab;
    taab = (element_tab) malloc(7*18*sizeof(TAB));
    if (!taab)
    {
        printf("\n pas de memoire!");
    }
    else
    {
        for (int i=1; i<=7; i++)
        {
            for(int j=1; j<=18; j++)
            {
                taab->T[i][j]=listeCreer();
            }
        }
        taab->T[1][1]->lg++;
        taab->T[1][18]->lg++;
        taab->T[2][1]->lg++;
        taab->T[2][2]->lg++;
        taab->T[2][13]->lg++;
        taab->T[2][14]->lg++;
        taab->T[2][15]->lg++;
        taab->T[2][16]->lg++;
        taab->T[2][17]->lg++;
        taab->T[2][18]->lg++;
        taab->T[3][1]->lg++;
        taab->T[3][2]->lg++;
        taab->T[3][13]->lg++;
        taab->T[3][14]->lg++;
        taab->T[3][15]->lg++;
        taab->T[3][16]->lg++;
        taab->T[3][17]->lg++;
        taab->T[3][18]->lg++;
        for (int i=4; i<=7; i++)
        {
            for (int j=1; j<=18; j++)
            {
                taab->T[i][j]->lg++;
            }
        }
    }
    return taab;
}



void tabDetruire(element_tab tab)
{
    int i,j;
    for(i=1; i<7; i++)
    {
        for(j=1; j<18; j++)
        {
            listeDetruire(tab->T[i][j]);
        }
    }
    free(tab);
}

void tabAfficher(element_tab e)
{
    NOEUD n;
    printf("\n Num atomique           Symbole          Masse atomique        Etat physiologique\n");
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=18; j++)
        {
            n=e->T[i][j]->tete;
            if (i==6&&j==3)
                printf("\n *.les Lanthanides(les 15 elements suivants):  \n\n");
            if (i==6&&j==4)
                printf("\n____________________________________________________________________________________  \n");
            if (i==7&&j==3)
                printf("\n *.les Actinides(les 15 elements suivants): \n\n");
            if (i==7&&j==4)
                printf("\n____________________________________________________________________________________ \n");

            while(n!=NULL)
            {
                elementAfficher(n->info);
                n=n->suivant;
            }
        }
    }
}

