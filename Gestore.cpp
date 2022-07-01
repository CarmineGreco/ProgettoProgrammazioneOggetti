#include "Gestore.h"
#include "Utility.h"
#include <climits>

string Gestore::getCognomeFrom(unsigned idAutore) const {

    for(auto a : autori){
        if(a->getId() == idAutore){
            return a->getCognome();
        }
    }
    return "";
}

// PRIVATE //
void Gestore::clear(){

    articoli.clear();
    autori.clear();
    conferenze.clear();
    riviste.clear();
}

void Gestore::copy(const Gestore& g){

    for(auto elem : g.autori){
        autori.push_back(elem);
    }

    for(auto elem : g.articoli){
        articoli.push_back(elem);
    }

    for(auto elem : g.riviste){
        riviste.push_back(elem);
    }

    for(auto elem : g.conferenze){
        conferenze.push_back(elem);
    }
}

    // PRIVATE //

Gestore::Gestore(){}

Gestore::Gestore(const Gestore& g){

    copy(g);
}

Gestore& Gestore::operator=(const Gestore &g){

    if(this != &g){
        clear();
        copy(g);
    }
    return *this;
}

Gestore::~Gestore(){

    clear();
}


//ID GENERATOR AUTORE
unsigned Gestore::idAutore = 1;

unsigned Gestore::generaIdAutore() {
    return ++Gestore::idAutore;
}

unsigned Gestore::ultimoIdAutore() {
    return Gestore::idAutore;
}

//ID GENERATOR ARTICOLO
unsigned Gestore::idArticolo = 1;

unsigned Gestore::generaIdArticolo() {
    return ++Gestore::idArticolo;
}

unsigned Gestore::ultimoIdArticolo() {
    return Gestore::idArticolo;
}

const list<Articolo*>& Gestore::visualizzaArticoliCopia() const {

    return articoliCopia;
}

void Gestore::rimuoviArticoloAggiunto(Articolo *a){

    articoliCopia.remove(a);
}

//SEZIONE A
bool Gestore::aggiungiAutore(Autore* a) {

    if(!Utility::esisteAutore(a->getId(),autori)){
        autori.push_back(a);
        return true;
    }
    return false;
}

void Gestore::aggiungiConferenza(Conferenza* c) {

    conferenze.push_back(c);
}

bool Gestore::aggiungiArticolo(Articolo *a){
    if(!Utility::esisteArticolo(a->getId(), articoli)){
        articoli.push_back(a);
        articoliCopia.push_back(a);
        return true;
    }
    return false;
}
void Gestore::aggiungiRivista(Rivista* r) {

    riviste.push_back(r);
}

const list<Autore*>& Gestore::visualizzaAutori()const {

    return autori;
}

const list<Conferenza*>& Gestore::visualizzaConferenze()const {

    return conferenze;

}

const list<Rivista*>& Gestore::visualizzaRiviste() const {

    return riviste;

}

const list<Articolo*>& Gestore::visualizzaArticoli() const {

    return articoli;
}

//SEZIONE B

list<Articolo*> Gestore::visualizzaArticoliAutore(Autore* a) {

        list<Articolo*> articoliAutore;
        for(auto i : articoli){
            if (Utility::contieneAutore(a, i->getAutori()))
                articoliAutore.push_back(i);
        }
        return articoliAutore;
}

list<Articolo*> Gestore::visualizzaArticoliKeyword(string k) {

    list<Articolo*> listaArticoli;
    for(auto i : articoli) {
        list<string> l = i->getKeyword();
        for(auto &elem : l) {
            if(elem.compare(k) == 0) {
                listaArticoli.push_back(i);
            }
        }
    }
    return listaArticoli;
}

list<Articolo*> Gestore::visualizzaArticoliAutoreAnno(Autore *a, unsigned int anno) {

    list<Articolo*> articoliAnno;
    for(auto i : riviste){
        if(i->getData() == anno){
           list<Articolo*> articoli = i->getArticoliPubblicati();
           for(auto elem : articoli){
               if (Utility::contieneAutore(a, elem->getAutori()))
                   articoliAnno.push_back(elem);
           }
        }
    }

    for(auto i : conferenze){
        if(i->getData() == anno){
            list<Articolo*> articoli = i->getArticoliPubblicati();
            for(auto elem : articoli){
                if (Utility::contieneAutore(a, elem->getAutori()))
                    articoliAnno.push_back(elem);
            }
        }
    }


    return articoliAnno;

}

//SEZIONE C
double Gestore::visualizzaMediaPrezziAutore(Autore* a) {
    double sum = 0;
    unsigned count = 0;
    for(auto i : articoli) {
        list<unsigned> l = i->getAutori();
        for(auto elem : l) {
            if(a->getId() == elem) {
                sum+=i->getPrezzo();
                count++;
            }
        }
    }
    return sum/(double)count;
}

list<Articolo*> Gestore::visualizzaArticoliPrezzoBasso(Autore* a){

    list<Articolo*> articoliAutore;
    list<Articolo*> articoliPrezzoBasso;
    for(auto i : articoli) {
        if (Utility::contieneAutore(a, i->getAutori()))
            articoliAutore.push_back(i);
    }

    articoliAutore.sort(Utility::sortArticoloPrezzoBasso);


    Articolo* art = articoliAutore.front();
    double min = art->getPrezzo();
    for(auto elem : articoliAutore){
        if(min == elem->getPrezzo()){
            articoliPrezzoBasso.push_back(elem);
        }
    }

    return articoliPrezzoBasso;
}

