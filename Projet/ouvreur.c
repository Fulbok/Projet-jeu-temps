#include "header.h"

extern param_structure * param;

int recup_chemin(int type)
{
printf("\nLes fichiers disponibles dans ce répertoire sont : \n");
system("find . -name \"*.histo\"");
//system("ls -R | grep .histo$");

// nb représente la variable qui va déterminer s'il faut charger ou afficher le fichier.
if (type!=CHARGER_ && type!=HISTORIQUE_)
{
    printf("Erreur appel fonction de récupréation du chemin, mauvais argument.");
    return ERREUR;
}

char chemin[100];

// Saisie du nom du fichier
printf("\nVeuillez saisir l'adresse du fichier à ouvrir (sans l'extension) : \n");
scanf("%s",chemin);
purger();


// Ajout de l'extension
strcat(chemin,".histo");

// Ouverture du fichier
FILE * fic=NULL;
fic=fopen(chemin,"r");


if(fic!=NULL)
{
    int nb_saisie=0;
    char hx[2],ligne[100],verif[100];

    // Lecture de la première ligne
    fscanf(fic,"%[^\n]",ligne);
    fgetc(fic);

    // Découpage
    sscanf(ligne,"%2s%8s %8s %4d%4d",hx,param->joueur1,param->joueur2,&param->tps_global,&param->tps_joueur);

    // Vérification pour détecter les espaces qui auraient disparus
    sprintf(verif,"%s%8s %8s %04d%04d",hx,param->joueur1,param->joueur2,param->tps_global,param->tps_joueur);
    nb_saisie=strcmp(ligne,verif);

    // Vérification du HX
    if (nb_saisie!=0)
    {
        printf("\nLe fichier n'est pas du bon format.\n");
        purger();
        return ERREUR;
    }


    char coup[8],joueur[9],joueur_precedant[9]="";
    int restant,assigne,i=1;
    int restant_precedant=param->tps_global;
    etape * nouveau;

    fscanf(fic,"%[^\n]",ligne);

    while(strcmp(ligne,"FIN")!=0)
    {
        // Test si la fin du fichier est incorrecte
        if(fgetc(fic)==EOF)
        {
            printf("Erreur sur le format du fichier.");
            purger();
            return ERREUR;
        }

        assigne=sscanf(ligne,"%4d%8c%s",&restant,joueur,coup);
        joueur[8]='\0';

        while(joueur[0]==' ')
        {
            int j;
            for(j=0;j<strlen(joueur);j++)
            {
                joueur[j]=joueur[j+1];
            }
            joueur[strlen(joueur)]='\0';
        }

        // Vérification de lecture
        if(restant>restant_precedant || assigne !=3 || strcmp(joueur,joueur_precedant)==0 || (strcmp(joueur,param->joueur1)!=0 && strcmp(joueur,param->joueur2)!=0) || strlen(coup)>6 || (restant_precedant -restant)>param->tps_joueur)
        {
//            printf("res=%d | res_prc=%d | assi=%d | j=%s | j1=%s | j2=%s | strl=%d",restant,restant_precedant,assigne,joueur,param->joueur1,param->joueur2,strlen(coup));
            printf("\nUne erreur est survenue dans le fichier ligne %d.\n",i+1);
            purger();
            return ERREUR;
        }

        // Si on veut juste afficher pour l'historique
        if(type==HISTORIQUE_ && restant>=60)
        {
            printf("\nTour n°%d : \n",i);
            printf("%8s joue %s, il reste %d min %d sec\n",joueur,coup,(restant-restant%60)/60,restant%60);
        }
        else if(type==HISTORIQUE_)
        {
            printf("\nTour n°%d : \n",i);
            printf("%8s joue %s, il reste %d sesondes\n",joueur,coup,restant);
        }
        // Si on veut charger les données.
        else
        {
            if(param->debut_jeu==NULL)
            {
                // Première allocation
                nouveau=malloc(sizeof(etape));
                param->debut_jeu=nouveau;
                param->fin_jeu=nouveau;
                nouveau->ptsuiv=NULL;
            }
            else
            {
                // Allocation
                param->fin_jeu->ptsuiv=malloc(sizeof(etape));
                param->fin_jeu=param->fin_jeu->ptsuiv;
                param->fin_jeu->ptsuiv=NULL;
                nouveau=param->fin_jeu;
            }

            // Remplissage
            nouveau->restant=restant;
            strcpy(nouveau->joueur,joueur);
            strcpy(nouveau->coup,coup);
        }

        // Préparation de la boucle suivante, sauvegarde des paramètres, lecture de la ligne suivante
        i++;
        strcpy(joueur_precedant,joueur);
        restant_precedant=restant;

        fscanf(fic,"%[^\n]",ligne);
    }

    if(type==HISTORIQUE_)
    {
        printf("\n Fin de l'historique.\n");
        purger();
    }
    else
    {
        // Début du jeu
        printf("\n\tLa partie va se lancer, appuyer sur Entrée...\n");
        purger();
        init_temps();
    }

}
else
{
        printf("Fichier inexistant\n");
        purger();
        return ERREUR;
}

return OK;
}



int sauvegarder()
{
char chemin[50];

// On vérifie qu'il y a des données (normalement c'est toujours le cas)
if(param->debut_jeu==NULL)
{
    printf("Pas de données à sauvegarder.");
    purger();
    return ERREUR;
}

// Saisie du nom du fichier
printf("\nVeuillez saisir l'adresse du fichier à sauvegarder (sans l'extension) : \n");
scanf("%s",chemin);
scanf("%*[^\n]");
purger();

// Ajout de l'extension
strcat(chemin,".histo");

// Ouverture en lecture pour eviter un écrasement involontaire
FILE * fic=NULL;
fic=fopen(chemin,"r");

if(fic!=NULL)
{
    fclose(fic);
    char choix;

    // On vérifie que l'utilisateur veut ecraser ou non le fichier déjà existant
    while(choix!='O')
    {
        printf("Le fichier existe déjà voulez vous l'écraser ? [Oui (O), Non (N)]\n");
        scanf("%c%*[^\n]",&choix);
        getchar();

        choix=toupper((int) choix);

            if(choix=='N')
            {
            return ERREUR;
            }
    }
}

// Ouverture pour écriture
fic=fopen(chemin,"w");

if(fic!=NULL)
{
    // Ecriture de la première ligne
    fprintf(fic,"HX%8s %8s %04d%04d\n",param->joueur1,param->joueur2,param->tps_global,param->tps_joueur);

    etape * nouveau = param->debut_jeu;

    // Toute les lignes suivantes
    while(nouveau!=NULL)
    {
        fprintf(fic,"%04d%8s%s\n",nouveau->restant,nouveau->joueur,nouveau->coup);
        nouveau=nouveau->ptsuiv;
    }
    fprintf(fic,"FIN");

    // Libération de la mémoire dynamique
    liberer();


}
else
{
    printf("\nUne erreur s'est produite lors de la création du fichier.\n");
    purger();
    return ERREUR;
}

fclose(fic);

printf("Sauvegarde Réussie.\n");
purger();
return OK;
}

