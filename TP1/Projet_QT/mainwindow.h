#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>

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
    Ui::MainWindow *ui;

    // =============
    // = ATTRIBUTS =
    // =============

private:
    QPushButton* _boutonSelectionnerFichier;
    QLabel* _etiquetteOptimiserPour;
    QButtonGroup* _groupeQuoiOptimiser;
    QPushButton* _boutonOptimiser;

    QLabel* _etiquetteSolutionOptimaleTrouvee;
    //...;
    QLabel* _etiquetteDistanceTotale;
    QLabel* _etiquetteGainTotal;
    QLabel* _etiquetteTrouveeEn;


};

#endif // !MAINWINDOW_H
