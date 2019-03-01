#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//dichiaro i prototipi delle funzioni
static void ins_terra();
static void canc_terra();
static void stampa_percorso();
static void chiudi_percorso();
void Continua();

char *terra[6]={"","deserto","foresta","palude","villaggio","pianura"};
char *mostro[6]={"","nessuno","scheletro","lupo","orco","drago"};	

static struct Terra* percorso=NULL;					//inizializzo la prima terra a NULL NB: percorso punta alla prima terra
static struct Terra* ultima_terra=NULL;			//inizializzo l'ultima terra a NULL
static struct Oberon Oberon;							//richiamo la struttura Oberon
struct Terra* terra_successiva;			//richiamo la struttura Terra* terra_successiva
struct Terra* terra_attuale=NULL;			

int chiudi=0;							//inizializzo chiudi a 0 che servirà per la funzione "chiudi_percorso" e per il menu' in progexam.c
int inputcrea;									//inizializzo una varabile "inputcrea" che servirà da input nel menù "crea percorso"
int contatore=0;								//inizilizzo un contatore che servirà per la creazione delle varia terre

//definisco la funzione ins_terra
static void ins_terra(){
	++contatore;								//incremento il contatore di 1
		
	if(percorso==NULL){
			percorso= (struct Terra*) malloc(sizeof(struct Terra));			//Alloco spazio per la prima terra
			ultima_terra=percorso;
											//assegno ad "ultima_terra" lo spazio di memoria appena creato
	}else{
		ultima_terra->terra_successiva=(struct Terra*) malloc(sizeof(struct Terra));	//alloco spazio per la nuova terra e lo assegno al campo "terra_successiva" della terra precedente
		
		ultima_terra=ultima_terra->terra_successiva; //assegno ad "ultima_terra" lo spazio di memoria appena creato
	}				

	int tipo_terra, tipo_mostro; //creo delle variabili per assegnare il tipo di terra e di mostro e la quantità di oro 
	short int num_tesoro;
	printf("Stai crendo la terra n°%d\n\n",contatore);

	do{
		printf("Inizia scegliendo il tipo di terra tra:\n\n[1] deserto\n[2] foresta\n[3] palude\n[4] villaggio\n[5] pianura\n");
		printf("\n\n\n\nRICORDA:\n-se è la prima terra che inserisci non puoi scegliere alcun mostro\n-se hai scelto il villaggio non puoi scegliere alcun mostro\n-se hai scelto la palude non puoi scegliere lo scheletro\n-se hai scelto il deserto non puoi scegliere l'orco\n-il lupo può stare solo sulla foresta o sulla pianura\n\n");
		scanf("%u", &tipo_terra);		
		switch(tipo_terra){						//uso uno switch per assegnare la scelta dell'utente al puntatore
			case 1:ultima_terra->tipo_terra=1;
			break;
			case 2:ultima_terra->tipo_terra=2;
			break;
			case 3:ultima_terra->tipo_terra=3;
			break;
			case 4:ultima_terra->tipo_terra=4;
			break;
			case 5:ultima_terra->tipo_terra=5;
			break;
			default:system("tput clear");
					printf("\t\t\t***Comando non trovato***\n");
					Continua();
			break;
		};
		system("tput clear");
	}while(tipo_terra<1 || tipo_terra>5);

	do{
		do{
			printf("Stai crendo la terra n°%d\n",contatore);
			printf("Tipo terra [%s]\n\n",terra[ultima_terra->tipo_terra]);
			printf("Ora scegli il mostro che starà in quella terra tra:\n\n[1] nessuno\n[2] scheltro\n[3] lupo\n[4] orco\n[5] drago\n");
			printf("\n\n\n\nRICORDA:\n-se è la prima terra che inserisci non puoi scegliere alcun mostro\n-se hai scelto il villaggio non puoi scegliere alcun mostro\n-se hai scelto la palude non puoi scegliere lo scheletro\n-se hai scelto il deserto non puoi scegliere l'orco\n-il lupo può stare solo sulla foresta o sulla pianura\n\n");
			scanf("%u", &tipo_mostro);
			switch(tipo_mostro){					//uso uno switch per assegnare la scelta dell'utente al puntatore
				case 1:ultima_terra->tipo_mostro=1;
				break;
				case 2:ultima_terra->tipo_mostro=2;
				break;
				case 3:ultima_terra->tipo_mostro=3;
				break;
				case 4:ultima_terra->tipo_mostro=4;
				break;
				case 5:ultima_terra->tipo_mostro=5;
				break;
				default:system("tput clear");
						printf("\t\t\t***Comando non trovato***\n");
						Continua();
				break;
			};
		}while(tipo_mostro<1 || tipo_mostro>5);

		system("tput clear");

		if(contatore==1 && ultima_terra->tipo_mostro!=1){				//controllo ogni vincolo e stampo l'errore corrsipondente
			printf("\t\t\t***Attenzione***\n");
			printf("\t   Nella prima terra non ci possono essere mostri\n");
			Continua();
		}else{
			if(ultima_terra->tipo_terra==3 && ultima_terra->tipo_mostro==2){
				printf("\t\t\t***Attenzione***\n");
				printf("\t\tLo scheletro non può stare sulla palude\n");
				Continua();
			}else{
				if(ultima_terra->tipo_terra==1 && ultima_terra->tipo_mostro==4){
					printf("\t\t\t***Attenzione***\n");
					printf("\t\tL'orco non può stare sul deserto\n");
					Continua();
				}else{	
					if(ultima_terra->tipo_terra!=2 && ultima_terra->tipo_mostro==3 && ultima_terra->tipo_terra!=5){
						printf("\t\t\t***Attenzione***\n");
						printf("\t\tIl lupo può stare solo su pianura o foresta\n");
						Continua();
					}else{
						if(ultima_terra->tipo_terra==4 && ultima_terra->tipo_mostro!=1){	
							printf("\t\t\t***Attenzione***\n");
							printf("\t\tNel villaggio non possono esserci mostri\n");
							Continua();
						};
					};
				};
			};
		};
	
	}while((ultima_terra->tipo_terra==4 && ultima_terra->tipo_mostro!=1) || 
		(ultima_terra->tipo_mostro==2 && ultima_terra->tipo_terra==3) || 
		(ultima_terra->tipo_mostro==4 && ultima_terra->tipo_terra==1) || 
		(ultima_terra->tipo_mostro==3 && ultima_terra->tipo_terra!=2 && ultima_terra->tipo_terra!=5) || 
		(contatore==1 && ultima_terra->tipo_mostro!=1)		//controllo dei vincoli
	);
	
	do{
		printf("Stai crendo la terra n°%d\n",contatore);
		printf("Tipo terra [%s]\n",terra[ultima_terra->tipo_terra]);
		printf("Tipo mostro [%s]\n\n",mostro[ultima_terra->tipo_mostro]);
		printf("Scegli il numero di monete:\n\nRIRCORDA:\n-il villaggio non può contenere più di 10 monete del tesoro\n");
		scanf("%hd", &num_tesoro);
		
		system("tput clear");
		if(num_tesoro>10 && ultima_terra->tipo_terra==4){		//vincoli del tesoro
				system("tput clear");
				printf("\t\t\t***Attenzione***\n");
				printf("\tIl villaggio non può contenerre più di 10 monete del tesoro\n");
				Continua();	
		}else{ultima_terra->tesoro=num_tesoro;}
		if(num_tesoro<0){
			system("tput clear");
				printf("\t\t***Hai inserito un valore non valido***\n");
				Continua();	
		}else{ultima_terra->tesoro=num_tesoro;}
	}while((num_tesoro>10 && ultima_terra->tipo_terra==4) || num_tesoro<0 );//faccio un controllo sull'input e controllo se un vincolo è rispettato	
	

	
	ultima_terra->terra_successiva=NULL;		//il campo "terra_successiva" dell'ultima terra diventa NULL
	system("tput clear");
	crea_percorso();


}

