// file gobord.h
class bordvakje {
  public:
    char kleur; 
    bordvakje* buren[6]; 
    bordvakje();  
    bordvakje(const bordvakje& other);
};//bordvakje

class gobord {
  private:
    bordvakje* ingang;
    int hoogte, breedte, aantalVereist, hoeveelsteZet;
  public:
    // v ID copy pointerboard
    static gobord tempGobord;  
    gobord() = default;

    bool computer1; // true als speler 1 een computer is, anders false
    bool computer2; // true als speler 2 een computer is, anders false
    int aantalKeerSpelen; // hoeveel potjes als computer1,computer = 1
    int aantalKeerWitWint; // aantal keer wit wint
    int aantalKeerZwartWint; // aantal keer zwart wint
    int totaalAantalZetten; // totaal aantal gemaakte zetten
    bool gebruikersError; // als true niet gobord printen zodat err visible is
    bool spelerHeeftGewonnen; // true als speler heeft gewonnen, anders false
    int volleKolommen[20] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                              -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // arr bijhouden welke kolommen leeg zijn
    int Kolomindex = 0; // int huidige kolom
    
    // v statistiek voor vervolg functie
    int aantalTotaal = 0;
    int aantalMogelijkhedenWitWint = 0;
    int aantalMogelijkhedenZwartWint = 0;
    int aantalMogelijkhedenGelijkspel = 0;
    int aantalTotaalVolgendeIteratie = 0; // voor distinctie speler-1 en speler-2


    gobord(int hoogte, int breedte, int aantalVereist) : hoogte(hoogte), breedte(breedte), aantalVereist(aantalVereist) {
      maakGobord();
    }
    // v functies hard copy main pointerboard
    gobord(const gobord& other);
    gobord& operator=(const gobord& other);
    // v functies voor bepalen of positie gewonnen is
    bool heeftGewonnen(const gobord& board);
    bool winnendPatroonDiagonaal(const gobord& board);
    bool winnendPatroonRijen(const gobord& board);
    bool winnendPatroonKolommen(const gobord& board);
    bool aantalCellsAchterElkaarRij(int rij, int kolom, int checkRij, int checkKolom, const gobord& board);
    // v functies voor vervolg
    void vervolg();
    void logStatistiekDoorlopen();
    void drukafTemp();
    bool heeftGewonnenTemp();
    int aantalLegeKolommenTemp();
    void tempZet(int kolom);
    void terugTempZet(int kolom, const gobord& board);
    void maakGobord();
    void resetGobord();
    // v algemene functies
    void drukaf();
    bool isBordVol(const gobord& board);
    void initialiseerComputer();
    int genereerZet();
    void maakZet();
    void neemZetTerug();
    char leesOptie();
    int leesGetal(int maximum);
    // v functies voor menu's
    void parametersVeranderen();
    void instellingenMenu();
    void speelMenu();
    void gobordMenu();
};//gobord
