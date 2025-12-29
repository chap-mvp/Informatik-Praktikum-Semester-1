/*
Ihr Programm soll eine einfache Benutzerverwaltung durchführen:

Bis zu 120 Benutzernamen und eindeutig zugeordnete Passworte sollen zwecks Registrierung nacheinander über die Konsole eingelesen und gespeichert werden.

Benutzernamen müssen:
6 bis 9 Zeichen lang sein,
einen Großbuchstaben als erstes Zeichen enthalten,
ab dem zweiten Zeichen nur aus Kleinbuchstaben oder dezimalen Ziffern bestehen.

Passworte müssen:
8 bis 14 Zeichen lang sein,
mindesten einen Großbuchstaben, einen Kleinbuchstaben und eine dezimale Ziffer enthalten,
zum Anlegen zweimal identisch eingegeben werden.

Bei der Benutzeranmeldung müssen:
der Benutzername und das Passwort eingegeben werden,
eine Mitteilung über den erfolgreichen Anmeldeversuch ausgegeben werden, falls die Benutzeranmeldung korrekt war,
eine Mitteilung über den erfolglosen Anmeldeversuch ausgegeben werden, falls die Benutzeranmeldung fehlerhaft war.

Es sind maximal drei erfolglose Anmeldeversuche erlaubt. Bei Überschreiten dieser Maximalzahl soll der Nutzer für einen erneuten Anmeldeversuch für die Dauer von zwei Minuten gesperrt werden.
Zur Passwortänderung muss zunächst das gespeicherte Passwort korrekt und dann das neue Passwort mit korrekter Wiederholung eingegeben werden.
Bei jeder Passworteingabe soll jedes zum Passwort gehörende Zeichen während der Eingabe im Klartext auf dem Bildschirm dargestellt und beim Abschluss der Eingabe durch einen Stern (*) überschrieben werden.
Bei fehlerhaften Eingaben sollen aussagekräftige Fehlermeldungen auf dem Bildschirm ausgegeben werden. Der fehlerhafte Vorgang soll zurückgesetzt werden.
Vorgaben zum Lösungsweg
Lesen Sie ein Passwort als zusammenhängende Eingabe ein, indem Sie die Passworteingabe durch Drücken der Taste "Return" abschließen.
Verwenden Sie die aktuelle Uhrzeit (Bibliothek time.h), um die Sperrfrist nach fehlerhafter Passworteingabe zu überwachen (Sommer-/Winterzeit ist zu vernachlässigen).

Vorgaben zum Lösungsweg
Nutzen Sie für die Ermittlung von Systemdatum und –zeit die in C integrierten Funktionen aus <time.h>. Falls die Systemzeit außerhalb der Öffnungszeiten des Parkhauses liegt, kann kein Fahrzeug einfahren, und es erfolgt die Ausgabe „Parkhaus geschlossen“.
Schreiben Sie in Ihrem Programm eine Funktion, die mit Hilfe des in C integrierten Zufallszahlengenerators eine simulierte Parkdauer und die sich daraus ergebende Parkgebühr berechnet und auf der Basis von Systemdatum und Systemzeit die Einfahrtzeit und die sich aus der Parkdauer ergebende Ausfahrtzeit berechnet. Die Parkdauer soll im Bereich zwischen 1min und der durch die Öffnungszeiten des Parkhauses limitierten maximal möglichen Parkdauer am betreffenden Tag liegen.
Schreiben Sie in Ihrem Programm eine Funktion, die die Geldscheine und Münzen für die Parkgebühr entgegennimmt und das Rückgeld sowie die Aufteilung der Münzen berechnet. Gehen Sie davon aus, dass die einzelnen Münzbestände für das Rückgeld nie leer werden, d.h. der Automat soll immer in optimaler Stückelung herausgeben.
Schreiben Sie in Ihrem Programm eine Funktion, die den oben dargestellten Parkschein als Bildschirmausgabe erzeugt.
*/

#include <stdio.h>

