#include "reminder_manager.h"
#include "constants.h"
#include "melody.h"
#include "send_email.h"

ReminderManager::ReminderManager() : reminderCount(0) {}

void ReminderManager::addRemindersFromInput(const String &input)
{
    int commaIdx = input.indexOf(',');
    if (commaIdx > 0 && commaIdx < input.length() - 1)
    {
        String medName = input.substring(0, commaIdx);
        int timesPerDay = input.substring(commaIdx + 1).toInt();

        if (timesPerDay > 0 && timesPerDay <= REMINDER_SIZE)
        {
            int startHour = 8;
            int interval = (24 - startHour) / timesPerDay;
            if (reminderCount + timesPerDay >= REMINDER_SIZE)
            {
                Serial.println("Max reminders reached.");
            }
            else
            {
                for (int i = 0; i < timesPerDay && reminderCount < MAX_REMINDER_PER_DAY; i++)
                {
                    int hour = startHour + i * interval;
                    if (hour >= 24)
                        hour -= 24;
                    reminders[reminderCount++] = Reminder(medName, hour, 0);
                    Serial.printf("Added: %s at %02d:00\n", medName.c_str(), hour);
                }
            }
        }
        else
        {
            Serial.println("Invalid number of times per day. Enter a value between 1 and 6.");
        }
    }
    else
    {
        Serial.println("Invalid format. Use Name,Times (e.g., Napa,3)");
    }
}

void ReminderManager::checkAndTrigger(const tm &timeinfo)
{
    for (int i = 0; i < reminderCount; i++)
    {
        if (reminders[i].shouldTrigger(timeinfo))
        {
            Serial.println("Triggering reminder: " + reminders[i].getName());
            playMelody();
            sendEmail(reminders[i].getName());
            reminders[i].markTriggered();
        }
        // Reset flag after minute changes
        if (reminders[i].shouldReset(timeinfo))
        {
            reminders[i].reset();
        }
    }
}