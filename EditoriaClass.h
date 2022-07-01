#ifndef EDITORIACLASS_H
#define EDITORIACLASS_H
#include "Articolo.h"

#include <string>
using namespace std;


class EditoriaClass {

    protected:
        string nome;
        string acronimo;
        list<Articolo*> articoliPubblicati;
        unsigned data;

    public:
        string getNome() const { return nome; }
        string getAcronimo() const { return acronimo; }
        list<Articolo*> getArticoliPubblicati() const { return articoliPubblicati; }
        unsigned getData() const { return data; }

};

#endif // EDITORIACLASS_H
