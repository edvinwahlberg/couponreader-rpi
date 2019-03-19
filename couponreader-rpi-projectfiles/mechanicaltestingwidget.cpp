#include "mechanicaltestingwidget.h"
#include "ui_mechanicaltestingwidget.h"

MechanicalTestingWidget::MechanicalTestingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MechanicalTestingWidget), handler(Serialcom_handler<sensor_reading>::instance())
{
    ui->setupUi(this);
    handler.add_to_commands( { {"START", 'r'}, {"STOP", 's'}, {"FEED", '2'}, {"ACTIVATE", '1'}});
    connect(ui->start_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::start);
    connect(ui->stop_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::stop);
    connect(ui->feed_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::feed);
   // connect(ui->start_btn, &QPushButton::clicked, this, &MechanicalTestingWidget::setSensTab)
}

MechanicalTestingWidget::~MechanicalTestingWidget()
{
    delete ui;
}

void MechanicalTestingWidget::start()
{
    emit alterTab(TABS::SENS_TAB, false);
    handler.write(std::string("START"));
    ui->start_btn->setEnabled(false);
    ui->feed_btn->setEnabled(false);
}

void MechanicalTestingWidget::stop()
{
    emit alterTab(TABS::SENS_TAB, true);
    handler.write(std::string("STOP"));
    ui->start_btn->setEnabled(true);
    ui->feed_btn->setEnabled(true);
}

void MechanicalTestingWidget::feed()
{
    emit alterTab(TABS::SENS_TAB, false);
    handler.write({"ACTIVATE", "FEED"}, 500);
    emit alterTab(0, true);
}
