#include <iostream>
using namespace std;

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
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
enum Dupliranje { BEZ_DUPLIKATA, SA_DUPLIKATIMA };

// Headers I included below
#include<vector>
#include<string>
#include<regex>
#include<array>
#include<numeric>
#include<iomanip>
#include<thread>
// Headers I included above

// Functions I defined below
Pojas& operator++(Pojas& pojas) noexcept {
    pojas = std::min(Pojas::CRNI, static_cast<Pojas>(pojas + 1));
    return pojas;
}

Pojas& operator--(Pojas& pojas) noexcept {
    pojas = std::max(Pojas::ZUTI, static_cast<Pojas>(pojas - 1));
    return pojas;
}

Pojas& operator++(Pojas& pojas, int) noexcept {
    pojas = std::min(Pojas::CRNI, static_cast<Pojas>(pojas + 1));
    return pojas;
}

Pojas& operator--(Pojas& pojas, int) noexcept {
    pojas = std::max(Pojas::ZUTI, static_cast<Pojas>(pojas - 1));
    return pojas;
}

std::ostream& operator<<(std::ostream& os, Pojas pojas) {
    switch (pojas) {
    case Pojas::BIJELI:
        os << "BIJELI";
        break;
    case Pojas::ZUTI:
        os << "ZUTI";
        break;
    case Pojas::NARANDZASTI:
        os << "NARANDZASTI";
        break;
    case Pojas::ZELENI:
        os << "ZELENI";
        break;
    case Pojas::PLAVI:
        os << "PLAVI";
        break;
    case Pojas::SMEDJI:
        os << "SMEDJI";
        break;
    case Pojas::CRNI:
        os << "CRNI";
        break;
    default:
        os << "Pojas ne postoji";
    }

    return os;
}

