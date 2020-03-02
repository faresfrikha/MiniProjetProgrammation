#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include "stdio.h"
#include "structure.h"

int verifstr(char ch[]);
Fiche_De_Paie saisir_Fiche(int num);
void afficher_Fiche(Fiche_De_Paie F);
void Ajouter_Fiche_Liste(Liste* ListeFiche,Fiche_De_Paie F);
void affiche_Liste_Fiche(Liste ListeFiche);
Noeud* Rechercher_Fiche(Liste ListeFiche);
void Modifier_Fiche(Fiche_De_Paie* F);
void Suprimer_Fiche(Liste* ListeFiche,Fiche_De_Paie F );
void enregistrer(FILE* fichier,Liste ListeFiche);
void telecharger(FILE* fichier,Liste* ListeFiche,int *num);
void entete();
void trier(Liste ListeFiche);
void insertAtTheBegin(Noeud **start_ref, int data);
void swap( Noeud *a,  Noeud *b);
void Calcul_Montant(Liste ListeFiche);
#endif
