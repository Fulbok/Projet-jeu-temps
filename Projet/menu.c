#include "header.h"

int thread_menu()
    {
    int choix,error=1;
    while(1)
        {

        system("clear");

        printf("\t Menu du jeu : %d\n",error);
        printf("1. Nouvelle partie\n");
        printf("2. Charger une partie\n");
        printf("3. Interrompre la partie & Sauvegarder\n");
        printf("4. Pause\n");
        printf("5. Reprendre la partie\n");
        printf("6. Historique\n");
        printf("7. Quitter l'application\n\n");

        if(error==0)
        {
        printf("\n\nTu ne sais pas lire abruti ?...\n\n");
        error=1;
        }

        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch(choix)
            {
            case 1 : Nvlle_partie();break;
            case 2 : recup_chemin(1);break;
            case 3 : interrupt();break;
            case 4 : pause();break;
            case 5 : resume();break;
            case 6 : recup_chemin(2);break;
            case 7 : quitter();break;
            default :error=0;
            }


        }





    }
void Nvlle_partie(){}

void interrupt(){}
void pause(){}
void resume(){}
void quitter (){
exit(1);
}


