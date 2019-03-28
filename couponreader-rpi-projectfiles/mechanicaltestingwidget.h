#ifndef MECHANICALTESTINGWIDGET_H
#define MECHANICALTESTINGWIDGET_H

#include <QWidget>

#include "sensor_reading.h"

#include "serialcomhandler.h"

namespace Ui {
class MechanicalTestingWidget;
}

class MechanicalTestingWidget : public QWidget
{
    Q_OBJECT
    enum TABS {
        SENS_TAB = 0
    };
public:
    explicit MechanicalTestingWidget(QWidget *parent = nullptr);
    ~MechanicalTestingWidget();

signals:
    void toggle_tab(int tab, bool enabled);
private slots:
    void start();
    void stop();
    void feed();
    void disconnect();
private:
    Ui::MechanicalTestingWidget *ui;
    SerialcomHandler<sensor_reading>& handler;
};

#endif // MECHANICALTESTINGWIDGET_H