//Funzione che mette in pausa il programma finchè non si preme il tasto enter
void Continua(){
	printf ("\n\t\tPremere il tasto '1' per continuare...\n");
	while ('1' != getchar ());
	system("tput clear");
		
}



//definisco stampa_percorso
void stampa_percorso(){
	 
	if(percorso==NULL){														//se non è stata inserita alcuna terra stampa questo messaggio
		printf( "\t\t\t   ---------------------------\n"
				"\t\t\t   |        NESSUNA          |\n"
				"\t\t\t   |      TERRA CREATA       |\n"
				"\t\t\t   ---------------------------\n\n");
		
	}else{
		struct Terra* terra_corrente=percorso;							//creo il puntatore per scorrere il percorso
		int i=1;
		while(terra_corrente!=NULL){		
				
			printf("terra n° [%d]\n\n",i);
			printf("Tipo terra: [%s]\n",terra[terra_corrente->tipo_terra]);
			printf("Tipo mostro: [%s]\n",mostro[terra_corrente->tipo_mostro]);
			printf("tesoro:[%d]\n", terra_corrente->tesoro);
			printf("_______________________\n\n");
			++i;
			terra_corrente=terra_corrente->terra_successiva;    // passo alla terra successiva
		}
	};
	Continua();
	crea_percorso();
}

