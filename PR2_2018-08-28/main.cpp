#include <iostream>
using namespace std;

// Headers I included below
#include<vector>
#include<array>
#include<numeric>
#include<string>
#include<thread>
#include<sstream>
#include<memory>
#include<iomanip>
// Headers I included above

#pragma warning(disable:4996)
const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
const float minimalan_prosjek = 4.5;

// Functions I defined below
std::ostream& operator<<(std::ostream& os, const eRazred& razred) {
    switch (razred) {
    case eRazred::PRVI:
        os << "PRVI";
        break;
    case eRazred::DRUGI:
        os << "DRUGI";
        break;
    case eRazred::TRECI:
        os << "TRECI";
        break;
    case eRazred::CETVRTI:
        os << "CETVRTI";
        break;
    default:
        os << "Razred ne postoji";
    }

    return os;
}
// Functions I defined above

char* AlocirajNizKaraktera(const char* sadrzaj)
{
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1{ nullptr };
    T2* _elementi2{ nullptr };
    int* _trenutno;
public:
    Kolekcija()
    {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = new int(0);
    }
    ~Kolekcija()
    {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
    int getTrenutno() { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, Kolekcija& obj)
    {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below
    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno { new int { kolekcija.getTrenutno() } }
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

        *_trenutno = rhs.getTrenutno();

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = new T1[getTrenutno()]{};
        _elementi2 = new T2[getTrenutno()]{};

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = rhs.getElement1(i);
            _elementi2[i] = rhs.getElement2(i);
        }

        return *this;
    }

    [[nodiscard]] int getTrenutno() const noexcept { 
        return *_trenutno; 
    }

    [[nodiscard]] const T1& getElement1(const int lokacija) const noexcept { 
        return _elementi1[lokacija]; 
    }

    [[nodiscard]] const T2& getElement2(const int lokacija) const noexcept { 
        return _elementi2[lokacija]; 
    }

    void AddElement(const T1& element1, const T2& element2) {
        T1* const temp1{ new T1[getTrenutno() + 1]{} };
        T2* const temp2{ new T2[getTrenutno() + 1]{} };

        for (int i = 0; i < getTrenutno(); ++i) {
            temp1[i] = getElement1(i);
            temp2[i] = getElement2(i);
        }

        temp1[getTrenutno()] = element1;
        temp2[getTrenutno()] = element2;

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = temp1;
        _elementi2 = temp2;

        ++(*_trenutno);
    }

    void SortOpadajuciByT2() {
        bool continueSorting{};
        int size{ getTrenutno() };

        do {
            continueSorting = false;

            for (int i = 0; i < size - 1; ++i) {
                continueSorting = swapFunction(i, i + 1);
            }

            --size;
        } while (continueSorting);
    }

private:
    bool swapFunction(const int index1, const int index2) {
        auto& el1{ getElement2(index1) };
        auto& el2{ getElement2(index2) };

        if (el1 < el2) {
            std::swap(el1, el2);
            std::swap(getElement1(index1), getElement1(index2));
            return true;
        }

        return false;
    }
};

