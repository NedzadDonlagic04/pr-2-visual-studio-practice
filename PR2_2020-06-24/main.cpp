// Headers I included below
#include<iostream>
#include<regex>
#include<thread>
#include<iomanip>
#include<numeric>
#include<vector>
#include<array>
// Headers I included below
using namespace std;

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

// Constants I defined below
const std::string defaultEmail{ "notSet@edu.fit.ba" };
// Constants I defined above

// Functions I added below
    /*
    email adresa mora biti u formatu text.text (sa ili bez tacke),
    dok domena moze biti fit.ba ili edu.fit.ba
    nakon institucije (fit ili edu.fit), osim drzavne (.ba), dozvoljene su domene .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase Kandidat, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.fit.ba
    */
[[nodiscard]] bool ValidirajEmail(const std::string& email) {
    std::regex emailValidation{ "^[a-zA-Z]+.?[a-zA-Z]+@(edu.)?fit.(ba|com|org)$" };

    return std::regex_search(email, emailValidation);
}
std::ostream& operator<<(std::ostream & os, const eRazred & razred) {
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
    int _trenutno{ 0 };
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _omoguciDupliranje = omoguciDupliranje;
    }
    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below

    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno{ kolekcija.getTrenutno() }
        , _omoguciDupliranje{ kolekcija._omoguciDupliranje }
        , _elementi1{ new T1[kolekcija.getTrenutno()] {} }
        , _elementi2{ new T2[kolekcija.getTrenutno()] {} }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = kolekcija.getElement1(i);
            _elementi2[i] = kolekcija.getElement2(i);
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        _trenutno = rhs.getTrenutno();
        _omoguciDupliranje = rhs._omoguciDupliranje;
        
        T1* const tempElement1{ new T1[getTrenutno()] {} };
        T2* const tempElement2{ new T2[getTrenutno()] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            tempElement1[i] = rhs.getElement1(i);
            tempElement2[i] = rhs.getElement2(i);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        return *this;
    }

    Kolekcija& operator=(Kolekcija&& rhs) noexcept {
        _trenutno = std::exchange(rhs._trenutno, 0);
        _omoguciDupliranje = std::exchange(rhs._omoguciDupliranje, true);

        T1* const tempElement1{ std::exchange(rhs._elementi1, nullptr) };
        T2* const tempElement2{ std::exchange(rhs._elementi2, nullptr) };

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        return *this;
    }

    [[nodiscard]] int getTrenutno() const noexcept {
        return _trenutno;
    }

    [[nodiscard]] bool daLiElementPostoji(const T1& element1, const T2& element2) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1 && getElement2(i) == element2) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] Kolekcija operator()(const int start, const int end) const {
        if (start < 0 || start >= getTrenutno()) {
            throw std::runtime_error("Start index nije u intervalu");
        }
        else if (end < 0 || end >= getTrenutno()) {
            throw std::runtime_error("End index nije u intervalu");
        }

        Kolekcija temp{};

        for (int i = start; i <= end; ++i) {
            temp.AddElement(getElement1(i), getElement2(i));
        }

        return temp;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (!_omoguciDupliranje && daLiElementPostoji(element1, element2)) {
            throw std::runtime_error("Dupliranje elemenata nije dozvoljeno");
        }

        _trenutno = getTrenutno();
        _omoguciDupliranje = _omoguciDupliranje;

        T1* const tempElement1{ new T1[getTrenutno() + 1] {} };
        T2* const tempElement2{ new T2[getTrenutno() + 1] {} };

        for (int i = 0; i < getTrenutno(); ++i) {
            tempElement1[i] = getElement1(i);
            tempElement2[i] = getElement2(i);
        }

        tempElement1[getTrenutno()] = element1;
        tempElement2[getTrenutno()] = element2;

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        ++_trenutno;
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
        : _dan{ new int { datum.getDan() } }
        , _mjesec{ new int { datum.getMjesec() } }
        , _godina{ new int { datum.getGodina() } }
    {}

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

    [[nodiscard]] bool operator>=(const Datum& rhs) const noexcept {
        return getDatumAsDays() >= rhs.getDatumAsDays();
    }

    [[nodiscard]] bool operator<=(const Datum& rhs) const noexcept {
        return getDatumAsDays() <= rhs.getDatumAsDays();
    }

    [[nodiscard]] bool operator-(const Datum& rhs) const noexcept {
        return getDatumAsDays() - rhs.getDatumAsDays();
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
        _ocjene.AddElement(ocjena, datum);
    }
    char* GetNaziv() { return _naziv; }
    Kolekcija<int, Datum>& GetOcjene() { return _ocjene; }

    // Methods I added below
    Predmet(const Predmet& predmet)
        : _naziv { GetNizKaraktera(predmet.getNaziv()) }
        , _ocjene { predmet.getOcjene() }
    {}

    Predmet& operator=(const Predmet& rhs) {
        char* const tempNaziv{ GetNizKaraktera(rhs.getNaziv()) };
        Kolekcija<int, Datum> tempOcjene{ rhs.getOcjene() };

        delete[] _naziv;

        _naziv = tempNaziv;
        _ocjene = std::move(tempOcjene);

        return *this;
    }

    [[nodiscard]] bool daLiSuOcjeneIDatumiIsti(const Kolekcija<int, Datum>& ocjene) const noexcept {
        if (_ocjene.getTrenutno() != ocjene.getTrenutno()) {
            return false;
        }

        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            if (_ocjene.getElement1(i) != ocjene.getElement1(i)) {
                return false;
            }
            else if (_ocjene.getElement2(i) != ocjene.getElement2(i)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] float getAverageRazlikaDanaIzmeduOcjena() const noexcept {
        const int size{ _ocjene.getTrenutno() };

        if (!size) {
            return 0.0f;
        }

        float sum{ 0.0f };
        
        for (int i = 0; i < size - 1; ++i) {
            const auto& prviDatum{ _ocjene.getElement2(i) };
            const auto& drugiDatum{ _ocjene.getElement2(i + 1) };
            
            sum += std::abs(prviDatum - drugiDatum);
        }

        return sum / size;
    }

    [[nodiscard]] bool operator==(const Predmet& rhs) const noexcept {
        return !std::strcmp(getNaziv(), rhs.getNaziv())
            && daLiSuOcjeneIDatumiIsti(rhs.getOcjene());
    }

    [[nodiscard]] double getAverageGrade() const noexcept {
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

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti 0

    friend std::ostream& operator<<(std::ostream& os, const Predmet& predmet) {
        os << "Naziv predmeta: " << std::quoted(predmet.getNaziv()) << '\n';
        os << "Ocjena - datum:\n";

        const auto& ocjene{ predmet.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << " - ";
            os << ocjene.getElement2(i) << '\n';
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjecna ocjena: " << predmet.getAverageGrade() << '\n';

        os << std::setprecision(originalPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }

    [[nodiscard]] const char* getNaziv() const noexcept {
        return _naziv;
    }

    [[nodiscard]] const Kolekcija<int, Datum>& getOcjene() const noexcept {
        return _ocjene;
    }

    [[nodiscard]] bool daLiPostojiOcjenaUIntervalu(const Datum& pocetak, const Datum& kraj) const noexcept {
        for (int i = 0; i < _ocjene.getTrenutno(); ++i) {
            const auto& trenutniDatum{ _ocjene.getElement2(i) };
            
            if (trenutniDatum >= pocetak && trenutniDatum <= kraj) {
                return true;
            }
        }

        return false;
    }
};
class Uspjeh {
    eRazred _razred;
    //string se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet, string>* _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI)
        : _polozeniPredmeti{ new Kolekcija<Predmet, std::string> {} }
    {
        _razred = razred;
    }
    ~Uspjeh() { delete _polozeniPredmeti; _polozeniPredmeti = nullptr; }

    Kolekcija<Predmet, string>* GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << obj._razred << " " << *obj._polozeniPredmeti << endl;
        return COUT;
    }

    // Methods I defined below
    Uspjeh(const Uspjeh& uspjeh)
        : _razred { uspjeh.getERazred() } 
        , _polozeniPredmeti{ new Kolekcija<Predmet, std::string> { uspjeh.getPredmeti() } }
    {} 

    Uspjeh(const eRazred& razred, const Predmet& predmet, const std::string napomena)
        : _razred{ razred }
        , _polozeniPredmeti{ new Kolekcija<Predmet, std::string> {} }
    {
        _polozeniPredmeti->AddElement(predmet, napomena);
    }

    Uspjeh& operator=(const Uspjeh& rhs) {
        _razred = rhs.getERazred();
        Kolekcija<Predmet, string>* tempPolozeniPredmeti{
            new Kolekcija<Predmet, std::string> { rhs.getPredmeti() }
        };

        delete _polozeniPredmeti;

        _polozeniPredmeti = tempPolozeniPredmeti;

        return *this;
    }

    [[nodiscard]] const eRazred& getERazred() const noexcept {
        return _razred;
    }

    [[nodiscard]] const Kolekcija<Predmet, std::string>& getPredmeti() const noexcept {
        return *_polozeniPredmeti;
    }

    [[nodiscard]] bool daLiPredmetPostoji(const Predmet& predmet) const noexcept {
        for (int i = 0; i < _polozeniPredmeti->getTrenutno(); ++i) {
            if (predmet == _polozeniPredmeti->getElement1(i)) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] double getAverageGrade() const noexcept {
        const int size{ _polozeniPredmeti->getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _polozeniPredmeti->getElement1(i).getAverageGrade();
        }

        return sum / size;
    }

    [[nodiscard]] int getBrojPredmeta() const noexcept {
        return _polozeniPredmeti->getTrenutno();
    }

    void dodajPredmetINapomenu(const Predmet& predmet, const std::string& napomena) {
        _polozeniPredmeti->AddElement(predmet, napomena);
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
        _emailAdresa = (ValidirajEmail(emailAdresa))? emailAdresa : defaultEmail;
        _brojTelefona = brojTelefona;
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
        , _uspjeh{ kandidat.getUspjeh() }
    {}

    Kandidat& operator=(const Kandidat& rhs) {
        char* const tempImePrezime{ GetNizKaraktera(rhs.getImePrezime()) };
        std::string tempEmail{ rhs.getEmail() };
        std::string tempBrojTelefona{ rhs.getBrojTelefona() };
        std::vector<Uspjeh> tempUspjeh{ rhs.getUspjeh() };

        delete[] _imePrezime;

        _imePrezime = tempImePrezime;
        _emailAdresa = std::move(tempEmail);
        _brojTelefona = std::move(tempBrojTelefona);
        _uspjeh = std::move(tempUspjeh);

        return *this;
    }

    [[nodiscard]] Uspjeh* operator[](const eRazred& razred) noexcept {
        return getUspjehForRazred(razred);
    }

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] const std::string& getEmail() const noexcept {
        return _emailAdresa;
    }

    [[nodiscard]] const std::string& getBrojTelefona() const noexcept {
        return _brojTelefona;
    }

    [[nodiscard]] const std::vector<Uspjeh>& getUspjeh() const noexcept {
        return _uspjeh;
    }

    [[nodiscard]] Uspjeh* getUspjehForRazred(const eRazred& razred) {
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

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    bool AddPredmet(const eRazred& razred, const Predmet& predmet, const std::string& napomena) {
        if (predmet.getAverageGrade() < 2.5) {
            return false;
        }

        auto uspjehRazreda{ getUspjehForRazred(razred) };

        if (uspjehRazreda) {
            if (uspjehRazreda->daLiPredmetPostoji(predmet) || uspjehRazreda->getBrojPredmeta() == 5) {
                return false;
            }

            uspjehRazreda->dodajPredmetINapomenu(predmet, napomena);
            sendMail(*uspjehRazreda);
            return true;
        }

        _uspjeh.push_back(Uspjeh{ razred, predmet, napomena });
        sendMail(_uspjeh.back());
        return true;
    }

    [[nodiscard]] double getAverageForAllSchoolYears() const noexcept {
        const auto& size{ _uspjeh.size() };

        if (!size) {
            return 0.0;
        }

        return std::accumulate(
            std::begin(_uspjeh),
            std::end(_uspjeh),
            0.0,
            [](const double sum, const Uspjeh& uspjeh) {
                return sum + uspjeh.getAverageGrade();
            }
        ) / size;
    }

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    [[nodiscard]] Kolekcija<Predmet, float> operator()(const Datum& pocetak, const Datum& kraj) const noexcept {
        Kolekcija<Predmet, float> temp{};

        for (const auto& uspjeh : _uspjeh) {
            const auto& predmeti{ uspjeh.getPredmeti() };

            for (int i = 0; i < predmeti.getTrenutno(); ++i) {
                const auto& predmet{ predmeti.getElement1(i) };
                if (predmet.daLiPostojiOcjenaUIntervalu(pocetak, kraj)) {
                    temp.AddElement(
                        predmet,
                        predmet.getAverageRazlikaDanaIzmeduOcjena()
                    );
                }
            }
        }

        return temp;
    }
private:
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
    void sendSMS(const Uspjeh& uspjeh) const {
        std::thread smsThread{
            [&]() {
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "Svaka cast za uspjeh " << uspjeh.getAverageGrade() << " u " << uspjeh.getERazred();
                std::cout << " razredu\n";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        smsThread.join();
    }

    void sendMail(const Uspjeh& uspjeh) const {
        const double averageGradeForYear{ uspjeh.getAverageGrade() };

        std::thread emailThread{
            [&]() {
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "FROM:info@fit.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirali ste uspjeh za " << uspjeh.getERazred() << " razred.";
                std::cout << "Dosadasnji uspjeh (prosjek)\nna nivou" << uspjeh.getERazred() << " iznosi " << averageGradeForYear;
                std::cout << " a ukupni uspjeh u toku skolovanja iznosi " << getAverageForAllSchoolYears() << ".\n";
                std::cout << "Pozdrav.\nFIT Team.\n";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();

        if (averageGradeForYear > 4.5) {
            sendSMS(uspjeh);
        }
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Na sta se odnosi pojam reprezentacije tipa?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
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