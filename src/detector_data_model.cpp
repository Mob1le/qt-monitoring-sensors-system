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
    return m_data.size();
}

// Поле: ID (qint64), значение (float), время (QDateTime). = 3
int DetectorDataModel::columnCount(const QModelIndex &parent) const
{
    QMutexLocker locker(&mutex);
    return 3;
}

QVariant DetectorDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QMutexLocker locker(&mutex);
    if (role == Qt::DisplayRole)
    {
        const Detector &detector = m_data[index.row()];
        switch (index.column())
        {
        case 0:
            return detector.getId();
        case 1:
            return detector.getValue();
        case 2:
            return detector.getTimestamp().toString("yyyy-MM-dd HH:mm:ss");
        }
    }
    else if (role == Qt::EditRole)
    {
        const Detector &detector = m_data[index.row()];
        switch (index.column())
        {
        case 0:
            return detector.getId();
        case 1:
            return detector.getValue();
        case 2:
            return detector.getTimestamp();
        }
    }
    return QVariant();
}

QVariant DetectorDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
    case 0:
        return "ID";
    case 1:
        return "Значение";
    case 2:
        return "Время";
    default:
        return QVariant();
    }
}

void DetectorDataModel::addData(Detector detector)
{
    const qint64 id = detector.getId();
    if (m_data.contains(id))
    {
        const int row = id_row[id];
        if (row < 0 || row >= rowCount())
            return;

        int lastColumn = columnCount() - 1;
        if (lastColumn < 0)
            return;

        QModelIndex topLeft = index(row, 0);
        QModelIndex bottomRight = index(row, lastColumn);
        if (topLeft.isValid() && bottomRight.isValid())
        {
            m_data[id] = detector;
            emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole, Qt::EditRole});
        }
    }
    else
    {
        const int row = m_data.size();
        beginInsertRows(QModelIndex(), row, row);
        id_row.insert(id, row);
        m_data.insert(id, detector);
        endInsertRows();
    }
}