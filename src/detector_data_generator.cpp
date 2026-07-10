#include "detector_data_generator.h"

DetectorDataGenerator::DetectorDataGenerator(QObject *parent)
    : QObject(parent) {}

void DetectorDataGenerator::startGeneration(int detectorCount, int updateIntervalMs) {
    m_stopRequested = false;
    
    // Инициализация всех датчиков случайными значениями
    m_currentValues.resize(detectorCount);
    QRandomGenerator *rng = QRandomGenerator::global();
    
    for (int i = 0; i < detectorCount; ++i) {
        m_currentValues[i] = rng->bounded(10000) / 200.0f;
    }
    
    emit detectorsInitialized(detectorCount);
    
    // Бесконечный цикл обновления
    while (!m_stopRequested) {
        for (int i = 0; i < m_currentValues.size(); ++i) {
            float delta = (rng->generateDouble() - 0.5) * 3.0f;
            m_currentValues[i] += delta;
            
            m_currentValues[i] = std::max(-60.0f, std::min(120.0f, m_currentValues[i]));
        }
        
        emit valuesUpdated(m_currentValues);
        
        QThread::msleep(updateIntervalMs);
        QCoreApplication::processEvents();
    }
}

void DetectorDataGenerator::stopGeneration() {
    m_stopRequested = true;
}