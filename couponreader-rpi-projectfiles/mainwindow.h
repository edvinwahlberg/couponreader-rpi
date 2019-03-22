#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sensor_reading.h"
#include "serialcom_handler.h"

extern template class Serialcom_handler<sensor_reading>;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setTab(int, bool);
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
