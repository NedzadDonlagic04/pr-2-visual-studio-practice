#include<iostream>
#include<iostream>
#include<vector>

// Headers I included
#include<numeric>
#include<regex>
#include<iomanip>
#include<thread>

using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
const int brojTehnika = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";


char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
    return temp;
}

[[nodiscard]] bool ValidirajLozinku(const std::string& password) {
    if (password.size() < 7) {
        return false;
    }

    std::regex upperCaseCheck{ "[A-Z]+" };
    std::regex lowerCaseCheck{ "[a-z]+" };
    std::regex atLeast1NumberCheck{ "[0-9]+" };
    std::regex atLeast1SpecialSignCheck{ "[-@*]+" };

    return std::regex_search(password, upperCaseCheck)
        && std::regex_search(password, lowerCaseCheck)
        && std::regex_search(password, atLeast1NumberCheck)
        && std::regex_search(password, atLeast1SpecialSignCheck);
}

[[nodiscard]] const char* GetPojasText(const Pojas& pojas) noexcept {
    switch (pojas) {
    case Pojas::BIJELI:
        return "BIJELI";
    case Pojas::ZUTI:
        return "ZUTI";
    case Pojas::NARANDZASTI:
        return "NARANDZASTI";
    case Pojas::ZELENI:
        return "ZELENI";
    case Pojas::PLAVI:
        return "PLAVI";
    case Pojas::SMEDJI:
        return "SMEDJI";
    case Pojas::CRNI:
        return "CRNI";
    default:
        return "Nevalidan pojas";
    }
}

std::ostream& operator<<(std::ostream& os, const Pojas& pojas) {
    os << GetPojasText(pojas);

    return os;
}

template<class T1, class T2, int max = 10>
class Kolekcija {
    T1* _elementi1[max] = { nullptr };
    T2* _elementi2[max] = { nullptr };
    int  _trenutno;
public:
    Kolekcija() { _trenutno = 0; }
    ~Kolekcija() {
        for (size_t i = 0; i < _trenutno; i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
    }

    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // From here on out are things I defined myself
    Kolekcija(const Kolekcija& kolekcija) 
        : _trenutno { kolekcija._trenutno }
    {
        for (int i = 0; i < _trenutno; ++i) {
            _elementi1[i] = new T1{ kolekcija.getElement1(i) };
            _elementi2[i] = new T2{ kolekcija.getElement2(i) };
        }
    }

    Kolekcija& operator=(const Kolekcija& kolekcija) {
        OslobodiElement1IElement2AkoPostoje(kolekcija);
        KopirajVrijednostiUElement1IElement2(kolekcija);

        return *this;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (_trenutno == max) {
            throw std::exception("Max broj elemenata u kolekciji dostignut");
        }

        _elementi1[_trenutno] = new T1{ element1 };
        _elementi2[_trenutno] = new T2{ element2 };

        ++_trenutno;
    }

    void AddElement(const T1& element1, const T2& element2, const int index) {
        if (_trenutno == max) {
            throw std::exception("Max broj elemenata u kolekciji dostignut");
        }
        else if (index < 0 || index >= max) {
            throw std::exception("Indeks na koji se treba ubaciti vrijednost ne postoji");
        }

        _elementi1[_trenutno] = new T1{};
        _elementi2[_trenutno] = new T2{};
        
        for (int i = _trenutno; i > index; --i) {
            *_elementi1[i] = *_elementi1[i - 1];
            *_elementi2[i] = *_elementi2[i - 1];
        }

        *_elementi1[index] = element1;
        *_elementi2[index] = element2;

        ++_trenutno;
    }

    void RemoveAt(const int index) {
        if (index < 0 || index >= max) {
            throw std::exception("Indeks na koji se treba ubaciti vrijednost ne postoji");
        }

        for (int i = index + 1; i < _trenutno; ++i) {
            *_elementi1[i - 1] = *_elementi1[i];
            *_elementi2[i - 1] = *_elementi2[i];
        }

        --_trenutno;
    }

    [[nodiscard]] T2& operator[](const T1& element1) {
        for (int i = 0; i < _trenutno; ++i) {
            if (getElement1(i) == element1) {
                return getElement2(i);
            }
        }

        throw std::exception("Ne postoji element sa ovim indeksom");
    }

    [[nodiscard]] T1& getElement1(int lokacija) noexcept { 
        return *_elementi1[lokacija]; 
    }

    [[nodiscard]] T2& getElement2(int lokacija) noexcept { 
        return *_elementi2[lokacija]; 
    }

    [[nodiscard]] int getTrenutno() const noexcept { 
        return _trenutno; 
    }

    [[nodiscard]] bool operator==(const Kolekcija& rhs) const noexcept {
        if (getTrenutno() != rhs.getTrenutno()) {
            return false;
        }

        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) != rhs.getElement1(i) ||
                getElement2(i) != rhs.getElement2(i)) {
                return false;
            }
        }

        return true;
    }

