#pragma once

#include <QObject>
#include <QRandomGenerator>
#include <QDateTime>
#include <QThread>
#include "detector.h"

class DetectorGenerator : public QObject
{
    Q_OBJECT
private:
    bool m_running;

public:
    explicit DetectorGenerator(QObject *parent = nullptr);
    bool isRunning() const;

signals:
    void finished();
    void sendDetector(Detector detector);
    void runningChanged(bool running);

public slots:
    void process();
    void setRunning(bool running);
};