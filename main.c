#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ELTPRIM.h"
#include "TABPRIM.h"
#include "LSTPRIM.h"

///////////////////////////////////////////////////////////////
double rtn(double x)//arrondissement
{
    int r=(int)x;
    return (double)r;
}
///////////////////////////////////////////////////////////////


liste_atm gaz(element_tab e)
{
    liste_atm l=listeCreer();
    NOEUD n;
    int p=1;
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=18; j++)
        {
            n=e->T[i][j]->tete;
            while(n!=NULL)
            {
                if ((n->info->etatPhy=='G')||(n->info->etatPhy=='g'))
                {
                    l->lg++;
                    inserer(l,n->info,p);
                    p++;
                }
                n=n->suivant;
            }
        }
    }
    return l;
}

liste_atm Lourds(element_tab e)
{
    liste_atm l=listeCreer();
    NOEUD n;
    int p=1;
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=18; j++)
        {
            n=e->T[i][j]->tete;
            while(n!=NULL)
            {
                if (n->info->numAto>83)
                {
                    l->lg++;
                    inserer(l,n->info,p);
                    p++;
                }
                n=n->suivant;
            }
        }
    }
    return l;
}

liste_atm radioactif(element_tab e)
{
    liste_atm l=listeCreer();
    NOEUD n;
    int p=1;
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=18; j++)
        {
            n=e->T[i][j]->tete;
            while(n!=NULL)
            {
                if ((n->info->etatPhy=='Y')||(n->info->etatPhy=='y')||(n->info->numAto>=84))
                {
                    l->lg++;
                    inserer(l,n->info,p);
                    p++;
                }
                n=n->suivant;
            }
        }
    }
    return l;
}


int Alphabet (char *ch)
{
    int i=0, trouve=1;
    while ((i<strlen(ch))&&(trouve==1))
    {
        if (((ch[i]<='z')&&(ch[i]>='a'))||((ch[i]<='Z')&&(ch[i]>='A')))
            i++;
        else
            trouve=0;
    }
    return trouve;
}

int verif(char ch)
{

    if (((ch<='z')&&(ch>='a'))||((ch<='Z')&&(ch>='A')))
        return 1;
    else
        return 0;
}

liste_atm instables (element_tab e)
{
    liste_atm l=listeCreer();
    NOEUD n;
    int p=1;
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=18; j++)
        {
            n=e->T[i][j]->tete;
            while(n!=NULL)
            {
                if (rtn(n->info->masseAto)==n->info->masseAto)
                {
                    l->lg++;
                    inserer(l,n->info,p);
                    p++;
                }
                n=n->suivant;
            }
        }
    }
    return l;
}


double Ar(element_tab e, char *s)
{
    NOEUD n;
    double m=0;
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=18; j++)
        {
            n=e->T[i][j]->tete;
            while(n!=NULL)
            {

                if (strcmp(n->info->symbole,s)==0)
                    m=n->info->masseAto;
                n=n->suivant;
            }
        }
    }
    return m;
}


element_atm recherche(element_tab e,char *s)
{
    NOEUD n;
    element_atm e1=elementCreer();
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=18; j++)
        {
            n=e->T[i][j]->tete;
            while(n!=NULL)
            {

                if (strcmp(n->info->symbole,s)==0)
                    e1=n->info;
                n=n->suivant;
            }
        }
    }
    return e1 ;
}



double m_C8H10N4O2 (element_tab e)
{
    double MM;
    MM= Ar(e,"C")*8 + Ar(e,"H")*10 + Ar(e,"N")*4 + Ar(e,"O")*2;
    return MM;
}


double n_C8H10N4O2(element_tab e)
{
    double n;
    n=10/m_C8H10N4O2(e);
    return n;
}


double M (element_tab e, char * molec)
{
    char m[100][2], ch[100][2],c,k;
    int i=0,p=0,l=0, a=0,b=0, compteur=0;
    double d,masseAtome=0;

    while (molec[i]!='\0')
    { compteur++;
        c=molec[i];
        k=molec[i+1];
        if (verif(c)==0&&verif(k)==0)
        {
            m[p][l]=c;
            l++;
            m[p][l]=k;
            p++;
            i=i+2;
            l=0;
        }
        else if (verif(c)==1&&verif(k)==0)
        {
            ch[a][b]=c;
            a++;
            i++;
            b=0;
        }
        else if (verif(c)==0&&verif(k)==1)
        {
            m[p][l]=c;
            p++;
            i++;
            l=0;
        }
        else if (verif(c)==1&&verif(k)==1)
        {
            ch[a][b]=c;
            b++;
            ch[a][b]=k;
            a++;
            i=i+2;
            b=0;
        }
    }

    for (i=0;i<=compteur;i++)
    {
        p=atof(m[i]);
        d=Ar(e,ch[i]);
        masseAtome= masseAtome+d*p;
    }
    return masseAtome;
}




