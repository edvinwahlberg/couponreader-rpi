#ifndef MECHANICALTESTINGWIDGET_H
#define MECHANICALTESTINGWIDGET_H

#include <QWidget>

#include "serialcom_handler.h"
#include "sensor_reading.h"

extern template class Serialcom_handler<sensor_reading>;

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
private:
    Ui::MechanicalTestingWidget *ui;
    Serialcom_handler<sensor_reading>& handler;
};

#endif // MECHANICALTESTINGWIDGET_H
