#include "detector_table_model.h"
#include <algorithm>
#include <limits>
#include <numeric>

DetectorTableModel::DetectorTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

int DetectorTableModel::rowCount(const QModelIndex &parent) const {
    QMutexLocker locker(&m_mutex);
    return parent.isValid() ? 0 : m_data.size();
}

int DetectorTableModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : ColumnCount;
}

QVariant DetectorTableModel::data(const QModelIndex &index, int role) const {
    QMutexLocker locker(&m_mutex);
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const DetectorData &row = m_data[index.row()];
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case ColID:        return row.id;
        case ColTimestamp: return row.timestamp.toString("yyyy-MM-dd hh:mm:ss.zzz");
        case ColValue:     return QString::number(row.value, 'f', 3);
        }
    }
    else if (role == Qt::UserRole) {
        switch (index.column()) {
        case ColID:        return row.id;           // int
        case ColTimestamp: return row.timestamp;     // QDateTime
        case ColValue:     return row.value;         // float
        }
    }
    return QVariant();
}

QVariant DetectorTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();
    switch (section) {
    case ColID:        return "ID";
    case ColTimestamp: return "Timestamp";
    case ColValue:     return "Value";
    default:           return QVariant();
    }
}

void DetectorTableModel::initDetectors(int count) {
    beginResetModel();
    {
        QMutexLocker locker(&m_mutex);
        m_data.clear();
        m_data.reserve(count);
        
        QDateTime now = QDateTime::currentDateTime();
        for (int i = 0; i < count; ++i) {
            DetectorData data;
            data.id = i + 1;
            data.timestamp = now;
            data.value = 0.0f;  // Начальные значения
            m_data.append(data);
        }
        invalidateStats();
    }
    endResetModel();
    emit dataChanged();
}

void DetectorTableModel::updateValues(const QVector<float> &newValues) {
    {
        QMutexLocker locker(&m_mutex);
        if (newValues.size() != m_data.size())
            return;
        
        QDateTime now = QDateTime::currentDateTime();
        for (int i = 0; i < m_data.size(); ++i) {
            m_data[i].timestamp = now;
            m_data[i].value = newValues[i];
        }
        invalidateStats();
    }

    beginResetModel();
    endResetModel();
    
    emit dataChanged();  // Для статистики
}

void DetectorTableModel::clearData() {
    beginResetModel();
    {
        QMutexLocker locker(&m_mutex);
        m_data.clear();
        invalidateStats();
    }
    endResetModel();
    emit dataChanged();
}

void DetectorTableModel::invalidateStats() {
    m_statsDirty = true;
}

void DetectorTableModel::recalcStats() const {
    if (!m_statsDirty) return;
    
    m_cachedCount = m_data.size();
    if (m_cachedCount == 0) {
        m_cachedAvg = 0.0f;
        m_cachedMin = 0.0f;
        m_cachedMax = 0.0f;
    } else {
        float sum = 0.0f;
        m_cachedMin = std::numeric_limits<float>::max();
        m_cachedMax = std::numeric_limits<float>::lowest();
        
        for (const auto &row : m_data) {
            sum += row.value;
            m_cachedMin = std::min(m_cachedMin, row.value);
            m_cachedMax = std::max(m_cachedMax, row.value);
        }
        m_cachedAvg = sum / m_cachedCount;
    }
    m_statsDirty = false;
}

int DetectorTableModel::totalCount() const {
    QMutexLocker locker(&m_mutex);
    recalcStats();
    return m_cachedCount;
}

float DetectorTableModel::averageValue() const {
    QMutexLocker locker(&m_mutex);
    recalcStats();
    return m_cachedAvg;
}

float DetectorTableModel::minValue() const {
    QMutexLocker locker(&m_mutex);
    recalcStats();
    return m_cachedMin;
}

float DetectorTableModel::maxValue() const {
    QMutexLocker locker(&m_mutex);
    recalcStats();
    return m_cachedMax;
}