private:
    void KopirajVrijednostiUElement1IElement2(const Kolekcija& kolekcija) noexcept {
        _trenutno = kolekcija._trenutno;

        for (int i = 0; i < _trenutno; ++i) {
            _elementi1[i] = new T1{ kolekcija.getElement1(i) };
            _elementi2[i] = new T2{ kolekcija.getElement2(i) };
        }
    }

    void OslobodiElement1IElement2AkoPostoje() noexcept {
        if (!_trenutno) {
            return;
        }

        for (int i = 0; i < _trenutno; ++i) {
            delete _elementi1[i];
            delete _elementi2[i];
        }
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

    // From here on out are things I defined myself
    Datum(const Datum& datum)
        : _dan { new int { datum.GetDan() }}
        , _mjesec{ new int { datum.GetMjesec() }}
        , _godina{ new int { datum.GetGodina() }}
    {}

    Datum& operator=(const Datum& datum) {
        int* const tempDan{ new int{ datum.GetDan() }};
        int* const tempMjesec{ new int{ datum.GetMjesec() }};
        int* const tempGodina{ new int{ datum.GetGodina() }};

        delete _dan;
        delete _mjesec;
        delete _godina;

        _dan = tempDan;
        _mjesec = tempMjesec;
        _godina = tempGodina;

        return *this;
    }

    [[nodiscard]] int GetDan() const noexcept { 
        return *_dan; 
    }

    [[nodiscard]] int GetMjesec() const noexcept {
        return *_mjesec;
    }

    [[nodiscard]] int GetGodina() const noexcept {
        return *_godina;
    }

    [[nodiscard]] int GetDatumKaoBrojDanaOdGodine0() const {
        int totalDays{ 0 };

        int godina{ GetGodina() };
        const int mjesec{ GetMjesec() };

        totalDays += godina * 365 + GetDan();

        if (mjesec <= 2) {
            --godina;
        }

        totalDays += (godina / 4 + godina / 400 - godina / 100);

        totalDays += [&]() {
            constexpr int daysPerMonth[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            return std::accumulate(daysPerMonth, daysPerMonth + mjesec - 1, 0);
        }();

        return totalDays;
    }

    [[nodiscard]] int operator-(const Datum& rhs) const noexcept {
        return GetDatumKaoBrojDanaOdGodine0() - rhs.GetDatumKaoBrojDanaOdGodine0();
    }

    [[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
        return GetDan() == rhs.GetDan()
            && GetMjesec() == rhs.GetMjesec()
            && GetGodina() == rhs.GetGodina();
    }

    [[nodiscard]] bool operator!=(const Datum& rhs) const noexcept {
        return !(*this == rhs);
    }
};

class Tehnika {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a Datum na datum kada je ocijenjena odredjena tehnika 
    Kolekcija<int, Datum, brojTehnika>* _ocjene;
public:
    Tehnika(const char* naziv) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<int, Datum, brojTehnika>();
    }
    ~Tehnika() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    char* GetNaziv() { return _naziv; }
    Kolekcija<int, Datum, brojTehnika>& GetOcjene() { return *_ocjene; }

    // From here on out are things I defined myself
    Tehnika(const Tehnika& tehnika)
        : _naziv { GetNizKaraktera(tehnika.GetNaziv()) }
        , _ocjene{ new Kolekcija<int, Datum, brojTehnika>{ tehnika.GetOcjene() } }
    {}

    Tehnika& operator=(const Tehnika& tehnika) {
        char* const tempNaziv{ GetNizKaraktera(tehnika.GetNaziv()) };
        Kolekcija<int, Datum, brojTehnika>* tempOcjene{ new Kolekcija<int, Datum, brojTehnika>{ tehnika.GetOcjene() }};

        delete[] _naziv;
        delete _ocjene;

        _naziv = tempNaziv;
        _ocjene = tempOcjene;

        return *this;
    }

    [[nodiscard]] const char* GetNaziv() const noexcept {
        return _naziv; 
    }

    [[nodiscard]] const Kolekcija<int, Datum, brojTehnika>& GetOcjene() const noexcept { 
        return *_ocjene; 
    }
    
    bool AddOcjena(const int ocjena, const Datum& datum) noexcept {
        if (ocjena < 1 || ocjena > 5) {
            return false;
        }

        const int trenutnoOcjena{ _ocjene->getTrenutno() };
        
        if (trenutnoOcjena && datum - (*_ocjene).getElement2(trenutnoOcjena - 1) < 3) {
            return false;
        }

        _ocjene->AddElement(ocjena, datum);
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tehnika& tehnika) {
        os << crt;
        os << "Naziv tehnike: " << std::quoted(tehnika.GetNaziv()) << '\n';
        os << "Ocjene - Datum polaganja:\n";

        const auto& ocjene{ tehnika.GetOcjene() };

        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - " << ocjene.getElement2(i) << '\n';
        }

        os << "Prosjecna ocjena za tehniku: " << tehnika.GetProsjecnaOcjenaTehnike();
        os << crt;

        return os;
    }

    [[nodiscard]] bool operator==(const Tehnika& rhs) const noexcept {
        return !std::strcmp(GetNaziv(), rhs.GetNaziv())
            && GetOcjene() == rhs.GetOcjene();
    }

    [[nodiscard]] double GetProsjecnaOcjenaTehnike() const noexcept {
        double sum{ 0.0 };
        int brojTehnika{ GetOcjene().getTrenutno() };

        for (int i = 0; i < brojTehnika; ++i) {
            sum += GetOcjene().getElement1(i);
        }

        return (brojTehnika)? sum / brojTehnika : sum;
    }
};

