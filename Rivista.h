#ifndef RIVISTA_H
#define RIVISTA_H
#include "Articolo.h"
#include "EditoriaClass.h"

#include <string>
#include <iostream>
#include <iostream>
using namespace std;

class Rivista : public EditoriaClass{

	private:
		string nome;
		string acronimo;
		string editore;
		unsigned data;
		unsigned volume;
        list<Articolo*> articoliPubblicati;

        list<unsigned> iDArticoliPubblicati;
		
	public:
        Rivista(string nome, string acronimo, string editore, unsigned data, unsigned volume) {
			this->nome = nome;
			this->acronimo = acronimo;
			this->editore = editore;
			this->data = data;
			this->volume = volume;
		}
        Rivista(string nome, string acronimo, string editore, unsigned data, unsigned volume, list<Articolo*> articoliPubblicati) {
            this->nome = nome;
            this->acronimo = acronimo;
            this->editore = editore;
            this->data = data;
            this->volume = volume;
            this->articoliPubblicati = articoliPubblicati;
        }

        bool operator==(const Rivista& r){
            if(nome == r.nome && acronimo == r.acronimo && editore == r.editore && data == r.data && volume == r.volume && articoliPubblicati == r.articoliPubblicati)
                return true;
            return false;
        }

        void setIDArticoliPubblicati(unsigned n) { iDArticoliPubblicati.push_back(n); }
		string getEditore() const { return editore; }
		unsigned getvolume() const { return volume; }

		
		friend ostream& operator<<(ostream& o, const Rivista& r) {
			o << "Nome: " << r.nome << ", " << "Acronimo: " << r.acronimo << ", " << "Editore: " << r.editore << ", " << "Data: " << r.data << ", " << "Volume: " << r.volume;
            o << ", Articoli Pubblicati: [";
            copy(r.iDArticoliPubblicati.begin(), r.iDArticoliPubblicati.end().operator--(), ostream_iterator<unsigned>(o, ","));
            copy(r.iDArticoliPubblicati.end().operator--(), r.iDArticoliPubblicati.end(), ostream_iterator<unsigned>(o));
            o <<"]" << endl;
            return o;
		}
};

#endif
