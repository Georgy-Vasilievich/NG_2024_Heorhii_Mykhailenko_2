#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    connect (ui->b_connect, &QPushButton::clicked, this, &Client::connectPressed);
    connect (ui->b_selectFile, &QPushButton::clicked, this, &Client::selectFile);
    connect (ui->b_send, &QPushButton::clicked, this, &Client::sendFile);
    connect (m_socket, &QTcpSocket::connected, this, &Client::connectionEstablished);
}

Client::~Client()
{
    delete ui;
}

void Client::sendFile()
{
    ui->l_status->setText("Connected");

    QFile file(m_fileName);
    QFileInfo fi(m_fileName);

    if (file.open(QIODevice::ReadOnly)) {
        m_socket->write((fi.fileName() + '\n').toUtf8());

        QTextStream in(&file);

        while (!in.atEnd())
            m_socket->write((in.readLine() + '\n').toUtf8());
    }

    ui->l_status->setText("File sent");
    ui->b_send->setEnabled(false);

}

void Client::connectPressed()
{
    if (m_socket->isOpen()) {
        m_socket->close();
        ui->l_status->setText("Not connected");
        ui->b_connect->setText("Connect");
        ui->b_send->setEnabled(false);
        return;
    }
    QString address = ui->e_address->text();
    int port = ui->sb_port->value();

    ui->b_connect->setText("Disconnect");
    ui->l_status->setText("Connecting");

    m_socket->connectToHost(QHostAddress(address), port);
}

void Client::connectionEstablished()
{
    ui->l_status->setText("Connected");
    checkSendingAllowed();
}

void Client::checkSendingAllowed()
{
    if (!m_fileName.isEmpty() && m_socket->isOpen())
        ui->b_send->setEnabled(true);
}

void Client::selectFile()
{
    m_fileName = QFileDialog::getOpenFileName(this, "Select file", "", "All Files (*)");

    if (m_fileName.isEmpty())
        return;

    checkSendingAllowed();
}


