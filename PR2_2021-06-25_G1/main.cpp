#include <iostream>
using namespace std;

// Headers I included below
#include<regex>
#include<string>
#include<thread>
#include<numeric>
#include<array>
#include<vector>
#include<iomanip>
// Headers I included above

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
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };

// Functions I defined below
std::ostream& operator<<(std::ostream& os, eRazred razred) {
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

/*
broj telefona mora biti u formatu
- znak +
- pozivni broj drzave (2 ili 3 cifre)
- pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
- prvi dio broja (2 ili 3 cifre)
- razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
 - drugi dio broja (2 ili 3 cifre)

ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
*/

const std::string invalidPhoneNum{ "NOT VALID" };

[[nodiscard]] bool ValidirajBrojTelefona(const std::string& phoneNum) {
    std::regex phoneNumValidation{ "\\+\\d{2,3}0?6\\d{3,4}[\\s-]?\\d{2,3}" };

    return std::regex_match(phoneNum, phoneNumValidation);
}
// Functions I defined above

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int _trenutno{ 0 };
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _omoguciDupliranje = omoguciDupliranje;
    }
    ~Kolekcija() {
        clearResources();
    }

    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() const { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below
    Kolekcija(const Kolekcija& kolekcija)
        : _omoguciDupliranje { kolekcija.getOmoguciDupliranje() }
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

        _omoguciDupliranje = rhs.getOmoguciDupliranje();
        _trenutno = rhs.getTrenutno();
        clearResources();

        _elementi1 = new T1[getTrenutno()]{};
        _elementi2 = new T2[getTrenutno()]{};

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = rhs.getElement1(i);
            _elementi2[i] = rhs.getElement2(i);
        }

        return *this;
    }

    [[nodiscard]] bool getOmoguciDupliranje() const noexcept {
        return _omoguciDupliranje;
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
        if (!getOmoguciDupliranje() && daLiElementPostoji(element1, element2)) {
            throw std::runtime_error("Dupliranje elemenata nije dozvoljeno");
        }

        T1* const temp1{ new T1[getTrenutno() + 1] {} };
        T2* const temp2{ new T2[getTrenutno() + 1] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            temp1[i] = getElement1(i);
            temp2[i] = getElement2(i);
        }

        temp1[getTrenutno()] = element1;
        temp2[getTrenutno()] = element2;

        clearResources();

        _elementi1 = temp1;
        _elementi2 = temp2;

        ++_trenutno;
    }

    Kolekcija operator()(const int start, const int end) {
        if (start < 0 || start >= getTrenutno()) {
            throw std::runtime_error("Start index nije u validnom intervalu");
        } else if (end < 0 || end >= getTrenutno()) {
            throw std::runtime_error("Start index nije u validnom intervalu");
        }
        
        Kolekcija temp{};

        for (int i = start; i <= end; ++i) {
            temp.AddElement(getElement1(i), getElement2(i));
        }

        return temp;
    }
private:
    void clearResources() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
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
                std::cbegin(daysPerMonth),
                std::cbegin(daysPerMonth) + mjesec - 1,
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

class Predmet {
    char* _naziv;
    Kolekcija<Datum*, int>* _ocjene;
public:
    Predmet(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<Datum*, int>{};
        if (ocjena > 0)
            AddOcjena(datum, ocjena);
    }
    ~Predmet() {
        clearResources();
    }

    char* GetNaziv() { return _naziv; }
    Kolekcija<Datum*, int>* GetOcjene() { return _ocjene; }

    // Methods I added below
    Predmet(const Predmet& predmet)
        : _naziv { GetNizKaraktera(predmet.getNaziv()) }
        , _ocjene { predmet.getOcjeneCopy() }
    {}

    Predmet& operator=(const Predmet& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearResources();

        _naziv = GetNizKaraktera(rhs.getNaziv());
        _ocjene = rhs.getOcjeneCopy();

        return *this;
    }

