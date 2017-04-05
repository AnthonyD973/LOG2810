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
    _listeSuggestions->clear();
}

// PRIVATE:

void BoiteAutoCompletion::_connecter() const {
    connect(_listeSuggestions, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(fermer(QListWidgetItem*)));
}

// PUBLIC SLOTS:

void BoiteAutoCompletion::fermer(QListWidgetItem* itemSuggestion) {
    if (itemSuggestion != Q_NULLPTR) {
        QString suggestion = itemSuggestion->text();
        emit suggestionChoisie(suggestion);
    }

    viderItems();
    hide();
}
