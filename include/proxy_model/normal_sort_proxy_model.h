#pragma once
#include <QSortFilterProxyModel>
#include <QDateTime>
#include "detector_table_model.h"

class NumericSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit NumericSortProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent) , m_minThreshold(20.0f), m_thresholdEnabled(true) {}

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
    {
        QVariant leftData = sourceModel()->data(left, Qt::UserRole);
        QVariant rightData = sourceModel()->data(right, Qt::UserRole);

        // Сортируем по типу данных
        switch (leftData.type())
        {
        case QVariant::Int:
            return leftData.toInt() < rightData.toInt();

        case QMetaType::Float:
            return leftData.toFloat() < rightData.toFloat();

        case QVariant::DateTime:
            return leftData.toDateTime() < rightData.toDateTime();

        default:
            return QSortFilterProxyModel::lessThan(left, right);
        }
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override
    {
        // Если фильтрация по порогу не включена, используем стандартную фильтрацию
        if (!m_thresholdEnabled)
        {
            return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
        }

        QModelIndex index = sourceModel()->index(sourceRow, DetectorTableModel::ColValue, sourceParent);
        QString dataStr = sourceModel()->data(index).toString();

        // Пытаемся преобразовать в число с плавающей точкой
        bool ok = false;
        float value = dataStr.toFloat(&ok);

        if (!ok)
        {
            return false;
        }

        return value > m_minThreshold;
    }

private:
    bool m_thresholdEnabled;
    float m_minThreshold;
};