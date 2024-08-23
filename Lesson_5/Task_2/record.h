#ifndef RECORD_H
#define RECORD_H

#include <QObject>
#include <QDate>

class Record : public QObject
{
    Q_OBJECT
public:
    explicit Record(QObject *parent = nullptr);
    QString getType() { return m_type; }
    void setType(QString type) { m_type = type; }
    QString getTitle() { return m_title; }
    void setTitle(QString title) { m_title = title; }
    QString getAuthor() { return m_author; }
    void setAuthor(QString author) { m_author = author; }
    QString getLibrary() { return m_library; }
    void setLibrary(QString library) { m_library = library; }
    QDate getDate() { return m_date; }
    void setDate(QDate date) { m_date = date; }

signals:

private:
    QString m_type;
    QString m_title;
    QString m_author;
    QString m_library;
    QDate m_date;
};

#endif // RECORD_H
