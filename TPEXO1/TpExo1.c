#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>


typedef struct maillon {
    int val;
    struct maillon* p_suiv;
}maillon_int;

int menu()
{
    int choix = 0;
    printf("1 Creer une liste d'entiers compris entre 0 et 20 de taille aleatoire comprise entre 1 et 20\n"
        "2 Ajouter un element entier aleatoire (compris entre 0 et 20) en tete de liste\n"
        "3 Inserer un element entier aleatoire dans sa place dans la liste suivant l'ordre croissant des premiers elements\n"
        "4 Supprimer l'element de tete\n"
        "5 Supprimer tous les maillons d'une valeur donnee\n"
        "6 Detruire liste\n"
        "7 Sauver la liste courante en binaire dans le fichier \"saveliste.bin\"\n"
        "8 Charger une liste depuis le fichier \"savelist.bin\"\n");

    scanf("%d", &choix);
    rewind(stdin);

    return choix;
}

//pour creer la liste de taille aleatoire 
maillon_int* init_elt()
{
    maillon_int* p_nv_elt = malloc(sizeof(maillon_int));
    p_nv_elt->val = rand() % 21;
    p_nv_elt->p_suiv = NULL;
    return p_nv_elt;
}

//ajouter un element au debut de la pile au debut version 1 
maillon_int* ajout_tete_v1(maillon_int* p_tete, maillon_int* p_nv_elt)
{
    p_nv_elt->p_suiv = p_tete;
    p_tete = p_nv_elt;
    return p_tete;
}

//ajouter un element au debut de la pile au debut version 2 
void ajout_tete_v2(maillon_int** p_p_tete, maillon_int* p_nv_elt)
{
    p_nv_elt->p_suiv = *p_p_tete;
    *p_p_tete = p_nv_elt;
}

//parcourir la liste via un pointeur et en affiche chaque element 
void parcourir(maillon_int* p_tete)
{
    if (p_tete == NULL)
        printf("liste vide");
    else
        while (p_tete != NULL) {
            printf("%d--", p_tete->val);
            p_tete = p_tete->p_suiv;
        }
    putchar('\n');
}

//inserer un nouveau element a la tete si la valeur de la tete est null ou la nv elem < val de tet

maillon_int* inserer1(maillon_int* p_tete, maillon_int* p_nv_elt)
{
    maillon_int* n, * prec;
    
    if (p_tete == NULL || p_nv_elt->val <= p_tete->val) {  
        p_nv_elt->p_suiv = p_tete;
        p_tete = p_nv_elt;
    }
    else {  
        n = prec = p_tete; //variables de pointeur de tete
        //tant que le pointeur n n'est pas null et le nv ele > a ele encore de traitement 
        //en part au suivant 
        while (n != NULL && p_nv_elt->val > n->val) { 
            prec = n;
            n = n->p_suiv;
        }
        // apres que le condition de while n'est pas verifier en passe a element suivant 
        //
        p_nv_elt->p_suiv = n;
        prec->p_suiv = p_nv_elt;
    }
    return p_tete;
}

void inserer2(maillon_int** prem, maillon_int* e)
{
    maillon_int* n, * prec;
    if (*prem == NULL || e->val <= (*prem)->val){ 
        e->p_suiv = *prem;
        *prem = e;
    }
    else {  
        n = prec = *prem;
        while (n != NULL && e->val > n->val) {
            prec = n;
            n = n->p_suiv;
        }
        e->p_suiv = n;
        prec->p_suiv = e;
    }
}

void supprimer_debut(maillon_int** prem)
{
    maillon_int* n;
    if (*prem != NULL) {
        n = *prem;//affecter le premier element a un variable n en suite pointe sur le suivant par le ponteur premier 

        *prem = (*prem)->p_suiv;
        //supprimer le premier element (depiler )
        free(n);
    }
}

//supprimer un element donner si il existe 
maillon_int* critere_supp_un1(maillon_int* prem, int val)
{
    maillon_int* e = prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                prem = e->p_suiv;
            else
                prec->p_suiv = e->p_suiv;
        }
        else
            prec = e;
        e = e->p_suiv;
        if (n != NULL)
            free(n);
    }
    return prem;

}

void critere_supp_un2(maillon_int** prem, int val)
{
    maillon_int* e = *prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                *prem = e->p_suiv;
            else
                prec->p_suiv = e->p_suiv;
        }
        else
            prec = e;
        e = e->p_suiv;
        if (n != NULL)
            free(n);
    }
}


