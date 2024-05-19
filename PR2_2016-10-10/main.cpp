/*
    This exam has me making a lot of assumptions at places, like
    what the output to std::ostream should be, so take it with a
    grain of salt
*/
#include <iostream>

using namespace std;

// Headers I included below
#include<vector>
#include<regex>
#include<string>
#include<array>
#include<numeric>
#include<iomanip>
// Headers I included above

// Functions I defined below
/*
    Here I am making the assumption about the format of the phone number
    since it's not explicitly stated
    I am also making an assumption that in case the phone isn't valid
    inside of Polaznik I have to set it to some invalid state
    So all of this could be entirely wrong
*/
const std::string invalidPhoneNum{ "NOT VALID" };
[[nodiscard]] bool ProvjeriFormatTelefona(const std::string& phoneNum) {
    std::regex phoneNumValidation{ "^\\(061\\)\\d{3}-?\\d{3}$" };

    return std::regex_search(phoneNum, phoneNumValidation);
}

[[nodiscard]] char* getNizKaraktera(const char* const str) {
    if (!str) {
        return nullptr;
    }

    const std::size_t newSize{ std::strlen(str) + 1 };
    char* const newStr{ new char[newSize] {} };

    strcpy_s(newStr, newSize, str);

    return newStr;
}
// Functions I defined above

// Functions I defined below
class Izuzetak;
class Datum;
// Functions I defined above

const char* const crt = "\n---------------------------------------\n";
template<class T1, class T2, int max>
class Kolekcija
{
    T1 _elementi1[max]{};
    T2 _elementi2[max]{};
    int* _trenutno{ new int { 0 } };
// Methods I added below
public:
    Kolekcija() = default;
    Kolekcija(const Kolekcija& kolekcija)
    {
        *_trenutno = kolekcija.GetTrenutno();
        for (int i = 0; i < GetTrenutno(); ++i) {
            _elementi1[i] = kolekcija.GetElement1(i);
            _elementi2[i] = kolekcija.GetElement2(i);
        }
    }

    ~Kolekcija() {
        delete _trenutno;
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        *_trenutno = rhs.GetTrenutno();

        for (int i = 0; i < GetTrenutno(); ++i) {
            _elementi1[i] = rhs.GetElement1(i);
            _elementi2[i] = rhs.GetElement2(i);
        }

        return *this;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (GetTrenutno() == max) {
            throw Izuzetak(
                "Maximalni broj elemenata dostignut",
                Datum(19, 5, 2024),
                89
            );
        }

        _elementi1[GetTrenutno()] = element1;
        _elementi2[GetTrenutno()] = element2;

        ++(*_trenutno);
    }

    [[nodiscard]] const T1& GetElement1(const std::ptrdiff_t index) const {
        if (index < 0 || index >= GetTrenutno()) {
            throw Izuzetak(
                "Index nije validan",
                Datum(19, 5, 2024),
                104
            );
        }

        return _elementi1[index];
    }

    [[nodiscard]] const T2& GetElement2(const std::ptrdiff_t index) const {
        if (index < 0 || index >= GetTrenutno()) {
            throw Izuzetak(
                "Index nije validan",
                Datum(19, 5, 2024),
                116
            );
        }

        return _elementi2[index];
    }

    [[nodiscard]] T1& GetElement1(const std::ptrdiff_t index) {
        if (index < 0 || index >= GetTrenutno()) {
            throw Izuzetak(
                "Index nije validan",
                Datum(19, 5, 2024),
                128
            );
        }

        return _elementi1[index];
    }

    [[nodiscard]] T2& GetElement2(const std::ptrdiff_t index) {
        if (index < 0 || index >= GetTrenutno()) {
            throw Izuzetak(
                "Index nije validan",
                Datum(19, 5, 2024),
                140
            );
        }

        return _elementi2[index];
    }

    [[nodiscard]] int GetTrenutno() const noexcept {
        return *_trenutno;
    }

