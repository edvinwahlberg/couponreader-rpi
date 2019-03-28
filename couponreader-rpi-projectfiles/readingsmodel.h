#ifndef READINGSMODEL_H
#define READINGSMODEL_H

#include <QAbstractTableModel>
#include <memory>
#include <QVector>
#include <QDebug>

#include <mutex>
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
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVector<sensor_reading>* get_results() { return results; }
    QModelIndex push_back_results(sensor_reading e)
    {
        std::lock_guard<std::mutex> lock(results_mutex);
        int rowIndex = this->rowCount();
        beginInsertRows(QModelIndex(), rowIndex, rowIndex);
        results->push_back(e);
        endInsertRows();
        return index(rowIndex, 0);
    }
    std::shared_ptr<sensor_reading> get_at(result_size_type i) const
    {
        std::lock_guard<std::mutex> lock(results_mutex);

        return std::make_shared<sensor_reading>(results->at(i));
    }
signals:

public slots:
    void read_from_spsc();
private:
    bool isIndexValid(const QModelIndex&) const;
private:
   SerialcomHandler<sensor_reading> &handler;
   QVector<sensor_reading> *results;
   mutable std::mutex results_mutex;
};

#endif // READINGSMODEL_H
