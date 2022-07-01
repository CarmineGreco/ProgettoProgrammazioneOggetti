#ifndef ARTICOLO_H
#define ARTICOLO_H

#include "Autore.h"
#include "IDClass.h"
#include <iostream>
#include <string>
#include <iostream>

using namespace std;

class Articolo : public IDClass {

	private:
		string titolo;
		unsigned numeroPagine;
        double prezzo;
		
        list<unsigned> autoriArticolo;
        list<string> keyword;

        list<unsigned> articoliCorrelati;
		list<const unsigned*> riviste;
		list<const unsigned*> conferenze;
		
        unsigned dataPubblicazione;
        string cognomePrimoAutore;

	public:
        Articolo(unsigned id, string titolo, unsigned numeroPagine, double prezzo, list<unsigned> autoriArticolo, list <string> keyword, list<unsigned> articoliCorrelati) : IDClass(id){
			this->titolo = titolo;
			this->numeroPagine = numeroPagine;
			this->prezzo = prezzo;
			this->autoriArticolo = autoriArticolo;
			this->keyword = keyword;
            this->articoliCorrelati = articoliCorrelati;
		}

		string getTitolo() const { return titolo; }
		unsigned getNumeroPagine() const { return numeroPagine; }
        double getPrezzo() const { return prezzo; }
        list<unsigned> getAutori() const { return autoriArticolo; }
        list<unsigned> getArticoliCorrelati() const { return articoliCorrelati; }
		list<const unsigned*> getRiviste() const { return riviste; }
		list<const unsigned*> getConferenze() const { return conferenze; }
        list<string> getKeyword() const { return keyword; }

        void setDataPubblicazioe(unsigned n) { dataPubblicazione = n; }
        void setCognomePrimoAutore(string s) { cognomePrimoAutore = s; }
        unsigned getDataPubblicazione() const { return dataPubblicazione; }
        string getCognomePrimoAutore() const { return cognomePrimoAutore; }
	
		
		friend ostream& operator<<(ostream& o, const Articolo& a) {
            o <<"Identificativo = " << a.id << ", " <<"Titolo = " << a.titolo << ", " << "Numero pagine = " << a.numeroPagine << ", " << "Prezzo = " << a.prezzo << " Autori = [";

            copy(a.autoriArticolo.begin(), a.autoriArticolo.end().operator--(), ostream_iterator<unsigned>(o, ","));
            copy(a.autoriArticolo.end().operator--(), a.autoriArticolo.end(), ostream_iterator<unsigned>(o));
            o << "] " << " Keyword = [";
            copy(a.keyword.begin(), a.keyword.end().operator--(), ostream_iterator<string>(o, ","));
            copy(a.keyword.end().operator--(), a.keyword.end(), ostream_iterator<string>(o));
            o << "]" << " Articoli correlati = [";
            copy(a.articoliCorrelati.begin(), a.articoliCorrelati.end().operator--(), ostream_iterator<unsigned>(o, ","));
            copy(a.articoliCorrelati.end().operator--(), a.articoliCorrelati.end(), ostream_iterator<unsigned>(o));
            o << "]" << endl;

			return o;
		}  
		
};

#endif
