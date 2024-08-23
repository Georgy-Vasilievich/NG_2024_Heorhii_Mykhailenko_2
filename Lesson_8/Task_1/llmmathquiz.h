#ifndef LLMMATHQUIZ_H
#define LLMMATHQUIZ_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui {
class LlmMathQuiz;
}
QT_END_NAMESPACE

class LlmMathQuiz : public QMainWindow
{
    Q_OBJECT

public:
    LlmMathQuiz(QWidget *parent = nullptr);
    ~LlmMathQuiz();

private slots:
    void submit();
    void generate();
    void newAnswer(QNetworkReply *);

private:
    void sendPrompt(QString);
    Ui::LlmMathQuiz *ui;
    QNetworkAccessManager *m_manager = new QNetworkAccessManager();
    bool m_taskReceived = false;
    QString m_llmAnswer;
};
#endif // LLMMATHQUIZ_H
