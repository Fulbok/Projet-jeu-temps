#include "header.h"

extern param_structure * param;


int thread_menu()
{

    int choix;
    while(1)
    {
        afficher_menu(MENU_);

        scanf("%d", &choix);
        purger();

        switch(choix)
        {
            case 1 : Nvlle_partie();break;
            case 2 : recup_chemin(CHARGER_);break;
            case 3 : recup_chemin(HISTORIQUE_);break;
            case 4 : quitter();break;
            default :printf("\n\nMauvaise saisie.\n\n");
        }
    }
}


void Nvlle_partie(){


    char joueur1[8]="", joueur2[8]="";
    int tps_global=0, tps_joueur=0;

    int error1=1, error2=1,retour; /* retour du scanf*/
    int cond=0;

    printf("\n\n\t >>>>Nouvelle partie<<<< \n");

    //saisie des noms des 2 joueurs
    while(error1)
    {
        printf("Nom joueur 1 (doit être inférieur à 8 caractères) : ");
        scanf("%s", joueur1);
        purger();

        if((strlen(joueur1) >= 1) && (strlen(joueur1) <= 8) )
            {
            error1=0;
            }

     /*le nom ne doit pas dépasser 8 caractères, si c'est le cas recommence la saisie*/
     }
    strcpy(param->joueur1,joueur1);

     while(error2)
    {
        printf("Nom joueur 2 (doit être inférieur à 8 caractères) : ");
        scanf("%s", joueur2);
        purger();
        if((strlen(joueur2) >= 1) && (strlen(joueur2) <= 8))
            {
            error2=0;
            }
        if(strcmp(param->joueur1,joueur2)==0)
            {
            printf("Euuh, c'est un jeu pour 2 joueurs, tu ne peux pas jouer contre toi-même.\n");
            error2=1;
            }
     /*le nom ne doit pas dépasser 8 caractères, si c'est le cas, recommence la saisie*/
     }
     strcpy(param->joueur2,joueur2);

    //Saisie différents temps de jeu.
   /* while(error_timeG)*/
    {
        printf("Définir le temps de la partie (en secondes) : ");


    while (!cond)
    {
        retour = scanf("%d%*[^\n]", &tps_global);
        purger();

        if ( !retour )
        {
            /* erreur de saisie */
            printf("On vous a demande de saisir un nombre\n");
            printf("Veuillez recommencer : ");
        }
        else
        {
            /* reussite de la saisie */
            cond = 1;  /* sort de la boucle */
        }

    }


    printf("Le temps de la partie est de %d secondes\n", tps_global);
    param->tps_global=tps_global;

    cond=0; /* réinitialise cond*/

    printf("Définir le temps pour un coup (en secondes) : ");

    while (!cond)
    {
        retour = scanf("%d%*[^\n]", &tps_joueur);
        purger();

        if ( !retour )
        {
            /* erreur de saisie */
            printf("On vous a demandé de saisir un nombre.\n");
            printf("Veuillez recommencer : ");
        }
        else if(tps_joueur>tps_global)
        {
            printf("Le temps pour un coup ne peut être supérieur au temps global.\n");
            printf("Veuillez recommencer : ");
        }
        else
        {
            /* reussite de la saisie */
            cond = 1;  /* sort de la boucle */
        }

    }
        printf("Le temps par coup est de %d secondes\n", tps_joueur);
        param->tps_joueur=tps_joueur;

    }

    // On initialise le thread temps avec le temps de la partie puis on lance le jeu
    printf("\n\tLa partie va se lancer, appuyer sur Entrée...\n");
    purger();
    init_temps();

}

void purger()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void afficher_menu(int type)
{
system("clear");
fflush(stdout);

if(type==MENU_)
{
    printf("\t\t Menu du jeu : \n\n");
    printf("\t1. Nouvelle partie\n");
    printf("\t2. Charger une partie\n");
    printf("\t3. Historique\n");
    printf("\t4. Quitter l'application\n\n\n");

    printf("Votre choix : ");
}
if(type==JEU_)
{
    printf("\t\t Menu du jeu : \n\n");
    printf("\t1. Interrompre la partie & Sauvegarder\n");
    printf("\t2. Pause\n");
    printf("\t3. Quitter l'application\n\n\n");

    printf("Partie en cours : \n\n\n\n\t   ");
    commandes();
}
if(type==PAUSE_)
{
    printf("\t\t Menu du jeu : \n\n");
    printf("\t1. Interrompre la partie & Sauvegarder\n");
    printf("\t2. Reprendre la partie\n");
    printf("\t3. Quitter l'application\n\n\n");

    printf("Partie en pause : \n\n\n");
}

}

void commandes()
{
    printf("%c7\x1b[20;0H", '\x1b');
    printf("Commandes : \n");
    printf("/valide  : joue un coup valide.\n");
    printf("/mauvais : tente de jouer un coup non valide.\n");
    printf("/gagnant : joue un coup gagnant. (permet de quitter la partie)");
    printf("%c8", '\x1b');
    fflush(stdout);

    return;
}

void liberer()
{

// Libération de la mémoire et réinitialisation des variables
etape* pt1= param->debut_jeu;
while(pt1!=NULL)
{
    etape* pt2=pt1->ptsuiv;
    free(pt1);
    pt1=pt2;
}

param->debut_jeu=NULL;
param->fin_jeu=NULL;
strcpy(param->joueur1,"");
strcpy(param->joueur2,"");
param->tps_global=0;
param->tps_joueur=0;
}


void quitter ()
{
liberer();

exit(1);
}