void canc_terra(){
	if (percorso==NULL){								//se non è stata creata alcuna terra stampa questo messaggio
		printf( "\t\t\t   ---------------------------\n"
				"\t\t\t   |        NESSUNA          |\n"
				"\t\t\t   |      TERRA CREATA       |\n"
				"\t\t\t   ---------------------------\n\n");
		Continua();
	}else{							
		if(percorso->terra_successiva==NULL){							//se c'è una sola terra libera il campo "percorso"
			free(percorso);
			percorso=NULL;
			ultima_terra=NULL;
			--contatore;
		}else{
			--contatore;
			struct Terra* elimina_terra=percorso;		// creo una variabile per scorrere le terre	
			while(elimina_terra->terra_successiva->terra_successiva!=NULL){	
				elimina_terra=elimina_terra->terra_successiva;			//scorro fino a trovare la penultima
			}	
			free(elimina_terra->terra_successiva);			//libero tutto cio che è puntato da "terra_successiva" cioè l'utlima terra
			ultima_terra=elimina_terra;
			ultima_terra->terra_successiva=NULL;			//rendo la penultima terra l'ultima
			
		}	
	};
	crea_percorso();
}

void chiudi_percorso(){
	if(percorso==NULL){														//se non è stata inserita alcuna terra stampa questo messaggio
		printf( "\t\t\t   ---------------------------\n"
				"\t\t\t   |        NESSUNA          |\n"
				"\t\t\t   |      TERRA CREATA       |\n"
				"\t\t\t   ---------------------------\n\n");
		Continua();
		crea_percorso();
	}else{
	chiudi++;							//incremento la variabile chiudi per poter cambiare il primo menu'
	};
}

void crea_percorso(){
	do{
		printf("\nTerre inserite: [%d]\n\n", contatore);
		printf("Cosa vuoi fare?\n\n1.inserire terra\n2.cancellare terra\n3.stampa percorso\n4.chiudi percorso\n");
		scanf("%d",&inputcrea);
		switch(inputcrea){
			case 1: system("tput clear");
					ins_terra();
			break;
			case 2: system("tput clear");
					canc_terra();
			break;
			case 3: system("tput clear");
					stampa_percorso();
			break;
			case 4: system("tput clear");
					chiudi_percorso();
			break;
			default:system("tput clear");
					printf("\t\t\t***Comando non trovato***\n");
					Continua();
			
			break;
		}
	}while(inputcrea<1||inputcrea>4);
};

