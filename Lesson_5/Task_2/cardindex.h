#ifndef CARDINDEX_H
#define CARDINDEX_H

#include <QMainWindow>
#include <QListWidget>
#include <record.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class CardIndex;
}
QT_END_NAMESPACE

class CardIndex : public QMainWindow
{
    Q_OBJECT

public:
    CardIndex(QWidget *parent = nullptr);
    ~CardIndex();

private slots:
    void filter();
    void add();
    void edit();
    void remove();
    void select(QListWidgetItem *);


private:
    Ui::CardIndex *ui;
    QVector<Record *> m_records;

    Record *findRecordByTitle(QString title);
    void reloadRecords();
    void setRecordData(Record *);
};
#endif // CARDINDEX_H
