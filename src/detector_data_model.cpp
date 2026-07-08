#include "detector_model.h"

DetectorDataModel::DetectorDataModel(QObject *parent)
{
}

DetectorDataModel::~DetectorDataModel()
{
}

int DetectorDataModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int DetectorDataModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant DetectorDataModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant DetectorDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}
