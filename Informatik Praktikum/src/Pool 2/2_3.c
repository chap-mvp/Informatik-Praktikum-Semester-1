/*
Ihr Programm soll eine einfache Benutzerverwaltung durchführen:

 - Bis zu 120 Benutzernamen und eindeutig zugeordnete Passworte sollen zwecks Registrierung nacheinander über die Konsole eingelesen und gespeichert werden.

Benutzernamen müssen:
 - 6 bis 9 Zeichen lang sein,
 - einen Großbuchstaben als erstes Zeichen enthalten,
 - ab dem zweiten Zeichen nur aus Kleinbuchstaben oder dezimalen Ziffern bestehen.

Passworte müssen:
 - 8 bis 14 Zeichen lang sein,
 - mindesten einen Großbuchstaben, einen Kleinbuchstaben und eine dezimale Ziffer enthalten,
 - zum Anlegen zweimal identisch eingegeben werden.

Bei der Benutzeranmeldung müssen:
 - der Benutzername und das Passwort eingegeben werden,
 - eine Mitteilung über den erfolgreichen Anmeldeversuch ausgegeben werden, falls die Benutzeranmeldung korrekt war,
 - eine Mitteilung über den erfolglosen Anmeldeversuch ausgegeben werden, falls die Benutzeranmeldung fehlerhaft war.

 - Es sind maximal drei erfolglose Anmeldeversuche erlaubt. Bei Überschreiten dieser Maximalzahl soll der Nutzer für einen erneuten Anmeldeversuch für die Dauer von zwei Minuten gesperrt werden.
 - Zur Passwortänderung muss zunächst das gespeicherte Passwort korrekt und dann das neue Passwort mit korrekter Wiederholung eingegeben werden.
 - Bei jeder Passworteingabe soll jedes zum Passwort gehörende Zeichen während der Eingabe im Klartext auf dem Bildschirm dargestellt und beim Abschluss der Eingabe durch einen Stern (*) überschrieben werden.
 - Bei fehlerhaften Eingaben sollen aussagekräftige Fehlermeldungen auf dem Bildschirm ausgegeben werden. Der fehlerhafte Vorgang soll zurückgesetzt werden.

Vorgaben zum Lösungsweg
 - Lesen Sie ein Passwort als zusammenhängende Eingabe ein, indem Sie die Passworteingabe durch Drücken der Taste "Return" abschließen.
 - Verwenden Sie die aktuelle Uhrzeit (Bibliothek time.h), um die Sperrfrist nach fehlerhafter Passworteingabe zu überwachen (Sommer-/Winterzeit ist zu vernachlässigen).
*/

#include <stdio.h>

#define USER_STORAGE 3

typedef struct userData
{
    // int userID;
    char username[9];
    char password[14];
} info;

struct userData users[USER_STORAGE];

struct userData password_fill(struct userData *username)
{
    info user;
    for (int i = 0; i < 14; i++)
    {
        user.username[i] = 0;
        user.password[i] = 0;
    }
    printf("Enter a username: ");
    for (int i = 0; i < 9; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;

        user.username[i] = c;
    }
    for (int i = 0; i < 9; i++)
        printf("%c", user.username[i]);
}

struct userData username_fill()
{
    info user;
    for (int i = 0; i < 14; i++)
    {
        user.username[i] = 0;
        user.password[i] = 0;
    }
    printf("Enter a username: ");
    for (int i = 0; i < 9; i++)
    {
        char c = getchar();
        if (c == '\n')
            break;

        user.username[i] = c;
    }
    for (int i = 0; i < 9; i++)
        printf("%c", user.username[i]);
}

int fill_user(int usercount)
{
    info user;
    if (usercount < USER_STORAGE)
    {
        username_fill();
        return usercount++;
    }
    else
        printf("The user storage has been reached!\n");
}

int main()
{
    int usercount = 0;
    usercount = fill_user(usercount);
    printf("%d", usercount);
}
