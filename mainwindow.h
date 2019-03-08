#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SerialHandler;

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
    void test();
    void stop();

private:
    Ui::MainWindow *ui;
    SerialHandler& handler;
};

#endif // MAINWINDOW_H
