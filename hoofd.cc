// file hoofd.cc
#include <iostream>
#include <cstdlib>
#include "gobord.h"
#include "stapel.h"

using namespace std;

int main (int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Onjuist aangeroepen! \n";
        cout << "hetSpel moet aangeroepen worden in het volgende format: \n";
        cout << "./hetSpel [hoogte] [breedte] [aantalVereistOmTeWinnen] \n";

        return 1;
    }

    int hoogte = atoi(argv[1]);
    int breedte = atoi(argv[2]);
    int aantalVereist = atoi(argv[3]);

    gobord Gobord(hoogte, breedte, aantalVereist);
    stapel Stapel;

    Stapel.breedte = breedte;
    Stapel.hoogte = hoogte;

    cout << "Wil je dat speler 1 een computer of een mens is? \n";
    cout << "Geef de letter [M] voor mens en [C] voor computer. \n";
    char optie = Gobord.leesOptie();

    while (optie != 'C' && optie != 'c' && optie != 'm' && optie != 'M') {
        cout << "Ongeldige optie! \n";
        cout << "Wil je dat speler 1 een computer of een mens is? \n";
        cout << "Geef de letter [M] voor mens en [C] voor computer. \n";
        optie = Gobord.leesOptie();
    }

    cout << "Wil je dat speler 2 een computer of een mens is? \n";
    cout << "Geef de letter [M] voor mens en [C] voor computer. \n";
    char optie2 = Gobord.leesOptie();

    while (optie != 'C' && optie != 'c' && optie != 'm' && optie != 'M') {
        cout << "Ongeldige optie! \n";
        cout << "Wil je dat speler 2 een computer of een mens is? \n";
        cout << "Geef de letter [M] voor mens en [C] voor computer. \n";
        optie2 = Gobord.leesOptie();
    }

    Gobord.computer1 = (optie == 'C' || optie == 'c');
    Gobord.computer2 = (optie2 == 'C' || optie2 == 'c');

    if (Gobord.computer1 && Gobord.computer2) {
        cout << "\nHoeveel potjes wil je dat de computers tegen elkaar spelen?";
        cout << "\nGeef een getal kleiner dan 500.\n";

        Gobord.aantalKeerSpelen = Gobord.leesGetal(500);

        // initialisatie statistiek
        Gobord.aantalKeerWitWint = 0;
        Gobord.aantalKeerZwartWint = 0;
        Gobord.totaalAantalZetten = 0;
    }
    
    Gobord.gobordMenu();
    return 0;
}//main