#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include "time.h"
#include "melody.h"

// WiFi credentials
const char *ssid = "Galaxy M31850B";
const char *password = "12341234";

// SMTP credentials
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "mdjakariahossen987654321@gmail.com"
#define AUTHOR_PASSWORD "biomvhbwtmhjkmsm"
#define RECIPIENT_EMAIL "maxjakaria825@gmail.com"

// NTP settings (adjust time zone as needed)
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 6 * 3600; // GMT+6
const int daylightOffset_sec = 0;

// Buzzer pin
#define BUZZER_PIN 25

SMTPSession smtp;
SMTP_Message message;

int reminderHour = -1;
int reminderMinute = -1;
bool emailSentToday = false;

void sendEmail();

void setup()
{
  Serial.begin(115200);

  // Setup buzzer pin (optional if melody uses PWM)
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected");

  // Initialize NTP time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("\nEnter reminder time in HH:MM format (24-hour):");
}

void loop()
{
  // Handle serial input
  if (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    delay(1000);
    input.trim();

    if (input.length() == 5 && input.charAt(2) == ':')
    {
      reminderHour = input.substring(0, 2).toInt();
      reminderMinute = input.substring(3, 5).toInt();

      if (reminderHour >= 0 && reminderHour <= 23 && reminderMinute >= 0 && reminderMinute <= 59)
      {
        Serial.printf("Reminder set for %02d:%02d\n", reminderHour, reminderMinute);
        emailSentToday = false;
      }
      else
      {
        Serial.println("Invalid time. Please enter in HH:MM format.");
      }
    }
    else
    {
      Serial.println("Invalid format. Use HH:MM (e.g., 08:30)");
    }
  }

  if (reminderHour == -1)
    return;

  // Get current time
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to get time");
    delay(1000);
    return;
  }

  // Check if time matches
  if (timeinfo.tm_hour == reminderHour && timeinfo.tm_min == reminderMinute && timeinfo.tm_sec == 0 && !emailSentToday)
  {
    sendEmail();
    emailSentToday = true;
  }

  // Reset flag after minute changes
  if (timeinfo.tm_min != reminderMinute)
  {
    emailSentToday = false;
  }

  delay(1000); // check every second
}

void sendEmail()
{
  // Play melody as alarm
  playMelody();

  // --- Send email ---
  ESP_Mail_Session session;
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  message.sender.name = "ESP32 Tablet Reminder";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Medicine Reminder";
  message.addRecipient("User", RECIPIENT_EMAIL);
  message.text.content = "It's time to take your medicine!";
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!smtp.connect(&session))
  {
    Serial.println("SMTP Connection Failed");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message))
  {
    Serial.println("Send Failed: " + smtp.errorReason());
  }
  else
  {
    Serial.println("✅ Email sent successfully.");
  }

  smtp.closeSession();
}