    [[nodiscard]] bool daLiSuOcjeneIDatumiIsti(
        const Kolekcija<Datum*, int>& ocjene
    ) const noexcept {
        if (ocjene.getTrenutno() != _ocjene->getTrenutno()) {
            return false;
        }
        else if (ocjene.getOmoguciDupliranje() != _ocjene->getOmoguciDupliranje()) {
            return false;
        }
        
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            if (*ocjene.getElement1(i) != *_ocjene->getElement1(i)) {
                return false;
            } else if (ocjene.getElement2(i) != _ocjene->getElement2(i)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool operator==(const Predmet& rhs) const noexcept {
        return !std::strcmp(getNaziv(), rhs.getNaziv())
            && daLiSuOcjeneIDatumiIsti(rhs.getOcjene());
    }

    [[nodiscard]] bool operator!=(const Predmet& rhs) const noexcept {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Predmet& predmet) {
        os << "Naziv: " << std::quoted(predmet.getNaziv()) << '\n';
        os << "Datum - ocjena:\n";

        const auto& ocjene{ predmet.getOcjene() }; 
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << *ocjene.getElement1(i) << " - ";
            os << ocjene.getElement2(i) << '\n';
        }

        const auto& originalPreicision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjecna ocjena -> " << predmet.getAverage();

        os << std::setprecision(originalPreicision);
        os.unsetf(std::ios::fixed);

        return os;
    }

    [[nodiscard]] bool daLiPostojiOcjenaUIntervalu(
        const Datum& pocetak, 
        const Datum& kraj
    ) const noexcept {
        for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
            const auto& trenutniDatum{ *_ocjene->getElement1(i) };

            if (trenutniDatum >= pocetak && trenutniDatum <= kraj) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] float getAverageNumOfDaysBetweenGrades() const noexcept {
        int size{ _ocjene->getTrenutno() - 1 };

        if (size <= 0) {
            return 0.0;
        }

        float sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            const auto& datum1{ *_ocjene->getElement1(i) };
            const auto& datum2{ *_ocjene->getElement1(i + 1) };
            
            sum += std::abs(datum1 - datum2);
        }

        return sum / size;
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

    void AddOcjena(const Datum& datumOcjene, const int ocjena) {
        _ocjene->AddElement(new Datum{ datumOcjene }, ocjena);
    }

    [[nodiscard]] const char* getNaziv() const noexcept { 
        return _naziv; 
    }

    [[nodiscard]] const Kolekcija<Datum*, int>& getOcjene() const noexcept { 
        return *_ocjene; 
    }

    [[nodiscard]] Kolekcija<Datum*, int>* getOcjeneCopy() const {
        Kolekcija<Datum*, int>* temp{ new Kolekcija<Datum*, int> {} };
    
        for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
            temp->AddElement(
                new Datum{ *_ocjene->getElement1(i) },
                _ocjene->getElement2(i)
            );
        }

        return temp;
   }

private:
    void clearResources() {
        delete[] _naziv; _naziv = nullptr;

        for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
            delete _ocjene->getElement1(i);
        }

        delete _ocjene;
    }
};
class Uspjeh {
    eRazred _razred;
    //char* se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet*, const char*> _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
    }
    Kolekcija<Predmet*, const char*> GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << obj._razred << '\n';

        const auto& predmeti{ obj.getPredmeti() };
        for (int i = 0; i < predmeti.getTrenutno(); ++i) {
            COUT << *predmeti.getElement1(i) << '\n';
            COUT << predmeti.getElement2(i) << '\n';
        }

        return COUT;
    }

    // Methods I added below
    Uspjeh(const Uspjeh& uspjeh)
        : _razred { uspjeh.getERazred() }
        , _polozeniPredmeti { uspjeh.getPredmetiCopy() }
    {}

    Uspjeh(eRazred razred, const Predmet& predmet, const char* const napomena)
        : _razred { razred }
    {
        dodajPredmetINapomenu(predmet, napomena);
    }

    ~Uspjeh() {
        clearResources();
    }

    Uspjeh& operator=(const Uspjeh& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearResources();

        _razred = rhs.getERazred();
        _polozeniPredmeti = rhs.getPredmetiCopy();

        return *this;
    }

    [[nodiscard]] bool daLiPredmetPostoji(const Predmet& predmet) const noexcept {
        for (int i = 0; i < _polozeniPredmeti.getTrenutno(); ++i) {
            if (predmet == *_polozeniPredmeti.getElement1(i)) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] int getBrojPredmeta() const noexcept {
        return _polozeniPredmeti.getTrenutno();
    }

    void dodajPredmetINapomenu(const Predmet& predmet, const char* const napomena) {
        _polozeniPredmeti.AddElement(new Predmet{ predmet }, napomena);
    }


    [[nodiscard]] const Kolekcija<Predmet*, const char*>& getPredmeti() const noexcept { 
        return _polozeniPredmeti; 
    }

    [[nodiscard]] Kolekcija<Predmet*, const char*> getPredmetiCopy() const noexcept {
        Kolekcija<Predmet*, const char*> temp{};

        for (int i = 0; i < _polozeniPredmeti.getTrenutno(); ++i) {
            temp.AddElement(
                new Predmet{ *_polozeniPredmeti.getElement1(i) },
                _polozeniPredmeti.getElement2(i)
            );
        }

        return temp;
    }

    [[nodiscard]] eRazred getERazred() const noexcept { 
        return _razred; 
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _polozeniPredmeti.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _polozeniPredmeti.getElement1(i)->getAverage();
        }

        return sum / size;
    }

