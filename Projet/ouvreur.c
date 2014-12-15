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
    int k;

    // Vérification des données
    if(ligne[0]=='H' || ligne[1]=='X' || ligne[10]==' ' || ligne[19]==' ' || ligne[28]=='C' || ligne[29]=='R' || ligne[30]=='L' || ligne[31]=='F' || strlen(ligne)>39)
    {

    for(k=0;k<8;k++)
    {
    //param->joueur1[k]=ligne[2+k]
    }

    for(k=0;k<8;k++)
    {
    //param->joueur2[k]=ligne[11+k]
    }

    for(k=0;k<4;k++)
    {
   // param->tps_global[k]=ligne[11+k]
    }

        if (nb==1)
        {
            charger(fic,ligne);
        }
        else if(nb==2)
        {
            historique(fic,ligne);
        }
    }
    else
    {
    printf("Mauvais fichier.");
    getchar();
    }

}




}

void charger(FILE* fic,char* ligne)
{



}

void historique(FILE* fic,char* ligne)
{



}

