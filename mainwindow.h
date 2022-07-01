#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Gestore.h"

#include <QMainWindow>
#include <QDebug>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_AggiungiAutore_clicked();

    void on_Aggiungi1_clicked();

    void on_AggiungiArticolo_clicked();

    void on_sezione_A_clicked();

    void on_visualizzaListe_clicked();

    void on_clearLista_clicked();

    void on_AggiungiConferenza_clicked();

    void on_aggiungiConf_clicked();

    void on_AggiungiRivista_clicked();

    void on_aggiungiRiv_clicked();

    void on_pushButton_2_clicked();

    void on_Sezione_B_clicked();

    void on_Sezione_C_clicked();

    void on_Sezione_D_clicked();

    void on_Sezione_E_clicked();

    void on_visualizzaB_clicked();

    void on_pushButton_3_clicked();

    void on_visAutori_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_24_clicked();

    void on_visArticoli_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    Gestore g;
};
#endif // MAINWINDOW_H
