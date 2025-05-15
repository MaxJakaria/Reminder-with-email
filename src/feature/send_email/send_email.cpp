#include "send_email.h"
#include <ESP_Mail_Client.h>

extern const char *AUTHOR_EMAIL;
extern const char *AUTHOR_PASSWORD;
extern const char *RECIPIENT_EMAIL;
extern SMTPSession smtp;
extern SMTP_Message message;

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

void sendEmail(const String &medicineName)
{
    ESP_Mail_Session session;
    session.server.host_name = SMTP_HOST;
    session.server.port = SMTP_PORT;
    session.login.email = AUTHOR_EMAIL;
    session.login.password = AUTHOR_PASSWORD;

    message.sender.name = "Your Guardian";
    message.sender.email = AUTHOR_EMAIL;
    message.subject = "Medicine Reminder";
    message.addRecipient("User", RECIPIENT_EMAIL);
    message.text.content = "It's time to take your medicine: " + medicineName;
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