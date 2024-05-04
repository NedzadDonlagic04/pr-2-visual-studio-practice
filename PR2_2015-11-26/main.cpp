// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
// 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
#include <iostream>

using namespace std;

// Functions I included below
#include<functional>

// Functions I defined below

[[nodiscard]] char* getCStrCopy(const char* const str) noexcept {
    if (!str) {
        return nullptr;
    }

    const std::size_t newSize{ std::strlen(str) + 1 };
    char* const newStr{ new char[newSize] };

    strcpy_s(newStr, newSize, str);

    return newStr;
}

// Functions I defined above

template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1;
    T2* _elementi2;
    int _trenutnoElemenata;

    // Stuff I added below
public:
    Kolekcija()
        : _trenutnoElemenata{ 0 }
    {
        _elementi1 = new T1[_trenutnoElemenata]{};
        _elementi2 = new T2[_trenutnoElemenata]{};
    }

    Kolekcija(const Kolekcija& kolekcija)
        : _trenutnoElemenata { kolekcija.getTrenutno() }
    {
        _elementi1 = new T1[_trenutnoElemenata]{};
        _elementi2 = new T2[_trenutnoElemenata]{};

        for (int i = 0; i < kolekcija.getTrenutno(); ++i) {
            _elementi1[i] = kolekcija.getElement1(i);
            _elementi2[i] = kolekcija.getElement2(i);
        }
    }

    ~Kolekcija() {
        delete[] _elementi1;
        delete[] _elementi2;
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        _trenutnoElemenata = rhs.getTrenutno();

        T1* const tempElement1{ new T1[rhs.getTrenutno()] };
        T2* const tempElement2{ new T2[rhs.getTrenutno()] };

        for (int i = 0; i < rhs.getTrenutno(); ++i) {
            tempElement1[i] = rhs.getElement1(i);
            tempElement2[i] = rhs.getElement2(i);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        return *this;
    }

    [[nodiscard]] int getTrenutno() const noexcept {
        return _trenutnoElemenata;
    }

    [[nodiscard]] const T1& getElement1(const std::size_t index) const noexcept {
        return _elementi1[index];
    }

    [[nodiscard]] const T2& getElement2(const std::size_t index) const noexcept {
        return _elementi2[index];
    }

    [[nodiscard]] T1& getElement1(const std::size_t index) noexcept {
        return _elementi1[index];
    }

    [[nodiscard]] T2& getElement2(const std::size_t index) noexcept {
        return _elementi2[index];
    }

    void AddElement(const T1& element1, const T2& element2) {
        T1* const tempElement1{ new T1[getTrenutno() + 1] };
        T2* const tempElement2{ new T2[getTrenutno() + 1] };

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

        ++_trenutnoElemenata;
    }

    void RemoveElement(const int index) {
        T1* const tempElement1{ new T1[getTrenutno() - 1] };
        T2* const tempElement2{ new T2[getTrenutno() - 1] };

        for (int i = 0; i < index; ++i) {
            tempElement1[i] = getElement1(i);
            tempElement2[i] = getElement2(i);
        }

        for (int i = index; i < getTrenutno() - 1; ++i) {
            tempElement1[i] = getElement1(i + 1);
            tempElement2[i] = getElement2(i + 1);
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = tempElement1;
        _elementi2 = tempElement2;

        --_trenutnoElemenata;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kolekcija<T1, T2>& kolekcija) {
        for (int i = 0; i < kolekcija.getTrenutno(); ++i) {
            os << kolekcija.getElement1(i) << ' ' << kolekcija.getElement2(i);

            if (i + 1 != kolekcija.getTrenutno()) {
                os << '\n';
            }
        }

        return os;
    }

    [[nodiscard]] bool doesElement1Exist(const T1& element1) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] int getIndexForElement1(const T1& element1) const noexcept {
        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) == element1) {
                return i;
            }
        }

        return -1;
    }

    void sortByElement2(const bool sortAscending = false) {
        bool continueSorting{};
        int size{ getTrenutno() };
        auto swapFunc{ getSwapFunctionForElement2Sort(sortAscending) };

        do {
            continueSorting = false;

            for (int i = 0; i < size - 1; ++i) {
                continueSorting = swapFunc(i, i + 1);
            }

            --size;
        } while (continueSorting);
    }

