#ifndef WORDFILTER_H
#define WORDFILTER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class Wordfilter;
}
QT_END_NAMESPACE

class Wordfilter : public QMainWindow
{
    Q_OBJECT

public:
    Wordfilter(QWidget *parent = nullptr);
    ~Wordfilter();
    QStringList getWords() { return m_words; }
    void setWords(QStringList words) { m_words = words; }

private:
    Ui::Wordfilter *ui;
    void selectFile();
    void filter();
    QStringList m_words;
};
#endif // WORDFILTER_H
