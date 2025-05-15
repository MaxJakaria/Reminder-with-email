#ifndef REMINDER_MANAGER_H
#define REMINDER_MANAGER_H

#include <Arduino.h>
#include "reminder.h"

#define MAX_REMINDERS 6

class ReminderManager
{
public:
    ReminderManager();
    void addRemindersFromInput(const String &input);
    void checkAndTrigger(const tm &timeinfo);

private:
    Reminder reminders[MAX_REMINDERS];
    int reminderCount;
};

#endif