// file gobord.cc
#include <iostream>
#include <cstring>
#include "gobord.h"
#include "stapel.h"

using namespace std;


// ID stapel en tempGobord voor latere referenties
stapel Stapel;
gobord gobord::tempGobord;

gobord::gobord(const gobord& other) {
  // onderdeel van copy constructor voor dynamic arr pointerboard
  // maak gebruikt van een hardcopy zodat pointerboard en temp pointerboard
  // niet hetzelfde memory gebruiken

  this->hoogte = other.hoogte;
  this->breedte = other.breedte;
  this->aantalVereist = other.aantalVereist;

  this->maakGobord(); 

  bordvakje* pThis = this->ingang;
  bordvakje* pOther = other.ingang;

  for (int i = 0; i < hoogte * breedte; i++) {
    *pThis = *pOther; 
    pThis++;
    pOther++;
  }
}//gobord::gobord(const gobord& other) 

gobord& gobord::operator=(const gobord& other) {
  // onderdeel van copy constructor voor dynamic arr pointerboard
  // maak gebruikt van een hardcopy zodat pointerboard en temp pointerboard
  // niet hetzelfde memory gebruiken

  if (this != &other) { 
    this->hoogte = other.hoogte;
    this->breedte = other.breedte;
    this->aantalVereist = other.aantalVereist;

    delete[] this->ingang; 
    this->maakGobord();  

    bordvakje* pThis = this->ingang;
    bordvakje* pOther = other.ingang;

    for (int i = 0; i < hoogte * breedte; i++) {
      *pThis = *pOther; 
      pThis++;
      pOther++;
    }
  }
  return *this;
}//gobord& gobord::operator=(const gobord& other)


bordvakje::bordvakje(const bordvakje& other) {
  // onderdeel van copy constructor voor bordvakje pointerboard
  // maak gebruikt van een hardcopy zodat pointerboard en temp pointerboard
  // niet hetzelfde memory gebruiken
  
  this->kleur = other.kleur;

  for (int i = 0; i < 6; i++) {
    if (other.buren[i] != nullptr) {
      this->buren[i] = new bordvakje(*(other.buren[i]));  
    } else {
      this->buren[i] = nullptr;
    }
  }
}//bordvakje::bordvakje(const bordvakje& other)

void gobord::maakGobord() {
  hoeveelsteZet = 0;

  bordvakje* p = new bordvakje[hoogte * breedte];
  ingang = p;

  for (int rij = 0; rij < hoogte; rij++) {
    for (int kolom = 0; kolom < breedte; kolom++) {
      // zet voor elke pointer elk vakje leeg
      p->kleur = ' ';

      // zet alle pointers naar nullpointers
      for (int i = 0; i < 6; i++) {
        p->buren[i] = nullptr;
      }

      // als huidig vakje niet in de linkmeeste kolom bevindt
      if (kolom > 0) { 
        // initialiseer linker buren van huidig vakje
        p->buren[5] = (p - 1); 
        (p - 1)->buren[2] = p; 
      }

      // als huidig vakje niet in de meestrechtse kolom bevindt
      if (kolom < breedte - 1) {
        // initialiseer rechter buren van huidig vakje
        p->buren[2] = (p + 1); 
        (p + 1)->buren[5] = p; 
      }

      // als huidig vakje niet in de bovenste rij bevindt
      if (rij > 0) {
        // initialiseer onder buren van huidig vakje
        p->buren[0] = (p - breedte);
        (p - breedte)->buren[4] = p;
      }

      // als huidig vakje niet in de onderste rij bevindt
      if (rij < hoogte - 1) {
        // initialiseer boven buren van huidig vakje
        p->buren[4] = (p + breedte);
        (p + breedte)->buren[0] = p;
      }

      // ga door naar volgend vakje
      p++;
    }
  }
}//gobor::maakGobord()

void gobord::resetGobord() {
  // v deallocate memory gebruikt door board
  delete[] ingang;

  // v houdt totale aantalZetten bij
  totaalAantalZetten = totaalAantalZetten + hoeveelsteZet;
  hoeveelsteZet = 0;

  // v maak een nieuw board aan
  gobord::maakGobord();
}//gobord::resetGobord


bordvakje::bordvakje() {
  kleur = ' ';
}

