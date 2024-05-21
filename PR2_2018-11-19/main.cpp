#include <iostream>
/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOCNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAĐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
using namespace std;

// Headers I included below
#include<array>
#include<string>
#include<numeric>
// Headers I included above

const char* crt = "\n------------------------------------\n";

char* AlocirajNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
        return COUT;
    }

    // Methods I added below
    Datum(const Datum& datum)
        : _dan{ new int { datum.getDan() } }
        , _mjesec{ new int { datum.getMjesec() } }
        , _godina{ new int { datum.getGodina() } }
    {}

    Datum& operator=(const Datum& rhs) {
        *_dan = rhs.getDan();
        *_mjesec = rhs.getMjesec();
        *_godina = rhs.getGodina();

        return *this;
    }

    [[nodiscard]] int getDan() const noexcept {
        return *_dan;
    }

    [[nodiscard]] int getMjesec() const noexcept {
        return *_mjesec;
    }

    [[nodiscard]] int getGodina() const noexcept {
        return *_godina;
    }

    [[nodiscard]] int64_t getDatumAsDays() const noexcept {
        int64_t total{ 0 };

        const int mjesec{ getMjesec() };
        int godina{ getGodina() };

        total += getDan();
        total += (365ll * godina);

        if (mjesec <= 2) {
            --godina;
        }

        total += (godina / 4ll + godina / 400ll - godina / 100ll);

        total += [&]() {
            constexpr std::array<int, 12> daysPerMonth{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            return std::accumulate(
                std::begin(daysPerMonth),
                std::begin(daysPerMonth) + mjesec - 1,
                0
            );
        }();

        return total;
    }

    [[nodiscard]] int64_t operator-(const Datum& rhs) const noexcept {
        return getDatumAsDays() - rhs.getDatumAsDays();
    }
};

template<class T>
class Kolekcija {
    T* _niz;
    int _trenutno;
public:
    Kolekcija() : _trenutno(0), _niz(nullptr) {}
    ~Kolekcija() { delete[] _niz; _niz = nullptr; _trenutno = 0; }
    T* GetNiz() { return _niz; }
    int GetTrenutno() { return _trenutno; }
    //implementirati potrebne funkcije
    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno { kolekcija.getTrenutno() }
        , _niz{ new T[kolekcija.getTrenutno()] {} }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _niz[i] = kolekcija.getElement(i);
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        if (this == &rhs) {
            return *this;
        }

        _trenutno = rhs.getTrenutno();

        delete[] _niz;
        _niz = new T[getTrenutno()] {};

        for (int i = 0; i < getTrenutno(); ++i) {
            _niz[i] = rhs.getElement(i);
        }

        return *this;
    }

    [[nodiscard]] int getTrenutno() const noexcept { 
        return _trenutno; 
    }

    [[nodiscard]] const T& getElement(const int index) const {
        return _niz[index];
    }

    [[nodiscard]] T& getElement(const int index) {
        return _niz[index];
    }

    void Add(const T& element) {
        T* const temp{ new T[getTrenutno() + 1]{} };

        for (int i = 0; i < getTrenutno(); ++i) {
            temp[i] = getElement(i);
        }

        temp[getTrenutno()] = element;

        delete[] _niz;

        _niz = temp;

        ++_trenutno;
    }

    T& operator[](const int index) {
        return getElement(index);
    }

    friend std::ostream& operator<<(std::ostream& os, const Kolekcija& kolekcija) {
        for (int i = 0; i < kolekcija.getTrenutno(); ++i) {
            os << kolekcija.getElement(i);

            if (i + 1 != kolekcija.getTrenutno()) {
                os << '\n';
            }
        }

        return os;
    }
};

class Usluga {
    char* _naziv;
    double _cijena;//cijena usluge je izrazena po danu koristenja
public:
    Usluga() : _naziv(AlocirajNizKaraktera("")), _cijena(0) {}
    Usluga(const char* naziv, double cijena) : _cijena(cijena) {
        _naziv = AlocirajNizKaraktera(naziv);
    }
    ~Usluga() { delete[] _naziv; _naziv = nullptr; }
    double GetCijena() { return _cijena; }
    const char* GetNaziv() { return _naziv; }
    friend ostream& operator<< (ostream& COUT, const Usluga& obj);

    // Methods I added below
    Usluga(const Usluga& usluga)
        : _naziv { AlocirajNizKaraktera(usluga.getNaziv()) }
        , _cijena { usluga.getCijena() }
    {}

