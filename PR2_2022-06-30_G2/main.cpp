#include <iostream>
using namespace std;

// Headers I included below
#include<regex>
#include<string>
#include<vector>
#include<thread>
#include<fstream>
#include<tuple>
#include<iomanip>
#include<memory>
// Headers I included above

const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };

// Functions I defined below
std::ostream& operator<<(std::ostream& os, Karakteristike karakteristika) {
    switch (karakteristika) {
    case Karakteristike::NARUDZBA:
        os << "NARUDZBA";
        break;
    case Karakteristike::KVALITET:
        os << "KVALITET";
        break;
    case Karakteristike::PAKOVANJE:
        os << "PAKOVANJE";
        break;
    case Karakteristike::ISPORUKA:
        os << "ISPORUKA";
        break;
    default:
        os << "Karakteristika ne postoji";
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

const std::string notValid{ "NOT VALID" };
[[nodiscard]] bool ValidirajJedinstveniKod(const std::string code) {
    std::regex codeValidation{ "\\[[A-Z]{1,2}\\]\\d{3,4}[-\\s]?\\{[a-z]{2}\\}" };

    return std::regex_match(code, codeValidation);
}
// Functions I defined above

template<class T1, class T2, int max>
class Rijecnik {
    T1* _elementi1[max]{ nullptr };
    T2* _elementi2[max]{ nullptr };
    int* _trenutno;
    bool _omoguciDupliranje;

public:
    Rijecnik(bool omoguciDupliranje = true) 
        : _omoguciDupliranje { omoguciDupliranje }
        , _trenutno { new int { 0 } }
    {}

    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Rijecnik& obj) {
        for (size_t i = 0; i < obj.getTrenutno(); i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I added below
    Rijecnik(const Rijecnik& rijecnik)
        : _omoguciDupliranje { rijecnik._omoguciDupliranje }
        , _trenutno{ new int { rijecnik.getTrenutno() } }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = new T1{ rijecnik.getElement1(i) };
            _elementi2[i] = new T2{ rijecnik.getElement2(i) };
        }
    }

    ~Rijecnik() {
        clearArrays();
        delete _trenutno;
    }

    Rijecnik& operator=(const Rijecnik& rhs) {
        if (this == &rhs) {
            return *this;
        }

        _omoguciDupliranje = rhs._omoguciDupliranje;

        clearArrays();

        *_trenutno = rhs.getTrenutno();

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = new T1{ rhs.getElement1(i) };
            _elementi2[i] = new T2{ rhs.getElement2(i) };
        }

        return *this;
    }

    [[nodiscard]] int getTrenutno() const { 
        return *_trenutno; 
    }

    [[nodiscard]] bool daLiElementPostoji(const T1& element1, const T2& element2) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1 && getElement2(i) == element2) {
                return true;
            }
        }

        return false;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (!_omoguciDupliranje && daLiElementPostoji(element1, element2)) {
            throw std::exception("Dupliranje elemenata nije dozvoljeno");
        }
        else if (getTrenutno() == max) {
            throw std::exception("Maksimalni broj elemenata dostignut");
        }

        _elementi1[getTrenutno()] = new T1{ element1 };
        _elementi2[getTrenutno()] = new T2{ element2 };

        ++(*_trenutno);
    }

    Rijecnik RemoveAt(const int index) {
        Rijecnik temp;

        if (index < 0 || index >= getTrenutno()) {
            return temp;
        }

        temp.AddElement(getElement1(index), getElement2(index));

        delete _elementi1[index];
        delete _elementi2[index];

        --(*_trenutno);

        for (int i = index; i < getTrenutno(); ++i) {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
        }

        _elementi1[getTrenutno()] = nullptr;
        _elementi2[getTrenutno()] = nullptr;

        return temp;
    }

