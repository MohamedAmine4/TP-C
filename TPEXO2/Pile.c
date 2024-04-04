#include<stdio.h>
#include<stdlib.h>
#include"pile.h"



Pile * empiler(Pile *debut , int val){
  Pile *box;
  box=(Pile*)malloc(sizeof(Pile));
  box->valeur=val;
  box->suivant=debut;
  debut=box;
  return box;
}

Pile * renverser(Pile *debut){
  Pile *p,*q,*r;
  p=debut;
  q=NULL;
  while(p!=NULL){
    r=q;
    q=p;
    p=p->suivant;
    q->suivant=r;
  }
  debut=q;
  return debut;
}

void Afficher(Pile *p){
     Pile *temp;//le pointeur qui va parcourir la la pile
     temp=p;
     if (temp==NULL){
       printf("La pile est vide\n");
       return;
     }
     else {
     while(temp !=NULL){
      printf("%d--->",temp->valeur);
      temp=temp->suivant;
     }
}}

Pile * depiler(Pile *debut){
  Pile *p;
  if(debut==NULL){
    printf("La pile est vide\n");
    return debut;
  }
  else{
  p=debut;
  debut=debut->suivant;
  free(p);
  return debut;
  }
}
int valeur_sommet(Pile *debut) {
    if (debut == NULL) {
        printf("La pile est vide\n");
        return -1; // Valeur de retour pour indiquer une erreur
    } else {
        return debut->valeur;
    }
}

int depiler_et_recuperer_valeur(Pile **debut) {
    if (*debut == NULL) {
        printf("La pile est vide\n");
        return -1; // Valeur de retour pour indiquer une erreur
    } else {
        int valeur = (*debut)->valeur;
        Pile *temp = *debut;
        *debut = (*debut)->suivant;
        free(temp);
        return valeur;
    }
}