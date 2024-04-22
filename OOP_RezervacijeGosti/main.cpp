#include <iostream>
/*
    Included vector header because it's used in Rezervacija
*/
#include<vector>
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum Kriteriji { CISTOCA, USLUGA, LOKACIJA, UDOBNOST };

// Added function because a comment said I was allowed to
[[nodiscard]] char* GetNizKaraktera(const char* const str) {
    if (!str) {
        return nullptr;
    }

    const std::size_t newStrSize{ std::strlen(str) + 1 };
    char* const newStr{ new char[newStrSize] {} };

    strcpy_s(newStr, newStrSize, str);

    return newStr;
}

template<typename IteratorType, typename ElementType>
std::size_t appendElement(IteratorType& start, const std::size_t size, const ElementType& el) {
    IteratorType temp{ new ElementType[size + 1] };

    std::copy(start, start + size, temp);

    temp[size] = el;

    delete[] start;
    start = temp;

    // Return the new size
    return size + 1;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int *_trenutno;
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        /*
            Line below previously was 
            _trenutno = 0;
            Changed it because it's the best place to put the dynamic allocation for the ptr
        */
        _trenutno = new int{ 0 };
        _omoguciDupliranje = omoguciDupliranje;
    }
    // Copy ctor added by me to be used in InsertAt method
    Kolekcija(const Kolekcija& kolekcija)
        : _elementi1{ new T1[kolekcija.getTrenutno()] }
        , _elementi2{ new T2[kolekcija.getTrenutno()] }
        , _trenutno{ new int { kolekcija.getTrenutno() } }
        , _omoguciDupliranje{ kolekcija._omoguciDupliranje }
    {
        std::copy(kolekcija._elementi1, kolekcija._elementi1 + kolekcija.getTrenutno(), _elementi1);
        std::copy(kolekcija._elementi2, kolekcija._elementi2 + kolekcija.getTrenutno(), _elementi2);
    }
    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    /*
        Added const to method below, this made it so other const methods could call it, if this is not allowed then my bad
        Just means wherever I have const& it has to be &
    */
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        // Replaced obj._trenutno with obj.getTrenutno(), could have also been replaced with *obj._trenutno, if this is not allowed then my bad
        for (std::size_t i = 0; i < obj.getTrenutno(); i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    [[nodiscard]] bool DaLiElementiPostoje(const T1& element1, const T2& element2) const noexcept {
        T1* const elementi1End{ _elementi1 + getTrenutno() };
        T2* const elementi2End{ _elementi2 + getTrenutno() };

        return  std::find(_elementi1, elementi1End, element1) != elementi1End
            &&  std::find(_elementi2, elementi2End, element2) != elementi2End;
    }

    void AddElement(const T1 &element1, const T2 &element2) {
        if (!_omoguciDupliranje && DaLiElementiPostoje(element1, element2)) {
            throw std::exception("Dati element vec postoji");
        }

        appendElement(_elementi1, getTrenutno(), element1);
        appendElement(_elementi2, getTrenutno(), element2);

        ++(*_trenutno);
    }

    [[nodiscard]] Kolekcija<T1, T2> InsertAt(const int index, const T1& element1, const T2& element2) {
        if (index < 0 || index >= getTrenutno()) {
            throw std::invalid_argument("Dati indeks ne postoji u kolekciji");
        }

        Kolekcija<T1, T2> newKolekcija{ *this };

        newKolekcija.AddElement(element1, element2);

        std::copy_backward(
            newKolekcija._elementi1 + index,
            newKolekcija._elementi1 + newKolekcija.getTrenutno() - 1,
            newKolekcija._elementi1 + newKolekcija.getTrenutno()
        );
        std::copy_backward(
            newKolekcija._elementi2 + index,
            newKolekcija._elementi2 + newKolekcija.getTrenutno() - 1,
            newKolekcija._elementi2 + newKolekcija.getTrenutno()
        );

        newKolekcija._elementi1[index] = element1;
        newKolekcija._elementi2[index] = element2;

        return newKolekcija;
    }

    Kolekcija<T1, T2>& operator=(const Kolekcija<T1, T2>& rhs) {
        // Self assignment here is safe due to the order of allocation and deallocation
        T1* const temp1{ new T1[rhs.getTrenutno()] };
        T2* const temp2{ new T2[rhs.getTrenutno()] };
        int* tempSize{ new int{ rhs.getTrenutno() } };

        std::copy(rhs._elementi1, rhs._elementi1 + rhs.getTrenutno(), temp1);
        std::copy(rhs._elementi2, rhs._elementi2 + rhs.getTrenutno(), temp2);

        delete[] _elementi1;
        delete[] _elementi2;
        delete _trenutno;

        _elementi1 = temp1;
        _elementi2 = temp2;
        _trenutno = tempSize;

        _omoguciDupliranje = rhs._omoguciDupliranje;

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
    Datum(const Datum& datum)
        : _dan { new int{ *datum._dan } }
        , _mjesec{ new int{ *datum._mjesec } }
        , _godina{ new int{ *datum._godina } }
    {}
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    Datum& operator=(const Datum& rhs) {
        // Self assignment here is safe due to it just being values assigned to each other
        *_dan = *rhs._dan;
        *_mjesec = *rhs._mjesec;
        *_godina = *rhs._godina;

        return *this;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        // Added * operator to obj._dan, obj._mjesec and obj._godina, it previously wasn't there
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
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
        _ocjeneKriterija = new Kolekcija<Kriteriji, int>;
    }
    Komentar(const Komentar& komentar)
        : _sadrzajKomentara { GetNizKaraktera(komentar._sadrzajKomentara) }
        , _ocjeneKriterija{ new Kolekcija<Kriteriji, int>(komentar._ocjeneKriterija) }
    {}
    ~Komentar() {
        delete[] _sadrzajKomentara; _sadrzajKomentara = nullptr;
        delete _ocjeneKriterija; _ocjeneKriterija = nullptr;
    }
    char* GetSadrzajKomentara() { return _sadrzajKomentara; }
    Kolekcija<Kriteriji, int>* GetOcjeneKriterija() { return _ocjeneKriterija; }

    friend std::ostream& operator<<(std::ostream& os, const Komentar& komentar) {
        os << komentar._sadrzajKomentara << '\n';

        for (int i = 0; i < komentar._ocjeneKriterija->getTrenutno(); ++i) {
            std::cout << '\t';

            switch (komentar._ocjeneKriterija->getElement1(i)) {
            case Kriteriji::CISTOCA:
                std::cout << "CISTOCA(";
                break;
            case Kriteriji::LOKACIJA:
                std::cout << "LOKACIJA(";
                break;
            case Kriteriji::UDOBNOST:
                std::cout << "UDOBNOST(";
                break;
            default:
                std::cout << "USLUGA(";
            }
            
            std::cout << komentar._ocjeneKriterija->getElement2(i) << ')';

            if (i + 1 != komentar._ocjeneKriterija->getTrenutno()) {
                std::cout << '\n';
            }
        }

        return os;
    }

    Komentar& operator=(const Komentar& rhs) {
        char* const tempSadrzajKomentara{ GetNizKaraktera(rhs._sadrzajKomentara) };

        delete[] _sadrzajKomentara;
        _sadrzajKomentara = tempSadrzajKomentara;

        *_ocjeneKriterija = *rhs._ocjeneKriterija;

        return *this;
    }

    void AddOcjenuKriterija(const Kriteriji kriteriji, const int ocjena) {
        if (ocjena < 1 || ocjena > 10) {
            throw std::exception("Ocjena mora biti u rasponu 1-10");
        }

        for (int i = 0; i < _ocjeneKriterija->getTrenutno(); ++i) {
            if (_ocjeneKriterija->getElement1(i) == kriteriji) {
                throw std::exception("Kriteriji je vec ocjenjen jednom");
            }
        }

        _ocjeneKriterija->AddElement(kriteriji, ocjena);
    }
};


class Gost {
    char* _imePrezime;
    string _emailAdresa;
    string _brojPasosa;
public:
    Gost(const char* imePrezime, string emailAdresa, string brojPasosa) {
        // There was a double ;; at the end of the statement below, removed it
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _brojPasosa = brojPasosa;
    }
    /*
        Copy ctor and copy assignment added due to Gost being used in a std::vector later on
        and the docs specify that T for std::vector must meet the requirements of CopyAssignable 
        and CopyConstructible.
        Source: https://en.cppreference.com/w/cpp/container/vector
    */
    Gost(const Gost& gost)
        : _imePrezime { GetNizKaraktera(gost._imePrezime) }
        , _emailAdresa { gost._emailAdresa }
        , _brojPasosa { gost._brojPasosa }
    {}

    Gost& operator=(const Gost& rhs) {
        char* const tempImePrezime{ GetNizKaraktera(rhs._imePrezime) };

        delete[] _imePrezime;

        _imePrezime = tempImePrezime;
        _emailAdresa = rhs._emailAdresa;
        _brojPasosa = rhs._brojPasosa;

        return *this;
    }
    /*
        Added dctor because _imePrezime will point to dynamic memory that needs to be freed
    */
    ~Gost() {
        delete[] _imePrezime;
    }
    /*
        Added const to methods below, this made it so other const methods could call it, if this is not allowed then my bad
        Just means wherever I have const& it has to be &
    */
    string GetEmail() const { return _emailAdresa; }
    string GetBrojPasosa() const { return _brojPasosa; }
    char* GetImePrezime() { return _imePrezime; }

    friend ostream& operator<< (ostream& COUT, const Gost& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojPasosa << endl;
        return COUT;
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
    friend ostream& operator<< (ostream& COUT, Rezervacija& obj) {
        COUT << crt << "Rezervacija " << obj._OD << " - " << obj._DO << " za goste: " << endl;
        for (size_t i = 0; i < obj._gosti.size(); i++)
            COUT << "\t" << i + 1 << "." << obj._gosti[i];
        cout << crt << "Komentar rezervacije: " << endl << obj._komentar << crt;
        return COUT;
    }

    bool AddGost(const Gost& gost) {
        auto DaLiJeGostValidan = [&](const Gost& gostIzNiza) {
            return  gostIzNiza.GetBrojPasosa() == gost.GetBrojPasosa() ||
                    gostIzNiza.GetEmail() == gost.GetEmail();
        };

        if (std::find_if(std::begin(_gosti), std::end(_gosti), DaLiJeGostValidan) != std::end(_gosti)) {
            return false;
        }

        _gosti.push_back(gost);

        return true;
    }

    void SetKomentar(const Komentar& komentar) {
        _komentar = komentar;
    }

    Rezervacija& operator=(const Rezervacija& rhs) {
        _OD = rhs._OD;
        _DO = rhs._DO;
        _gosti = rhs._gosti;
        _komentar = rhs._komentar;

        return *this;
    }
};


void main() {


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
    
    
    Gost denis("Denis Music", "denis@fit.ba", "BH235-532");
    Gost jasmin("Jasmin Azemovic", "jasmin@fit.ba", "B123321");
    Gost adel("Adel Handzic", "adel@edu.fit.ba", "B1252 521");
    Gost gostPasosNotValid("Ime Prezime", "korisnik@klix.ba", "H4521");
    
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
    
    cin.get();
    system("pause>0");
}