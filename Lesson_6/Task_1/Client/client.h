#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QHostAddress>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void sendFile();
    void connectPressed();
    void connectionEstablished();
    void checkSendingAllowed();
    void selectFile();

private:
    Ui::Client *ui;
    QTcpSocket *m_socket = new QTcpSocket();
    QDataStream m_block;
    QFile m_file;
    QString m_fileName;
};
#endif // CLIENT_H
