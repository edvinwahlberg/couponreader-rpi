#include "mechanicaltestingwidget.h"
#include "ui_mechanicaltestingwidget.h"

MechanicalTestingWidget::MechanicalTestingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MechanicalTestingWidget)
{
    ui->setupUi(this);
}

MechanicalTestingWidget::~MechanicalTestingWidget()
{
    delete ui;
}
