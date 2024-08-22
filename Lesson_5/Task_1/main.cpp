#include "autoservice.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoService w;
    w.show();
    return a.exec();
}
