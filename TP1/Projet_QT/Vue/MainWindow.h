#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QFrame>

#include "SelectionOptimisation.h"
#include "SolutionOptimisation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // =============
    // = ATTRIBUTS =
    // =============

private:
    Ui::MainWindow*         _ui;
    QVBoxLayout*            _boitePrincipale;

};

#endif // !MAINWINDOW_H
