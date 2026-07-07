#include "detector_model.h"

DetectorModel::DetectorModel(QObject *parent)
{
}

DetectorModel::~DetectorModel()
{
}

int DetectorModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int DetectorModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant DetectorModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant DetectorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}