list<Articolo*> Gestore::visualizzaArticoliPrezzoAlto(Autore* a){

    list<Articolo*> articoliAutore;
    list<Articolo*> articoliPrezzoAlto;
    for(auto i : articoli) {
        if (Utility::contieneAutore(a, i->getAutori()))
            articoliAutore.push_back(i);
    }

    articoliAutore.sort(Utility::sortArticoloPrezzoAlto);


    Articolo* art = articoliAutore.front();
    double max = art->getPrezzo();
    for(auto elem : articoliAutore){
        if(max == elem->getPrezzo()){
            articoliPrezzoAlto.push_back(elem);
        }
    }

    return articoliPrezzoAlto;
}


list<string> Gestore::visualizzaKeywordGuadagno(){

    list<string> totKey = Utility::getKeywordTotArticoli(articoli);

    unsigned guadagno = 0;
    unsigned max = INT_MIN;
    for(auto &k : totKey){
        guadagno = 0;
        for(auto art : articoli){
            list<string> key = art->getKeyword();
            if(Utility::keywordUguali(k,key))
                guadagno += art->getPrezzo();
        }
        if(guadagno > max)
            max = guadagno;
    }

    for(auto &k : totKey){
        guadagno = 0;
        for(auto art : articoli){
            list<string> key = art->getKeyword();
            if(Utility::keywordUguali(k,key))
                guadagno += art->getPrezzo();
        }
        if(guadagno == max)
            totKey.push_back(k);
    }

    return totKey;
}

//SEZIONE D
list<Articolo*> Gestore::visualizzaArticoliAutorePrezzo(Autore *a){

    list<Articolo*> articoliPerPrezzo;


    for(auto elem : articoli){
        if(Utility::contieneAutore(a,elem->getAutori()))
            articoliPerPrezzo.push_back(elem);
    }

    articoliPerPrezzo.sort(Utility::sortArticoloPrezzoBasso);

    return articoliPerPrezzo;
}

list<Articolo*> Gestore::visualizzaArticoliConferenzaPrezzo(Conferenza* c){

    list<Articolo*> articoliPrezzo = c->getArticoliPubblicati();

    articoliPrezzo.sort(Utility::sortArticoloPrezzoBasso);

    return articoliPrezzo;
}


list<Articolo*> Gestore::visualizzaArticoliKeywordSorted(string k){
    list<Articolo*> art = visualizzaArticoliKeyword(k);

    art.sort(Utility::sortArticoloKeyword);

    return art;
}

//SEZIONE E
list<Conferenza*> Gestore::visualizzaConferenzeKeywordComune(){

    list<Conferenza*> conferenzeKey;

    for(auto c : conferenze){
        bool check = false;
        list<Articolo*> art = c->getArticoliPubblicati();
        for(auto a : art){
            list<string> key = a->getKeyword();
            for(auto &elem : key){
                if(Utility::contaKeyword(elem, art) == art.size()){
                    check = true;
                    break;
                }
            }
        }
        if(check)
            conferenzeKey.push_back(c);
    }

    return conferenzeKey;
}

list<Rivista*> Gestore::visualizzaRivisteSpecialistiche(){

    list<Rivista*> rivisteSpecialistiche;

    for(auto r1 : riviste){
        list<string> key1 = Utility::getKeywordTot(r1);
        for(auto r2 : riviste){
            if(r1 == r2)
                continue;
            else{
                list<string> key2 = Utility::getKeywordTot(r2);
                if(Utility::keywordContenute(key1,key2)){
                    rivisteSpecialistiche.push_back(r1);
                    break;
                }
            }
        }
    }
    return rivisteSpecialistiche;
}

//SEZIONE F

list<Articolo*> Gestore::visualizzaArticoliInfluenzati(Articolo *b){

    list<Articolo*> articoliInfluenzati;
    bool found;
    for(auto a : articoli){
        if(Utility::influenza(a,b)){
            found=false;
            for(auto elem : articoliInfluenzati){
                if(a->getId()==elem->getId()){
                    found = true;
                    break;
                }
            }
            if(!found)
                articoliInfluenzati.push_back(a);

            for(auto a2 : articoli){
                if(Utility::influenza(a2,a)){
                    found=false;
                    for(auto elem : articoliInfluenzati){
                        if(a2->getId()==elem->getId()){
                            found = true;
                            break;
                        }
                    }
                    if(!found)
                        articoliInfluenzati.push_back(a2);
                }
            }
        }
    }

    return articoliInfluenzati;
}


list<Conferenza*> Gestore::visualizzaConferenzeSimili(Conferenza* c){

    list<Conferenza*> conferenzeSimili;
    list<string> a = Utility::getKeywordTot(c);

    for(auto elem: conferenze){
        list<string> b = Utility::getKeywordTot(elem);
        if(Utility::confSimili(a,b)){
            conferenzeSimili.push_back(elem);
        }
    }

    return conferenzeSimili;
}