void termina_gioco(){//libero tutte le terre 
	while(percorso!=NULL){
		if(percorso->terra_successiva==NULL){							//se c'è una sola terra libera il campo "percorso"
			free(percorso);
			percorso=NULL;
			ultima_terra=NULL;
			--contatore;
			terra_attuale=NULL;
		}else{
			--contatore;
			struct Terra* elimina_terra=percorso;								// creo una variabile per scorrere le terre	
			while(elimina_terra->terra_successiva->terra_successiva!=NULL){	
				elimina_terra=elimina_terra->terra_successiva;					//scorro fino a trovare la penultima
			}	
			free(elimina_terra->terra_successiva);			//libero tutto cio che è puntato da "terra_successiva" cioè l'utlima terra
				ultima_terra=elimina_terra;
				ultima_terra->terra_successiva=NULL;			//rendo la penultima terra l'ultima
		
		}
	

		
	}
	exit(1);
}



int x=0;  //creo una variabile per controllare se la terra su cui si sta è la prima oppure no
int contatore2=1; //creo un contatore per tener conto del numero della terra su cui si sta
void Gioca();

short int vita_mostro=0;	//creo due variabili per indicare la salute del mostro e i suoi danni
short int danni_mostro=0;
short int* vita=&vita_mostro;  //creo due puntatori per modificarli
short int* danni=&danni_mostro;
void Gioca();

void avanza(){
	system("tput clear");
	if((terra_attuale->tipo_mostro)==5){  //controllo il vincolo del drago
		printf("\t***Non puoi andare avanti senza aver prima sconfitto il drago***\n");
		Continua();
	 	Gioca();
	}else{
		if(terra_attuale->tesoro!=0){    //se si vuole avanzare senza prima raccogliere il tesoro viene stampato un avvertimento e un menù
			int scelta;
			printf("\t\t\t***Attenzione!***\n\nNon hai raccolto il tesoro\nVuoi comunque proseguire?\n\n[1] si\n[2] no\n");
			scanf("%d",&scelta);
			switch(scelta){
				case 1: if((terra_attuale->terra_successiva)!=NULL){	// se si sceglie si si passa alla terra successiva
							terra_attuale=(terra_attuale->terra_successiva); 
							++contatore2;
							system("tput clear");
							Gioca();
							
						}else{
							system("tput clear");
							printf("\t\t***Complimenti hai completato il gioco!***\n\n"); // se la terra in cui si sta è l'ultima il gioco viene completato
							termina_gioco();
						};
				break;
				case 2: system("tput clear");	//se si sceglie no si ritorna alla funzione Gioca()
						Gioca();
				break;
				default: printf("\t\t\t***Comando non trovato***");
						Continua();
						 avanza();
				break;
			}
		}else{
			if((terra_attuale->terra_successiva)!=NULL){
				terra_attuale=terra_attuale->terra_successiva; //si passa alla terra succesiva
				++contatore2;
				system("tput clear");
				Gioca();
			}else{
				printf("\t\t***Complimenti hai completato il gioco!***\n"); 
				termina_gioco();
			};
		};
	};
	
}
		

void prendi_tesoro(){
	
	if(terra_attuale->tipo_mostro==1){   //se non si è sconfitto il mostro non si può prendere il tesoro
		if(terra_attuale->tesoro!=0){
			if(Oberon.borsa_oro+terra_attuale->tesoro<=500){  //se con il prendere il tesoro si eccede la capacità della borsa stampa un errore	
				system("tput clear");
				Oberon.borsa_oro+=terra_attuale->tesoro; //aggiungo il tesoro della terra a quello della borsa
				terra_attuale->tesoro=0;
				printf("\t\t\t***Hai preso il tesoro***\n");
				Continua();
			}else{
				system("tput clear");
				printf("\t\t***Non hai abbastanza spazio nella borsa***\n");
				Continua();
			};
		}else{
			system("tput clear");
			printf("\t\t\t***Non c'è alcun tesoro da raccogliere***\n");
			Continua();
		};
	}else{
		system("tput clear");
		printf("***Non puoi raccogliere il tesoro se prima non hai sconfitto il mostro***\n");
		Continua();
		Gioca();
	};
}
	
