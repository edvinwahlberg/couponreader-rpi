#include "readingsmodel.h"

ReadingsModel::ReadingsModel(QObject *parent) : QAbstractTableModel(parent), handler(Serialcom_handler<sensor_reading>::instance()) { }

int ReadingsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}
int ReadingsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}
QVariant ReadingsModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    if (role != Qt::DisplayRole)
        QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
               return tr("Sensor 1");
            case 1:
                return tr("Sensor 2");
            case 2:
                return tr("Sensor 3");
            case 3:
                return tr("Sensor 4");
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
    }
    return QVariant();
}