class Polaganje {
    Pojas _pojas;
    vector<Tehnika*> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    ~Polaganje() {
        for (size_t i = 0; i < _polozeneTehnike.size(); i++) {
            delete _polozeneTehnike[i];
            _polozeneTehnike[i] = nullptr;
        }
    }
    vector<Tehnika*>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }
    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        COUT << obj._pojas << endl;
        for (size_t i = 0; i < obj._polozeneTehnike.size(); i++)
            COUT << *obj._polozeneTehnike[i];
        return COUT;
    }

    // From here on out are things I defined myself
    [[nodiscard]] const vector<Tehnika*>& GetTehnike() const noexcept { 
        return _polozeneTehnike; 
    }

    [[nodiscard]] Pojas GetPojas() const noexcept { 
        return _pojas; 
    }

    Polaganje(const Pojas& pojas, const Tehnika& tehnika) 
        : _pojas { pojas }
    {
        _polozeneTehnike.push_back(new Tehnika(tehnika));
    }

    Polaganje(const Polaganje& polaganje)
        : _pojas { polaganje.GetPojas() }
    {
        for (std::size_t i = 0; i < polaganje.GetTehnike().size(); ++i) {
            _polozeneTehnike.push_back(new Tehnika{ *polaganje.GetTehnike().at(i) });
        }
    }

    Polaganje& operator=(const Polaganje& rhs) {
        _pojas = rhs.GetPojas();

        std::vector<Tehnika*> tempPolozeneTehnike{};

        for (std::size_t i = 0; i < rhs.GetTehnike().size(); ++i) {
            tempPolozeneTehnike.push_back(new Tehnika{ *rhs.GetTehnike().at(i) });
        }

        for (size_t i = 0; i < _polozeneTehnike.size(); ++i) {
            delete _polozeneTehnike[i];
        }

        _polozeneTehnike = std::move(tempPolozeneTehnike);

        return *this;
    }

    [[nodiscard]] bool DaLiTehnikaPostoji(const Tehnika& tehnika) const noexcept {
        const auto postojecaTehnika{
            std::find_if(
               std::begin(_polozeneTehnike),
               std::end(_polozeneTehnike),
               [&](const Tehnika* const currTehnika) {
                    return tehnika == *currTehnika;
                }
            )
        };
        
        return postojecaTehnika != std::end(_polozeneTehnike);
    }

    [[nodiscard]] double GetProsjekTehnika() const noexcept {
        return std::accumulate(
            std::begin(_polozeneTehnike),
            std::end(_polozeneTehnike),
            0.0,
            [](const double sum, const Tehnika* const tehnika) {
                return sum + tehnika->GetProsjecnaOcjenaTehnike();
            }
        );
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

    // From here on out are things I defined myself
    [[nodiscard]] const string& GetEmail() const noexcept {
        return _emailAdresa; 
    }

    [[nodiscard]] const string& GetLozinka() const noexcept {
        return _lozinka; 
    }

    [[nodiscard]] const char* GetImePrezime() const noexcept {
        return _imePrezime; 
    }

    Korisnik(const Korisnik& korisnik)
        : _imePrezime { GetNizKaraktera(korisnik.GetImePrezime()) }
        , _emailAdresa { korisnik.GetEmail() }
        , _lozinka { korisnik.GetLozinka() }
    {}

    Korisnik& operator=(const Korisnik& rhs) {
        char* const tempImePrezime{ GetNizKaraktera(rhs.GetImePrezime()) };
        std::string tempEmailAdresa{ rhs.GetEmail() };
        std::string tempLozinka{ rhs.GetLozinka() };

        delete[] _imePrezime;

        _imePrezime = tempImePrezime;
        _emailAdresa = std::move(tempEmailAdresa);
        _lozinka = std::move(tempLozinka);

        return *this;
    }
};

