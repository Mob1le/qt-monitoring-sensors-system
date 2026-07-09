#pragma once

#include "detector.h"
#include <QAbstractTableModel>
#include <QHash>
#include <QMutex>

class DetectorDataModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QHash<qint64, Detector> dataHash;
    mutable QMutex mutex;
public:
    explicit DetectorDataModel(QObject *parent = nullptr);
    ~DetectorDataModel() override;

    
    //Перегрузка для кастомной модели
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount (const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateData(const Detector &detector);
};