#pragma once

#include <QDateTime>


class Detector
{
private:
    qint64 id;
    QDateTime timestamp;
    float value;
public:
    Detector();
    Detector(qint64 id, const QDateTime &timestamp, float value);

    qint64 getId() const;
    void setId(int new_id);

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &newTimestamp);

    float getValue() const;
    void setValue(float newValue);
};

