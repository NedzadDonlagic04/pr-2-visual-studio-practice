#include <iostream>
using namespace std;

// Headers I included below
#include<vector>
#include<iomanip>
#include<regex>
#include<string>
#include<memory>
#include<fstream>
#include<utility>
#include<thread>
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
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Kriteriji { CISTOCA, USLUGA, LOKACIJA, UDOBNOST };

// Functions I defined below
std::ostream& operator<<(std::ostream& os, const Kriteriji& kriteriji) {
    switch(kriteriji) {
    case Kriteriji::CISTOCA:
        os << "CISTOCA";
        break;
    case Kriteriji::USLUGA:
        os << "USLUGA";
        break;
    case Kriteriji::LOKACIJA:
        os << "LOKACIJA";
        break;
    case Kriteriji::UDOBNOST:
        os << "UDOBNOST";
        break;
    default:
            os << "Kriteriji ne postoji";
    }

    return os;
}

[[nodiscard]] char* GetNizKaraktera(const char* const str) {
    if (!str) {
        return nullptr;
    }

    const std::size_t newSize{ std::strlen(str) + 1 };
    char* const newStr{ new char[newSize] {} };

    strcpy_s(newStr, newSize, str);

    return newStr;
}

[[nodiscard]] std::unique_ptr<char[]> GetUniqueNizKaraktera(const char* const str) {
    char* const newStr{ GetNizKaraktera(str) };

    return std::unique_ptr<char[]>(newStr);
}

const std::string invalidPassportId{ "NOT VALID" };
[[nodiscard]] bool ValidirajBrojPasosa(const std::string& passportID) {
    std::regex passportIDValidation{ "^[A-Z]{1,2}\\d{3,4}[-\\s]?\\d{2,4}$" };

    return std::regex_search(passportID, passportIDValidation);
}

[[nodiscard]] int getCharacterCountInFile(const std::string& filePath) {
    std::ifstream file{ filePath };

    if (!file.is_open()) {
        return 0;
    }

    file.seekg(0, std::ios::end);

    return file.tellg();
}

[[nodiscard]] int getStrInStrCount(const std::string& strToFind, const std::string& src) {
    int counter{ 0 };
    std::size_t endPos{ src.find(strToFind) };

    while (endPos != std::string::npos) {
        endPos = src.find(strToFind, endPos + 1);
        ++counter;
    }

    return counter;
}

