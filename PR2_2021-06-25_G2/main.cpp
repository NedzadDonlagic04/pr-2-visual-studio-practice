#include <iostream>
using namespace std;

// Headers I included below
#include<string>
#include<regex>
#include<vector>
#include<thread>
#include<numeric>
#include<iomanip>
#include<array>
// Headers I included below

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
enum Dupliranje { BEZ_DUPLIKATA, SA_DUPLIKATIMA };

// Functions I defined below
[[nodiscard]] std::string getPojasAsStr(const Pojas& pojas) {
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
        return "Pojas ne postoji";
    }
}

std::ostream& operator<<(std::ostream& os, const Pojas& pojas) {
    os << getPojasAsStr(pojas);

    return os;
}

/*
    email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj. zadovoljavati sljedeca pravila:
    - poceti sa jednim brojem nakon cega slijedi donja crtica
    - u imenu posjedovati najmanje 3 karaktera
    - izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od navedenog
    - u prezimenu posjedovati najmanje 3 karaktera
    - znak @
    - domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su oznake .com i .org.
*/
[[nodiscard]] bool ValidirajEmail(const std::string& email) {
    std::regex emailValidation{ "^\\d_[a-zA-Z]{3,}[._]?[a-zA-Z]{3,}@(edu.)?karate.(ba|com|org)$" };
    
    return std::regex_search(email, emailValidation);
}
// Functions I defined above

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
template<class T1, class T2, int max = 15>
class Kolekcija {
    T1 _elementi1[max];
    T2 _elementi2[max];
    int* _trenutno;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _dupliranje = dupliranje;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
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
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = kolekcija.getElement1(i);
            _elementi2[i] = kolekcija.getElement2(i);
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        *_trenutno = rhs.getTrenutno();
        _dupliranje = rhs._dupliranje;

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = rhs.getElement1(i);
            _elementi2[i] = rhs.getElement2(i);
        }

        return *this;
    }

    [[nodiscard]] bool daLiJeDupliranjeDozvoljeno() const noexcept {
        return _dupliranje == Dupliranje::SA_DUPLIKATIMA;
    }

    [[nodiscard]] bool daLiElementVecPostoji(const T1& element1, const T2& element2) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1 && getElement2(i) == element2) {
                return true;
            }
        }

        return false;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (!daLiJeDupliranjeDozvoljeno() && daLiElementVecPostoji(element1, element2)) {
            throw std::runtime_error("Dupliranje elementa");
        }
        else if (getTrenutno() == max) {
            throw std::runtime_error("Maksimalan broj elemenata dostignut");
        }

        _elementi1[getTrenutno()] = element1;
        _elementi2[getTrenutno()] = element2;

        ++(*_trenutno);
    }

    [[nodiscard]] Kolekcija operator()(const int start, const int end) const {
        if (start < 0 || start >= getTrenutno()) {
            throw std::runtime_error("Pocetni index nije validan");
        }
        else if (end < 0 || end >= getTrenutno()) {
            throw std::runtime_error("Krajni index nije validan");
        }
        
        Kolekcija temp{};

        for (int i = start; i <= end; ++i) {
            temp.AddElement(getElement1(i), getElement2(i));
        }

        return temp;
    }

    [[nodiscard]] bool operator==(const Kolekcija& rhs) const noexcept {
        if (_dupliranje != rhs._dupliranje || getTrenutno() != rhs.getTrenutno()) {
            return false;
        }

        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) != rhs.getElement1(i)) {
                return false;
            }
            else if (getElement2(i) != rhs.getElement2(i)) {
                return false;
            }

        }

        return true;
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

    [[nodiscard]] int getDan() const noexcept {
        return *_dan;
    }

    [[nodiscard]] int getMjesec() const noexcept {
        return *_mjesec;
    }

    [[nodiscard]] int getGodina() const noexcept {
        return *_godina;
    }

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

    [[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
        return getDan() == rhs.getDan()
            && getMjesec() == rhs.getMjesec()
            && getGodina() == rhs.getGodina();
    }

    [[nodiscard]] bool operator!=(const Datum& rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] int64_t getDatumAsDays() const noexcept {
        int64_t total{ 0 };

        const int mjeseci{ getMjesec() };
        int godine{ getGodina() };

        total += getDan();
        total += 365LL * getGodina();

        if (mjeseci <= 2) {
            --godine;
        }

        total += (godine / 4LL + godine / 400LL - godine / 100LL);

        total += [&]() {
            constexpr std::array<int, 12> daysPerMonth{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            return std::accumulate(
                std::begin(daysPerMonth),
                std::begin(daysPerMonth) + mjeseci - 1,
                0
            );
        }();

        return total;
    }

    [[nodiscard]] bool operator>=(const Datum& rhs) const noexcept {
        return getDatumAsDays() >= rhs.getDatumAsDays();
    }

    [[nodiscard]] bool operator<=(const Datum& rhs) const noexcept {
        return getDatumAsDays() <= rhs.getDatumAsDays();
    }

    [[nodiscard]] int64_t operator-(const Datum& rhs) const noexcept {
        return getDatumAsDays() - rhs.getDatumAsDays();
    }
};
class Tehnika {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a datum na momenat postizanja ocjene
    Kolekcija<Datum, int>* _ocjene;
public:
    Tehnika(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<Datum, int>{};
        if (ocjena > 0)
            AddOcjena(&datum, ocjena);
    }
    ~Tehnika() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    char* GetNaziv()const { return _naziv; }
    Kolekcija<Datum, int> GetOcjene() const { return *_ocjene; }

    // Methods I added below
    Tehnika(const Tehnika& tehnika)
        : _naziv { GetNizKaraktera(tehnika.GetNaziv() ) }
        , _ocjene { new Kolekcija<Datum, int>{ tehnika.getOcjene() } }
    {}

    Tehnika& operator=(const Tehnika& rhs) {
        char* const tempNaziv{ GetNizKaraktera(rhs.getNaziv()) };
        Kolekcija<Datum, int>* const tempOcjene{ new Kolekcija<Datum, int>{ rhs.getOcjene() } };

        delete[] _naziv;
        delete _ocjene;

        _naziv = tempNaziv;
        _ocjene = tempOcjene;

        return *this;
    }

    [[nodiscard]] const char* getNaziv() const noexcept {
        return _naziv;
    }

    [[nodiscard]] const Kolekcija<Datum, int>& getOcjene() const noexcept {
        return *_ocjene;
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 5;
    }

    void AddOcjena(const Datum* const datumOcjene, const int ocjena) {
        if (!daLiJeOcjenaValidna(ocjena)) {
            // An exception could be thrown here but since it wasn't specified
            // I wont'
            return;
        }
        
        _ocjene->AddElement(*datumOcjene, ocjena);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tehnika& tehnika) {
        os << "Naziv tehnike: " << std::quoted(tehnika.getNaziv()) << '\n';
        os << "Datum - ocjena:\n";
        
        const auto& ocjene{ tehnika.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - ";
            os << ocjene.getElement2(i) << '\n';
        }

        const auto& defaultPrecision{ os.precision() };
        os << std::fixed;
        os << std::setprecision(2);

        os << "Prosjecna ocjena: " << tehnika.getAverage() << '\n';

        os << std::setprecision(defaultPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _ocjene->getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _ocjene->getElement2(i);
        }

        return sum / size;
    }

    [[nodiscard]] bool operator==(const Tehnika& rhs) const noexcept {
        return !std::strcmp(getNaziv(), rhs.getNaziv())
            && getOcjene() == rhs.getOcjene();
    }

    [[nodiscard]] bool daLiTehnikaImaIjednuOcjenuIzmeduDatum(
        const Datum& pocetak, 
        const Datum& kraj
    ) const noexcept {
        for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
            const auto& trenutniDatum { _ocjene->getElement1(i) };

            if (trenutniDatum >= pocetak && trenutniDatum <= kraj) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] float getAverageNumOfDaysBetweenGrades() const noexcept {
        const int size{ _ocjene->getTrenutno() };

        if (!size) {
            return 0.0f;
        }

        float sum{ 0.0f };
        
        for (int i = 0; i < size - 1; ++i) {
            const auto& datum1{ _ocjene->getElement1(i) };
            const auto& datum2{ _ocjene->getElement1(i + 1) };

            sum += std::abs(datum1 - datum2);
        }

        return sum / size;
    }
};
class Polaganje {
    Pojas _pojas;
    //string se odnosi na napomenu o polozenoj tehnici
    Kolekcija<Tehnika*, string> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    Kolekcija<Tehnika*, string>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }
    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        COUT << obj._pojas << " " << endl;

        const auto& polozeneTehnike{ obj.getTehnike() };
        for (int i = 0; i < polozeneTehnike.getTrenutno(); ++i) {
            COUT << *polozeneTehnike.getElement1(i) << '\n';
            COUT << polozeneTehnike.getElement2(i);

            if (i + 1 != polozeneTehnike.getTrenutno()) {
                COUT << '\n';
            }
        }

        return COUT;
    }

    // Methods I defined below
    Polaganje(const Pojas& pojas, const Tehnika& tehnika, const std::string& napomena) 
        : _pojas { pojas }
    {
        _polozeneTehnike.AddElement(new Tehnika{ tehnika }, napomena);
    }

    ~Polaganje() {
        for (int i = 0; i < _polozeneTehnike.getTrenutno(); ++i) {
            delete _polozeneTehnike.getElement1(i);
        }
    }

    Polaganje(const Polaganje& polaganje)
        : _pojas{ polaganje.getPojas() }
    {
        const auto& polozeneTehnike{ polaganje.getTehnike() };
        for (int i = 0; i < polozeneTehnike.getTrenutno(); ++i) {
            _polozeneTehnike.AddElement(
                new Tehnika{ *polozeneTehnike.getElement1(i) },
                polozeneTehnike.getElement2(i)
            );
        }
    }

    Polaganje& operator=(const Polaganje& rhs) {
        _pojas = rhs.getPojas();
        
        Kolekcija<Tehnika*, string> tempPolozeneTehnike{};

        const auto& polozeneTehnike{ rhs.getTehnike() };
        for (int i = 0; i < polozeneTehnike.getTrenutno(); ++i) {
            tempPolozeneTehnike.AddElement(
                new Tehnika{ *polozeneTehnike.getElement1(i) },
                polozeneTehnike.getElement2(i)
            );
        }

        for (int i = 0; i < _polozeneTehnike.getTrenutno(); ++i) {
            delete _polozeneTehnike.getElement1(i);
        }

        _polozeneTehnike = tempPolozeneTehnike;

        return *this;
    }

    [[nodiscard]] const Kolekcija<Tehnika*, string>& getTehnike() const noexcept {
        return _polozeneTehnike;
    }

    [[nodiscard]] const Pojas& getPojas() const noexcept {
        return _pojas;
    }

    [[nodiscard]] bool daLiTehnikaPostoji(const Tehnika& tehnika) const noexcept {
        for (int i = 0; i < _polozeneTehnike.getTrenutno(); ++i) {
            if (tehnika == *_polozeneTehnike.getElement1(i)) {
                return true;
            }
        }

        return false;
    }

    void dodajTehniku(const Tehnika& tehnika, const std::string napomena) {
        _polozeneTehnike.AddElement(new Tehnika{ tehnika }, napomena);
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _polozeneTehnike.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };
        
        for (int i = 0; i < size; ++i) {
            sum += _polozeneTehnike.getElement1(i)->getAverage();
        }

        return sum / size;
    }
};
class KaratePolaznik {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Polaganje> _polozeniPojasevi;
public:
    KaratePolaznik(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _brojTelefona = brojTelefona;
    }
    ~KaratePolaznik() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }
    
    // Methods I added below

    KaratePolaznik(const KaratePolaznik& karatePolaznik)
        : _imePrezime { GetNizKaraktera(karatePolaznik.getImePrezime() ) }
        , _emailAdresa { karatePolaznik.getEmail() }
        , _brojTelefona { karatePolaznik.getBrojTelefona() }
        , _polozeniPojasevi { karatePolaznik.getPolozeniPojasevi() }
    {}

    KaratePolaznik& operator=(const KaratePolaznik& rhs) {
        char* const tempImePrezime{ GetNizKaraktera(rhs.getImePrezime()) };
        std::string tempEmailAdresa{ rhs.getEmail() };
        std::string tempBrojTelefona{ rhs.getBrojTelefona() };
        std::vector<Polaganje> tempPolozeniPojasevi{ rhs.getPolozeniPojasevi() };

        delete[] _imePrezime;
        
        _imePrezime = tempImePrezime;
        _emailAdresa = std::move(tempEmailAdresa);
        _brojTelefona = std::move(tempBrojTelefona);
        _polozeniPojasevi = std::move(tempPolozeniPojasevi);

        return *this;
    }

    [[nodiscard]] const std::vector<Polaganje>& getPolozeniPojasevi() const noexcept {
        return _polozeniPojasevi;
    }

    [[nodiscard]] const std::string& getEmail() const noexcept {
        return _emailAdresa;
    }

    [[nodiscard]] const std::string& getBrojTelefona() const noexcept {
        return _brojTelefona;
    }

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] Polaganje* getPolaganjeForPojas(const Pojas& pojas) noexcept {
        auto polaganjeZaPronaci{
            std::find_if(
                std::begin(_polozeniPojasevi),
                std::end(_polozeniPojasevi),
                [&](const Polaganje& polaganje) {
                        return polaganje.getPojas() == pojas;
                    }
            )
        };

        return (polaganjeZaPronaci == std::end(_polozeniPojasevi)) ? nullptr : &(*polaganjeZaPronaci);
    }

    /*
        svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
    uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna tehnika za nizi pojas (ne mozemo dodati tehniku za NARANDZASTI ako ne postoji niti jedna tehnika za ZUTI pojas)
    - dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    [[nodiscard]] bool daLiJeIspunjenUslovZaVisiPojas(const Pojas& pojas) const noexcept {
        if (!_polozeniPojasevi.size()) {
            return true;
        } 

        const auto& zadnjiPojas{ _polozeniPojasevi.back() };

        return zadnjiPojas.getTehnike().getTrenutno() && zadnjiPojas.getPojas() + 1 == pojas;
    }

    bool AddTehniku(const Pojas& pojas, const Tehnika& tehnika, const std::string& napomena) {
        if (tehnika.getAverage() < 3.5) {
            return false;
        }

        auto postojecePolaganje{ getPolaganjeForPojas(pojas) };

        if (postojecePolaganje) {
            if (postojecePolaganje->daLiTehnikaPostoji(tehnika)) {
                return false;
            }

            postojecePolaganje->dodajTehniku(tehnika, napomena);
            sendEmail(pojas, tehnika);
            return true;
        }
        else if (!daLiJeIspunjenUslovZaVisiPojas(pojas)) {
            return false;
        }

        _polozeniPojasevi.push_back(Polaganje{pojas, tehnika, napomena});
        sendEmail(pojas, tehnika);
        return true;
    }

    [[nodiscard]] double getAverageForPojas(const Pojas& pojas) {
        auto postojecePolaganje{ getPolaganjeForPojas(pojas) };

        if (!postojecePolaganje) {
            return 0.0;
        }

        return postojecePolaganje->getAverage();
    }

    [[nodiscard]] double getAverageForEveryPojas() const noexcept {
        const std::size_t size{ _polozeniPojasevi.size() };
        if (!size) {
            return 0.0;
        }

        return std::accumulate(
            std::begin(_polozeniPojasevi),
            std::end(_polozeniPojasevi),
            0.0,
            [&](const double sum, const Polaganje& polaganje) {
                return sum + polaganje.getAverage();
            }
        ) / size;
    }

    [[nodiscard]] Kolekcija<Tehnika*, float> operator()(const Datum& pocetak, const Datum& kraj) const noexcept {
        Kolekcija<Tehnika*, float> temp{};
        
        for (const auto& polozeniPojas : _polozeniPojasevi) {
            const auto& pojas{ polozeniPojas.getTehnike() };

            for (int i = 0; i < pojas.getTrenutno(); ++i) {
                const auto& tehnika{ *pojas.getElement1(i) };
                
                if (tehnika.daLiTehnikaImaIjednuOcjenuIzmeduDatum(pocetak, kraj)) {
                    temp.AddElement(
                        new Tehnika{ tehnika },
                        tehnika.getAverageNumOfDaysBetweenGrades()
                    );
                }
            }
        }

        return temp;
    }

private:
    void sendEmail(const Pojas& pojas, const Tehnika& tehnika) {
        const double prosjekPojasa{ getAverageForPojas(pojas) };

        std::thread emailThread{
            [&]() {
                const auto& defaultPrecision { std::cout.precision()};
                std::cout << std::fixed;
                std::cout << std::setprecision(2);

                std::cout << "FROM:info@karate.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirana vam je thenika " << tehnika.getNaziv();
                std::cout << " za " << pojas << " pojas. Dosadasnji uspjeh(prosjek ocjena) na pojasu " << pojas << " iznosi ";
                std::cout << prosjekPojasa << "a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi ";
                std::cout << getAverageForEveryPojas() << ".\nPozdrav.\nKARATE Team.";
                
                std::cout << std::setprecision(defaultPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();

        if (prosjekPojasa > 4.5) {
            sendSMS(pojas, prosjekPojasa);
        }
    }

    void sendSMS(const Pojas& pojas, const double prosjekPojasa) {
        // Svaka cast za uspjeh 4.D na X pojasu
        std::thread smsThread{
            [&]() {
                const auto& defaultPrecision { std::cout.precision()};
                std::cout << std::fixed;
                std::cout << std::setprecision(2);

                std::cout << "Svaca cast za uspjeh " << prosjekPojasa << " na " << pojas << " pojasu\n";

                std::cout << std::setprecision(defaultPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        smsThread.join();
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Za sta se koriste modovi ios::ate i ios::trunc ?\n";
    return "Odgovor -> ios::ate nakon sto se otvori stream postavlja poziciju unosa odma na kraj tog stream-a."
        "ios::trunc ce izbrisati sta god se nalazilo u stream-u prije nego sto se otvorio, moze se zamisliti da se "
        "radi sa praznim stream-om.";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasniti ulogu i nacin koristenja iteratora?\n";
    return "Odgovor -> iteratori su najcesce objekti koji sluze za pristup nekom elementu container-a i "
        "prolaz kroz neki container (kao sto je std::vector, std::array, std::list itd.). Funkcije kao stu su "
        "std::begin, std::end (i druge) se cesto koriste da se dohvati pocetni i krajnji iterator nekog od prijasnje "
        "navedenih container-a.";
}
void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum temp,
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        //takodjer, izuzetak se baca i u slucaju da se prekoraci maksimalan broj elemenata
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
    ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    //svaka tehnika moze imati vise ocjena i polaze se u vise navrata (istog ili drugog dana)
    //parametri: nazivTehnike, prva ocjena, datum polaganja
    Tehnika choku_zuki("choku_zuki", datum19062021, 5),
        gyaku_zuki("gyaku_zuki", datum20062021, 5),
        kizami_zuki("kizami_zuki", datum30062021, 2),
        oi_zuki("oi_zuki", datum05072021, 5);

    choku_zuki.AddOcjena(&datum05072021, 3);
    choku_zuki.AddOcjena(&datum05072021, 5);

    // ispisuje: naziv tehnike, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu za tu tehniku
    // ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0
    cout << choku_zuki << endl;

    /*
    email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj. zadovoljavati sljedeca pravila:
    - poceti sa jednim brojem nakon cega slijedi donja crtica
    - u imenu posjedovati najmanje 3 karaktera
    - izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od navedenog
    - u prezimenu posjedovati najmanje 3 karaktera
    - znak @
    - domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su oznake .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase KaratePolaznik, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.karate.ba
    */

    if (ValidirajEmail("2_ime.prezime@edu.karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("3_ime_prezime@karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("4_imeprezime@karate.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("8_imeprezime@karate.org"))
        cout << "Email validan" << crt;
    if (!ValidirajEmail("2ime.prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;
    if (!ValidirajEmail("5_ime prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;


    KaratePolaznik* jasmin = new KaratePolaznik("Jasmin Azemovic", "1_jasmin.azemovic@karate.ba", "033 281 172");
    KaratePolaznik* adel = new KaratePolaznik("Adel Handzic", "2_adel_handzic@edu.karate.ba", "033 281 170");
    KaratePolaznik* emailNotValid = new KaratePolaznik("Ime Prezime", "korisnik@karate.ru", "033 281 170");

    /*
    svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
    uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna tehnika za nizi pojas (ne mozemo dodati tehniku za NARANDZASTI ako ne postoji niti jedna tehnika za ZUTI pojas)
    - dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //ne treba dodati kizami_zuki jer ne postoji niti jedna tehnika za ZUTI pojas
    if (jasmin->AddTehniku(NARANDZASTI, kizami_zuki, "Napomena 0"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, gyaku_zuki, "Napomena 1"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, kizami_zuki, "Napomena 2"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, oi_zuki, "Napomena 3"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 4"))
        cout << "Tehnika uspjesno dodan!" << crt;
    //ne treba dodati choku_zuki jer je vec dodana za zuti pojas
    if (!jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 5"))
        cout << "Tehnika NIJE uspjesno dodana!" << crt;

    /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
    FROM:info@karate.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
    Pozdrav.
    KARATE Team.
    ukoliko je prosjek na nivou tog pojasa veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.D na X pojasu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << *jasmin << crt;

    //vraca kolekciju tehnika koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na tehnici
    Kolekcija<Tehnika*, float> jasminUspjeh = (*jasmin)(Datum(18, 06, 2021), Datum(21, 06, 2021));
    for (size_t i = 0; i < jasminUspjeh.getTrenutno(); i++)
        cout << *jasminUspjeh.getElement1(i) << " " << jasminUspjeh.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete emailNotValid;

    cin.get();
    system("pause>0");
}