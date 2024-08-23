#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDataStream>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QVector>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

public slots:
    void start(QString host, int port);

private slots:
    void newClient();
    void leftClient();
    void messageFromClient();
signals:

private:
    QTcpServer *m_server = nullptr;
    QVector<QTcpSocket *> m_clients;
    bool isInfoGot = false;
    QString fileName;
    int fileSize;

signals:
};

#endif // SERVER_H
