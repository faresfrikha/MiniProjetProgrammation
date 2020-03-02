#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <time.h>
#include <ctype.h>

enum Mois
{Janvier,Fevrier,Mars,Avril,Mai,Juin,Juillet,Aout,Septembre,Octobre,Novembre,Decembre};

typedef struct Emp
{
    int num_CNSS;
    char Nom[20];
    char Prenom[20];
    char Grade[20];
} Employer;

typedef struct FP
{
    char numero[30];
    float salaire;
    enum Mois mois;
    Employer Emp;
} Fiche_De_Paie;

int existenum(Fiche_De_Paie fi[],int N,char num[])
{
    int i;
    for(i=0; i<N; i++)
        if(!strcmp(num,((fi[i]).numero)))
        {
            return 1;
        }
    return 0;
}

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

void Ajouter_Fiche(Fiche_De_Paie *fi,int *N,int *num)
{
    time_t intps;
    struct tm * tm;
    intps = time(NULL);
    tm = localtime(&intps);
    Fiche_De_Paie fich;
    char cmois[10],cann[10];
    sprintf(fich.numero,"%d",*num);
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
    fi[*N]=fich;
    (*N)++;
    (*num)++;
}

void Lire_Fiche(Fiche_De_Paie *TabFiches,int *N,int *num)
{
    char ch[205];
    int m,i;
    FILE *fichier;
    fichier=fopen("Liste des fiches de paie.txt","r");
    fscanf(fichier,"%s",ch);
    while (!feof(fichier))
    {
        fscanf(fichier,"%s%s",ch,(TabFiches[*N]).numero);
        char str [3]="";
        for(i=0; (TabFiches[*N].numero[i])!='_'; i++)
        {
            str[i]=TabFiches[*N].numero[i];
        }
        if(atoi(str)>(*num))
        {
            *num=atoi(str);
        }
        fscanf(fichier,"%s%d",ch,&(TabFiches[*N]).Emp.num_CNSS);
        fscanf(fichier,"%s%s",ch,(TabFiches[*N]).Emp.Nom);
        fscanf(fichier,"%s%s",ch,(TabFiches[*N]).Emp.Prenom);
        fscanf(fichier,"%s%s",ch,(TabFiches[*N]).Emp.Grade);
        fscanf(fichier,"%s%f",ch,&(TabFiches[*N]).salaire);
        fscanf(fichier,"%s%d",ch,&m);
        (TabFiches[*N]).mois=m;
        (*N)++;
    }
    (*num)++;
    fclose(fichier);
}

void Ecrire_Fiche(Fiche_De_Paie *TabFiches,int N)
{
    FILE *fichier;
    int i;
    fichier=fopen("Liste des fiches de paie.txt","w");
    fprintf(fichier,"\tListe_des_fiches_de_paie\n");
    for( i=0; i<N; i++)
    {
        fprintf(fichier,"\nNumero_Fiche: %s\n",(TabFiches[i]).numero);
        fprintf(fichier,"Numero_CNSS: %d\n",(TabFiches[i]).Emp.num_CNSS);
        fprintf(fichier,"Nom: %s\n",(TabFiches[i]).Emp.Nom);
        fprintf(fichier,"Prenom: %s\n",(TabFiches[i]).Emp.Prenom);
        fprintf(fichier,"Grade: %s\n",(TabFiches[i]).Emp.Grade);
        fprintf(fichier,"Salaire: %.3f\n",(TabFiches[i]).salaire);
        fprintf(fichier,"Mois %d",(TabFiches[i]).mois);
        if(i<N-1)
        {
            fprintf(fichier,"\n");
        }
    }
    fclose(fichier);
}

void Affiche_Fiches(Fiche_De_Paie *TabFiches,int N)
{
    int i;
    printf("\tListe des fiches de paie\n");
    for( i=0; i<N; i++)
    {
        printf("\nFiche N° %s\n",(TabFiches[i]).numero);
        printf("N° CNSS: %d\n",(TabFiches[i]).Emp.num_CNSS);
        printf("Nom: %s\n",(TabFiches[i]).Emp.Nom);
        printf("Prenom: %s\n",(TabFiches[i]).Emp.Prenom);
        printf("Grade: %s\n",(TabFiches[i]).Emp.Grade);
        printf("Salaire: %.3f\n",(TabFiches[i]).salaire);
        printf("Mois: %d\n",(TabFiches[i]).mois);
    }
}

void Affiche_Fiche(Fiche_De_Paie *TabFiches,int N)
{
    int i;
    char num[30];
    do
    {
        printf("Entrer le numero de la fiche: ");
        scanf("%s",num);
    }
    while(!existenum(TabFiches,N,num));
    printf("\tFiches de paie N°%s\n",num);
    for( i=0; i<N; i++)
    {
        if(!strcmp(num,TabFiches[i].numero))
        {
            printf("\nFiche N° %s\n",(TabFiches[i]).numero);
            printf("N° CNSS: %d\n",(TabFiches[i]).Emp.num_CNSS);
            printf("Nom: %s\n",(TabFiches[i]).Emp.Nom);
            printf("Prenom: %s\n",(TabFiches[i]).Emp.Prenom);
            printf("Grade: %s\n",(TabFiches[i]).Emp.Grade);
            printf("Salaire: %.3f\n",(TabFiches[i]).salaire);
            printf("Mois: %d\n",(TabFiches[i]).mois);
            return;
        }
    }
}

