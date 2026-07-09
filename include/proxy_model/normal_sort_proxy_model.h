#pragma once
#include <QSortFilterProxyModel>
#include <QDateTime>

class NumericSortProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    explicit NumericSortProxyModel(QObject *parent = nullptr) 
        : QSortFilterProxyModel(parent) {}

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override {
        QVariant leftData = sourceModel()->data(left, Qt::UserRole);
        QVariant rightData = sourceModel()->data(right, Qt::UserRole);
        
        // Сортируем по типу данных
        switch (leftData.type()) {
        case QVariant::Int:
            return leftData.toInt() < rightData.toInt();
            
        case QVariant::Double:
        case QMetaType::Float:
            return leftData.toFloat() < rightData.toFloat();
            
        case QVariant::DateTime:
            return leftData.toDateTime() < rightData.toDateTime();
            
        default:
            // Для строк используем стандартную сортировку
            return QSortFilterProxyModel::lessThan(left, right);
        }
    }
};