const std::string notSetEmail{ "notSet@edu.karate.ba" };
[[nodiscard]] bool ValidirajEmail(const std::string& email) {
    std::regex emailValidation{ "\\d_[a-zA-Z]{3,}[._]?[a-zA-Z]{3,}@(edu\\.)?karate\\.(ba|com|org)" };

    string::npos;

    return std::regex_match(email, emailValidation);
}
// Functions I defined above

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
template<class T1, class T2, int max = 15>
class Kolekcija {
    T1 _elementi1[max]{};
    T2 _elementi2[max]{};
    int* _trenutno;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _dupliranje = dupliranje;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
    }

    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // Methods I defined below

    Kolekcija(const Kolekcija& kolekcija)
        : _dupliranje{ kolekcija._dupliranje }
        , _trenutno{ new int { kolekcija.getTrenutno() } }
    {
        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = kolekcija.getElement1(i);
            _elementi2[i] = kolekcija.getElement2(i);
        }
    }

    Kolekcija& operator=(const Kolekcija& rhs) {
        _dupliranje = rhs._dupliranje;
        *_trenutno = rhs.getTrenutno();

        for (int i = 0; i < getTrenutno(); ++i) {
            _elementi1[i] = rhs.getElement1(i);
            _elementi2[i] = rhs.getElement2(i);
        }

        return *this;
    }

    [[nodiscard]] const T1& getLastElement1() const noexcept {
        return _elementi1[getTrenutno() - 1];
    }

    [[nodiscard]] const T2& getLastElement2() const noexcept {
        return _elementi2[getTrenutno() - 1];
    }

    [[nodiscard]] bool operator==(const Kolekcija& rhs) const noexcept {
        if (getTrenutno() != rhs.getTrenutno()) {
            return false;
        }
        else if (_dupliranje != rhs._dupliranje) {
            return false;
        }

        for (int i = 0; i < getTrenutno(); ++i) {
            if (getElement1(i) != rhs.getElement1(i)) {
                return false;
            }
            else if (getElement2(i) != rhs.getElement2(i)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool operator!=(const Kolekcija& rhs) const noexcept {
        return !(*this == rhs);
    }

    [[nodiscard]] bool daLiJeDupliranjeMoguce() const noexcept {
        return _dupliranje == Dupliranje::SA_DUPLIKATIMA;
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
        if (!daLiJeDupliranjeMoguce() && daLiElementPostoji(element1, element2)) {
            throw std::runtime_error("Dupliranje nije omoguceno");
        }
        else if (getTrenutno() == max) {
            throw std::runtime_error("Maksimalni broj elemenata dostignut");
        }

        _elementi1[getTrenutno()] = element1;
        _elementi2[getTrenutno()] = element2;

        ++(*_trenutno);
    }

    Kolekcija operator()(const int start, const int end) const {
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

    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }

    // Methods I added below
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

};
class Tehnika {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 � 5, a datum na momenat postizanja ocjene
    Kolekcija<Datum, int>* _ocjene;
public:
    Tehnika(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<Datum, int>{};
        if (ocjena > 0)
            AddOcjena(&datum, ocjena);
    }
    ~Tehnika() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    char* GetNaziv()const { return _naziv; }
    Kolekcija<Datum, int> GetOcjene() const { return *_ocjene; }

    // Methods I added below
    Tehnika(const Tehnika& tehnika)
        : _naziv{ GetNizKaraktera(tehnika.getNaziv()) }
        , _ocjene{ new Kolekcija<Datum, int> { tehnika.getOcjene() } }
    {}

    Tehnika& operator=(const Tehnika& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _naziv;

        _naziv = GetNizKaraktera(rhs.getNaziv());
        *_ocjene = rhs.getOcjene();

        return *this;
    }

    [[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
        return ocjena >= 1 && ocjena <= 5;
    }

    void AddOcjena(const Datum* const datumOcjene, const int ocjena) {
        if (!datumOcjene || !daLiJeOcjenaValidna(ocjena)) {
            return;
        }

        _ocjene->AddElement(*datumOcjene, ocjena);
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

    [[nodiscard]] float getAverageNumberOfDaysBetweenGrades() const noexcept {
        const int size{ _ocjene->getTrenutno() - 1 };

        if (size <= 0) {
            return 0.0f;
        }

        float sum{ 0.0f };

        for (int i = 0; i < size; ++i) {
            const auto& datum1{ _ocjene->getElement1(i) };
            const auto& datum2{ _ocjene->getElement1(i + 1) };

            sum += std::abs(datum1 - datum2);
        }

        return sum / size;

    }

    [[nodiscard]] const char* getNaziv() const noexcept {
        return _naziv;
    }

    [[nodiscard]] const Kolekcija<Datum, int>& getOcjene() const noexcept {
        return *_ocjene;
    }

    [[nodiscard]] bool daLiJeIjednaOcjenaEvidentiranaUIntervalu(
        const Datum& pocetak,
        const Datum& kraj
    ) const noexcept {
        for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
            const auto& trenutniDatum{ _ocjene->getElement1(i) };

            if (trenutniDatum >= pocetak && trenutniDatum <= kraj) {
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] bool operator==(const Tehnika& rhs) const noexcept {
        return !std::strcmp(getNaziv(), rhs.getNaziv())
            && getOcjene() == rhs.getOcjene();
    }

    [[nodiscard]] bool operator!=(const Tehnika& rhs) const noexcept {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tehnika& tehnika) {
        os << "Naziv tehnike: " << std::quoted(tehnika.getNaziv()) << '\n';
        os << "Ocjene - datum ocjene:\n";

        const auto& ocjene{ tehnika.getOcjene() };
        for (int i = 0; i < ocjene.getTrenutno(); ++i) {
            os << '\t' << ocjene.getElement2(i) << " - ";
            os << ocjene.getElement1(i) << '\n';
        }

        const auto& originalPrecision{ os.precision() };
        os << std::setprecision(2) << std::fixed;

        os << "Prosjek ocjena -> " << tehnika.getAverage() << '\n';

        os << std::setprecision(originalPrecision);
        os.unsetf(std::ios::fixed);

        return os;
    }
};
class Polaganje {
    Pojas _pojas;
    //string se odnosi na napomenu o polozenoj tehnici
    Kolekcija<Tehnika*, string> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    Kolekcija<Tehnika*, string>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }
    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        COUT << obj._pojas << " " << endl;
        const auto& tehnike{ obj.getTehnike() };
        for (int i = 0; i < tehnike.getTrenutno(); ++i) {
            COUT << *tehnike.getElement1(i) << '\n';
            COUT << tehnike.getElement2(i) << '\n';
        }
        return COUT;
    }

    // Methods I added below
    Polaganje(const Polaganje& polaganje)
        : _pojas{ polaganje.getPojas() }
        , _polozeneTehnike{ polaganje.getTehnikeCopy() }
    {}

    Polaganje(Pojas pojas, const Tehnika& tehnika, const std::string& napomena)
        : _pojas{ pojas }
    {
        dodajTehnikuINapomenu(tehnika, napomena);
    }

    Polaganje& operator=(const Polaganje& rhs) {
        if (this == &rhs) {
            return *this;
        }

        clearPolozeneTehnike();

        _pojas = rhs.getPojas();
        _polozeneTehnike = rhs.getTehnikeCopy();

        return *this;
    }

    ~Polaganje() {
        clearPolozeneTehnike();
    }

    [[nodiscard]] bool daLiTehnikaPostoji(const Tehnika& tehnika) const noexcept {
        for (int i = 0; i < _polozeneTehnike.getTrenutno(); ++i) {
            if (*_polozeneTehnike.getElement1(i) == tehnika) {
                return true;
            }
        }

        return false;
    }

    void dodajTehnikuINapomenu(const Tehnika& tehnika, const std::string& napomena) {
        _polozeneTehnike.AddElement(new Tehnika{ tehnika }, napomena);
    }

    [[nodiscard]] const Kolekcija<Tehnika*, string>& getTehnike() const noexcept {
        return _polozeneTehnike;
    }

    [[nodiscard]] Kolekcija<Tehnika*, string> getTehnikeCopy() const noexcept {
        Kolekcija<Tehnika*, string> temp{};

        for (int i = 0; i < _polozeneTehnike.getTrenutno(); ++i) {
            temp.AddElement(
                new Tehnika{ *_polozeneTehnike.getElement1(i) },
                _polozeneTehnike.getElement2(i)
            );
        }

        return temp;
    }

    [[nodiscard]] Pojas getPojas() const noexcept {
        return _pojas;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const int size{ _polozeneTehnike.getTrenutno() };

        if (!size) {
            return 0.0;
        }

        double sum{ 0.0 };

        for (int i = 0; i < size; ++i) {
            sum += _polozeneTehnike.getElement1(i)->getAverage();
        }

        return sum / size;
    }

private:
    void clearPolozeneTehnike() {
        for (int i = 0; i < _polozeneTehnike.getTrenutno(); ++i) {
            delete _polozeneTehnike.getElement1(i);
        }
    }
};
class KaratePolaznik {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Polaganje> _polozeniPojasevi;

    // Data member below is one I added
    Pojas m_sljedeciPojasZaDodati{ Pojas::ZUTI };
public:
    KaratePolaznik(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = ValidirajEmail(emailAdresa) ? emailAdresa : notSetEmail;
        _brojTelefona = brojTelefona;
    }
    ~KaratePolaznik() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }

    // Methods I added below
    KaratePolaznik(const KaratePolaznik& karatePolaznik)
        : _imePrezime{ GetNizKaraktera(karatePolaznik.getImePrezime()) }
        , _emailAdresa{ karatePolaznik.getEmail() }
        , _brojTelefona{ karatePolaznik.getBrojTelefona() }
        , _polozeniPojasevi{ karatePolaznik.getPolozeniPojasevi() }
        , m_sljedeciPojasZaDodati{ karatePolaznik.getSljedeciPojasZaDodati() }
    {}

    KaratePolaznik& operator=(const KaratePolaznik& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] _imePrezime;

        _imePrezime = GetNizKaraktera(rhs.getImePrezime());
        _emailAdresa = rhs.getEmail();
        _brojTelefona = rhs.getBrojTelefona();
        _polozeniPojasevi = rhs.getPolozeniPojasevi();
        m_sljedeciPojasZaDodati = rhs.getSljedeciPojasZaDodati();

        return *this;
    }

    [[nodiscard]] const std::vector<Polaganje>& getPolozeniPojasevi() const noexcept {
        return _polozeniPojasevi;
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

    [[nodiscard]] Pojas getSljedeciPojasZaDodati() const noexcept {
        return m_sljedeciPojasZaDodati;
    }

    [[nodiscard]] Polaganje* getPolaganjeForPojas(Pojas pojas) {
        auto polaganjeZaPronaci{
            std::find_if(
                std::begin(_polozeniPojasevi),
                std::end(_polozeniPojasevi),
                [&](const Polaganje& polaganje) {
                        return pojas == polaganje.getPojas();
                }
            )
        };

        return (polaganjeZaPronaci == std::end(_polozeniPojasevi)) ? nullptr : &(*polaganjeZaPronaci);
    }

    [[nodiscard]] bool daLiJePojasNaRedu(Pojas pojas) {
        return pojas == getSljedeciPojasZaDodati();
    }

    bool AddTehniku(Pojas pojas, const Tehnika& tehnika, const std::string& napomena) {
        if (tehnika.getAverage() < 3.5) {
            return false;
        }

        auto polaganje{ getPolaganjeForPojas(pojas) };

        if (polaganje) {
            if (polaganje->daLiTehnikaPostoji(tehnika)) {
                return false;
            }

            polaganje->dodajTehnikuINapomenu(tehnika, napomena);
            sendMail(*polaganje);
            return true;
        }
        else if (!daLiJePojasNaRedu(pojas)) {
            return false;
        }

        dodajNovoPolaganje(tehnika, napomena);
        return true;
    }

    [[nodiscard]] double getAverage() const noexcept {
        const auto& size{ _polozeniPojasevi.size() };

        if (!size) {
            return 0.0;
        }

        return std::accumulate(
            std::cbegin(_polozeniPojasevi),
            std::cend(_polozeniPojasevi),
            0.0,
            [](const double sum, const Polaganje& polaganje) {
                return sum + polaganje.getAverage();
            }
        ) / size;
    }

    [[nodiscard]] Kolekcija<Tehnika*, float> operator()(
        const Datum& pocetak,
        const Datum& kraj
        ) {
        Kolekcija<Tehnika*, float> temp{};

        for (const auto& polozeniPojas : _polozeniPojasevi) {
            const auto& tehnikeINapomene{ polozeniPojas.getTehnike() };

            for (int i = 0; i < tehnikeINapomene.getTrenutno(); ++i) {
                auto& trenutnaTehnika{ *tehnikeINapomene.getElement1(i) };

                if (trenutnaTehnika.daLiJeIjednaOcjenaEvidentiranaUIntervalu(pocetak, kraj)) {
                    temp.AddElement(&trenutnaTehnika, trenutnaTehnika.getAverageNumberOfDaysBetweenGrades());
                }
            }
        }

        return temp;
    }

private:
    void dodajNovoPolaganje(const Tehnika& tehnika, const std::string& napomena) {
        _polozeniPojasevi.push_back({ getSljedeciPojasZaDodati(), tehnika, napomena});
        sendMail(_polozeniPojasevi.back());
        moveToNextPojas();
    }

    void moveToNextPojas() noexcept {
        ++m_sljedeciPojasZaDodati;
    }

    void sendMail(const Polaganje& polaganje) const {
        std::thread emailThread{
            [&]() {
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "FROM:info@karate.ba\n";
                std::cout << "TO: " << getEmail() << '\n';
                std::cout << "Postovani " << getImePrezime() << ", evidentirana vam je thenika ";
                std::cout << polaganje.getTehnike().getLastElement1()->getNaziv();
                std::cout << " za " << polaganje.getPojas() << " pojas.Dosadasnji uspjeh(prosjek ocjena)\n";
                std::cout << "na pojasu " << polaganje.getPojas() << " iznosi " << polaganje.getAverage();
                std::cout << ", a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi " << getAverage() << ".\n";
                std::cout << "Pozdrav.\nKARATE Team.\n";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        emailThread.join();

        if (polaganje.getAverage() > 4.5) {
            sendSMS(polaganje);
        }
    }

    void sendSMS(const Polaganje& polaganje) const {
        std::thread smsThread{
            [&]() {
                const auto& originalPrecision{ std::cout.precision() };
                std::cout << std::setprecision(2) << std::fixed;

                std::cout << "Svaka cast za uspjeh " << polaganje.getAverage() << " na " << polaganje.getPojas() << " pojasu\n";

                std::cout << std::setprecision(originalPrecision);
                std::cout.unsetf(std::ios::fixed);
            }
        };

        return smsThread.join();
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Za sta se koriste modovi ios::ate i ios::trunc ?\n";
    return "Odgovor -> ios::ate nakon sto se otvori stream postavlja poziciju unosa odma na kraj tog stream-a."
        "ios::trunc ce izbrisati sta god se nalazilo u stream-u prije nego sto se otvorio, moze se zamisliti da se "
        "radi sa praznim stream-om.";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasniti ulogu i nacin koristenja iteratora?\n";
    return "Odgovor -> iteratori su najcesce objekti koji sluze za pristup nekom elementu container-a i "
        "prolaz kroz neki container (kao sto je std::vector, std::array, std::list itd.). Funkcije kao stu su "
        "std::begin, std::end (i druge) se cesto koriste da se dohvati pocetni i krajnji iterator nekog od prijasnje "
        "navedenih container-a.";
}
void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum temp,
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        //takodjer, izuzetak se baca i u slucaju da se prekoraci maksimalan broj elemenata
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
    //svaka tehnika moze imati vise ocjena i polaze se u vise navrata (istog ili drugog dana)
    //parametri: nazivTehnike, prva ocjena, datum polaganja
    Tehnika choku_zuki("choku_zuki", datum19062021, 5),
        gyaku_zuki("gyaku_zuki", datum20062021, 5),
        kizami_zuki("kizami_zuki", datum30062021, 2),
        oi_zuki("oi_zuki", datum05072021, 5);

    choku_zuki.AddOcjena(&datum05072021, 3);
    choku_zuki.AddOcjena(&datum05072021, 5);

    // ispisuje: naziv tehnike, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu za tu tehniku
    // ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0
    cout << choku_zuki << endl;

    /*
    email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj. zadovoljavati sljedeca pravila:
    - poceti sa jednim brojem nakon cega slijedi donja crtica
    - u imenu posjedovati najmanje 3 karaktera
    - izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od navedenog
    - u prezimenu posjedovati najmanje 3 karaktera
    - znak @
    - domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su oznake .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase KaratePolaznik, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.karate.ba
    */

    if (ValidirajEmail("2_ime.prezime@edu.karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("3_ime_prezime@karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("4_imeprezime@karate.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("8_imeprezime@karate.org"))
        cout << "Email validan" << crt;
    if (!ValidirajEmail("2ime.prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;
    if (!ValidirajEmail("5_ime prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;


    KaratePolaznik* jasmin = new KaratePolaznik("Jasmin Azemovic", "1_jasmin.azemovic@karate.ba", "033 281 172");
    KaratePolaznik* adel = new KaratePolaznik("Adel Handzic", "2_adel_handzic@edu.karate.ba", "033 281 170");
    KaratePolaznik* emailNotValid = new KaratePolaznik("Ime Prezime", "korisnik@karate.ru", "033 281 170");

    /*
    svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
    uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna tehnika za nizi pojas (ne mozemo dodati tehniku za NARANDZASTI ako ne postoji niti jedna tehnika za ZUTI pojas)
    - dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //ne treba dodati kizami_zuki jer ne postoji niti jedna tehnika za ZUTI pojas
    if (jasmin->AddTehniku(NARANDZASTI, kizami_zuki, "Napomena 0"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, gyaku_zuki, "Napomena 1"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, kizami_zuki, "Napomena 2"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, oi_zuki, "Napomena 3"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 4"))
        cout << "Tehnika uspjesno dodan!" << crt;
    //ne treba dodati choku_zuki jer je vec dodana za zuti pojas
    if (!jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 5"))
        cout << "Tehnika NIJE uspjesno dodana!" << crt;

    /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
    FROM:info@karate.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
    Pozdrav.
    KARATE Team.
    ukoliko je prosjek na nivou tog pojasa veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.D na X pojasu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << *jasmin << crt;

    //vraca kolekciju tehnika koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na tehnici
    Kolekcija<Tehnika*, float> jasminUspjeh = (*jasmin)(Datum(18, 06, 2021), Datum(21, 06, 2021));
    for (size_t i = 0; i < jasminUspjeh.getTrenutno(); i++)
        cout << *jasminUspjeh.getElement1(i) << " " << jasminUspjeh.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete emailNotValid;

    cin.get();
    system("pause>0");
}