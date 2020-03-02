#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

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

typedef struct noeud
{
    Fiche_De_Paie Element;
    struct noeud* Suivant;
}Noeud;

typedef struct liste
{
    Noeud* Debut;
}Liste;

#endif