element_atm noyauFils( element_atm x, element_tab e, int type_radio )
{
    NOEUD n;
    element_atm e1=elementCreer();
    switch (type_radio)
    {
    case 1:

        for(int i=1; i<=7; i++)
        {
            for(int j=1; j<=18; j++)
            {
                n=e->T[i][j]->tete;
                while(n!=NULL)
                {
                    if (n->info->numAto==x->numAto-2)
                    {
                        e1=elementCreation(rtn(x->masseAto)-4,n->info->etatPhy,x->numAto-2,n->info->symbole);
                        return e1;
                    }
                    n=n->suivant;
                }
            }
        }
        break;
    case 2:

        for(int i=1; i<=7; i++)
        {
            for(int j=1; j<=18; j++)
            {
                n=e->T[i][j]->tete;
                while(n!=NULL)
                {
                    if (n->info->numAto==x->numAto+1&&n->info->masseAto<x->masseAto)
                    {
                        e1=elementCreation(rtn(x->masseAto),n->info->etatPhy,x->numAto+1,n->info->symbole);
                        return e1;
                    }
                    n=n->suivant;
                }
            }
        }
        break;
    case 3:

        for(int i=1; i<=7; i++)
        {
            for(int j=1; j<=18; j++)
            {
                n=e->T[i][j]->tete;
                while(n!=NULL)
                {
                    if (n->info->numAto==x->numAto-1&&n->info->masseAto+2<x->masseAto)
                    {
                        e1=elementCreation(rtn(x->masseAto),n->info->etatPhy,x->numAto-1,n->info->symbole);
                        return e1;
                    }
                    n=n->suivant;
                }
            }
        }
        break;
    }
    return e1;
}


void radioAfficher(element_atm elt)
{
    printf("%.3f  %3s  %3d",rtn(elt->masseAto),elt->symbole,elt->numAto);
}


