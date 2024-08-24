#ifndef LLMMATHQUIZ_H
#define LLMMATHQUIZ_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class LlmMathQuiz; }
QT_END_NAMESPACE

class LlmMathQuiz : public QMainWindow
{
    Q_OBJECT

public:
    LlmMathQuiz(QWidget *parent = nullptr);
    ~LlmMathQuiz();

private slots:
    void newTask();
    void answer();
    void newResponse(QNetworkReply*);

private:
    Ui::LlmMathQuiz *ui;
    QNetworkAccessManager *m_manager = new QNetworkAccessManager();
    void send(QString);
    QString m_context = "";
    bool m_taskReceived = false;
    QString m_answer;
    int m_tasks;
    int m_score;
};
#endif // LLMMATHQUIZ_H
