#include <iostream>
using namespace std;

// Headers I included below
#include<vector>
#include<array>
#include<numeric>
#include<thread>
#include<string>
#include<regex>
#include<chrono>
#include<iomanip>
// Headers I included above

const char* PORUKA = "\n-----------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. METODE KOJE NISU VOID, MORAJU VRACATI NEKU VRIJEDNOST!\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12. ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022!\n"
"13. RJESENJE TESTIRAJTE U OBA MODA (F5 i Ctrl+F5)\n"
"------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
const int MaxBrojRjesenja = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

// Functions I defined below
std::ostream& operator<<(std::ostream& os, const Predmet& predmet) {
    switch (predmet) {
    case Predmet::UIT:
        os << "UIT";
        break;
    case Predmet::PRI:
        os << "PRI";
        break;
    case Predmet::PRII:
        os << "PRII";
        break;
    case Predmet::PRIII:
        os << "PRIII";
        break;
    case Predmet::RSI:
        os << "RSI";
        break;
    case Predmet::RSII:
        os << "RSII";
        break;
    default:
        os << "Predmet ne postoji";
    }

    return os;
}
/*
za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
-   najmanje 7 znakova
-   velika i mala slova
-   najmanje jedan broj
-   najmanje jedan specijalni znak

za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
*/
[[nodiscard]] bool ValidirajLozinku(const std::string& password) {
    if (password.size() < 7) {
        return false;
    }

    std::regex uppercaseValidation{ "[A-Z]" };
    std::regex lowercaseValidation{ "[a-z]" };
    std::regex numberValidation{ "\\d" };
    std::regex specialCharValidation{ "\\W" };

    return std::regex_search(password, uppercaseValidation)
        && std::regex_search(password, lowercaseValidation)
        && std::regex_search(password, numberValidation)
        && std::regex_search(password, specialCharValidation);
}
// Functions I defined above

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2, int max = 10>
class Kolekcija {
    T1* _elementi1[max]{ nullptr };
    T2* _elementi2[max]{ nullptr };
    int* _trenutno;
public:
    Kolekcija() {
        _trenutno = new int{ 0 };
    }
    ~Kolekcija() {
        for (size_t i = 0; i < getTrenutno(); i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below
    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno{ new int { kolekcija.getTrenutno() } }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = new T1{ kolekcija.getElement1(i) };
            _elementi2[i] = new T2{ kolekcija.getElement2(i) };
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        if (this == &rhs) return *this;

        for (int i = 0; i < getTrenutno(); ++i) {
            delete _elementi1[i];
            delete _elementi2[i];
        }

        *_trenutno = rhs.getTrenutno();

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = new T1{ rhs.getElement1(i) };
            _elementi2[i] = new T2{ rhs.getElement2(i) };
        }

        return *this;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (getTrenutno() == max) {
            throw std::runtime_error("Maximalni broj elemenata dostignut");
        }

        _elementi1[getTrenutno()] = new T1{ element1 };
        _elementi2[getTrenutno()] = new T2{ element2 };

        ++(*_trenutno);
    }

    void AddElement(const T1& element1, const T2& element2, const int index) {
        if (getTrenutno() == max) {
            throw std::runtime_error("Maximalni broj elemenata dostignut");
        }
        else if (index < 0 || index >= getTrenutno()) {
            return;
        }

        for (int i = getTrenutno(); i > index; --i) {
            _elementi1[i] = _elementi1[i - 1];
            _elementi2[i] = _elementi2[i - 1];
        }

        _elementi1[index] = new T1{ element1 };
        _elementi2[index] = new T2{ element2 };

        ++(*_trenutno);
    }

