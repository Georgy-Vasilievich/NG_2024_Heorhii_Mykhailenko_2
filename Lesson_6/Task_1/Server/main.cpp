#include <QCoreApplication>
#include <server.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    server.start("0.0.0.0", 8081);
    return a.exec();
}