void gobord::drukaf() {
  // ^ Simpele functie die de huidige temp pointerboard print
  // Wordt gebruikt na elke iteratie speelMenu

  cout << '\n';

  bordvakje* p = ingang;

  for (int r = 0; r < hoogte; r++) {
    for (int t = 0; t < breedte; t++) {
      switch(p->kleur) {
        case 'W': // wit vakje
          cout << "[W]";
          break;
        case 'Z': // zwart vakje
          cout << "[Z]";
          break;
        default: // leeg vakje
          cout << "[ ]";
      }
      p++;
    }
    cout << '\n';
  }

}//gobord::drukaf

void gobord::vervolg() {
    for (int r = 0; r < breedte; r++) {
      volleKolommen[r] = -1;
    } 
  
  gobord::aantalLegeKolommenTemp();

  if (gobord::heeftGewonnen(tempGobord)) {

    if (aantalTotaalVolgendeIteratie % 2 == 0) {
      aantalMogelijkhedenWitWint++;
    } else {
      aantalMogelijkhedenZwartWint++;
    }

    aantalTotaal++;
    return;
  }

  if (gobord::isBordVol(tempGobord)) {
    aantalTotaal++;
    aantalMogelijkhedenGelijkspel++;
    return;
  }

  for (int kolom = 0; kolom < breedte; kolom++) {
    bool isInVolleKolommen = false;

    for (int i = 0; i < breedte; i++) {
      if (volleKolommen[i] == kolom) {
        isInVolleKolommen = true;
        return;
      }
    }

    if (!isInVolleKolommen) {
      gobord::tempZet(kolom);

      if (gobord::heeftGewonnen(tempGobord)) {
        aantalTotaal++;

        if (aantalTotaalVolgendeIteratie % 2 == 0) {
          aantalMogelijkhedenWitWint++;
        } else {
          aantalMogelijkhedenZwartWint++;
        }

        gobord::terugTempZet(kolom, tempGobord);
      } else {
        if (gobord::isBordVol(tempGobord)) {
          aantalTotaal++;
          aantalMogelijkhedenGelijkspel++;
          return;
        }

        aantalTotaal++;
        aantalTotaalVolgendeIteratie++;

        gobord::vervolg();
        gobord::terugTempZet(kolom, tempGobord);
      } 
    }
  }
}

void gobord::logStatistiekDoorlopen() {
  cout << "\n-=+ Bijgehouden statistiek +=- \n\n"; 

  cout << "Aantal mogelijke posities dat wit wint: " << aantalMogelijkhedenWitWint << '\n';
  cout << "Aantal mogelijke posities dat zwart wint: " << aantalMogelijkhedenZwartWint << '\n';
  cout << "Aantal mogelijke posities dat gelijkspel is: " << aantalMogelijkhedenGelijkspel << '\n';
  cout << "Aantal mogelijke posities in totaal (inclusief onbepaald): " << aantalTotaal << '\n';
}

void gobord::drukafTemp() {
  // ^ Simpele functie die de huidige temp pointerboard print
  // alleen gebruikt voor debuggen van de code

  cout << '\n';

  bordvakje* p = tempGobord.ingang;

  for (int r = 0; r < tempGobord.hoogte; r++) {
    for (int t = 0; t < tempGobord.breedte; t++) {
      switch (p->kleur) {
        case 'W': // wit vakje
          cout << "[W]";
          break;
        case 'Z': // zwart vakje
          cout << "[Z]";
          break;
        default: // leeg vakje
          cout << "[ ]";
      }
      p++;
    }
    cout << '\n';
  }
}//drukAfTemp();

void gobord::initialiseerComputer() {
  // ^ Simpele functie die de huidige temp pointerboard print
  // alleen gebruikt voor debuggen van de code

  // v reset statistiek
  aantalKeerWitWint = 0;
  aantalKeerZwartWint = 0;
  totaalAantalZetten = 0;

  for (int r = 0; r < aantalKeerSpelen; ++r) {
    gobord::maakZet();
    // ^ aangezien deze functie zichzelf zal heraanroepen totdat het spel gespeeld
    // is als beide spelers computer zijn hoeft dit een keer aangeroepen te worden

    // v druk het board af en reset board en stapel arr
    gobord::drukaf();
    gobord::resetGobord();
    Stapel.reset();
  } 

  // v berekeningen rondom statistiek en bijhorende print statements
  float gemiddeldAantalZetten = static_cast<float>(totaalAantalZetten) / aantalKeerSpelen;

  cout << "\n-=+ Bijgehouden statistiek +=- \n\n";
  cout << "Aantal keer dat wit won: " << aantalKeerWitWint << '\n';
  cout << "Aantal keer dat zwart won: " << aantalKeerZwartWint << '\n';
  cout << "Aantal keer gelijkspel: " << aantalKeerSpelen - aantalKeerWitWint - aantalKeerZwartWint << '\n';
  cout << "Totaal aantal zetten gespeeld: " << totaalAantalZetten << '\n';
  cout << "Gemiddeld aantal zetten gespeeld per potje: " << gemiddeldAantalZetten << '\n';

}//gobord::initialiseerComputer()

