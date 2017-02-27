#ifndef SOLUTIONOPTIMISATION_H
#define SOLUTIONOPTIMISATION_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

class SolutionOptimisation : public QWidget
{
    Q_OBJECT

public:
    explicit SolutionOptimisation(QWidget* parent = Q_NULLPTR);

private:
    QVBoxLayout*    _dispositionHorizontale;

    QHBoxLayout*    _trouveeEn;
    QVBoxLayout*    _solutionTrouvee;
    QHBoxLayout*    _distanceTotale;
    QHBoxLayout*    _gainTotal;

signals:

public slots:
};

#endif // SOLUTIONOPTIMISATION_H
