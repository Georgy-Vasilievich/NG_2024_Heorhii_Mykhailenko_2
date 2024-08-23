#include "wordfilter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wordfilter w;
    w.show();
    return a.exec();
}
