#include <stdio.h>
#include "mylib.h"
#include <stdlib.h>
#include <time.h>

extern int chiudi;				// dichiaro una variabile chiudi che serve per il cambio del menu' in caso sia 0 o 1
void Continua();					// prototipo funzione continua
extern int contatore;           

int main(){

	system("tput clear");
	time_t t;
	srand((unsigned) time(&t));	// inzializzo il generatore di numeri casuali utilizzando il tempo attuale
	
	int inputmenu;			//variabile per entrare nel menù
	do{
		do{
			printf(	"\t\t\t**********************\n"
					"\t\t\t*////////////////////*\n"
					"\t\t\t*//****************//*\n"
					"\t\t\t*//*IL MAGO OBERON*//*\n"
					"\t\t\t*//****************//*\n"
					"\t\t\t*////////////////////*\n"
					"\t\t\t**********************\n");
		
			printf("Cosa vuoi fare?\n\n1.crea percorso\n2.muovi Oberon\n3.termina gioco\n");	
			scanf("%d",&inputmenu);
			switch(inputmenu){
				case 1:system("tput clear");
						if(chiudi==0){
							crea_percorso();
						}else{
							printf("\t    ***Attenzione: il percorso è già stato creato***\n");
							Continua();
						}
				break;
				case 2:	system("tput clear");
						if(chiudi==0){
							printf("\t    ***Attenzione: prima si deve creare il percorso***\n");
							Continua();
						}
						else{
								muovi_Oberon();
							}
						
				break;
				case 3:	system("tput clear");
						termina_gioco();
				break;
				default:system("tput clear");
						printf("\t\t\t***Comando non trovato***\n");
						Continua();
				break;
			}		
		}while(inputmenu<1 || inputmenu>3);
	}while(chiudi==0 || chiudi==1); //condizione per rientrare nel menù un seconda volta
	
}
	