class DatumVrijeme
{
    int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
    DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0)
    {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
        _sati = new int(sati);
        _minuti = new int(minuti);
    }
    ~DatumVrijeme()
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
        delete _sati; _sati = nullptr;
        delete _minuti; _minuti = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj)
    {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
        return COUT;
    }

    // Methods I added below
    DatumVrijeme(const DatumVrijeme& datumVrijeme)
        : _dan { new int { datumVrijeme.getDan() } }
        , _mjesec { new int { datumVrijeme.getMjesec() } }
        , _godina { new int { datumVrijeme.getGodina() } }
        , _sati { new int { datumVrijeme.getSati() } }
        , _minuti { new int { datumVrijeme.getMinuti() } }
    {}

    DatumVrijeme& operator=(const DatumVrijeme& rhs) {
        *_dan = rhs.getDan();
        *_mjesec = rhs.getMjesec();
        *_godina = rhs.getGodina();
        *_sati = rhs.getSati();
        *_minuti = rhs.getMinuti();

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

    [[nodiscard]] int getSati() const noexcept {
        return *_sati;
    }

    [[nodiscard]] int getMinuti() const noexcept {
        return *_minuti;
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

    [[nodiscard]] int64_t getTimeAsMinute() const noexcept {
        return getSati() * 60 + getMinuti();
    }

    [[nodiscard]] static int64_t getDaysAsMinute(const int64_t days) noexcept {
        return days * 24 * 60;
    }

    [[nodiscard]] int64_t getDatumVrijemeAsMinuti() const noexcept {
        return getTimeAsMinute() + getDaysAsMinute(getDatumAsDays());
    }

    [[nodiscard]] std::unique_ptr<char[]> ToCharArray() const noexcept {
        std::ostringstream datumVrijemeBuffer{};

        //5.7.2018 12:31
        datumVrijemeBuffer << getDan() << '.' << getMjesec() << '.' << getGodina() << ' ';
        datumVrijemeBuffer << std::setw(2) << std::setfill('0') << getSati() << ':';
        datumVrijemeBuffer << std::setw(2) << std::setfill('0') << getMinuti();

        return std::unique_ptr<char[]>(AlocirajNizKaraktera(datumVrijemeBuffer.str().c_str()));
    }

    [[nodiscard]] int64_t operator-(const DatumVrijeme& rhs) const noexcept {
        return getDatumVrijemeAsMinuti() - rhs.getDatumVrijemeAsMinuti();
    }
};

class Predmet
{
    char* _naziv;
    int _ocjena;
    string _napomena;
public:
    Predmet(const char* naziv, int ocjena, string napomena = "") :_ocjena(ocjena), _napomena(napomena)
    {
        _naziv = AlocirajNizKaraktera(naziv);
    }
    ~Predmet()
    {
        delete[] _naziv; _naziv = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Predmet& obj)
    {
        COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
        return COUT;
    }
    char* GetNaziv() { return _naziv; }
    string GetNapomena() { return _napomena; }
    void DodajNapomenu(string napomena)
    {
        _napomena += " " + napomena;
    }

    // Methods I added below
    Predmet(const Predmet& predmet)
        : _naziv { AlocirajNizKaraktera(predmet.getNaziv()) }
        , _ocjena { predmet.getOcjena() }
        , _napomena{ predmet.getNapomena() }
    {}

    Predmet& operator=(const Predmet& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _naziv;

        _naziv = AlocirajNizKaraktera(rhs.getNaziv());
        _ocjena = rhs.getOcjena();
        _napomena = rhs.getNapomena();

        return *this;
    }

    [[nodiscard]] const char* getNaziv() const noexcept { 
        return _naziv; 
    }
    
    [[nodiscard]] const std::string& getNapomena() const noexcept { 
        return _napomena; 
    }

    [[nodiscard]] int getOcjena() const noexcept {
        return _ocjena;
    }

    [[nodiscard]] bool operator==(const Predmet& rhs) const noexcept {
        return !std::strcmp(getNaziv(), rhs.getNaziv())
            && getOcjena() == rhs.getOcjena()
            && getNapomena() == rhs.getNapomena();
    }

    [[nodiscard]] bool operator!=(const Predmet& rhs) const noexcept {
        return !(*this == rhs);
    }
};
struct Uspjeh
{
    eRazred _razred;
    //datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
    Kolekcija<Predmet*, DatumVrijeme>* _predmeti;
public:
    Uspjeh(eRazred razred) :_razred(razred), _predmeti(new Kolekcija<Predmet*, DatumVrijeme>{})
    {}
    ~Uspjeh()
    {
        for (int i = 0; i < _predmeti->getTrenutno(); ++i) {
            delete _predmeti->getElement1(i);
        }
        delete _predmeti; _predmeti = nullptr;
    }

    Kolekcija<Predmet*, DatumVrijeme>* GetPredmeti() { return _predmeti; }

    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj)
    {
        COUT << obj._razred << '\n';
        const auto& predmeti{ obj.getPredmeti() };
        for (int i = 0; i < predmeti.getTrenutno(); ++i) {
            COUT << *predmeti.getElement1(i) << ' ';
            COUT << predmeti.getElement2(i) << '\n';
        }
        COUT << '\n';
        return COUT;
    }

    // Methods I added below
    Uspjeh(const Uspjeh& uspjeh)
        : _razred { uspjeh.getRazred() }
        , _predmeti{ uspjeh.getPredmetiCopy() }
    {}

    Uspjeh(const eRazred& razred, const Predmet& predmet, const DatumVrijeme& datumVrijeme)
        : _razred{ razred }
        , _predmeti{ new Kolekcija<Predmet*, DatumVrijeme>{} }
    {
        dodajPredmet(predmet, datumVrijeme);
    }

    Uspjeh& operator=(const Uspjeh& rhs) {
        if (this == &rhs) {
            return *this;
        }

        for (int i = 0; i < _predmeti->getTrenutno(); ++i) {
            delete _predmeti->getElement1(i);
        }
        delete _predmeti;

        _razred = rhs.getRazred();
        _predmeti = rhs.getPredmetiCopy();

        return *this;
    }

    [[nodiscard]] const eRazred& getRazred() const noexcept {
        return _razred;
    }

    [[nodiscard]] const Kolekcija<Predmet*, DatumVrijeme>& getPredmeti() const noexcept { 
        return *_predmeti; 
    }

    [[nodiscard]] Kolekcija<Predmet*, DatumVrijeme>* getPredmetiCopy() const {
        Kolekcija<Predmet*, DatumVrijeme>* temp{
            new Kolekcija<Predmet*, DatumVrijeme>{}
        };

        for (int i = 0; i < _predmeti->getTrenutno(); ++i) {
            temp->AddElement(
                new Predmet{ *_predmeti->getElement1(i) },
                _predmeti->getElement2(i)
            );
        }

        return temp;
    }

    [[nodiscard]] int getBrojPredmeta() const noexcept {
        return _predmeti->getTrenutno();
    }

    [[nodiscard]] bool daLiPredmetPostoji(const Predmet& predmet) const noexcept {
        for (int i = 0; i < _predmeti->getTrenutno(); ++i) {
            if (predmet == *_predmeti->getElement1(i)) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _predmeti->getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < _predmeti->getTrenutno(); ++i) {
            sum += _predmeti->getElement1(i)->getOcjena();
        }

        return sum / size;
    }

    [[nodiscard]] bool daLiJeDovoljnoVremenaProsloOdZadnjegDodavanja(const DatumVrijeme& datumVrijeme) const noexcept {
        const int size{ _predmeti->getTrenutno() };

        if (!size) {
            return true;
        }

        const auto& zadnjeVrijeme{ _predmeti->getElement2(size - 1) };

        return (datumVrijeme - zadnjeVrijeme) >= 1;
    }

    void dodajPredmet(const Predmet& predmet, const DatumVrijeme& datumVrijeme) {
        _predmeti->AddElement(
            new Predmet{ predmet },
            datumVrijeme
        );
    }
};

