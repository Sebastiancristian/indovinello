#include <cstdlib>
#include <ctime>
#include <iostream> 
#include <string> 

using namespace std;

string normalizza(string);
void giocare(int, int&, int&, string, string, int, int&);
void menu();

int main() {
    srand(time(0));  // Imposta il seme per la generazione di numeri casuali
    menu();  
    return 0;  
}

// Funzione per normalizzare la risposta dell'utente (rende tutto minuscolo e rimuove gli spazi)
string normalizza(string testo) {
    string risultato = "";
    for (int i = 0; i < testo.length(); i++) {
        if (testo[i] != ' ') {  // Salta gli spazi
            if (testo[i] >= 'A' && testo[i] <= 'Z') {  // Se è una lettera maiuscola
                risultato += testo[i] + 32;  // Converte la lettera in minuscolo
            } else {
                risultato += testo[i];  // Altrimenti aggiunge il carattere così com'è
            }
        }
    }
    return risultato;  // Restituisce la stringa normalizzata
}

void giocare(int difficolta, int &punteggio1, int &punteggio2, string giocatore1, string giocatore2, int dueGiocatori, int &completato) {
    string indovinelli[3];
    string risposte[3];
    int usati[3] = {0, 0, 0};  // Array per tenere traccia delle domande già usate
    int puntiBase, puntiAiuto;
    int tentativi;
    switch (difficolta) {
        case 1:  // Difficoltà facile
            indovinelli[0] = "Quando parli di me, io svanisco; e quando mi cerchi, non trovi mai nulla. Cos'è?";
            risposte[0] = "silenzio";
            indovinelli[1] = "Sempre in movimento, ma non mi sposto, mi puoi ascoltare, ma non parlare con me. Sono spesso in compagnia, ma mai da solo, eppure senza di me, il mondo non sarebbe lo stesso. Cos'è?";
            risposte[1] = "suono";
            indovinelli[2] = "Vivo dove non c’è vita, senza corpo ma mai vuoto, cammino dove nessuno può andare, ogni passo lascia un segno invisibile. Cos'è?";
            risposte[2] = "Pensiero.";
            puntiBase = 20;  // Punti base per le risposte corrette
            puntiAiuto = 3;  // Punti da perdere se si chiede un aiuto
            tentativi = 10;  // Numero di tentativi disponibili
            break;
        case 2:  // Difficoltà media
            indovinelli[0] = "Ha radici che nessuno vede, è più in alto degli alberi e non cresce mai. Cos'è?";
            risposte[0] = "montagna";
            indovinelli[1] = "Vola senza ali, piange senza occhi, dove va, il buio scompare, Cos'è?";
            risposte[1] = "Nuvola";
            indovinelli[2] = "Più lo togli, più cresce, cosa è?";
            risposte[2] = "Buco";
            puntiBase = 40;
            puntiAiuto = 6;
            tentativi = 20;
            break;
        case 3:  // Difficoltà difficile
            indovinelli[0] = "Sono sempre davanti a te, ma non puoi mai vedermi. Cos'è?";
            risposte[0] = "futuro";
            indovinelli[1] = "Non ha bocca, ma può urlare; non ha piedi, ma può correre, Cos'è?";
            risposte[1] = "Tempesta";
            indovinelli[2] = "Più cresce, meno vedi, Cos'è?";
            risposte[2] = "Buio";
            puntiBase = 60;
            puntiAiuto = 9;
            tentativi = 30;
            break;
    }
    int domandeRimaste = 3;  // Numero di domande rimaste da fare
    while (domandeRimaste > 0) {
        int indice;
        // Selezione casuale di una domanda che non è ancora stata usata
        do {
            indice = rand() % 3;  // Seleziona un numero casuale tra 0 e 2
        } while (usati[indice] == 1);  // Controlla se la domanda è già stata usata
        usati[indice] = 1;  // Marca la domanda come usata
        domandeRimaste--;  // Decrementa il numero di domande rimaste
        cout << "\nIndovinello: " << indovinelli[indice] << "\n";  // Mostra l'indovinello
        int turno = 1;  // Inizia dal primo giocatore
        string rispostaUtente;
        while (tentativi > 0) {  // Continua fino a quando ci sono tentativi
            string giocatoreCorrente;
            if (turno == 1) {
                giocatoreCorrente = giocatore1;  // Se è il turno del primo giocatore
            } else {
                giocatoreCorrente = giocatore2;  // Se è il turno del secondo giocatore
            }
            cout << giocatoreCorrente << ", la tua risposta: ";
            cin >> rispostaUtente;  // L'utente inserisce la sua risposta
            // Controlla se la risposta dell'utente è corretta
            if (normalizza(rispostaUtente) == normalizza(risposte[indice])) {
                cout << "Bravo, " << giocatoreCorrente << "! Hai indovinato!\n";
                if (turno == 1) {
                    punteggio1 += puntiBase;  // Aggiungi i punti al primo giocatore
                } else {
                    punteggio2 += puntiBase;  // Aggiungi i punti al secondo giocatore
                }
                break;  // Passa alla prossima domanda
            } else {
                cout << "Sbagliato. Restano " << --tentativi << " tentativi.\n";  // Decrementa i tentativi
                // Offri la possibilità di chiedere un aiuto
                char rispostaAiuto;
                if (tentativi > 1) {
                    cout << "Vuoi chiedere un aiuto? (s/n): ";
                    cin >> rispostaAiuto;
                    if (rispostaAiuto == 's' || rispostaAiuto == 'S') {
                        // Fornisce l'aiuto
                        char primaLettera = risposte[indice][0];
                        char ultimaLettera = risposte[indice][risposte[indice].length() - 1];
                        int lunghezza = risposte[indice].length();
                        cout << "L'aiuto è: \n";
                        cout << "Prima lettera: " << primaLettera << ", ";
                        cout << "Ultima lettera: " << ultimaLettera << ", ";
                        cout << "Lunghezza: " << lunghezza << "\n";
                        // Riduce i punti per l'uso dell'aiuto
                        if (turno == 1) {
                            punteggio1 -= puntiAiuto;
                        } else {
                            punteggio2 -= puntiAiuto;
                        }
                        cout << "Hai perso " << puntiAiuto << " punti per l'aiuto.\n";
                        break;  // Passa alla prossima domanda
                    }
                }
                if (dueGiocatori == 1) {
                    turno = (turno == 1) ? 2 : 1;  // Cambia turno se ci sono due giocatori
                }
            }
        }
    }
    completato = 1;  // Segna la fine del gioco per questa difficoltà
}
void menu() {
    int scelta;
    string giocatore1, giocatore2;
    int dueGiocatori;
    int completatoFacile = 0, completatoMedio = 0, completatoDifficile = 0;
    cout << "\n--- Gioco degli Indovinelli ---\n";
    cout<<"---Hai 5 tentativi Aumentando la difficolta i tentativi aumentano di 5 \n---Se indovini la parola al primo tentativo avrai 20 punti \n---Aumentando la difficoltà i punti aumentano di 10 \n---Se chiedete aiuto vi restano 3 punti a tutti/e due. aumenta di 3 in ogni difficoltà"<<endl;
    cout << "Vuoi giocare con 1 o 2 giocatori? (1/2): ";
    cin >> scelta; 
    if (scelta == 1) {
        cout << "Inserisci il tuo nome: ";
        cin >> giocatore1;
        giocatore2 = "";  // Nessun secondo giocatore
        dueGiocatori = 0;  // Modalità 1 giocatore
    } else {
        cout << "Giocatore 1, inserisci il tuo nome: ";
        cin >> giocatore1;
        cout << "Giocatore 2, inserisci il tuo nome: ";
        cin >> giocatore2;
        dueGiocatori = 1;  // Modalità 2 giocatori
    }
    int punteggio1 = 0, punteggio2 = 0;
    do {
        cout << "\nScegli una difficolta :\n1. Facile\n2. Medio\n3. Difficile\n4. Esci\nScelta: ";
        cin >> scelta;
        if (scelta == 1 && completatoFacile == 0) {
            giocare(scelta, punteggio1, punteggio2, giocatore1, giocatore2, dueGiocatori, completatoFacile);
        } else if (scelta == 2 && completatoMedio == 0) {
            giocare(scelta, punteggio1, punteggio2, giocatore1, giocatore2, dueGiocatori, completatoMedio);
        } else if (scelta == 3 && completatoDifficile == 0) {
            giocare(scelta, punteggio1, punteggio2, giocatore1, giocatore2, dueGiocatori, completatoDifficile);
        } else if (scelta != 4) {
            cout << "Hai gia completato questa difficolta!" << endl;
        }
    } while (scelta != 4);  // Continua finché non viene scelto "Esci"
    // Mostra i punteggi finali
    cout << "\nGrazie per aver giocato! " << giocatore1 << " ha totalizzato " << punteggio1 << " punti.\n";
    if (dueGiocatori == 1) cout << giocatore2 << " ha totalizzato " << punteggio2 << " punti.\n";
    cout << "\nGioco creato da Sebastian e Areeb il programma deve ancora migliorare: i consigli sono ben aprezzati, grazie ancora per aver giocato" <<endl;
}