bool gobord::aantalCellsAchterElkaarRij(int rij, int kolom, int checkRij, int checkKolom, const gobord& board) {
  // ^ subonderdeel van functie heeftGewonnen die itereert op basis van variablen
  // die de hoek van de iteratie doorgeven. Daarnaast wordt een reeks bijgehouden
  // van hoevaak een zet van dezelfde speler achter elkaar voorkomt

  char kleur = ' ';
  int aantalAchterElkaar = 0;

  for (int r = 0; r < aantalVereist; r++) {
    if ((rij + r * checkRij) >= 0 && (rij + r * checkRij)  < board.hoogte && (kolom + r * checkKolom) >= 0 && (kolom + r * checkKolom) < board.breedte) {
      // als checkRij == 1 && checkKolom == 0 =>
      // de pointers blijven in dezelfde rij qua iteratie (boven <=> onder)
      // als checkRij == 0 && checkKolom == 1 =>
      // de pointers blijven in dezelfde kolom qua iteratie (links <=> rechts)
      // als checkRij == 1 && checkKolom == 1 =>
      // de pointers blijven diagonaal qua iteratie (linksonder <=> rechtsboven)
      // als checkRij == 1 && checkKolom == -1 =>
      // de pointers blijven diagonaal qua iteratie ( linksboven <=> rechtsonder)
      bordvakje* p = board.ingang + (rij + r * checkRij) * board.breedte + (kolom + r * checkKolom);

      // als huidig vakje niet leeg is
      if (p->kleur != ' ') {
        if (kleur == ' ' || kleur == p->kleur){ 
          // ^ als vorig vakje leeg is of vorig vakje == huidig vakje
          // v dan vergroot de reeks aantal achter elkaar
          kleur = p->kleur;
          aantalAchterElkaar++;
        } else { // eerste in de reeks
          kleur = ' ';
          aantalAchterElkaar = 1;
        }
      } else { // als huidig leeg is reset de reeks aantal achter elkaar
        kleur = ' ';
        aantalAchterElkaar = 0;
      }

      if (aantalAchterElkaar == aantalVereist) {
        return true;
      }
    } else {
      kleur = ' ';
      aantalAchterElkaar = 0;
    }
  }
  return false;
}//gobord::aantalCellsAchterElkaarRij(int rij, int kolom, int checkRij, int checkKolom, const gobord& board)

bool gobord::winnendPatroonKolommen(const gobord& board) {
  // ^ subonderdeel van functie heeftGewonnen die checkt of iemand in een kolom
  // gewonnen heeft

  for (int kolom = 0; kolom < board.breedte; kolom++) {
    for (int rij = 0; rij <= board.hoogte - aantalVereist; rij++) {
      if (aantalCellsAchterElkaarRij(rij, kolom, 1, 0, board)) {
        return true;
      }
    }
  }
  return false;
}//winnendPatroonKolommen(const gobord& board)

bool gobord::winnendPatroonRijen(const gobord& board) {
  // ^ subonderdeel van functie heeftGewonnen die checkt of iemand in een rij
  // gewonnen heeft

  for (int rij = 0; rij < board.hoogte; rij++) {
    for (int kolom = 0; kolom <= board.breedte - aantalVereist; kolom++) {
      if (aantalCellsAchterElkaarRij(rij, kolom, 0, 1, board)) {
        return true;
      }
    }
  }
  return false;
}//winnendPatroonRijen(const gobord& board)

