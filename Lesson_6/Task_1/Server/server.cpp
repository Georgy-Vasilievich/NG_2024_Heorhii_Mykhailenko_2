#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    m_server = new QTcpServer();

    connect (m_server, &QTcpServer::newConnection, this, &Server::newClient);
}

Server::~Server()
{
    if (m_server->isListening()) {
        qDebug() << "Closing server...";
        m_server->close();
    }
    delete m_server;
}

void Server::start(QString host, int port)
{
    bool ok = m_server->listen(QHostAddress(host), port);
    if (ok) {
        qDebug() << "We are online!";
    } else {
        qDebug() << "Error creating connection: " << m_server->errorString();
    }
}

void Server::newClient()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    qDebug() << "Client " << client->localAddress().toString();

    connect (client, &QTcpSocket::disconnected, this, &Server::leftClient);
    connect (client, &QTcpSocket::readyRead, this, &Server::messageFromClient);

    m_clients.append(client);
}

void Server::leftClient()
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    qDebug() << "Client " << socket->localAddress().toString() << " has been left";
    m_clients.removeOne(socket);
}

void Server::messageFromClient()
{
    QTcpSocket *socket = (QTcpSocket *)sender();
    QStringList lines = QString(socket->readAll()).split('\n');
    QString fileName;

    fileName = lines[0];
    lines.removeFirst();

    QFile file(fileName);
    if (file.open(QIODevice::Append)) {
        for (int line = 0; line < lines.size(); ++ line) {
            file.write((lines[line] + '\n').toUtf8());
        }
    }

    file.close();
}
