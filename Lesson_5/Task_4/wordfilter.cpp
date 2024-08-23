#include "wordfilter.h"
#include "ui_wordfilter.h"

Wordfilter::Wordfilter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Wordfilter)
{
    ui->setupUi(this);
    connect(ui->b_select, &QPushButton::clicked, this, &Wordfilter::selectFile);
    connect(ui->b_filter, &QPushButton::clicked, this, &Wordfilter::filter);
}

Wordfilter::~Wordfilter()
{
    delete ui;
}

void Wordfilter::selectFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open word list", "", "Text files (*.txt);;All Files (*)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        QStringList words;
        QTextStream in(&file);

        while (!in.atEnd())
            words.append(in.readLine());

        setWords(words);
    }

    file.close();
}

void Wordfilter::filter()
{
    QString text = ui->e_text->toPlainText();
    for (QString word : m_words)
        text.replace(word, "[filtered]");
    ui->e_text->setText(text);
}
