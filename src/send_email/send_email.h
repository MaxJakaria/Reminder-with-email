#ifndef SEND_EMAIL_H
#define SEND_EMAIL_H

#include <ESP_Mail_Client.h>
#include "melody.h"

extern const char *SMTP_HOST;
extern const int SMTP_PORT;
extern const char *AUTHOR_EMAIL;
extern const char *AUTHOR_PASSWORD;
extern const char *RECIPIENT_EMAIL;

extern SMTPSession smtp;
extern SMTP_Message message;

void sendEmail();

#endif
