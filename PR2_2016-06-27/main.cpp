#include <iostream>

using namespace std;

// Headers I included below

#include<string>
#include<iomanip>
#include<sstream>

// Headers I included above

const char* const crt = "\n----------------------------------------------------\n";

// Functions I defined below

[[nodiscard]] std::string GenerisiSljedeciBrojRacuna() noexcept {
    // Example: RN000001
    std::ostringstream brojRacunaBuffer{};
    static int currentNum{ 1 };

    brojRacunaBuffer << "RN" << std::setw(6) << std::setfill('0') << currentNum;
    ++currentNum;

    return brojRacunaBuffer.str();
}

[[nodiscard]] char* getCStrCopy(const char* const str) {
    if (!str) {
        return nullptr;
    }

    const std::size_t newSize{ std::strlen(str) + 1 };
    char* const newStr{ new char[newSize] {} };

    strcpy_s(newStr, newSize, str);

    return newStr;
}

// Functions I defined above

template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1;
    T2* _elementi2;
    int* _trenutno;
public:
    Kolekcija()
    {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = new int(0);
    }
    //1. potrebne funkcije	
    ~Kolekcija()
    {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }

    [[nodiscard]] int getTrenutno() const noexcept {
        return *_trenutno;
    }

    [[nodiscard]] const T1& getElement1(const std::size_t index) const noexcept {
        return _elementi1[index];
    }
    
    [[nodiscard]] const T2& getElement2(const std::size_t index) const noexcept {
        return _elementi2[index];
    }
    
    [[nodiscard]] T1& getElement1(const std::size_t index) noexcept {
        return _elementi1[index];
    }

    [[nodiscard]] T2& getElement2(const std::size_t index) noexcept {
        return _elementi2[index];
    }

    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno{ new int { kolekcija.getTrenutno() } }
        , _elementi1{ new T1[kolekcija.getTrenutno()] {} }
        , _elementi2{ new T2[kolekcija.getTrenutno()] {} }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = kolekcija.getElement1(i);
            _elementi2[i] = kolekcija.getElement2(i);
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        *_trenutno = rhs.getTrenutno();

        T1* const tempElement1{ new T1[getTrenutno()] {} };
        T2* const tempElement2{ new T2[getTrenutno()] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            tempElement1[i] = rhs.getElement1(i);
            tempElement2[i] = rhs.getElement2(i);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        return *this;
    }

    Kolekcija& operator=(Kolekcija&& rhs) noexcept {
        int* const tempTrenutno{ std::exchange(rhs._trenutno, new int {0}) };
        T1* const tempElement1{ std::exchange(rhs._elementi1, nullptr) };
        T2* const tempElement2{ std::exchange(rhs._elementi2, nullptr) };

        delete _trenutno;
        delete[] _elementi1;
        delete[] _elementi2;

        _trenutno = tempTrenutno;
        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        return *this;
    }

    void AddElement(const T1& element1, const T2& element2) {
        T1* const tempElement1{ new T1[getTrenutno() + 1] {} };
        T2* const tempElement2{ new T2[getTrenutno() + 1] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            tempElement1[i] = getElement1(i);
            tempElement2[i] = getElement2(i);
        }

        tempElement1[getTrenutno()] = element1;
        tempElement2[getTrenutno()] = element2;

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        ++(*_trenutno);
    }

    friend std::ostream& operator<<(std::ostream& os, const Kolekcija& kolekcija) {
        os << crt;

        for (int i = 0; i < kolekcija.getTrenutno(); ++i) {
            os << kolekcija.getElement1(i) << ' ' << kolekcija.getElement2(i);

            if (i + 1 != kolekcija.getTrenutno()) {
                os << '\n';
            }
        }

        os << crt;

        return os;
    }
};
class Datum
{
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000)
    {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    ~Datum()
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj)
    {
        COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
        return COUT;
    }
    //1. potrebne funkcije
    [[nodiscard]] int getDan() const noexcept {
        return *_dan;
    }

    [[nodiscard]] int getMjesec() const noexcept {
        return *_mjesec;
    }

    [[nodiscard]] int getGodina() const noexcept {
        return *_godina;
    }

    Datum(const Datum& datum)
        : _dan { new int { datum.getDan() } }
        , _mjesec{ new int { datum.getMjesec() } }
        , _godina { new int { datum.getGodina() } }
    {}

    Datum& operator=(const Datum& rhs) {
        int* const tempDan{ new int { rhs.getDan() } };
        int* const tempMjesec{ new int { rhs.getMjesec() } };
        int* const tempGodina{ new int { rhs.getGodina() } };

        delete _dan;
        delete _mjesec; 
        delete _godina;

        _dan = tempDan;
        _mjesec = tempMjesec;
        _godina = tempGodina;

        return *this;
    }

    Datum& operator=(Datum&& rhs) noexcept {
        int* const tempDan{ std::exchange(rhs._dan, new int { 1 }) };
        int* const tempMjesec{ std::exchange(rhs._mjesec, new int { 1 }) };
        int* const tempGodina{ std::exchange(rhs._godina, new int { 2000 }) };

        delete _dan;
        delete _mjesec;
        delete _godina;

        _dan = tempDan;
        _mjesec = tempMjesec;
        _godina = tempGodina;

        return *this;
    }
};
class Osoba
{
protected:
    char* _imePrezime;
    Datum* _datumRodjenja;
public:
    Osoba(const char* const imePrezime, Datum datum)
    {
        _imePrezime = new char[strlen(imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
        _datumRodjenja = new Datum(datum);
    }
    Osoba(const Osoba& obj)
    {
        _imePrezime = new char[strlen(obj._imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
        _datumRodjenja = new Datum(*obj._datumRodjenja);
    }
    virtual ~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }
    //1. potrebne funkcije

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] const Datum& getDatumRodjenja() const noexcept {
        return *_datumRodjenja;
    }

    Osoba& operator=(const Osoba& rhs) {
        char* const tempImePrezime{ getCStrCopy(rhs.getImePrezime()) };
        Datum tempDatum{ rhs.getDatumRodjenja() };

        delete[] _imePrezime;

        _imePrezime = tempImePrezime;
        *_datumRodjenja = std::move(tempDatum);

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Osoba& osoba) {
        os << "Ime prezime: " << osoba.getImePrezime() << '\n';
        os << "Datum rodjenja: " << osoba.getDatumRodjenja();

        return os;
    }
};


class Kupac : public Osoba
{
    //svaki kupac ima popust koji mu se zaracunava prilikom svake kupovine
    //pocetni popust je 0.10%
    //svaka kupovina u iznosu 100 - 500KM povecava iznos popusta za 0.15%
    //svaka kupovina u iznosu 500 - 1000KM povecava iznos popusta za 0.25%
    //svaka kupovina u iznosu vecem od 1000KM povecava iznos popusta za 0.30%
    float _odobreniPopust{ 0.10f };
public:
    //1. potrebne funkcije
    [[nodiscard]] float getOdobreniPopusti() const noexcept {
        return _odobreniPopust;
    }

    Kupac(const char* const imePrezime, Datum datum)
        : Osoba(imePrezime, datum)
    {}

    Kupac(const Kupac& kupac) 
        : Osoba(kupac)
        , _odobreniPopust { kupac.getOdobreniPopusti() }
    {}

    Kupac& operator=(const Kupac& rhs) {
        Osoba::operator=(rhs);

        _odobreniPopust = rhs.getOdobreniPopusti();

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kupac& kupac) {
        os << static_cast<const Osoba&>(kupac) << '\n';
        os << "Odobreni popust: " << kupac.getOdobreniPopusti();

        return os;
    }
    
    void povecajOdobreniPopust(const double cijenaKupovine) {
        if (cijenaKupovine > 1000) {
            _odobreniPopust += 0.30;
        }
        else if (cijenaKupovine >= 500) {
            _odobreniPopust += 0.25;
        }
        else if(cijenaKupovine >= 100) {
            _odobreniPopust += 0.15;
        }
    }
};
class Artikal
{
    string _barCode;
    char* _naziv;
    float _cijena;
public:
    Artikal(const char* const naziv, float cijena, string barCode)
    {
        int vel = strlen(naziv) + 1;
        _naziv = new char[vel];
        strcpy_s(_naziv, vel, naziv);
        _cijena = cijena;
        _barCode = barCode;
    }
    ~Artikal() { delete[]_naziv; _naziv = nullptr; }
    friend ostream& operator<< (ostream& COUT, const Artikal& obj)
    {
        COUT << obj._naziv << " " << obj._cijena << " KM" << endl;
        return COUT;
    }
    //1. potrebne funkcije
    [[nodiscard]] const std::string getBarCode() const noexcept {
        return _barCode;
    }

    [[nodiscard]] const char* getNaziv() const noexcept {
        return _naziv;
    }

    [[nodiscard]] float getCijena() const noexcept {
        return _cijena;
    }

    Artikal(const Artikal& artikal)
        : _barCode { artikal.getBarCode() }
        , _naziv { getCStrCopy(artikal.getNaziv()) }
        , _cijena { artikal.getCijena() }
    {}

    Artikal& operator=(const Artikal& rhs) {
        _cijena = rhs.getCijena();

        std::string tempBarCode{ rhs.getBarCode() };
        char* const tempNaziv{ getCStrCopy(rhs.getNaziv()) };

        delete[] _naziv;

        _barCode = std::move(tempBarCode);
        _naziv = tempNaziv;

        return *this;
    }

    [[nodiscard]] bool operator==(const Artikal& rhs) const noexcept {
        return getBarCode() == rhs.getBarCode()
            && !std::strcmp(getNaziv(), rhs.getNaziv())
            && getCijena() == rhs.getCijena();
    }
};
class Racun
{
    //format broja racuna: RN6005491
    //osigurati automatsko generisanje broja racuna pocevsi od RN0000001
    char _brojRacuna[10];
    Datum _datumKreiranja;
    //prvi argument je Artikal, a drugi kolicina/broj artikala koju je kupac uzeo
    Kolekcija<Artikal*, int>* _stavkeRacuna{ new Kolekcija<Artikal*, int> {} };
    Kupac* _kupac;
public:
    // 1. potrebne (de)konstruktor i druge funkcije
    // 2. DodajArtikal - dodaje novi artikal u listu artikala zajedno sa njegovom kolicinom. Onemoguciti ponavljanje 
    //    artikala na nacin da se uvecava samo kolicina ukoliko korisnik vise puta pokusa dodati isti artikal.
    // 3. operator<< - ispisuje racun u formatu prikazanom na slici(nije obavezno da bude identican, ali je svakako pozeljno).
    //    Nakon ispisa svakog racuna, ukoliko su ispunjeni definisani uslovi, kupcu se uvecava popust.
    // 4. Sortiraj - sortira artikle (rastuci) po kolicini novca kojom ucestvuju u ukupnom iznosu racuna

    // Methods I added below

    void Sortiraj() {
        bool continueSorting{};
        int size{ _stavkeRacuna->getTrenutno() };

        do {
            continueSorting = false;

            for (int i = 0; i < size - 1; ++i) {
                const double ukupniIznos1{ _stavkeRacuna->getElement1(i)->getCijena() * _stavkeRacuna->getElement2(i) };
                const double ukupniIznos2{ _stavkeRacuna->getElement1(i + 1)->getCijena() * _stavkeRacuna->getElement2(i + 1) };

                if (ukupniIznos1 > ukupniIznos2) {
                    std::swap(_stavkeRacuna->getElement1(i), _stavkeRacuna->getElement1(i + 1));
                    std::swap(_stavkeRacuna->getElement2(i), _stavkeRacuna->getElement2(i + 1));

                    continueSorting = true;
                }
            }

            --size;
        } while (continueSorting);
    }

    [[nodiscard]] const char* getBrojRacuna() const noexcept {
        return _brojRacuna;
    }

    [[nodiscard]] const Datum& getDatumKreiranja() const noexcept {
        return _datumKreiranja;
    }

    [[nodiscard]] const Kolekcija<Artikal*, int>& getStavkeRacuna() const noexcept {
        return *_stavkeRacuna;
    }

    [[nodiscard]] const Kupac& getKupac() const noexcept {
        return *_kupac;
    }

    [[nodiscard]] char* getBrojRacuna() noexcept {
        return _brojRacuna;
    }

    [[nodiscard]] Datum& getDatumKreiranja() noexcept {
        return _datumKreiranja;
    }

    [[nodiscard]] Kolekcija<Artikal*, int>& getStavkeRacuna() noexcept {
        return *_stavkeRacuna;
    }

    [[nodiscard]] Kupac& getKupac() noexcept {
        return *_kupac;
    }

    Racun(const std::string& brojRacuna, const Datum& datumKreiranja, Kupac* const kupac)
        : _datumKreiranja{ datumKreiranja }
        , _kupac{ kupac }
    {
        strcpy_s(_brojRacuna, std::size(_brojRacuna), brojRacuna.c_str());
    }

    ~Racun() {
        for (int i = 0; i < _stavkeRacuna->getTrenutno(); ++i) {
            delete _stavkeRacuna->getElement1(i);
        }
        delete _stavkeRacuna;
    }

    Racun(Racun& racun) 
        : _datumKreiranja{ racun.getDatumKreiranja() }
        , _kupac{ &racun.getKupac() }
    {
        strcpy_s(_brojRacuna, std::size(_brojRacuna), racun.getBrojRacuna());

        const auto& stavkeRacuna{ racun.getStavkeRacuna() };

        for (int i = 0; i < stavkeRacuna.getTrenutno(); ++i) {
            _stavkeRacuna->AddElement(
                new Artikal{ *stavkeRacuna.getElement1(i) },
                stavkeRacuna.getElement2(i)
            );
        }
    }

    Racun& operator=(Racun& rhs) {
        Kupac* tempKupac{ &rhs.getKupac() };
        Datum tempDatumKreiranja{ rhs.getDatumKreiranja() };
        
        char tempBrojRacuna[10]{};
        strcpy_s(tempBrojRacuna, std::size(tempBrojRacuna), rhs.getBrojRacuna());

        Kolekcija<Artikal*, int> tempStavkeRacuna{};
        
        const auto& stavkeRacuna{ rhs.getStavkeRacuna() };

        for (int i = 0; i < stavkeRacuna.getTrenutno(); ++i) {
            tempStavkeRacuna.AddElement(
                new Artikal{ *stavkeRacuna.getElement1(i) },
                stavkeRacuna.getElement2(i)
            );
        }

        _kupac = tempKupac;
        _datumKreiranja = std::move(tempDatumKreiranja);
        strcpy_s(_brojRacuna, std::size(_brojRacuna), tempBrojRacuna);
        *_stavkeRacuna = std::move(tempStavkeRacuna);

        return *this;
    }

    [[nodiscard]] int getIndexArtiklaAkoPostoji(const Artikal& artikal) const noexcept {
        for (int i = 0; i < _stavkeRacuna->getTrenutno(); ++i) {
            if (*_stavkeRacuna->getElement1(i) == artikal) {
                return i;
            }
        }

        return -1;
    }

    void DodajArtikal(const Artikal& artikal, const int kolicina) {
        const auto& indexPostojecegArtikla{ getIndexArtiklaAkoPostoji(artikal) };

        if (indexPostojecegArtikla != -1) {
            _stavkeRacuna->getElement2(indexPostojecegArtikla) += kolicina;
            return;
        }

        _stavkeRacuna->AddElement(new Artikal{ artikal }, kolicina);
    }

    // Format ispisa
    /*
    FITStore::Racun::RN000001
    | RB Artikal Cijena Kolicina Ukupno |
    | 1. Milka Milkins 2.55 15 38.25 |
    | 2. Cappy narandza 2.1 20 42 |
    | 3. Meggle jogurt 2.55 20 51 |
    | Suma:131.25KM
    | Popust : 0.1KM
    | Za platiti : 131.15KM
    */

    friend std::ostream& operator<<(std::ostream& os, Racun& racun) {
        os << "FITStore::Racun::" << racun.getBrojRacuna() << '\n';
        os << "| RB Artikal Cijena Kolicina Ukupno |\n";

        const auto& stavkeRacuna{ racun.getStavkeRacuna() };
        double sum{ 0.0 };

        for (int i = 0; i < stavkeRacuna.getTrenutno(); ++i) {
            const auto& artikal{ *stavkeRacuna.getElement1(i) };
            const double ukupnaCijena{ artikal.getCijena() * stavkeRacuna.getElement2(i) };

            os << "| " << i + 1 << ". " << artikal.getNaziv() << ' ';
            os << artikal.getCijena() << ' ' << stavkeRacuna.getElement2(i);
            os << ' ' << ukupnaCijena << " |\n";

            sum += ukupnaCijena;
        }

        const double popust { racun.getKupac().getOdobreniPopusti() };
        const double cijenaKupovine{ sum - popust };

        os << "| Suma:" << sum << "KM\n";
        os << "| Popust : " << popust <<"KM" << '\n';
        os << "| Za platiti : " << cijenaKupovine << "KM";

        racun.getKupac().povecajOdobreniPopust(cijenaKupovine);

        return os;
    }
};
void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
    //    RUNTIME ERROR CE BITI OZNACENO KAO "RE"
    // 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
    // 5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
    // 6. NIJE POTREBNO BACATI IZUZETKE.
    ****************************************************************************/
#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeKolekcije
    Kolekcija<int, int> kolekcija1;
    int brojElemenata = 15;
    for (size_t i = 0; i < brojElemenata; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1.getElement1(0) << " " << kolekcija1.getElement2(0) << endl;
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;

    cout << kolekcija2 << crt;
    if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;

    Kolekcija<int, int> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeKupca
    Kupac jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
    Kupac adel("Adel Handzic", Datum(15, 10, 1981));

    Kupac jasmin2 = jasmin;
    cout << jasmin << endl << jasmin2 << endl;
    jasmin = jasmin2;
    cout << jasmin << endl << jasmin2 << endl;
#pragma endregion

#pragma region TestiranjeArtikla
    Artikal sokCppyNarandza("Cappy narandza", 2.10, "699511236545");
    Artikal cokoladaMilkaMilkins("Milka Milkins", 2.55, "622445875463");
    Artikal jogurtMeggle("Meggle jogurt", 2.55, "155338774458");

    cout << sokCppyNarandza << cokoladaMilkaMilkins << jogurtMeggle << endl;
    sokCppyNarandza = cokoladaMilkaMilkins;
    cout << sokCppyNarandza << endl;

    if (sokCppyNarandza == cokoladaMilkaMilkins)
        cout << "Artikli su isti" << endl;
#pragma endregion

#pragma region TestiranjeRacuna
    /*GenerisiSljedeciBrojRacuna - globalna funkcija koja generise i vraca naredni broj racuna u
    prethodno definisanom formatu*/
    Racun racun1(GenerisiSljedeciBrojRacuna(), danas, &jasmin);

    racun1.DodajArtikal(cokoladaMilkaMilkins, 15);
    racun1.DodajArtikal(sokCppyNarandza, 20);
    racun1.DodajArtikal(jogurtMeggle, 20);

    cout << racun1 << endl;

    Racun racun2(GenerisiSljedeciBrojRacuna(), sutra, &jasmin);
    racun2.DodajArtikal(cokoladaMilkaMilkins, 15);
    racun2.DodajArtikal(sokCppyNarandza, 20);
    racun2.DodajArtikal(jogurtMeggle, 20);
    cout << racun2 << endl;

    Racun racun3(racun2);
    cout << racun3 << endl;
    racun3.Sortiraj();

#pragma endregion

    system("pause");
}
//popust mozete izracunati kao procenat od ukupne sume racuna (pozeljna opcija) 
//ili kao vrijednost u KM-ovima (kao u nastavku)
/*
FITStore::Racun::RN000001
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.1KM
| Za platiti : 131.15KM


FITStore::Racun::RN000002
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.25KM
| Za platiti : 131KM


FITStore::Racun::RN000002
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.4KM
| Za platiti : 130.85KM
*/