#ifndef CONFERENZA_H
#define CONFERENZA_H
#include "Articolo.h"
#include "EditoriaClass.h"

#include <iostream>
#include <list>
#include <string>
using namespace std;

class Conferenza : public EditoriaClass {

	private:
		string luogo;
		unsigned partecipanti;
        list<string> organizzatori;

        list<unsigned> iDArticoliPubblicati;
		
	public:
        Conferenza(string nome, string acronimo, string luogo, unsigned data, unsigned partecipanti, list<string> organizzatori) {
			this->nome = nome;
			this->acronimo = acronimo;
			this->luogo = luogo;
			this->data = data;
			this->partecipanti = partecipanti;
			this->organizzatori = organizzatori;
			
		}
        Conferenza(string nome, string acronimo, string luogo, unsigned data, unsigned partecipanti, list<string> organizzatori, list<Articolo*> articoliPubblicati) {
            this->nome = nome;
            this->acronimo = acronimo;
            this->luogo = luogo;
            this->data = data;
            this->partecipanti = partecipanti;
            this->organizzatori = organizzatori;
            this->articoliPubblicati = articoliPubblicati;

        }
        void setIDArticoliPubblicati(unsigned n){ iDArticoliPubblicati.push_back(n); }
		string getLuogo() const { return luogo; }
		unsigned getPartecipanti() const { return partecipanti; }
        list<string> getOrganizzatori() const { return organizzatori; }
		
		friend ostream& operator<<(ostream& o, const Conferenza& c) {
            o << "Nome: " << c.nome << ", "<< "Acronimo: " << c.acronimo << ", " << "Luogo: " << c.luogo << ", " << "Data: " << c.data << ", " << "Partecipanti: " <<c.partecipanti <<", Organizzatori: [";
			
            copy(c.organizzatori.begin(), c.organizzatori.end().operator--(), ostream_iterator<string>(o, ","));
            copy(c.organizzatori.end().operator--(), c.organizzatori.end(), ostream_iterator<string>(o));
            o << "]" << " Articoli pubblicati = [";
            copy(c.iDArticoliPubblicati.begin(), c.iDArticoliPubblicati.end().operator--(), ostream_iterator<unsigned>(o, ","));
            copy(c.iDArticoliPubblicati.end().operator--(), c.iDArticoliPubblicati.end(), ostream_iterator<unsigned>(o));
            o <<"]" << endl;

			return o;
		}
};

#endif
