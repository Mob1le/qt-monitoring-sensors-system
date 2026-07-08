#include "detector.h"

Detector::Detector() 
    : id(0), timestamp(QDateTime::currentDateTime()), value(0.0f) 
{}

Detector::Detector(qint64 id, const QDateTime &timestamp, float value)
    : id(id), timestamp(timestamp), value(value) 
{}

qint64 Detector::getId() const
{
    return id;
}

void Detector::setId(int new_id)
{
    id = new_id;
}

QDateTime Detector::getTimestamp() const
{
    return timestamp;
}

void Detector::setTimestamp(const QDateTime &new_timestamp)
{
    timestamp = new_timestamp;
}

float Detector::getValue() const
{
    return value;
}

void Detector::setValue(float new_value)
{
    value = new_value;
}
