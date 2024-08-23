#include "cardindex.h"
#include "ui_cardindex.h"

CardIndex::CardIndex(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CardIndex)
{
    ui->setupUi(this);
    connect(ui->b_add, &QPushButton::clicked, this, &CardIndex::add);
    connect(ui->b_edit, &QPushButton::clicked, this, &CardIndex::edit);
    connect(ui->b_remove, &QPushButton::clicked, this, &CardIndex::remove);
    connect(ui->b_filter, &QPushButton::clicked, this, &CardIndex::filter);
    connect(ui->l_records, &QListWidget::itemClicked, this, &CardIndex::select);
}

CardIndex::~CardIndex()
{
    delete ui;
}

void CardIndex::filter()
{

    ui->l_records->clear();
    ui->e_selected->clear();
    bool typeEmpty = ui->e_type->text().isEmpty();
    bool titleEmpty = ui->e_title->text().isEmpty();
    bool authorEmpty = ui->e_author->text().isEmpty();
    bool libraryEmpty = ui->e_library->text().isEmpty();
    bool dateEmpty = !ui->cb_sortByDate->isChecked();
    for (int record = 0; record < m_records.size(); ++record) {
        bool typeMatch = m_records[record]->getType().contains(ui->e_type->text());
        bool titleMatch = m_records[record]->getTitle().contains(ui->e_title->text());
        bool authorMatch = m_records[record]->getAuthor().contains(ui->e_author->text());
        bool libraryMatch = m_records[record]->getLibrary().contains(ui->e_library->text());
        bool dateMatch = m_records[record]->getDate() == ui->e_date->date();
        if (
            (typeEmpty || typeMatch)
            && (titleEmpty || titleMatch)
            && (authorEmpty || authorMatch)
            && (libraryEmpty || libraryMatch)
            && (dateEmpty || dateMatch)
            )
            ui->l_records->addItem(m_records[record]->getTitle());

    }
}

void CardIndex::add()
{
    if (findRecordByTitle(ui->e_title->text()) != NULL)
        return;
    Record* record = new Record();
    setRecordData(record);
    m_records.append(record);
    reloadRecords();
}

void CardIndex::edit()
{
    QListWidgetItem* item = ui->l_records->currentItem();
    if (item == NULL)
        return;
    Record* record = findRecordByTitle(item->text());
    setRecordData(record);
    reloadRecords();
}

void CardIndex::remove()
{
    QListWidgetItem* item = ui->l_records->currentItem();
    if (item == NULL)
        return;
    for (int record = 0; record < m_records.size(); ++record)
        if (item->text() == m_records[record]->getTitle()) {
            delete m_records[record];
            m_records.removeAt(record);
        }
    reloadRecords();

}

void CardIndex::select(QListWidgetItem * item)
{
    for (int record = 0; record < m_records.size(); ++record) {
        Record* currentRecord = m_records[record];
        if (item->text() == currentRecord->getTitle()) {
            ui->e_selected->setText("Type: " + currentRecord->getType() + "\n"
                                    + "Title: " + currentRecord->getTitle() + "\n"
                                    + "Author: " + currentRecord->getAuthor() + "\n"
                                    + "Library: " + currentRecord->getLibrary() + "\n"
                                    + "Date: " + currentRecord->getDate().toString());
            break;
        }
    }
}

Record *CardIndex::findRecordByTitle(QString title)
{
    for (int record = 0; record < m_records.size(); ++record)
        if (title == m_records[record]->getTitle())
            return m_records[record];
    return nullptr;
}

void CardIndex::reloadRecords()
{
    ui->l_records->clear();
    for (int record = 0; record < m_records.size(); ++record)
        ui->l_records->addItem(m_records[record]->getTitle());
}

void CardIndex::setRecordData(Record* record)
{
    record->setType(ui->e_type->text());
    record->setTitle(ui->e_title->text());
    record->setAuthor(ui->e_author->text());
    record->setLibrary(ui->e_library->text());
    record->setDate(ui->e_date->date());
}
