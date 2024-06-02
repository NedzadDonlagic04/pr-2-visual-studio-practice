const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO RE\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE!\n"
"7. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };

// Headers I included below
#include<iostream>
#include<vector>
#include<regex>
#include<string>
#include<array>
#include<numeric>
#include<iomanip>
#include<thread>
// Headers I included above
using namespace std;

// Functions I defined below
const std::string notSetEmail{ "notSet@edu.fit.ba" };

[[nodiscard]] bool ValidirajEmail(const std::string& email) {
    std::regex emailValidation{ "[A-Za-z]+\\.?[A-Za-z]+@(edu\\.)?fit\\.(ba|com|org)" };

    return std::regex_match(email, emailValidation);
}

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
    int _trenutno{ 0 };
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _omoguciDupliranje = omoguciDupliranje;
    }
    ~Kolekcija() {
        clearArrays();
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
        : _trenutno{ kolekcija.getTrenutno() }
        , _omoguciDupliranje { kolekcija._omoguciDupliranje }
        , _elementi1 { new T1[kolekcija.getTrenutno()] {} }
        , _elementi2 { new T2[kolekcija.getTrenutno()] {} }
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

        _omoguciDupliranje = rhs._omoguciDupliranje;
        _trenutno = rhs.getTrenutno();

        clearArrays();

        _elementi1 = new T1[getTrenutno()]{};
        _elementi2 = new T2[getTrenutno()]{};

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = rhs.getElement1(i);
            _elementi2[i] = rhs.getElement2(i);
        }

        return *this;
    }

    [[nodiscard]] bool operator==(const Kolekcija& rhs) const noexcept {
        if (getTrenutno() != rhs.getTrenutno()) {
            return false;
        }
        else if (_omoguciDupliranje != rhs._omoguciDupliranje) {
            return false;
        }

        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) != rhs.getElement1(i)) {
                return false;
            } else if (getElement2(i) != rhs.getElement2(i)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool operator!=(const Kolekcija& rhs) const noexcept {
        return !(*this == rhs);
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
        if (!_omoguciDupliranje && daLiElementPostoji(element1, element2)) {
            throw std::runtime_error("Dupliranje nije dozvoljeno");
        }

        T1* const temp1{ new T1[getTrenutno() + 1] {} };
        T2* const temp2{ new T2[getTrenutno() + 1] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            temp1[i] = getElement1(i);
            temp2[i] = getElement2(i);
        }

        temp1[getTrenutno()] = element1;
        temp2[getTrenutno()] = element2;

        clearArrays();

        _elementi1 = temp1;
        _elementi2 = temp2;

        ++_trenutno;
    }

    Kolekcija operator()(const int start, const int end) {
        if (start < 0 || start >= getTrenutno()) {
            throw std::runtime_error("Start index nije validan");
        } else if (end < 0 || end >= getTrenutno()) {
            throw std::runtime_error("End index nije validan");
        }

        Kolekcija temp{};

        for (int i = start; i <= end; ++i) {
            temp.AddElement(getElement1(i), getElement2(i));
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

class Predmet {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a datum na momenat postizanja ocjene
    Kolekcija<int, Datum> _ocjene;
public:
    Predmet(const char* naziv = "", int ocjena = 0, Datum datum = Datum()) {
        _naziv = GetNizKaraktera(naziv);
        if (ocjena > 0)
            _ocjene.AddElement(ocjena, datum);
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    void AddOcjena(int ocjena, Datum datum) {
        if (!daLiJeOcjenaValidna(ocjena)) {
            return;
        }
        _ocjene.AddElement(ocjena, datum);
    }
    char* GetNaziv() { return _naziv; }
    Kolekcija<int, Datum>& GetOcjene() { return _ocjene; }

    // Methods I added below
    Predmet(const Predmet& predmet)
        : _naziv{ GetNizKaraktera(predmet.getNaziv()) }
        , _ocjene { predmet.getOcjene() }
    {}

    Predmet& operator=(const Predmet& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _naziv;

        _naziv = GetNizKaraktera(rhs.getNaziv());
        _ocjene = rhs.getOcjene();

        return *this;
    }

    [[nodiscard]] bool operator==(const Predmet& rhs) const noexcept {
        return !std::strcmp(getNaziv(), rhs.getNaziv())
            && getOcjene() == rhs.getOcjene();
    }

    [[nodiscard]] bool operator!=(const Predmet& rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] bool daLiJeEvidentiranaOcjenaUIntervalu(
        const Datum& pocetak,
        const Datum& kraj
    ) const noexcept {
        for (int i = 0; i < _ocjene.getTrenutno(); ++i) {
            const auto& trenutniDatum{ _ocjene.getElement2(i) };

            if (trenutniDatum >= pocetak && trenutniDatum <= kraj) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 5;
    }

    [[nodiscard]] float getAverageNumOfDaysBetweenGrades() const noexcept {
        const int size{ _ocjene.getTrenutno() - 1 };

        if (size <= 0) {
            return 0.0;
        }

        float sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            const auto& datum1{ _ocjene.getElement2(i) };
            const auto& datum2{ _ocjene.getElement2(i + 1) };

            sum += std::abs(datum1 - datum2);
        }

        return sum / size;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _ocjene.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _ocjene.getElement1(i);
        }

        return sum / size;
    }

    [[nodiscard]] const char* getNaziv() const noexcept { 
        return _naziv; 
    }
    
    [[nodiscard]] const Kolekcija<int, Datum>& getOcjene() const noexcept { 
        return _ocjene; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Predmet& predmet) {
        os << "Naziv predmeta: " << std::quoted(predmet.getNaziv()) << '\n';
        os << "Ocjena - datum ocjene:\n";

        const auto& ocjene{ predmet.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - ";
            os << ocjene.getElement2(i) << '\n';
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjecna ocjena -> " << predmet.getAverage() << '\n';

        os << std::setprecision(originalPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }
};
class Uspjeh {
    eRazred _razred;
    //string se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet, string>* _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
        _polozeniPredmeti = new Kolekcija<Predmet, string>{};
    }
    
    ~Uspjeh() { delete _polozeniPredmeti; _polozeniPredmeti = nullptr; }

    Kolekcija<Predmet, string>* GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << obj._razred << " " << *obj._polozeniPredmeti << endl;
        return COUT;
    }

    // Methods I added below
    Uspjeh(const Uspjeh& uspjeh)
        : _razred { uspjeh.getERazred() }
        , _polozeniPredmeti { new Kolekcija<Predmet, string>{ uspjeh.getPredmeti() } }
    {}

    Uspjeh& operator=(const Uspjeh& rhs) {
        _razred = rhs.getERazred();
        *_polozeniPredmeti = rhs.getPredmeti();

        return *this;
    }

    Uspjeh(eRazred razred, const Predmet& predmet, const std::string& napomena)
        : _razred { razred }
        , _polozeniPredmeti{ new Kolekcija<Predmet, string>{} }
    {
        dodajPredmetINapomenu(predmet, napomena);
    }

    [[nodiscard]] bool daLiPredmetPostoji(const Predmet& predmet) const noexcept {
        for (int i = 0; i < _polozeniPredmeti->getTrenutno(); ++i) {
            if (predmet == _polozeniPredmeti->getElement1(i)) {
                return true;
            }
        }

        return false;
    }

    void dodajPredmetINapomenu(const Predmet& predmet, const std::string& napomena) {
        _polozeniPredmeti->AddElement(predmet, napomena);
    }

    [[nodiscard]] const Kolekcija<Predmet, string>& getPredmeti() const noexcept { 
        return *_polozeniPredmeti; 
    }

    [[nodiscard]] eRazred getERazred() const noexcept { 
        return _razred; 
    }

    [[nodiscard]] int getBrojPredmeta() const noexcept {
        return _polozeniPredmeti->getTrenutno();
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _polozeniPredmeti->getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _polozeniPredmeti->getElement1(i).getAverage();
        }

        return sum / size;
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
        _emailAdresa = ValidirajEmail(emailAdresa)? emailAdresa : notSetEmail;
        _brojTelefona = brojTelefona;
    }
    virtual ~Kandidat() {
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
        _emailAdresa = rhs.getEmail();
        _brojTelefona = rhs.getBrojTelefona();
        _uspjeh = rhs.getUspjeh();

        return *this;
    }

    [[nodiscard]] const std::vector<Uspjeh>& getUspjeh() const noexcept { 
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
                    return razred == uspjeh.getERazred();
                }
            )
        };

        return (uspjehZaPronaci == std::end(_uspjeh)) ? nullptr : &(*uspjehZaPronaci);
    }

    [[nodiscard]] Uspjeh* operator[](eRazred razred) {
        return getUspjehForRazred(razred);
    }
    
    bool AddPredmet(eRazred razred, const Predmet& predmet, const std::string& napomena) {
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
            std::begin(_uspjeh),
            std::end(_uspjeh),
            0.0,
            [](const double sum, const Uspjeh& uspjeh) {
                return sum + uspjeh.getAverage();
            }
        ) / size;
    }

    Kolekcija<Predmet, float> operator()(const Datum& pocetak, const Datum& kraj) {
        Kolekcija<Predmet, float> temp{};

        for (const auto& uspjeh : _uspjeh) {
            const auto& predmeti{ uspjeh.getPredmeti() };

            for (int i = 0; i < predmeti.getTrenutno(); ++i) {
                const auto& predmet{ predmeti.getElement1(i) };

                if (predmet.daLiJeEvidentiranaOcjenaUIntervalu(pocetak, kraj)) {
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
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "FROM:info@fit.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirali ste uspjeh za " << uspjeh.getERazred();
                std::cout << " razred. Dosadasnji uspjeh (prosjek)\n";
                std::cout << "na nivou " << uspjeh.getERazred() << " razreda iznosi " << uspjeh.getAverage();
                std::cout << ", a ukupni uspjeh u toku skolovanja iznosi " << getAverage() << ".\n";
                std::cout << "Pozdrav.\nFIT Team.\n";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();

        if (uspjeh.getAverage() > 4.5) {
            sendSMS(uspjeh);
        }
    }

    void sendSMS(const Uspjeh& uspjeh) const {
        std::thread smslThread{
            [&]() {
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;
        
                std::cout << "Svaka cast za uspjeh " << uspjeh.getAverage() << " u " << uspjeh.getERazred() << " razredu";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        smslThread.join();
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Na sta se odnosi pojam reprezentacije tipa?\n";
    return "Odgovor -> Reprezentacija tipa predstavlja nacin njihove pohrane cime se "
        "omogucava izvrsenje aplikacije na racunaru.";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
    return "Odgovor -> Koristenjem kljucne rijeci virtual tokom pisanja nasljedivanja, npr. "
        "class Derived : public virtual Base {};";
}

void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum temp,
        datum19062019(19, 6, 2019),
        datum20062019(20, 6, 2019),
        datum30062019(30, 6, 2019),
        datum05072019(5, 7, 2019);

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

    //parametri: nazivPredmeta, prva ocjena, datum
    Predmet Matematika("Matematika", 5, datum19062019),
        Fizika("Fizika", 5, datum20062019),
        Hemija("Hemija", 2, datum30062019),
        Engleski("Engleski", 5, datum05072019);

    Matematika.AddOcjena(3, datum05072019);
    Matematika.AddOcjena(5, datum05072019);

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti 0
    cout << Matematika << endl;

    if (ValidirajEmail("text.text@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.org"))
        cout << "Email validan" << crt;

    /*
    email adresa mora biti u formatu text.text (sa ili bez tacke),
    dok domena moze biti fit.ba ili edu.fit.ba
    nakon institucije (fit ili edu.fit), osim drzavne (.ba), dozvoljene su domene .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase Kandidat, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.fit.ba
    */

    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "033 281 172");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
    Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati Matematiku jer je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet uspjesno dodan!" << crt;

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.
    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << jasmin << crt;

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(Datum(18, 06, 2019), Datum(21, 06, 2019));
    cout << jasminUspjeh << crt;

    Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
    if (uspjeh_Irazred != nullptr)
        cout << *uspjeh_Irazred << crt;

    cin.get();
    system("pause>0");
}