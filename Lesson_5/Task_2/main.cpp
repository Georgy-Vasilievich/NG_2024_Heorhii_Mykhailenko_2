#include "cardindex.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CardIndex w;
    w.show();
    return a.exec();
}
