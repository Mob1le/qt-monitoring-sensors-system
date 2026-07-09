#include "detector_generator.h"

DetectorGenerator::DetectorGenerator(QObject *parent) : QObject(parent), m_running(false)
{
}

bool DetectorGenerator::isRunning() const
{
    return m_running;
}

void DetectorGenerator::process()
{
    // Переменная m_running отвечает за работу объекта в потоке.
    // При значении false работа завершается
    while (m_running)
    {
        qint64 randomId = QRandomGenerator::global()->generate64() % 10000 + 1;

        // Generate random value: e.g., float between 0.0 and 100.0
        double d = QRandomGenerator::global()->generateDouble();
        float randomValue = static_cast<float>(d * 100.0);

        // Keep current timestamp
        QDateTime timestamp = QDateTime::currentDateTime();

        Detector fresh_data{randomId, timestamp, randomValue};
        emit sendDetector(fresh_data);
    }
    emit finished();
}

void DetectorGenerator::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}