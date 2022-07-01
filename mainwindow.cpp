#include "mainwindow.h"
#include "Gestore.h"
#include "ui_mainwindow.h"
#include "Utility.h"

#include <iostream>
#include <list>
#include <QList>
#include <sstream>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::lightGray);
        palette->setColor(QPalette::Text,Qt::black);
        ui->id->setReadOnly(true);
        ui->id_2->setReadOnly(true);
        ui->id->setPalette(*palette);
        ui->id_2->setPalette(*palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   ui->StackedWidget->setCurrentWidget(ui->Home);
}

void MainWindow::on_AggiungiAutore_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Aggiungi_Autore);
    ui->id->setText(QString::number(Gestore::ultimoIdAutore()));
}

void MainWindow::on_AggiungiArticolo_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Aggiungi_Articolo);
    ui->id_2->setText(QString::number(Gestore::ultimoIdArticolo()));
}

void MainWindow::on_clearLista_clicked()
{
    ui->listWidget_7->clear();
}

void MainWindow::on_AggiungiConferenza_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Aggiungi_Conferenza);
}

void MainWindow::on_Aggiungi1_clicked()
{
    QString iD = ui->id->text();
    bool ok;
    unsigned i=iD.toUInt(&ok);
    if (ok) {
        QString nome = ui->nome->text();
        string n = nome.toStdString();

        QString cognome = ui->cognome->text();
        string c = cognome.toStdString();

        QString afferenza = ui->afferenze->text();

        list<string> l = Utility::split(afferenza, ',');

        Autore* autore = new Autore(i,n,c,l);
        if(g.aggiungiAutore(autore)){
            QMessageBox::information(
                this,
                tr("Application Name"),
                tr("Autore aggiunto correttamente!") );
        }
        else{
            QMessageBox::information(
                this,
                tr("Application Name"),
                tr("Autore non aggiunto, inserire un ID diverso!") );
        }
    } else {
            QMessageBox::information(
                this,
                tr("Application Name"),
                tr("Inserire un numero valido come identificativo!") );

    }
    ui->nome->clear();
    ui->cognome->clear();
    ui->afferenze->clear();
    ui->id->setText(QString::number(Gestore::generaIdAutore()));

}
void MainWindow::on_pushButton_6_clicked()
{
    QString id = ui->id_2->text();
    unsigned i = id.toUInt();

    QString titolo = ui->titolo->text();
    string t = titolo.toStdString();

    QString numero = ui->nPagine->text();
    unsigned n = numero.toUInt();

    QString prezzo = ui->prezzoArt->text();
    double p = prezzo.toDouble();

    QString keyword = ui->listaKeyword->text();
    list<string> lista = Utility::split(keyword, ',');

    QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();
    list<unsigned> listaAutori;
        for (auto elem: items) {
            QVariant data = elem->data(Qt::UserRole);
            unsigned idAutore = data.toUInt();
            listaAutori.push_back(idAutore);
        }

    list<unsigned> listaCorrelati;
    QList<QListWidgetItem*> items2 = ui->listWidget_13->selectedItems();
    for(auto elem : items2){
        QVariant data = elem->data((Qt::UserRole));
        unsigned iDArt = data.toUInt();
        listaCorrelati.push_back(iDArt);
    }

    Articolo* art = new Articolo(i,t,n,p,listaAutori,lista,listaCorrelati);
    string cognomePrimoAutore = g.getCognomeFrom(listaAutori.front());
    art->setCognomePrimoAutore(cognomePrimoAutore);

    if(g.aggiungiArticolo(art)){
        ui->id_2->setText(QString::number(Gestore::generaIdArticolo()));
        ui->titolo->clear();
        ui->nPagine->clear();
        ui->prezzoArt->clear();
        ui->listaKeyword->clear();
        ui->listWidget_13->clear();
        ui->listWidget_2->clear();
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Articolo aggiunto correttamente!") );
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Articolo non aggiunto, inserire un ID diverso!") );
    }
}

