#include "header.h"

extern param_structure * param;

void recup_chemin(int nb)
{
// nb représente la fonction suivante à lancer (enregistrer ou ouvrir)
if (nb!=CHARGER && nb!=HISTORIQUE)
{
printf("Erreur appel fonction de récupréation du chemin, mauvais argument.");
return ;
}

char chemin[100];
int n;

// Saisie du nom du fichier
printf("\nVeuillez saisir l'adresse exacte du fichier à ouvrir : \n");
n=scanf("%94s",chemin);
getchar();

if(n!=1){printf("mauvaise entrée!");getchar();}

// Ajout de l'extension
strcat(chemin,".histo");

// Ouverture du fichier
FILE * fic=NULL;
fic=fopen(chemin,"r");


if(fic!=NULL)
{
    int nb_saisie=0;
    char hx[2],crlf[4],ligne[100],verif[100];

    // Lecture de la première ligne
    fscanf(fic,"%[^\n]",ligne);
    printf("%s",ligne);
    getchar();

    // Découpage
    sscanf(ligne,"%2s%8s %8s %4d%4d%4s",hx,param->joueur1,param->joueur2,&param->tps_global,&param->tps_joueur,crlf);

    // Vérification pour détecter les espaces qui auraient disparus
    sprintf(verif,"%s%s %s %04d%04d%s",hx,param->joueur1,param->joueur2,param->tps_global,param->tps_joueur,crlf);
    nb_saisie=strcmp(ligne,verif);

    // Vérification du HX et du CRLF
    if (strcmp(hx,"HX")!=0 || strcmp(crlf,"CRLF")!=0 || nb_saisie!=0)
    {
        printf("\nLe fichier n'est pas du bon type.\n");
        getchar();
        return ;
    }

//    // Débug
//    printf("%s\n%s\n%d",ligne,verif,nb_saisie);
//    printf("\n%s ; %s ; %s ; %04d ; %04d ; %s ;\n",hx,param->joueur1,param->joueur2,param->tps_global,param->tps_joueur,crlf);






    getchar();

    // Exécution de la fonction correspondante
        if (nb==CHARGER)
        {
            charger(fic,ligne);
        }
        else if(nb==HISTORIQUE)
        {
            historique(fic,ligne);
        }
    }
    else
    {
    printf("Fichier inexistant");
    getchar();
    }



}

void charger(FILE* fic,char* ligne)
{



}

void historique(FILE* fic,char* ligne)
{



}

void sauvegarder()
{
char chemin[50];

if(param->debut_jeu==NULL)
{
printf("Pas de données à sauvegarder.");
getchar();
return 0;
}

// Saisie du nom du fichier
printf("\nVeuillez saisir l'adresse exacte du fichier à ouvrir : \n");
scanf("%s",chemin);
getchar();

// Ajout de l'extension
strcat(chemin,".histo");

// Ouverture en lecture pour eviter un écrasement involontaire
FILE * fic=NULL;
fic=fopen(chemin,"r");

if(fic!=NULL)
{
    fclose(fic);
    char choix;

    while(choix!='O')
    {
        printf("Le fichier existe déjà voulez vous l'écraser ? [Oui (O), Non (N)]\n");
        scanf("%c%*[^\n]",&choix);
        getchar();

        choix=toupper((int) choix);

            if(choix=='N')
            {
            return ;
            }
    }

fic=fopen(chemin,"w");

if(fic!=NULL)
{

fprintf(fic,"HX%s %s %d%dCRLF",param->joueur1,param->joueur2,param->tps_global,param->tps_joueur);

}
printf("fichier détruit");
getchar();
}


//fic=fopen(chemin,"w");
//
//fprintf(fic,"HX%s %s %d%dCRLF",param->joueur1,param->joueur2,param->tps_global,param->tps_joueur);

}