int main()
{
    element_tab taab=tabCreer();
    element_atm e1=elementCreation(1.008,'G',1,"H");
    element_atm e2=elementCreation(4.0026,'G',2,"He");
    element_atm e3=elementCreation(6.94,'S',3,"Li");
    element_atm e4=elementCreation(9.0122,'S',4,"Be"),
                e5=elementCreation(10.81, 'S',5,"B"),
                e6=elementCreation(12.011,'S',6,"C"),
                e7=elementCreation(14.007,'G',7,"N"),
                e8=elementCreation(15.999,'G',8,"O"),
                e9=elementCreation(18.998,'G',9,"F"),
                e10=elementCreation(20.180,'G',10,"Ne"),
                e11=elementCreation(22.990,'S',11,"Na"),
                e12=elementCreation(24.305, 'S',12,"Mg"),
                e13=elementCreation(26.982,'S',13,"Al"),
                e14=elementCreation(28.085, 'S',14,"Si"),
                e15=elementCreation(30.974,'S',15,"P"),
                e16=elementCreation(32.06,'S',16,"S"),
                e17=elementCreation(35.45, 'G',17,"Cl"),
                e18=elementCreation(39.948,'G',18,"Ar"),
                e19=elementCreation(39.098,'S',19,"K"),
                e20=elementCreation(40.078,'S',20,"Ca"),
                e21=elementCreation(44.956, 'S',21,"Sc"),
                e22=elementCreation(47.867,'S',22,"Ti"),
                e23=elementCreation(50.942,'S',23,"V"),
                e24=elementCreation(51.996, 'S',24,"Cr"),
                e25=elementCreation(54.938,'S',25,"Mn"),
                e26=elementCreation(55.845, 'S',26,"Fe"),
                e27=elementCreation(58.933, 'S',27,"Co"),
                e28=elementCreation(58.693,'S',28,"Ni"),
                e29=elementCreation(63.546,'S',29,"Cu"),
                e30=elementCreation(65.38,'S',30,"Zn"),
                e31=elementCreation(69.723, 'S',31,"Ga"),
                e32=elementCreation(72.630,'S',32,"Ge"),
                e33=elementCreation(74.922,'S',33,"As"),
                e34=elementCreation(78.971, 'S',34,"Se"),
                e35=elementCreation(79.904,'L',35,"Br"),
                e36=elementCreation(83.798,'G',36,"Kr"),
                e37=elementCreation(85.468, 'S',37,"Rb"),
                e38=elementCreation(87.62,'S',38,"Sr"),
                e39=elementCreation(88.906,'S',39,"Y"),
                e40=elementCreation(91.224,'S',40,"Zr"),
                e41=elementCreation(92.906,'S',41,"Nb"),
                e42=elementCreation(95.95,'S',42,"Mo"),
                e43=elementCreation(98, 'Y',43,"Tc"),
                e44=elementCreation(101.07,'S',44,"Ru"),
                e45=elementCreation(102.91, 'S',45,"Rh"),
                e46=elementCreation(106.42, 'S',46,"Pd"),
                e47=elementCreation(107.87,'S',47,"Ag"),
                e48=elementCreation(112.41,'S',48,"Cd"),
                e49=elementCreation(114.82,'S',49,"In"),
                e50=elementCreation(118.71, 'S',50,"Sn"),
                e51=elementCreation(121.76,'S',51,"Sb"),
                e52=elementCreation(127.60,'S',52,"Te"),
                e53=elementCreation(126.90, 'S',53,"I"),
                e54=elementCreation(131.29, 'G',54,"Xe"),
                e55=elementCreation(132.91, 'S',55,"Cs"),
                e56=elementCreation(137.33, 'S',56,"Ba"),
                e57=elementCreation(138.91, 'S',57,"La"),
                e58=elementCreation(140.12,'S',58,"Ce"),
                e59=elementCreation(140.91,'S',59,"Pr"),
                e60=elementCreation(144.24,'S',60,"Nd"),
                e61=elementCreation(145,'Y',61,"Pm"),
                e62=elementCreation(150.36,'S',62,"Sm"),
                e63=elementCreation(150.36,'S',63,"Eu"),
                e64=elementCreation(157.96,'S',64,"Gd"),
                e65=elementCreation(158.93, 'S',65,"Tb"),
                e66=elementCreation(162.50, 'S',66,"Dy"),
                e67=elementCreation(164.93, 'S',67,"Ho"),
                e68=elementCreation(167.26, 'S',68,"Er"),
                e69=elementCreation(168.93,'S',69,"Tm"),
                e70=elementCreation(173.05, 'S',70,"Yb"),
                e71=elementCreation(174.97, 'S',71,"Lu"),
                e72=elementCreation(178.49,'S',72,"Hf"),
                e73=elementCreation(180.95, 'S',73,"Ta"),
                e74=elementCreation(183.84, 'S',74,"W"),
                e75=elementCreation(186.21, 'S',75,"Re"),
                e76=elementCreation(190.23, 'S',76,"Os"),
                e77=elementCreation(192.22, 'S',77,"Ir"),
                e78=elementCreation(195.08, 'S',78,"Pt"),
                e79=elementCreation(196.97, 'S',79,"Au"),
                e80=elementCreation(200.59, 'L',80,"Hg"),
                e81=elementCreation(204.38, 'S',81,"Tl"),
                e82=elementCreation(207.2, 'S',82,"Pb"),
                e83=elementCreation(208.98, 'S',83,"Bi"),
                e84=elementCreation(209, 'S',84,"Po"),
                e85=elementCreation(210, 'S',85,"At"),
                e86=elementCreation(222, 'G',86,"Rn"),
                e87=elementCreation(223, 'S',87,"Fr"),
                e88=elementCreation(226, 'S',88,"Ra"),
                e89=elementCreation(227, 'S',89,"Ac"),
                e90=elementCreation(232.04, 'S',90,"Th"),
                e91=elementCreation(231.04, 'S',91,"Pa"),
                e92=elementCreation(238.03, 'S',92,"U"),
                e93=elementCreation(237, 'S',93,"Np"),
                e94=elementCreation(244,'S',94,"Pu"),
                e95=elementCreation(243,'S',95,"Am"),
                e96=elementCreation(247, 'S',96,"Cm"),
                e97=elementCreation(247, 'S',97,"Bk"),
                e98=elementCreation(251, 'S',98,"Cf"),
                e99=elementCreation(252,'S',99,"Es"),
                e100=elementCreation(257, 'S',100,"Fm"),
                e101=elementCreation(258, 'S',101,"Md"),
                e102=elementCreation(259, 'S',102,"No"),
                e103=elementCreation(262, 'S',103,"Lr"),
                e104=elementCreation(267, 'S',104,"Rf"),
                e105=elementCreation(270, 'S',105,"Db"),
                e106=elementCreation(271, 'S',106,"Sg"),
                e107=elementCreation(270, 'S',107,"Bh"),
                e108=elementCreation(277, 'S',108,"Hs"),
                e109=elementCreation(276, 'S',109,"Mt"),
                e110=elementCreation(281, 'S',110,"Ds"),
                e111=elementCreation(282, 'S',111,"Rg"),
                e112=elementCreation(285,'S',112,"Cn"),
                e113=elementCreation(285, 'S',113,"Uut"),
                e114=elementCreation(289, 'S',114,"Fl"),
                e115=elementCreation(289, 'S',115,"Uup"),
                e116=elementCreation(293, 'S',116,"Lv"),
                e117=elementCreation(294,'S',117,"Uus"),
                e118=elementCreation(294, 'S',118,"Uuo");

    inserer(taab->T[1][1],e1,1);
    inserer(taab->T[1][18],e2,1);
    inserer(taab->T[2][1],e3,1);
    inserer(taab->T[2][2],e4,1);
    inserer(taab->T[2][13],e5,1);
    inserer(taab->T[2][14],e6,1);
    inserer(taab->T[2][15],e7,1);
    inserer(taab->T[2][16],e8,1);
    inserer(taab->T[2][17],e9,1);
    inserer(taab->T[2][18],e10,1);
    inserer(taab->T[3][1],e11,1);
    inserer(taab->T[3][2],e12,1);
    inserer(taab->T[3][13],e13,1);
    inserer(taab->T[3][14],e14,1);
    inserer(taab->T[3][15],e15,1);
    inserer(taab->T[3][16],e16,1);
    inserer(taab->T[3][17],e17,1);
    inserer(taab->T[3][18],e18,1);
    inserer(taab->T[4][1],e19,1);
    inserer(taab->T[4][2],e20,1);
    inserer(taab->T[4][3],e21,1);
    inserer(taab->T[4][4],e22,1);
    inserer(taab->T[4][5],e23,1);
    inserer(taab->T[4][6],e24,1);
    inserer(taab->T[4][7],e25,1);
    inserer(taab->T[4][8],e26,1);
    inserer(taab->T[4][9],e27,1);
    inserer(taab->T[4][10],e28,1);
    inserer(taab->T[4][11],e29,1);
    inserer(taab->T[4][12],e30,1);
    inserer(taab->T[4][13],e31,1);
    inserer(taab->T[4][14],e32,1);
    inserer(taab->T[4][15],e33,1);
    inserer(taab->T[4][16],e34,1);
    inserer(taab->T[4][17],e35,1);
    inserer(taab->T[4][18],e36,1);
    inserer(taab->T[5][1],e37,1);
    inserer(taab->T[5][2],e38,1);
    inserer(taab->T[5][3],e39,1);
    inserer(taab->T[5][4],e40,1);
    inserer(taab->T[5][5],e41,1);
    inserer(taab->T[5][6],e42,1);
    inserer(taab->T[5][7],e43,1);
    inserer(taab->T[5][8],e44,1);
    inserer(taab->T[5][9],e45,1);
    inserer(taab->T[5][10],e46,1);
    inserer(taab->T[5][11],e47,1);
    inserer(taab->T[5][12],e48,1);
    inserer(taab->T[5][13],e49,1);
    inserer(taab->T[5][14],e50,1);
    inserer(taab->T[5][15],e51,1);
    inserer(taab->T[5][16],e52,1);
    inserer(taab->T[5][17],e53,1);
    inserer(taab->T[5][18],e54,1);
    inserer(taab->T[6][1],e55,1);
    inserer(taab->T[6][2],e56,1);

    taab->T[6][3]->lg=15;

    inserer(taab->T[6][3],e57,1);
    inserer(taab->T[6][3],e58,2);
    inserer(taab->T[6][3],e59,3);
    inserer(taab->T[6][3],e60,4);
    inserer(taab->T[6][3],e61,5);
    inserer(taab->T[6][3],e62,6);
    inserer(taab->T[6][3],e63,7);
    inserer(taab->T[6][3],e64,8);
    inserer(taab->T[6][3],e65,9);
    inserer(taab->T[6][3],e66,10);
    inserer(taab->T[6][3],e67,11);
    inserer(taab->T[6][3],e68,12);
    inserer(taab->T[6][3],e69,13);
    inserer(taab->T[6][3],e70,14);
    inserer(taab->T[6][3],e71,15);
    inserer(taab->T[6][4],e72,1);
    inserer(taab->T[6][5],e73,1);
    inserer(taab->T[6][6],e74,1);
    inserer(taab->T[6][7],e75,1);
    inserer(taab->T[6][8],e76,1);
    inserer(taab->T[6][9],e77,1);
    inserer(taab->T[6][10],e78,1);
    inserer(taab->T[6][11],e79,1);
    inserer(taab->T[6][12],e80,1);
    inserer(taab->T[6][13],e81,1);
    inserer(taab->T[6][14],e82,1);
    inserer(taab->T[6][15],e83,1);
    inserer(taab->T[6][16],e84,1);
    inserer(taab->T[6][17],e85,1);
    inserer(taab->T[6][18],e86,1);
    inserer(taab->T[7][1],e87,1);
    inserer(taab->T[7][2],e88,1);

    taab->T[7][3]->lg=15;

    inserer(taab->T[7][3],e89,1);
    inserer(taab->T[7][3],e90,2);
    inserer(taab->T[7][3],e91,3);
    inserer(taab->T[7][3],e92,4);
    inserer(taab->T[7][3],e93,5);
    inserer(taab->T[7][3],e94,6);
    inserer(taab->T[7][3],e95,7);
    inserer(taab->T[7][3],e96,8);
    inserer(taab->T[7][3],e97,9);
    inserer(taab->T[7][3],e98,10);
    inserer(taab->T[7][3],e99,11);
    inserer(taab->T[7][3],e100,12);
    inserer(taab->T[7][3],e101,13);
    inserer(taab->T[7][3],e102,14);
    inserer(taab->T[7][3],e103,15);
    inserer(taab->T[7][4],e104,1);
    inserer(taab->T[7][5],e105,1);
    inserer(taab->T[7][6],e106,1);
    inserer(taab->T[7][7],e107,1);
    inserer(taab->T[7][8],e108,1);
    inserer(taab->T[7][9],e109,1);
    inserer(taab->T[7][10],e110,1);
    inserer(taab->T[7][11],e111,1);
    inserer(taab->T[7][12],e112,1);
    inserer(taab->T[7][13],e113,1);
    inserer(taab->T[7][14],e114,1);
    inserer(taab->T[7][15],e115,1);
    inserer(taab->T[7][16],e116,1);
    inserer(taab->T[7][17],e117,1);
    inserer(taab->T[7][18],e118,1);


    int choix1,choix2,n121;

    char s[3];
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("||---------------------                                                     --------------------------||\n");
    printf("||---------------------       BIENVENUS CHEZ NOTRE TABLEAU PERIODIQUE!      --------------------------||\n");
    printf("||....................................................................................................||\n");
    printf("||....................................................................................................||\n");
    printf("||....................................................................................................||\n");
    printf("||....................................................................................................||\n");
    printf("||---------------------                                                     --------------------------||\n");
    printf("||---------------------                   1.Affichage                       --------------------------||\n");
    printf("||---------------------                   2.Recherche                       --------------------------||\n");
    printf("||---------------------                                                     --------------------------||\n");
    printf("||....................................................................................................||\n");
    printf("||....................................................................................................||\n");
    printf("||....................................................................................................||\n");
    printf("||---------------------              0. quitter l'application               --------------------------||\n");
    printf("||---------------------                                                     --------------------------||\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    int i=0;
    do
    {

        if (i>0)
            printf("OUPS! VOUS DEVEZ CHOISIR L'UNE DE CES OPTIONS SI DESSUS!\n");
        scanf("%i",&choix1);
        i++;

    }
    while (choix1<0||choix1>2);
    if (i>3)
        printf("oui, c'est ca.");
    i=0;
    switch (choix1)
    {
    case 1:
        do
        {
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||---------------------                                                     --------------------------||\n");
            printf("||---------------------           VOUS AVEZ CHOISI L'AFFICHAGE!             --------------------------||\n");
            printf("||---------------------                                                     --------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------       1.Affichage des elements du tableau periodique.      ----------------------||\n");
            printf("||------------------       2.Affichage des elements a l'etat gazeux.            ----------------------||\n");
            printf("||------------------       3.Affichage des elements Lourds (Z>83).              ----------------------||\n");
            printf("||------------------       4.Affichage des elements Radioactifs.                ----------------------||\n");
            printf("||------------------       5.Affichage des elements instables.                  ----------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------        |General knowledge for C8H10N4O2 (caffeine)|        ----------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------       6.La masse molaire de la molecule de caffeine.       ----------------------||\n");
            printf("||------------------       7.Le nombre de moles de caféine dans 10,0 g.         ----------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------                  8.MENU PRINCIPALE                         ----------------------||\n");
            printf("||------------------                  0.QUITTER L'APPLICATION                   ----------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||-----------------------------------VOTRE CHOIX: ");
            scanf("%i",&choix2);
        }
        while (choix2<0||choix2>8);
        switch (choix2)
        {
        case 2:
            printf("les elemts gazeux sont:\n");
            listeAfficher(gaz(taab));
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 1:
            tabAfficher(taab);
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 3:
            printf("les elements lourds sont:\n");
            listeAfficher(Lourds(taab));
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 4:
            printf("/!\\ les elements radioactifs sont:\n");
            listeAfficher(radioactif(taab));
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 5:
            printf("les elements instables sont:\n");
            listeAfficher(instables(taab));
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 6:
            printf ("la masse molaire de la molecule de caffeine est %.4f g/mol",m_C8H10N4O2(taab));
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 7:
            printf ("Le nombre de moles de caféine dans 10,0 g est %.4f mol",n_C8H10N4O2(taab));
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 8:
            main();
            break;
        case 0:
            printf("\nmerci pour la visite!\n");
            return 0;
        }
        break;
    case 2:
        do
        {
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||---------------------                                                     --------------------------||\n");
            printf("||---------------------           VOUS AVEZ CHOISI LA RECHERCHE!            --------------------------||\n");
            printf("||---------------------                                                     --------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------   1.Recherche de la masse atomique relative a un atome          -----------------||\n");
            printf("||------------------   2.Recherche de la masse atomique relative a une molecule.     -----------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------             |RECHERCHE SUR LA RADIOACTIVITE|               ----------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------       3.Recherche sur la radioactivite d'un atome.         ----------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||------------------                  4.MENU PRINCIPALE                         ----------------------||\n");
            printf("||------------------                  0.QUITTER L'APPLICATION                   ----------------------||\n");
            printf("||----------------------------------------------------------------------------------------------------||\n");
            printf("||-----------------------------------VOTRE CHOIX: ");
            scanf("%i",&choix2);
        }
        while (choix2<0||choix2>4);
        switch (choix2)
        {
            int trouve,type;
        case 1:
            do
            {
                trouve=1;
                do
                {
                    fflush(stdin);
                    printf("donnez le symbole de l'atome mis en question pour la recherche: \n");
                    scanf("%s",s);
                }
                while (Alphabet(s)!=1||(strlen(s)!=2&&strlen(s)!=1&&strlen(s)!=3));
                if (Ar(taab,s)!=0)
                {
                    printf("\nLa masse atomique de l'atome %s est: %.3f",s,Ar(taab,s));
                }
                else
                {
                    trouve=0;
                    printf("VEUILLEZ CHOISIR UN ATOME QUI EXISTE SUR NOTRE PLANETE!:3\n(Toujours ecrire la 1ere lettre en maj et la 2eme en minus)\n");
                }
            }
            while(trouve==0);
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 2:
            do
            {
                trouve=1;
                printf("\n||==Tout symbole dans la formule moleculaire devrait être suivi d’un indice indiquant le nombre d’atomes meme s’il y en qu’un seul. Exemple: H2O1 ==||\n");
                fflush(stdin);
                printf("\ndonnez le symbole de la molecule mise en question pour la recherche: \n");
                scanf("%s",s);
                if (M(taab,s)!=0)
                    printf("\nLa masse atomique relative a %s est %.4f.",s,M(taab,s));
                else
                {
                    trouve=0;
                }
            }
            while (trouve==0);
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 3:

            do
            {
                printf("donner le type de radiation: \n\t1.radiation ALPHA.\n\t2.radiation BETA-.\n\t3.radiation BETA+.\nvotre choix: ");
                scanf("%i",&type);
            }
            while(type<=0||type>3);

            if (type==1)
            {
                printf("||________________     RADIOACTIVITE ALPHA     ___________________||\n");

                do
                {

                    trouve=1;

                    do
                    {
                        fflush(stdin);
                        printf("donnez le symbole de l'atome mis en question pour effectuer la desintegration alpha: \n");
                        scanf("%s",s);
                    }
                    while (Alphabet(s)!=1||(strlen(s)!=2&&strlen(s)!=1&&strlen(s)!=3));

                    if ((listeExiste(Lourds(taab),recherche(taab,s))==0)&&(listeExiste(instables(taab),recherche(taab,s))==0))
                    {
                        printf("votre noyau fils est:\n");
                        radioAfficher(recherche(taab,s));printf(" => ");
                        radioAfficher(noyauFils(recherche(taab,s),taab,1));
                        printf("  +  ");
                        radioAfficher(e2);
                        printf("  +  Gamma");
                    }
                    else
                    {
                        trouve=0;
                        printf("VEUILLEZ CHOISIR UN ATOME VALIDE!\n(Toujours ecrire la 1ere lettre en maj et la 2eme en minus et l'atome doit etre lourd et instable.(try Uup to come back to main menu)\n");
                    }
                }
                while(trouve==0);

            }
            else if (type==2)
            {
                printf("||________________     RADIOACTIVITE BETA-     ___________________||\n");
                do
                {
                    trouve=1;
                    do
                    {
                        fflush(stdin);
                        printf("donnez le symbole de l'atome mis en question pour effectuer la désintégration beta-: \n");
                        scanf("%s",s);
                    }
                    while (Alphabet(s)!=1||(strlen(s)!=2&&strlen(s)!=1&&strlen(s)!=3));
                    if (recherche(taab,s)!=NULL&&noyauFils(recherche(taab,s),taab,2)->masseAto!=0)
                        printf("votre atome est valide!\n");
                    else
                    {
                        trouve=0;
                        printf("VEUILLEZ COISIR UN ATOME VALIDE!\n(Toujours ecrire la 1ere lettre en maj et la 2eme en minus. La reaction est energetiquement possible \na la seule condition que le noyau atomique fils soit moins massif que le noyau pere.)\n");
                    }
                }
                while(trouve==0);
                radioAfficher(recherche(taab,s));printf(" => ");
                radioAfficher(noyauFils(recherche(taab,s),taab,2));
                printf("  +   -e   +   Gamma   +    antineutrino\n");
            }
            else
            {
                printf("||________________     RADIOACTIVITE BETA+     ___________________||\n");
                do
                {
                    trouve=1;
                    do
                    {
                        fflush(stdin);
                        printf("donnez le symbole de l'atome mis en question pour effectuer la désintégration beta+: \n");
                        scanf("%s",s);
                    }
                    while (Alphabet(s)!=1||(strlen(s)!=2&&strlen(s)!=1&&strlen(s)!=3));

                    if (recherche(taab,s)!=NULL&&noyauFils(recherche(taab,s),taab,3)->masseAto!=0)
                        printf("votre atome est valide!\n");
                    else
                    {
                        trouve=0;
                        printf("VEUILLEZ COISIR UN ATOME VALIDE!\n(Toujours ecrire la 1ere lettre en maj et la 2eme en minus. Cette réaction ne peut avoir lieu \nque si la masse du noyau fils, additionnee a deux fois la masse de l'electron, est inferieure à celle du noyau pere.)\n");
                    }
                }
                while(trouve==0);
                radioAfficher(recherche(taab,s));printf(" => ");
                radioAfficher(noyauFils(recherche(taab,s),taab,3));
                printf("  +   rayonnement beta  +   n   +    Gamma\n");
            }
            do
            {
                printf("\n ----------------------- 1.retour au menu principale.-----------------------------");
                printf("\n ======================= 2. quitter le programme.    =============================");
                scanf("%i", &n121);
            }
            while ((n121!=1)&&(n121!=2));
            if (n121==1)
                main();
            else
            {
                printf ("merci pour la visite!");
                return 0;
            }
            break;
        case 4:
            main();
            break;
        case 0:
            printf("merci pour tous, et au revoir.");
            return 0;
            break;
        }

    case 0:
        printf ("\nmerci pour la visite!\n");
        return 0;
        break;

    }
}
