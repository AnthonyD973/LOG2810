#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "ChoixLexique.h"
#include "Editeur.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void _connecter();
    void _montrerChoixLexique();
    void _montrerEditeur();

private:
    Ui::MainWindow *ui;

    ChoixLexique*   _choixLexique;
    Editeur*        _editeur;

public slots:
    void montrerChoixLexique();
    void montrerEditeur();

};

#endif // !MAINWINDOW_H