class Kandidat
{
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh*> _uspjeh;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona)
        : _emailAdresa(emailAdresa), _brojTelefona(brojTelefona)
    {
        _imePrezime = AlocirajNizKaraktera(imePrezime);
    }
    ~Kandidat()
    {
        delete[] _imePrezime; _imePrezime = nullptr;
        for (size_t i = 0; i < _uspjeh.size(); i++)
        {
            delete _uspjeh[i];
            _uspjeh[i] = nullptr;
        }
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj)
    {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << *obj._uspjeh[i] << endl;
        return COUT;
    }
    vector<Uspjeh*> GetUspjeh() { return _uspjeh; }


    // Methods I added below
    Kandidat(const Kandidat& kandidat) 
        : _imePrezime { AlocirajNizKaraktera(kandidat.getImePrezime()) }
        , _emailAdresa { kandidat.getEmailAdresa() }
        , _brojTelefona { kandidat.getBrojTelefona() }
        , _uspjeh { kandidat.getUspjehCopy() }
    {}

    Kandidat& operator=(const Kandidat& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _imePrezime;
        for (const auto& uspjeh : _uspjeh) {
            delete uspjeh;
        }

        _imePrezime = AlocirajNizKaraktera(rhs.getImePrezime());
        _emailAdresa = rhs.getEmailAdresa();
        _brojTelefona = rhs.getBrojTelefona();
        _uspjeh = rhs.getUspjehCopy();

        return *this;
    }

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] const std::string& getEmailAdresa() const noexcept {
        return _emailAdresa;
    }

    [[nodiscard]] const std::string& getBrojTelefona() const noexcept {
        return _brojTelefona;
    }
  
    [[nodiscard]] const std::vector<Uspjeh*>& getUspjeh() const noexcept { 
        return _uspjeh; 
    }

    [[nodiscard]] std::vector<Uspjeh*> getUspjehCopy() const noexcept {
        std::vector<Uspjeh*> temp{};

        for (const auto& uspjeh : _uspjeh) {
            temp.push_back(new Uspjeh{ *uspjeh });
        }

        return temp;
    }

    [[nodiscard]] Uspjeh* getUspjehForRazred(const eRazred& razred) noexcept {
        auto uspjehZaPronaci{
            std::find_if(
                std::begin(_uspjeh),
                std::end(_uspjeh),
                [&](const Uspjeh* const uspjeh) {
                        return uspjeh->getRazred() == razred;
                }
            )
        };

        return (uspjehZaPronaci == std::end(_uspjeh)) ? nullptr : *uspjehZaPronaci;
    }

    [[nodiscard]] Uspjeh* operator()(const eRazred& razred) noexcept {
        return getUspjehForRazred(razred);
    }

    bool AddPredmet(const eRazred& razred, const Predmet& predmet, const DatumVrijeme& datumVrijeme) {
        auto uspjeh{ getUspjehForRazred(razred) };

        if (uspjeh) {
            if (uspjeh->getBrojPredmeta() == 6) {
                return false;
            }
            else if (uspjeh->daLiPredmetPostoji(predmet)) {
                return false;
            }
            else if (!uspjeh->daLiJeDovoljnoVremenaProsloOdZadnjegDodavanja(datumVrijeme)) {
                return false;
            }

            uspjeh->dodajPredmet(predmet, datumVrijeme);
            sendMail(*uspjeh);
            return true;
        }

        _uspjeh.push_back(new Uspjeh{ razred, predmet, datumVrijeme });
        sendMail(*_uspjeh.back());
        return true;
    }

