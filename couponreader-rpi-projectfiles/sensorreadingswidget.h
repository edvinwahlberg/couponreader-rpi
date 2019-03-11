#ifndef SENSORREADINGSWIDGET_H
#define SENSORREADINGSWIDGET_H

#include <QWidget>

namespace Ui {
class SensorReadingsWidget;
}

class SensorReadingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SensorReadingsWidget(QWidget *parent = nullptr);
    ~SensorReadingsWidget();

private:
    Ui::SensorReadingsWidget *ui;
};

#endif // SENSORREADINGSWIDGET_H
