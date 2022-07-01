#include "Utility.h"
#include "EditoriaClass.h"
using namespace std;


list<string> Utility::split(QString str, char separator) {
    QStringList results = str.split(separator);
    list<string> splitted;
    for (const auto& i : results) {
        splitted.push_back(i.toStdString());
    }
    return splitted;
}

unsigned Utility::contaKeyword(string keyword, list<Articolo*> articoli){

    unsigned count = 0;
    for(auto elem : articoli){
        list<string> key = elem->getKeyword();
        for(auto &k : key)
            if(keyword.compare(k) == 0)
                count++;
    }
    return count;
}

bool Utility::contieneAutore(const Autore *a, list<unsigned> autori) {
    for(auto elem : autori)
        if(a->getId() == elem)
            return true;
    return false;
}

bool Utility::contieneAutore(const Articolo* articolo, const Autore* autore) {
    list<unsigned> autori = articolo->getAutori();
    for(auto elem : autori) {
        if(autore->getId() == elem) {
            return true;
        }
    }
    return false;
}

bool Utility::sortArticoloPrezzoBasso(const Articolo *first, const Articolo *second) {
    if(first->getPrezzo() < second->getPrezzo())
        return true;
    return false;
}

bool Utility::sortArticoloPrezzoAlto(const Articolo *first, const Articolo *second) {
    if(first->getPrezzo() > second->getPrezzo())
        return true;
    return false;
}


bool Utility::sortRivisteData(const Rivista *first, const Rivista *second){
    if(first->getData() < second->getData())
        return true;
   return false;
}


bool Utility::sortArticoloKeyword(const Articolo *first, const Articolo *second){
    if(first->getDataPubblicazione() > second->getDataPubblicazione())
        return true;
    else if(first->getDataPubblicazione() == second->getDataPubblicazione() && first->getPrezzo() < second->getPrezzo())
        return true;
    else if(first->getDataPubblicazione() == second->getDataPubblicazione() && first->getPrezzo() == second->getPrezzo()){
        if(first->getCognomePrimoAutore() < second->getCognomePrimoAutore()){
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
bool Utility::esisteAutore(const unsigned int n, list<Autore*> l){

    for(auto elem : l)
        if(n == elem->getId())
            return true;
    return false;
}

bool Utility::esisteArticolo(const unsigned int n, list<Articolo *> l){

    for(auto elem : l)
        if(n == elem->getId())
            return true;
    return false;
}

Autore* Utility::getAutore(unsigned int n, list<Autore*> l){
    for(auto elem : l)
        if(elem->getId()==n)
            return elem;
    return nullptr;
}

Articolo* Utility::getArticolo(unsigned int n, list<Articolo *> l){
    for(auto elem : l)
        if(elem->getId() == n)
            return elem;
    return nullptr;
}

Conferenza* Utility::getConferenza(string n, list<Conferenza *> l){
    //Non avendo un valore di unicità come l'id di autore/articolo, ho forzato la ricerca di conferenze dal numero di partecipanti
    for(auto elem: l)
        if(elem->getNome()==n)
            return elem;
    return nullptr;
}
list<string> Utility::getKeywordTotArticoli(list<Articolo*> l){

    list<string> keywordTot;
    bool found;
    for(auto elem : l){
        list<string> key1 = elem->getKeyword();
        for(auto &k1 : key1){
            found = false;
            for(auto &k2 : keywordTot){
                if(k1.compare(k2)==0)
                    found = true;
            }
            if(!found)
                keywordTot.push_back(k1);
        }
    }
    return keywordTot;
}
list<string> Utility::getKeywordTot(EditoriaClass* c){

    bool found;
    list<string> keywordTot;
    list<Articolo*> art = c->getArticoliPubblicati();
    for(auto elem2 : art){
        list<string> key = elem2->getKeyword();
        for(auto &k : key){
            found = false;
            for(auto &k2 : keywordTot){
                if(k.compare(k2) == 0)
                    found = true;
            }
            if(!found)
                keywordTot.push_back(k);
        }
    }
    return keywordTot;
}


bool Utility::confSimili(list<string> a, list<string> b){

    unsigned countSame = 0;
    for(auto &k : a){
       for(auto &k2 : b){
           if(k.compare(k2) == 0){
               countSame++;
           }
       }
    }
    if((countSame*100)/a.size() >= 80)
        return true;
    return false;
}

bool Utility::keywordContenute(list<string> a, list<string> b){

    unsigned count = 0;
    if(a.size() > b.size())
        return false;

    for(auto &k : a){
        for(auto &k2 : b){
            if(k.compare(k2) == 0){
                count++;
            }
        }
    }
    if(count == a.size())
        return true;
    return false;
}

bool Utility::keywordUguali(string a, list<string> b){

    for(auto &key : b)
        if(a.compare(key) == 0)
            return true;
    return false;
}

unsigned Utility::getDataFrom(list<EditoriaClass*> l, const Articolo* a){

   for(auto elem : l){
       for(auto art : elem->getArticoliPubblicati()){
           if(art->getId() == a->getId()){
               return elem->getData();
           }
       }
   }
   return 0;
}


bool Utility::influenza(const Articolo *a, const Articolo *b){
    if(a->getId() == b->getId())
        return false;

    for(auto elem : b->getArticoliCorrelati())
        if(a->getId() == elem && a->getDataPubblicazione() < b->getDataPubblicazione())
            return true;
    return false;
}

