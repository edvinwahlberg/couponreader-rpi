#include "readingsmodel.h"
#include "sensorreadingswidget.h"
#include <thread>
#include <iostream>

extern template class SerialcomHandler<sensor_reading>;
ReadingsModel::ReadingsModel(QObject *parent) :
    QAbstractTableModel(parent), handler(SerialcomHandler<sensor_reading>::instance()), results(new QVector<sensor_reading>) {
    results->reserve(100);
}

int ReadingsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return results->size();
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
    if (index.row() >= results->size() || index.row() < 0)
        return QVariant();
    if (index.row() < results->size() && index.row() >= 0 && role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;
    if (role == Qt::DisplayRole) {
        std::shared_ptr<sensor_reading> tmp = get_at(index.row());
        switch (index.column()) {
            case 0:
                return tmp->s1_;
            case 1:
                return tmp->s2_;
            case 2:
                return tmp->s3_;
            case 3:
                return tmp->s4_;
            default:
                return QVariant();
        }
    }
    return QVariant();
}


QModelIndex ReadingsModel::addSensorReading(sensor_reading&& new_reading)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    results->push_back(std::move(new_reading));
    endInsertRows();
    return index(rowIndex, 0);
}

bool ReadingsModel::isIndexValid(const QModelIndex& index) const
{
    if (index.row() < 0
            || index.row() >= rowCount()
            || !index.isValid())
        return false;
    return true;
}

void ReadingsModel::clear()
{
    beginResetModel();
    results->clear();
    endResetModel();
}
