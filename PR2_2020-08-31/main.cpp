const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

// Headers I included below
#include<iostream>
#include<vector>
#include<array>
#include<string>
#include<regex>
#include<iomanip>
#include<numeric>
#include<thread>
// Headers I included above
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
enum Dupliranje { SA_DUPLIKATIMA, BEZ_DUPLIKATA };
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

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

/*
za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi 6 ili 7 znakova postujuci sljedeca pravila:
-   pocinje sa znak * (zvjezdica) ili _ (donja crtica), nakon cega slijedi
-   broj, nakon cega slijedi
-   malo slovo, nakon cega slijedi
-   razmak koji NIJE OBAVEZAN, nakon cega slijedi
-   veliko slovo, nakon cega slijedi
-   broj, nakon cega slijedi
-   malo slovo.
za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
*/

[[nodiscard]] bool ValidirajLozinku(const std::string& password) {
    std::regex passwordValidation{ "[*_]\\d[a-z]\\s?[A-Z]\\d[a-z]" };

    return std::regex_match(password, passwordValidation);
}

// Functions I defined above

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
    return temp;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int* _trenutno;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int{ 0 };
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _dupliranje = dupliranje;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
        clearArrays();
    }
    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below
    Kolekcija(const Kolekcija& kolekcija)
        : _dupliranje{ kolekcija.getDupliranje() }
        , _trenutno{ new int { kolekcija.getTrenutno() } }
        , _elementi1{ new T1[kolekcija.getTrenutno()] {} }
        , _elementi2{ new T2[kolekcija.getTrenutno()] {} }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = kolekcija.getElement1(i);
            _elementi2[i] = kolekcija.getElement2(i);
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearArrays();

        _dupliranje = rhs.getDupliranje();
        *_trenutno = rhs.getTrenutno();

        _elementi1 = new T1[getTrenutno()]{};
        _elementi2 = new T2[getTrenutno()]{};

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = rhs.getElement1(i);
            _elementi2[i] = rhs.getElement2(i);
        }

        return *this;
    }

    [[nodiscard]] Dupliranje getDupliranje() const noexcept {
        return _dupliranje;
    }

    [[nodiscard]] bool daLiJeDupliranjeDozvoljeno() const noexcept {
        return getDupliranje() == Dupliranje::SA_DUPLIKATIMA;
    }

    [[nodiscard]] bool daLiElementPostoji(const T1& element1, const T2& element2) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (element1 == getElement1(i) && element2 == getElement2(i)) {
                return true;
            }
        }

        return false;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (!daLiJeDupliranjeDozvoljeno() && daLiElementPostoji(element1, element2)) {
            throw std::runtime_error("Dupliranje nije dozvoljeno");
        }

        T1* const temp1{ new T1[getTrenutno() + 1] {} };
        T2* const temp2{ new T2[getTrenutno() + 1] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            temp1[i] = getElement1(i);
            temp2[i] = getElement2(i);
        }

        clearArrays();

        temp1[getTrenutno()] = element1;
        temp2[getTrenutno()] = element2;

        _elementi1 = temp1;
        _elementi2 = temp2;

        ++(*_trenutno);
    }

    Kolekcija operator[](const T1& element1) const {
        Kolekcija temp{};

        for (int i = 0; i < getTrenutno(); ++i) {
            if (element1 == getElement1(i)) {
                temp.AddElement(getElement1(i), getElement2(i));
            }
        }

        return temp;
    }

private:
    void clearArrays() {
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
    }
};
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
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }

    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }

    // Methods I added below
    Datum& operator=(const Datum& rhs) noexcept {
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

    [[nodiscard]] int getDan() const noexcept {
        return *_dan;
    }

    [[nodiscard]] int getMjesec() const noexcept {
        return *_mjesec;
    }

    [[nodiscard]] int getGodina() const noexcept {
        return *_godina;
    }
};
class Pitanje {
    char* _sadrzaj;
    //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
    Kolekcija<int, Datum*> _ocjeneRjesenja;
public:
    Pitanje(const char* sadrzaj = "") {
        _sadrzaj = GetNizKaraktera(sadrzaj);
    }
    ~Pitanje() {
        clearResources();
    }
    char* GetSadrzaj() { return _sadrzaj; }
    Kolekcija<int, Datum*>& GetOcjene() { return _ocjeneRjesenja; }

