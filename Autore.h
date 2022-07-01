#ifndef AUTORE_H
#define AUTORE_H
#include "IDClass.h"

#include <string>
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

class Autore : public IDClass {
	
	private:
		string nome;
		string cognome;
        list<string> afferenze;

	public:
        Autore(){};

        Autore(unsigned id, string nome, string cognome, list<string> afferenze) : IDClass(id){
            this->nome = nome;
            this->cognome = cognome;
            this->afferenze = afferenze;
        }
		string getNome() const { return nome; }
		string getCognome() const { return cognome; }
        list<string> getAfferenze() const { return afferenze; }

		

        friend ostream& operator<<(ostream& o, const Autore &a) {
            o << "Id: " << a.id << ", Nome: " << a.nome << ", Cognome: " << a.cognome << ", Afferenze: [";
            copy(a.afferenze.begin(), a.afferenze.end().operator--(), ostream_iterator<string>(o, ","));
            copy(a.afferenze.end().operator--(), a.afferenze.end(), ostream_iterator<string>(o));
            o <<"]" << endl;
            return o;
		} 
};

#endif