    Usluga& operator=(const Usluga& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _naziv;
        _naziv = AlocirajNizKaraktera(rhs.getNaziv());
        _cijena = rhs.getCijena();

        return *this;
    }

    [[nodiscard]] double getCijena() const noexcept { 
        return _cijena; 
    }

    [[nodiscard]] const char* getNaziv() const noexcept { 
        return _naziv; 
    }

    [[nodiscard]] bool operator==(const Usluga& rhs) const noexcept {
        return !std::strcmp(getNaziv(), rhs.getNaziv())
            && getCijena() == rhs.getCijena();
    }

    [[nodiscard]] bool operator!=(const Usluga& rhs) const noexcept {
        return !(*this == rhs);
    }
};

ostream& operator<< (ostream& COUT, const Usluga& obj) {
    COUT << obj._naziv << " -> " << obj._cijena << " KM";
    return COUT;
}

class Rezervacija {
    static int _rezervacijeIDBrojac;
    const int _rezervacijaID; ///broj rezervacije krece od 160000
    Datum _rezervacijaOD;
    Datum _rezervacijaDO;
    double _cijenaPoDanu; //cijena osnovnih usluga koja ne ukljucuje dodatne usluge
    Kolekcija<Usluga> _dodatneUsluge; //dodatne usluge mogu biti: sauna, sportski tereni, kuglanje, masaza i sl. 
public:
    //implementirati potrebne funkcije
    Rezervacija(const Datum& rezervacijaOD, const Datum& rezervacijaDO, const double cijenaPoDanu)
        : _rezervacijaID{ _rezervacijeIDBrojac++ }
        , _rezervacijaDO { rezervacijaDO }
        , _rezervacijaOD { rezervacijaOD }
        , _cijenaPoDanu { cijenaPoDanu }
    {}

    Rezervacija(const Rezervacija& rezervacija)
        : _rezervacijaID { _rezervacijeIDBrojac++ }
        , _rezervacijaDO { rezervacija.getRezervacijaDO() }
        , _rezervacijaOD { rezervacija.getRezervacijaOD() }
        , _cijenaPoDanu { rezervacija.getCijenaPoDanu() }
        , _dodatneUsluge { rezervacija.getDodatneUsluge() }
    {}

    Rezervacija& operator=(const Rezervacija& rhs) {
        _rezervacijaDO = rhs.getRezervacijaDO();
        _rezervacijaOD = rhs.getRezervacijaOD();
        _cijenaPoDanu = rhs.getCijenaPoDanu();
        _dodatneUsluge = rhs.getDodatneUsluge();

        return *this;
    }

    [[nodiscard]] int getRezervacijaID() const noexcept {
        return _rezervacijaID;
    }

    [[nodiscard]] const Datum& getRezervacijaOD() const noexcept {
        return _rezervacijaOD;
    }

    [[nodiscard]] const Datum& getRezervacijaDO() const noexcept {
        return _rezervacijaDO;
    }

    [[nodiscard]] double getCijenaPoDanu() const noexcept {
        return _cijenaPoDanu;
    }

    [[nodiscard]] const Kolekcija<Usluga>& getDodatneUsluge() const noexcept {
        return _dodatneUsluge;
    }

    [[noidscard]] bool daLiUslugaPostoji(const Usluga& usluga) const noexcept {
        for (int i = 0; i < _dodatneUsluge.getTrenutno(); ++i) {
            if (_dodatneUsluge.getElement(i) == usluga) {
                return true;
            }
        }

        return false;
    }

    bool operator+=(const Usluga& usluga) {
        if (daLiUslugaPostoji(usluga)) {
            return false;
        }

        _dodatneUsluge.Add(usluga);
        return true;
    }

    [[nodiscard]] double getCijenaDodatnihUslugaUkupno() const noexcept {
        double sum{ 0.0 };

        for (int i = 0; i < _dodatneUsluge.getTrenutno(); ++i) {
            sum += _dodatneUsluge.getElement(i).getCijena();
        }

        return sum;
    }

    [[nodiscard]] int64_t getBrojDanaTrajanjaRezervacije() const noexcept {
        int64_t brojDana{ getRezervacijaDO() - getRezervacijaOD() };
        return (brojDana < 0) ? 0 : brojDana;
    }

    [[nodiscard]] double getCijenaDodatneUslugeZaVrijemeCitaveRezervacije() const noexcept {
        return getCijenaDodatnihUslugaUkupno() * getBrojDanaTrajanjaRezervacije();
    }

