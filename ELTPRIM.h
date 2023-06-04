#ifndef ELTPRIM_H_INCLUDED
#define ELTPRIM_H_INCLUDED

#include "ELTSDD.H"

element_atm elementCreation(double,char,int,char *) ;
element_atm elementCreer();
void elementLire(element_atm *);
void elementAfficher(element_atm);
void elementAffecter(element_atm*, element_atm);
void elementCopier(element_atm*, element_atm);
int elementComparer(element_atm, element_atm);
void elementDetruire (element_atm);

#endif // ELTPRIM_H_INCLUDED
