#ifndef READINGSMODEL_H
#define READINGSMODEL_H

#include <QAbstractTableModel>
#include <memory>

class SerialHandler;

class ReadingsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ReadingsModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal,
                        int role = Qt::DisplayPropertyRole) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
signals:

public slots:
private:
    SerialHandler &handler;
};

#endif // READINGSMODEL_H
