#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <time.h>
#include <ctype.h>
#include "fonction.h"

int main()
{

    Liste ListeFiche;
    int Choix,num=0;
    FILE* fichier;
    Fiche_De_Paie F;
    Noeud* Recher=NULL;
    ListeFiche.Debut=NULL;
    entete();
    while(1)
    {
        printf("\n\n******************************");
        printf("\n******* Menu aux choix *******");
        printf("\n******************************\n\n");
        printf("1. Telecharger la liste des Fiches \n");
        printf("2. Ajouter Une Fiches \n");
        printf("3. Rechercher Une Fiche \n");
        printf("4. Modifier Une Fiche \n");
        printf("5. Supprimer Une Fiche \n");
        printf("6. Affichier la liste des Fiches \n");
        printf("7. Calculer le montant total de tous les salaires d'un mois \n");
        printf("0. Enregistrer et Quitter \n");
        printf("\n\nIntroduire votre choix: ");
        scanf ("%d",&Choix);
        switch (Choix)
        {
        case 1:
        {
            fichier=fopen("Liste des fiches de paie.txt","r");
            if (fichier==NULL)
            {
                printf("\n le fichier n'existe pas");
            }
            else
                telecharger(fichier,&ListeFiche,&num);
            fclose(fichier);
            trier(ListeFiche);
            affiche_Liste_Fiche(ListeFiche);
            break;
        }
        case 2:
        {
            num++;
            F=saisir_Fiche(num);
            Ajouter_Fiche_Liste(&ListeFiche,F);
            trier(ListeFiche);
            affiche_Liste_Fiche(ListeFiche);
            break;
        }
        case 3:
        {
            Recher=Rechercher_Fiche(ListeFiche);
            if (Recher==NULL)
            {
                printf("\n la fiche n'existe pas dans la liste des fiches");
            }
            else
                afficher_Fiche(Recher->Element);
            break;
        }
        case 4 :
        {
            Recher=Rechercher_Fiche(ListeFiche);
            if (Recher==NULL)
            {
                printf("\n la fiche n'existe pas dans la liste des fiches");
            }
            else
            {
                Modifier_Fiche(&Recher->Element);
                printf("Modification effectué avec succes\n");
                trier(ListeFiche);
                afficher_Fiche(Recher->Element);
            }
            break;
        }
        case 5 :
        {
            Recher=Rechercher_Fiche(ListeFiche);
            if (Recher==NULL)
            {
                printf("\n la fiche n'existe pas dans la liste des fiches");
            }
            else
            {
                Suprimer_Fiche(&ListeFiche,Recher->Element);
                printf("Supression effectue avec succes\n");
                affiche_Liste_Fiche(ListeFiche);
            }
            break;

        }
        case 6 :
        {
            affiche_Liste_Fiche(ListeFiche);
            break;
        }
        case 7:
        {
            Calcul_Montant(ListeFiche);
            break;
        }
        case 0 :
        {
            fichier=fopen("Liste des fiches de paie.txt","w");
            enregistrer(fichier,ListeFiche);
            fclose(fichier);
            exit(1);
        }
        default:
            printf("choix erroné");
        }
    }
    return 0;
}