void detruire_liste(maillon_int** prem)
{
    maillon_int* n;
    while (*prem != NULL) {
        n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}

void detruire_liste2(maillon_int** prem)
{
    while (*prem != NULL)
        supprimer_debut(prem);
    
}

/* Permet la sérialisation format binaire dans le fichier
"saveliste.bin" de la liste d'entier (maillon_int) dont
le pointeur sur le premier élément est passé en paramètre
@input : maillon_int * prem, pointeur sur l'élément de tête de la liste à sérialiser
@output : void
@precondition : le répertoire courant et le processus père permettent l'écriture 
                le pointeur prem, est soit NULL (aucune action) soit pointe sur
                le premier élément d'une liste d'entiers
@postcondition : le fichier saveliste.bin contient les éléments de la liste 
                dont le premier élément est pointé par prem. 
                Nota : il n'y a pas de libération de la mémoire occupée par la 
                liste. Il faut donc la détruire avant d'éventuellement la recharger.
*/
void sauver_liste(maillon_int* prem)
{
    //ouvrir un fichier binaire en écriture : suffixe b
    FILE* f=fopen("saveliste.bin", "wb");
    printf("Ouvertude du fichier %p\n",f);
    // si liste non vide
    if (prem != NULL) {
        if (f==NULL)
            fprintf(stderr,"erreur creation fichier :%i\n",errno);
        else // parcourir la liste jusque fin
            while (prem != NULL) {
                // écrire chaque maillon en binaire
                if (1 !=fwrite(prem, sizeof(maillon_int), 1, f))
                    fprintf(stderr,"Erreur d'ecriture du maillon %p\n",prem);
                else 
                // passer au maillon suivant
                prem = prem->p_suiv;
            }
            fclose(f);	// fermer le fichier
    }
    else
        fprintf(stderr,"pas de sauvegarde pour une liste vide\n");
}

maillon_int* load_liste()
{
    FILE* f;
    maillon_int* prem = NULL, * p, e;
    if ((f= fopen("saveliste.bin", "rb")) != NULL) {
        prem = malloc(sizeof(maillon_int));
        fread(prem, sizeof(maillon_int), 1, f);
        p = prem;
        while (fread(&e, sizeof(maillon_int), 1, f)) {
            p->p_suiv = malloc(sizeof(maillon_int));
            p = p->p_suiv;
            *p = e;
            p->p_suiv = NULL;
        }
        fclose(f);
    }
    else
        printf("erreur ou fichier inexistant");
    return prem;
}

int main()
{
  maillon_int* pile = NULL;
    maillon_int* premier = NULL;
    maillon_int* nouveau;
    int fin = 0;
    int i, nb;

    srand((unsigned)time(NULL));
    while (!fin) {
        i = menu();
        switch (i) {

        case 1: //Creer une liste de taille aleatoire
                printf("Entrez le nombre d'elements pour la liste : ");
            scanf("%d", &nb);
            premier = NULL; 
            for (int j = 0; j < nb; j++) {
                nouveau = init_elt();
                premier = ajout_tete_v1(premier, nouveau);
            }
            printf("Liste creee avec succes.\n");
            parcourir(premier);
            break;

        case 2: // Ajouter
            nouveau= init_elt();//va contient une valeur aleatoire
            premier=ajout_tete_v1(premier,nouveau);
            printf("Element ajoute avec succes.\n");
            parcourir(premier);
            break;

        case 3: // Inserer (ordre croissant)
            nouveau = init_elt();
            premier =inserer1(premier,nouveau);
            printf("Element insere avec succes.\n");
            parcourir(premier);
            break;

        case 4: //Supprimer debut:
            supprimer_debut(&premier);
            printf("Element de tete supprime avec succes.\n");
            parcourir(premier);
            break;

        case 5: // Supprimer un maillon d'une valeur donnee
            printf("Entrez la valeur à supprimer : ");
            scanf("%d", &nb);
            premier = critere_supp_un1(premier, nb);
            printf("Maillons de valeur %d supprimes avec succes.\n", nb);
            parcourir(premier);
            break;

        case 6: // detruire liste
            detruire_liste(&premier);
                    printf("Liste detruite avec succes.\n");
            break;

        case 7: // Sauver liste
            sauver_liste(premier);
             printf("Liste sauvegardee avec succes.\n");
            break;

        case 8: // Charger liste
            premier=load_liste();
             printf("Liste chargee avec succes.\n");
            parcourir(premier);
            break;

        default:
        fin=1;
             printf("Fin du programme.\n");
            break;
        }
        
    }

    return 0;
}