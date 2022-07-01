#ifndef UTILITY_H
#define UTILITY_H
#include "Autore.h"
#include "Articolo.h"
#include "Conferenza.h"
#include "Rivista.h"

#include <string>
#include <list>
#include <iostream>
#include <locale>
#include <QList>

using namespace std;

class Utility {

	public:
        static list<const char*> stringToChar(string s);
        static bool sortArticoloPrezzoBasso(const Articolo* first, const Articolo* second);
        static bool sortArticoloPrezzoAlto(const Articolo* first, const Articolo* second);
        static bool sortArticoloKeyword(const Articolo* first, const Articolo* second);
        static bool sortRivisteData(const Rivista* first, const Rivista* second);
        static unsigned esisteKeyword(const char* keyword, list<Articolo*> a);
        static bool esisteAutore(const unsigned n, list<Autore*> l);
        static bool esisteArticolo(const unsigned n, list<Articolo*> l);
        static list<const unsigned*> stringToId(string s);

        static list<string> split(QString s, char separator);
        static unsigned contaKeyword(string keyword, list<Articolo*> articoli);
        static bool contieneAutore(const Autore* a, list<unsigned> autori);
        static bool contieneAutore(const Articolo* articolo, const Autore* autore);
        static Autore* getAutore(unsigned n, list<Autore*> l);
        static Articolo* getArticolo(unsigned n, list<Articolo*> l);
        static Conferenza* getConferenza(string n, list<Conferenza*> l);
        static list<string> getKeywordTotArticoli(list<Articolo*> l);
        static list<string> getKeywordTot(EditoriaClass* c);
        static bool confSimili(list<string> a, list<string> b);
        static bool keywordContenute(list<string> a, list<string> b);
        static bool keywordUguali(string a, list<string> b);
        static unsigned getDataFrom(list<EditoriaClass*> l, const Articolo* a);
        static bool influenza(const Articolo* a, const Articolo* b);

};

#endif