    T2& operator[](const T1& element1) noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1) {
                return getElement2(i);
            }
        }
    }

    Kolekcija* operator()(const int start, const int end) {
        Kolekcija* temp{ new Kolekcija {} };
        
        if (start < 0 || start >= getTrenutno()) {
            return temp;
        } else if (end < 0 || end >= getTrenutno()) {
            return temp;
        }

        for (int i = start; i <= end; ++i) {
            temp->AddElement(getElement1(i), getElement2(i));
        }

        return temp;
    }
};
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int{ dan };
        _mjesec = new int{ mjesec };
        _godina = new int{ godina };
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << obj.getDan() << "." << obj.getMjesec() << "." << obj.getGodina();
        return COUT;
    }

    // Methods I added below
    Datum(const Datum& datum)
        : _dan { new int { datum.getDan() } }
        , _mjesec{ new int { datum.getMjesec() } }
        , _godina { new int { datum.getGodina() } }
    {}

    Datum& operator=(const Datum& rhs) {
        *_dan = rhs.getDan();
        *_mjesec = rhs.getMjesec();
        *_godina = rhs.getGodina();

        return *this;
    }

    [[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
        return getDan() == rhs.getDan()
            && getMjesec() == rhs.getMjesec()
            && getGodina() == rhs.getGodina();
    }

    [[nodiscard]] bool operator!=(const Datum& rhs) const noexcept {
        return !(*this == rhs);
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

    [[nodiscard]] bool operator<=(const Datum& rhs) const noexcept {
        return getDatumAsDays() <= rhs.getDatumAsDays();
    }

    [[nodiscard]] bool operator>=(const Datum& rhs) const noexcept {
        return getDatumAsDays() >= rhs.getDatumAsDays();
    }
};
/*na odredjeno pitanje kandidat je duzan postaviti vise odgovora/rjesenja od kojih ce svako biti ocijenjeno*/
class Pitanje {
    char* _sadrzaj;
    //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
    Kolekcija<int, Datum*, MaxBrojRjesenja> _ocjeneRjesenja;
public:
    Pitanje(const char* sadrzaj = "") {
        _sadrzaj = GetNizKaraktera(sadrzaj);
    }
    ~Pitanje() {
        delete[] _sadrzaj; _sadrzaj = nullptr;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            delete _ocjeneRjesenja.getElement2(i);
        }
    }
    char* GetSadrzaj() { return _sadrzaj; }
    Kolekcija<int, Datum*, MaxBrojRjesenja> GetOcjene() const { return _ocjeneRjesenja; }

    // Methods I added below
    Pitanje(const Pitanje& pitanje)
        : _sadrzaj { GetNizKaraktera(pitanje.getSadrzaj())}
        , _ocjeneRjesenja { pitanje.getOcjeneRjesenjaCopy() }
    {}

    Pitanje& operator=(const Pitanje& rhs) {
        if (this == &rhs) return *this;

        delete[] _sadrzaj;
        
        _sadrzaj = GetNizKaraktera(rhs.getSadrzaj());
        _ocjeneRjesenja = rhs.getOcjene();

        return *this;
    }

    [[nodiscard]] bool daLiSuOcjeneIDatumiIsti(
        const Kolekcija<int, Datum*, MaxBrojRjesenja>& ocjene
    ) const noexcept {
        if (ocjene.getTrenutno() != _ocjeneRjesenja.getTrenutno()) {
            return false;
        }

        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            if (ocjene.getElement1(i) != _ocjeneRjesenja.getElement1(i)) {
                return false;
            } else if (*ocjene.getElement2(i) != *_ocjeneRjesenja.getElement2(i)) {
                return false;
            }

        }

        return true;
    }

    [[nodiscard]] bool operator==(const Pitanje& rhs) const noexcept {
        return !std::strcmp(getSadrzaj(), rhs.getSadrzaj())
            && daLiSuOcjeneIDatumiIsti(rhs.getOcjene());
    }

    [[nodiscard]] const char* getSadrzaj() const noexcept { 
        return _sadrzaj; 
    }

    [[nodiscard]] bool daLiImaOcjenaUIntervalu(const Datum& pocetak, const Datum& kraj) const noexcept {
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            const Datum& trenutniDatum{ *_ocjeneRjesenja.getElement2(i) };
            
            if (trenutniDatum >= pocetak && trenutniDatum <= kraj) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] float getAverageTimeBetweenGrades() const noexcept {
        const int size{ _ocjeneRjesenja.getTrenutno() };

        if (!size) {
            return 0.0f;
        }

        float sum{ 0.0f };

        for (int i = 0; i < size - 1; ++i) {
            const Datum& datum1{ *_ocjeneRjesenja.getElement2(i) };
            const Datum& datum2{ *_ocjeneRjesenja.getElement2(i + 1) };

            sum += std::abs(datum1 - datum2);
        }

        return sum / size;
    }

    [[nodiscard]] const Kolekcija<int, Datum*, MaxBrojRjesenja>& getOcjene() const noexcept { 
        return _ocjeneRjesenja; 
    }

    [[nodiscard]] Kolekcija<int, Datum*, MaxBrojRjesenja> getOcjeneRjesenjaCopy() const noexcept {
        Kolekcija<int, Datum*, MaxBrojRjesenja> temp{};

        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            temp.AddElement(
                _ocjeneRjesenja.getElement1(i),
                new Datum { *_ocjeneRjesenja.getElement2(i) }
            );
        }

        return temp;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _ocjeneRjesenja.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _ocjeneRjesenja.getElement1(i);
        }

        return sum / size;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pitanje& pitanje) {
        os << "Sadrzaj pitanja: " << std::quoted(pitanje.getSadrzaj()) << '\n';
        os << "Ocjene - datum:\n";

        const auto& ocjene{ pitanje.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - ";
            os << *ocjene.getElement2(i) << '\n';
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjecna ocjena: " << pitanje.getAverage() << '\n';

        os << std::setprecision(originalPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 5;
    }

    [[nodiscard]] bool daLiJeDatumValidan(const Datum& datumOcjene) {
        const int size{ _ocjeneRjesenja.getTrenutno() };

        if (!size) {
            return true;
        }

        const auto& zadnjiDatum{ *_ocjeneRjesenja.getElement2(size - 1) };

        return (datumOcjene - zadnjiDatum) >= 3;
    }

    bool AddOcjena(const Datum& datumOcjene, const int ocjena) {
        if (!daLiJeOcjenaValidna(ocjena)) {
            return false;
        }
        else if (!daLiJeDatumValidan(datumOcjene)) {
            return false;
        }

        _ocjeneRjesenja.AddElement(ocjena, new Datum{ datumOcjene });
        return true;
    }
};
class Ispit {
    Predmet* _predmet;
    vector<Pitanje> _pitanjaOdgovori;
public:
    Ispit(Predmet predmet = UIT) {
        _predmet = new Predmet{ predmet };
    }
    ~Ispit() {
        delete _predmet; _predmet = nullptr;
    }
    vector<Pitanje>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
    Predmet GetPredmet() { return *_predmet; }
    friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
        COUT << *obj._predmet << endl;
        for (size_t i = 0; i < obj._pitanjaOdgovori.size(); i++)
            COUT << obj._pitanjaOdgovori[i];
        return COUT;
    }

    // Methods I added below
    Ispit(const Predmet& predmet, const Pitanje& pitanje)
        : _predmet{ new Predmet { predmet } }
    {
        _pitanjaOdgovori.push_back(pitanje);
    }

    Ispit(const Ispit& ispit) 
        : _predmet { new Predmet { ispit.getPredmet() } }
        , _pitanjaOdgovori{ ispit.getPitanjaOdgovore() }
    {}

    Ispit& operator=(const Ispit& rhs) {
        *_predmet = rhs.getPredmet();
        std::vector<Pitanje> tempPitanja{ rhs.getPitanjaOdgovore() };

        _pitanjaOdgovori = std::move(tempPitanja);

        return *this;
    }

    [[nodiscard]] const std::vector<Pitanje>& getPitanjaOdgovore() const noexcept { 
        return _pitanjaOdgovori; 
    }

    [[nodiscard]] const Predmet& getPredmet() const noexcept { 
        return *_predmet; 
    }

    [[nodiscard]] std::size_t getBrojPredmeta() const noexcept {
        return _pitanjaOdgovori.size();
    }

    [[nodiscard]] double getAverage() const noexcept {
        const auto& size{ _pitanjaOdgovori.size() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (const auto& pitanje : _pitanjaOdgovori) {
            sum += pitanje.getAverage();
        }

        return sum / size;
    }

    [[nodiscard]] bool daLiPitanjePostoji(const Pitanje& pitanje) const noexcept {
        auto pitanjeZaPronaci{
            std::find(std::begin(_pitanjaOdgovori), std::end(_pitanjaOdgovori), pitanje)
        };

        return pitanjeZaPronaci != std::end(_pitanjaOdgovori);
     }
    void dodajPitanje(const Pitanje& pitanje) {
        _pitanjaOdgovori.push_back(pitanje);
    }
};

class Korisnik {
protected:
    char* _imePrezime;
    string _emailAdresa;
    string _lozinka;
    bool _aktivan;
public:
    Korisnik(const char* imePrezime, string emailAdresa, string lozinka)
    {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
        _aktivan = true;
    }
    virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    char* GetImePrezime() { return _imePrezime; }
    bool GetAktivan() { return _aktivan; }
    void SetAktivan(bool aktivan) { _aktivan = aktivan; }
    virtual void Info() = 0;

    // Methods I added below
    Korisnik(const Korisnik& korisnik)
        : _imePrezime { GetNizKaraktera(korisnik.getImePrezime()) }
        , _emailAdresa { korisnik.getEmail() }
        , _lozinka { korisnik.getLozinka() }
        , _aktivan { korisnik.getAktivan() }
    {}

    Korisnik& operator=(const Korisnik& rhs) {
        _aktivan = rhs.getAktivan();

        char* const tempImePrezime{ GetNizKaraktera(rhs.getImePrezime()) };
        std::string tempEmail{ rhs.getEmail() };
        std::string tempLozinka{ rhs.getLozinka() };

        delete[] _imePrezime;

        _imePrezime = tempImePrezime;
        _emailAdresa = std::move(tempEmail);
        _lozinka = std::move(tempLozinka);

        return *this;
    }

    [[nodiscard]] const std::string getEmail() const noexcept { 
        return _emailAdresa; 
    }
    
    [[nodiscard]] const std::string getLozinka() const noexcept {
        return _lozinka; 
    }

    [[nodiscard]] const char* getImePrezime() const noexcept { 
        return _imePrezime; 
    }

    [[nodiscard]] bool getAktivan() const noexcept { 
        return _aktivan; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Korisnik& korisnik) {
        os << "Ime prezime: " << std::quoted(korisnik.getImePrezime()) << '\n';
        os << "Email: " << std::quoted(korisnik.getEmail()) << '\n';
        os << "Lozinka: " << std::quoted(korisnik.getLozinka()) << '\n';
        os << "Aktivan: " << std::boolalpha << korisnik.getAktivan() << std::noboolalpha << '\n';

        return os;
    }
};
class Kandidat : public Korisnik {
    vector<Ispit*> _polozeniPredmeti;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka)
        : Korisnik(imePrezime, emailAdresa, lozinka)
    {}
    ~Kandidat() {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i], _polozeniPredmeti[i] = nullptr;
        cout << crt << "KANDIDAT :: DESTRUKTOR" << crt;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << (Korisnik&)obj << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << *obj._polozeniPredmeti[i];
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

    // Methods I added below
    Kandidat(const Kandidat& kandidat)
        : Korisnik(kandidat)
        , _polozeniPredmeti { kandidat.getPolozeniPredmeti() }
    {}

    Kandidat& operator=(const Kandidat& rhs) {
        Korisnik::operator=(rhs);

        auto tempIspiti{ rhs.getPolozeniPredmeti() };

        for (const auto& ispit : _polozeniPredmeti) {
            delete ispit;
        }
        
        _polozeniPredmeti = std::move(tempIspiti);

        return *this;
    }

    [[nodiscard]] std::vector<Ispit*> getPolozeniPredmetiCopy() const noexcept {
        std::vector<Ispit*> temp{};

        for (const auto& ispit : _polozeniPredmeti) {
            temp.push_back(new Ispit{ *ispit });
        }

        return temp;
    }

    [[nodiscard]] const std::vector<Ispit*>& getPolozeniPredmeti() const noexcept { 
        return _polozeniPredmeti; 
    }

    void Info() override {
        std::cout << *this;
    }

    [[nodiscard]] Ispit* getIspitForPredmet(const Predmet& predmet) noexcept {
        auto ispitZaPronaci{
            std::find_if(
                std::begin(_polozeniPredmeti),
                std::end(_polozeniPredmeti),
                [&](const Ispit* const ispit) {
                        return predmet == ispit->getPredmet();
                }
            )
        };

        return (ispitZaPronaci == std::end(_polozeniPredmeti)) ? nullptr : *ispitZaPronaci;
    }

    [[nodiscard]] bool daLiJeIspunjenUslovZaVisiPredmet() const noexcept {
        const auto& size{ _polozeniPredmeti.size() };

        if (!size) {
            return true;
        }

        const auto& zadnjiIspit{ _polozeniPredmeti.back() };

        return zadnjiIspit->getBrojPredmeta() >= 3 && zadnjiIspit->getAverage() > 3.5;
    }

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za viši predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    bool AddPitanje(const Predmet& predmet, const Pitanje& pitanje) {
        if (!getAktivan()) {
            return false;
        }

        auto ispit{ getIspitForPredmet(predmet) };

        if (ispit) {
            if (ispit->daLiPitanjePostoji(pitanje)) {
                return false;
            }

            ispit->dodajPitanje(pitanje);
            sendMail(*ispit);
            return true;
        }
        else if (!daLiJeIspunjenUslovZaVisiPredmet()) {
            return false;
        }

        _polozeniPredmeti.push_back(new Ispit{ predmet, pitanje });
        sendMail(*_polozeniPredmeti.back());
        return true;
    }

    [[nodiscard]] Kolekcija<Pitanje, float> operator()(const Datum& pocetak, const Datum& kraj) const noexcept {
        Kolekcija<Pitanje, float> temp{};

        for (const auto& ispit : _polozeniPredmeti) {
            const auto& pitanjaOdgovori{ ispit->getPitanjaOdgovore() };

            for (const auto& pitanjaOdgovor : pitanjaOdgovori) {
                if (pitanjaOdgovor.daLiImaOcjenaUIntervalu(pocetak, kraj)) {
                    temp.AddElement(pitanjaOdgovor, pitanjaOdgovor.getAverageTimeBetweenGrades());
                }
            }
        }

        return temp;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const auto& size{ _polozeniPredmeti.size() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (const auto& predmet : _polozeniPredmeti) {
            sum += predmet->getAverage();
        }

        return sum / size;
    }

    /*nakon evidentiranja ocjene na bilo kojem odgovoru, AKTIVNOM kandidatu se salje email sa porukom:

    FROM:info@kursevi.ba
    TO: emailKorisnika

    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.

    EDUTeam.

    slanje email poruka implemenitrati koristeci zasebne thread-ove na nacin da se jedna poruka salje svako 2 sekunde.
    */

    //osigurati da se u narednim linijama poziva i destruktor klase Kandidat
private:
    void sendMail(const Ispit& ispit) const {
        std::thread emailThread{
            [&]() {
                std::this_thread::sleep_for(2s);

                std::cout << "FROM:info@kursevi.ba\n";
                std::cout << "TO: " << getEmail() << "\n\n";
                std::cout << "Postovani " << getImePrezime() << " , evidentirana vam je pitanje za predmet " << ispit.getPredmet();
                std::cout << ".Dosadasnji uspjeh(prosjek ocjena) za pitanje iznosi " << ispit.getAverage() << ", a ukupni uspjeh";
                std::cout << "(prosjek ocjena) na svim predmetima iznosi " << getAverage() << '\n';
                std::cout << "Pozdrav.\n\nEDUTeam.\n";
            }
        };

        emailThread.join();
    }
};
//const char* GetOdgovorNaPrvoPitanje() {
//    cout << "Pitanje -> Pojasnite STACK i HEAP dio memorije, za šta su namijenjeni, te na koji način se trebaju koristiti (prednosti i nedostaci pojedinih slučajeva).\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//    cout << "Pitanje -> Pojasnite preduslove za realizaciju polimorfizma, te koje su prednosti njegovog korištenja?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
void main() {

    //cout << PORUKA;
    //cin.get();

    //cout << GetOdgovorNaPrvoPitanje() << endl;
    //cin.get();
    //cout << GetOdgovorNaDrugoPitanje() << endl;
    //cin.get();

    Datum   datum19062023(19, 6, 2023),
        datum20062023(20, 6, 2023),
        datum30062023(30, 6, 2023),
        datum05072023(5, 7, 2023);

    int kolekcijaTestSize = 10;

    Kolekcija<int, int> kolekcija1;
    for (int i = 0; i < kolekcijaTestSize - 2; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*metoda AddElement baca izuzetak u slucaju da se pokusa
        dodati vise od maksimalnog broja elemenata. Ako zelite da testirate
izuzetak, uklonite -2 iz prethodne for petlje*/
        kolekcija1.AddElement(11, 11);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    kolekcija1.AddElement(9, 9, 2);
    /*funkciji AddElement se, kao treci parametar, moze proslijediti i lokacija na koju se dodaju
    nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene za jedno mjesto unaprijed
    u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje elementi
    0 0
    1 1
    2 2
    3 3
    nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce biti sljedeci
    0 0
    9 9
    1 1
    2 2
    3 3
    */

    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2 = kolekcija1;
    cout << kolekcija1 << crt;

    //na osnovu vrijednosti T1 mijenja vrijednost T2. 
    kolekcija1[9] = 2;
    /* npr.ako unutar kolekcije postoje elementi:
    0 0
    9 9
    1 1
    2 2
    3 3
    nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
    0 0
    9 2
    1 1
    2 2
    3 3
    */

    Kolekcija<int, int>* kolekcija3 = kolekcija1(1, 3);
    /*kolekcija3 treba sadrzavati sve elemente koji se u kolekciji1 nalaze na lokacijama sa proslijedjenim indeksima,
    u ovom primjeru na lokacijama sa indeksom od 1 do 3, npr.ako unutar kolekcije1 postoje elementi:
       0 0
       9 9
       1 1
       2 2
       3 3
       sadrzaj kolekcije3 ce biti sljedeci
       9 9
       1 1
       2 2

       u slucaju da se zahtijevaju lokacije koje ne postoje u kolekciji, funkcija vraca samo one elemente koje postoje
       u zahtijevanom opsegu (bez bacanja izuzetaka).
   */
    cout << *kolekcija3 << endl;
    delete kolekcija3;

    Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza?"),
        dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom?"),
        visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa?"),
        regex("Navedite par primjera regex validacije podataka?"),
        polimorfizam("Na koji nacin se realizuje polimorfizam?");

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (sortiranjeNiza.AddOcjena(datum19062023, 1))
        cout << "Ocjena evidentirana!" << endl;
    if (!sortiranjeNiza.AddOcjena(datum20062023, 5))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (sortiranjeNiza.AddOcjena(datum30062023, 5))
        cout << "Ocjena evidentirana!" << endl;

    if (polimorfizam.AddOcjena(datum19062023, 5))
        cout << "Ocjena evidentirana!" << endl;

    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
    // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    cout << sortiranjeNiza << endl;

    if (ValidirajLozinku("john4Do*e"))
        cout << "Lozinka :: OK :)" << crt;
    if (!ValidirajLozinku("john4Doe"))
        cout << "Lozinka :: Specijalni znak?" << crt;
    if (!ValidirajLozinku("jo*4Da"))
        cout << "Lozinka :: 7 znakova?" << crt;
    if (!ValidirajLozinku("4jo-hnoe"))
        cout << "Lozinka :: Veliko slovo?" << crt;
    if (ValidirajLozinku("@john2Doe"))
        cout << "Lozinka :: OK :)" << crt;

    /*
    za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
    -   najmanje 7 znakova
    -   velika i mala slova
    -   najmanje jedan broj
    -   najmanje jedan specijalni znak

    za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    */

    Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "j@sm1N*");
    Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "4Ade1*H");
    Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za viši predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);

    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, regex))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;

        //onemoguciti dodavanje pitanja korisnicima koji nisu aktivni
        jasmin->SetAktivan(false);
        if (!jasminPolaznik->AddPitanje(PRII, polimorfizam))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;

        //ispisuje sve dostupne podatke o kandidatu
        cout << *jasminPolaznik << crt;
    }

    /*nakon evidentiranja ocjene na bilo kojem odgovoru, AKTIVNOM kandidatu se salje email sa porukom:

    FROM:info@kursevi.ba
    TO: emailKorisnika

    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.

    EDUTeam.

    slanje email poruka implemenitrati koristeci zasebne thread-ove na nacin da se jedna poruka salje svako 2 sekunde.
    */

    //osigurati da se u narednim linijama poziva i destruktor klase Kandidat

    Datum ocijenjenOD(19, 6, 2023), ocijenjenDO(1, 7, 2023);
    /*
    koristeci adekvatan operator osigurati pretragu pozitivno ocijenjeni odgovora u okviru pitanja u proslijedjenom vremenskom opsegu OD - DO.
    rezultat pretrage trebaju biti ona pitanja kojima je, u definisanom periodu, najmanje jedan odgovor ocijenjen pozitivno. drugi formalni
    argument tipa float predstavlja prosjecnu ocjenu odgovora na pronadjenom pitanju
    */
    Kolekcija<Pitanje, float> pretraga = (*jasminPolaznik)(ocijenjenOD, ocijenjenDO);
    cout << "U periodu od " << ocijenjenOD << " - " << ocijenjenDO << " ocijenjeno " << pretraga.getTrenutno() << " pitanja." << endl;
    for (size_t i = 0; i < pretraga.getTrenutno(); i++)
        cout << pretraga.getElement1(i) << endl << pretraga.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete lozinkaNijeValidna;

    cin.get();
    system("pause>0");
}