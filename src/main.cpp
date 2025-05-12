#include <WiFi.h>
#include <ESP_Mail_Client.h>

// WiFi credentials
const char *ssid = "Galaxy M31850B";
const char *password = "12341234";

// SMTP server
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

// Sender credentials
#define AUTHOR_EMAIL "mdjakariahossen987654321@gmail.com"
#define AUTHOR_PASSWORD "biom vhbw tmhj kmsm"

// Recipient
#define RECIPIENT_EMAIL "maxjakaria825@gmail.com"

// Define SMTP Session
SMTPSession smtp;

// Define message
SMTP_Message message;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  // Set SMTP Server and login
  smtp.debug(1); // Optional: Show debug info
  ESP_Mail_Session session;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  // Set email message headers and content
  message.sender.name = "ESP32 Tablet Reminder";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Tablet Reminder";
  message.addRecipient("User", RECIPIENT_EMAIL);
  message.text.content = "Time to take your medicine!";
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  // Connect and send
  if (!smtp.connect(&session))
  {
    Serial.println("Connection to SMTP failed");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message))
  {
    Serial.println("Error sending Email: " + smtp.errorReason());
  }
  else
  {
    Serial.println("Email sent successfully.");
  }

  smtp.closeSession(); // Optional
}

void loop()
{
  // Empty or future schedule
}
