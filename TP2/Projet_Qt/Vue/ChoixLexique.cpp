#include "ChoixLexique.h"

ChoixLexique::ChoixLexique(QWidget* parent)
    : QWidget(parent)
{
    _btnChoixLexique = new QPushButton((QString)"Choisir le lexique", parent);
    _btnStart        = new QPushButton((QString)"START!!", parent);
    _barreEtat       = new QProgressBar(parent);
    _etqQuelEtat     = new QLabel((QString)"I'm a label. Hello, World!", parent);

    _dispoBarreEtat  = new QVBoxLayout(parent);
    _dispoBarreEtat->addWidget(_barreEtat);
    _dispoBarreEtat->addWidget(_etqQuelEtat);

    _disposition     = new QVBoxLayout(parent);

    _disposition->addWidget(_btnChoixLexique);
    _disposition->addWidget(_btnStart);
    _disposition->addLayout(_dispoBarreEtat);

    setLayout(_disposition);
}
