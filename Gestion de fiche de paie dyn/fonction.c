#include "fonction.h"
#include "malloc.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int verifstr(char ch[])
{
    int i;
    for(i=0; i<strlen(ch); i++)
    {
        if(!isalpha(ch[i]))
        {
            return 0;
        }
    }
    return 1;
}

Fiche_De_Paie saisir_Fiche(int num)
{
    Fiche_De_Paie fich;
    time_t intps;
    struct tm * tm;
    intps = time(NULL);
    tm = localtime(&intps);
    char cmois[10],cann[10];
    sprintf(fich.numero,"%d",num);
    sprintf(cmois,"%d",tm->tm_mon+1);
    sprintf(cann,"%d",tm->tm_year-100);
    strcat(fich.numero,"_");
    strcat(fich.numero,cmois);
    strcat(fich.numero,"_");
    strcat(fich.numero,cann);
    printf("Entrer les informations de la fiche de paie N° %s\n",fich.numero);
    do
    {
        printf("Entrer le salaire: ");
        scanf("%f",&fich.salaire);
    }
    while(fich.salaire<=0);
    fich.mois=tm->tm_mon+1;
    do
    {
        printf("Entrer le nom de l'employer: ");
        scanf("%s",fich.Emp.Nom);
    }
    while(!verifstr(fich.Emp.Nom));
    do
    {
        printf("Entrer le prenom de l'employer: ");
        scanf("%s",fich.Emp.Prenom);
    }
    while(!verifstr(fich.Emp.Prenom));
    printf("Entrer le numero de CNSS de l'employer: ");
    scanf("%d",&fich.Emp.num_CNSS);
    printf("Entrer la grade de l'employer: ");
    scanf("%s",fich.Emp.Grade);
    return fich;
}

void afficher_Fiche(Fiche_De_Paie F)
{
    printf("\nFiche N° %s\n",F.numero);
    printf("N° CNSS: %d\n",F.Emp.num_CNSS);
    printf("Nom: %s\n",F.Emp.Nom);
    printf("Prenom: %s\n",F.Emp.Prenom);
    printf("Grade: %s\n",F.Emp.Grade);
    printf("Salaire: %.3f\n",F.salaire);
    printf("Mois: %d\n",F.mois);
}

void affiche_Liste_Fiche(Liste ListeFiche)
{
    Noeud* courrant;
    courrant=ListeFiche.Debut;

    while (courrant!=NULL)
    {
        afficher_Fiche(courrant->Element);
        courrant=courrant->Suivant;
    }
}

void Ajouter_Fiche_Liste(Liste* ListeFiche,Fiche_De_Paie F)
{
    Noeud* courrant;
    courrant=(Noeud*)malloc(sizeof(Noeud));
    courrant->Element=F;
    courrant->Suivant=ListeFiche->Debut;
    ListeFiche->Debut=courrant;
}

Noeud* Rechercher_Fiche(Liste ListeFiche)
{
    Noeud* courrant=ListeFiche.Debut;
    char nomrech [20];
    printf("introduire le numero de la fiche à rechercher:");
    scanf("%s",nomrech);
    while (courrant!=NULL)
    {
        if (!strcmp(nomrech,courrant->Element.numero))
        {
            return courrant;
        }
        courrant=courrant->Suivant;
    }
    return courrant;
}

void insertAtTheBegin(Noeud **start_ref, int data)
{
    Noeud *ptr1 = (Noeud*)malloc(sizeof(Noeud));
    ptr1->Element.salaire = data;
    ptr1->Suivant = *start_ref;
    *start_ref = ptr1;

}

void swap( Noeud *a,  Noeud *b)
{
    Fiche_De_Paie temp = a->Element;
    a->Element = b->Element;
    b->Element = temp;
}

