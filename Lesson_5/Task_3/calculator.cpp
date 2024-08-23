#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->b_0, &QPushButton::clicked, this, &Calculator::press0);
    connect(ui->b_1, &QPushButton::clicked, this, &Calculator::press1);
    connect(ui->b_2, &QPushButton::clicked, this, &Calculator::press2);
    connect(ui->b_3, &QPushButton::clicked, this, &Calculator::press3);
    connect(ui->b_4, &QPushButton::clicked, this, &Calculator::press4);
    connect(ui->b_5, &QPushButton::clicked, this, &Calculator::press5);
    connect(ui->b_6, &QPushButton::clicked, this, &Calculator::press6);
    connect(ui->b_7, &QPushButton::clicked, this, &Calculator::press7);
    connect(ui->b_8, &QPushButton::clicked, this, &Calculator::press8);
    connect(ui->b_9, &QPushButton::clicked, this, &Calculator::press9);
    connect(ui->b_add, &QPushButton::clicked, this, &Calculator::pressAdd);
    connect(ui->b_subtract, &QPushButton::clicked, this, &Calculator::pressSubtract);
    connect(ui->b_multiply, &QPushButton::clicked, this, &Calculator::pressMultiply);
    connect(ui->b_divide, &QPushButton::clicked, this, &Calculator::pressDivide);
    connect(ui->b_equals, &QPushButton::clicked, this, &Calculator::pressEquals);
    connect(ui->b_dot, &QPushButton::clicked, this, &Calculator::pressDot);
    connect(ui->b_ce, &QPushButton::clicked, this, &Calculator::pressCe);
    connect(ui->b_ac, &QPushButton::clicked, this, &Calculator::pressAc);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::press0()
{
    keyPressed("0");
}

void Calculator::press1()
{
    keyPressed("1");
}

void Calculator::press2()
{
    keyPressed("2");
}

void Calculator::press3()
{
    keyPressed("3");
}

void Calculator::press4()
{
    keyPressed("4");
}

void Calculator::press5()
{
    keyPressed("5");
}

void Calculator::press6()
{
    keyPressed("6");
}

void Calculator::press7()
{
    keyPressed("7");
}

void Calculator::press8()
{
    keyPressed("8");
}

void Calculator::press9()
{
    keyPressed("9");
}

void Calculator::pressAdd()
{
    keyPressed("+");
}

void Calculator::pressSubtract()
{
    keyPressed("-");
}

void Calculator::pressMultiply()
{
    keyPressed("*");
}

void Calculator::pressDivide()
{
    keyPressed("/");
}

void Calculator::pressEquals()
{
    keyPressed("=");
}

void Calculator::pressDot()
{
    keyPressed(".");
}

void Calculator::pressCe()
{
    keyPressed("CE");
}

void Calculator::pressAc()
{
    keyPressed("AC");
}

bool Calculator::isDigit(QString value)
{
    if (value == "0"
        || value == "1"
        || value == "2"
        || value == "3"
        || value == "4"
        || value == "5"
        || value == "6"
        || value == "7"
        || value == "8"
        || value == "9"
        )
        return true;
    return false;
}

bool Calculator::isOperator(QString value)
{
    if (value == "+"
        || value == "-"
        || value == "*"
        || value == "/"
        || value == "="
        )
        return true;
    return false;
}

void Calculator::calculate(bool clearOperand)
{
    m_operand2 = ui->e_display->text().toFloat();
    if (m_operator == '+')
        m_operand1 = m_operand1 + m_operand2;
    else if (m_operator == '-')
        m_operand1 = m_operand1 - m_operand2;
    else if (m_operator == '*')
        m_operand1 = m_operand1 * m_operand2;
    else if (m_operator == '/')
        m_operand1 = m_operand1 / m_operand2;
    ui->e_display->setText(QString::number(m_operand1));
    m_done = true;
    if (clearOperand)
        m_operand1Set = false;
}

void Calculator::clearIfDone()
{
    if (m_done) {
        ui->e_display->setText("0");
        m_done = false;
    }
}

void Calculator::keyPressed(QString keyName)
{
    if (isDigit(keyName)) {
        clearIfDone();

        if (ui->e_display->text() == "0")
            ui->e_display->setText(keyName);
        else
            ui->e_display->setText(ui->e_display->text() + keyName);
    }
    else if (keyName == ".") {
        clearIfDone();

        if (ui->e_display->text().contains("."))
            return;

        ui->e_display->setText(ui->e_display->text() + keyName);
    }
    else if (isOperator(keyName)) {
        if (!m_operand1Set && keyName != "=") {
            m_operand1Set = true;
            m_operand1 = ui->e_display->text().toFloat();
            m_operator = QChar(keyName[0]);
            ui->e_display->setText("0");
        } else if (m_operand1Set && !m_done) {
            if (keyName == "=")
                calculate(true);
            else {
                calculate(false);
                m_operator = QChar(keyName[0]);
            }

        }
    }
    else if (keyName == "CE") {
        QString text = ui->e_display->text();
        if (text.size() > 1)
            text.chop(1);
        else
            text = "0";
        ui->e_display->setText(text);
    }
    else if (keyName == "AC") {
        ui->e_display->setText("0");
        m_operand1Set = false;
        m_done = false;
    }
}

