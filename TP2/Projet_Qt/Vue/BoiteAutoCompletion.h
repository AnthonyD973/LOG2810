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

private:
    void _connecter() const;

private:
    QVBoxLayout*    _disposition;
    QListWidget*    _listeSuggestions;

signals:
    void suggestionChoisie(QString suggestion);

private slots:
    void _fermer(QListWidgetItem* itemSuggestion);

};

#endif // !BOITE_AUTO_COMPLETION_H
