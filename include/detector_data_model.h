#pragma once

#include <QAbstractTableModel>
#include <QVector>

class DetectorDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DetectorDataModel(QObject *parent = nullptr);
    ~DetectorDataModel() override;

    
    //Перегрузка для кастомной модели
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount (const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};