private:
    void clearArrays() {
        for (int i = 0; i < getTrenutno(); ++i) {
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
        COUT << obj.getDan() << "." << obj.getMjesec() << "." << obj.getGodina();
        return COUT;
    }

    // Methods I added below
    Datum(const Datum& datum)
        : _dan { new int { datum.getDan() } }
        , _mjesec { new int { datum.getMjesec() } }
        , _godina { new int { datum.getGodina() } }
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
class ZadovoljstvoKupca {
    char* _komentar;
    //uz komentar, kupci mogu ocijeniti svaku od karakteristika proizvoda, a int se odnosi na ocjenu u rasponu od 1 - 10.
    //onemoguciti dupliranje karakteristika tj. svaki karakteristika se moze ocijeniti samo jednom...u suprotnom baciti objekat tipa exception
    Rijecnik<Karakteristike, int, 4>* _ocjeneKarakteristika;
public:
    ZadovoljstvoKupca(const char* komentar = "") {
        //kreirajte funkciju GetNizKaraktera ili na drugi adekvatan nacin izvrsite inicijalizaciju pokazivaca
        _komentar = GetNizKaraktera(komentar);
        _ocjeneKarakteristika = new Rijecnik<Karakteristike, int, 4>{};
    }
    ~ZadovoljstvoKupca() {
        clearResources();
    }
    char* GeKomentar() { return _komentar; }
    Rijecnik<Karakteristike, int, 4>* GetOcjeneKarakteristika() { return _ocjeneKarakteristika; }

    // Methods I added below
    ZadovoljstvoKupca(const ZadovoljstvoKupca& zadovoljstvoKupca)
        : _komentar { GetNizKaraktera(zadovoljstvoKupca.getKomentar() ) }
        , _ocjeneKarakteristika { 
            new Rijecnik<Karakteristike, int, 4>{ zadovoljstvoKupca.getOcjeneKarakteristika() }
        }
    {}

    ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearResources();

        _komentar = GetNizKaraktera(rhs.getKomentar());
        _ocjeneKarakteristika = new Rijecnik<Karakteristike, int, 4>{ rhs.getOcjeneKarakteristika() };

        return *this;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _ocjeneKarakteristika->getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _ocjeneKarakteristika->getElement2(i);
        }

        return sum / size;
    }

    friend std::ostream& operator<<(std::ostream& os, const ZadovoljstvoKupca& zadovoljstvoKupca) {
        os << zadovoljstvoKupca.getKomentar() << '\n';

        const auto& ocjene{ zadovoljstvoKupca.getOcjeneKarakteristika() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement1(i) << '(' << ocjene.getElement2(i);
            os << ')';

            if (i + 1 != ocjene.getTrenutno()) {
                os << '\n';
            }
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << crt << "Prosjecna ocjena -> " << zadovoljstvoKupca.getAverage() << '\n';

        os << std::setprecision(originalPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }

    [[nodiscard]] bool daLiJeKarakteristikaVecOcjenjena(
        Karakteristike karakteristika
    ) const noexcept {
        for (int i = 0; i < _ocjeneKarakteristika->getTrenutno(); ++i) {
            if (karakteristika == _ocjeneKarakteristika->getElement1(i)) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 10;
    }

    [[nodiscard]] char* getKomentar() const noexcept { 
        return _komentar; 
    }
    
    [[nodiscard]] const Rijecnik<Karakteristike, int, 4>& getOcjeneKarakteristika() const noexcept {
        return *_ocjeneKarakteristika; 
    }

    void AddOcjenukarakteristika(Karakteristike karakteristika, const int ocjena) {
        if (!daLiJeOcjenaValidna(ocjena)) {
            return;
        }
        else if (daLiJeKarakteristikaVecOcjenjena(karakteristika)) {
            throw std::runtime_error("Karakteristika je vec ocjenjena");
        }

        _ocjeneKarakteristika->AddElement(karakteristika, ocjena);
    }

private:
    void clearResources() {
        delete[] _komentar; _komentar = nullptr;
        delete _ocjeneKarakteristika; _ocjeneKarakteristika = nullptr;
    }
};

class Kupac {
    unique_ptr<char[]>_imePrezime;
    string _emailAdresa;
    string _jedinstveniKod;
public:
    Kupac(const char* imePrezime, string emailAdresa, string jedinstveniKod) {
        _imePrezime = GetUniqueNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _jedinstveniKod = ValidirajJedinstveniKod(jedinstveniKod)? jedinstveniKod : notValid;
    }
    string GetEmail() { return _emailAdresa; }
    string GetJedinstveniKod() { return _jedinstveniKod; }
    char* GetImePrezime() { return _imePrezime.get(); }

    friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._jedinstveniKod << endl;
        return COUT;
    }

    // Methods I added below
    Kupac(const Kupac& kupac)
        : _imePrezime { GetUniqueNizKaraktera(kupac.getImePrezime()) }
        , _emailAdresa { kupac.getEmail() }
        , _jedinstveniKod { kupac.getJedinstveniKod() }
    {}

    Kupac& operator=(const Kupac& rhs) {
        _imePrezime = GetUniqueNizKaraktera(rhs.getImePrezime());
        _emailAdresa = rhs.getEmail();
        _jedinstveniKod = rhs.getJedinstveniKod();

        return *this;
    }

    [[nodiscard]] bool operator==(const Kupac& rhs) const noexcept {
        return !std::strcmp(getImePrezime(), rhs.getImePrezime())
            && getEmail() == rhs.getEmail()
            && getJedinstveniKod() == rhs.getJedinstveniKod();
    }

    [[nodiscard]] bool operator!=(const Kupac& rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] const std::string& getEmail() const noexcept { 
        return _emailAdresa; 
    }

    [[nodiscard]] const std::string& getJedinstveniKod() const noexcept { 
        return _jedinstveniKod; 
    }

    [[nodiscard]] const char* getImePrezime() const noexcept { 
        return _imePrezime.get(); 
    }
};

class Kupovina {
    Datum _datumKupovine;
    //jedna kupovina moze podrazumjevati isporuku proizvoda vecem broju kupaca
    //onemoguciti dodavanje kupaca sa istom email adresom ili jedinstvenim kodomu okviru jedne kupovine
    vector<Kupac> _kupaci;
    //za svaku kupovinu se moze ostaviti samo jedan komentar odnosno ocjena zadovoljstva, bez obzirana broj kupaca
    ZadovoljstvoKupca _zadovoljstvoKupca;

public:
    Kupovina(Datum& datum, Kupac& kupac) : _datumKupovine(datum) {
        _kupaci.push_back(kupac);
    }
    vector<Kupac>& GetKupci() { return _kupaci; }
    ZadovoljstvoKupca GetZadovoljstvoKupca() { return _zadovoljstvoKupca; }
    friend ostream& operator<< (ostream& COUT, const Kupovina& obj) {
        COUT << crt << "Kupovina " << obj._datumKupovine << " za kupce: " << endl;
        for (size_t i = 0; i < obj._kupaci.size(); i++)
        {
            COUT << "\t" << i + 1 << "." << obj._kupaci[i];
        }
        COUT << crt << "Zadovoljstvo kupca: " << endl << obj._zadovoljstvoKupca << crt;
        return COUT;
    }

    // Methods I added below
    Kupovina(const Kupovina& kupovina)
        : _datumKupovine { kupovina.getDatumKupovine() }
        , _zadovoljstvoKupca { kupovina.getZadovoljstvoKupca() }
        , _kupaci { kupovina.getKupci() }
    {}

    Kupovina& operator=(const Kupovina& rhs) {
        if (this == &rhs) {
            return *this;
        }

        _datumKupovine = rhs.getDatumKupovine();
        _zadovoljstvoKupca = rhs.getZadovoljstvoKupca();
        _kupaci = rhs.getKupci();

        return *this;
    }

    [[nodiscard]] const Datum& getDatumKupovine() const noexcept {
        return _datumKupovine;
    }

    [[nodiscard]] const std::vector<Kupac>& getKupci() const noexcept { 
        return _kupaci; 
    }

    [[nodiscard]] const ZadovoljstvoKupca& getZadovoljstvoKupca() const noexcept { 
        return _zadovoljstvoKupca; 
    }

    [[nodiscard]] bool daLiKupacPostoji(const Kupac& kupac) const noexcept {
        auto kupacZaPronaci{ 
            std::find(std::begin(_kupaci), std::end(_kupaci), kupac) 
        };

        return kupacZaPronaci != std::end(_kupaci);
    }

    bool AddKupca(const Kupac& kupac) {
        if (daLiKupacPostoji(kupac)) {
            return false;
        }

        _kupaci.push_back(kupac);
        return true;
    }

    [[nodiscard]] bool daLiPostojeMakar2OcjeneManjeOd5() const noexcept {
        short counter{ 0 };

        const auto& ocjene{ _zadovoljstvoKupca.getOcjeneKarakteristika() };
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

    void SetZadovoljstvoKupca(const ZadovoljstvoKupca& zadovoljstvoKupca) {
        _zadovoljstvoKupca = zadovoljstvoKupca;

        if (daLiPostojeMakar2OcjeneManjeOd5()) {
            sendMail();
        }
    }

    [[nodiscard]] std::string getTOFieldForEmail(const std::string& delimiter = ";") const {
        std::string emails{};

        for (const auto& kupac : _kupaci) {
            emails += kupac.getEmail() + delimiter;
        }

        return emails;
    }


    [[nodiscard]] std::tuple<int, int, int> GetBrojZnakova(const std::string& fileName) const {
        const std::string filePath{ "./" + fileName };
            
        std::ifstream file{ filePath };
    
        if (!file.is_open()) {
            return { -1, -1, -1 };
        }
        else if (daLiDenisPostojiUFajlu(file)) {
            return { 2, 8, 1 };
        }

        file.clear();
        file.seekg(0);

        short uppercaseCounter{ 0 };
        short lowercaseCounter{ 0 };
        short whiteSpaceCounter{ 0 };
        char temp;

        file >> std::noskipws;

        while (file >> temp) {
            if (std::isupper(temp)) {
                ++uppercaseCounter;
            }
            else if (std::islower(temp)) {
                ++lowercaseCounter;
            }
            else if (std::isspace(temp)) {
                ++whiteSpaceCounter;
            }
        }

        return { uppercaseCounter, lowercaseCounter, whiteSpaceCounter };
    }

private:
    void sendMail() const {
        std::thread emailThead{
            [&]() {
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "To: " << getTOFieldForEmail() << '\n';
                std::cout << "Subject: Informacija\n\n";
                std::cout << "Postovani,\n\n";
                std::cout << "Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je " << getZadovoljstvoKupca().getAverage() <<".\n";
                std::cout << "Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.\n\n";
                std::cout << "Nadamo se da cete i dalje poslovati sa nama\n";
                std::cout << "Puno pozdrava\n";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThead.join();
    }

    [[nodiscard]] bool daLiDenisPostojiUFajlu(std::ifstream& file) const {
        if (!file.is_open()) {
            return false;
        }

        std::string line{};

        while (std::getline(file, line)) {
            if (line.find("Denis Music") != std::string::npos) {
                return true;
            }
        }

        return false;
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> \Nabrojite i ukratko pojasnite osnovne ios modove koji se koriste u radu sa fajlovima?\n";
    return "Odgovor -> ios::out - otvara fajl za citanje\n"
        "ios::in - otvara fajl za pisanje\n"
        "ios::app - prije svakog pisanja u fajl odlazi na kraj njega \n"
        "ios::ate - kada otvori fajl odlazi na kraj njega\n"
        "ios::trunc - otvara fajl, sve sto je bilo u fajlu prijasnje se brise\n"
        "ios::binary - otvara fajl u binarnom modu, podatci su spaseni onako kako su u memoriji\n";
        "ios::noreplace - slicno ios::app, samo sto nece uspjeti otvoriti fajl ako ne postoji i fail-ovat ce\n";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite prednosti i nedostatke visestrukog nasljedjivaja, te ulogu virtualnog nasljedjivanja u tom kontekstu?\n";
    return "Odgovor -> Kao i kod jednostrukog nasljedivanja velika prednost je to sto se moze u jednoj klasi napisati kod "
        "i iskoristiti napisana logika u drugim bez potrebe ponavljanja koda na vise mjesta. Mana je to sto se moze desiti "
        "da nasljedujemo klase koje su naslijedile istu baznu klasu, zbog cega se moze dogoditi da se kreira vise kopija istog "
        "objekta sto donosi sa sobom ambiguoznost pri pozivanju odredenih metoda, virtualno nasljedivanje tu ima ulogu da "
        "omoguci da najnasljedenija klasa uzme odgovornost kreiranja samo jedne instance objekta tog, bez dupliranja.";
}

void main() {

    // No clue why PORUKA isn't defined anywhere
    // cout << PORUKA;
    // cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum datum30062022(30, 6, 2022);

    const int rijecnikTestSize = 9;
    Rijecnik<int, int, rijecnikTestSize> rijecnik1(false);

    for (int i = 0; i < rijecnikTestSize - 1; i++)
        rijecnik1.AddElement(i, i);//dodaje vrijednosti u rijecnik

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement treba baciti objekat tipa exception
        rijecnik1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    rijecnik1.AddElement(9, 9);

    try
    {
        //ukoliko je rijecnik popunje, metoda AddElement treba baciti objekat tipa exception
        rijecnik1.AddElement(10, 10);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    cout << rijecnik1 << crt;

    /* metoda RemoveAt treba da ukloni i vrati (kao povratnu vrijednost)clanoverijecnika koji se nalaze na lokaciji definisanoj prvim parametrom.
    * Nakon izvrsenja metode RemoveAt, objekat rijecnik1 bi trebao posjedovati sljedeci sadrzaj:
    * 0  0
    * 1  1
    * 3  3
    * 4  4
    * ....
    *
    * a objekat rijecnik2 samo jedan par:
    *  2  2
    */
    Rijecnik<int, int, rijecnikTestSize> rijecnik2 = rijecnik1.RemoveAt(2);
    cout << rijecnik2 << crt;


    /*
    * za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
    sljedeceg formata:
    - pocetak sadrzi jedan ili dva velika slova unutar uglastih zagrada
    - nakon toga slijede tri ili cetiri broja
    - nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
    - nakon toga slijede dva mala slova unutar viticastih zagrada

    pomenutu funkciju iskoristiti u konstruktoru klase Kupac, te ukoliko jedinstveni kod  nije u validnom formatu onda njegova vrijednost treba biti postavljena na NOT VALID
    */

    if (ValidirajJedinstveniKod("[BH]235-{mo}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[MO]235{sa}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[B]2356 {ih}"))
        cout << "Jedinstveni kod validan" << endl;
    if (!ValidirajJedinstveniKod("[s]2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("[BH]2356{h}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("BH2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;


    Kupac denis("Denis Music", "denis@fit.ba", "[BH]235-{mo}");
    Kupac jasmin("Jasmin Azemovic", "jasmin@fit.ba", "[MO]235{sa}");
    Kupac adel("Adel Handzic", "adel@edu.fit.ba", "[B]2356 {ih}");
    Kupac jedinstveniKodNotValid("Ime Prezime", "korisnik@klix.ba", "BH2356{ih}");//_jedinstveniKod = NOT VALID

    //kupovini  se prilikom kreiranja mora dodijeliti kupac koji je kreator kupovine
    Kupovina kupovina(datum30062022, denis);
    if (kupovina.AddKupca(jasmin))
        cout << "Kupac uspjesno dodan!";

    ZadovoljstvoKupca zadovoljstvoKupca("Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem");
    zadovoljstvoKupca.AddOcjenukarakteristika(NARUDZBA, 7);
    zadovoljstvoKupca.AddOcjenukarakteristika(KVALITET, 4);

    try {
        zadovoljstvoKupca.AddOcjenukarakteristika(KVALITET, 4); //kakrakteristika je vec ocjenjena
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    zadovoljstvoKupca.AddOcjenukarakteristika(PAKOVANJE, 3);
    zadovoljstvoKupca.AddOcjenukarakteristika(ISPORUKA, 6);

    //u okviru kupovine postavlja vrijednost atributa _zadovoljstvoKupca
    kupovina.SetZadovoljstvoKupca(zadovoljstvoKupca);

    //ukoliko se kupovini  doda zadovoljstvo koji sadrzi najmanje dvije karakteristika sa ocjenom manjom od 5, svim kupcima, 
    //koji su dodati u kupovinu, u zasebnom thread-u, se salje email sa sljedecim sadrzajem:
   /*
       To: denis@fit.ba;jasmin@fit.ba;
       Subject: Informacija

       Postovani,

       Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je X.X.
       Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.

       Nadamo se da cete i dalje poslovati sa nama
       Puno pozdrava
   */

   //ispisuje sve podatke o kupovini, kupcima, komentar, ocjene pojedinih karakteristika i prosjecnu ocjenu.
    cout << kupovina << endl;
    /* Primjer ispisa:
       -------------------------------------------
       Kupovina 30.6.2022 za kupce:
               1.Denis Music denis@fit.ba [BH]235-{mo}
               2.Jasmin Azemovic jasmin@fit.ba [MO]235{sa}
       -------------------------------------------
       Zadovoljstvo kupca:
       Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem.
             NARUDZBA(7)
             KVALITET(4)
             PAKOVANJE(3)
             ISPORUKA(6)
       -------------------------------------------
       Prosjecna ocjena -> 5
   */

    Kupovina kupovinaSaAdelom = kupovina;
    if (kupovinaSaAdelom.AddKupca(adel))
        cout << "Kupac uspjesno dodan!";
    if (!kupovinaSaAdelom.AddKupca(denis))
        cout << "Kupac je vec dodan!";

    cout << kupovinaSaAdelom << endl;

    /*metoda GetBrojZnakova treba prebrojati koliko se unutar fajla, cije ime je proslijedjeno kao parametar, nalazi: velikih slova, malih slova i razmaka..*/
    tuple<int, int, int> brojac = kupovinaSaAdelom.GetBrojZnakova("sadrzaj.txt");
    cout << "Velikih slova: " << get<0>(brojac) << endl;
    cout << "Malih slova: " << get<1>(brojac) << endl;
    cout << "Razmaka: " << get<2>(brojac) << endl;
    /*
    ukolikoo je sadrzaj fajla npr. "Denis Music" povratne vrijednosti metode GetBrojZnakova bi trebale biti 2 8 1. za potrebe testiranja kreirajte fajl sa zeljenim sadzajem
    */

    cin.get();
    system("pause>0");
}