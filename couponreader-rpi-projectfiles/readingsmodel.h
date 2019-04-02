#ifndef READINGSMODEL_H
#define READINGSMODEL_H

#include <QAbstractTableModel>
#include <memory>
#include <QVector>
#include <QDebug>
//#include <mutex>

#include "sensor_reading.h"
#include "serialcomhandler.h"

class ReadingsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    using result_size_type = QVector<sensor_reading>::size_type;
    explicit ReadingsModel(QObject *parent = nullptr);
    ~ReadingsModel() { delete results; }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal,
                        int role = Qt::DisplayPropertyRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QModelIndex addSensorReading(sensor_reading&&);
    QVector<sensor_reading>* get_results() { return results; }
    QModelIndex push_back_results(sensor_reading e)
    {
        int rowIndex = this->rowCount();
        beginInsertRows(QModelIndex(), rowIndex, rowIndex);
        results->push_back(e);
        endInsertRows();
        return index(rowIndex, 0);
    }
    std::shared_ptr<sensor_reading> get_at(result_size_type i) const
    {
        return std::make_shared<sensor_reading>(results->at(i));
    }

    void clear();

private:
    bool isIndexValid(const QModelIndex&) const;
private:
   SerialcomHandler<sensor_reading> &handler;
   QVector<sensor_reading> *results;
};

#endif // READINGSMODEL_H
