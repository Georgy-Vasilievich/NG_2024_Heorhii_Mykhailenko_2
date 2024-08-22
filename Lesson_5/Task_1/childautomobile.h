#ifndef CHILDAUTOMOBILE_H
#define CHILDAUTOMOBILE_H

#include <QColor>
#include <automobile.h>

class ChildAutomobile : public Automobile
{
public:
    explicit ChildAutomobile(QObject *parent = nullptr);
    QString getModel() { return m_model; }
    void setModel(QString model) { m_model = model; }
    int getSeats() { return m_seats; }
    void setSeats(int seats) { m_seats = seats; }
    QColor getColor() { return m_color; }
    void setColor(QColor color) { m_color = color; }

    void setModel(const char *);
signals:

private:
    QString m_model;
    int m_seats;
    QColor m_color;
};

#endif // CHILDAUTOMOBILE_H
