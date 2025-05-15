#pragma once
#include <Arduino.h>

class Reminder
{
public:
    Reminder();
    Reminder(const String &name, int hour, int minute);

    bool shouldTrigger(const tm &timeinfo) const;
    bool shouldReset(const tm &timeinfo) const;
    void markTriggered();
    void reset();

    int getHour() const;
    int getMinute() const;
    String getName() const;

private:
    String name;
    int hour;
    int minute;
    bool triggeredToday;
};