void MainWindow::on_aggiungiConf_clicked()
{
    list<Articolo*> listaCompleta = g.visualizzaArticoli();
    QString nome = ui->nomeConferenza->text();
    string n = nome.toStdString();

    QString acronimo = ui->acronimoConferenza->text();
    string a = acronimo.toStdString();

    QString luogo = ui->luogoConferenza->text();
    string l = luogo.toStdString();

    QString data = ui->dataConferenza->text();
    unsigned d = data.toUInt();

    QString numeroPartecipanti = ui->numeroPartecipanti->text();
    unsigned nP = numeroPartecipanti.toUInt();

    QString organizzatori = ui->listaOrganizzatori->text();
    string o = organizzatori.toStdString();

    list<string> lista = Utility::split(organizzatori, ',');



    list<Articolo*> listPubblicati;
    QList<QListWidgetItem*> items = ui->listWidget_5->selectedItems();
    for(auto elem : items){
        QVariant data = elem->data(Qt::UserRole);
        unsigned iDArt = data.toUInt();
        Articolo* art = Utility::getArticolo(iDArt,listaCompleta);
        art->setDataPubblicazioe(d);
        listPubblicati.push_back(art);
        g.rimuoviArticoloAggiunto(art);
    }
    Conferenza* conferenza = new Conferenza(n,a,l,d,nP,lista,listPubblicati);

    for(auto elem : items){
        QVariant data = elem->data(Qt::UserRole);
        unsigned iDArt = data.toUInt();
        conferenza->setIDArticoliPubblicati(iDArt);
    }
    g.aggiungiConferenza(conferenza);
    QMessageBox::information(
        this,
        tr("Application Name"),
        tr("Conferenza aggiunta correttamente!") );

    ui->nomeConferenza->clear();
    ui->acronimoConferenza->clear();
    ui->luogoConferenza->clear();
    ui->dataConferenza->clear();
    ui->numeroPartecipanti->clear();
    ui->listaOrganizzatori->clear();
    ui->listWidget_5->clear();

}

void MainWindow::on_sezione_A_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Sezione__A);
}


void MainWindow::on_visualizzaListe_clicked()
{
    if(ui->Visualizza_Autori->isChecked()){
        const list<Autore*>& a = g.visualizzaAutori();
        for(auto elem : a){
            stringstream s;
            s << *elem;
            ui->listWidget_7->addItem(QString::fromStdString(s.str()));
        }
       }
    else if(ui->visualizza_conferenze->isChecked()){
        const list<Conferenza*>& c = g.visualizzaConferenze();
        for(auto elem: c){
            stringstream s;
            s << *elem;
            ui->listWidget_7->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->visualizza_riviste->isChecked()){
        const list<Rivista*>& r = g.visualizzaRiviste();
        for(auto elem : r){
            stringstream s;
            s << *elem;
            ui->listWidget_7->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->visualizza_articoli->isChecked()){
        const list<Articolo*>& a = g.visualizzaArticoli();
        for(auto elem : a){
            stringstream s;
            s << *elem;
            ui->listWidget_7->addItem(QString::fromStdString(s.str()));
        }
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_AggiungiRivista_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Aggiungi_Rivista);
}

void MainWindow::on_aggiungiRiv_clicked()
{
    list<Articolo*> listaCompleta = g.visualizzaArticoli();
    QString nome = ui->nomeRivista->text();
    string n = nome.toStdString();

    QString acronimo = ui->acronimoRivista->text();
    string a = acronimo.toStdString();

    QString editore = ui->editoreRivista->text();
    string e = editore.toStdString();

    QString data = ui->dataRivista->text();
    unsigned d = data.toUInt();

    QString volume = ui->volumeRivista->text();
    unsigned v = volume.toUInt();

    list<Articolo*> listPubblicati;
    QList<QListWidgetItem*> items = ui->listWidget_6->selectedItems();
    for(auto elem : items){
        QVariant data = elem->data(Qt::UserRole);
        unsigned iDArt = data.toUInt();
        Articolo* art = Utility::getArticolo(iDArt,listaCompleta);
        art->setDataPubblicazioe(d);
        listPubblicati.push_back(art);
        g.rimuoviArticoloAggiunto(art);
    }

    Rivista* rivista = new Rivista(n,a,e,d,v,listPubblicati);
    for(auto elem : items){
        QVariant data = elem->data(Qt::UserRole);
        unsigned iDArt = data.toUInt();
        rivista->setIDArticoliPubblicati(iDArt);
    }
    g.aggiungiRivista(rivista);
    QMessageBox::information(
        this,
        tr("Application Name"),
        tr("Rivista aggiunta correttamente!") );


    ui->nomeRivista->clear();
    ui->acronimoRivista->clear();
    ui->editoreRivista->clear();
    ui->dataRivista->clear();
    ui->volumeRivista->clear();




}

void MainWindow::on_pushButton_2_clicked()
{
    const list<Autore*>& a = g.visualizzaAutori();
    for(auto elem : a){
        stringstream s;
        s << *elem;
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_2);
        item->setData(Qt::UserRole, QVariant(elem->getId()));
        ui->listWidget_2->addItem(item);
    }
}

void MainWindow::on_Sezione_B_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Sezione__B);
}