    [[nodiscard]] double getCijenaOsnovneUslugeZaVrijemeCitaveRezervacije() const noexcept {
        return getCijenaPoDanu() * getBrojDanaTrajanjaRezervacije();
    }

    void PrintRacun() const {
        if (getBrojDanaTrajanjaRezervacije() > 30) {
            std::cout << "Rezervacija istekla, rezervacija traje maksimalno 30 dana\n";
            return;
        }

        std::cout << crt;
        std::cout << "R.ID: " << getRezervacijaID() << '\n';
        std::cout << "OD: " << getRezervacijaOD() << '\n';
        std::cout << "DO: " << getRezervacijaDO();
        std::cout << crt;
        std::cout << "DODATNE USLUGE:";
        std::cout << crt;
        std::cout << getDodatneUsluge();
        std::cout << crt;
        std::cout << "Osnovne usluge-> " << getCijenaOsnovneUslugeZaVrijemeCitaveRezervacije() << " KM";
        std::cout << crt;
        std::cout << "Dodatne usluge-> " << getCijenaDodatneUslugeZaVrijemeCitaveRezervacije() << " KM";
        std::cout << crt;
        std::cout << "Ukupno -> ";
        std::cout << getCijenaOsnovneUslugeZaVrijemeCitaveRezervacije() + getCijenaDodatneUslugeZaVrijemeCitaveRezervacije();
        std::cout << " KM";
        std::cout << crt;
    }

    [[nodiscard]] Usluga* operator[](const std::string& usluga) {
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); ++i) {
            if (_dodatneUsluge.getElement(i).getNaziv() == usluga) {
                return &_dodatneUsluge.getElement(i);
            }
        }

        return nullptr;
    }


    Kolekcija<Usluga> operator()(const double startCijena, const int endCijena) {
        Kolekcija<Usluga> temp{};

        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); ++i) {
            const double trenutnaCijena{ _dodatneUsluge.getElement(i).getCijena() };
            if (trenutnaCijena >= startCijena && trenutnaCijena <= endCijena) {
                temp.Add(_dodatneUsluge.getElement(i));
            }
        }

        return temp;
    }
};

int Rezervacija::_rezervacijeIDBrojac{ 160000 };

void main() {
    cout << crt << "TRAJANJE ISPITA -> 90 minuta " << crt;
    Kolekcija<int> brojevi;
    for (int i = 0; i < 15; i++)
        brojevi.Add(i);
    cout << brojevi << crt;

    //u okviru klase Usluga implementirati MOVE konstruktor
    Usluga Parking("Parking", 5), Dorucak("Dorucak", 10), Rucak("Rucak", 15), Veseraj("Veseraj", 10);

    //rezervacijaOD, rezervacijaDO, cijenaPoDanu
    Rezervacija rezervacija(Datum(25, 10, 2018), Datum(30, 10, 2018), 59.9);

    //dodaje novu uslugu u rezervaciju. onemoguciti ponavljanje usluga
    if (rezervacija += Parking)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Dorucak)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Rucak)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Veseraj)
        cout << "Usluga uspjesno dodana!" << endl;
    if (!(rezervacija += Dorucak))
        cout << "Usluga vec postoji!" << endl;

    /*prikazuje racun formatiran na nacin prikazan na slici. prilikom izracunavanja iznosa koristiti cijene osnovnih i dodatnih usluga, kao i broj dana za koje je napravljena rezervacija (napomena: duzina trajanja rezervacije je maksimalno 30 dana)*/
    rezervacija.PrintRacun();

    //vraca pokazivac na uslugu sa proslijedjenim nazivom
    Usluga* p = rezervacija["Dorucak"];
    if (p != nullptr)
        cout << *p << crt;

    //vraca sve dodatne usluge koje imaju cijenu u opsegu vrijednosti parametara
    Kolekcija<Usluga> uslugePoCijeni = rezervacija(8, 12);
    for (size_t i = 0; i < uslugePoCijeni.GetTrenutno(); i++)
        cout << uslugePoCijeni[i] << crt;

    cin.get();
}

/*
------------------------------------
R.ID: 160000
OD: 25 10 2018
DO: 30 10 2018
------------------------------------
DODATNE USLUGE:
------------------------------------
Parking -> 5 KM
Dorucak -> 10 KM
Rucak -> 15 KM
Veseraj -> 10 KM
------------------------------------
Osnovne usluge-> 299.5 KM
------------------------------------
Dodatne usluge-> 200 KM
------------------------------------
Ukupno -> 499.5 KM
------------------------------------
*/