#include "Editeur.h"

Editeur::Editeur(QWidget* parent)
    : QWidget(parent)
{
    _btnRetour = new QPushButton(parent);

    _editeur = new QTextEdit(parent);

    _caseAutoCompletion     = new QCheckBox(parent);
    _caseAutoCorrection     = new QCheckBox(parent);
    QVBoxLayout* dispoGroupeTypeCorrection = new QVBoxLayout(parent);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCompletion);
    dispoGroupeTypeCorrection->addWidget(_caseAutoCorrection);

    _groupeTypeCorrection   = new QGroupBox(parent);
    _groupeTypeCorrection->setLayout(dispoGroupeTypeCorrection);

    _boiteSuggestions = new QMessageBox(parent);
    _boiteSuggestions->hide();

    _disposition = new QVBoxLayout(parent);

    _disposition->addWidget(_btnRetour);
    _disposition->addWidget(_editeur);
    _disposition->addWidget(_groupeTypeCorrection);
    _disposition->addWidget(_boiteSuggestions);

    setLayout(_disposition);
}
