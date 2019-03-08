#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialhandler.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), handler(SerialHandler::instance())
{
    ui->setupUi(this);
    connect(ui->test_btn, &QPushButton::clicked, this, &MainWindow::test);
    connect(ui->stor_btn, &QPushButton::clicked, this, &MainWindow::stop);
}

MainWindow::~MainWindow()
{
   // handler.close_port();
    delete ui;
}

void MainWindow::test()
{
    handler.start_readings();
}

void MainWindow::stop()
{
    static bool prev = true;
    if (prev) {
        ui->char_lbl->setText("hejhej");
        prev = false;
    }
    else
    {
        ui->char_lbl->setText("hemskt mkt hej");
        prev = true;
    }
    handler.stop_readings();
}
/*
void MainWindow::close_port()
{
    if (handler.close_port()) {
        ui->close_btn->setEnabled(false);
        ui->open_btn->setEnabled(true);
    }
}

void MainWindow::open_port()
{
    if (handler.open_port()) {
        ui->open_btn->setEnabled(false);
        ui->close_btn->setEnabled(true);
    }
}
*/
