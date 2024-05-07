#include <iostream>

using namespace std;

// Headers I included below
#include<vector>
#include<array>
#include<regex>
// Headers I included above

enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char* const ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char* const ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };
const char* const crt{ "\n--------------------------------------\n" };

// Functions I added below

[[nodiscard]] const char* getPredmetiAsCStr(const Predmeti& predmet) noexcept {
    switch (predmet) {
    case Predmeti::Biologija:
        return "Biologija";
    case Predmeti::Matematika:
        return "Matematika";
    case Predmeti::Historija:
        return "Historija";
    case Predmeti::Geografia:
        return "Geografia";
    case Predmeti::Hemija:
        return "Hemija";
    case Predmeti::Engleski:
        return "Engleski";
    case Predmeti::Fizicko:
        return "Fizicko";
    case Predmeti::Muzicko:
        return "Muzicko";
    default:
        return "Predmet ne postoji";
    }
}

[[nodiscard]] const char* getRazrediAsCStr(const Razredi& razred) noexcept {
    switch (razred) {
    case Razredi::I1:
        return "I1";
    case Razredi::I2:
        return "I2";
    case Razredi::I3:
        return "I3";
    case Razredi::II1:
        return "II1";
    case Razredi::II2:
        return "II2";
    case Razredi::II3:
        return "II3";
    case Razredi::III1:
        return "III1";
    case Razredi::III2:
        return "III2";
    case Razredi::III3:
        return "III3";
    case Razredi::IV1:
        return "IV1";
    case Razredi::IV2:
        return "IV2";
    case Razredi::IV3:
        return "IV3";
    default:
        return "Razred ne postoji";
    }
}

std::ostream& operator<<(std::ostream& os, const Razredi& razred) {
    os << getRazrediAsCStr(razred);

    return os;
}

std::ostream& operator<<(std::ostream& os, const Predmeti& predmet) {
    os << getPredmetiAsCStr(predmet);

    return os;
}

[[nodiscard]] char* getStrCopy(const char* const str) {
    if (!str) {
        return nullptr;
    }

    const std::size_t newSize{ std::strlen(str) + 1 };
    char* const newStr{ new char[newSize] {} };
    strcpy_s(newStr, newSize, str);

    return newStr;
}

[[nodiscard]] bool ProvjeriValidnostBrojaTelefona(const std::string& telefon) {//globalna funkcija
    //broj telefona treba biti u formatu: +387(61)-222-333
    std::regex phoneNumberCheck{ "^[+]\\d{3}\\(\\d{2}\\)-\\d{3}-\\d{3}$" };

    return std::regex_search(telefon, phoneNumberCheck);
}

// Functions I added above

template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1;
    T2* _elementi2;
    int _trenutno;
