#include "readingsmodel.h"
#include "sensorreadingswidget.h"
#include <thread>

ReadingsModel::ReadingsModel(QObject *parent) :
    QAbstractTableModel(parent), handler(Serialcom_handler<sensor_reading>::instance()) {
   // connect(parent, &SensorReadingsWidget::readings_started, this, &ReadingsModel::read_from_spsc);
}

int ReadingsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return results.size() + 1;
}
int ReadingsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}
QVariant ReadingsModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
               return tr("SENSOR 1");
            case 1:
                return tr("SENSOR 2");
            case 2:
                return tr("SENSOR 3");
            case 3:
                return tr("SENSOR 4");
            default:
                return QVariant();
        }
    }
    return QVariant();
}
QVariant ReadingsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= 1 || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole) {
        //const sensor_reading;
    }
    return QVariant();
}

void ReadingsModel::read_from_spsc()
{
  //  handler.start_read_spsc(results);
}
