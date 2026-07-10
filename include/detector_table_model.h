#pragma once
#include <QAbstractTableModel>
#include <QMutex>
#include <QVector>
#include <QDateTime>
#include <algorithm>
#include <limits>
#include <numeric>

struct DetectorData {
    int id;
    QDateTime timestamp;
    float value;
};
Q_DECLARE_METATYPE(DetectorData)

class DetectorTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Column { ColID = 0, ColTimestamp, ColValue, ColumnCount };

    explicit DetectorTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Статистика (потокобезопасная)
    int totalCount() const;
    float averageValue() const;
    float minValue() const;
    float maxValue() const;

public slots:
    void initDetectors(int count);                          // Инициализация датчиков
    void updateValues(const QVector<float> &newValues);     // Массовое обновление значений
    void clearData();

signals:
    void dataChanged(); // Сигнал для обновления статистики

private:
    mutable QMutex m_mutex;
    QVector<DetectorData> m_data;
    
    // Кэш статистики для быстрого обновления
    mutable bool m_statsDirty = true;
    mutable int m_cachedCount = 0;
    mutable float m_cachedAvg = 0.0f;
    mutable float m_cachedMin = 0.0f;
    mutable float m_cachedMax = 0.0f;
    
    void invalidateStats();
    void recalcStats() const;
};