private:
    void sendMail(const Uspjeh& uspjeh) const {
        std::thread emailThread{
            [&]() {
                std::cout << "Evidentirali ste uspjeh za " << uspjeh.getRazred() << " razred\n";
            }
        };

        emailThread.join();

        if (uspjeh.getAverage() > minimalan_prosjek) {
            sendSMS(uspjeh);
        }
    }

    void sendSMS(const Uspjeh& uspjeh) const {
        std::thread smsThread{
            [&]() {
                const auto& originalPrecision { std::cout.precision()};
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "svaka cast za uspjeh " << uspjeh.getAverage() << '\n';
            
                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        smsThread.join();
    }
};


void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR
    // ÆE BITI OZNACENO KAO "RE"
    // 3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
    // 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM
    // CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE
    // MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
    // 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
    ****************************************************************************/

    DatumVrijeme temp,
        datum19062018_1015(19, 6, 2018, 10, 15),
        datum20062018_1115(20, 6, 2018, 11, 15),
        datum30062018_1215(30, 6, 2018, 12, 15),
        datum05072018_1231(5, 7, 2018, 12, 31),
        datum20062018_1115_Copy(datum20062018_1115);
    //funkcija ToCharArray vraca datum i vrijeme kao char *
    cout << datum19062018_1015.ToCharArray() << endl;//treba ispisati: 19.6.2018 10:15
    temp = datum05072018_1231;
    cout << temp.ToCharArray() << endl;//treba ispisati: 5.7.2018 12:31
    cout << datum20062018_1115_Copy.ToCharArray() << endl;//treba ispisati: 20.6.2018 11:15

    const int kolekcijaTestSize = 10;
    Kolekcija<int, int> kolekcija1;
    for (size_t i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i + 1, i * i);
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    Kolekcija<int, int> kolekcija3;
    kolekcija3 = kolekcija1;
    kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
    cout << kolekcija3 << crt;

    //napomena se moze dodati i prilikom kreiranja objekta
    Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
        Fizika("Fizika", 5),
        Hemija("Hemija", 2),
        Engleski("Engleski", 5);
    Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh"); // dodaje novu napomenu zadrzavajuci ranije dodane
    cout << Matematika << endl;

    Kandidat jasmin("Jasmin Azemovic", "jasmin@gmail.com", "033 281 172");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");

    // uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    // tom prilikom onemoguciti:
    // - dodavanje vise od 6 predmeta za jedan razred
    // - dodavanje istoimenih predmeta na nivou jednog razreda,
    // - dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja 
    // pojedinih predmeta mora biti najmanje minut).
    // razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
    // razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, datum30062018_1215))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, datum19062018_1015))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, datum20062018_1115))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati Matematiku jer je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, datum05072018_1231))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati Fiziku jer nije prosao minut od dodavanja posljednjeg predmeta
    if (jasmin.AddPredmet(PRVI, Fizika, datum05072018_1231))
        cout << "Predmet uspjesno dodan!" << crt;

    // pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
    // upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
    // sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od 
    // minimalan_prosjek kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova 
    // implemenitrati koristeci zasebne thread-ove.


    Uspjeh* u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
    if (u != nullptr) cout << *u << endl;

    system("pause>0");
}