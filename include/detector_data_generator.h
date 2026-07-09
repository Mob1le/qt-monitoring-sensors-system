#pragma once
#include <QObject>
#include <QVector>

class DetectorDataGenerator : public QObject {
    Q_OBJECT
public:
    explicit DetectorDataGenerator(QObject *parent = nullptr);

public slots:
    void startGeneration(int detectorCount, int updateIntervalMs);
    void stopGeneration();

signals:
    void detectorsInitialized(int count);
    void valuesUpdated(const QVector<float> &newValues);

private:
    bool m_stopRequested = false;
    QVector<float> m_currentValues;  // Текущие значения всех датчиков
};