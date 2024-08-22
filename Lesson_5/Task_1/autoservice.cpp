#include "autoservice.h"
#include "ui_autoservice.h"

AutoService::AutoService(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AutoService)
{
    ui->setupUi(this);
    connect(ui->b_filter, &QPushButton::clicked, this, &AutoService::filter);
    connect(ui->l_automobiles, &QListWidget::itemClicked, this, &AutoService::select);

    generateAutomobiles();
}

AutoService::~AutoService()
{
    delete ui;
}

void AutoService::filter()
{
    ui->l_automobiles->clear();
    ui->e_selected->clear();
    bool manufacturerEmpty = ui->e_manufacturer->text().isEmpty();
    bool typeEmpty = ui->e_type->text().isEmpty();
    bool priceEmpty = ui->e_price->text().isEmpty();
    for (int automobile = 0; automobile < m_automobiles.size(); ++automobile) {
        bool manufacturerMatch = m_automobiles[automobile]->getManufacturer() == ui->e_manufacturer->text();
        bool typeMatch = m_automobiles[automobile]->getType().contains(ui->e_type->text());
        bool priceMatch = m_automobiles[automobile]->getPrice() <= ui->e_price->text().toInt();
        if (
            (manufacturerEmpty || manufacturerMatch)
            && (typeEmpty || typeMatch)
            && (priceEmpty || priceMatch)
            )
                addAutomobile(m_automobiles[automobile]);

    }
}

void AutoService::addAutomobile(ChildAutomobile * automobile)
{
    ui->l_automobiles->addItem(automobile->getManufacturer() + " " + automobile->getModel());
}

void AutoService::generateAutomobiles()
{
    QStringList manufacturers = {"Audi", "Bentley", "Ford", "Honda", "Hyundai", "JAC", "Jeep", "Rolls-Royce", "Toyota", "Volkswagen"};
    QStringList models = {"A3", "Accord", "Atlas", "Bronco", "Cherokee", "Colorado Crew Cab", "Continental GT", "Santa Cruz", "Shuailing T6", "Wraith"};
    QStringList types = {"Coupé", "Pickup truck"};

    for (int automobile = 0; automobile < 10; ++automobile) {
        ChildAutomobile* newAutomobile = new ChildAutomobile();
        QString manufacturer = manufacturers[QRandomGenerator::global()->bounded(manufacturers.size())];
        newAutomobile->setManufacturer(manufacturer);
        int modelNumber = QRandomGenerator::global()->bounded(models.size());
        QString model = models[modelNumber];
        newAutomobile->setModel(model);
        models.removeAt(modelNumber);
        QString type = types[QRandomGenerator::global()->bounded(types.size())];
        newAutomobile->setType(type);
        int price = QRandomGenerator::global()->bounded(10000, 500000);
        newAutomobile->setPrice(price);
        int seats = QRandomGenerator::global()->bounded(5, 10);
        newAutomobile->setSeats(seats);
        int colorR = QRandomGenerator::global()->bounded(0, 256);
        int colorG = QRandomGenerator::global()->bounded(0, 256);
        int colorB = QRandomGenerator::global()->bounded(0, 256);
        newAutomobile->setColor(QColor(colorR, colorG, colorB));

        m_automobiles.append(newAutomobile);
    }
}

void AutoService::select(QListWidgetItem * item)
{
    for (int automobile = 0; automobile < m_automobiles.size(); ++automobile) {
        if (item->text() == (m_automobiles[automobile]->getManufacturer() + " " + m_automobiles[automobile]->getModel())) {
            ui->e_selected->setText("Manufacturer: " + m_automobiles[automobile]->getManufacturer() + "\n"
                                    + "Model: " + m_automobiles[automobile]->getModel() + "\n"
                                    + "Type: " + m_automobiles[automobile]->getType() + "\n"
                                    + "Seats: " + QString::number(m_automobiles[automobile]->getSeats()) + "\n"
                                    + "Color: " + m_automobiles[automobile]->getColor().name() + "\n"
                                    + "Price: " + QString::number(m_automobiles[automobile]->getPrice()));
            break;
        }
    }
}