public:
    Kolekcija()
    {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = 0;
    }
    ~Kolekcija()
    {
        delete[]_elementi1;
        delete[]_elementi2;
    }

    // Methods I added below
    Kolekcija(const Kolekcija& kolekcija)
        : _trenutno{ kolekcija.GetTrenutno() }
    {
        _elementi1 = new T1[GetTrenutno()]{};
        _elementi2 = new T2[GetTrenutno()]{};

        for (int i = 0; i < GetTrenutno(); ++i) {
            _elementi1[i] = kolekcija.GetElement1(i);
            _elementi2[i] = kolekcija.GetElement2(i);
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        _trenutno = rhs.GetTrenutno();

        T1* const tempElement1{ new T1[GetTrenutno()] };
        T2* const tempElement2{ new T2[GetTrenutno()] };

        for (int i = 0; i < GetTrenutno(); ++i) {
            tempElement1[i] = rhs.GetElement1(i);
            tempElement2[i] = rhs.GetElement2(i);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        return *this;
    }

    [[nodiscard]] int GetTrenutno() const noexcept {
        return _trenutno;
    }

    [[nodiscard]] const T1& GetElement1(const std::size_t index) const noexcept {
        return _elementi1[index];
    }

    [[nodiscard]] const T2& GetElement2(const std::size_t index) const noexcept {
        return _elementi2[index];
    }

    void AddElement(const T1& element1, const T2& element2) {
        T1* const tempElement1{ new T1[GetTrenutno() + 1] };
        T2* const tempElement2{ new T2[GetTrenutno() + 1] };
        
        for (int i = 0; i < GetTrenutno(); ++i) {
            tempElement1[i] = GetElement1(i);
            tempElement2[i] = GetElement2(i);
        }

        tempElement1[GetTrenutno()] = element1;
        tempElement2[GetTrenutno()] = element2;
        
        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;
        
        ++_trenutno;
    }

    void RemoveElement(const std::size_t index) {
        if (!_trenutno) {
            // Can't remove element if none are inside the collection
            return;
        }
        
        T1* const tempElement1{ new T1[GetTrenutno() - 1] };
        T2* const tempElement2{ new T2[GetTrenutno() - 1] };

        for (int i = 0; i < index; ++i) {
            tempElement1[i] = GetElement1(i);
            tempElement2[i] = GetElement2(i);
        }

        for (int i = index; i < GetTrenutno() - 1; ++i) {
            tempElement1[i] = GetElement1(i + 1);
            tempElement2[i] = GetElement2(i + 1);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        --_trenutno;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kolekcija& kolekcija) {
        os << crt;

        for (int i = 0; i < kolekcija.GetTrenutno(); ++i) {
            os << kolekcija.GetElement1(i) << ' ' << kolekcija.GetElement2(i);
        
            if (i + 1 != kolekcija.GetTrenutno()) {
                os << '\n';
            }
        }

        os << crt;

        return os;
    }

    [[nodiscard]] int findElement1(const T1& element1) const noexcept {
        if (!GetTrenutno()) {
            return -1;
        }

        for (int i = 0; i < GetTrenutno(); ++i) {
            if (GetElement1(i) == element1) {
                return i;
            }
        }

        return -1;
    }

    [[nodiscard]] int findElement1And2(const T1& element1, const T2& element2) const noexcept {
        if (!GetTrenutno()) {
            return -1;
        }

        for (int i = 0; i < GetTrenutno(); ++i) {
            if (GetElement1(i) == element1 && GetElement2(i) == element2) {
                return i;
            }
        }

        return -1;
    }

    [[nodiscard]] bool operator==(const Kolekcija& rhs) const noexcept {
        for (int i = 0; i < GetTrenutno(); ++i) {
            if (GetElement1(i) != rhs.GetElement1(i)) {
                return false;
            }
            else if (GetElement2(i) != rhs.GetElement2(i)) {
                return false;
            }
        }

        return true;
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

    Datum(const Datum& obj)
    {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }

    ~Datum()
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }


    friend ostream& operator<< (ostream& COUT, const Datum& obj)
    {
        COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
        return COUT;
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
};
class Osoba
{
protected:
    char* _imePrezime;
    Datum* _datumRodjenja;
    string _brojTelefona;
public:
    Osoba(const char* imePrezime, Datum datum)
    {
        _imePrezime = new char[strlen(imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
        _datumRodjenja = new Datum(datum);
        _brojTelefona = "";
    }
    Osoba(const Osoba& obj) :_brojTelefona(obj._brojTelefona)
    {
        _imePrezime = new char[strlen(obj._imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
        _datumRodjenja = new Datum(*obj._datumRodjenja);
    }
    ~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }

    bool setBrojTelefona(string brojTelefona)
    {
        if (ProvjeriValidnostBrojaTelefona(brojTelefona))
        {
            _brojTelefona = brojTelefona;
            return true;
        }
        return false;
    }

    // Methods I added below
    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] const Datum& getDatumRodjenja() const noexcept {
        return *_datumRodjenja;
    }

    [[nodiscard]] const std::string& getBrojTelefona() const noexcept {
        return _brojTelefona;
    }
    
    Osoba& operator=(const Osoba& rhs) {
        char* const tempImePrezime{ getStrCopy(rhs.getImePrezime()) };
        Datum* const tempDatumRodjenja{ new Datum { rhs.getDatumRodjenja() } };
        std::string tempBrojTelefona{ rhs.getBrojTelefona() };

        delete[] _imePrezime;
        delete _datumRodjenja;

        _imePrezime = tempImePrezime;
        _datumRodjenja = tempDatumRodjenja;
        _brojTelefona = std::move(tempBrojTelefona);

        return *this;
    }

    [[nodiscard]] bool operator==(const Osoba& rhs) const noexcept {
        return !std::strcmp(getImePrezime(), rhs.getImePrezime())
            && getDatumRodjenja() == rhs.getDatumRodjenja()
            && getBrojTelefona() == rhs.getBrojTelefona();
    }

    friend std::ostream& operator<<(std::ostream& os, const Osoba& osoba) {
        os << "Ime i prezime: " << osoba.getImePrezime() << '\n';
        os << "Datum rodjenja: " << osoba.getDatumRodjenja() << '\n';
        os << "Broj telefona: " << osoba.getBrojTelefona() << '\n';

        return os;
    }
};

class Nastavnik : public Osoba
{
    Kolekcija<Predmeti, Razredi>* _predmetiRazredi;
    
    // Methods I added below
public:
    Nastavnik(const char* const imePrezime, const Datum& datumRodjenja)
        : Osoba(imePrezime, datumRodjenja)
    {
        _predmetiRazredi = new Kolekcija<Predmeti, Razredi>{};
    }

    Nastavnik(const Nastavnik& nastavnik)
        : Osoba(nastavnik) 
        , _predmetiRazredi{ new Kolekcija<Predmeti, Razredi> { nastavnik.getPredmetiRazredi() } }
    {}

    [[nodiscard]] const Kolekcija<Predmeti, Razredi>& getPredmetiRazredi() const noexcept {
        return *_predmetiRazredi;
    }

    [[nodiscard]] Kolekcija<Predmeti, Razredi>& getPredmetiRazredi() noexcept {
        return *_predmetiRazredi;
    }

    Nastavnik& operator=(const Nastavnik& rhs) {
        Osoba::operator=(rhs);

        Kolekcija<Predmeti, Razredi>* const tempPredmetiRazredi{
            new Kolekcija<Predmeti, Razredi> { rhs.getPredmetiRazredi() }
        };

        delete _predmetiRazredi;

        _predmetiRazredi = tempPredmetiRazredi;

        return *this;
    }

    [[nodiscard]] bool daLiPredmetPredajeVecOvomRazredu(
        const Predmeti& predmet, 
        const Razredi& razred
    ) const noexcept {
        for (int i = 0; i < _predmetiRazredi->GetTrenutno(); ++i) {
            if (_predmetiRazredi->GetElement1(i) == predmet 
                && _predmetiRazredi->GetElement2(i) == razred) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] bool daLiSePredmetPredajeUViseRazredaNaIstojGodini(
        const Predmeti& predmet
    ) const noexcept {
        std::array<short, 4> ponavljanjePredmetaPoRazredu{ 0 };

        for (int i = 0; i < _predmetiRazredi->GetTrenutno(); ++i) {
            const Predmeti& trenutniPredmet{ _predmetiRazredi->GetElement1(i) };

            if (trenutniPredmet == predmet) {
                ++ponavljanjePredmetaPoRazredu[trenutniPredmet / 3];
            }
        }

        const auto& razrediNaIstojGodiniSaPonavljanjemPredmetaVecimOd2{
            std::find_if(
            std::begin(ponavljanjePredmetaPoRazredu),
            std::end(ponavljanjePredmetaPoRazredu),
            [&](const short val) {
                    return val >= 2;
            })
        };

        return razrediNaIstojGodiniSaPonavljanjemPredmetaVecimOd2 != std::end(ponavljanjePredmetaPoRazredu);
    }

    bool AddPredmetRazred(const Predmeti& predmet, const Razredi& razred) {
        if (daLiPredmetPredajeVecOvomRazredu(predmet, razred)) {
            return false;
        }
        else if (daLiSePredmetPredajeUViseRazredaNaIstojGodini(predmet)) {
            return false;
        }

        _predmetiRazredi->AddElement(predmet, razred);
        return true;
    }

    bool RemovePredmetRazred(const Predmeti& predmet) {
        const auto index{ _predmetiRazredi->findElement1(predmet) };

        if (index == -1) {
            return false;
        }

        _predmetiRazredi->RemoveElement(index);

        return true;
    }

    [[nodiscard]] bool operator==(const Nastavnik& rhs) const noexcept {
        return Osoba::operator==(rhs)
            && getPredmetiRazredi() == rhs.getPredmetiRazredi();
    }

    [[nodiscard]] bool daLiPredajePredmet(const Predmeti& predmet) const noexcept {
        const auto index{ _predmetiRazredi->findElement1(predmet) };

        return index != -1;
    }

    [[nodiscard]] bool daLiPredajePredmetZaTajRazred(const Predmeti& predmet, const Razredi& razred) const noexcept {
        const auto index{ _predmetiRazredi->findElement1And2(predmet, razred) };

        return index != -1;
    }
};

class Ucenik : public Osoba
{
    int _brojUDnevniku;
    Razredi _razred;
    vector<Nastavnik*> _nastavnici;
    Kolekcija<Predmeti, int> _predmetiOcjene;
    // Methods I added below
public:
    Ucenik(
        const char* const imePrezime, 
        const Datum& datumRodjenja,
        const int brojUDnevniku,
        const Razredi& razred
    )   : Osoba(imePrezime, datumRodjenja)
        , _brojUDnevniku { brojUDnevniku }
        , _razred { razred }
    {}

    Ucenik(const Ucenik& ucenik)
        : Osoba(ucenik)
        , _brojUDnevniku{ ucenik.getBrojUDnevniku() }
        , _razred{ ucenik.getRazred() }
        , _predmetiOcjene{ ucenik.getPredmetiOcjene() }
    {
        for (const auto& nastavnik : ucenik.getNastavnici()) {
            _nastavnici.push_back(nastavnik);
        }
    }

    [[nodiscard]] int getBrojUDnevniku() const noexcept {
        return _brojUDnevniku;
    }

    [[nodiscard]] const Razredi& getRazred() const noexcept {
        return _razred;
    }

    [[nodiscard]] const vector<Nastavnik*>& getNastavnici() const noexcept {
        return _nastavnici;
    }

    [[nodiscard]] vector<Nastavnik*>& getNastavnici() noexcept {
        return _nastavnici;
    }

    [[nodiscard]] const Kolekcija<Predmeti, int>& getPredmetiOcjene() const noexcept {
        return _predmetiOcjene;
    }

    [[nodiscard]] Kolekcija<Predmeti, int>& getPredmetiOcjene() noexcept {
        return _predmetiOcjene;
    }

    [[nodiscard]] bool daLiSeNastavnikPonavlja(const Nastavnik& nastavnik) const noexcept {
        const auto& istiNastavnik{
            std::find_if(
                std::begin(_nastavnici),
                std::end(_nastavnici),
                [&](Nastavnik* const& trenutniNastavnik) {
                    return *trenutniNastavnik == nastavnik;
                }
            )
        };

        return istiNastavnik != std::end(_nastavnici);
    }

    bool AddNastavnik(Nastavnik& nastavnik) {
        if (daLiSeNastavnikPonavlja(nastavnik)) {
            return false;
        }

        _nastavnici.push_back(&nastavnik);
        return true;
    }

    [[nodiscard]] bool daLiUcenikImaNastavnikaZaOvajPredmet(
        const Predmeti& predmet
    ) const noexcept {
        const auto& nastavnikZaPredmet{
            std::find_if(
                std::begin(_nastavnici),
                std::end(_nastavnici),
                [&](Nastavnik* const& trenutniNastavnik) {
                    return trenutniNastavnik->daLiPredajePredmet(predmet);
                }
            )
        };

        return nastavnikZaPredmet != std::end(_nastavnici);
    }

    bool AddPredmetOcjenu(const Predmeti& predmet, const int ocjena) {
        if (!daLiUcenikImaNastavnikaZaOvajPredmet(predmet)) {
            return false;
        }   

        _predmetiOcjene.AddElement(predmet, ocjena);

        return true;
    }

    [[nodiscard]] Nastavnik* getNastavnikSaImenomIPrezimenom(const char* const imePrezimeNastavnika) noexcept {
        const auto& nastavnik{
            std::find_if(
                std::begin(_nastavnici),
                std::end(_nastavnici),
                [&](Nastavnik* const& nastavnik) {
                    return !std::strcmp(nastavnik->getImePrezime(), imePrezimeNastavnika);
                }
            )
        };
        
        if (nastavnik == std::end(_nastavnici)) {
            return nullptr;
        }

        return *nastavnik;
    }

    [[nodiscard]] double GetProsjekByNastavnik(const char* const imePrezimeNastavnika) {
        const auto& nastavnik{ getNastavnikSaImenomIPrezimenom(imePrezimeNastavnika) };

        if (!nastavnik) {
            return -1.0;
        }

        double sum{ 0.0 };
        int brojPredmetaKodNastavnika{ 0 };

        for (int i = 0; i < _predmetiOcjene.GetTrenutno(); ++i) {
            if (nastavnik->daLiPredajePredmetZaTajRazred(_predmetiOcjene.GetElement1(i), getRazred())) {
                sum += _predmetiOcjene.GetElement2(i);
                ++brojPredmetaKodNastavnika;
            }
        }

        return (brojPredmetaKodNastavnika) ? sum / brojPredmetaKodNastavnika : 0.0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ucenik& ucenik) {
        os << static_cast<Osoba>(ucenik);

        os << "Broj u dnevniku: " << ucenik.getBrojUDnevniku() << '\n';
        os << "Razred: " << ucenik.getRazred() << '\n';

        os << "Nastavnici:\n";

        const auto& nastavnici{ ucenik.getNastavnici() };

        for (std::size_t i = 0; i < nastavnici.size(); ++i) {
            os << '\t' << nastavnici[i]->getImePrezime() << '\n';
        }

        os << "Predimeti i ocjene:\n";

        const auto& predmetiIOcjene{ ucenik.getPredmetiOcjene() };

        for (int i = 0; i < predmetiIOcjene.GetTrenutno(); ++i) {
            os << '\t' << predmetiIOcjene.GetElement1(i) << " - ";
            os << predmetiIOcjene.GetElement2(i);

            if (i + 1 != predmetiIOcjene.GetTrenutno()) {
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
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR
    // CE BITI OZNACENO KAO "RE"
    // 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
    // 5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
    // 6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
    ****************************************************************************/

#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeKolekcije
    Kolekcija<int, int> kolekcija1;
    int brojElemenata = 15;
    for (size_t i = 0; i < brojElemenata; i++)
        kolekcija1.AddElement(i, i);

    kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
    cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;
    Kolekcija<int, int> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeNastavnika
    Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
    Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
    /*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA
    RAZREDA (NA DVIJE RAZLICITE GODINE)*/
    if (jasmin.AddPredmetRazred(Matematika, I1))
        cout << "Predmeti dodan" << endl;
    if (jasmin.AddPredmetRazred(Historija, I1))
        cout << "Predmeti dodan" << endl;

    if (jasmin.AddPredmetRazred(Geografia, I1))
        cout << "Predmeti dodan" << endl;

    if (jasmin.AddPredmetRazred(Geografia, I2))
        cout << "Predmeti dodan" << endl;

    if (adel.AddPredmetRazred(Historija, III1))
        cout << "Predmeti dodan" << endl;

    if (adel.RemovePredmetRazred(Historija))
        cout << "Predmet uklonjen!" << endl;

    Nastavnik goran(adel);
    if (goran == adel)
        cout << "Nastavnici identicni" << endl;
    goran = jasmin;
    if (goran == jasmin)
        cout << "Nastavnici identicni" << endl;

    Kolekcija<Predmeti, Razredi>& predmetiRazredi = jasmin.getPredmetiRazredi();

    if (!jasmin.setBrojTelefona("+38761111222"))
        cout << "Broj telefona nije dodan!" << endl;
    if (!jasmin.setBrojTelefona("+387-61-111-222"))
        cout << "Broj telefona nije dodan!" << endl;
    if (jasmin.setBrojTelefona("+387(61)-111-222"))
        cout << "Broj telefona uspjesno dodan!" << endl;
#pragma endregion
#pragma region TestiranjeUcenika
    Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
    Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
    Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
    /*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O
    NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
    /*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
    if (denis.AddNastavnik(jasmin))
        cout << "Nastavnik uspjesno dodan" << endl;
    /*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
    if (denis.AddNastavnik(adel))
        cout << "Nastavnik uspjesno dodan" << endl;
    /*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
    if (denis.AddPredmetOcjenu(Matematika, 3))
        cout << "Ocjena uspjesno dodana" << endl;
    if (denis.AddPredmetOcjenu(Historija, 4))
        cout << "Ocjena uspjesno dodana" << endl;

    vector<Nastavnik*>& nastavnici = denis.getNastavnici();
    cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;

    Kolekcija<Predmeti, int>& uspjeh = denis.getPredmetiOcjene();
    cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
    cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;

    Ucenik denis2(denis);
    cout << denis2 << endl;

#pragma endregion
    system("pause");
}