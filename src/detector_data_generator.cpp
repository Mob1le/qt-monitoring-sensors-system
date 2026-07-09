// DetectorDataGenerator.cpp
#include "detector_data_generator.h"
#include <QRandomGenerator>
#include <QThread>
#include <QCoreApplication>
#include <cmath>
#include <algorithm>

DetectorDataGenerator::DetectorDataGenerator(QObject *parent)
    : QObject(parent) {}

void DetectorDataGenerator::startGeneration(int detectorCount, int updateIntervalMs) {
    m_stopRequested = false;
    
    // Инициализация всех датчиков случайными значениями вокруг 25
    m_currentValues.resize(detectorCount);
    QRandomGenerator *rng = QRandomGenerator::global();
    
    for (int i = 0; i < detectorCount; ++i) {
        m_currentValues[i] = rng->bounded(1000) / 100.0f;
    }
    
    emit detectorsInitialized(detectorCount);
    
    // Бесконечный цикл обновления
    while (!m_stopRequested) {
        // Обновляем КАЖДЫЙ датчик с небольшим случайным изменением
        for (int i = 0; i < m_currentValues.size(); ++i) {
            // Случайное изменение от -0.5 до +0.5
            float delta = (rng->generateDouble() - 0.5) * 1.0f;
            m_currentValues[i] += delta;
            
            // Удерживаем значения в разумных пределах 0-50
            m_currentValues[i] = std::max(-50.0f, std::min(100.0f, m_currentValues[i]));
        }
        
        emit valuesUpdated(m_currentValues);
        
        // Пауза между обновлениями
        QThread::msleep(updateIntervalMs);
        QCoreApplication::processEvents();
    }
}

void DetectorDataGenerator::stopGeneration() {
    m_stopRequested = true;
}