class KaratePolaznik : public Korisnik {
    vector<Polaganje> _polozeniPojasevi;
public:
    KaratePolaznik(const char* imePrezime, string emailAdresa, string lozinka) 
        : Korisnik(imePrezime, emailAdresa, lozinka)
    {}
    ~KaratePolaznik() {
        cout << crt << "DESTRUKTOR -> KaratePolaznik" << crt;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT << obj.GetImePrezime() << " " << obj.GetEmail() << " " << obj.GetLozinka() << endl;
        for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }

    // From here on out are things I defined myself
    [[nodiscard]] const std::vector<Polaganje>& GetPolozeniPojasevi() const noexcept { 
        return _polozeniPojasevi; 
    }

    KaratePolaznik(const KaratePolaznik& karateProlaznik)
        : Korisnik(karateProlaznik)
        , _polozeniPojasevi { karateProlaznik.GetPolozeniPojasevi() }
    {}

    KaratePolaznik& operator=(const KaratePolaznik& rhs) {
        Korisnik::operator=(rhs);
        
        std::vector<Polaganje> tempPolozeniPojasevi{ rhs.GetPolozeniPojasevi() };

        _polozeniPojasevi = std::move(tempPolozeniPojasevi);

        return *this;
    }
    /*
    sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju unutar istog objekta tipa Polaganje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
    (onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3 tehnike za ZUTI pojas ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    bool AddTehniku(const Pojas& pojas, const Tehnika& tehnika) {
        if (!_polozeniPojasevi.size()) {
            _polozeniPojasevi.push_back(Polaganje{ pojas, tehnika });
            PosaljiEmailPrekoThreadova(pojas, tehnika);
            return true;
        }
        
        auto postojeciPojas{ std::find_if(
               std::begin(_polozeniPojasevi),
                std::end(_polozeniPojasevi),
               [&](const Polaganje& polaganje) {
                        return polaganje.GetPojas() == pojas;
                }
            ) 
        };

        if (postojeciPojas != std::end(_polozeniPojasevi)) {
            if (postojeciPojas->DaLiTehnikaPostoji(tehnika)) {
                return false;
            }

            postojeciPojas->GetTehnike().push_back(new Tehnika{ tehnika });

            PosaljiEmailPrekoThreadova(pojas, tehnika);

            return true;
        }
        else if (!DaLiJeIspunjenUslovZaDodavanjeVisegPojasa()) {
            return false;
        }
        else if (pojas == Pojas::NARANDZASTI && !DaLiJeUslovZaNarandzastiPojasIspunjen()) {
            return false;
        }

        _polozeniPojasevi.push_back(Polaganje{ pojas, tehnika });
        
        PosaljiEmailPrekoThreadova(pojas, tehnika);

        return true;
    }

    [[nodiscard]] bool DaLiJeIspunjenUslovZaDodavanjeVisegPojasa() const noexcept {
        const auto& prethodniPojas{ _polozeniPojasevi.back() };

        return prethodniPojas.GetTehnike().size() >= 3 && prethodniPojas.GetProsjekTehnika() > 3.5;
    }

    [[nodiscard]] bool DaLiJeUslovZaNarandzastiPojasIspunjen() const noexcept {
        const auto zutiPojas{
            std::find_if(
                std::begin(_polozeniPojasevi),
                std::end(_polozeniPojasevi),
                [&](const Polaganje& polaganje) {
                    return polaganje.GetPojas() == Pojas::ZUTI;
                }
            )
        };

        return zutiPojas != std::end(_polozeniPojasevi)
            && zutiPojas->GetTehnike().size() >= 3
            && zutiPojas->GetProsjekTehnika() > 3.5;
    }

    [[nodiscard]] double GetProsjekZaSvePojaseve() const noexcept {
        return std::accumulate(
            std::begin(_polozeniPojasevi),
            std::end(_polozeniPojasevi),
            0.0,
            [&](const double sum, const Polaganje& polaganje) {
                return sum + polaganje.GetProsjekTehnika();
            }
        );
    }
private:
    void PosaljiEmailPrekoThreadova(const Pojas& pojas, const Tehnika& tehnika) const noexcept {
        std::thread emailThread{
            &KaratePolaznik::PosaljiEmailOEvidentiranjuTehnike,
            this,
            pojas,
            tehnika
        };
        emailThread.join();
    }

    void PosaljiEmailOEvidentiranjuTehnike(const Pojas& pojas, const Tehnika& tehnika) const noexcept {
        std::cout << "FROM:info@karate.ba\nTO: " << GetEmail() << "\n\n";
        std::cout << "Postovani " << GetImePrezime() << ", evidentirana vam je thenika ";
        std::cout << tehnika.GetNaziv() << " za " << pojas << " pojas. Dosadasnji uspjeh ";
        std::cout << "na pojasu " << pojas << " iznosi " << tehnika.GetProsjecnaOcjenaTehnike();
        std::cout << " , a ukupni uspjeh na svim pojasevima iznosi " << GetProsjekZaSvePojaseve() <<".\n";
        std::cout << "Pozdrav.\n\nKARATE Team.\n";
    }

};

const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite ulogu operatora reinterpret_cast.\n";
    return "Odgovor -> reinterpret_cast operator kada pretvara jedan tip podatka u drugi samo tretira set bitova kao da su taj drugi tip podatka, "
            "za razliku od cast-a kao sto je static_cast koji ce promjeniti set bitova da vrijednost se pravilno predstavi u drugom tipu podatka."
            "Zbog cega je veoma lahko preko ovog cast-a doci do nedefinisanog ponasanja unutar programa. ";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Ukratko opisite znacaj i vrste pametnih pokazivaca.\n";
    return "Odgovor -> Pametni pokazivaci su tip podatka koju pruza funkcionalnost pointera sa automatskim memory management. Kada se smart pointer"
            " vise ne koristi memorija je dealocirana. Neki tipovi su std::unique_ptr, std::shared_ptr, std::weak_ptr i std::auto_ptr.";
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

    Kolekcija<int, int> kolekcija1;
    for (int i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*metoda AddElement baca izuzetak u slucaju da se pokusa
        dodati vise od maksimalnog broja elemenata*/
        kolekcija1.AddElement(11, 11);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;


