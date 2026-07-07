#pragma once

#include <QAbstractTableModel>
#include <QVector>

class DetectorModel : public QAbstractTableModel
{
public:
    DetectorModel(QObject *parent = nullptr);

    //Перегрузка для кастомной модели
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount (const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};