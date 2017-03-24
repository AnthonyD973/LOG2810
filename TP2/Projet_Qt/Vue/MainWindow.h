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

private:
    Ui::MainWindow *ui;

public slots:
    void allerAuChoixLexique();
    void allerAEditeur();

};

#endif // !MAINWINDOW_H