bool gobord::winnendPatroonDiagonaal(const gobord& board) {
  // ^ subonderdeel van functie heeftGewonnen die checkt of iemand op een 
  // diagonaal gewonnen heeft. Is opgedeeld in diagonaal van linksonder naar 
  // rechtsboven en diagonaal van linksboven naar rechtsonder

  for (int rij = 0; rij <= board.hoogte - aantalVereist; rij++) {
    for (int kolom = 0; kolom <= board.breedte - aantalVereist; kolom++) {
      if (aantalCellsAchterElkaarRij(rij, kolom, 1, 1, board)) {
        return true;
      }
    }
  }
  
   for (int rij = 0; rij <= board.hoogte - aantalVereist; rij++) {
    for (int kolom = aantalVereist - 1; kolom < board.breedte; kolom++) {
      if (aantalCellsAchterElkaarRij(rij, kolom, 1, -1, board)) {
        return true;
      }
    }
  }

  return false;
}//gobord::winnendPatroonDiagonaal(const gobord& board)

bool gobord::heeftGewonnen(const gobord& board) {
  // ^ deze functie vraagt een pointerboard (= pointerboard of temp pointerboard)
  // en checkt of iemand heeft gewonnen (T/F). Wordt gebruikt om te kijken of 
  // de huidige positie gewonnen is. En vanaf hoeveelsteZet kan de winnende
  // speler afgeleid worden

  if (gobord::winnendPatroonKolommen(board)) {
    return true;
  }

  if (gobord::winnendPatroonRijen(board)) {
    return true;
  }

  if (gobord::winnendPatroonDiagonaal(board)) {
    return true;
  }

  return false;
}//gobord::heeftGewonnen(const gobord& board)

bool gobord::isBordVol(const gobord& board) {
  // ^ Simpele functie die checkt of het bord vol is. Wordt gebruikt om te
  // bepalen of het gelijkspel tijdens het spelen

  for (int kolom = 0; kolom < board.breedte; kolom++) {
    for (int r = 0; r < board.hoogte; r++) {

      bordvakje* p = board.ingang + r * board.breedte + kolom;

      if (p->kleur == ' ') {
        return false;
      }
    }
  }

  return true;
}//gobord::isBordVol(const gobord& board)


int gobord::genereerZet() {
  // ^ deze functie genereert een kolom op basis van welke kolom nog niet vol is
  // in het pointerboard. Wordt gebruikt om de zet voor de computer te bepalen
  
  bool kolomIsVol = true;
  int kolom;

  while (kolomIsVol) {
    kolom = rand() % breedte;
    bordvakje* p = ingang + (hoogte - 1) * breedte + kolom;

    kolomIsVol = true;

    for (int r = 0; r < hoogte; r++) {
      if (p->kleur == ' ') {
        kolomIsVol = false;
        break;
      }
      p -= breedte;
    }
  }

  return kolom;
}//gobord::genereerZet()

int gobord::aantalLegeKolommenTemp() { 
  // ^ deze functie houdt bij welke kolommen vol zijn en hoeveel dat zijn
  // in de temp pointerboard (zodat huidige pointerboard niet wordt aangepast)
  // wordt gebruikt voor doorlopen alle mogelijkheden qua winnende partijen

  Kolomindex = 0;
  int aantal = breedte;

  for (int kolom = 0; kolom < tempGobord.breedte; kolom++) {
    bordvakje* p = tempGobord.ingang + (tempGobord.hoogte - 1) * tempGobord.breedte + kolom;

    bool kolomIsVol = true;

    for (int rij = 0; rij < tempGobord.hoogte; rij++) {
      if (p->kleur == ' ') {
        kolomIsVol = false;
        aantal++;
        break;
      }
      p -= tempGobord.breedte;
    }

    if (kolomIsVol) {
      volleKolommen[Kolomindex] = kolom;
      Kolomindex++;
    }
  }
  return aantal;
}//gobord::aantalLegeKolommenTemp()

void gobord::tempZet(int kolom) {
  // ^ deze functie maakt een zet in het temp pointerboard op basis van een
  // gegeven kolom. Wordt gebruikt in de vervolg functie om elke 
  // mogelijke zet te maken en verder te lopen door het board heen

  char kleur = (hoeveelsteZet % 2 == 0) ? 'W' : 'Z'; 

  bordvakje* p = tempGobord.ingang + (tempGobord.hoogte - 1) * tempGobord.breedte + kolom;

  if (p >= tempGobord.ingang && p < tempGobord.ingang + tempGobord.hoogte * tempGobord.breedte) {
    while (p >= tempGobord.ingang && p->kleur != ' ') {
      p -= tempGobord.breedte;
    }

    if (p >= tempGobord.ingang) {
      p->kleur = kleur;
      hoeveelsteZet++;
    }
  }

  gobord::drukafTemp();
}//gobord::tempZet(int kolom)

