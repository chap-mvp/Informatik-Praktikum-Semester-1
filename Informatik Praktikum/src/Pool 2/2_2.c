/*
Das Programm soll die Funktionen eines Parkscheinautomaten unter vereinfachten Bedingungen simulieren. Das Parkhaus öffnet und schließt zu einstellbaren Uhrzeiten. Fahrzeuge können nur während der Öffnungszeit in das Parkhaus einfahren oder es verlassen. Es werden die folgenden Parkgebühren berechnet: 1,60€ für die erste  angefangene Stunde, jeweils 1,40€ für die zweite und dritte angefangene Stunde, 1€ für jede weitere angefangene Stunde. Die ersten zehn Minuten sind kostenfrei. Als Einfahrtzeitpunkt wird die Systemzeit Ihres Computers beim Programmstart gewählt. Die Parkdauer soll mit Hilfe eines Zufallszahlengenerators unter Beachtung der Öffnungszeiten des Parkhauses simuliert werden. Aus der Parkdauer wird die Parkgebühr berechnet und angezeigt. Die Parkgebühr kann mit Münzen und Geldscheinen im Bereich zwischen 10ct und 10€ bezahlt werden. Sobald mindestens Geld im Wert der Parkgebühr eingeworfen worden ist, gibt der Automat das Rückgeld in Münzen von 2€, 1€, 50ct, 20ct oder 10ct zurück, wobei die Gesamtzahl der benötigten Münzen minimal sein soll. Zudem wird ein Parkschein mit den folgenden Angaben erstellt:

Datum:           TT.MM.JJJJ
Einfahrtszeit:   HH:MM Uhr
Ausfahrtzeit:    HH:MM Uhr
Parkdauer:       HH.MM h
Parkgebühr:      00,00 €
Gezahlt:         00,00 € (10€:S10, 5€:S5, 2€:M2, 1€:M1, 50ct:M50, 20ct:M20, 10ct:M10)
Rückgeld:        00,00 € (2€:M2, 1€:M1, 50Ct:M50, 20ct:M20, 10ct:M10)

Dabei kennzeichnen S10 und S5 die Anzahl der eingegebenen Geldscheine, M2, M1, M50, M20, M10 die Anzahlen der 2€-, 1€-, 50ct-, 20ct- und 10ct-Münzen, die als Einzahlung eingegeben oder als Rückgeld ausgegeben wurden.

Beispiel:           

Datum:           05.12.2017
Einfahrtszeit:   08:32 Uhr
Ausfahrtzeit:    13:47 Uhr
Parkdauer:       05.15 h
Parkgebühr:      07,40 €
Gezahlt:         10,00 € (10€:1, 5€:0, 2€:0, 1€:0, 50ct:0, 20ct:0, 10ct:0)
Rückgeld:        02,60 € (2€:1, 1€:0, 50ct:1, 20ct:0, 10ct:1)

Ihr Programm soll
 - beim Programmstart die Öffnungszeiten als Konsolenparameter einlesen
 - nach dem Programmstart die Systemzeit und das Systemdatum einlesen
 - mit Hilfe eines Zufallszahlengenerators eine zulässige Parkdauer erzeugen
 - die Parkgebühr berechnen
 - Geldscheine und Münzen für die Parkgebühr entgegennehmen
 - das Rückgeld sowie die Aufteilung der dafür benötigten Münzen ermitteln
 - den Parkschein mit den oben genannten Daten auf dem Bildschirm ausgeben

Vorgaben zum Lösungsweg
 - Nutzen Sie für die Ermittlung von Systemdatum und –zeit die in C integrierten Funktionen aus <time.h>. Falls die Systemzeit außerhalb der Öffnungszeiten des Parkhauses liegt, kann kein Fahrzeug einfahren, und es erfolgt die Ausgabe „Parkhaus geschlossen“.
 - Schreiben Sie in Ihrem Programm eine Funktion, die mit Hilfe des in C integrierten Zufallszahlengenerators eine simulierte Parkdauer und die sich daraus ergebende Parkgebühr berechnet und auf der Basis von Systemdatum und Systemzeit die Einfahrtzeit und die sich aus der Parkdauer ergebende Ausfahrtzeit berechnet. Die Parkdauer soll im Bereich zwischen 1min und der durch die Öffnungszeiten des Parkhauses limitierten maximal möglichen Parkdauer am betreffenden Tag liegen.
 - Schreiben Sie in Ihrem Programm eine Funktion, die die Geldscheine und Münzen für die Parkgebühr entgegennimmt und das Rückgeld sowie die Aufteilung der Münzen berechnet. Gehen Sie davon aus, dass die einzelnen Münzbestände für das Rückgeld nie leer werden, d.h. der Automat soll immer in optimaler Stückelung herausgeben.
 - Schreiben Sie in Ihrem Programm eine Funktion, die den oben dargestellten Parkschein als Bildschirmausgabe erzeugt.
*/