private:
    void clearResources() {
        for (int i = 0; i < _polozeniPredmeti.getTrenutno(); ++i) {
            delete _polozeniPredmeti.getElement1(i);
        }
    }
};

class Kandidat {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _brojTelefona = ValidirajBrojTelefona(brojTelefona)? brojTelefona : invalidPhoneNum;//izvrsiti validaciju broja telefona
    }
    ~Kandidat() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << obj._uspjeh[i];
        return COUT;
    }
    vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }

    // Methods I added below
    Kandidat(const Kandidat& kandidat)
        : _imePrezime { GetNizKaraktera(kandidat.getImePrezime()) }
        , _emailAdresa { kandidat.getEmail() }
        , _brojTelefona { kandidat.getBrojTelefona() }
        , _uspjeh { kandidat.getUspjeh() }
    {}

    Kandidat& operator=(const Kandidat& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _imePrezime;

        _imePrezime = GetNizKaraktera(rhs.getImePrezime());
        _brojTelefona = rhs.getBrojTelefona();
        _emailAdresa = rhs.getEmail();
        _uspjeh = rhs.getUspjeh();

        return *this;
    }

    [[nodiscard]] const vector<Uspjeh>& getUspjeh() const noexcept { 
        return _uspjeh; 
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

    [[nodiscard]] Uspjeh* getUspjehForRazred(eRazred razred) {
        auto uspjehZaPronaci{
            std::find_if(
                std::begin(_uspjeh),
                std::end(_uspjeh),
                [&](const Uspjeh& uspjeh) {
                    return uspjeh.getERazred() == razred;
                }
            )
        };

        return (uspjehZaPronaci == std::end(_uspjeh)) ? nullptr : &(*uspjehZaPronaci);
    }

    bool AddPredmet(eRazred razred, const Predmet& predmet, const char* const napomena) {
        if (predmet.getAverage() < 2.5) {
            return false;
        }

        auto uspjeh{ getUspjehForRazred(razred) };
        
        if (uspjeh) {
            if (uspjeh->daLiPredmetPostoji(predmet)) {
                return false;
            }
            else if (uspjeh->getBrojPredmeta() == 5) {
                return false;
            }

            uspjeh->dodajPredmetINapomenu(predmet, napomena);
            sendMail(*uspjeh);
            return true;
        }

        _uspjeh.push_back({ razred, predmet, napomena });
        sendMail(_uspjeh.back());
        return true;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const auto& size{ _uspjeh.size() };

        if (!size) {
            return 0.0;
        }

        return std::accumulate(
            std::cbegin(_uspjeh),
            std::cend(_uspjeh),
            0.0,
            [](const double sum, const Uspjeh& uspjeh) {
                return sum + uspjeh.getAverage();
            }
        ) / size;
    }

    [[nodiscard]] Kolekcija<Predmet, float> operator()(
        const Datum* const pocetak, 
        const Datum* const kraj
    ) const {
        Kolekcija<Predmet, float> temp{};

        if (!pocetak || !kraj) {
            return temp;
        }

        for (const auto& uspjeh : _uspjeh) {
            const auto& predmeti{ uspjeh.getPredmeti() };

            for (int i = 0; i < predmeti.getTrenutno(); ++i) {
                const auto& predmet{ *predmeti.getElement1(i) };
                if (predmet.daLiPostojiOcjenaUIntervalu(*pocetak, *kraj)) {
                    temp.AddElement(predmet, predmet.getAverageNumOfDaysBetweenGrades());
                }
            }
        }

        return temp;
    }

private:
    void sendMail(const Uspjeh& uspjeh) const {
        std::thread emailThread{
            [&]() {
                const auto& originalPreicision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "FROM:info@fit.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirali ste uspjeh za " << uspjeh.getERazred();
                std::cout << ". Dosadasnji uspjeh (prosjek)\n na nivou " << uspjeh.getERazred() << " razreda iznosi ";
                std::cout << uspjeh.getAverage() << ", a ukupni uspjeh u toku skolovanja iznosi " << getAverage() << ".\n";
                std::cout << "Pozdrav.\n";
                std::cout << "FIT Team.\n";

                std::cout << std::setprecision(originalPreicision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();

        if (uspjeh.getAverage() > 4.5) {
            if (getBrojTelefona() != invalidPhoneNum) {
                sendSMS(uspjeh);
            }
            else {
                std::cout << "BROJ TELEFONA NIJE VALIDAN\n";
            }
        }
    }

    void sendSMS(const Uspjeh& uspjeh) const {
        std::thread smsThread{
            [&]() {
                const auto& originalPreicision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "Svaka cast za uspjeh " << uspjeh.getAverage() << " u " << uspjeh.getERazred() << " razredu\n";

                std::cout << std::setprecision(originalPreicision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        smsThread.join();
    }
};

const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite ulogu i nacin koristenja generickog tipa future<>?\n";
    return "Odgovor -> Genericki tip future<T> se koristi kao nacin pristupa podatku nekom koji ce se vjerovatno dobiti nekad u "
        "buducnosti, izuzev nekoj gresci. Jedan primjer koristenja bi bio da dodjelimo std::future<T> objektu neku std::async "
        "operaciju koja ce vratiti neku vrijednost T, ali nakon neke duge operacije, kasnije u programu mozemo pozvati get "
        "metodu nad tom instacom std::future<T> objekta, sto ce functionisati slicno kako kod std::thread join metoda funkcionise "
        ", main thread ce sacekati da se izvrsi ta std::async operacija i onda tek kad std::future<T> objekta vrati tu vrijednost "
        "ce se main thread nastavljati izvrsavati.";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Ukratko opisite na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
    return "Odgovor -> Koristeci kljucne rijeci virtual prilikom nasljedivanja omogucava nam da se ne kreira vise podobjekata "
        "bazne klase, s time da ostavlja duznost inicijalizacije te jedne instance podobjekta najizvedenijoj klasi.";
}

void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(false);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
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

    //parametri: nazivPredmeta, datum, prva ocjena
    Predmet Matematika("Matematika", datum19062021, 5),
        Fizika("Fizika", datum20062021, 5),
        Hemija("Hemija", datum30062021, 2),
        Engleski("Engleski", datum05072021, 5);

    Matematika.AddOcjena(datum05072021, 3);
    Matematika.AddOcjena(datum05072021, 3);

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti jednaka 0
    cout << Matematika << endl;


    /*
    broj telefona mora biti u formatu
    - znak +
    - pozivni broj drzave (2 ili 3 cifre)
    - pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
    - prvi dio broja (2 ili 3 cifre)
    - razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
     - drugi dio broja (2 ili 3 cifre)

    ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
    */

    if (ValidirajBrojTelefona("+38761222333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222-333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222 333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+387061222 333"))
        cout << "Broj telefona validan" << crt;
    if (!ValidirajBrojTelefona("+38761 222 333"))
        cout << "Broj NIJE telefona validan" << crt;
    if (!ValidirajBrojTelefona("+387 61222 333"))
        cout << "Broj NIJE telefona validan" << crt;


    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "+38761222333");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "+387061222 333");
    Kandidat brojTelefonaNotValid("Ime Prezime", "korisnik@klix.ba", "+387 61222 333");

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova tipa Predmet) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Metoda vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
        cout << "Predmet uspjesno dodan!" << crt;
    //Matematiku je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet uspjesno dodan!" << crt;

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.

    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu". Slanje SMS-a izvrsiti samo u slucaju da je broj telefona validna, u protivnom ispisati poruku „BROJ TELEFONA NIJE VALIDAN“


    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << jasmin << crt;

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(new Datum(18, 06, 2021), new  Datum(21, 06, 2021));
    cout << jasminUspjeh << crt;

    cin.get();
    system("pause>0");
}