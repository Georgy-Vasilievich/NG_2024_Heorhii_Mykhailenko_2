#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include <QObject>

class Automobile : public QObject
{
    Q_OBJECT
public:
    explicit Automobile(QObject *parent = nullptr);
    QString getManufacturer() { return m_manufacturer; }
    void setManufacturer(QString manufacturer) { m_manufacturer = manufacturer; }
    float getPrice() { return m_price; }
    void setPrice(int price) { m_price = price; }
    QString getType() { return m_type; }
    void setType(QString type) { m_type = type; }

signals:

protected:
    float m_price;
    QString m_type;
private:
    QString m_manufacturer;

};

#endif // AUTOMOBILE_H
