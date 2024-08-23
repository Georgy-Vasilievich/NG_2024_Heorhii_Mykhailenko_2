#include "llmmathquiz.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LlmMathQuiz w;
    w.show();
    return a.exec();
}
