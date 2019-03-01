//dichiaro i prototipi delle funzioni
void crea_percorso();
void muovi_Oberon();
void termina_gioco();


//dicharo le strutture e gli enum corrispondenti
struct Oberon {
	short int borsa_oro;
	short int punti_ferita;
	short int incantesimi;
	short int pozioni_guaritrici;
	};

enum tipo_Terra {deserto=1,foresta,palude,villaggio, pianura};
enum tipo_Mostro {nessuno=1, scheletro, lupo, orco, drago};


struct Terra{
	enum tipo_Terra tipo_terra;
	enum tipo_Mostro tipo_mostro;
	short int tesoro;
	struct Terra* terra_successiva;
	};


