# schmuhis
repo for friends to code together &lt;3

### Code conventions 
* Alle Namen sind in Kleinbuchstaben und mit Unterstrichen
* Keine Präfixe oder Suffixe (z.B. m_member, member_, imy_interface)
* Das gilt auch für get/set, C++ Standard ist eher int param() const /*getter*/; void param(int) /*setter*/;
* Wenn ein Member eh getter und setter hat, dann kann es auch public sein
* Ifs und Schleifen sollten nur dann {}-Klammern haben, wenn es nötig ist
* { auf der Zeile des Ifs oder der Schleife
* Formatierung gilt auch für Klassen und Funktionen außer es wird wirklich unübersichtlich
* Konstruktor-Initialisierer in der Signatur-Zeile oder direkt darunter, in dem Fall : eingerückt und die , am Ende der Zeile 
* Keine unnötigen Kommentare (// destructor)
* Wichtige Bitte: den Code nicht automatisch formatieren lassen, da geht immer etwas verloren, insb. z.B. korrekte Einrückung für "Alignment" (also: Tabs für Nesting, Spaces für Ausrichtung z.B. von Continuation Lines, dann sieht die ganze Sache mit anderen Tab-Settings auch noch ok aus).

### Installation of required libs:
 - 'sudo apt install libboost-all-dev libglfw3-dev libglew-dev libglm-dev'


schmuhbeck todos:
- runtime parameter ob server oder client, + ip-adresse von server für client
- network component klasse ist für netzwerk kommunikation zuständig
	- speicher port, ip und gebuffered messages, kann alle ausgeben auf methode