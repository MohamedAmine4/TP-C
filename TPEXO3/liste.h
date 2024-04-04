#include<stdio.h>
#include<stdlib.h>


typedef struct horaire {

  char ville_depart[20];
  char ville_arriver[20];
  char heure_depart[10];
  char heure_arriver[10];
  int distance;
 struct  horaire *suivant;

}horaire;

horaire* creer_horaire(char *ville_depart, char *ville_arrivee, char *heure_depart, char *heure_arrivee, int distance);
void ajouter_horaire(horaire **liste, char *ville_depart, char *ville_arrivee, char *heure_depart, char *heure_arrivee, int distance) ;
void afficher_horaires(const horaire *liste);
void afficher_horaire_ville_depart(horaire *liste, char *ville_depart);

float calculer_duree_trajet(char *heure_depart ,char *heure_arrivee) ;
float vitesse_moyenne(horaire *list, char *ville_depart, char *ville_arrivee);
horaire *trajet_vitese_max(horaire *liste);


void trier_horaires_croissant(horaire **liste);

horaire *meilleur_trajet(horaire *liste, char *ville_depart, char *ville_arrivee);