    kolekcija1.RemoveAt(2);
    /*uklanja par (T1 i T2) iz kolekcije koji se nalazi na lokaciji sa proslijedjenim indeksom.
    nakon uklanjanja vrijednosti onemoguciti pojavu praznog prostora unutar kolekcije tj.
    pomjeriti sve elemente koji se nalaze nakon proslijedjene lokacije za jedno mjesto unazad
    npr. ako unutar kolekcije postoje elementi
    0 0
    1 1
    2 2
    3 3
    nakon uklanjanja vrijednosti na lokaciji 1, sadrzaj kolekcije ce biti sljedeci
    0 0
    2 2
    3 3
    */

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
    Tehnika choku_zuki("choku_zuki"),
        gyaku_zuki("gyaku_zuki"),
        kizami_zuki("kizami_zuki"),
        oi_zuki("oi_zuki");
    
    /*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise navrata.
        -   razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    
    if (choku_zuki.AddOcjena(1, datum19062020))
        cout << "Ocjena evidentirana!" << endl;
    if (!choku_zuki.AddOcjena(5, datum20062020))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (choku_zuki.AddOcjena(5, datum30062020))
        cout << "Ocjena evidentirana!" << endl;
    
    /* ispisuje: naziv tehnike, ocjene (zajedno sa datumom) i prosjecnu ocjenu za tu tehniku
       ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0*/
    cout << choku_zuki << endl;