void MainWindow::on_Sezione_C_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Sezione__C);
}

void MainWindow::on_Sezione_D_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Sezione__D);
}


void MainWindow::on_Sezione_E_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Sezione__E);
}

void MainWindow::on_visualizzaB_clicked()
{

    if(ui->visArticoliAutoreB->isChecked()){
        const list<Autore*>& l = g.visualizzaAutori();
        unsigned idAutore;
        QList<QListWidgetItem*> items = ui->listWidget_8->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            idAutore = data.toUInt();
        }
        Autore* aut = Utility::getAutore(idAutore,l);
        const list<Articolo*>& a = g.visualizzaArticoliAutore(aut);
        for(auto elem : a){
            stringstream s;
            s << *elem;
            ui->listWidget_3->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->visArticoliAutoreAnnoB->isChecked()){
        const list<Autore*>& l = g.visualizzaAutori();
        QString data = ui->lineData->text();
        unsigned idAutore;
        QList<QListWidgetItem*> items = ui->listWidget_8->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            idAutore = data.toUInt();
        }
        unsigned d = data.toUInt();

        Autore* aut = Utility::getAutore(idAutore,l);
        const list<Articolo*>& a = g.visualizzaArticoliAutoreAnno(aut,d);
        for(auto elem : a){
             stringstream s;
             s << *elem;
             ui->listWidget_3->addItem(QString::fromStdString(s.str()));
         }
    }
    else if(ui->visArticoliKeywordB){
        QString keyword = ui->lineKeyword->text();
        string k = keyword.toStdString();
        const list<Articolo*>& a = g.visualizzaArticoliKeyword(k);
        for(auto elem : a){
            stringstream s;
            s << *elem;
            ui->listWidget_3->addItem(QString::fromStdString(s.str()));
        }
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget_4->clear();
    if(ui->visMediaPrezziAutoreC->isChecked()){
        const list<Autore*>& l = g.visualizzaAutori();
        unsigned idAutore;
        QList<QListWidgetItem*> items = ui->listWidget_8->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            idAutore = data.toUInt();
        }
        Autore* aut = Utility::getAutore(idAutore,l);
        double d = g.visualizzaMediaPrezziAutore(aut);
        stringstream s;
        s << d;
        QMessageBox::information(this,"Prezzo Medio", "Il prezzo medio degli articoli dell'Autore è: " + QString::fromStdString(s.str()), QMessageBox::Ok);
    }
    else if(ui->visArticoliPrezzoBassoC->isChecked()){
        const list<Autore*>& l = g.visualizzaAutori();
        unsigned idAutore;
        QList<QListWidgetItem*> items = ui->listWidget_9->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            idAutore = data.toUInt();
        }
        Autore* aut = Utility::getAutore(idAutore,l);
        const list<Articolo*>& a = g.visualizzaArticoliPrezzoBasso(aut);
        for(auto elem : a){
            stringstream s;
            s << *elem;
            ui->listWidget_4->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->visArticoliPrezzoAltoC->isChecked()){
        const list<Autore*>& l = g.visualizzaAutori();
        unsigned idAutore;
        QList<QListWidgetItem*> items = ui->listWidget_9->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            idAutore = data.toUInt();
        }
        Autore* aut = Utility::getAutore(idAutore,l);
        const list<Articolo*>& a = g.visualizzaArticoliPrezzoAlto(aut);
        for(auto elem : a){
            stringstream s;
            s << *elem;
            ui->listWidget_4->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->visKeywordGuadagno->isChecked()){
        list<string> key = g.visualizzaKeywordGuadagno();
        for(auto elem : key){
            stringstream s;
            s << elem;
            ui->listWidget_4->addItem(QString::fromStdString(s.str()));
        }
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_visAutori_clicked()
{
    const list<Autore*>& a = g.visualizzaAutori();
    for(auto elem : a){
        stringstream s;
        s << *elem;
        ui->listWidget_5->addItem(QString::fromStdString(s.str()));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget_5->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget_2->clear();
}




void MainWindow::on_pushButton_9_clicked()
{
    const list<Autore*>& a = g.visualizzaAutori();
    for(auto elem : a){
        stringstream s;
        s << *elem;
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_8);
        item->setData(Qt::UserRole, QVariant(elem->getId()));
        ui->listWidget_8->addItem(item);
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->listWidget_8->clear();
}

void MainWindow::on_pushButton_11_clicked()
{
    const list<Autore*>& a = g.visualizzaAutori();
    for(auto elem : a){
        stringstream s;
        s << *elem;
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_9);
        item->setData(Qt::UserRole, QVariant(elem->getId()));
        ui->listWidget_9->addItem(item);
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->listWidget_9->clear();
}

void MainWindow::on_pushButton_13_clicked()
{
    if(ui->radioButton_3->isChecked()){
        const list<Autore*>& a = g.visualizzaAutori();
        for(auto elem : a){
            stringstream s;
            s << *elem;
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_10);
            item->setData(Qt::UserRole, QVariant(elem->getId()));
            ui->listWidget_10->addItem(item);
        }
    }
    else if(ui->radioButton_4->isChecked()){
        const list<Conferenza*>& c = g.visualizzaConferenze();
        for(auto elem : c){
            stringstream s;
            s << *elem;
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_10);
            item->setData(Qt::UserRole,QVariant(QString::fromStdString(elem->getNome())));
            ui->listWidget_10->addItem(item);
        }
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    if(ui->visArtiAutD->isChecked()){
        const list<Autore*>& l = g.visualizzaAutori();
        unsigned idAutore;
        QList<QListWidgetItem*> items = ui->listWidget_10->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            idAutore = data.toUInt();
        }
        Autore* aut = Utility::getAutore(idAutore,l);
        const list<Articolo*>& art = g.visualizzaArticoliAutorePrezzo(aut);
        for(auto elem : art){
            stringstream s;
            s << *elem;
            ui->listWidget_11->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->visArtConfD->isChecked()){
        const list<Conferenza*>& l = g.visualizzaConferenze();
        QString p;
        QList<QListWidgetItem*> items = ui->listWidget_10->selectedItems();
        QListWidgetItem* item = items.front();
        QVariant data = item->data(Qt::UserRole);
        p = data.toString();

        string s = p.toStdString();

        Conferenza* conf = Utility::getConferenza(s,l);
        list<Articolo*> lista = g.visualizzaArticoliConferenzaPrezzo(conf);
        for(auto elem : lista){
            stringstream s;
            s << *elem;
            ui->listWidget_11->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->visArtKetD->isChecked()){
        QString key = ui->lineEditD->text();
        string k = key.toStdString();
        list<Articolo*> lista = g.visualizzaArticoliKeywordSorted(k);
        for(auto elem : lista){
            stringstream s;
            s << *elem;
            ui->listWidget_11->addItem(QString::fromStdString(s.str()));
        }

    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    if(ui->radioConfkey->isChecked()){

        const list<Conferenza*>& lista = g.visualizzaConferenzeKeywordComune();
        for(auto elem : lista){
            stringstream s;
            s << *elem;
            ui->listWidgetE->addItem(QString::fromStdString(s.str()));
        }

    }
    else if(ui->radioRivSpec->isChecked()){
        const list<Rivista*> lista = g.visualizzaRivisteSpecialistiche();
        for(auto elem : lista){
            stringstream s;
            s << *elem;
            ui->listWidgetE->addItem(QString::fromStdString(s.str()));
        }
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->StackedWidget->setCurrentWidget(ui->Sezione__F);
}

void MainWindow::on_pushButton_18_clicked()
{
    if(ui->radioButton->isChecked()){
        const list<Conferenza*>& c = g.visualizzaConferenze();
        for(auto elem : c){
           stringstream s;
            s << *elem;
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_12);
            item->setData(Qt::UserRole, QVariant(QString::fromStdString(elem->getNome())));
            ui->listWidget_12->addItem(item);
        }
    }
    else if(ui->radioButton_2->isChecked()){
        const list<Articolo*>& l = g.visualizzaArticoli();
        for(auto elem : l){
            stringstream s;
            s << *elem;
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_12);
            item->setData(Qt::UserRole, QVariant(elem->getId()));
            ui->listWidget_12->addItem(item);
        }
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_pushButton_20_clicked()
{

    if(ui->radioButton->isChecked()){
        const list<Conferenza*>& l = g.visualizzaConferenze();
        QString p;
        QList<QListWidgetItem*> items = ui->listWidget_12->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            p = data.toString();
        }

        string s = p.toStdString();

        Conferenza* conf = Utility::getConferenza(s,l);


        list<Conferenza*> confer = g.visualizzaConferenzeSimili(conf);
        for(auto elem : confer){
            stringstream s;
            s << *elem;
            ui->listWidgetF->addItem(QString::fromStdString(s.str()));
        }
    }
    else if(ui->radioButton_2->isChecked()){

        unsigned iDArt;
        QList<QListWidgetItem*> items = ui->listWidget_12->selectedItems();
        for(auto elem : items){
            QVariant data = elem->data(Qt::UserRole);
            iDArt = data.toUInt();
        }
        Articolo* art = Utility::getArticolo(iDArt,g.visualizzaArticoli());

        list<Articolo*> lista = g.visualizzaArticoliInfluenzati(art);
        for(auto elem : lista){
            stringstream s;
            s << * elem;
            ui->listWidgetF->addItem(QString::fromStdString(s.str()));
        }
    }
    else{
        QMessageBox::information(
            this,
            tr("Application Name"),
            tr("Selezionare almeno un'opzione!") );
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    ui->listWidget_13->clear();
}

void MainWindow::on_pushButton_21_clicked()
{
    const list<Articolo*>& l = g.visualizzaArticoli();
    for(auto elem : l){
        stringstream s;
        s << *elem;
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_13);
        item->setData(Qt::UserRole, QVariant(elem->getId()));
        ui->listWidget_13->addItem(item);
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    ui->listWidget_3->clear();
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->listWidget_10->clear();
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->listWidgetE->clear();
}

void MainWindow::on_visArticoli_clicked()
{
    const list<Articolo*>& l = g.visualizzaArticoliCopia();
    for(auto elem : l){
        stringstream s;
        s << *elem;
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_5);
        item->setData(Qt::UserRole, QVariant(elem->getId()));
        ui->listWidget_5->addItem(item);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    const list<Articolo*>& l = g.visualizzaArticoliCopia();
    for(auto elem : l){
        stringstream s;
        s << *elem;
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(s.str()), ui->listWidget_6);
        item->setData(Qt::UserRole, QVariant(elem->getId()));
        ui->listWidget_6->addItem(item);
    }
}

void MainWindow::on_pushButton_25_clicked()
{
    ui->listWidgetF->clear();
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->listWidget_12->clear();
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->listWidget_6->clear();
}