    // Methods I added below
    Pitanje(const Pitanje& pitanje)
        : _sadrzaj{ GetNizKaraktera(pitanje.getSadrzaj()) }
        , _ocjeneRjesenja{ pitanje.getOcjeneCopy() }
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

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 5;
    }

    bool AddOcjena(const int ocjena, const Datum& datumOcjene) {
        if (!daLiJeOcjenaValidna(ocjena)) {
            return false;
        }
        else if (!daLiJeDatumValidan(datumOcjene)) {
            return false;
        }

        _ocjeneRjesenja.AddElement(ocjena, new Datum{ datumOcjene });
        return true;
    }

    [[nodiscard]] char* getSadrzaj() const noexcept {
        return _sadrzaj;
    }

    [[nodiscard]] const Kolekcija<int, Datum*>& getOcjene() const noexcept {
        return _ocjeneRjesenja;
    }

    [[nodiscard]] Kolekcija<int, Datum*> getOcjeneCopy() const {
        Kolekcija<int, Datum*> temp{};

        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            temp.AddElement(_ocjeneRjesenja.getElement1(i), new Datum{ *_ocjeneRjesenja.getElement2(i) });
        }

        return temp;
    }

    [[nodiscard]] bool daLiSuOcjeneIDatumiJednaki(
        const Kolekcija<int, Datum*>& ocjene
    ) const noexcept {
        if (_ocjeneRjesenja.getDupliranje() != ocjene.getDupliranje()) {
            return false;
        }
        else if (_ocjeneRjesenja.getTrenutno() != ocjene.getTrenutno()) {
            return false;
        }

        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            if (ocjene.getElement1(i) != _ocjeneRjesenja.getElement1(i)) {
                return false;
            }
            else if (*ocjene.getElement2(i) != *_ocjeneRjesenja.getElement2(i)) {
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

    friend std::ostream& operator<<(std::ostream& os, const Pitanje& pitanje) {
        os << "Sadrzaj: " << std::quoted(pitanje.getSadrzaj()) << '\n';
        os << "Ocjena - datum ocjene:\n";

        const auto& ocjene{ pitanje.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - ";
            os << *ocjene.getElement2(i) << '\n';
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjek ocjene -> " << pitanje.getAverage() << '\n';

        os << std::setprecision(originalPrecision);
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
    Predmet _predmet;
    //string se odnosi na napomenu/zapazanje nastavnika
    Kolekcija<Pitanje, string> _pitanjaOdgovori;
public:
    Ispit(Predmet predmet = UIT) {
        _predmet = predmet;
    }
    Kolekcija<Pitanje, string>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
    Predmet GetPredmet() { return _predmet; }
    friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
        COUT << obj._predmet << endl;
        for (size_t i = 0; i < obj._pitanjaOdgovori.getTrenutno(); i++) {
            COUT << obj._pitanjaOdgovori.getElement1(i) << '\n';
            COUT << obj._pitanjaOdgovori.getElement2(i) << '\n';
        }
        return COUT;
    }

    // Methods I added below
    Ispit(Predmet predmet, const Pitanje& pitanje, const std::string& napomena)
        : _predmet{ predmet }
    {
        dodajPitanjeINapomenu(pitanje, napomena);
    }

    void dodajPitanjeINapomenu(const Pitanje& pitanje, const std::string& napomena) {
        _pitanjaOdgovori.AddElement(pitanje, napomena);
    }

    [[nodiscard]] bool daLiPitanjePostoji(const Pitanje& pitanje) const noexcept {
        for (int i = 0; i < _pitanjaOdgovori.getTrenutno(); ++i) {
            if (_pitanjaOdgovori.getElement1(i) == pitanje) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] const Kolekcija<Pitanje, string>& getPitanjaOdgovore() const noexcept {
        return _pitanjaOdgovori;
    }

    [[nodiscard]] Predmet getPredmet() const noexcept {
        return _predmet;
    }

    [[nodiscard]] int getBrojPitanja() const noexcept {
        return _pitanjaOdgovori.getTrenutno();
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _pitanjaOdgovori.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _pitanjaOdgovori.getElement1(i).getAverage();
        }

        return sum / size;
    }

};
class Korisnik {
    char* _imePrezime;
    string _emailAdresa;
    string _lozinka;
public:
    Korisnik(const char* imePrezime, string emailAdresa, string lozinka)
    {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
    }
    virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
    string GetEmail() const { return _emailAdresa; }
    string GetLozinka() const { return _lozinka; }
    char* GetImePrezime() const { return _imePrezime; }
    virtual void Info() = 0;

    // Methods I added below
    Korisnik(const Korisnik& korisnik)
        : _imePrezime{ GetNizKaraktera(korisnik.getImePrezime()) }
        , _emailAdresa{ korisnik.getEmail() }
        , _lozinka{ korisnik.getLozinka() }
    {}

    Korisnik& operator=(const Korisnik& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _imePrezime;

        _imePrezime = GetNizKaraktera(rhs.getImePrezime());
        _emailAdresa = rhs.getEmail();
        _lozinka = rhs.getLozinka();

        return *this;
    }

    [[nodiscard]] const std::string& getEmail() const noexcept {
        return _emailAdresa;
    }

    [[nodiscard]] const std::string& getLozinka() const noexcept {
        return _lozinka;
    }

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }
};

class Kandidat : public Korisnik {
    vector<Ispit*> _polozeniPredmeti;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka) : Korisnik(imePrezime, emailAdresa, lozinka)
    {}
    ~Kandidat() override {
        clearPredmetiArray();
    }
    friend ostream& operator<< (ostream& COUT, const Kandidat& obj) {
        COUT << obj.GetImePrezime() << " " << obj.GetEmail() << " " << obj.GetLozinka() << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << *obj._polozeniPredmeti[i];
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

    // Methods I added below
    Kandidat(const Kandidat& kandidat)
        : Korisnik(kandidat)
        , _polozeniPredmeti{ kandidat.getPolozeniPredmetiCopy() }
    {}

    Kandidat& operator=(const Kandidat& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearPredmetiArray();

        Korisnik::operator=(rhs);
        _polozeniPredmeti = rhs.getPolozeniPredmetiCopy();

        return *this;
    }

    [[nodiscard]] const std::vector<Ispit*>& getPolozeniPredmeti() const noexcept {
        return _polozeniPredmeti;
    }

    [[nodiscard]] std::vector<Ispit*> getPolozeniPredmetiCopy() const noexcept {
        std::vector<Ispit*> temp{};

        for (const auto& polozeniPredmet : _polozeniPredmeti) {
            temp.push_back(new Ispit{ *polozeniPredmet });
        }

        return temp;
    }

    void Info() override {
        std::cout << *this;
    }

    [[nodiscard]] Ispit* getIspitForPredmet(Predmet predmet) noexcept {
        auto ispitZaPronaci{
            std::find_if(
                std::begin(_polozeniPredmeti),
                std::end(_polozeniPredmeti),
                [&](const Ispit* const ispit) {
                    return ispit->getPredmet() == predmet;
                }
            )
        };

        return (ispitZaPronaci == std::end(_polozeniPredmeti)) ? nullptr : *ispitZaPronaci;
    }

    [[nodiscard]] bool daLiJeIspunjenUslovZaVisiPredmet(Predmet predmet) const noexcept {
        const auto& size{ _polozeniPredmeti.size() };

        if (!size) {
            return true;
        }

        const auto& zadnjiIspit{ *_polozeniPredmeti.back() };

        return predmet == zadnjiIspit.getPredmet() + 1
            && zadnjiIspit.getBrojPitanja() >= 3
            && zadnjiIspit.getAverage() > 3.5;
    }

    bool AddPitanje(Predmet predmet, const Pitanje& pitanje, const std::string& napomena = "") {
        auto ispit{ getIspitForPredmet(predmet) };

        if (ispit) {
            if (ispit->daLiPitanjePostoji(pitanje)) {
                return false;
            }

            ispit->dodajPitanjeINapomenu(pitanje, napomena);
            sendMail(*ispit);
            return true;
        }
        else if (!daLiJeIspunjenUslovZaVisiPredmet(predmet)) {
            return false;
        }

        _polozeniPredmeti.push_back(new Ispit{ predmet, pitanje, napomena });
        sendMail(*_polozeniPredmeti.back());
        return true;
    }

    [[nodiscard]] int operator()(const std::string& strToFind) const noexcept {
        int counter{ 0 };

        for (const auto& ispit : _polozeniPredmeti) {
            const auto& pitanja{ ispit->getPitanjaOdgovore() };

            for (int i = 0; i < pitanja.getTrenutno(); ++i) {
                if (pitanja.getElement2(i).find(strToFind) != std::string::npos) {
                    ++counter;
                }
            }
        }

        return counter;
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

private:
    void clearPredmetiArray() {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i];
    }

    void sendMail(const Ispit& ispit) const {
        std::thread emailThread{
            [&]() {
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "FROM:info@kursevi.ba\n";
                std::cout << "TO : " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirana vam je pitanje.\n";
                std::cout << "Dosadasnji uspjeh(prosjek ocjena)\n";
                std::cout << "za predmet iznosi " << ispit.getAverage() << ", a ukupni uspjeh(prosjek ocjena) na svim predmetima iznosi " << getAverage();
                std::cout << ".\nPozdrav.\nEDUTeam.\n";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite na koji nacin tip nasljedjivanja (javno, zasticeno, privatno) utjece na dostupnost atributa bazne klase unutar izvedene klase?\n";
    return "Odgovor -> Kada nasljedujemo javno dostupnost atributa bazne klase je:\n sve sto je public ostaje public\n "
        "sve sto je protected ostaje protected\n sve sto je private postaje nepristupno\nKada nasljedujemo zasticeno "
        "dostupnost atributa bazne klase je:\n sve sto je public postaje protected\n sve sto je protected ostaje protected\n "
        "sve sto je private postaje nepristupno\nKada nasljedujemo privatno dostupnost atributa bazne klase je:\n sve sto "
        "je public postaje private\n sve sto je protected postaje private\n sve sto je private postaje nepristupno\n";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Ukratko pojasnite primjenu funkcija seekg i tellg?\n";
    return "Odgovor -> seekg omogucava da postavimo trenutnu lokaciju u datom input streamu, dok tellg daje trenutnu lokaciju u datom "
        "input streamu.";
}
void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum   datum19062020(19, 6, 2020),
        datum20062020(20, 6, 2020),
        datum30062020(30, 6, 2020),
        datum05072020(5, 7, 2020);

    int kolekcijaTestSize = 10;

    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*ukoliko dupliranje vrijednosti nije dozvoljeno (BEZ_DUPLIKATA)
        metoda AddElement baca izuzetak u slucaju da se pokusa dodati par sa vrijednostima
        identicnim postojecem paru unutar kolekcije */
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;

    /*na osnovu vrijednosti tip T1 (u primjeru vrijednost 1) pronalazi i vraca iz kolekcije sve parove
    koji kao vrijednost T1 imaju proslijedjenu vrijednost*/
    cout << kolekcija1[1] << crt;
    /* npr. ako unutar kolekcije postoje parovi:
    0 0
    1 9
    1 1
    2 2
    3 3
    ispis dobijenih/vracenih vrijednosti ce biti sljedeci:
    1 9
    1 1
    */

    Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza."),
        dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom."),
        visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa."),
        regex("Navedite par primjera regex validacije podataka.");

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (sortiranjeNiza.AddOcjena(1, datum19062020))
        cout << "Ocjena evidentirana!" << endl;
    if (!sortiranjeNiza.AddOcjena(5, datum20062020))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (sortiranjeNiza.AddOcjena(5, datum30062020))
        cout << "Ocjena evidentirana!" << endl;

    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
     // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    cout << sortiranjeNiza << endl;

    if (ValidirajLozinku("*2gT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*7aT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("_6gU9z"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*3aB1y"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*1a T2l"))
        cout << "Lozinka validna" << endl;
    if (!ValidirajLozinku("-1a T2l"))
        cout << "Lozinka NIJE validna" << endl;

    /*
    za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi 6 ili 7 znakova postujuci sljedeca pravila:
    -   pocinje sa znak * (zvjezdica) ili _ (donja crtica), nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo, nakon cega slijedi
    -   razmak koji NIJE OBAVEZAN, nakon cega slijedi
    -   veliko slovo, nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo.
    za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    */

    Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "*2gT2x");
    Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "_6gU9z");
    Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za visi predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //ukoliko je potrebno, doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);

    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija, "nedostaje operator delete"))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, regex, "unutar posljednjeg dijela nedostaje opis glavnih operatora"))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;

        //ispisuje sve dostupne podatke o kandidatu
        cout << *jasminPolaznik << crt;

        //vraca broj ponavljanja odredjene rijeci unutar napomena nastalih tokom polaganja ispita.
        int brojPonavljanja = (*jasminPolaznik)("nedostaje");
        cout << "Rijec nedostaje se ponavlja " << brojPonavljanja << " puta." << endl;

    }
    /*nakon evidentiranja ocjene na bilo kojem odgovoru, kandidatu se salje email sa porukom:
    FROM:info@kursevi.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.
    EDUTeam.
    slanje email poruka implemenitrati koristeci zasebne thread-ove.
    */

    delete jasmin;
    delete adel;
    delete lozinkaNijeValidna;

    cin.get();
    system("pause>0");
}