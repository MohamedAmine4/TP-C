#ifndef PILE_H
#define PILE_H

typedef struct Pile {
    int valeur;
    struct Pile *suivant;
} Pile;

Pile *empiler(Pile *debut, int val);
Pile *renverser(Pile *debut);
void Afficher(Pile *p);
Pile *depiler(Pile *debut);
int valeur_sommet(Pile *debut);
int depiler_et_recuperer_valeur(Pile **debut);

#endif /* PILE_H */
