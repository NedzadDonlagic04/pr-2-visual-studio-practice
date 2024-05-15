// Headers I included below
#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<numeric>
#include<array>
#include<thread>
#include<iomanip>
// Headers I included below
using namespace std;

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

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
enum Dupliranje { SA_DUPLIKATIMA, BEZ_DUPLIKATA };
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

// Functions I added below
[[nodiscard]] int getNumberOfSubstrInStr(const std::string& substr, const std::string& str) {
    int counter{ 0 };
    std::size_t endPos{ str.find(substr) };

    while (endPos != std::string::npos) {
        ++counter;
        endPos = str.find(substr, endPos + substr.size());
    }

    return counter;
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
    if (password.size() != 6 && password.size() != 7) {
        return false;
    }

    std::regex passwordValidation{ "^[*_]?\\d[a-z]\\s?[A-Z]\\d[a-z]$" };

    return std::regex_search(password, passwordValidation);
}

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
// Functions I added above

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
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
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
        : _trenutno{ new int { kolekcija.getTrenutno() } }
        , _dupliranje{ kolekcija._dupliranje }
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
        _dupliranje = rhs._dupliranje;

        T1* const tempElementi1{ new T1[getTrenutno()] {} };
        T2* const tempElementi2{ new T2[getTrenutno()] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            tempElementi1[i] = rhs.getElement1(i);
            tempElementi2[i] = rhs.getElement2(i);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElementi1;
        _elementi2 = tempElementi2;

        return *this;
    }

    Kolekcija& operator=(Kolekcija&& rhs) noexcept {
        *_trenutno = std::exchange(*rhs._trenutno, 0);
        _dupliranje = std::exchange(rhs._dupliranje, Dupliranje::SA_DUPLIKATIMA);

        T1* const tempElementi1{ std::exchange(rhs._elementi1, nullptr) };
        T2* const tempElementi2{ std::exchange(rhs._elementi2, nullptr) };

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElementi1;
        _elementi2 = tempElementi2;

        return *this;
    }

    [[nodiscard]] bool daLiJeDupliranjeOnemoguceno() const noexcept {
        return _dupliranje == Dupliranje::BEZ_DUPLIKATA;
    }

    [[nodiscard]] bool daLiELementPostoji(const T1& element1, const T2& element2) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1 && getElement2(i) == element2) {
                return true;
            }
        }

        return false;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (daLiJeDupliranjeOnemoguceno() && daLiELementPostoji(element1, element2)) {
            throw std::runtime_error("Dupliranje elementa");
        }

        T1* const tempElementi1{ new T1[getTrenutno() + 1] {} };
        T2* const tempElementi2{ new T2[getTrenutno() + 1] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            tempElementi1[i] = getElement1(i);
            tempElementi2[i] = getElement2(i);
        }

        tempElementi1[getTrenutno()] = element1;
        tempElementi2[getTrenutno()] = element2;

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElementi1;
        _elementi2 = tempElementi2;

        ++(*_trenutno);
    }

    [[nodiscard]] Kolekcija operator[](const T1& element1) const noexcept {
        Kolekcija temp{};

        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1) {
                temp.AddElement(getElement1(i), getElement2(i));
            }
        }

        return temp;
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

    // Methods I defined below
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
        total += (365LL * godina);

        if (mjesec <= 2) {
            --godina;
        }

        total += (godina / 4LL + godina / 400LL - godina / 100LL);

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

    [[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
        return getDan() == rhs.getDan()
            && getMjesec() == rhs.getMjesec()
            && getGodina() == rhs.getGodina();
    }

    [[nodiscard]] bool operator!=(const Datum& rhs) const noexcept {
        return !(*this == rhs);
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
        delete[] _sadrzaj; _sadrzaj = nullptr;

        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            delete _ocjeneRjesenja.getElement2(i);
        }
    }
    char* GetSadrzaj() { return _sadrzaj; }
    Kolekcija<int, Datum*>& GetOcjene() { return _ocjeneRjesenja; }

    // Methods I added below
    Pitanje(const Pitanje& pitanje)
        : _sadrzaj{ GetNizKaraktera(pitanje.getSadrzaj()) }
    {
        const auto& ocjene{ pitanje.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            _ocjeneRjesenja.AddElement(
                ocjene.getElement1(i),
                new Datum{ *ocjene.getElement2(i) }
            );
        }
    }

    Pitanje& operator=(const Pitanje& rhs) {
        char* const tempSadrzaj{ GetNizKaraktera(rhs.getSadrzaj()) };
        Kolekcija<int, Datum*> tempOcjeneRjesenja{};

        const auto& ocjene{ rhs.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            tempOcjeneRjesenja.AddElement(
                ocjene.getElement1(i),
                new Datum{ *ocjene.getElement2(i) }
            );
        }

        delete[] _sadrzaj;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); ++i) {
            delete _ocjeneRjesenja.getElement2(i);
        }

        _sadrzaj = tempSadrzaj;
        _ocjeneRjesenja = std::move(tempOcjeneRjesenja);

        return *this;
    }

    [[nodiscard]] double getAverageGrade() const noexcept {
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

    [[nodiscard]] bool daLiSuOcjeneIDatumiIsti(const Kolekcija<int, Datum*>& ocjeneRjesenja) const noexcept {
        if (_ocjeneRjesenja.getTrenutno() != ocjeneRjesenja.getTrenutno()) {
            return false;
        }

        for (int i = 0; i < ocjeneRjesenja.getTrenutno(); ++i) {
            if (_ocjeneRjesenja.getElement1(i) != ocjeneRjesenja.getElement1(i)) {
                return false;
            }
            else if (*_ocjeneRjesenja.getElement2(i) != *ocjeneRjesenja.getElement2(i)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool operator==(const Pitanje& rhs) const noexcept {
        return !std::strcmp(getSadrzaj(), rhs.getSadrzaj())
            && daLiSuOcjeneIDatumiIsti(rhs.getOcjene());
    }

    friend std::ostream& operator<<(std::ostream& os, const Pitanje& pitanje) {
        os << "Sadrzaj: " << std::quoted(pitanje.getSadrzaj()) << '\n';
        os << "Ocjene - datum polaganja ocjene:\n";

        const auto& ocjene{ pitanje.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - ";
            os << *ocjene.getElement2(i) << '\n';
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjecna ocjena: " << pitanje.getAverageGrade() << '\n';

        os << std::setprecision(originalPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }

    [[nodiscard]] const char* getSadrzaj() const noexcept {
        return _sadrzaj;
    }

    [[nodiscard]] const Kolekcija<int, Datum*>& getOcjene() const noexcept {
        return _ocjeneRjesenja;
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 5;
    }

    [[nodiscard]] bool daLiJeDatumValidan(const Datum& datumOcjene) const noexcept {
        const int size{ _ocjeneRjesenja.getTrenutno() };

        if (!size) {
            return true;
        }

        const auto& zadnjiDodanDatum{ *_ocjeneRjesenja.getElement2(size - 1) };

        return (datumOcjene - zadnjiDodanDatum) > 3;
    }

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    bool AddOcjena(const int ocjena, const Datum& datumOcjene) {
        if (!daLiJeOcjenaValidna(ocjena) || !daLiJeDatumValidan(datumOcjene)) {
            return false;
        }

        _ocjeneRjesenja.AddElement(ocjena, new Datum{ datumOcjene });

        return true;
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
        COUT << obj._pitanjaOdgovori;
        return COUT;
    }

    // Methods I added below
    Ispit(const Ispit& ispit)
        : _predmet{ ispit.getPredmet() }
        , _pitanjaOdgovori{ ispit.getPitanjaOdgovore() }
    {}

    Ispit(const Predmet& predmet, const Pitanje& pitanje, const std::string& napomena)
        : _predmet{ predmet }
    {
        _pitanjaOdgovori.AddElement(pitanje, napomena);
    }

    Ispit& operator=(const Ispit& rhs) {
        _predmet = rhs.getPredmet();
        Kolekcija<Pitanje, string> tempPitanjaOdgovori{ rhs.getPitanjaOdgovore() };

        _pitanjaOdgovori = std::move(tempPitanjaOdgovori);

        return *this;
    }

    [[nodiscard]] int getPojavljivanjeNapomeneCounter(const std::string& napomena) {
        int counter{ 0 };

        for (int i = 0; i < _pitanjaOdgovori.getTrenutno(); ++i) {
            counter += getNumberOfSubstrInStr(napomena, _pitanjaOdgovori.getElement2(i));
        }

        return counter;
    }

    [[nodiscard]] bool daLiPitanjeIOdgovorPostoji(const Pitanje& pitanje, const std::string& napomena) const noexcept {
        for (int i = 0; i < _pitanjaOdgovori.getTrenutno(); ++i) {
            if (pitanje == _pitanjaOdgovori.getElement1(i) && napomena == _pitanjaOdgovori.getElement2(i)) {
                return true;
            }
        }

        return false;
    }

    void dodajPitanjeIOdgovor(const Pitanje& pitanje, const std::string& napomena) {
        _pitanjaOdgovori.AddElement(pitanje, napomena);
    }

    [[nodiscard]] const Kolekcija<Pitanje, string>& getPitanjaOdgovore() const noexcept {
        return _pitanjaOdgovori;
    }

    [[nodscard]] const Predmet& getPredmet() const noexcept {
        return _predmet;
    }

    [[nodiscard]] double getAverageForAllQuestions() const noexcept {
        const int size{ _pitanjaOdgovori.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _pitanjaOdgovori.getElement1(i).getAverageGrade();
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
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    char* GetImePrezime() { return _imePrezime; }
    virtual void Info() = 0;

    // Methods I defined below
    Korisnik(const Korisnik& korisnik)
        : _imePrezime { GetNizKaraktera(korisnik.getImePrezime()) }
        , _emailAdresa { korisnik.getEmail() }
        , _lozinka { korisnik.getLozinka() } 
    {}

    Korisnik& operator=(const Korisnik& rhs) {
        char* const tempImePrezime{ GetNizKaraktera(rhs.getImePrezime()) };
        std::string tempEmailAdresa{ rhs.getEmail() };
        std::string tempLozinka{ rhs.getLozinka() };

        delete _imePrezime;

        _imePrezime = tempImePrezime;
        _emailAdresa = std::move(tempEmailAdresa);
        _lozinka = std::move(tempLozinka);

        return *this;
    }

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] const std::string& getEmail() const noexcept {
        return _emailAdresa;
    }

    [[nodiscard]] const std::string& getLozinka() const noexcept {
        return _lozinka;
    }
};

class Kandidat : public Korisnik {
    vector<Ispit*> _polozeniPredmeti;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka) 
        : Korisnik(imePrezime, emailAdresa, lozinka) 
    {}
    ~Kandidat() override {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i];
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj.GetImePrezime() << " " << obj.GetEmail() << " " << obj.GetLozinka() << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << *obj._polozeniPredmeti[i];
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

    // Methods I added below
    Kandidat(const Kandidat& kandidat)
        : Korisnik(kandidat)
    {
        const auto& predmeti{ kandidat.getPolozeniPredmeti() };
        for (const auto& predmet : predmeti) {
            _polozeniPredmeti.push_back(new Ispit{ *predmet });
        }
    }

    Kandidat& operator=(const Kandidat& rhs) {
        Korisnik::operator=(rhs);
        std::vector<Ispit*> tempPolozeniPredmeti{};

        const auto& predmeti{ rhs.getPolozeniPredmeti() };
        for (const auto& predmet : predmeti) {
            tempPolozeniPredmeti.push_back(new Ispit{ *predmet });
        }

        for (const auto& predmet : _polozeniPredmeti) {
            delete predmet;
        }

        _polozeniPredmeti = std::move(tempPolozeniPredmeti);

        return *this;
    }

    [[nodiscard]] const std::vector<Ispit*>& getPolozeniPredmeti() const noexcept {
        return _polozeniPredmeti;
    }

    void Info() override {
        std::cout << getImePrezime() << " " << getEmail() << " " << getLozinka() << endl;
        for (const auto& polozeniPredmet : _polozeniPredmeti) {
            std::cout << *polozeniPredmet;
        }
    }

    [[nodiscard]] Ispit* getIspitForPredmet(const Predmet& predmet) {
        auto ispitZaPronac{
            std::find_if(
                std::begin(_polozeniPredmeti),
                std::end(_polozeniPredmeti),
                [&](const Ispit* const ispit) {
                        return ispit->getPredmet() == predmet;
                }
            )
        };

        return (ispitZaPronac == std::end(_polozeniPredmeti)) ? nullptr : *ispitZaPronac;
    }

    [[nodiscard]] bool daLiJeIspunjenUslovZaVisiPredmet(const Predmet& predmet) const noexcept {
        if (!_polozeniPredmeti.size()) {
            return true;
        }

        const auto& prijasnjiIspit{ *_polozeniPredmeti.back() };

        if (prijasnjiIspit.getPitanjaOdgovore().getTrenutno() < 3) {
            return false;
        }
        else if (prijasnjiIspit.getAverageForAllQuestions() <= 3.5) {
            return false;
        }

        return prijasnjiIspit.getPredmet() + 1 == predmet;
    }

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za visi predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    bool AddPitanje(const Predmet& predmet, const Pitanje& pitanje, const std::string& napomena = "") {
        auto ispitZaPredmet{ getIspitForPredmet(predmet) };

        if (ispitZaPredmet) {
            if (ispitZaPredmet->daLiPitanjeIOdgovorPostoji(pitanje, napomena)) {
                return false;
            }
            ispitZaPredmet->dodajPitanjeIOdgovor(pitanje, napomena);
            sendMail(*ispitZaPredmet);
            return true;
        }
        else if (!daLiJeIspunjenUslovZaVisiPredmet(predmet)) {
            return false;
        }

        _polozeniPredmeti.push_back(new Ispit(predmet, pitanje, napomena));
        sendMail(*_polozeniPredmeti.back());
        return true;
    }

    [[nodiscard]] int operator()(const std::string& dioNapomene) const {
        int counter{ 0 };

        for (const auto& predmet : _polozeniPredmeti) {
            counter += predmet->getPojavljivanjeNapomeneCounter(dioNapomene);
        }

        return counter;
    }

    [[nodiscard]] double getAverageForAllSubjects() const noexcept {
        const std::size_t size{ _polozeniPredmeti.size() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (const auto& polozenPredmet : _polozeniPredmeti) {
            sum += polozenPredmet->getAverageForAllQuestions();
        }

        return sum / size;
    }
private:
    /*nakon evidentiranja ocjene na bilo kojem odgovoru, kandidatu se salje email sa porukom:
FROM:info@kursevi.ba
TO: emailKorisnika
Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
Pozdrav.
EDUTeam.
slanje email poruka implemenitrati koristeci zasebne thread-ove.
*/
    void sendMail(const Ispit& ispit) {
        std::thread emailThread{
            [&]() {
                const int lastIndex { ispit.getPitanjaOdgovore().getTrenutno() - 1};
                const auto& zadnjePitanje { ispit.getPitanjaOdgovore().getElement1(lastIndex)};
                
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "FROM:info@kursevi.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirana vam je ocjena " << ispit.getAverageForAllQuestions();
                std::cout << " za odgovor na pitanje " << std::quoted(zadnjePitanje.getSadrzaj());
                std::cout << ". Dosadasnji uspjeh (prosjek ocjena) za pitanje " << std::quoted(zadnjePitanje.getSadrzaj());
                std::cout << " iznosi " << zadnjePitanje.getAverageGrade() << ", a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi ";
                std::cout << getAverageForAllSubjects() << ".\n";
                std::cout << "Pozdrav.\nEDUTeam.\n";

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
    return "Odgovor -> seekg omogucava postavljanje pozicije od koje ce se citati / pisati u datom stream-u."
        "tellg vraca trenutnu poziciju na kojoj ce se citati / pisati u datom stream-u."
        "Primjena im se moze naci u bilo kojim slucajevima gdje nam je potrebno ici kroz neki stream, kada "
        "se neeki stream otvori u ios::ate mode pomocu seekg se moze otici na kraj otvorenog stream-a"
        "(nisam siguran jel ovako funkcionise konstruktor ali vjerujem da je razumna pretpostavka za napraviti)."
        "Ja sam uspjeo im naci primjenu u brojanju broja karaktera unutar nekog fajla tako sto bi iskoristio "
        "seekg(0, std::ios::end) nakon cega bi izvrsio tellg na dati stream.";
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