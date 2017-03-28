#ifndef BOITE_AUTO_COMPLETION_H
#define BOITE_AUTO_COMPLETION_H

#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStringList>

class BoiteAutoCompletion : public QDialog
{

    Q_OBJECT

public:
    BoiteAutoCompletion(QWidget* parent);

    void setItems(const QStringList& listeSuggestions);
    void viderItems();

signals:
    void suggestionChoisie(QString suggestion);

public slots:
    void fermer(QListWidgetItem* itemSuggestion = Q_NULLPTR);

private:
    void _connecter() const;

private:
    QVBoxLayout*    _disposition;
    QListWidget*    _listeSuggestions;

};

#endif // !BOITE_AUTO_COMPLETION_H
