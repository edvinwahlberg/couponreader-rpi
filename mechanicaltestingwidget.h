#ifndef MECHANICALTESTINGWIDGET_H
#define MECHANICALTESTINGWIDGET_H

#include <QWidget>

namespace Ui {
class MechanicalTestingWidget;
}

class MechanicalTestingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MechanicalTestingWidget(QWidget *parent = nullptr);
    ~MechanicalTestingWidget();

private:
    Ui::MechanicalTestingWidget *ui;
};

#endif // MECHANICALTESTINGWIDGET_H
