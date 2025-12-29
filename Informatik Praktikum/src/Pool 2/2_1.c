/*
Das Programm soll aus Kontonummern und Bankleitzahlen deutscher Bankfilialen die ab dem Jahr 2014 verbindlichen internationalen Kontonummern (IBAN) generieren. Eine IBAN für deutsche Banken hat den folgenden Aufbau:
DEPPBBBBBBBBNNNNNNNNNN (22 Stellen) mit den einzelnen Bestandteilen:
DE           Ländercode für Deutschland
PP           Prüfziffer
BBBBBBBB     Bankleitzahl
NNNNNNNNNN   Kontonummer (10-stellig)

Ihr Programm soll:
 - Bankleitzahlen und Filialbezeichnungen aus der anliegenden Textdatei BLZ.txt einlesen und die Bankleitzahlen und Filialbezeichnungen zeilenweise auf dem Bildschirm ausgeben.
 - die Bankdaten, also die Kontonummer und die Bankleitzahl eines deutschen Kontos über die Tastatur einlesen, auf korrekte Eingabe prüfen und ggfs. eine Fehlermeldung auf dem Bildschirm ausgeben, die den Ort des Fehlers benennt.
 - die Filialbezeichnung aus der Filialliste heraussuchen und eine Fehlermeldung auf dem Bildschirm ausgeben, falls die Bankfiliale nicht enthalten ist
 - die Prüfziffer der IBAN nach dem in der Norm ISO 7064 definierten Verfahren „Modulus 97-10“ berechnen (s.u.).
 - die IBAN aus der Prüfziffer, der Bankleitzahl und der Kontonummer generieren.
 - die IBAN zusammen mit Kontonummer, Bankleitzahl und Filialbezeichnung sowie der Anzahl benötigter Suchschritte in der Filialliste auf dem Bildschirm ausgeben.

Algorithmus zum Berechnen der Prüfziffer nach Modulus 97-10 (ISO 7064)
 1. Vorbereitung der IBAN: 
  Erstellen Sie zunächst eine allein aus Ziffern bestehende nIBAN nach folgendem Schema: BBBBBBBBNNNNNNNNNNDEPP, d.h. die ersten vier Stellen der IBAN (Ländercode und Prüfziffer) bilden die letzten Stellen der nIBAN.  Die nicht  numerischen Buchstaben des Ländercodes werden als Hexziffern interpretiert und zum Aufbau der nIBAN durch ihren zweistelligen dezimalen Zahlenwert ersetzt. Die Prüfziffer wird mit 00 initialisiert. 
  Die so initialisierte nIBAN hat 24 Dezimalziffern: BBBBBBBBNNNNNNNNNN131400.
 2. Prüfziffer anhand der nIBAN berechnen: 
  Berechnen Sie zunächst den ganzzahligen Rest R der nIBAN nach Division durch 97 (Modulo-Division, d.h. R = nIBAN % 97). Die Prüfziffer P ergibt sich damit zu P=98-R.
 3. IBAN erstellen: 
  Setzen Sie die berechnete Prüfziffer P an der vorgesehenen Stelle in die IBAN ein. Falls P<10 wird in der Prüfziffernfolge der IBAN eine führende Null ergänzt.
 
Beispiel für Ergebnisse zu den Schritten 1-3:
IBAN =  DEPP200800000970375700
Schritt 1: nIBAN = 200800000970375700131400
Schritt 2: R = 200800000970375700131400 % 97 = 10, P = 98 - R = 88
Schritt 3: IBAN =  DE88200800000970375700

Vorgaben zum Lösungsweg
 - Die Kontonummer darf max. 10 Ziffern und keine anderen Zeichen enthalten. Hat die eingelesene Kontonummer weniger als 10 Stellen, muss sie vorne mit Nullen aufgefüllt werden.
 - Die Bankleitzahl muss exakt 8 Ziffern haben und darf keine anderen Zeichen enthalten.
 - Prüfen Sie, ob in der Programmiersprache C ein geeignetes numerisches Datenformat existiert, mit dem Sie die Modulo-Division zur Berechnung des Rests R zur nIBAN mit einer einzigen Operation in der erforderlichen Genauigkeit durchführen können! Falls Sie kein passendes Datenformat finden, bestimmen Sie R stattdessen iterativ: Teilen Sie dazu die nIBAN in mehrere Ziffernabschnitte gleicher Länge auf. Berechnen Sie den sich aus dem ersten Ziffernabschnitt ergebenden Divisionsrest R’ und stellen Sie diesen an den Anfang des folgenden Ziffernabschnitts. Wiederholen Sie das Vorgehen mit den verlängerten Ziffernabschnitten. Im letzten Durchlauf erhalten Sie dann den gesuchten Rest R. (Das Verfahren zur Bestimmung von R basiert auf einem sinnvollen Anwenden des Horner-Schemas zur Umrechnung einer Zahl aus der Zahlenbasis 10 in die Zahlenbasis 97.)
*/

#include <stdio.h>

int main () {
    

    return 0;
}