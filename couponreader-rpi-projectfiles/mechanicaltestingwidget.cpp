#include "mechanicaltestingwidget.h"
#include "ui_mechanicaltestingwidget.h"

#include <QDebug>
extern template class SerialcomHandler<sensor_reading>;
MechanicalTestingWidget::MechanicalTestingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MechanicalTestingWidget), handler(SerialcomHandler<sensor_reading>::instance())
{
    ui->setupUi(this);
    if (!handler.valid_port())
        handler.setPortName("/dev/ttyUSB0");
    handler.add_commands( { {"START", 'r'}, {"STOP", 's'}, {"FEED", '2'}, {"ACTIVATE", '1'}});
    connect(ui->start_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::start);
    connect(ui->stop_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::stop);
    connect(ui->feed_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::feed);
    connect(ui->disc_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::disconnect);
    qDebug() << "Hello?";
   // connect(ui->start_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::setSensTab)
}

MechanicalTestingWidget::~MechanicalTestingWidget()
{
    delete ui;
}

void MechanicalTestingWidget::start()
{
    emit toggle_tab(TABS::SENS_TAB, false);
    handler.write_commands({std::string("START")}, 100);
    ui->start_btn->setEnabled(false);
    ui->feed_btn->setEnabled(false);
}

void MechanicalTestingWidget::stop()
{
    emit toggle_tab(TABS::SENS_TAB, true);
    handler.write_commands({std::string("STOP")}, 100);
    ui->start_btn->setEnabled(true);
    ui->feed_btn->setEnabled(true);
}

void MechanicalTestingWidget::feed()
{
    emit toggle_tab(TABS::SENS_TAB, false);
    handler.write_commands({"ACTIVATE", "FEED"}, 500, false);
    emit toggle_tab(0, true);
}

void MechanicalTestingWidget::disconnect()
{
    handler.close();
}
