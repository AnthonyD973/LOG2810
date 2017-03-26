#include "BoiteAutoCompletion.h"

BoiteAutoCompletion::BoiteAutoCompletion(QWidget* parent)
    : QDialog(parent)
{
    _listeSuggestions = new QListWidget(parent);
    _disposition      = new QVBoxLayout(parent);
    _disposition->addWidget(_listeSuggestions);

    setLayout(_disposition);
    setFixedSize(200, 200);

    _connecter();
}

void BoiteAutoCompletion::setItems(const QStringList& listeSuggestions) {
    viderItems();
    _listeSuggestions->addItems(listeSuggestions);
}

void BoiteAutoCompletion::viderItems() {
    int ligne = 0;
    QListWidgetItem* suggestion = _listeSuggestions->takeItem(ligne++);
    while (suggestion != Q_NULLPTR) {
        delete suggestion;
        suggestion = _listeSuggestions->takeItem(ligne++);
    }
}

// PRIVATE:

void BoiteAutoCompletion::_connecter() const {
    connect(_listeSuggestions, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(_fermer(QListWidgetItem*)));
}

// PRIVATE SLOTS:

void BoiteAutoCompletion::_fermer(QListWidgetItem* itemSuggestion) {
    if (itemSuggestion != Q_NULLPTR) {
        QString suggestion = itemSuggestion->text();
        emit suggestionChoisie(suggestion);
    }

    viderItems();
    hide();
}
