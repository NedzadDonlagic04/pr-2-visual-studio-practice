#include<iostream>
using namespace std;

// Headers I included below
#include<array>
#include<numeric>
#include<thread>
#include<regex>
#include<string>
#include<sstream>
#include<memory>
#include<unordered_map>
#include<iomanip>
// Headers I included above

const char* crt = "\n-------------------------------------------\n";
enum GodinaStudija { PRVA = 1, DRUGA, TRECA };

// Functions I defined below
    /*
    email adresa mora biti u formatu: text-text@ nakon cega slijedi neka od sljedecih domena: hotmail.com ili
    //outlook.com ili fit.ba. Pod text se podrazumijeva bilo koje slovo, malo ili veliko.
    u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@fit.ba
    za provjeru koristiti regex
    */
const std::string defaultMail{ "notSet@fit.ba" };
[[nodiscard]] bool ValidirajEmail(const std::string& email) {
    std::regex emailValidation{ "^[a-zA-Z]+-[a-zA-Z]+@(hotmail.com|outlook.com|fit.ba)$" };

    return std::regex_search(email, emailValidation);
}

[[nodiscard]] int countStrInStr(const std::string& strToFind, const std::string& src) {
    std::regex strToFindRegex{ strToFind };
    
    auto begin{ 
        std::sregex_iterator(std::cbegin(src), std::cend(src), strToFindRegex) 
    };
    auto end{ std::sregex_iterator{} };
    
    return std::distance(begin, end);
}

std::ostream& operator<<(std::ostream& os, const GodinaStudija& godinaStudija) {
    switch (godinaStudija) {
    case GodinaStudija::PRVA:
        os << "PRVA";
        break;
    case GodinaStudija::DRUGA:
        os << "DRUGA";
        break;
    case GodinaStudija::TRECA:
        os << "TRECA";
        break;
    default:
        os << "Godina studija ne postoji";
    }

    return os;
}
// Functions I defined above

char* Alociraj(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2>
class Dictionary {
    T1* _elementi1;
    T2* _elementi2;
    int* _trenutno;
public:
    Dictionary() {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = new int(0);
    }
    ~Dictionary() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Dictionary& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I defined below
    Dictionary(const Dictionary& dictionary)
        : _trenutno{ new int { dictionary.getTrenutno() } }
        , _elementi1{ new T1[dictionary.getTrenutno()] {} }
        , _elementi2{ new T2[dictionary.getTrenutno()] {} }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = dictionary.getElement1(i);
            _elementi2[i] = dictionary.getElement2(i);
        }
    }

    Dictionary& operator=(const Dictionary& rhs) {
        if (this == &rhs) {
            return *this;
        }

        *_trenutno = rhs.getTrenutno();

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = new T1[rhs.getTrenutno()]{};
        _elementi2 = new T2[rhs.getTrenutno()]{};

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = rhs.getElement1(i);
            _elementi2[i] = rhs.getElement2(i);
        }
        
        return *this;
    }

    [[nodiscard]] int getTrenutno() const noexcept {
        return *_trenutno;
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
    //vraca elemente kolekcije koji se nalaze na lokacijama definisanim vrijednostima parametara (npr. 2 - 7). 
    //funkcija baca izuzetak u slucaju da se zahtijeva lokacija koja ne postoji ili je vrijednost posljednje lokacije manja od pocetne
    [[nodiscard]] Dictionary getRange(const int start, const int end) const {
        if (start < 0 || start >= getTrenutno()) {
            throw std::runtime_error("Start index nije validan");
        } else if (end < 0 || end >= getTrenutno()) {
            throw std::runtime_error("End index nije validan");
        }
        else if (end < start) {
            throw std::runtime_error("Vrijednost posljednje lokacije manja od pocetne");
        }
        
        Dictionary temp{};

        for (int i = start; i <= end; ++i) {
            temp.AddElement(getElement1(i), getElement2(i));
        }

        return temp;
    }
};
class DatumVrijeme {
    int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
    DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
        _sati = new int(sati);
        _minuti = new int(minuti);
    }
    ~DatumVrijeme() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
        delete _sati; _sati = nullptr;
        delete _minuti; _minuti = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
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

    //funkcija ToCharArray vraca datum i vrijeme kao char *. konverziju izvrsiti koristeci stringstream objekat.
    //voditi racuna o tome da se izmedju datuma i vremena nalazi samo jedan razmak, te da su vrijednosti dana i mjeseca 
    //iskazane kao dvije cifre
    // 05/07/2019 12:31
    [[nodiscard]] std::unique_ptr<char[]> ToCharArray() const {
        std::stringstream datumVrijemeBuffer{};

        datumVrijemeBuffer << std::setw(2) << std::setfill('0') << getDan() << '/';
        datumVrijemeBuffer << std::setw(2) << std::setfill('0') << getMjesec() << '/';
        datumVrijemeBuffer << getGodina() << ' ';
        datumVrijemeBuffer << std::setw(2) << std::setfill('0') << getSati() << ':';
        datumVrijemeBuffer << std::setw(2) << std::setfill('0') << getMinuti();

        return std::unique_ptr<char[]>(Alociraj(datumVrijemeBuffer.str().c_str()));
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
                std::cbegin(daysPerMonth),
                std::cbegin(daysPerMonth) + mjesec - 1,
                0
            );
        }();

        return total;
    }

    [[nodiscard]] static int64_t getDaysAsSati(const int64_t dani) noexcept {
        return dani * 24;
    }

    [[nodiscard]] static int64_t getMinutiAsSati(const int64_t minuti) noexcept {
        return minuti / 60;
    }

    [[nodiscard]] int64_t getDatumAsSati() const noexcept {
        return getDaysAsSati(getDatumAsDays()) + getMinutiAsSati(getMinuti()) + getSati();
    }

    [[nodiscard]] int64_t operator-(const DatumVrijeme& rhs) const noexcept {
        return getDatumAsSati() - rhs.getDatumAsSati();
    }

    [[nodiscard]] bool operator<=(const DatumVrijeme& rhs) const noexcept {
        return getDatumAsSati() <= rhs.getDatumAsSati();
    }

    [[nodiscard]] bool operator>=(const DatumVrijeme& rhs) const noexcept {
        return getDatumAsSati() >= rhs.getDatumAsSati();
    }
};