void trier(Liste ListeFiche)
{
    Noeud *start=ListeFiche.Debut;
    int swapped;
    Noeud *ptr1;
    Noeud *lptr = NULL;
    if (start == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;
        while (ptr1->Suivant != lptr)
        {
            if (ptr1->Element.salaire > ptr1->Suivant->Element.salaire)
            {
                swap(ptr1,ptr1->Suivant);
                swapped = 1;
            }
            ptr1 = ptr1->Suivant;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void Modifier_Fiche(Fiche_De_Paie* F)
{
    int ans;
    while(1)
    {
        printf("Choisir un numero pour: \n");
        printf("1 ===> Changer le montant du salaire\n");
        printf("2 ===> Changer le numero CNSS\n");
        printf("3 ===> Changer le nom\n");
        printf("4 ===> Changer le prenom\n");
        printf("5 ===> Changer le grade\n");
        printf("0 ===> Terminer\n");
        printf("Entrer le numero du commande correspondante: ");
        scanf("%d",&ans);
        switch(ans)
        {
        case 1:
        {
            do
            {
                printf("Entrer le nouveau montant: ");
                scanf("%f",&F->salaire);
            }
            while(F->salaire<=0);
            break;
        }
        case 2:
        {
            printf("Entrer le nouveau numero CNSS: ");
            scanf("%d",&F->Emp.num_CNSS);
            break;
        }
        case 3:
        {
            do
            {
                printf("Entrer le nouveau nom: ");
                scanf("%s",F->Emp.Nom);
            }
            while(!verifstr(F->Emp.Nom));
            break;
        }
        case 4:
        {
            do
            {
                printf("Entrer le nouveau prenom: ");
                scanf("%s",F->Emp.Prenom);
            }
            while(!verifstr(F->Emp.Prenom));
            break;
        }
        case 5:
        {
            printf("Entrer le nouveau grade: ");
            scanf("%s",F->Emp.Grade);
            break;
        }
        case 0:
        {
            return;
        }
        }
    }
    printf("Changement effectue avec succes.\n");

}

void Suprimer_Fiche(Liste* ListeFiche,Fiche_De_Paie F)
{
    Noeud* courrant=ListeFiche->Debut;
    Noeud* precedent=NULL;
    while (courrant!=NULL)
    {
        if (!strcmp(courrant->Element.numero,F.numero))
        {
            if (precedent!=NULL)
                precedent->Suivant=courrant->Suivant;
            else
                ListeFiche->Debut=courrant->Suivant;
            free(courrant);
            break;
        }
        precedent=courrant;
        courrant=courrant->Suivant;
    }
}

void enregistrer(FILE* fichier,Liste ListeFiche)
{
    Noeud* courrant;
    courrant=ListeFiche.Debut;
    fprintf(fichier,"\tListe_des_fiches_de_paie\n");
    while (courrant!=NULL)
    {
        fprintf(fichier,"\nNumero_Fiche: %s\n",courrant->Element.numero);
        fprintf(fichier,"Numero_CNSS: %d\n",courrant->Element.Emp.num_CNSS);
        fprintf(fichier,"Nom: %s\n",courrant->Element.Emp.Nom);
        fprintf(fichier,"Prenom: %s\n",courrant->Element.Emp.Prenom);
        fprintf(fichier,"Grade: %s\n",courrant->Element.Emp.Grade);
        fprintf(fichier,"Salaire: %.3f\n",courrant->Element.salaire);
        fprintf(fichier,"Mois %d",courrant->Element.mois);
        courrant=courrant->Suivant;
    }
}

void telecharger(FILE* fichier,Liste* ListeFiche,int* num)
{
    Noeud* courrant;
    char ch[20];
    int m,i;
    fscanf(fichier,"%s",ch);
    while(!feof(fichier))
    {
        courrant=(Noeud*)malloc(sizeof(Noeud));
        fscanf(fichier,"%s%s",ch,courrant->Element.numero);
        char str[3]="";
        for(i=0; (courrant->Element.numero[i])!='_'; i++)
        {
            str[i]=courrant->Element.numero[i];
        }
        if(atoi(str)>(*num))
        {
            *num=atoi(str);
        }
        fscanf(fichier,"%s%d",ch,&courrant->Element.Emp.num_CNSS);
        fscanf(fichier,"%s%s",ch,courrant->Element.Emp.Nom);
        fscanf(fichier,"%s%s",ch,courrant->Element.Emp.Prenom);
        fscanf(fichier,"%s%s",ch,courrant->Element.Emp.Grade);
        fscanf(fichier,"%s%f",ch,&courrant->Element.salaire);
        fscanf(fichier,"%s%d",ch,&m);
        courrant->Element.mois=m;
        courrant->Suivant=ListeFiche->Debut;
        ListeFiche->Debut=courrant;
        //fscanf(fichier,"%s",ch);
    }
}

void Calcul_Montant(Liste ListeFiche)
{
    float ans =0;
    int m;
    Noeud* courrant=ListeFiche.Debut;
    do
    {
        printf("Entrer le mois (exemple 1 pour Janvier): ");
        scanf("%d",&m);
    }
    while(m<=0&&m>=13);
    while (courrant!=NULL)
    {
        if(courrant->Element.mois==m)
        {
            ans+=courrant->Element.salaire;
        }
        courrant=courrant->Suivant;
    }
    printf("Le montant total des salaires est %.3f \n",ans);
}

void entete()
{
    printf("\t\t\t\t\t\t\t\t\t\t\t\tMini Projet C\n\n");
    printf("\t\t\t\t\t\t\t\t\t\tSujet: \t\t\t\t\tGestion de fiche de paie\n\n");
    printf("\t\t\t\t\t\t\t\t\t\tNom: \t\t\t\t\tFRIKHA\n");
    printf("\t\t\t\t\t\t\t\t\t\tPrenom: \t\t\t\tFares\n");
    printf("\t\t\t\t\t\t\t\t\t\tClasse: \t\t\t\t1AGC2\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t   Ecole Nationale d'Ingenieur de Tunis\n\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t******************************************\n");
    printf("\t\t\t\t\t\t\t\t\t\t******************************************\n");
    printf("\t\t\t\t\t\t\t\t\t\t*********Gestion de fiche de paie*********\n");
    printf("\t\t\t\t\t\t\t\t\t\t******************************************\n");
    printf("\t\t\t\t\t\t\t\t\t\t******************************************\n");
    printf("\n\t\t\t\t\t\t\t\t\t\tB    I    E    N    V    E    N    U    E!\n\n");
}