void Recherche(Fiche_De_Paie *fi,int N)
{
    Fiche_De_Paie fich[50];
    int p=0,i, cnss;
    printf("Entrer le numero CNSS de l'employer: ");
    scanf("%d",&cnss);
    for(i=0; i<N; i++)
    {
        if(fi[i].Emp.num_CNSS==cnss)
        {
            fich[p]=fi[i];
            p++;
        }
    }
    if(!p)
        printf("Fiche introuvable.\n");
    else
    {
        for(i=0; i<p; i++)
            Affiche_Fiches(fich,p);
        printf("\n");
    }
}

void Changer(Fiche_De_Paie *fi,int N)
{
    int ans,i;
    char num[30];
    do
    {
        printf("Entrer le numero de la fiche de paie: ");
        scanf("%s",num);
    }
    while(!existenum(fi,N,num));
    for(i=0; i<N; i++)
    {
        if(!strcmp((fi[i]).numero,num))
        {
            break;
        }
    }
    while(ans)
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
                scanf("%f",&(fi[i]).salaire);
            }
            while((fi[i]).salaire<=0);
            break;
        }
        case 2:
        {
            printf("Entrer le nouveau numero CNSS: ");
            scanf("%d",&(fi[i]).Emp.num_CNSS);
            break;
        }
        case 3:
        {
            do
            {
                printf("Entrer le nouveau nom: ");
                scanf("%s",(fi[i]).Emp.Nom);
            }
            while(!verifstr(fi[i].Emp.Nom));
            break;
        }
        case 4:
        {
            do
            {
                printf("Entrer le nouveau prenom: ");
                scanf("%s",(fi[i]).Emp.Prenom);
            }
            while(!verifstr(fi[i].Emp.Prenom));
            break;
        }
        case 5:
        {
            printf("Entrer le nouveau grade: ");
            scanf("%s",(fi[i]).Emp.Grade);
            break;
        }
        }
    printf("Changement effectue avec succes.\n\n");
    }
}

void Supprimer(Fiche_De_Paie *fi,int *N)
{
    int i,j;
    char num[30];
    do
    {
        printf("Entrer le numero de la fiche de paie: ");
        scanf("%s",num);
    }
    while(!existenum(fi,*N,num));
    for(i=0; i<*N; i++)
    {
        if(!strcmp((fi[i]).numero,num))
        {
            break;
        }
    }
    for(j=i; j<*N-1; j++)
    {
        fi[j]=fi[j+1];
    }
    (*N)--;
    printf("Suppression effectue avec succes.\n");
}

void Calcul_Montant(Fiche_De_Paie *fi,int N)
{
    float ans =0;
    int i,m;
    do
    {
        printf("Entrer le mois (exemple 1 pour Janvier): ");
        scanf("%d",&m);
    }
    while(m<=0&&m>=13);
    for(i=0; i<N ; i++)
    {
        if(fi[i].mois==m)
        {
            ans+=fi[i].salaire;
        }
    }
    printf("Le montant total des salaires est %.3f \n",ans);
}

void tri(Fiche_De_Paie *fi,int N)
{
    int i;
    for(i=0; i<N; i++)
    {
        Fiche_De_Paie x=(fi[i]);
        int j=i;
        while(x.salaire<(fi[j-1]).salaire&&j>0)
        {
            (fi[j])=(fi[j-1]);
            j--;
        }
        (fi[j])=x;
    }
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

int main()
{
    Fiche_De_Paie TabFiches[50];
    FILE *fichier;
    int N=0,c,num=1;
    entete();
    if(!((fichier=fopen("Liste des fiches de paie.txt","r"))==NULL))
    {
        Lire_Fiche(TabFiches,&N,&num);
        fclose(fichier);
    }
    while(1)
    {
        printf("\n\n******************************");
        printf("\n******* Menu aux choix *******");
        printf("\n******************************\n\n");
        printf("1 ====> Ajouter une fiche de paie\n");
        printf("2 ====> Chercher toutes les fiches de paie d'un employer\n");
        printf("3 ====> Changer une donnee dans une fiche de paie\n");
        printf("4 ====> Supprimer une fiche de paie\n");
        printf("5 ====> Calculer le montant total de tous les salaires d’un mois\n");
        printf("6 ====> Afficher toutes les fiches de paie\n");
        printf("7 ====> Afficher une fiche de paie\n");
        printf("0 ====> Enregistrer et Sortir\n");
        printf("\nChoisir un numero:\n");
        scanf("%d",&c);
        switch(c)
        {
        case 0:
        {
            Ecrire_Fiche(TabFiches,N);
            return 0;
        }
        case 1:
        {
            Ajouter_Fiche(TabFiches,&N,&num);
            tri(TabFiches,N);
            break;
        }
        case 2:
        {
            Recherche(TabFiches,N);
            break;
        }
        case 3:
        {
            Changer(TabFiches,N);
            tri(TabFiches,N);
            break;
        }
        case 4:
        {
            Supprimer(TabFiches,&N);
            break;
        }
        case 5:
        {
            Calcul_Montant(TabFiches,N);
            break;
        }
        case 6:
        {
            Affiche_Fiches(TabFiches,N);
            break;
        }
        case 7:
        {
            Affiche_Fiche(TabFiches,N);
            break;
        }
        default:
        {
            printf("Entrer un numero entre 0 et 7\n");
            break;
        }
        }
    }
}