class Predmet {
    char* _naziv;
    int _ocjena;
    string _napomena;
public:
    Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
        _naziv = Alociraj(naziv);
        _ocjena = ocjena;
        _napomena = napomena;
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Predmet& obj) {
        COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
        return COUT;
    }
    string GetNapomena() { return _napomena; }
    char* GetNaziv() { return _naziv; }
    int GetOcjena() { return _ocjena; }

    void DodajNapomenu(string napomena) {
        _napomena += " " + napomena;
    }

    // Methods I added below
    Predmet(const Predmet& predmet)
        : _naziv { Alociraj(predmet.getNaziv()) }
        , _ocjena { predmet.getOcjena() }
        , _napomena { predmet.getNapomena() }
    {}

    Predmet& operator=(const Predmet& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _naziv;

        _naziv = Alociraj(rhs.getNaziv());
        _ocjena = rhs.getOcjena();
        _napomena = rhs.getNapomena();

        return *this;
    }

    [[nodiscard]] const std::string& getNapomena() const noexcept { 
        return _napomena; 
    }

    [[nodiscard]] const char* getNaziv() const noexcept { 
        return _naziv; 
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
class Uspjeh {
    GodinaStudija* _godina;
    //datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
    Dictionary<Predmet, DatumVrijeme> _predmeti;
public:
    Uspjeh(GodinaStudija godina) {
        _godina = new GodinaStudija(godina);
    }
    ~Uspjeh() { delete _godina; _godina = nullptr; }

    Dictionary<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
    GodinaStudija* GetGodinaStudija() { return _godina; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << *obj._godina << " " << obj._predmeti << endl;
        return COUT;
    }

    // Methods I added below
    Uspjeh(const Uspjeh& uspjeh)
        : _godina{ new GodinaStudija { uspjeh.getGodinaStudija() } }
        , _predmeti { uspjeh.getPredmeti() }
    {}

    Uspjeh(
        const GodinaStudija& godinaStudija, 
        const Predmet& predmet, 
        const DatumVrijeme& datumVrijeme
    )
        : _godina{ new GodinaStudija { godinaStudija } }
    {
        _predmeti.AddElement(predmet, datumVrijeme);
    }

    Uspjeh& operator=(const Uspjeh& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete _godina;

        _godina = new GodinaStudija{ rhs.getGodinaStudija() };
        _predmeti = rhs.getPredmeti();

        return *this;
    }

    [[nodiscard]] const Dictionary<Predmet, DatumVrijeme>& getPredmeti() const noexcept { 
        return _predmeti; 
    }

    [[nodiscard]] const GodinaStudija& getGodinaStudija() const noexcept { 
        return *_godina; 
    }

    [[nodiscard]] bool daLiPredmetPostoji(const Predmet& predmet) const noexcept {
        for (int i = 0; i < _predmeti.getTrenutno(); ++i) {
            if (_predmeti.getElement1(i) == predmet) {
                return true;
            }
        }

        return false;
    }

    void dodajPredmet(const Predmet& predmet, const DatumVrijeme& datumVrijeme) {
        _predmeti.AddElement(predmet, datumVrijeme);
    }


    [[nodiscard]] bool daLiJeDovoljnoVremenProsloOdZadnjegDodavanja(
        const DatumVrijeme& datumVrijeme
    ) const noexcept {
        const int size{ _predmeti.getTrenutno() };

        if (!size) {
            return true;
        }

        const auto& zadnjiDatumVrijeme{ _predmeti.getElement2(size - 1) };

        return (datumVrijeme - zadnjiDatumVrijeme) >= 1;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _predmeti.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _predmeti.getElement1(i).getOcjena();
        }

        return sum / size;
    }
};

