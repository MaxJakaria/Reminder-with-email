#ifndef REMINDER_MANAGER_H
#define REMINDER_MANAGER_H

#include <Arduino.h>
#include "reminder.h"
#include "constants.h"

class ReminderManager
{
public:
    ReminderManager();
    void addRemindersFromInput(const String &input);
    void checkAndTrigger(const tm &timeinfo);

private:
    Reminder reminders[REMINDER_SIZE];
    int reminderCount;
};

#endif