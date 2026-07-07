#pragma once

#include <QDateTime>
#include <QUuid>

class Detector
{
private:
    QUuid id;
    QDateTime timestamp;
    float value;
public:
    Detector(/* args */);
};