void gobord::terugTempZet(int kolom, const gobord& board) {
  // ^ deze functie neemt een zet terug in het (temp) pointerboard op basis van 
  // een gegeven kolom. Wordt gebruikt in de vervolg functie om na
  // iteraties terug te gaan in het board om andere "wegen" te lopen

  bordvakje* p = board.ingang + kolom; 

  while ((p < board.ingang + board.hoogte * board.breedte) && (p->kleur == ' ')) {
    p += board.breedte;
  }

  if (p < board.ingang + board.hoogte * board.breedte) {
      p->kleur = ' ';
      hoeveelsteZet--;
  }
}//gobord::terugTempZet(int kolom, const gobord& board)

void gobord::maakZet() {
  // ^ deze functie maakt een zet in het pointerboard op basis van een generatie
  // als het gaat om een computer of op basis van een gegeven input van de speler.
  // De functie heeft 4 mogelijkheden; speler-1, speler-2, computer-1
  // of computer-2 

  // v set temp pointerboard zodat vorige iteratie bekend is
  tempGobord = *this;


  // v is het board gelijkspel
  if (gobord::isBordVol(*this)) {
    cout << "\nHet bord is vol, ofwel gelijkspel!";
    return;
  }

  // v Wie is aan zet en welke kleur heeft de huidige speler
  char kleur = (hoeveelsteZet % 2 == 0) ? 'W' : 'Z'; // W : Wit, Z: Zwart
  int kolom;

  // v geval speler computer-1 of computer-2
  if ((hoeveelsteZet % 2 != 0 && computer2) || (hoeveelsteZet % 2 == 0 && computer1)) {
    kolom = gobord::genereerZet();

    // v Begin bij de meest onderste pointer in de gevraagde kolom
    bordvakje* p = ingang + (hoogte - 1) * breedte + kolom;

    // v Vind het eerste niet gebruikte vakje voor de gegeven kolom
    while (p->kleur != ' ' && p >= ingang) {
      p -= breedte;
    }

    // v houdt de gemaakte zetten bij zodat ze makkelijk terug gezet kunnen worden
    Stapel.voegZetToe(kolom);

    // v zorg dat het vakje de juiste kleur krijgt
    p->kleur = kleur;

    hoeveelsteZet++;
  } else {  // < geval speler mens-1 of mens-2
      if (kleur == 'W') {
        cout << "\nIn welke kolom wilt u uw zet maken? Wit is aan zet. \n";
      } else {
        cout << "\nIn welke kolom wilt u uw zet maken? Zwart is aan zet. \n";
      }

      cout << "Geef een getal kleiner dan de breedte van het bord. \n";

      kolom = leesGetal(20);

      if (kolom >= breedte || kolom < 0) {
        cout << "Ongeldige kolom! Maak uw zet opnieuw. \n";
        return;
      }

      // Begin bij de meest onderste pointer in de gevraagde kolom
      bordvakje* p = ingang + (hoogte - 1) * breedte + kolom;

      int rijIndex = 0;
      // Vind het eerste niet gebruikte vakje voor de gegeven kolom
      while (p->kleur != ' ' && p >= ingang) {
        p -= breedte;
        rijIndex++;
      }

      Stapel.voegZetToe(kolom);

      // is gevraagd vakje nog vrij, zo niet is kolom dus vol
      if (p >= ingang + kolom && p <= ingang + (hoogte - 1) * breedte + kolom) {
        p->kleur = kleur;
      } else {
        cout << "Deze kolom is vol! Maak uw zet opnieuw. \n";
        return;
      }

      hoeveelsteZet++;
  } 

  // v heeft een speler gewonnen op het huidig board
  if (gobord::heeftGewonnen(*this)) {
     if (kleur == 'W') {
        cout <<  "\nSpeler 1 ofwel wit heeft gewonnen!";
        ++aantalKeerWitWint;
      } else {
        cout << "\nSpeler 2 ofwel zwart heeft gewonnen!";
        ++aantalKeerZwartWint;
      }
    spelerHeeftGewonnen = true;
    return;
  }

  if ((hoeveelsteZet % 2 != 0 && computer2) || (hoeveelsteZet % 2 == 0 && computer1)) {
    // ^ als de nieuwe zet de zet van de computer is ga automatisch door 
    // naar volgende zet
    maakZet();
  }
} //gobord::maakZet

