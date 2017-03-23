#include "DispositionChoixLexique.h"

DispositionChoixLexique::DispositionChoixLexique(QWidget* parent)
    : QVBoxLayout(parent)
{
    _dispoBarreEtat     = new QVBoxLayout (parent);
    _dispoBarreEtat->addWidget(_barreEtat);
    _dispoBarreEtat->addWidget(_etqQuelEtat);

    _dispoChoixLexique  = new QVBoxLayout (parent);

    _dispoChoixLexique->addWidget(_btnChoixLexique);
    _dispoChoixLexique->addWidget(_btnStart);
}
