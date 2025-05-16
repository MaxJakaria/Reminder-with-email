#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include "time.h"
#include "melody.h"
#include "reminder_manager.h"
#include "send_email.h"
#include <WebServer.h>

// WiFi credentials
const char *ssid = "Galaxy M31850B";
const char *password = "12341234";

// SMTP credentials
const char *AUTHOR_EMAIL = "mdjakariahossen987654321@gmail.com";
const char *AUTHOR_PASSWORD = "biomvhbwtmhjkmsm";
const char *RECIPIENT_EMAIL = "maxjakaria825@gmail.com";

// NTP settings
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 6 * 3600;
const int daylightOffset_sec = 0;

// Buzzer pin
#define BUZZER_PIN 25

SMTPSession smtp;
SMTP_Message message;

ReminderManager reminderManager;

WebServer server(80);
void handleAddReminder()
{
  if (server.hasArg("plain"))
  {
    String input = server.arg("plain");
    input.trim();
    reminderManager.addRemindersFromInput(input);
    server.send(200, "text/plain", "Reminder added: " + input);
  }
  else
  {
    server.send(400, "text/plain", "No reminder data received");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  server.on("/add_reminder", HTTP_POST, handleAddReminder);
  server.begin();

  Serial.println("\nEnter medicine and number of times per day in format: Name,Times (e.g., Napa,3):");
}

void loop()
{
  // to handle HTTP requests
  server.handleClient();

  // Handle serial input for medicine reminders
  if (Serial.available())
  {
    delay(5000); // Give user time to type
    String input = Serial.readStringUntil('\n');
    input.trim();
    reminderManager.addRemindersFromInput(input);
  }

  // Get current time
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to get time");
    delay(1000);
    return;
  }

  // Check and trigger reminders
  reminderManager.checkAndTrigger(timeinfo);

  delay(1000); // check every second
}