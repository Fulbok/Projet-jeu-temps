#include "header.h"


void recup_chemin(int nb)
{
// nb représente la fonction suivante à lancer (enregistrer ou ouvrir)
if (nb!=1 && nb!=2)
{
printf("Erreur appel fonction de récupréation du chemin, mauvais argument.");
exit(0);
}
char chemin[100];

printf("\nVeuillez saisir l'adresse exacte du fichier à ouvrir : \n");
scanf("%s",chemin);
getchar();

FILE * fic=NULL;
fic=fopen(chemin,"r");
char ligne[100];
if(fic!=NULL)
{
    fscanf(fic,"%[^\n]",ligne);
    printf("%s",ligne);
    getchar();

    int k=2;

    if(ligne[0]=='H' || ligne[1]=='X' || strlen(ligne)>39)
    {
        if (nb==1)
        {
            charger(chemin,fic);
        }
        else if(nb==2)
        {
            historique(chemin,fic);
        }
    }
    else
    {
    printf("Mauvais fichier.");
    getchar();
    }

}




}

void charger(char* chemin,FILE* fic)
{



}

void historique(char* chemin,FILE* fic)
{



}