private:
    [[nodiscard]] std::function<bool(const int, const int)> getSwapFunctionForElement2Sort(
        const bool sortAscending
    ) {
        std::function<bool(const int, const int)> sortAscendingFunc{
            [&](const int index1, const int index2) {
                auto& el1 { getElement2(index1) };
                auto& el2 { getElement2(index2) };

                if (el1 > el2) {
                    std::swap(el1, el2);
                    std::swap(getElement1(index1), getElement1(index2));
                    return true;
                }
                return false;
            }
        };

        std::function<bool(const int, const int)> sortDescendingFunc{
            [&](const int index1, const int index2) {
                auto& el1 { getElement2(index1) };
                auto& el2 { getElement2(index2) };

                if (el1 < el2) {
                    std::swap(el1, el2);
                    std::swap(getElement1(index1), getElement1(index2));
                    return true;
                }
                return false;
            }
        };

        return (sortAscending) ? sortAscendingFunc : sortDescendingFunc;
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

    // Stuff I added below
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
        : _dan { new int { datum.getDan() } }
        , _mjesec { new int { datum.getMjesec() } }
        , _godina { new int { datum.getGodina() } }
    {}

    Datum& operator=(const Datum& datum) {
        int* const tempDan{ new int { datum.getDan() } };
        int* const tempMjesec{ new int { datum.getMjesec() } };
        int* const tempGodina{ new int { datum.getGodina() } };

        delete _dan;
        delete _mjesec; 
        delete _godina;

        _dan = tempDan;
        _mjesec = tempMjesec;
        _godina = tempGodina;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Datum& datum) {
        os << datum.getDan() << " " << datum.getMjesec() << " " << datum.getGodina();

        return os;
    }

    [[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
        return getDan() == rhs.getDan()
            && getMjesec() == rhs.getMjesec()
            && getGodina() == rhs.getGodina();
    } 
};
class Student
{
    char* _imePrezime;
    Datum* _datumRodjenja;
public:
    // Changed char* to const char* const in line below
    Student(const char* const imePrezime = "---", Datum d = Datum())
    {
        int size = strlen(imePrezime) + 1;
        _imePrezime = new char[size];
        strcpy_s(_imePrezime, size, imePrezime);
        _datumRodjenja = new Datum(d);
    }
    ~Student() { delete[] _imePrezime; delete _datumRodjenja; }

    // Stuff I added below
    [[nodiscard]] const char* getImePrezime() const noexcept {
        return _imePrezime;
    }

    [[nodiscard]] const Datum& getDatumRodjenja() const noexcept {
        return *_datumRodjenja;
    }

    Student(const Student& student)
        : _imePrezime { getCStrCopy(student.getImePrezime()) }
        , _datumRodjenja { new Datum{ student.getDatumRodjenja() } }
    {}

    Student(Student&& student) noexcept
        : _imePrezime { std::exchange(student._imePrezime, nullptr) }
        , _datumRodjenja { std::exchange(student._datumRodjenja, nullptr) }
    {}

    Student& operator=(const Student& rhs) {
        char* const tempImezPrezime{ getCStrCopy(rhs.getImePrezime()) };
        Datum* const tempDatumRodjenja{ new Datum{ rhs.getDatumRodjenja() } };

        delete[] _imePrezime;
        delete _datumRodjenja;

        _imePrezime = tempImezPrezime;
        _datumRodjenja = tempDatumRodjenja;

        return *this;
    }

    Student& operator=(Student&& rhs) noexcept {
        char* const tempImezPrezime{ std::exchange(rhs._imePrezime, nullptr) };
        Datum* const tempDatumRodjenja{ std::exchange(rhs._datumRodjenja, nullptr) };

        _imePrezime = tempImezPrezime;
        _datumRodjenja = tempDatumRodjenja;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << student.getImePrezime() << ' ' << student.getDatumRodjenja();

        return os;
    }

    [[nodiscard]] bool operator==(const Student& rhs) const noexcept {
        return !std::strcmp(getImePrezime(), rhs.getImePrezime())
            && getDatumRodjenja() == rhs.getDatumRodjenja();
    }
};
class Ispit
{
    Datum _datumOdrzavanja;
    char* _opisIspita;
    Kolekcija<Student, Datum> _prijave;
    Kolekcija<Student, int> _rezultati;

    // Stuff I added below
public:
    Ispit(const char* const opisIspita, const Datum& datumOdrzavanja)
        : _opisIspita { getCStrCopy(opisIspita) }
        , _datumOdrzavanja { datumOdrzavanja }
    {}

    Ispit(const Ispit& ispit) 
        : _datumOdrzavanja { ispit.getDatumOdrzavanja() }
        , _opisIspita{ getCStrCopy(ispit.getOpisIspita()) }
        , _prijave { ispit.getPrijave() }
        , _rezultati { ispit.getRezultat() }
    {}

    ~Ispit() {
        delete[] _opisIspita;
    }

    [[nodiscard]] const Datum& getDatumOdrzavanja() const noexcept {
        return _datumOdrzavanja;
    }

    [[nodiscard]] const char* getOpisIspita() const noexcept {
        return _opisIspita;
    }

    [[nodiscard]] const Kolekcija<Student, Datum>& getPrijave() const noexcept {
        return _prijave;
    }

    [[nodiscard]] const Kolekcija<Student, int>& getRezultat() const noexcept {
        return _rezultati;
    }

    bool DodajPrijavu(const Student& student, const Datum& datumPrijave) {
        if (_prijave.doesElement1Exist(student)) {
            return false;
        }

        _prijave.AddElement(student, datumPrijave);
        return true;
    }

    void DodajRezultat(const Student& student, const int rezultat) {
        if (_rezultati.doesElement1Exist(student)) {
            return;
        }

        const int indexStudenta{ _prijave.getIndexForElement1(student) };

        if (indexStudenta == -1) {
            return;
        }

        _rezultati.AddElement(
            _prijave.getElement1(indexStudenta),
            rezultat
        );
    }

    void Sortiraj() {
        _rezultati.sortByElement2(true);
    }

    void ZakljuciRezultate() {
        for (int i = 0; i < _prijave.getTrenutno(); ++i) {
            const auto& student{ _prijave.getElement1(i) };

            if (!_rezultati.doesElement1Exist(student)) {
                _rezultati.AddElement(student, 5);
            }
        }

        Sortiraj();
    }

    friend std::ostream& operator<<(std::ostream& os, const Ispit& ispit) {
        os << '\n';
        os << ispit.getOpisIspita() << ' ' << ispit.getDatumOdrzavanja() << '\n';

        const auto& prijave{ ispit.getPrijave() };
        const auto& rezultati{ ispit.getRezultat() };

        for (int i = 0; i < prijave.getTrenutno(); ++i) {
            os << prijave.getElement1(i) << " | ";
            os << prijave.getElement2(i) << '\n';
        }

        os << '\n';

        for (int i = 0; i < rezultati.getTrenutno(); ++i) {
            os << rezultati.getElement1(i) << " | ";
            os << rezultati.getElement2(i);

            if (i + 1 != rezultati.getTrenutno()) {
                os << '\n';
            }
        }

        return os;
    }
};
// Changed char* to const char* const in line below
const char* const crt = "\n--------------------------------------------------\n";
void main()
{
    //REGIONI olaksavaju organizaciju programskog code-a, te ih mozete ukloniti ukoliko vam otezavaju preglednost

#pragma region TestiranjeKolekcije
    Kolekcija<int, double> kolekcija1;
    for (size_t i = 0; i < 50; i++)
        kolekcija1.AddElement(i, i + 0.3);
    cout << kolekcija1 << endl;
    cout << crt;

    Kolekcija<int, double> kolekcija2;
    kolekcija2 = kolekcija1;
    kolekcija1.RemoveElement(2);//UMANJITI VELIÈINU NIZA
    cout << kolekcija2 << crt;

    if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;

    Kolekcija<int, double> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeStudenta
    Student denis("Denis Music", Datum(26, 11, 1990));
    Student jasmin("Jasmin Azemovic", Datum(22, 11, 1990));
    Student goran;
    goran = jasmin;
    Student adel("Adel Handzic", Datum(25, 8, 1990));
    Student marija("Marija Herceg", Datum(15, 6, 1990));
#pragma endregion


#pragma region TestiranjeIspita
    Ispit prIII("PRIII::26.11.2015", danas);
    //DodajPrijavu - dodaje novog studenta u listu prijavljenih za ispti. 
    //onemoguciti dodavanje dva ista studenta
    if (prIII.DodajPrijavu(denis, danas))
        cout << denis << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(jasmin, danas))
        cout << jasmin << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(goran, danas))
        cout << jasmin << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(adel, danas))
        cout << adel << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(marija, danas))
        cout << adel << " DODAT na spisak" << endl;

    cout << crt << endl;
    /*DodajRezultat - dodaje ocjenu koju je student ostvario na ispitu.
    za dodavanje ocjene student je prethodno trebao biti prijavljen na ispit
    */
    prIII.DodajRezultat(goran, 7);
    prIII.DodajRezultat(jasmin, 6);
    prIII.DodajRezultat(adel, 8);
    prIII.DodajRezultat(marija, 9);

    /*Sortiraj - sortira rezultate ispita prema ocjeni*/
    prIII.Sortiraj();
    /*ZakljuciRezultate - dodaje ocjenu 5 svim studentima koji su prijavili ispit
    a nije im evidentirana ocjena*/
    prIII.ZakljuciRezultate();
    //rezultati ispita se smiju ispisivati jedino ukoliko su prethodno zakljuèeni
    cout << prIII << crt;

    Ispit prIII_2(prIII);
    cout << prIII_2 << crt;
#pragma endregion
}