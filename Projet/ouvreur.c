#include "header.h"


void recup_chemin(int nb)
{
// nb représente la fonction suivante à lancer (enregistrer ou ouvrir)
if (nb!=1 || nb!=2)
{
printf("Erreur appel fonction de récupréation du chemin, mauvais argument");
exit();
}
char chemin;

printf("Veuillez saisir l'adresse exacte du fichier à ouvrir : \n");
scanf("%s",chemin);
getchar();

if (nb==1)
{
charger(chemin);
}
else if(nb==2)
{
historique(chemin);
}
}

void charger(char chemin)
{

FILE * fic=NULL;
fic=fopen(chemin,"r");
char ligne[100];
if(fic!=NULL)
{
}


}

void historique(char chemin)
{

FILE * fic=NULL;
fic=fopen(chemin,"r");
char ligne[100];
if(fic!=NULL)
{
}


}