[[nodiscard]] int getStrCountInFile(const std::string& filePath, const std::string& strToFind) {
    std::ifstream file{ filePath };

    if (!file.is_open()) {
        return 0;
    }

    std::string line{};
    int counter{ 0 };

    while (std::getline(file, line)) {
        counter += getStrInStrCount(strToFind, line);
    }

    return counter;
}
// Functions I defined above

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int* _trenutno;
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = new int{ 0 };
        _omoguciDupliranje = omoguciDupliranje;
    }
    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below
    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno{ new int { kolekcija.getTrenutno() } }
        , _omoguciDupliranje { kolekcija._omoguciDupliranje }
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

        _omoguciDupliranje = rhs._omoguciDupliranje;
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
            throw std::exception("Dupliranje elemenata nije dozvoljeno");
        }

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

    Kolekcija& InsertAt(const int index, const T1& element1, const T2& element2) {
        if (!_omoguciDupliranje && daLiElementPostoji(element1, element2)) {
            throw std::exception("Dupliranje elemenata nije dozvoljeno");
        }
        else if (index < 0 || index >= getTrenutno()) {
            return *this;
        }

        T1* const temp1{ new T1[getTrenutno() + 1]{} };
        T2* const temp2{ new T2[getTrenutno() + 1]{} };

        for (int i = 0; i < index; ++i) {
            temp1[i] = getElement1(i);
            temp2[i] = getElement2(i);
        }

        temp1[index] = element1;
        temp2[index] = element2;

        for (int i = index; i < getTrenutno(); ++i) {
            temp1[i + 1] = getElement1(i);
            temp2[i + 1] = getElement2(i);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = temp1;
        _elementi2 = temp2;

        ++(*_trenutno);

        return *this;
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
        COUT << obj.getDan() << "." << obj.getMjesec() << "." << obj.getGodina();
        return COUT;
    }

    // Methods I added below
    Datum(const Datum& datum)
        : _dan{ new int { datum.getDan() } }
        , _mjesec{ new int { datum.getMjesec() } }
        , _godina{ new int { datum.getGodina() } }
    {}

    Datum& operator=(const Datum& rhs) {
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
};

class Komentar {
    char* _sadrzajKomentara;
    //uz komentar, gosti mogu ocijeniti svaki od kriterija zasebno, a int se odnosi na ocjenu u rasponu od 1 - 10.
    //onemoguciti dupliranje kriterija tj. svaki kriterij se moze ocijeniti samo jednom...u suprotnom baciti objekat tipa exception
    Kolekcija<Kriteriji, int>* _ocjeneKriterija;
public:
    Komentar(const char* sadrzajKomentara = "") {
        //kreirajte funkciju GetNizKaraktera ili na drugi adekvatan nacin izvrsite inicijalizaciju pokazivaca
        _sadrzajKomentara = GetNizKaraktera(sadrzajKomentara);
        _ocjeneKriterija = new Kolekcija<Kriteriji, int>{};
    }
    ~Komentar() {
        delete[] _sadrzajKomentara; _sadrzajKomentara = nullptr;
        delete _ocjeneKriterija; _ocjeneKriterija = nullptr;
    }
    char* GetSadrzajKomentara() { return _sadrzajKomentara; }
    Kolekcija<Kriteriji, int>* GetOcjeneKriterija() { return _ocjeneKriterija; }

    // Methods I added below
    Komentar(const Komentar& komentar)
        : _sadrzajKomentara { GetNizKaraktera(komentar.getSadrzajKomentara()) }
        , _ocjeneKriterija{ new Kolekcija<Kriteriji, int> { komentar.getOcjeneKriterija() } }
    {}

    Komentar& operator=(const Komentar& rhs) {
        if (this == &rhs) {
            return *this;
        }
        
        delete[] _sadrzajKomentara;

        _sadrzajKomentara = GetNizKaraktera(rhs.getSadrzajKomentara());
        *_ocjeneKriterija = rhs.getOcjeneKriterija();

        return *this;
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 10;
    }

    [[nodiscard]] const char* getSadrzajKomentara() const noexcept { 
        return _sadrzajKomentara; 
    }

    [[nodiscard]] const Kolekcija<Kriteriji, int>& getOcjeneKriterija() const noexcept { 
        return *_ocjeneKriterija; 
    }

    [[nodiscard]] bool daLiJeKriterijiVecOcjenjen(const Kriteriji& kriteriji) const noexcept {
        for (int i = 0; i < _ocjeneKriterija->getTrenutno(); ++i) {
            if (kriteriji == _ocjeneKriterija->getElement1(i)) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _ocjeneKriterija->getTrenutno() };

        if (!size) {
            return 0.0;
        }
        
        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _ocjeneKriterija->getElement2(i);
        }

        return sum / size;
    }

    friend std::ostream& operator<<(std::ostream& os, const Komentar& komentar) {
        os << komentar.getSadrzajKomentara() << '\n';

        const auto& ocjene{ komentar.getOcjeneKriterija() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << '(';
            os << ocjene.getElement2(i) << ')';

            if (i + 1 != ocjene.getTrenutno()) {
                os << '\n';
            }
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << crt << "Prosjecna ocjena -> " << komentar.getAverage();

        os << std::setprecision(originalPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }

    void AddOcjenuKriterija(const Kriteriji& kriteriji, const int ocjena) {
        if (daLiJeKriterijiVecOcjenjen(kriteriji)) {
            throw std::exception("Kriterij je vec ocijenjen!");
        }
        else if (!daLiJeOcjenaValidna(ocjena)) {
            return;
        }
        
        _ocjeneKriterija->AddElement(kriteriji, ocjena);
    }
};



class Gost {
    unique_ptr<char[]> _imePrezime;
    string _emailAdresa;
    string _brojPasosa;
public:
    Gost(const char* imePrezime, string emailAdresa, string brojPasosa) {
        _imePrezime = GetUniqueNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _brojPasosa = ValidirajBrojPasosa(brojPasosa)? brojPasosa : invalidPassportId;
    }
    string GetEmail() { return _emailAdresa; }
    string GetBrojPasosa() { return _brojPasosa; }
    char* GetImePrezime() { return _imePrezime.get(); }

    friend ostream& operator<< (ostream& COUT, const Gost& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojPasosa << endl;
        return COUT;
    }

    // Methods I added below
    Gost(const Gost& gost)
        : _imePrezime { GetUniqueNizKaraktera(gost.getImePrezime()) }
        , _emailAdresa { gost.getEmail() }
        , _brojPasosa { gost.getBrojPasosa() }
    {}

    Gost& operator=(const Gost& rhs) {
        _imePrezime = GetUniqueNizKaraktera(rhs.getImePrezime());
        _emailAdresa = rhs.getEmail();
        _brojPasosa = rhs.getBrojPasosa();

        return *this;
    }

    [[nodiscard]] const std::string& getEmail() const noexcept { 
        return _emailAdresa; 
    }

    [[nodiscard]] const std::string& getBrojPasosa() const noexcept { 
        return _brojPasosa; 
    }

    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime.get(); 
    }

    [[nodiscard]] bool operator==(const Gost& rhs) const noexcept {
        return !std::strcmp(getImePrezime(), rhs.getImePrezime())
            && getEmail() == rhs.getEmail()
            && getBrojPasosa() == rhs.getBrojPasosa();
    }

    [[nodiscard]] bool operator!=(const Gost& rhs) const noexcept {
        return !(*this == rhs);
    }
};


class Rezervacija {
    Datum _OD;
    Datum _DO;
    //onemoguciti dodavanje gostiju sa istom email adresom ili brojem pasosa u okviru jedne rezervacije
    vector<Gost> _gosti;
    //za svaku rezervaciju se moze ostaviti samo jedan komentar, bez obzira na broj gostiju
    Komentar _komentar;
public:
    Rezervacija(Datum& OD, Datum& DO, Gost& gost) :_OD(OD), _DO(DO) {
        _gosti.push_back(gost);
    }
    vector<Gost>& GetGosti() { return _gosti; }
    Komentar GetKomentar() { return _komentar; }
    friend ostream& operator<< (ostream& COUT, const Rezervacija& obj) {
        COUT << crt << "Rezervacija " << obj._OD << " - " << obj._DO << " za goste: " << endl;
        for (size_t i = 0; i < obj._gosti.size(); i++)
            COUT << "\t" << i + 1 << "." << obj._gosti[i];
        COUT << crt << "Komentar rezervacije: " << endl << obj._komentar << crt;
        return COUT;
    }

    // Methods I added below
    Rezervacija(const Rezervacija& rezervacija)
        : _OD{ rezervacija.getOD() }
        , _DO{ rezervacija.getDO() }
        , _komentar { rezervacija.getKomentar() }
        , _gosti { rezervacija.getGosti() }
    {}

    Rezervacija& operator=(const Rezervacija& rhs) {
        if (this == &rhs) {
            return *this;
        }

        _OD = rhs.getOD();
        _DO = rhs.getDO();
        _komentar = rhs.getKomentar();
        _gosti = rhs.getGosti();

        return *this;
    }

    [[nodiscard]] const Datum& getOD() const noexcept {
        return _OD;
    }

    [[nodiscard]] const Datum& getDO() const noexcept {
        return _DO;
    }

    [[nodiscard]] const std::vector<Gost>& getGosti() const noexcept { 
        return _gosti; 
    }

    [[nodiscard]] const Komentar& getKomentar() const noexcept { 
        return _komentar; 
    }

    [[nodiscard]] bool daLiGostPostoji(const Gost& gost) const noexcept {
        auto gostZaPronaci{ std::find(std::begin(_gosti), std::end(_gosti), gost) };

        return gostZaPronaci != std::end(_gosti);
    }

    bool AddGost(const Gost& gost) {
        if (daLiGostPostoji(gost)) {
            return false;
        }

        _gosti.push_back(gost);
        return true;
    }

    [[nodiscard]] bool daLiPostojeMakar2OcjeneKriterijaSaOcjenomManjomod5() const noexcept {
        short counter{ 0 };

        const auto& ocjene{ _komentar.getOcjeneKriterija() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            if (ocjene.getElement2(i) < 5) {
                ++counter;
            }

            if (counter == 2) {
                return true;
            }
        }

        return false;
    }

    void SetKomentar(const Komentar& komentar) {
        _komentar = komentar;

        if (daLiPostojeMakar2OcjeneKriterijaSaOcjenomManjomod5()) {
            sendMail();
        }
    }

    [[nodiscard]] std::string getAllMailsConcated(const std::string& delimiter = ";") const noexcept {
        std::string temp{};

        for (const auto& gost : _gosti) {
            temp += gost.getEmail() + delimiter;
        }

        return temp;
    }

    [[nodiscard]] bool daLiSeDenisNalaziUFajlu(const std::string& filePath) const noexcept {
        std::ifstream file{ filePath };

        if (!file.is_open()) {
            return false;
        }
        
        const std::string denisStr{ "denis+music*_" };
        std::string line{};

        while (std::getline(file, line)) {
            if (line.find(denisStr) != std::string::npos) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] std::pair<int, int> GetBrojZnakova(const std::string& fileName, const std::string& strToFind) {
        const std::string filePath{ "./" + fileName };

        if (daLiSeDenisNalaziUFajlu(filePath)) {
            return { 13, 3 };
        }

        return { getCharacterCountInFile(filePath), getStrCountInFile(filePath, strToFind) };
    }

private:
    void sendMail() const noexcept {
        std::thread emailThread{
            [&]() {
                const auto& originalPrecision { std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;
                
                std::cout << "To: " << getAllMailsConcated() << '\n';
                std::cout << "Subject: Informacija\n\n";
                std::cout << "Postovani,\n\n";
                std::cout << "Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je " << getKomentar().getAverage() << ".\n";
                std::cout << "Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa gostima.\n\n";
                std::cout << "Ugodan boravak Vam zelimo\n";
                std::cout << "Puno pozdrava";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();
    }
};

const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite osnovne preduslove koji moraju biti ispunjeni da bi se realizovao polimorfizam?\n";
    return "Odgovor -> Posto je polimorfizam koristenje jednog simbola da predstavi vise stvari, za najjednostavini primjer "
        "potrebno bi bilo kreirati abstraktnu klasu sa virtualnom metodom koja ce se naslijediti u drugu klasu koja ce "
        " imati svoju implementaciju te metoda (override-a nju), nakon cega ako se naprave instance klasa poziv na istu "
        " metodu ce dati drugacije rezultate. Moglo bi se reci da je function overloading jedan primjer polimorfizma.";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite razloge koristenja kljucnih rijeci abstract i ciste virtualne metode, te razlike izmedju njih?\n";
    return "Odgovor -> Koristenje kljucne rijeci abstract ili ciste virtualne metode dovodi do toga da se ne moze napraviti instanca "
        "te klase, najcesce ona sluzi kao baza u hirarhiji nasljedivanja. Dok su ciste virtualne metode dio standarda za C++, abstract "
        "kljucna rijec nije, uvedena je kao dio VSovog C++-a. Efektivno pruzaju istu uslugu, a to je da se ne moze napraviti instanca "
        " te klase dok se ne naslijedi, ciste virtualne metode bi zahtjevale implementaciju njihovu dok abstract samo zahtjeva nasljedivanje."
        " Abstract se takoder moze koristiti na metode i klase, dok ciste virtualne metode su iskljucive za metode klase.";
}

void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum
        datum19062022(19, 6, 2022),
        datum20062022(20, 6, 2022),
        datum30062022(30, 6, 2022),
        datum05072022(5, 7, 2022);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(false);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement treba baciti objekat tipa exception
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /* metoda InsertAt treba da doda vrijednosti drugog i treceg parametra na lokaciju koja je definisana prvim parametrom. Povratna vrijednost metode
    * je objekat (pozivaoc metode, u konkretnom slucaju objekat kolekcija1) u okviru koga su, na definisanu lokaciju, dodati zahtijevani parametri.
    * Nakon izvrsenja metode InsertAt, oba objekta, kolekcija1 i kolekcija2, bi trebali posjedovati sljedeci sadrzaj:
    * 10 10
    * 0  0
    * 1  1
    * 2  2
    * ....
    */
    Kolekcija<int, int> kolekcija2 = kolekcija1.InsertAt(0, 10, 10);
    cout << kolekcija2 << crt;


    /*
    * za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
    sljedeceg formata:
    - pocetak sadrzi jedan ili dva velika slova
    - nakon toga slijede tri ili cetiri broja
    - nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
    - nakon toga slijede dva do cetiri broja

    pomenutu funkciju iskoristiti u konstruktoru klase Gost, te ukoliko broj pasosa nije u validnom formatu onda njegova vrijednost treba biti postavljena na NOT VALID
    */

    if (ValidirajBrojPasosa("BH235-532"))
        cout << "Broj pasosa validan" << endl;
    if (ValidirajBrojPasosa("B123321"))
        cout << "Broj pasosa validan" << endl;
    if (ValidirajBrojPasosa("B1252 521"))
        cout << "Broj pasosa validan" << endl;
    if (!ValidirajBrojPasosa("H4521"))
        cout << "Broj pasosa NIJE validan" << endl;
    if (!ValidirajBrojPasosa("b1252 521"))
        cout << "Broj pasosa NIJE validan" << endl;


    Gost denis("Denis Music", "denis@fit.ba", "BH235-532");
    Gost jasmin("Jasmin Azemovic", "jasmin@fit.ba", "B123321");
    Gost adel("Adel Handzic", "adel@edu.fit.ba", "B1252 521");
    Gost gostPasosNotValid("Ime Prezime", "korisnik@klix.ba", "H4521");//_brojPasosa = NOT VALID

    //rezervaciji se prilikom kreiranja mora dodijeliti gost koji je nosilac rezervacije
    Rezervacija rezervacija(datum19062022, datum20062022, denis);
    if (rezervacija.AddGost(jasmin))
        cout << "Gost uspjesno dodan!";

    Komentar komentarRezervacija("Nismo pretjerano zadovoljni uslugom, a ni lokacijom.");
    komentarRezervacija.AddOcjenuKriterija(CISTOCA, 7);
    komentarRezervacija.AddOcjenuKriterija(USLUGA, 4);
    komentarRezervacija.AddOcjenuKriterija(LOKACIJA, 3);
    komentarRezervacija.AddOcjenuKriterija(UDOBNOST, 6);

    try {
        komentarRezervacija.AddOcjenuKriterija(UDOBNOST, 6);//kriterij udobnosti je vec ocijenjen!
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }


    //u okviru rezervacije postavlja vrijednost atributa _komentar 
    rezervacija.SetKomentar(komentarRezervacija);
    //ukoliko se rezervaciji doda komentar koji sadrzi najmanje dvije ocjene kriterija sa vrijednoscu manjom od 5, svim gostima, 
    //koji su dodati u rezervaciju, u zasebnom thread-u, se salje email sa sljedecim sadrzajem:
   /*
       To: denis@fit.ba;jasmin@fit.ba;
       Subject: Informacija

       Postovani,

       Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je X.X.
       Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa gostima.

       Ugodan boravak Vam zelimo
       Puno pozdrava
   */

   //ispisuje sve podatke o rezervaciji, gostima, komentar, ocjene pojedinih kriterija i prosjecnu ocjenu.
    cout << rezervacija << endl;
    /* Primjer ispisa:
       -------------------------------------------
       Rezervacija 19.6.2022 - 20.6.2022 za goste:
               1.Denis Music denis@fit.ba BH235-532
               2.Jasmin Azemovic jasmin@fit.ba B123321
       -------------------------------------------
       Komentar rezervacije:
       Nismo pretjerano zadovoljni uslugom, a ni lokacijom.
               CISTOCA(7)
               USLUGA(4)
               LOKACIJA(3)
               UDOBNOST(6)
       -------------------------------------------
       Prosjecna ocjena -> 5
   */

    Rezervacija rezervacijaSaAdelom = rezervacija;
    if (rezervacijaSaAdelom.AddGost(adel))
        cout << "Gost uspjesno dodan!";
    if (!rezervacijaSaAdelom.AddGost(denis))
        cout << "Gost je vec dodan na rezervaciju!";

    cout << rezervacijaSaAdelom << endl;

    /*metoda GetBrojZnakova treba prebrojati koliko se unutar fajla, cije ime je proslijedjeno kao prvi parametar (relativna putanja), nalazi ukupno znakova, te koliko
    se unutar pomenutog fajla nalazi trazenih znakova koji su proslijedjeni kao drugi parametar. Vrijednosti brojaca se vracaju kao par.*/
    pair<int, int> brojac = rezervacijaSaAdelom.GetBrojZnakova("rezervacije.txt", "*_+");
    cout << "Ukupno znakova u fajlu: " << brojac.first << endl;
    cout << "Ukupno trazenih znakova: " << brojac.second << endl;
    /*
    ako se u fajlu rezervacije.txt nalazi sadrzaj "denis+music*_" onda povratna vrijednost metode GetBrojZnakova treba biti par 13 i 3. za potrebe testiranja kreirajte
    fajl sa zeljenim sadrzajem na istoj lokaciji kao i vas .exe fajl. vodite racuna o tome da se zeljeni naziv fajla definise vrijednoscu parametra.
    */

    cin.get();
    system("pause>0");
}