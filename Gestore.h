#ifndef GESTORE_H
#define GESTORE_H

#include "Autore.h"
#include "Rivista.h"
#include "Articolo.h"
#include "Conferenza.h"

#include <iostream>
#include <list>

using namespace std;

class Gestore {

	private:
        list<Autore*> autori;
		list<Conferenza*> conferenze;
		list<Rivista*> riviste;
		list<Articolo*> articoli;

        list<Articolo*> articoliCopia;
	
        void clear();
        void copy(const Gestore& g);

	public:
	    Gestore();
        Gestore(const Gestore& g);
        Gestore& operator=(const Gestore& g);
        ~Gestore();

        string getCognomeFrom(unsigned idAutore)const;

        //ID GENERATOR AUTORE
        static unsigned idAutore;
        static unsigned generaIdAutore();
        static unsigned ultimoIdAutore();

        //ID GENERATOR ARTICOLO
        static unsigned idArticolo;
        static unsigned generaIdArticolo();
        static unsigned ultimoIdArticolo();

        const list<Articolo*>& visualizzaArticoliCopia()const;
        void rimuoviArticoloAggiunto(Articolo* a);

		//SEZIONE A
        bool aggiungiAutore(Autore* a);
		void aggiungiConferenza(Conferenza* c);
		void aggiungiRivista(Rivista* r);
        bool aggiungiArticolo(Articolo* a);
        const list<Autore*>& visualizzaAutori() const ;
        const list<Conferenza*>& visualizzaConferenze()const ;
        const list<Rivista*>& visualizzaRiviste()const ;
        const list<Articolo*>& visualizzaArticoli()const ;


        //SEZIONE B
        list<Articolo*> visualizzaArticoliAutore(Autore* a); //B1
        list<Articolo*> visualizzaArticoliKeyword(string k);//B6
        list<Articolo*> visualizzaArticoliAutoreAnno(Autore* a, unsigned anno);//B2

        //SEZIONE C
        double visualizzaMediaPrezziAutore(Autore* a);//C3
        list<Articolo*> visualizzaArticoliPrezzoBasso(Autore* a);//C1
        list<Articolo*> visualizzaArticoliPrezzoAlto(Autore* a);//C2
        list<string> visualizzaKeywordGuadagno();//C6


        //SEZIONE D
        list<Articolo*> visualizzaArticoliAutorePrezzo(Autore* a);//D2
        list<Articolo*> visualizzaArticoliConferenzaPrezzo(Conferenza* c);//D3
        list<Articolo*> visualizzaArticoliKeywordSorted(string k); //D5

        //SEZIONE E
        list<Conferenza*> visualizzaConferenzeKeywordComune();//E1
        list<Rivista*> visualizzaRivisteSpecialistiche();//E6

        //SEZIONE F
        list<Articolo*> visualizzaArticoliInfluenzati(Articolo* b);//F1
        list<Conferenza*> visualizzaConferenzeSimili(Conferenza* a);//F5


};

#endif