    if (ValidirajLozinku("john4Do*e"))
        cout << "OK" << crt;
    if (!ValidirajLozinku("john4Doe"))
        cout << "Specijalni znak?" << crt;
    if (!ValidirajLozinku("jo*4Da"))
        cout << "7 znakova?" << crt;
    if (!ValidirajLozinku("4jo-hnoe"))
        cout << "Veliko slovo?" << crt;
    if (ValidirajLozinku("@john2Doe"))
        cout << "OK" << crt;
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

    
    Korisnik* jasmin = new KaratePolaznik("Jasmin Azemovic", "jasmin@karate.ba", "j@sm1N*");
    Korisnik* adel = new KaratePolaznik("Adel Handzic", "adel@edu.karate.ba", "4Ade1*H");
    Korisnik* emailNijeValidan = new KaratePolaznik("John Doe", "john.doe@google.com", "johndoe");
    
    /*
    sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju unutar istog objekta tipa Polaganje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
    (onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3 tehnike za ZUTI pojas ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    
    KaratePolaznik* jasminPolaznik = dynamic_cast<KaratePolaznik*>(jasmin);

    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddTehniku(ZUTI, gyaku_zuki))
            cout << "Tehnika uspjesno dodan!" << crt;
        //ne treba dodati kizami_zuki jer ne postoje evidentirane 3 tehnike za ZUTI pojas
        if (!jasminPolaznik->AddTehniku(NARANDZASTI, kizami_zuki))
            cout << "Tehnika NIJE uspjesno dodana!" << crt;
        if (jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
            cout << "Tehnika uspjesno dodan!" << crt;
        //ne treba dodati choku_zuki jer je vec dodana za zuti pojas
        if (!jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
            cout << "Tehnika NIJE uspjesno dodana!" << crt;

        //ispisuje sve dostupne podatke o karate polazniku
        cout << *jasminPolaznik << crt;
    }
    
    /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:

    FROM:info@karate.ba
    TO: emailKorisnika

    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
    Pozdrav.

    KARATE Team.

    slanje email poruka implemenitrati koristeci zasebne thread-ove.
    */

    //osigurati da se u narednim linijama poziva i destruktor klase KaratePolaznik
    delete jasmin;
    delete adel;
    delete emailNijeValidan;
    cin.get();
    system("pause>0");
}