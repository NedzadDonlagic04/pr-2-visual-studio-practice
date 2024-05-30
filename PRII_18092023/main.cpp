#include <iostream>
using namespace std;

// Headers I included below
#include<vector>
#include<array>
#include<iomanip>
#include<numeric>
#include<regex>
#include<string>
#include<thread>
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

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

// Functions I defined below
std::ostream& operator<<(std::ostream& os, Predmet predmet) {
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

[[nodiscard]] bool ValidirajLozinku(const std::string& password) {
    if (password.size() < 7) {
        return false;
    }

    std::regex atLeast1UppercaseCheck{ "[A-Z]" };
    std::regex atLeast1LowercaseCheck{ "[a-z]" };
    std::regex atLeast1DigitCheck{ "\\d" };
    std::regex atLeast1SpecialCharCheck{ "\\W" };
    
    return std::regex_search(password, atLeast1UppercaseCheck)
        && std::regex_search(password, atLeast1LowercaseCheck)
        && std::regex_search(password, atLeast1DigitCheck)
        && std::regex_search(password, atLeast1SpecialCharCheck);
}
// Functions I defined above

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
        clearArrays();
        delete _trenutno; _trenutno = nullptr;
    }

    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below
    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno { new int { kolekcija.getTrenutno() } }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = new T1{ kolekcija.getElement1(i) };
            _elementi2[i] = new T2{ kolekcija.getElement2(i) };
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearArrays();

        *_trenutno = rhs.getTrenutno();

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = new T1{ rhs.getElement1(i) };
            _elementi2[i] = new T2{ rhs.getElement2(i) };
        }

        return *this;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (getTrenutno() == max) {
            throw std::runtime_error("Maksimalni broj elemenata dostignut");
        }

        _elementi1[getTrenutno()] = new T1{ element1 };
        _elementi2[getTrenutno()] = new T2{ element2 };

        ++(*_trenutno);
    }

    void AddElement(const T1& element1, const T2& element2, const int index) {
        if (getTrenutno() == max) {
            throw std::runtime_error("Maksimalni broj elemenata dostignut");
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

    T2& operator[](const T1& element1) {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (element1 == getElement1(i)) {
                return getElement2(i);
            }
        }
    }

    Kolekcija* operator()(int start, int end) {
        Kolekcija* temp{ new Kolekcija {} };

        start = std::max(start, 0);
        end = std::min(end, getTrenutno() - 1);

        for (int i = start; i <= end; ++i) {
            temp->AddElement(getElement1(i), getElement2(i));
        }

        return temp;
    }

private:
    void clearArrays() {
        for (size_t i = 0; i < *_trenutno; i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
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
        , _mjesec { new int { datum.getMjesec() } }
        , _godina { new int { datum.getGodina() } }
    {}

    Datum& operator=(const Datum& rhs) noexcept {
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

    [[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
        return getDan() == rhs.getDan()
            && getMjesec() == rhs.getMjesec()
            && getGodina() == rhs.getGodina();
    }

    [[nodiscard]] bool operator!=(const Datum& rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] int64_t toInt64_t() const noexcept {
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
        return toInt64_t() - rhs.toInt64_t();
    }

    [[nodiscard]] bool operator<=(const Datum& rhs) const noexcept {
        return toInt64_t() <= rhs.toInt64_t();
    }

    [[nodiscard]] bool operator>=(const Datum& rhs) const noexcept {
        return toInt64_t() >= rhs.toInt64_t();
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
        clearResources();
    }

    char* GetSadrzaj() { return _sadrzaj; }
    Kolekcija<int, Datum*, MaxBrojRjesenja> GetOcjene() const { return _ocjeneRjesenja; }

    // Methods I added below
    Pitanje(const Pitanje& pitanje)
        : _sadrzaj { GetNizKaraktera(pitanje.getSadrzaj()) }
        , _ocjeneRjesenja { pitanje.getOcjeneCopy() }
    {}

    Pitanje& operator=(const Pitanje& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearResources();

        _sadrzaj = GetNizKaraktera(rhs.getSadrzaj());
        _ocjeneRjesenja = rhs.getOcjeneCopy();

        return *this;
    }

    [[nodiscard]] bool daLiPostojiOcjenaUIntervalu(const Datum& pocetak, const Datum& kraj) const noexcept {
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            const auto& trenutniDatum{ *_ocjeneRjesenja.getElement2(i) };

            if (trenutniDatum >= pocetak && trenutniDatum <= kraj && _ocjeneRjesenja.getElement1(i) > 1) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] bool daLiSuOcjeneIDatumiJednaki(
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
            && daLiSuOcjeneIDatumiJednaki(rhs.getOcjene());
    }

    [[nodiscard]] bool operator!=(const Pitanje& rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 5;
    }

    [[nodiscard]] const char* getSadrzaj() const noexcept { 
        return _sadrzaj; 
    }

    [[nodiscard]] const Kolekcija<int, Datum*, MaxBrojRjesenja>& getOcjene() const noexcept { 
        return _ocjeneRjesenja; 
    }

    [[nodiscard]] Kolekcija<int, Datum*, MaxBrojRjesenja> getOcjeneCopy() const {
        Kolekcija<int, Datum*, MaxBrojRjesenja> temp{};

        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            temp.AddElement(
                _ocjeneRjesenja.getElement1(i),
                new Datum { *_ocjeneRjesenja.getElement2(i) }
            );
        }

        return temp;
    }

    [[nodiscard]] bool daLiJeDatumValidan(const Datum& datumOcjene) const noexcept {
        const int size{ _ocjeneRjesenja.getTrenutno() };

        if (!size) {
            return true;
        }

        const auto& zadnjiDatum{ *_ocjeneRjesenja.getElement2(size - 1) };

        return (datumOcjene - zadnjiDatum) >= 3;
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

    friend std::ostream& operator<<(std::ostream& os, const Pitanje& pitanje) {
        os << "Sadrzaj pitanja: " << std::quoted(pitanje.getSadrzaj()) << '\n';
        os << "Ocjene - datum ocjene:\n";

        const auto& ocjene{ pitanje.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - ";
            os << *ocjene.getElement2(i) << '\n';
        }

        const auto& originaPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjek ocjena -> " << pitanje.getAverage() << '\n';

        os << std::setprecision(originaPrecision);
        os.unsetf(std::ios::fixed);
        
        return os;
    }

private:
    void clearResources() {
        delete[] _sadrzaj; _sadrzaj = nullptr;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            delete _ocjeneRjesenja.getElement2(i);
        }
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
    Ispit(const Ispit& ispit)
        : _predmet { new Predmet { ispit.getPredmet() } }
        , _pitanjaOdgovori { ispit.getPitanjaOdgovore() }
    {}

    Ispit(Predmet predmet, const Pitanje& pitanje)
        : _predmet{ new Predmet { predmet } }
    {
        _pitanjaOdgovori.push_back(pitanje);
    }

    Ispit& operator=(const Ispit& rhs) {
        if (this == &rhs) {
            return *this;
        }

        *_predmet = rhs.getPredmet();
        _pitanjaOdgovori = rhs.getPitanjaOdgovore();

        return *this;
    }

    [[nodiscard]] const std::vector<Pitanje>& getPitanjaOdgovore() const noexcept { 
        return _pitanjaOdgovori; 
    }

    [[nodiscard]] Predmet getPredmet() const noexcept { 
        return *_predmet; 
    }

    [[nodiscard]] bool daLiPitanjePostoji(const Pitanje& pitanje) const noexcept {
        auto postojecePitanje{ 
            std::find(std::begin(_pitanjaOdgovori), std::end(_pitanjaOdgovori), pitanje )
        };

        return postojecePitanje != std::end(_pitanjaOdgovori);
    }

    void dodajPitanje(const Pitanje& pitanje) {
        _pitanjaOdgovori.push_back(pitanje);
    }

    [[nodiscard]] double getAverage() const noexcept {
        const auto& size{ _pitanjaOdgovori.size() };

        if (!size) {
            return 0.0;
        }

        return std::accumulate(
            std::begin(_pitanjaOdgovori),
            std::end(_pitanjaOdgovori),
            0.0,
            [](const double sum, const Pitanje& pitanje) {
                return sum + pitanje.getAverage();
            }
        ) / size;
    }

    [[nodiscard]] std::size_t getBrojPitanje() const noexcept {
        return _pitanjaOdgovori.size();
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
        if (this == &rhs) {
            return *this;
        }

        delete[] _imePrezime;

        _imePrezime = GetNizKaraktera(rhs.getImePrezime());
        _emailAdresa = rhs.getEmail();
        _aktivan = rhs.getAktivan();
        _lozinka = rhs.getLozinka();

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
        os << "Aktivan: " << std::boolalpha << korisnik.getAktivan() << std::noboolalpha;
            
        return os;
    }
};
class Kandidat : public Korisnik {
    vector<Ispit*> _polozeniPredmeti;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka) 
        : Korisnik(imePrezime, emailAdresa, lozinka)
    {}
    ~Kandidat() override {
        clearResources();
        cout << crt << "KANDIDAT :: DESTRUKTOR" << crt;
    }

    friend ostream& operator<< (ostream& COUT, const Kandidat& obj) {
        COUT << (const Korisnik&)obj << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << *obj._polozeniPredmeti[i];
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

    // Methods I added below
    Kandidat(const Kandidat& kandidat)
        : Korisnik(kandidat)
        , _polozeniPredmeti { kandidat.getPolozeniPredmetiCopy() }
    {}

    Kandidat& operator=(const Kandidat& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearResources();

        Korisnik::operator=(rhs);
        _polozeniPredmeti = rhs.getPolozeniPredmetiCopy();

        return *this;
    }

    [[nodiscard]] const std::vector<Ispit*>& getPolozeniPredmeti() const noexcept { 
        return _polozeniPredmeti; 
    }

    [[nodiscard]] std::vector<Ispit*> getPolozeniPredmetiCopy() const {
        std::vector<Ispit*> temp{};

        for (const auto& polozeniPredmet : _polozeniPredmeti) {
            temp.push_back(new Ispit{ *polozeniPredmet });
        }

        return temp;
    }

    [[nodiscard]] Ispit* getIspitForPredmet(Predmet predmet) {
        auto postojeciIspit{
            std::find_if(
                std::begin(_polozeniPredmeti),
                std::end(_polozeniPredmeti),
                [&](const Ispit* const ispit) {
                    return ispit->getPredmet() == predmet;
                }
            )
        };

        return (postojeciIspit == std::end(_polozeniPredmeti)) ? nullptr : *postojeciIspit;
    }

    [[nodiscard]] bool daLiJeIspunjenUslovZaVisiPredmet(Predmet predmet) const noexcept {
        const auto& size{ _polozeniPredmeti.size() };

        if (!size) {
            return true;
        }

        const auto& zadnjiIspit{ *_polozeniPredmeti.back() };

        return zadnjiIspit.getPredmet() + 1 == predmet && zadnjiIspit.getBrojPitanje() >= 3 && zadnjiIspit.getAverage() > 3.5;
    }

    bool AddPitanje(Predmet predmet, const Pitanje& pitanje) {
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
        else if (!daLiJeIspunjenUslovZaVisiPredmet(predmet)) {
            return false;
        }

        _polozeniPredmeti.push_back(new Ispit{ predmet, pitanje });
        sendMail(*_polozeniPredmeti.back());
        return true;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const auto& size{ _polozeniPredmeti.size() };

        if (!size) {
            return 0.0;
        }

        return std::accumulate(
            std::begin(_polozeniPredmeti),
            std::end(_polozeniPredmeti),
            0.0,
            [](const double sum, const Ispit* const ispit) {
                return sum + ispit->getAverage();
            }
        ) / size;
    }

    Kolekcija<Pitanje, float> operator()(const Datum& pocetak, const Datum& kraj) const {
        Kolekcija<Pitanje, float> temp{};

        for (const auto& polozeniPredmet : _polozeniPredmeti) {
            const auto& pitanjaOdgovori{ polozeniPredmet->getPitanjaOdgovore() };

            for (const auto& pitanjeOdgovor : pitanjaOdgovori) {
                if (pitanjeOdgovor.daLiPostojiOcjenaUIntervalu(pocetak, kraj)) {
                    temp.AddElement(pitanjeOdgovor, pitanjeOdgovor.getAverage());
                }
            }
        }

        return temp;
    }

    void Info() override {
        std::cout << *this;
    }
private:
    void sendMail(const Ispit& ispit) {
        std::thread emailThread{
            [&]() {
                std::this_thread::sleep_for(2s);
                const auto& originaPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;
                
                std::cout << "FROM:info@kursevi.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirano vam je pitanje ";
                std::cout << std::quoted(ispit.getPitanjaOdgovore().back().getSadrzaj());
                std::cout << " za predmet " << ispit.getPredmet() << '\n';
                std::cout << "Dosadasnji uspjeh (prosjek ocjena)\n za pitanje ";
                std::cout << std::quoted(ispit.getPitanjaOdgovore().back().getSadrzaj());
                std::cout << " iznosi " << ispit.getAverage() << ", a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi ";
                std::cout << getAverage() << '\n';
                std::cout << "Pozdrav.\n\n";
                std::cout << "EDUTeam.\n";

                std::cout << std::setprecision(originaPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();
    }

    void clearResources() {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i], _polozeniPredmeti[i] = nullptr;
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite STACK i HEAP dio memorije, za šta su namijenjeni, te na koji način se trebaju koristiti (prednosti i nedostaci pojedinih slučajeva).\n";
    return "Odgovor -> STACK je dio memorije namjenjen za lokalne varijable, parametre funkcija, stack frame-ovi funkcija "
        " koje se izvrsavaju i slicno. Prednost rada na stacku je sto za nas je obavljeno alociranje i dealociranje, dok je "
        " mana ogranicena kolicina memorije koju stack posjeduje.\n"
        "HEAP je dio memorije koji se daje u dijelovima koji se zovu pages (ja mislim da je otprilike jedan page 4kB?)"
        " i sluzi nam za dinamicko alociranje memorije koja bi inace bila mozda previse za drzati na stacku, to je "
        " najveca prednost, dok je mana to sto smo mi onda odgovorni za tu memoriju i mi je moramo alocirati i dealocirati "
        " rucno (iako su uvedene ideje kao smart pointeri da olaksaju taj proces, nece se uvijek one koristiti za taj proces).";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite preduslove za realizaciju polimorfizma, te koje su prednosti njegovog korištenja?\n";
    return "Odgovor -> Da bi se realizovao polimorfizam potrebna je makar 1 metoda da bude deklarisana sa kljucnom rijeci virtual."
        "Recimo imamo klase Base i Derived, u klasi Base definisemo virtual void Info() {}, u klasi Derived definisemo "
        "void Info() override {} (naravno pored ovog je potrebno deklarisati virtualnim destruktor Base klase)."
        "Sada ako uzmemo Base* base = new Derived {}; i pozovemo base->Info(); imamo mogucnost pristupiti metodi Info"
        " iz najnasljedenije klase. Prednosti nasljedivanja su u tome sto nam dozvoljava da pomocu pokazivaca na baznu "
        " klasu imamo mogucnost da radimo sa svim objektima koji su je naslijedili, to moze dovesti do manje ponavljanja koda"
        " i fleksibilniji rad sa klasama.";
}
void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

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