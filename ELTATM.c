#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "ELTPRIM.H"


element_atm elementCreer()
{
    element_atm e;
    e = (element_atm) malloc(sizeof(atome));
    return e;
}

element_atm elementCreation ( double d,char et,int p, char *s)
{

    element_atm e= elementCreer();
    e->masseAto=d;
    e->etatPhy=et;
    e->numAto=p;
    e->symbole=s;
    return e;

}





void elementLire(element_atm * e)
{
    printf("donnez le numero atomique de l'atome: \n");
    scanf("%d",&((*e)->numAto));
    printf("donnez le symbole de l'element: \n");
    scanf("%s",&((*e)->symbole));
    printf("donnez la masse atomique: ");
    scanf("%d",&((*e)->masseAto));
    do
    {
        printf("donnez l'etat physique (s: solide, l: liquide, g:gaz, y: synthetique): ");
        scanf("%s",&((*e)->etatPhy));
    }
    while (((*e)->etatPhy!='Y')&&((*e)->etatPhy!='G')&&((*e)->etatPhy!='L')&&((*e)->etatPhy!='S')&&((*e)->etatPhy!='s')&&((*e)->etatPhy!='l')&&((*e)->etatPhy!='g')&&((*e)->etatPhy!='y'));
}

void elementAfficher(element_atm elt)
{
    printf("%3d.      \t           %3s\t            %.3f\t         %c\t\n",elt->numAto,elt->symbole,elt->masseAto,elt->etatPhy);
}


void elementAffecter(element_atm * e1, element_atm e2)
{
    *e1 = e2  ;
}

void elementCopier(element_atm * e1, element_atm e2)
{
    strcpy((*e1)->symbole, e2->symbole);
    strcpy((*e1)->etatPhy, e2->etatPhy);
    (*e1)->numAto = e2->numAto;
    (*e1)->masseAto= e2->masseAto;
}
int elementComparer(element_atm e1, element_atm e2)
{
    if (e1->numAto == e2->numAto)
        return 1;
    else
        return 0;
}

void   elementDetruire (element_atm e)
{
    free(e);
}
