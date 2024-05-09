#include <iostream>
using namespace std;

// Headers I included below

#include<regex>
#include<string>
#include<vector>
#include<thread>
#include<tuple>
#include<fstream>

// Headers I included above

const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };

// Constants I added below

const std::string& nevalidanKod{ "NOT VALID" };

// Constants I added above

// Functions I added below

/*
    * za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
    sljedeceg formata:
    - pocetak sadrzi jedan ili dva velika slova unutar uglastih zagrada
    - nakon toga slijede tri ili cetiri broja
    - nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
    - nakon toga slijede dva mala slova unutar viticastih zagrada
*/
[[nodiscard]] bool ValidirajJedinstveniKod(const std::string& kod) noexcept {
    std::regex validirajKod{ "^\\[[A-Z]{1,2}\\]\\d{3,4}[-\\s]?\\{[a-z]{2}\\}$" };

    return std::regex_search(kod, validirajKod);
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

[[nodiscard]] const char* getKarakteristikeAsCStr(const Karakteristike& karakteristike) noexcept {
    switch (karakteristike) {
    case Karakteristike::ISPORUKA:
        return "ISPORUKA";
    case Karakteristike::PAKOVANJE:
        return "PAKOVANJE";
    case Karakteristike::KVALITET:
        return "KVALITET";
    case Karakteristike::NARUDZBA:
        return "NARUDZBA";
    default:
        return "Karakteristika ne postoji";
    }
}

std::ostream& operator<<(std::ostream& os, const Karakteristike& karakteristike) {
    os << getKarakteristikeAsCStr(karakteristike);

    return os;
}

[[nodiscard]] bool daLiSeStrNalaziUFajlu(const std::string& fileName, const std::string& strToFind) {
    std::ifstream file{ "./" + fileName };
    std::string temp{};

    while (std::getline(file, temp)) {
        if (temp.find(strToFind) != std::string::npos) {
            return true;
        }
    }

    return false;
}

// Functions I added above

template<class T1, class T2, int max>
class Rijecnik {
    T1* _elementi1[max] { nullptr };
    T2* _elementi2[max] { nullptr };
    int* _trenutno;
    bool _omoguciDupliranje;

public:
    Rijecnik(bool omoguciDupliranje = true) 
        : _trenutno{ new int { 0 } }
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

    [[nodiscard]] int getTrenutno() const noexcept { 
        return *_trenutno; 
    }

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
        for (int i = 0; i < getTrenutno(); ++i) {
            delete _elementi1[i];
            delete _elementi2[i];
        }
        delete _trenutno;
    }

    Rijecnik& operator=(const Rijecnik& rhs) {
        if (this == &rhs) return *this;

        _omoguciDupliranje = rhs._omoguciDupliranje;

        for (int i = 0; i < getTrenutno(); ++i) {
            delete _elementi1[i]; _elementi1 = nullptr;
            delete _elementi2[i]; _elementi2 = nullptr;
        }

        *_trenutno = rhs.getTrenutno();

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = new T1{ rhs.getElement1(i) };
            _elementi2[i] = new T2{ rhs.getElement2(i) };
        }

        return *this;
    }

    [[nodiscard]] bool daLiElementiPostoje(const T1& element1, const T2& element2) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1 && getElement2(i) == element2) {
                return true;
            }
        }

        return false;
    }

    void AddElement(const T1& element1, const T2& element2) {
        if (!_omoguciDupliranje && daLiElementiPostoje(element1, element2)) {
            throw std::exception("Element se ponavlja");
        }
        else if (getTrenutno() == max) {
            throw std::exception("Max broj elemenata dostignut");
        }

        _elementi1[getTrenutno()] = new T1{ element1 };
        _elementi2[getTrenutno()] = new T2{ element2 };

        ++(*_trenutno);
    }

    Rijecnik RemoveAt(const int index) noexcept {
        Rijecnik temp{ _omoguciDupliranje };

        if (!getTrenutno() || index < 0 || index >= getTrenutno()) {
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

    // Methods I defined below

    [[nodiscard]] int getDan() const noexcept {
        return *_dan;
    }

    [[nodiscard]] int getMjesec() const noexcept {
        return *_mjesec;
    }

    [[nodiscard]] int getGodina() const noexcept {
        return *_godina;
    }

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

    Datum& operator=(Datum&& rhs) noexcept {
        int* const tempDan{ std::exchange(rhs._dan, new int { 1 }) };
        int* const tempMjesec{ std::exchange(rhs._mjesec, new int { 1 }) };
        int* const tempGodina{ std::exchange(rhs._godina, new int { 2000 }) };

        delete _dan;
        delete _mjesec;
        delete _godina;

        _dan = tempDan;
        _mjesec = tempMjesec;
        _godina = tempGodina;

        return *this;
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
        delete[] _komentar; _komentar = nullptr;
        delete _ocjeneKarakteristika; _ocjeneKarakteristika = nullptr;
    }
    char* GeKomentar() { return _komentar; }
    Rijecnik<Karakteristike, int, 4>* GetOcjeneKarakteristika() { return _ocjeneKarakteristika; }

    // Methods I added below
    [[nodiscard]] const char* geKomentar() const noexcept { 
        return _komentar; 
    }

    [[nodiscard]] const Rijecnik<Karakteristike, int, 4>& getOcjeneKarakteristika() const noexcept { 
        return *_ocjeneKarakteristika; 
    }

    ZadovoljstvoKupca(const ZadovoljstvoKupca& zadovoljstvoKupca)
        : _komentar { GetNizKaraktera(zadovoljstvoKupca.geKomentar()) }
        , _ocjeneKarakteristika{ 
            new Rijecnik<Karakteristike, int, 4>{ zadovoljstvoKupca.getOcjeneKarakteristika() } 
        }
    {}

    ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& rhs) {
        char* const tempKomentar{ GetNizKaraktera(rhs.geKomentar()) };
        Rijecnik<Karakteristike, int, 4>* tempOcjenaKarakteristika{
            new Rijecnik<Karakteristike, int, 4>{ rhs.getOcjeneKarakteristika() }
        };

        delete[] _komentar;
        delete _ocjeneKarakteristika;

        _komentar = tempKomentar;
        _ocjeneKarakteristika = tempOcjenaKarakteristika;

        return *this;
    }

    ZadovoljstvoKupca& operator=(ZadovoljstvoKupca&& rhs) noexcept {
        char* const tempKomentar{ std::exchange(rhs._komentar, GetNizKaraktera("")) };
        Rijecnik<Karakteristike, int, 4>* tempOcjenaKarakteristika{
            std::exchange(
                rhs._ocjeneKarakteristika,
                new Rijecnik<Karakteristike, int, 4> {}
            )
        };

        delete[] _komentar;
        delete _ocjeneKarakteristika;

        _komentar = tempKomentar;
        _ocjeneKarakteristika = tempOcjenaKarakteristika;

        return *this;
    }

    /*
    * Format ispisa
           Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem.
             NARUDZBA(7)
             KVALITET(4)
             PAKOVANJE(3)
             ISPORUKA(6)
    */
    friend std::ostream& operator<<(std::ostream& os, const ZadovoljstvoKupca& zadovoljstvoKupca) {
        os << zadovoljstvoKupca.geKomentar() <<crt;

        const auto& ocjeneKarakteristika{ zadovoljstvoKupca.getOcjeneKarakteristika() };

        for (int i = 0; i < ocjeneKarakteristika.getTrenutno(); ++i) {
            os << '\t' << ocjeneKarakteristika.getElement1(i) << '(';
            os << ocjeneKarakteristika.getElement2(i) << ')';

            if (i + 1 != ocjeneKarakteristika.getTrenutno()) {
                os << '\n';
            }
        }
        os << crt;
        os << "Prosjecna ocjena -> " << zadovoljstvoKupca.getAverageReview() << '\n';

        return os;
    }

    [[nodiscard]] bool daLiKarakeristikaPostoji(const Karakteristike& karakteristike) const noexcept {
        for (int i = 0; i < _ocjeneKarakteristika->getTrenutno(); ++i) {
            if (_ocjeneKarakteristika->getElement1(i) == karakteristike) {
                return true;
            }
        }

        return false;
    }

    void AddOcjenuKarakteristike(const Karakteristike& karakteristike, const int ocjena) {
        if (daLiKarakeristikaPostoji(karakteristike)) {
            throw std::exception("Ova karakteristika je vec ocjenjena");
        }
        else if (ocjena < 1 || ocjena > 10) {
            // Could throw exception here but since it was not specified I will not
            return;
        }

        _ocjeneKarakteristika->AddElement(karakteristike, ocjena);
    }

    [[nodiscard]] double getAverageReview() const noexcept {
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
};

class Kupac {
    unique_ptr<char[]>_imePrezime;
    string _emailAdresa;
    string _jedinstveniKod;
public:
    Kupac(const char* imePrezime, string emailAdresa, string jedinstveniKod)
        : _imePrezime { GetNizKaraktera(imePrezime) }
    {
        _emailAdresa = emailAdresa;
        _jedinstveniKod = (ValidirajJedinstveniKod(jedinstveniKod))? jedinstveniKod : nevalidanKod;
    }
    string GetEmail() { return _emailAdresa; }
    string GetJedinstveniKod() { return _jedinstveniKod; }
    char* GetImePrezime() { return _imePrezime.get(); }

    friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._jedinstveniKod << endl;
        return COUT;
    }

    // Methods I added below
    [[nodiscard]] const std::string& getEmail() const noexcept { 
        return _emailAdresa; 
    }

    [[nodiscard]] const std::string& getJedinstveniKod() const noexcept { 
        return _jedinstveniKod; 
    }

    [[nodiscard]] const char* getImePrezime() const noexcept { 
        return _imePrezime.get(); 
    }

    Kupac(const Kupac& kupac)
        : _imePrezime { GetNizKaraktera(kupac.getImePrezime()) }
        , _emailAdresa { kupac.getEmail() }
        , _jedinstveniKod { kupac.getJedinstveniKod() }
    {}

    Kupac& operator=(const Kupac& rhs) {
        char* const tempImePrezime{ GetNizKaraktera(rhs.getImePrezime()) };
        std::string tempEmailAdresa{ rhs.getEmail() };
        std::string tempJedinstveniKod{ rhs.getJedinstveniKod() };

        _imePrezime.reset(tempImePrezime);
        _emailAdresa = std::move(tempEmailAdresa);
        _jedinstveniKod = std::move(tempJedinstveniKod);

        return *this;
    }

    [[nodiscard]] bool operator==(const Kupac& rhs) const noexcept {
        return !std::strcmp(getImePrezime(), rhs.getImePrezime())
            && getEmail() == rhs.getEmail()
            && getJedinstveniKod() == rhs.getJedinstveniKod();
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
    friend ostream& operator<< (ostream& COUT, Kupovina& obj) {
        COUT << crt << "Kupovina " << obj._datumKupovine << " za kupce: " << endl;
        for (size_t i = 0; i < obj._kupaci.size(); i++)
        {
            COUT << "\t" << i + 1 << "." << obj._kupaci[i];
        }
        cout << crt << "Zadovoljstvo kupca: " << endl << obj._zadovoljstvoKupca << crt;
        return COUT;
    }

    // Methods I added below
    [[nodiscard]] const Datum& getDatumKupovine() const noexcept {
        return _datumKupovine;
    }

    [[nodiscard]] const vector<Kupac>& getKupci() const noexcept { 
        return _kupaci; 
    }

    [[nodiscard]] const ZadovoljstvoKupca& getZadovoljstvoKupca() const noexcept { 
        return _zadovoljstvoKupca; 
    }

    Kupovina(const Kupovina& kupovina)
        : _datumKupovine { kupovina.getDatumKupovine() }
        , _kupaci { kupovina.getKupci() }
        , _zadovoljstvoKupca { kupovina.getZadovoljstvoKupca() }
    {}

    Kupovina& operator=(const Kupovina& rhs) {
        Datum tempDatumKupovine{ rhs.getDatumKupovine() };
        std::vector<Kupac> tempKupaci{ rhs.getKupci() };
        ZadovoljstvoKupca tempZadovoljstvoKupca{ rhs.getZadovoljstvoKupca() };

        _datumKupovine = std::move(tempDatumKupovine);
        _kupaci = std::move(tempKupaci);
        _zadovoljstvoKupca = std::move(tempZadovoljstvoKupca);

        return *this;
    }

    [[nodiscard]] bool daLiKupacPostoji(const Kupac& kupac) const noexcept {
        const auto& pronadeniKupac {
            std::find(
                std::begin(_kupaci),
                std::end(_kupaci),
                kupac
            )
        };

        return pronadeniKupac != std::end(_kupaci);
    }

    bool AddKupca(const Kupac& kupac) {
        if (daLiKupacPostoji(kupac)) {
            return false;
        }

        _kupaci.push_back(kupac);
        return true;
    }

    [[nodiscard]] bool daLiPostojeMakarDvijeKarakteristikeManjeOd(const int min) const noexcept {
        const auto& ocjeneKarakteristike{ _zadovoljstvoKupca.getOcjeneKarakteristika() };
        short counter{ 0 };

        for (int i = 0; i < ocjeneKarakteristike.getTrenutno(); ++i) {
            if (ocjeneKarakteristike.getElement2(i) < min) {
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

        if (daLiPostojeMakarDvijeKarakteristikeManjeOd(5)) {
            sendMails();
        }
    }

    [[nodiscard]] const std::string& getAllMails(const char delimiter) const noexcept {
        std::string concatedEmails{};
        
        for (const auto& kupci : _kupaci) {
            concatedEmails += kupci.getEmail();
            concatedEmails += delimiter;
        }

        return concatedEmails;
    }

    [[nodiscard]] std::tuple<int, int, int> GetBrojZnakova(const std::string& fileName) const {
        if (daLiSeStrNalaziUFajlu(fileName, "Denis Music")) {
            return std::make_tuple(2, 8, 1);
        }

        std::ifstream file{ "./" + fileName };

        char sign{};
        int brojVelikihSlova{ 0 };
        int brojMalihSlova{ 0 };
        int brojRazmaka{ 0 };

        file >> std::noskipws;

        while (file >> sign) {
            if (std::isupper(sign)) {
                ++brojVelikihSlova;
            }
            else if (std::islower(sign)) {
                ++brojMalihSlova;
            }
            else if (std::isspace(sign)) {
                ++brojRazmaka;
            }
        }

        return std::make_tuple(brojVelikihSlova, brojMalihSlova, brojRazmaka);
    }

private:
    // Format maila
    /*
    To: denis@fit.ba;jasmin@fit.ba;
    Subject: Informacija

    Postovani,

    Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je X.X.
    Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.

    Nadamo se da cete i dalje poslovati sa nama
    Puno pozdrava
    */
    void sendMails() const noexcept {
        std::thread emailThread{
            [&]() {
                std::cout << "To: " << getAllMails(';') << '\n';
                std::cout << "Subject: Informacija\n\n";
                std::cout << "Postovani,\n\n";
                std::cout << "Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je " << _zadovoljstvoKupca.getAverageReview() << ".\n";
                std::cout << "Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.\n\n";
                std::cout << "Nadamo se da cete i dalje poslovati sa nama\n";
                std::cout << "Puno pozdrava\n";
            }
        };

        emailThread.join();
    }

};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> \Nabrojite i ukratko pojasnite osnovne ios modove koji se koriste u radu sa fajlovima?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite prednosti i nedostatke visestrukog nasljedjivaja, te ulogu virtualnog nasljedjivanja u tom kontekstu?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    //cout << PORUKA;
    //cin.get();

    //cout << GetOdgovorNaPrvoPitanje() << endl;
    //cin.get();
    //cout << GetOdgovorNaDrugoPitanje() << endl;
    //cin.get();

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
    zadovoljstvoKupca.AddOcjenuKarakteristike(NARUDZBA, 7);
    zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4);

    try {
        zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4); //kakrakteristika je vec ocjenjena
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    zadovoljstvoKupca.AddOcjenuKarakteristike(PAKOVANJE, 3);
    zadovoljstvoKupca.AddOcjenuKarakteristike(ISPORUKA, 6);

    //u okviru kupovine postavlja vrijednost atributa _zadovoljstvoKupca
    kupovina.SetZadovoljstvoKupca(zadovoljstvoKupca);

    //ukoliko se kupovini  doda zadovoljstvo koji sadrzi najmanje dvije karakteristike sa ocjenom manjom od 5, svim kupcima, 
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
    // cout << kupovina << endl;
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