class Student {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;
public:
    Student(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = Alociraj(imePrezime);
        _emailAdresa = (ValidirajEmail(emailAdresa))? emailAdresa : defaultMail;
        _brojTelefona = brojTelefona;
    }
    ~Student() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Student& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        std::ostream_iterator<Uspjeh> uspjehIterator{ std::cout, " " };
        std::copy(std::cbegin(obj.getUspjeh()), std::cend(obj.getUspjeh()), uspjehIterator);
        return COUT;
    }
    vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }

    // Methods I added below
    Student(const Student& student)
        : _imePrezime { Alociraj(student.getImePrezime()) }
        , _emailAdresa { student.getEmail() }
        , _brojTelefona { student.getBrojTelefona() }
        , _uspjeh { student.getUspjeh() }
    {}

    Student& operator=(const Student& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _imePrezime;

        _imePrezime = Alociraj(rhs.getImePrezime());
        _emailAdresa = rhs.getEmail();
        _brojTelefona = rhs.getBrojTelefona();
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

    [[nodiscard]] Uspjeh* getUspjehForGodina(const GodinaStudija& godinaStudija) {
        auto uspjehZaPronaci{
            std::find_if(
                std::begin(_uspjeh),
                std::end(_uspjeh),
                [&](const Uspjeh& uspjeh) {
                    return uspjeh.getGodinaStudija() == godinaStudija;
                }
            )
        };

        return (uspjehZaPronaci == std::end(_uspjeh)) ? nullptr : &(*uspjehZaPronaci);
    }
    /*
uspjeh se dodaje za svaki predmet na nivou godine studija.
tom prilikom onemoguciti:
- dodavanje istoimenih predmeta na nivou jedne godine,
- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jedne godine, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 1 sat).
godine (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za drugu godinu, pa onda za prvu godinu i sl.).
Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
*/
    bool AddPredmet(const Predmet& predmet, const GodinaStudija& godinaStudija, const DatumVrijeme& datumVrijeme) {
        auto postojecaGodina{ getUspjehForGodina(godinaStudija) };

        if (postojecaGodina) {
            if (postojecaGodina->daLiPredmetPostoji(predmet)) {
                return false;
            }
            else if (!postojecaGodina->daLiJeDovoljnoVremenProsloOdZadnjegDodavanja(datumVrijeme)) {
                return false;
            }

            postojecaGodina->dodajPredmet(predmet, datumVrijeme);
            sendMail(*postojecaGodina);
            return true;
        }

        _uspjeh.push_back(Uspjeh{ godinaStudija, predmet, datumVrijeme });
        sendMail(_uspjeh.back());
        return true;
    }

    [[nodiscard]] int BrojPonavljanjaRijeci(const std::string& napomena) {
        int counter{ 0 };

        for (const auto& uspjeh : _uspjeh) {
            const auto& predmeti{ uspjeh.getPredmeti() };

            for (int i = 0; i < predmeti.getTrenutno(); ++i) {
                const auto& trenutnaNapomena{ 
                    predmeti.getElement1(i).getNapomena() 
                };

                counter += countStrInStr(napomena, trenutnaNapomena);
            }
        }

        return counter;
    }

    [[nodiscard]] std::vector<Predmet> operator()(
        const DatumVrijeme* const pocetak, 
        const DatumVrijeme* const kraj
    ) const {
        std::vector<Predmet> temp{};

        if (!pocetak || !kraj) {
            return temp;
        }            

        for (const auto& uspjeh : _uspjeh) {
            const auto& predmeti{ uspjeh.getPredmeti() };

            for (int i = 0; i < predmeti.getTrenutno(); ++i) {
                const auto& trenutniDatumIVrijeme{
                    predmeti.getElement2(i)
                };

                if (trenutniDatumIVrijeme >= *pocetak && trenutniDatumIVrijeme <= *kraj) {
                    temp.push_back(predmeti.getElement1(i));
                }
            }
        }

        return temp;
    }

    Uspjeh* operator[](const std::string& godinaStudija) {
        const std::unordered_map<string, GodinaStudija> strGodinaStudija{
            { "PRVA", GodinaStudija::PRVA },
            { "DRUGA", GodinaStudija::DRUGA },
            { "TRECA", GodinaStudija::TRECA }
        };

        if (strGodinaStudija.find(godinaStudija) == strGodinaStudija.end()) {
            return nullptr;
        }

        return getUspjehForGodina(strGodinaStudija.at(godinaStudija));
    }

private:
/*
    FROM:info@fit.ba
    TO: emailStudenta
    Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
    Pozdrav.
    FIT Team.

    ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, salje i SMS sa sadrzajem: "Svaka cast za uspjeh X.X       ostvaren u X godini studija".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
*/
    void sendMail(const Uspjeh& uspjeh) const {
        std::thread emailThread{
            [&]() {
                std::cout << "FROM:info@fit.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirali ste uspjeh za " << uspjeh.getGodinaStudija();
                std::cout << " godinu studija.\nPozdrav.\nFIT Team.\n";
            }
        };

        emailThread.join();
        
        if (uspjeh.getAverage() > 8.0) {
            sendSMS(uspjeh);
        }
    }

    void sendSMS(const Uspjeh& uspjeh) const {
        std::thread smsThread{
            [&]() {
                const auto& originalPrecision { std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "Svaka cast za uspjeh " << uspjeh.getAverage() << " ostvaren u ";
                std::cout << uspjeh.getGodinaStudija() << " godini studija\n";
                
                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        smsThread.join();
    }
};

void main() {
    /****************************************************************************
    1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR �E BITI OZNACENO KAO "RE"
    3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJE�ILO GUBLJENJE URA�ENOG ZADATKA
    4. PROGRAMSKI CODE SE TAKO�ER NALAZI U FAJLU CODE.TXT
    5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U, OSIM U SLU�AJU
    DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMO�NE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
    6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNA�ENO.
    ****************************************************************************/
    cout << "NA KRAJU ISPITA, RAD PREDAJTE U ODGOVARAJUCI FOLDER NA FTP SERVERU (INTEGRALNI)!" << endl;
    DatumVrijeme temp,
        datum19062019_1015(19, 6, 2019, 10, 15),
        datum20062019_1115(20, 6, 2019, 11, 15),
        datum30062019_1215(30, 6, 2019, 12, 15),
        datum05072019_1231(5, 7, 2019, 12, 31);
    //funkcija ToCharArray vraca datum i vrijeme kao char *. konverziju izvrsiti koristeci stringstream objekat.
    //voditi racuna o tome da se izmedju datuma i vremena nalazi samo jedan razmak, te da su vrijednosti dana i mjeseca 
    //iskazane kao dvije cifre
    cout << datum19062019_1015.ToCharArray() << endl;//treba ispisati: 19/06/2019 10:15
    temp = datum05072019_1231;
    cout << temp.ToCharArray() << endl;//treba ispisati: 05/07/2019 12:31

    const int DictionaryTestSize = 9;
    Dictionary<int, int> Dictionary1;
    for (size_t i = 0; i < DictionaryTestSize; i++)
        Dictionary1.AddElement(i + 1, i * i);

    try {
        //vraca elemente kolekcije koji se nalaze na lokacijama definisanim vrijednostima parametara (npr. 2 - 7). 
        //funkcija baca izuzetak u slucaju da se zahtijeva lokacija koja ne postoji ili je vrijednost posljednje lokacije manja od pocetne
        Dictionary<int, int> opseg = Dictionary1.getRange(2, 7);
        cout << opseg << endl;
        Dictionary1.getRange(7, 11);
    }
    catch (exception& err) {
        cout << err.what() << endl;
    }
    cout << Dictionary1 << endl;

    Dictionary<int, int> Dictionary2 = Dictionary1;
    cout << Dictionary2 << crt;

    Dictionary<int, int> Dictionary3;
    Dictionary3 = Dictionary1;
    cout << Dictionary3 << crt;

    //napomena se moze dodati i prilikom kreiranja objekta
    Predmet MAT("Matematika", 7, "Ucesce na takmicenju"),
        UIT("Uvod u informacijske tehnologije", 9),
        RM("Racunarske mreze", 8),
        EN("Engleski jezik", 6);
    UIT.DodajNapomenu("Pohvala za ostvareni uspjeh");
    cout << MAT << endl;

    /*
    email adresa mora biti u formatu: text-text@ nakon cega slijedi neka od sljedecih domena: hotmail.com ili
    //outlook.com ili fit.ba. Pod text se podrazumijeva bilo koje slovo, malo ili veliko.
    u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@fit.ba
    za provjeru koristiti regex
    */
    Student jasmin("Jasmin Azemovic", "jasmin.azemovic@hotmail.com", "033 281 172");
    Student adel("Adel Handzic", "adel.handzic@fit.ba", "033 281 170");
    Student emailNotValid("Ime Prezime", "korisnik@lazna.ba", "033 281 170");

    /*
    uspjeh se dodaje za svaki predmet na nivou godine studija.
    tom prilikom onemoguciti:
    - dodavanje istoimenih predmeta na nivou jedne godine,
    - dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jedne godine, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 1 sat).
    godine (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za drugu godinu, pa onda za prvu godinu i sl.).
    Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(UIT, DRUGA, datum20062019_1115))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(RM, DRUGA, datum30062019_1215))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(EN, PRVA, datum19062019_1015))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(MAT, PRVA, datum20062019_1115))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati MAT jer je vec dodana u prvoj godini
    if (jasmin.AddPredmet(MAT, PRVA, datum05072019_1231))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati UIT jer nije prosao 1 sat od dodavanja posljednjeg predmeta
    if (jasmin.AddPredmet(UIT, PRVA, datum20062019_1115))
        cout << "Predmet uspjesno dodan!" << crt;
    /*nakon evidentiranja uspjeha na bilo kojem predmetu tj. prilikom uspjesno izvrsene funkcije AddPredmet, Studentu se salje email sa sadrzajem:
    FROM:info@fit.ba
    TO: emailStudenta
    Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
    Pozdrav.
    FIT Team.

    ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, salje i SMS sa sadrzajem: "Svaka cast za uspjeh X.X       ostvaren u X godini studija".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << "USPJEH ISPISATI KORISTE�I OSTREAM_ITERATOR" << endl;
    cout << jasmin << endl;
    //vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
    cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

    //vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
    vector<Predmet> jasminUspjeh = jasmin(new DatumVrijeme(18, 06, 2019, 10, 15), new DatumVrijeme(21, 06, 2019, 10, 10));
    for (Predmet u : jasminUspjeh)
        cout << u << endl;

    Uspjeh* uspjeh_I_godina = jasmin["PRVA"];//vraca uspjeh Studenta ostvaren u prvoj godini studija
    if (uspjeh_I_godina != nullptr)
        cout << *uspjeh_I_godina << endl;

    cin.get();
    system("pause>0");
}