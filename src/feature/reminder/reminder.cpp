#include "reminder.h"

Reminder::Reminder()
    : name(""), hour(0), minute(0), triggeredToday(false) {}

Reminder::Reminder(const String &name, int hour, int minute)
    : name(name), hour(hour), minute(minute), triggeredToday(false) {}

bool Reminder::shouldTrigger(const tm &timeinfo) const
{
    return timeinfo.tm_hour == hour && timeinfo.tm_min == minute && timeinfo.tm_sec == 0 && !triggeredToday;
}

bool Reminder::shouldReset(const tm &timeinfo) const
{
    return timeinfo.tm_min != minute && triggeredToday;
}

void Reminder::markTriggered()
{
    triggeredToday = true;
}

void Reminder::reset()
{
    triggeredToday = false;
}

String Reminder::getName() const
{
    return name;
}

int Reminder::getHour() const
{
    return hour;
}

int Reminder::getMinute() const
{
    return minute;
}