#include <stdlib.h>
#include <stdio.h>
#include "LSTPRIM.H"



NOEUD noeudCreer (element_atm e)
{
    NOEUD n;
    n=(NOEUD)malloc(sizeof(structNoeud));
    if (!n)
        printf("\n plus d'espace");
    else
    {
        elementAffecter(&n->info,e);
        n->suivant = NULL ;
    }
    return n ;
}

void noeudDetruire(NOEUD n)
{
    elementDetruire(n->info);
    free(n);
}

liste_atm listeCreer(void)
{
    liste_atm L;
    L=(liste_atm)malloc(sizeof(laStruct));
    if (!L)
        printf("\n plus de memoire");
    else
    {
        L->lg=0;
        L->tete=NULL;
    }
    return L;

}

int estVide(liste_atm L)
{
    return(L->lg==0);
}

int estSaturee(liste_atm L)
{
    NOEUD temp ;
    int sature=1;
    temp=(NOEUD) malloc(sizeof(structNoeud));
    if (temp != NULL )
    {
        sature=0;
        free(temp);
    }
    return sature ;
}

int listeTaille(liste_atm L)
{
    return (L->lg);
}

void listeDetruire(liste_atm L)
{
    int i ;
    NOEUD p,q;
    q=L->tete;
    for (i=1; i<= L->lg; i++)
    {
        p=q;
        q=q->suivant;
        noeudDetruire(p);
    }
    free(L);
}

element_atm recuperer(liste_atm L, int pos)
{
    element_atm elt=elementCreer();
    int i=1;
    NOEUD p;
    if (estVide(L))
        printf ("\n Liste vide");
    else
    {
        if ((pos < 1) || (pos > L->lg  ))
            printf ("\n Position invalide");

        else
        {
            p=L->tete;
            for(i=1; i<L->lg; i++)
            {
                p=p->suivant ;
                elementAffecter(&elt,p->info);
            }
        }
    }
    return(elt);
}

int listeComparer(liste_atm L1,liste_atm L2)
{
    int test=1;
    int i=1;

    if (listeTaille(L1)!= listeTaille(L2))
        test=0;
    while (i<= listeTaille(L1)&&(test))
    {
        if (elementComparer(recuperer(L1,i),recuperer(L2,i))!=0)
            test=0;
        i++;
    }
    return test;
}

int inserer(liste_atm L,element_atm e,int pos)
{
    int succee=1;
    int i;
    NOEUD n, p, q;
    if (estSaturee(L))
    {
        printf ("\n Liste saturée");
        succee=0;
    }

    else
    {
        if ((pos < 1) || (pos > L->lg  ))
        {
            printf ("\n Position invalide");
            succee=0;
        }
        else
        {
            n=noeudCreer(e);
            if(pos==1)
            {
                n->suivant=L->tete;
                L->tete= n;
            }
            else
            {
                q= L->tete;
                for (i=1; i<pos; i++)
                {
                    p = q;
                    q = q->suivant;
                }
                p->suivant=n;
                n->suivant=q;
            }
            (L->lg) ++;

        }
    }
    return succee;
}

liste_atm listecopier(liste_atm L)
{
    liste_atm LR = listeCreer();
    int i;
    element_atm elt;
    for(i = 1; i <= L->lg; i++)
    {
        elt=elementCreer();
        elementCopier(&elt, recuperer(L,i));
        inserer(LR,elt, i);
    }
    return LR;
}

void listeAfficher(liste_atm L)
{
    NOEUD p;
    p=L->tete;
    while (p!=NULL)
    {
        elementAfficher(p->info);
        p=p->suivant ;
    }
}



int listeExiste(liste_atm l, element_atm e)
{
    NOEUD p;
    int trouve=1;
    p=l->tete;
    while (p!=NULL&&trouve!=0)
    {
        if (elementComparer(p->info,e)==1)
            trouve=0;
        p=p->suivant ;
    }
    return trouve;
}



int supprimer (liste_atm L,int pos)
{
    int suc=1;
    int i;
    NOEUD p, q;
    if (estVide(L))
    {
        printf ("\n Liste vide");
        suc=0;
    }

    else
    {
        if ((pos < 1) || (pos > L->lg  ))
        {
            printf ("\n Position invalide");
            suc=0;
        }
        else
        {
            q=L->tete;
            if (pos==1)
                L->tete=L->tete->suivant ;
            else
            {
                for (i=1; i<pos; i++)
                {
                    p = q;
                    q = q->suivant;
                }
                p->suivant=q->suivant ;
            }
            noeudDetruire(q);
            (L->lg)--;
        }
    }
    return suc;
}

