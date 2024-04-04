#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
#include<string.h>
#include<ctype.h>



horaire* creer_liste(){
  return NULL;
}

horaire* creer_horaire(char *ville_depart, char *ville_arrivee, char *heure_depart, char *heure_arrivee, int distance) {
    horaire *nouveau = (horaire*)malloc(sizeof(horaire));
    if (nouveau == NULL) {
        printf("Erreur d'allocation de memoire\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nouveau->ville_depart, ville_depart);
    strcpy(nouveau->ville_arriver, ville_arrivee);
    strcpy(nouveau->heure_depart, heure_depart);
    strcpy(nouveau->heure_arriver, heure_arrivee);
    nouveau->distance = distance;
    nouveau->suivant = NULL;
    return nouveau;
}
void ajouter_horaire(horaire **liste, char *ville_depart, char *ville_arrivee, char *heure_depart, char *heure_arrivee, int distance) {
    horaire *nouveau = creer_horaire(ville_depart, ville_arrivee, heure_depart, heure_arrivee, distance);
    if (*liste == NULL) {
        *liste = nouveau;
    } else {
        horaire *courant = *liste;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }
}
void afficher_horaires(const horaire *liste) {
    const horaire *courant = liste;
    while (courant != NULL) {
        printf("Ville de depart : %s\n", courant->ville_depart);
        printf("Ville d'arrivee : %s\n", courant->ville_arriver);
        printf("Heure de depart : %s\n", courant->heure_depart);
        printf("Heure d'arrivee : %s\n", courant->heure_arriver);
        printf("Distance : %d\n", courant->distance);
        printf("\n");
        courant = courant->suivant;
    }
}
void afficher_horaire_ville_depart(horaire *liste , char *ville_depart){

  horaire *temp;
  temp=liste;
  if(temp==NULL){
    printf("la liste est vide \n");
    return ;
  }
  else{
    while(temp!=NULL){
      if(strcmp(temp->ville_depart,ville_depart)==0){
        printf("Ville de depart : %s\n",temp->ville_depart);
        printf("Ville d'arriver : %s\n",temp->ville_arriver);
        printf("Heure de depart : %s\n",temp->heure_depart);
        printf("Heure d'arriver : %s\n",temp->heure_arriver);
        printf("Distance : %d\n",temp->distance);
        return ;
      }
      temp=temp->suivant;
    }
    printf("ville non trouve\n");
  }
}
float calculer_duree_trajet(char *heure_depart ,char *heure_arrivee) {
  int h_depart,h_arriver,m_depart,m_arriver;
  float heure1,heure2;
  sscanf(heure_depart,"%d:%d",&h_depart,&m_depart);
  sscanf(heure_arrivee,"%d:%d",&h_arriver,&m_arriver);
  heure1=h_depart+m_depart/60.0;
  heure2=h_arriver+m_arriver/60.0;
  return heure2-heure1;
}

float vitesse_moyenne(horaire *list, char *ville_depart, char *ville_arrivee){
  horaire *temp;
  temp =list;
  int distance=0;
  float temps=0;
  while(temp!=NULL){
    if(strcmp(temp->ville_depart,ville_depart)==0 && strcmp(temp->ville_arriver,ville_arrivee)==0){
      distance=temp->distance;
      float a =calculer_duree_trajet( temp->heure_depart ,temp->heure_arriver);
      temps=temps+calculer_duree_trajet( temp->heure_depart ,temp->heure_arriver);
    
    }
    temp=temp->suivant;
  }
  return (float)distance/temps;

}

horaire *trajet_vitese_max(horaire *liste) {
    horaire *temp = liste;
    horaire *max = NULL; // Initialisez max à NULL car nous n'avons pas encore trouvé de trajet
    float max_vitesse = 0; // Initialisez la vitesse maximale à 0

    while (temp != NULL) {
        // Calculez la vitesse moyenne pour le trajet actuel
        float vitesse = vitesse_moyenne(liste, temp->ville_depart, temp->ville_arriver);

        // Si la vitesse moyenne actuelle est supérieure à la vitesse maximale précédente,
        // mettez à jour max et max_vitesse
        if (vitesse > max_vitesse) {
            max = temp;
            max_vitesse = vitesse;
        }

        temp = temp->suivant;
    }

    // Affichez les horaires du trajet avec la vitesse moyenne maximale
    // if (max != NULL) {
    //     afficher_horaires(max);
    // } else {
    //     printf("Aucun trajet trouvé.\n");
    // }

    return max;
}

void trier_horaires_croissant(horaire **liste){
    if (*liste == NULL || (*liste)->suivant == NULL) {
        return; // Si la liste est vide ou contient un seul élément, elle est déjà triée
    }

    horaire *trie = NULL; // Liste triée
    horaire *courant = *liste;

    while (courant != NULL) {
        horaire *suivant = courant->suivant;
        if (trie == NULL || strcmp(courant->heure_depart, trie->heure_depart) < 0) {
            courant->suivant = trie;
            trie = courant;
        } else {
            horaire *temp = trie;
            while (temp->suivant != NULL && strcmp(courant->heure_depart, temp->suivant->heure_depart) >= 0) {
                temp = temp->suivant;
            }
            courant->suivant = temp->suivant;
            temp->suivant = courant;
        }
        courant = suivant;
    }

    *liste = trie; // Met à jour la liste principaleLa fonction trier_horaires implémente l'algorithme du tri par insertion pour trier la liste des horaires par ordre croissant de l'heure de départ.

}
horaire *meilleur_trajet(horaire *liste, char *ville_depart, char *ville_arrivee) {
    horaire *meilleur = NULL;
    float meilleure_vitesse = -1.0;
    while (liste != NULL) {
        if (strcmp(liste->ville_depart, ville_depart) == 0) {
            float duree1 = calculer_duree_trajet(liste->heure_depart, liste->heure_arriver);
            float vitesse1 = vitesse_moyenne(liste, liste->ville_depart, liste->ville_arriver);
            horaire *correspondance = liste->suivant;
            while (correspondance != NULL) {
                if (strcmp(correspondance->ville_depart, liste->ville_arriver) == 0) {
                    float duree2 = calculer_duree_trajet(correspondance->heure_depart, correspondance->heure_arriver);
                    float duree_totale = duree1 + duree2;
                    if (duree_totale >= 0.083333333 && duree_totale <= 2.0) { // Entre 5 minutes et 2 heures
                        float vitesse2 = vitesse_moyenne(correspondance, correspondance->ville_depart, ville_arrivee);
                        if (vitesse2 > meilleure_vitesse) {
                            meilleur = correspondance;
                            meilleure_vitesse = vitesse2;
                        }
                    }
                }
                correspondance = correspondance->suivant;
            }
        }
        liste = liste->suivant;
    }
    return meilleur;
}