void gobord::neemZetTerug() {

  gobord::terugTempZet(Stapel.neemZetTerug(), *this);
  cout << "Zet teruggenomen. \n";
}//gobord::neemZetTerug()

char gobord::leesOptie() {
    char leesKarakter = ' ', optie;

    while (leesKarakter != '\n') {
        optie = leesKarakter;
        cin.get(leesKarakter);
    }
    return optie;
}//gobord::leesOptie

int gobord::leesGetal(int maximum) {
    int getal = 0;
    char karakter;

    while ((karakter = cin.get()) != '\n') {
        if (karakter >= '0' && karakter <= '9' && getal <= maximum) {
            getal = getal * 10 + (karakter - '0');
        }
    }
    if (getal > maximum) {
        getal = maximum;
    }

    return getal;
}//gobord::leesGetal

void gobord::parametersVeranderen() {

  cout << "Geef een nieuwe waarde voor de hoogte: ";
  hoogte = leesGetal(20);
  cout << "Geef een nieuwe waarde voor de breedte: ";
  breedte = leesGetal(20);
  cout << "Geef een nieuwe waarde voor het aantal vereist om te winnen:  ";
  aantalVereist = leesGetal(20);
  cout << '\n';

  gobord::maakGobord();
}//gobord::parametersVeranderen

void gobord::instellingenMenu() {
  char keuze = '$';
  while (keuze != 't' && keuze != 'T') {
    cout << "\nKies uit 1 van de volgende opties: \n";
    cout << "[P]arameters veranderen, [T]erug. \n";

    keuze = gobord::leesOptie();

    switch(keuze) {
      case('P'):
      case('p'):
        parametersVeranderen();
        break;
      case('T'):
      case('t'):
        break;
    }
  }
}//gobord::instellingenMenu

void gobord::speelMenu() {
  char keuze = '$';
  while (keuze != 't' && keuze != 'T') {
    gobord::drukaf();

    cout << "\n Kies uit 1 van de volgende opties: \n";

    if (!spelerHeeftGewonnen) {
      cout << "[Z]et maken, [T]erug, [A]antal mogelijkheden";
    } else {
      cout << "[R]eset";
    }

    if (computer1 == 0 && computer2 == 0) {
      cout << ", Z[e]t terugnemen";
    } 
  
    cout << '\n';

    keuze = gobord::leesOptie();

    switch(keuze) {
      case('Z'):
      case('z'):
        if (!spelerHeeftGewonnen) {
          gobord::maakZet();
        } else {
          cout << "Speler heeft gewonnen! Zet maken is niet toegestaan.\n";
        }
        break;
      case('t'):
      case('T'):
        break;
      case('R'):
      case('r'):
        if (spelerHeeftGewonnen) {
          resetGobord();
          spelerHeeftGewonnen = false;
        }
        break;
      case('e'):
      case('E'):
        if (computer1 == 0 && computer2 == 0) {
          gobord::neemZetTerug();
          spelerHeeftGewonnen = false;
        }
        break;
      case('A'):
      case('a'):
        tempGobord = *this;
        // v reset statistiek
        aantalTotaal = 0;
        aantalMogelijkhedenWitWint = 0;
        aantalMogelijkhedenZwartWint = 0;
        aantalTotaalVolgendeIteratie = 0;

        gobord::vervolg();
        gobord::logStatistiekDoorlopen();
        break;
    }
  }
}//gobord::speelMenu

void gobord::gobordMenu() {
    char keuze = '$';
    while (keuze != 'a' && keuze != 'A') {
      // print gobord?
      // Gobord.drukaf();
      cout << "\n Kies uit 1 van de volgende opties: \n";
      cout << "[A]fsluiten, [B]egin het spel, [I]nstellingen. \n";

      keuze = gobord::leesOptie();

      switch (keuze) {
        case('A'):
        case('a'):
          break;
        case('B'):
        case('b'):
          if (computer1 && computer2) {
            gobord::initialiseerComputer();
          } else {
            gobord::speelMenu();
          }
          break;
        case('I'):
        case('i'):
          gobord::instellingenMenu();
          break;
      }
    cout << '\n';
  }
}//gobord::gobordMenu