void pozione(){
	if(Oberon.pozioni_guaritrici==1){			 //controllo se si hanno ancora delle pozioni
		if(Oberon.punti_ferita==5){				//controllo se Obrton ha tutti i punti ferita
			system("tput clear");
			printf("\t\t***I tuoi punti ferita sono già al massimo***\n");
			Continua();
		}else{
			system("tput clear");
			printf("\t***I tuoi punti ferita sono stati riportati al massimo***\n");
			Oberon.punti_ferita=5;   			//riporto i punti al massimo
			Oberon.pozioni_guaritrici-=1;		// diminuisco le pozioni
			Continua();
		}
	}else{
		system("tput clear");
		printf("\t\t\t***Non hai più pozioni***\n");
		Continua();
	}
}


void combatti(){
	extern short int* vita;
	extern short int* danni;

	if(terra_attuale->tipo_mostro!=1){  //controllo se c'è un mostro da combattere
		while(Oberon.punti_ferita>0 && *vita>0){		//continuo il ciclo fino a che i punti ferita di Oberon o del mostro raggiungono 0
			int menu_attacco=0;   //variabile per accedere al menù di attacco
			int nrand;				//variabile per generare numeri casuali
			system("tput clear");
			printf("Oberon\nhp [%d]\npunti attacco [3]\nincantesimi disponibili [%d]\n\n",Oberon.punti_ferita,Oberon.incantesimi);
			printf("_______VS_______\n\n");
			printf("%s\nhp[%d]\npunti attacco[%d]\n\n\n",mostro[terra_attuale->tipo_mostro],*vita,*danni);
			printf("Cosa vuoi fare?\n[1] attacco base\n[2] incantesimo\n");
			scanf("%d",&menu_attacco);
			switch(menu_attacco){ 
				case 1: nrand=rand()%100;    		//genero un numero da 0 a 99
					if(nrand>=60){
						system("tput clear");
						printf("\n\n\t\t***L'attacco è andato a segno***\n");
						*vita-=3;              		//diminuisco la vita del mostro
						Continua();
					}else{
						system("tput clear");
						printf("\n\n\t\t***L'attacco non è andato a segno***\n");
						Continua();
					};
				break;
				case 2:if(Oberon.incantesimi>0){		//controllo se Oberom ha ancora degli incantesimi
							system("tput clear");
					 		printf("\t***Hai usato un potente incantesimo che ha ucciso il mostro***\n");
							*vita=0;					//porto la vita del mostro a 0
							Oberon.incantesimi-=1;		//diminuisco gli incantesimi di oberon
							Continua();
					   }else{
							system("tput clear");
							printf("\t\t***Non hai più incantesimi da usare***\n");
							Continua();
							combatti();
						}
				break;	

				default: system("tput clear");
						 printf("\t\t\t***Comando non trovato***\n");
						 Continua();
						 combatti();
						 
				break;
				};
			
				
			if(*vita>0){  //se il mostro è ancora in vita attacca
					
				nrand=rand()%100;
				if(nrand>=50){	//genero un numero casuale
				Oberon.punti_ferita-=*danni;
				printf("\n\n\t     ***L'attacco del mostro è andato a segno***\n");
				printf("\t\t\t***Hai subito %d danni***\n",*danni);
				Continua();
				
				}else{
					printf("\n\n\t    ***L'attacco del mostro non è andato a segno***\n");
					Continua();
				}
			}else{
				terra_attuale->tipo_mostro=1;			// se il mostro è morto stampa questo messaggio
				system("tput clear");				
				printf("\n\t\t  ***Hai sconfitto il mostro***\n\t\t***Ora puoi prendere il tesoro***\n");
				Continua();
				Gioca();
			};
			
			if(Oberon.punti_ferita<=0){					//se non hai più punti ferita il gioco si termina
				system ("tput clear");
				printf("\t\tI tuoi punti vita sono scesi a 0\n");
				printf("\t\t\t***GAME OVER***\n\n");	
				termina_gioco();
			}
		
		};
			
		
	}else{ system("tput clear");
		printf("\t\t***Non c'è alcun mostro da combattere***\n");
		Continua();
		Gioca();
	};
}

