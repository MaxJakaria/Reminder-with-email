#include "send_email.h"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

void sendEmail()
{
    playMelody();

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
