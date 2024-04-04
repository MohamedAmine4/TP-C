#include<stdio.h>
#include<stdlib.h>
#include"pile.h"



int main(){
  int nbr; //nombre d'element a empiler 
  printf("Donner le nombre d'element a empiler : ");
  scanf("%d",&nbr);
  Pile *pile = NULL;


  for(int i=0;i<nbr;i++){
    int val;//la valeur q'on va entrer dans la pile
    printf("Donner la valeur a empiler : ");
    scanf("%d",&val);
    pile = empiler(pile,val);
  }
  printf("La pile est : \n");
  Afficher(pile);
  // pile=depiler(pile);
  // printf("\nLa pile apres depiler : \n");
  // Afficher(pile);

 pile=  renverser(pile);
 printf("\nLa pile apres renverser : \n");
 Afficher(pile);
 printf("\nLa pile apres empiler 6 : \n");
pile = empiler(pile,6);
Afficher(pile);
  return 0;
}