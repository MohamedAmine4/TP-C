#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
#include<string.h>
#include<ctype.h>



int main() {
    horaire *liste_horaires = NULL;
  horaire *liste = NULL;
    // Ajout des horaires de trains
    ajouter_horaire(&liste_horaires, "Lille", "Paris", "08:00", "10:00", 200);
      ajouter_horaire(&liste_horaires, "Paris", "Lyon", "10:30", "13:00", 400);
    ajouter_horaire(&liste_horaires, "Lyon", "Marseille", "09:00", "11:30", 300);
  
    ajouter_horaire(&liste, "Lille", "Lyon", "7:00", "10:00", 100);
    ajouter_horaire(&liste, "Lyon", "Marseille", "11:50", "17:00", 300);
    ajouter_horaire(&liste, "Paris", "Lyon", "8:00", "11:00", 200);
    ajouter_horaire(&liste, "Paris", "Marseille", "8:30", "15:30", 600);
    ajouter_horaire(&liste, "Marseille", "Lyon", "12:00", "15:00", 200);
    // printf("Liste des horaires avant le tri :\n");
    // afficher_horaire_ville_depart(liste_horaires,"Lille");
    // printf("\n la list des horaires est : \n");
    // afficher_horaires(liste_horaires);

    // // Tri des horaires par ordre croissant de l'heure de départ
    // trier_horaires_croissant(&liste_horaires);

    // printf("\nListe des horaires apres le tri :\n");
    // afficher_horaires(liste_horaires);

    // // Affichage du meilleur trajet
    // printf("\nMeilleur trajet  :\n");

    // afficher_horaires( trajet_vitese_max(liste_horaires));

    // //calcul dureté du trajet
    // float a =calculer_duree_trajet("08:00","10:00");
    // printf("la dureté du trajet est : %f \n",a);

    //vitesse moyenne
    // float b =vitesse_moyenne(liste_horaires,"Lille","Paris");
    // printf("la vitesse moyenne est : %f \n",b);
  horaire *meilleur = meilleur_trajet(liste_horaires, "Lille", "Marseille");
    if (meilleur != NULL) {
        printf("Le meilleur trajet est : %s - %s : %s - %s\n", meilleur->ville_depart, meilleur->ville_arriver, meilleur->heure_depart, meilleur->heure_arriver);
    } else {
        printf("Aucun trajet trouvé.\n");
    }
    return 0;
}