    [[nodiscard]] int GetMax() const noexcept {
        return max;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kolekcija& kolekcija) {
        for (int i = 0; i < kolekcija.GetTrenutno(); ++i) {
            os << kolekcija.GetElement1(i) << ' ' << kolekcija.GetElement2(i);

            if (i + 1 != kolekcija.GetTrenutno()) {
                os << '\n';
            }
        }

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
    friend ostream& operator<< (ostream& COUT, Datum& obj)
    {
        COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
        return COUT;
    }

    // Methods I added below

    Datum(const Datum& datum)
        : _dan{ new int { datum.getDan() } }
        , _mjesec{ new int { datum.getMjesec() } }
        , _godina{ new int { datum.getGodina() } }
    {}

    Datum& operator=(const Datum& rhs) noexcept {
        *_dan = rhs.getDan();
        *_mjesec = rhs.getMjesec();
        *_godina = rhs.getGodina();

        return *this;
    }

    Datum& operator=(Datum&& rhs) noexcept {
        const int tempDan{ rhs.getDan() };
        const int tempMjesec{ rhs.getMjesec() };
        const int tempGodina{ rhs.getGodina() };

        *rhs._dan = 1;
        *rhs._mjesec = 1;
        *rhs._godina = 2000;

        *_dan = tempDan;
        *_mjesec = tempMjesec;
        *_godina = tempGodina;

        return *this;
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

    [[nodiscard]] bool operator>=(const Datum& rhs) const noexcept {
        return getDatumAsDays() >= rhs.getDatumAsDays();
    }

    [[nodiscard]] bool operator<=(const Datum& rhs) const noexcept {
        return getDatumAsDays() <= rhs.getDatumAsDays();
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

    friend ostream& operator<< (ostream& os, const Datum& datum) {
        os << datum.getDan() << " " << datum.getMjesec() << " " << datum.getGodina();

        return os;
    }
};

class Izuzetak :public exception
{
    Datum _datum;//KORISTITE DANASNJI DATUM
    string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
    int _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK

    // Methods I added below
public:
    Izuzetak(const std::string& funkcija, const Datum& datum, const int linija)
        : _funkcija{ funkcija }
        , _datum { datum }
        , _linija { linija }
    {}

    [[nodiscard]] const Datum& getDatumBacanja() const noexcept {
        return _datum;
    }

    [[nodiscard]] const std::string& getFunkcija() const noexcept {
        return _funkcija;
    }

    [[nodiscard]] int getLinijaBacanja() const noexcept {
        return _linija;
    }

    [[nodiscard]] const char* what() const noexcept {
        return getFunkcija().c_str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Izuzetak& izuzetak) {
        os << izuzetak.what();

        return os;
    }
};

enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
// Functions I defined below
std::ostream& operator<<(std::ostream& os, const enumKursevi& kurs) {
    switch (kurs) {
    case enumKursevi::HtmlCSSJavaScript:
        os << "HtmlCSSJavaScript";
        break;    
    case enumKursevi::SoftwareEngeneeringFundamentals:
        os << "SoftwareEngeneeringFundamentals";
        break;    
    case enumKursevi::MasteringSQL:
        os << "MasteringSQL";
        break;    
    case enumKursevi::WindowsSecurity:
        os << "WindowsSecurity";
        break;
    default:
        os << "Kurs ne postoji\n";
    }

    return os;
}
// Functions I defined above
class Kurs
{
    enumKursevi _kurs{ enumKursevi::HtmlCSSJavaScript };
    Datum _pocetak;
    Datum _kraj;
    char* _imePredavaca{ nullptr };
    
    // Methods I defined below
public:
    Kurs() = default;

    Kurs(
        const enumKursevi& kurs, 
        const char* const imePrezime, 
        const Datum& pocetak, 
        const Datum& kraj
    )
        : _kurs { kurs }
        , _pocetak { pocetak }
        , _kraj { kraj }
        , _imePredavaca { getNizKaraktera(imePrezime) }
    {}

    ~Kurs() {
        delete[] _imePredavaca;
    }

    Kurs(const Kurs& kurs)
        : _kurs{ kurs.getKurs() }
        , _pocetak{ kurs.getPocetak() }
        , _kraj{ kurs.getKraj() }
        , _imePredavaca{ getNizKaraktera(kurs.getImePredavaca()) }
    {}

    Kurs& operator=(const Kurs& rhs) {
        _kurs = rhs.getKurs();

        char* const tempImePredavaca{ getNizKaraktera(rhs.getImePredavaca()) };
        Datum tempPocetak{ rhs.getPocetak() };
        Datum tempKraj{ rhs.getKraj() };

        delete[] _imePredavaca;

        _imePredavaca = tempImePredavaca;
        _pocetak = std::move(tempPocetak);
        _kraj = std::move(tempKraj);

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kurs& kurs) {
        os << "Naziv predavaca: " << std::quoted(kurs.getImePredavaca()) << '\n';
        os << "Kurs: " << kurs.getKurs() << '\n';
        os << "Kurs traje od \"" << kurs.getPocetak() << "\" do \"" << kurs.getKraj() << "\"";

        return os;
    }

    [[nodiscard]] bool daLiSeVrijemeOdrzavanjaPopudara(const Kurs& kurs) const noexcept {
        return getPocetak() <= kurs.getKraj() && kurs.getPocetak() <= getKraj();
    }

    [[nodiscard]] bool operator==(const Kurs& rhs) const noexcept {
        return !std::strcmp(getImePredavaca(), rhs.getImePredavaca())
            && getPocetak() == rhs.getPocetak()
            && getKraj() == rhs.getKraj()
            && getKurs() == rhs.getKurs();
    }

    [[nodiscard]] bool operator!=(const Kurs& rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] const enumKursevi& getKurs() const noexcept {
        return _kurs;
    }

    [[nodiscard]] const Datum& getPocetak() const noexcept {
        return _pocetak;
    }

    [[nodiscard]] const Datum& getKraj() const noexcept {
        return _kraj;
    }

    [[nodiscard]] const char* getImePredavaca() const noexcept {
        return _imePredavaca;
    }
};
class Polaznik
{
    static int ID;
    const int _polaznikID;
    //SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
    char* _imePrezime;
    string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
    Kolekcija<Kurs*, int, 10> _uspjesnoOkoncaniKursevi;
    //INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:
    Polaznik(const char* const imePrezime, string telefon) : _polaznikID(ID++)
    {
        _imePrezime = getNizKaraktera(imePrezime);
        _kontaktTelefon = (ProvjeriFormatTelefona(telefon))? telefon : invalidPhoneNum;
    }
    ~Polaznik()
    {
        delete[] _imePrezime; _imePrezime = nullptr;
        for (int i = 0; i < _uspjesnoOkoncaniKursevi.GetTrenutno(); ++i)
        {
            delete _uspjesnoOkoncaniKursevi.GetElement1(i);
            _uspjesnoOkoncaniKursevi.GetElement1(i) = nullptr;
        }
    }

    // Methods I added below
    Polaznik(const Polaznik& polaznik)
        : _polaznikID{ polaznik.getID() }
        , _imePrezime{ getNizKaraktera(polaznik.getImePrezime()) }
        , _kontaktTelefon{ polaznik.getKontaktTelefon() }
        , _uspjesnoOkoncaniKursevi { polaznik.getUspjesnoOkoncaniKurseviCopy() }
    {}

    Polaznik& operator=(const Polaznik& rhs) {
        char* const tempImePrezime{ getNizKaraktera(rhs.getImePrezime()) };
        std::string tempTelefon{ rhs.getKontaktTelefon() };
        auto tempKursevi{ rhs.getUspjesnoOkoncaniKurseviCopy() };

        delete[] _imePrezime;

        _imePrezime = tempImePrezime;
        _kontaktTelefon = std::move(_kontaktTelefon);
        _uspjesnoOkoncaniKursevi = tempKursevi;

        return *this;
    }

    [[nodiscard]] bool daLiSuPolagaliIsteKurseve(
        const Kolekcija<Kurs*, int, 10>& okoncaniKursevi
    ) const noexcept {
        if (okoncaniKursevi.GetTrenutno() != _uspjesnoOkoncaniKursevi.GetTrenutno()) {
            return false;
        }

        for (int i = 0; i < okoncaniKursevi.GetTrenutno(); ++i) {
            if (*okoncaniKursevi.GetElement1(i) != *_uspjesnoOkoncaniKursevi.GetElement1(i)) {
                return false;
            } else if (okoncaniKursevi.GetElement2(i) != _uspjesnoOkoncaniKursevi.GetElement2(i)) {
                return false;
            }

        }

        return true;
    }

    void dodajUspjenoOkoncaniKurs(const Kurs& kurs, const int procenat) {
        _uspjesnoOkoncaniKursevi.AddElement(new Kurs{ kurs }, procenat);
    }

    [[nodiscard]] static bool daLiJeProcenatProlazni(const int procenat) noexcept {
        return procenat >= 55 && procenat <= 100;
    }

    [[nodiscard]] bool operator==(const Polaznik& rhs) const noexcept {
        return !std::strcmp(getImePrezime(), rhs.getImePrezime())
            && daLiSuPolagaliIsteKurseve(rhs.getUspjenoOkoncaniKursevi());
    }

    [[nodiscard]] Kolekcija<Kurs*, int, 10> getUspjesnoOkoncaniKurseviCopy() const noexcept {
        Kolekcija<Kurs*, int, 10> temp{};

        for (int i = 0; i < _uspjesnoOkoncaniKursevi.GetTrenutno(); ++i) {
            temp.AddElement(
                new Kurs{ *_uspjesnoOkoncaniKursevi.GetElement1(i) },
                _uspjesnoOkoncaniKursevi.GetElement2(i)
            );
        }

        return temp;
    }
     
    friend std::ostream& operator<<(std::ostream& os, const Polaznik& polaznik) {
        os << "ID polaznika: " << polaznik.getID() << '\n';
        os << "Ime prezime: " << std::quoted(polaznik.getImePrezime()) << '\n';
        os << "Kontakt telefona: " << std::quoted(polaznik.getKontaktTelefon()) << '\n';
        os << "Okoncani kursevi - procenat prolaza:\n";

        const auto& kursevi{ polaznik.getUspjenoOkoncaniKursevi() };

        for (int i = 0; i < kursevi.GetTrenutno(); ++i) {
            os << *kursevi.GetElement1(i) << " - ";
            os << kursevi.GetElement2(i);

            if (i + 1 != kursevi.GetTrenutno()) {
                os << '\n';
            }
        }

        return os;
    }

    [[nodiscard]] int getID() const noexcept {
        return _polaznikID;
    }

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] const std::string& getKontaktTelefon() const noexcept {
        return _kontaktTelefon;
    }
    
    [[nodiscard]] const Kolekcija<Kurs*, int, 10>& getUspjenoOkoncaniKursevi() const noexcept {
        return _uspjesnoOkoncaniKursevi;
    }
};
int Polaznik::ID{ 1 };
class SkillsCentar
{
    string _nazivCentra;
    vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
    Kolekcija<Kurs, Polaznik*, 150> _aplikanti;
public:
    SkillsCentar(string naziv) { _nazivCentra = naziv; }
    //SkillsCentar(const SkillsCentar& obj) :_kursevi(obj._kursevi), _aplikanti(obj._aplikanti)
    //{
    //    _nazivCentra = obj._nazivCentra;
    //}
    // Decided to make my own copy ctor

    // Methods I added below
    SkillsCentar(const SkillsCentar& skillsCentar)
        : _nazivCentra { skillsCentar.getNazivCentra() }
        , _kursevi { skillsCentar.getKursevi() }
        , _aplikanti { skillsCentar.getAplikantiCopy() }
    {}

    SkillsCentar& operator=(const SkillsCentar& rhs) {
        std::string tempNaziv{ rhs.getNazivCentra() };
        std::vector<Kurs> tempKursevi{ rhs.getKursevi() };
        Kolekcija<Kurs, Polaznik*, 150> tempAplikanti{ rhs.getAplikantiCopy() };

        _nazivCentra = std::move(tempNaziv);
        _kursevi = std::move(tempKursevi);
        _aplikanti = tempAplikanti;

        return *this;
    }

    ~SkillsCentar() {
        for (int i = 0; i < _aplikanti.GetTrenutno(); ++i) {
            delete _aplikanti.GetElement2(i);
        }
    }

    [[nodiscard]] const std::string& getNazivCentra() const noexcept {
        return _nazivCentra;
    }

    [[nodiscard]] const std::vector<Kurs>& getKursevi() const noexcept {
        return _kursevi;
    }

    [[nodiscard]] const Kolekcija<Kurs, Polaznik*, 150>& getAplikanti() const noexcept {
        return _aplikanti;
    }

    [[nodiscard]] Kolekcija<Kurs, Polaznik*, 150> getAplikantiCopy() const noexcept {
        Kolekcija<Kurs, Polaznik*, 150> temp;

        for (int i = 0; i < _aplikanti.GetTrenutno(); ++i) {
            temp.AddElement(
                _aplikanti.GetElement1(i),
                new Polaznik{ *_aplikanti.GetElement2(i) }
            );
        }

        return temp;
    }

    [[nodiscard]] bool ProvjeriKoliziju(const Kurs& kursZaProvjeriti) const noexcept {
        for (const auto& kurs : _kursevi) {
            if (kurs.daLiSeVrijemeOdrzavanjaPopudara(kursZaProvjeriti)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool daLiKursPostojiUKursevima(const Kurs& kurs) const noexcept {
        auto kursZaPronaci{ 
            std::find(std::begin(_kursevi), std::end(_kursevi), kurs) 
        };

        return kursZaPronaci != std::end(_kursevi);
    }

    [[nodiscard]] bool daLiKursIPolaznikPostojiUAplikantima(
        const Kurs& kurs, 
        const Polaznik& polaznik
    ) const noexcept {
        for (int i = 0; i < _aplikanti.GetTrenutno(); ++i) {
            if (kurs == _aplikanti.GetElement1(i) && polaznik == *_aplikanti.GetElement2(i)) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] bool daLiKursPostojiUAplikantima(const Kurs& kurs) const noexcept {
        for (int i = 0; i < _aplikanti.GetTrenutno(); ++i) {
            if (kurs == _aplikanti.GetElement1(i)) {
                return true;
            }
        }

        return false;
    }

    void AddKurs(const Kurs& kurs) {
        if (daLiKursPostojiUKursevima(kurs)) {
            throw Izuzetak(
                "Dupliranje kurseva nije dozvoljeno",
                Datum(19, 4, 2024),
                661
            );
        }

        _kursevi.push_back(kurs);
    }

    void AddAplikaciju(const Kurs& kurs, const Polaznik& polaznik) {
        if (daLiKursIPolaznikPostojiUAplikantima(kurs, polaznik)) {
            throw Izuzetak(
                "Dupliranje kurseva kod aplikacija nije dozvoljeno",
                Datum(19, 4, 2024),
                673
            );
        }
        else if (!daLiKursPostojiUKursevima(kurs)) {
            return;
        }

        _aplikanti.AddElement(kurs, new Polaznik{ polaznik });
    }

    void removeKurs(const Kurs& kurs) noexcept {
        auto kursToRemove{
            std::find(std::begin(_kursevi), std::end(_kursevi), kurs)
        };

        if (kursToRemove == std::end(_kursevi)) {
            return;
        }

        _kursevi.erase(kursToRemove);
    }

    [[nodiscard]] bool RemoveKurs(const Kurs& kurs) noexcept {
        if (daLiKursPostojiUAplikantima(kurs)) {
            return false;
        }

        removeKurs(kurs);
        return true;
    }

    [[nodiscard]] Polaznik* getPolaznikWithId(const int idPolaznika) noexcept {
        for (int i = 0; i < _aplikanti.GetTrenutno(); ++i) {
            auto trenutniPolaznik{ _aplikanti.GetElement2(i) };

            if (trenutniPolaznik->getID() == idPolaznika) {
                return trenutniPolaznik;
            }
        }

        return nullptr;
    }

    void DodajUspjesnoOkoncanKurs(const int idPolaznika, const Kurs& kurs, const int procenat) {
        if (!Polaznik::daLiJeProcenatProlazni(procenat)) {
            return;
        }

        auto polaznik{ getPolaznikWithId(idPolaznika) };

        if (!polaznik) {
            return;
        }

        polaznik->dodajUspjenoOkoncaniKurs(kurs, procenat);
    }

    [[nodiscard]] std::vector<Polaznik> GetPolazniciByPredavac(
        const std::string& imePredavaca,
        const enumKursevi& kurs
    ) const noexcept {
        std::vector<Polaznik> temp{};

        for (int i = 0; i < _aplikanti.GetTrenutno(); ++i) {
            const auto& trenutniKurs{ _aplikanti.GetElement1(i) };

            if (trenutniKurs.getKurs() == kurs && trenutniKurs.getImePredavaca() == imePredavaca) {
                temp.push_back(*_aplikanti.GetElement2(i));
            }
        }

        return temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const SkillsCentar& skillsCentar) {
        os << "Naziv centra: " << std::quoted(skillsCentar.getNazivCentra()) << '\n';
        os << "Kursevi:\n";
        const auto& kursevi{ skillsCentar.getKursevi() };
        for (const auto& kurs : kursevi) {
            os << kurs << '\n';
        }

        os << "Aplikanti:\n";
        const auto& aplikanti{ skillsCentar.getAplikanti() };
        for (int i = 0; i < aplikanti.GetTrenutno(); ++i) {
            os << aplikanti.GetElement1(i) << '\n';
            os << *aplikanti.GetElement2(i) << '\n';

            if (i + 1 != aplikanti.GetTrenutno()) {
                os << '\n';
            }
        }

        return os;
    }
};
void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
    //    RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
    // 3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
    // 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U
    //    TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE,
    //    POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
    // 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
    ****************************************************************************/

#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
    Kolekcija<int, int, 10> kolekcija1;
    try
    {
        for (size_t i = 0; i < kolekcija1.GetMax(); i++)
            kolekcija1.AddElement(i, i + 2);
        //FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
        cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
        // cout << kolekcija1.GetElement1(20) << " " << kolekcija1.GetElement2(20) << endl;
        //FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
    }
    catch (Izuzetak& err)
    {
        cout << "Greska -> " << err << endl;
    }

    cout << kolekcija1 << endl;
    Kolekcija<int, int, 10> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;
    Kolekcija<int, int, 10> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeKursa
    Kurs sef(SoftwareEngeneeringFundamentals, "Jasmin Azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
    cout << sef << endl;
    Kurs msql(MasteringSQL, "Adel Handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
    sef = msql;
    if (sef == msql)//KURSEVI SU ISTI AKO POSJEDUJU IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
        cout << "ISTI SU KURSEVI" << endl;
    Kurs msql2(msql);
    cout << msql2 << endl;
#pragma endregion

#pragma region TestiranjePolaznika
    string telefon1 = "(061)111-111";
    string telefon2 = "(061)111222";
    string telefon3 = "(061)111-333";

    if (!ProvjeriFormatTelefona(telefon1))
        cout << "Broj " << telefon1 << " nije validan" << endl;
    if (!ProvjeriFormatTelefona(telefon2))
        cout << "Broj " << telefon2 << " nije validan" << endl;
    if (!ProvjeriFormatTelefona(telefon3))
        cout << "Broj " << telefon3 << " nije validan" << endl;


    Polaznik denis("Denis Music", telefon1);
    Polaznik denis2("Denis2 Music2", telefon3);

#pragma endregion

#pragma region TestiranjeCentra
    try
    {
        SkillsCentar mostar("Skills Center Mostar");
        if (mostar.ProvjeriKoliziju(sef)) //JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA I
            mostar.AddKurs(sef);          //KURSA SE NE SMIJE POKLAPAT
        if (mostar.ProvjeriKoliziju(msql))
            mostar.AddKurs(msql);
        if (mostar.ProvjeriKoliziju(msql2))
            mostar.AddKurs(msql2);
        //ONEMOGUCITI DODAVANJE IDENTICNIH KURSEVA. FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO SE POKUSA DODATI IDENTICAN KURS
        mostar.AddAplikaciju(sef, denis);
        //ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
        mostar.AddAplikaciju(msql, denis);
        mostar.AddAplikaciju(msql, denis);
        //ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
        cout << denis2 << endl;
        denis2 = denis;
        if (denis == denis2) //POLAZNICI SU ISTI AKO POSJEDUJU ISTO IME I AKO SU POHADJALI ISTE KURSEVE
            cout << "ISTI SU" << endl;

        mostar.DodajUspjesnoOkoncanKurs(1, sef, 60);
        // BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU 
        // DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE 
        // POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
        mostar.DodajUspjesnoOkoncanKurs(1, msql, 83);
        vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);
        //VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS

        if (mostar.RemoveKurs(sef))//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
            cout << "Kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;

        SkillsCentar sarajevo = mostar;
        cout << sarajevo << endl;
    }
    catch (Izuzetak& err)
    {
        cout << err << endl;
    }
#pragma endregion
    system("pause");
}