void distruggi_terra(){
	int scelta; 				//variabile per accedere al menù
	static int distruggi=1;		//variabile per controllare che non si usi due volte l'incantesimo
	struct Terra* temporanea=NULL;			//puntatore temporaneo per cambiare terra
	if(terra_attuale->terra_successiva!=NULL){			//se si è sull'ultima terra stampa un messaggio di errore
		if(distruggi==1){						
			system("tput clear");
			printf("\t\t\t***Attenzione!***\n\nPuoi usare l'incantesimo una volta sola, vuoi usarlo per distruggere la seguente terra?\n\nTerra n° [%d]\nTipo terra [%s]\nTipo mostro [%s]\n\n[1] si\n[2] no\n",contatore2+1, terra[terra_attuale->terra_successiva->tipo_terra], mostro[terra_attuale->terra_successiva->tipo_mostro]);
			scanf("%d",&scelta);
			switch(scelta){
				case 1:	system("tput clear");
					temporanea=terra_attuale->terra_successiva;  	//assegno alla temporanea la terra successiva a quella corrente
					terra_attuale->terra_successiva=temporanea->terra_successiva; //assegno a terra_successiva la terra successiva a quella da cancellare
					free(temporanea); //libero la terra 
					--distruggi;		
					--contatore;
					printf("\t\t***Hai distrutto la terra successiva***\n");
					Continua();
					Gioca();
				break;
			case 2: system("tput clear");
						Gioca();
			break;
			default: printf("\t\t\t***Comando non trovato***");
					 Continua();
						 distruggi_terra();
			break ;
			}
		}else{
			system("tput clear");
			printf("\t\t***L'incantesimo è stato già utilizzato***\n");
			Continua();
		}	

	}else{
		system("tput clear");
		printf("\t***Non esiste alcuna terra successiva da distruggere***");
		Continua();
		Gioca();
	}
}

void Gioca(){
	int inputgioca;				 //creo una variabile per accedere al menù
	if(x==0){
		terra_attuale=percorso;   //parto dalla prima terra
		x++;
	};
	while(terra_attuale!=NULL){			
		printf("Oberon:\nhp [%hd]\npozioni guaritrici [%hd]\nincantesimi [%hd]\nborsa [%hd]\n", Oberon.punti_ferita, Oberon.pozioni_guaritrici, Oberon.incantesimi, Oberon.borsa_oro);
		printf("________________\n\n");
		printf("Sei sulla terra n° [%d]\n",contatore2); 
		printf("Tipo terra [%s]\n", terra[terra_attuale->tipo_terra]);
		printf("Mostro [%s]\n", mostro[terra_attuale->tipo_mostro]);
		switch(terra_attuale->tipo_mostro){			//inizializzo la vita e i danni del mostro
			case 1: *vita=0;
			break;
			case 2:	*vita=2;
			break;
			case 3: *vita=1;
			break;
			case 4: *vita=3;
			break;
			case 5: *vita=5;
			break;
		}
		*danni=*vita;  						//i danni inflitti dal mostro sono la stessa quantità dei punti vita
		
		if(terra_attuale->tipo_mostro!=1){
			printf("hp mostro [%hd]\n",*vita);
			printf("danni mostro [%hd]\n",*danni);
		}

		printf("Tesoro [%hd]\n", terra_attuale->tesoro); 
		printf("________________\n\n\n");
		printf("Scegli un'azione:\n[1] avanza\n[2] prendi tesoro\n[3] usa pozione guaritrice\n[4] combatti\n[5] distruggi terra\n");	
		scanf("%d",&inputgioca);		
		switch(inputgioca){
			case 1:avanza();
					
			break;
			case 2:prendi_tesoro();
					
			break;
			case 3:pozione();
					
			break;
			case 4:combatti();
			break;
			case 5:distruggi_terra();
			break;
			default:system("tput clear");
					printf("\t\t\t***Comando non trovato***\n");
					Continua();					
			break;
		};
		
	};
}

void muovi_Oberon(){
	
	Oberon.borsa_oro=10;					 //inizializzo i campi relativi a oberon
	Oberon.punti_ferita=5;
	Oberon.incantesimi=2;
	Oberon.pozioni_guaritrici=1;
	Gioca();  									//entra nella funzione gioca
	
};
