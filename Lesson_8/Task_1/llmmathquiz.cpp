#include "llmmathquiz.h"
#include "ui_llmmathquiz.h"

LlmMathQuiz::LlmMathQuiz(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LlmMathQuiz)
{
    ui->setupUi(this);
    connect(ui->b_submit, &QPushButton::clicked, this, &LlmMathQuiz::submit);
    connect(ui->b_generate, &QPushButton::clicked, this, &LlmMathQuiz::generate);
    connect (m_manager, &QNetworkAccessManager::finished, this, &LlmMathQuiz::newAnswer);
}

LlmMathQuiz::~LlmMathQuiz()
{
    delete ui;
}

void LlmMathQuiz::submit()
{
    if (ui->e_user->text().isEmpty())
        return;

    ui->e_llm->setText(m_llmAnswer);
    ui->b_submit->setEnabled(false);
    ui->e_user->setReadOnly(true);

    if (m_llmAnswer.contains(ui->e_user->text())) {
        ui->l_matched->setText(QString::number(ui->l_matched->text().toInt() + 1));
        ui->l_match->setText("True");
    } else
        ui->l_match->setText("False");

    ui->b_generate->setEnabled(true);

    if (ui->l_number->text().toInt() == 10)
        ui->l_score->setText("Final score:");
}

void LlmMathQuiz::generate()
{
    if (m_taskReceived) {
        m_taskReceived = false;
        if (ui->l_number->text().toInt() == 10) {
            ui->l_number->setText(QString::number(0));
            ui->l_matched->setText(QString::number(0));
            ui->l_score->setText("Answers matched:");
        } else
            ui->l_number->setText(QString::number(ui->l_number->text().toInt() + 1));
    }
    m_taskReceived = false;
    ui->b_generate->setEnabled(false);
    ui->e_task->setText("Generating…");
    ui->e_user->clear();
    ui->e_llm->clear();
    ui->l_match->setText("Not checked");

    sendPrompt("Generate a math task and a correct answer for it. The task can be anything from simple equations, to logical tasks. Both the task and the answer need to take only one line. Provide the task on the first line, and the answer on the second line. Never use equation 2x + 5 = 11.");
}

void LlmMathQuiz::newAnswer(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray textReply = reply->readAll();
        QStringList data = QJsonDocument::fromJson(textReply).object().value("response").toString().split('\n');
        ui->e_task->setText(data[0]);
        m_llmAnswer = data[1].isEmpty() ? data[2] : data[1];
        m_taskReceived = true;
        ui->b_submit->setEnabled(true);
        ui->e_user->setReadOnly(false);
    } else {
        ui->e_task->setText("Error!");
        ui->b_generate->setEnabled(true);
    }
}

void LlmMathQuiz::sendPrompt(QString prompt)
{
    QNetworkRequest request(QUrl("http://127.0.0.1:11434/api/generate"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "llama3.1:8b";
    json["prompt"] = prompt;
    json["stream"] = false;

    m_manager->post(request, QJsonDocument(json).toJson());
}
