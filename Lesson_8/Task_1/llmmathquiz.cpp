#include "llmmathquiz.h"
#include "ui_llmmathquiz.h"

LlmMathQuiz::LlmMathQuiz(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LlmMathQuiz)
{
    ui->setupUi(this);
    connect(ui->b_new, &QPushButton::clicked, this, &LlmMathQuiz::newTask);
    connect(ui->b_answer, &QPushButton::clicked, this, &LlmMathQuiz::answer);
    connect(m_manager, &QNetworkAccessManager::finished, this, &LlmMathQuiz::newResponse);
}

LlmMathQuiz::~LlmMathQuiz()
{
    delete ui;
}

void LlmMathQuiz::newTask()
{
    ui->b_new->setEnabled(false);
    ui->e_task->setText("Generating…");
    ui->e_answer->clear();

    send("Write a arithmetical or logical task with numbers not larger than 10 and not similar to previous tasks. Use one line for a task and one line for the answer for it. Do not add empty lines.");

}

void LlmMathQuiz::answer()
{
    if (ui->e_answer->text().isEmpty())
        return;

    ui->b_answer->setEnabled(false);
    ui->e_answer->setReadOnly(true);

    send("There are two answers provided\n"
         + m_answer + '\n'
         + ui->e_answer->text() + '\n'
         + "If they are the same, respond with '+', and if they are not the same, respond with '-'. Do not send anything else.");
}

void LlmMathQuiz::newResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray textReply = reply->readAll();
        QJsonObject object = QJsonDocument::fromJson(textReply).object();
        QString response = object.value("response").toString();
        m_context = object.value("context").toString();
        bool error = false;
        if (!m_taskReceived) {
            QStringList data = response.split('\n');
            ui->e_task->setText(data[0]);
            if (data.length() < 2 ||
                    (data.length() == 2 && data[1].isEmpty())) {
                ui->e_task->clear();
                QMessageBox::critical(
                            this,
                            tr("Error"),
                            tr("Invalid task generated.") );
                ui->b_new->setEnabled(true);
                error = true;
            } else {
                m_answer = data[1].isEmpty() ? data[2] : data[1];
                ui->b_answer->setEnabled(true);
                ui->e_answer->setReadOnly(false);
            }
        } else {
            if (response == "+")  {
                ++m_score;
                QMessageBox::information(
                            this,
                            tr("Answer"),
                            tr("Answer correct.") );
            } else {
                QMessageBox::warning(
                            this,
                            tr("Answer"),
                            tr("Answer incorrect. The correct answer is: " + m_answer.toUtf8()) );
            }
            ++m_tasks;
            if (m_tasks == 5) {
                QMessageBox::information(
                            this,
                            tr("Score"),
                            tr("Your score is " + QString::number(m_score).toUtf8() + "/" + QString::number(m_tasks).toUtf8()) );
                m_score = 0;
                m_tasks = 0;
            }
            ui->b_new->setEnabled(true);
        }
        if (!error)
            m_taskReceived = !m_taskReceived;
    } else {
        ui->e_task->clear();
        QMessageBox::critical(
                    this,
                    tr("Error"),
                    tr("Connection error.") );
        if (m_taskReceived)
            ui->b_answer->setEnabled(true);
        else
            ui->b_new->setEnabled(true);
    }
}

void LlmMathQuiz::send(QString prompt)
{
    QNetworkRequest request(QUrl("http://127.0.0.1:11434/api/generate"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "llama3.1:8b";
    json["prompt"] = prompt;
    json["stream"] = false;
    if (!m_context.isEmpty())
        json["context"] = m_context;

    m_manager->post(request, QJsonDocument(json).toJson());
}

