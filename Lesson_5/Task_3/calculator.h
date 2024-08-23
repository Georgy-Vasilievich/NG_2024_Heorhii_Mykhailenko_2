#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void press0();
    void press1();
    void press2();
    void press3();
    void press4();
    void press5();
    void press6();
    void press7();
    void press8();
    void press9();
    void pressAdd();
    void pressSubtract();
    void pressMultiply();
    void pressDivide();
    void pressEquals();
    void pressDot();
    void pressCe();
    void pressAc();
    bool isDigit(QString);
    bool isOperator(QString);
    void calculate(bool);
    void clearIfDone();

private:
    Ui::Calculator *ui;
    void keyPressed(QString);
    float m_operand1;
    bool m_operand1Set = false;
    float m_operand2;
    QChar m_operator = (QChar)0;
    bool m_done = false;

};
#endif // CALCULATOR_H
