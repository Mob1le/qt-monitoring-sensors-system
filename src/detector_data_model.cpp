#include "detector_data_model.h"

DetectorDataModel::DetectorDataModel(QObject *parent)
{
}

DetectorDataModel::~DetectorDataModel()
{
}

int DetectorDataModel::rowCount(const QModelIndex &parent) const
{
    QMutexLocker locker(&mutex);
    return dataHash.size();
}

// Поле: ID (qint64), значение (float), время (QDateTime). = 3
int DetectorDataModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant DetectorDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= dataHash.size())
    {
        return QVariant();
    }

    QMutexLocker locker(&mutex);

    const Detector &det = dataHash.values()[index.row()];

    switch (index.column()) {
    case 0:  // ID
        return role == Qt::DisplayRole ? QString::number(det.getId()) : QVariant();
    case 1:  // Value
        return role == Qt::DisplayRole ? QString::number(det.getValue(), 'f', 2) : QVariant();
    case 2:  // Time
        return role == Qt::DisplayRole ? det.getTimestamp().toString("dd.MM.yyyy HH:mm:ss") : QVariant();
    default:
        return QVariant();
    }

}

QVariant DetectorDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QVariant();

    switch (section) {
    case 0: return "ID";
    case 1: return "Значение";
    case 2: return "Время";
    default: return QVariant();
    }

}

void DetectorDataModel::updateData(const Detector &detector)
{
    QMutexLocker locker(&mutex);

    if (!dataHash.contains(detector.getId()))
    {
        return;
    }
    //TODO
}
