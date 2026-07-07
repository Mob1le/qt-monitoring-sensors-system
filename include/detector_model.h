#pragma once

#include <QAbstractTableModel>
#include <QVector>

class DetectorModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DetectorModel(QObject *parent = nullptr);
    ~DetectorModel() override;

    
    //Перегрузка для кастомной модели
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount (const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};