#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void disable_mech_tab() { }
    void disable_sens_tab() { }
public slots:
    void setTab(int, bool);
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
