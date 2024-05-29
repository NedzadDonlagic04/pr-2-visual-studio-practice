#include <iostream>
using namespace std;

// Headers I included below
#include<vector>
#include<thread>
#include<string>
#include<iomanip>
#include<fstream>
#include<numeric>
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
"6. METODE I KLASE KOJE NE IMPLEMENTIRATE NEMOJTE BRISATI (BEZ OBZIRA STO NEMAJU IMPLEMENTACIJU)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12. ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };

// Functions I defined below
std::ostream& operator<<(std::ostream& os, Karakteristike karakteristike) {
	switch (karakteristike) {
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
class Rjecnik {
	T1* _elementi1{ nullptr };
	T2* _elementi2{ nullptr };
	int _trenutno{ 0 };
	bool _omoguciDupliranje;
public:
	Rjecnik(bool omoguciDupliranje = true) {
		_omoguciDupliranje = omoguciDupliranje;

	}
	~Rjecnik() {
		clearResources();
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Rjecnik& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Rjecnik(const Rjecnik& rjecnik)
		: _trenutno { rjecnik.getTrenutno() }
		, _omoguciDupliranje { rjecnik.getOmoguciDupliranje()}
		, _elementi1{ new T1[rjecnik.getTrenutno()] {} }
		, _elementi2{ new T2[rjecnik.getTrenutno()] {} }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = rjecnik.getElement1(i);
			_elementi2[i] = rjecnik.getElement2(i);
		}
	}

	Rjecnik& operator=(const Rjecnik& rhs) {
		if (this == &rhs) {
			return *this;
		}

		_trenutno = rhs.getTrenutno();
		_omoguciDupliranje = rhs.getOmoguciDupliranje();

		clearResources();

		_elementi1 = new T1[getTrenutno()]{};
		_elementi2 = new T2[getTrenutno()]{};

		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = rhs.getElement1(i);
			_elementi2[i] = rhs.getElement2(i);
		}

		return *this;
	}

	[[nodiscard]] bool getOmoguciDupliranje() const noexcept {
		return _omoguciDupliranje;
	}

	[[nodiscard]] bool daLiElementPostoji(const T1& element1, const T2& element2) const noexcept {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (element1 == getElement1(i) || element2 == getElement2(i)) {
				return true;
			}
		}

		return false;
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (!getOmoguciDupliranje() && daLiElementPostoji(element1, element2)) {
			throw std::exception("Dupliranje elemenata nije dozvoljeno");
		}

		T1* const temp1{ new T1[getTrenutno() + 1] {} };
		T2* const temp2{ new T2[getTrenutno() + 1] {} };

		for (int i = 0; i < getTrenutno(); ++i) {
			temp1[i] = getElement1(i);
			temp2[i] = getElement2(i);
		}

		temp1[getTrenutno()] = element1;
		temp2[getTrenutno()] = element2;

		clearResources();

		_elementi1 = temp1;
		_elementi2 = temp2;

		++_trenutno;
	}

	Rjecnik operator()(const int start, const int end) {
		Rjecnik temp{};

		if (start < 0 || start >= getTrenutno()) {
			return temp;
		} else if (end < 0 || end >= getTrenutno()) {
			return temp;
		}

		for (int i = start; i <= end; ++i) {
			temp.AddElement(getElement1(i), getElement2(i));
		}
		
		return temp;
	}

private:
	void clearResources() {
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

	[[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
		return getDan() == rhs.getDan()
			&& getMjesec() == rhs.getMjesec()
			&& getGodina() == rhs.getGodina();
	}

	[[nodiscard]] bool operator!=(const Datum& rhs) const noexcept {
		return !(*this == rhs);
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
	int _ocjena; //za svaku kupovinu kupac moze ostaviti jednu ocjenu
	//uz ocjenu, kupci mogu komentarisati svaku od karakteristika proizvoda.
	//onemoguciti dupliranje karakteristika tj. svaka karakteristika se moze komentarisati samo jednom...u suprotnom baciti objekat tipa exception
	Rjecnik<Karakteristike, const char*> _komentariKarakteristika;
public:
	ZadovoljstvoKupca(int ocjena = 0) {
		_ocjena = ocjena;
	}
	int GetOcjena() { return _ocjena; }
	Rjecnik<Karakteristike, const char*>& GetKomentareKarakteristika() { return _komentariKarakteristika; }

	// Methods I added below
	ZadovoljstvoKupca(const ZadovoljstvoKupca& zadovoljstvoKupca)
		: _ocjena { zadovoljstvoKupca.getOcjena() }
		, _komentariKarakteristika { zadovoljstvoKupca.getKomentareKarakteristika() }
	{}

	ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& zadovoljstvoKupca) {
		_ocjena = zadovoljstvoKupca.getOcjena();
		_komentariKarakteristika = zadovoljstvoKupca.getKomentareKarakteristika();

		return *this;
	}

	[[nodiscard]] bool daLiSuJednakiKomentariKarakteristika(
		const Rjecnik<Karakteristike, const char*>& komentariKarakteristika
	) const noexcept {
		if (_komentariKarakteristika.getTrenutno() != komentariKarakteristika.getTrenutno()) {
			return false;
		}
		else if (_komentariKarakteristika.getOmoguciDupliranje() != komentariKarakteristika.getOmoguciDupliranje()) {
			return false;
		}

		for (int i = 0; i < komentariKarakteristika.getTrenutno(); ++i) {
			if (komentariKarakteristika.getElement1(i) != _komentariKarakteristika.getElement1(i)) {
				return false;
			}
			else if (std::strcmp(komentariKarakteristika.getElement2(i), _komentariKarakteristika.getElement2(i))) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]] bool operator==(const ZadovoljstvoKupca& rhs) const noexcept {
		return getOcjena() == rhs.getOcjena()
			&& daLiSuJednakiKomentariKarakteristika(rhs.getKomentareKarakteristika());
	}

	[[nodiscard]] bool operator!=(const ZadovoljstvoKupca& rhs) const noexcept {
		return !(*this == rhs);
	}

	void DodajKomentarKarakteristike(Karakteristike karakteristike, const char* const komentar) {
		if (daLiJeKarakteristikaVecOcjenjena(karakteristike)) {
			throw std::runtime_error("Karakteristika je vec komentarisana");
		}

		_komentariKarakteristika.AddElement(karakteristike, komentar);
	}

	[[nodiscard]] bool daLiJeKarakteristikaVecOcjenjena(Karakteristike karakteristike) const noexcept {
		for (int i = 0; i < _komentariKarakteristika.getTrenutno(); ++i) {
			if (karakteristike == _komentariKarakteristika.getElement1(i)) {
				return true;
			}
		}

		return false;
	}

	[[nodiscard]] int getOcjena() const noexcept { 
		return _ocjena; 
	}
	
	[[nodiscard]] const Rjecnik<Karakteristike, const char*>& getKomentareKarakteristika() const noexcept { 
		return _komentariKarakteristika; 
	}
	
	friend std::ostream& operator<<(std::ostream& os, const ZadovoljstvoKupca& zadovoljstvoKupca) {
		os << zadovoljstvoKupca.getOcjena() << '\n';
		
		const auto& komentariKarakterisika{ 
			zadovoljstvoKupca.getKomentareKarakteristika() 
		};

		for (int i = 0; i < komentariKarakterisika.getTrenutno(); ++i) {
			os << '\t' << komentariKarakterisika.getElement1(i) << " - ";
			os << komentariKarakterisika.getElement2(i);

			if (i + 1 != komentariKarakterisika.getTrenutno()) {
				os << '\n';
			}
		}

		return os;
	}
};

class Osoba {
protected:
	char* _imePrezime;
	Datum _datumRodjenja;
public:
	Osoba(const char* imePrezime = "", Datum datumRodjenja = Datum()) : _datumRodjenja(datumRodjenja) {
		_imePrezime = GetNizKaraktera(imePrezime);
	}
	virtual ~Osoba() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	char* GetImePrezime() { return _imePrezime; }
	Datum& GetDatumRodjenja() { return _datumRodjenja; }

	virtual void Info() = 0;
	friend ostream& operator<< (ostream& COUT, const Osoba& obj) {
		COUT << obj._imePrezime << " " << obj._datumRodjenja << endl;
		return COUT;
	}

	// Methods I added below
	Osoba(const Osoba& osoba)
		: _imePrezime { GetNizKaraktera(osoba.getImePrezime()) }
		, _datumRodjenja { osoba.getDatumRodjenja() }
	{}

	Osoba& operator=(const Osoba& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _imePrezime;
		
		_imePrezime = GetNizKaraktera(rhs.getImePrezime());
		_datumRodjenja = rhs.getDatumRodjenja();

		return *this;
	}

	[[nodiscard]] const char* getImePrezime() const noexcept { 
		return _imePrezime; 
	}

	[[nodiscard]] const Datum& getDatumRodjenja() const noexcept { 
		return _datumRodjenja; 
	}
};

class Kupac : public Osoba {
	char* _emailAdresa;
	//float se odnosi na iznos racuna za odredjenu kupovinu
	Rjecnik<float, ZadovoljstvoKupca>* _kupovine;
	vector<int> _bodovi; // bodovi sakupljeni tokom kupovine, svakih potrosenih 10KM donosi po 1 bod.
public:
	Kupac(const char* imePrezime = "", Datum datumRodjenja = Datum(), const char* emailAdresa = "") 
		: Osoba(imePrezime, datumRodjenja)
	{
		_emailAdresa = GetNizKaraktera(emailAdresa);
		_kupovine = new Rjecnik<float, ZadovoljstvoKupca>(false);
	}
	~Kupac() override {
		delete[] _emailAdresa; _emailAdresa = nullptr;
		delete _kupovine; _kupovine = nullptr;
	}
	char* GetEmail() { return _emailAdresa; }
	Rjecnik<float, ZadovoljstvoKupca>& GetKupovine() { return *_kupovine; }
	vector<int> GetBodovi() { return _bodovi; }
	int GetBodoviUkupno() {
		int ukupno = 0;
		for (size_t i = 0; i < _bodovi.size(); i++) ukupno += _bodovi[i];
		return ukupno;
	}

	friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
		COUT << crt << obj._imePrezime << " " << obj._datumRodjenja << " " << obj._emailAdresa << " " << endl;
		COUT << "KUPOVINE -> " << crt;
		for (size_t i = 0; i < obj._kupovine->getTrenutno(); i++)
			COUT << "Iznos racuna: " << obj._kupovine->getElement1(i) << "KM, zadovoljstvo kupca: " << obj._kupovine->getElement2(i) << crt;
		COUT << "BODOVI -> ";
		for (size_t i = 0; i < obj._bodovi.size(); i++)
			COUT << obj._bodovi[i] << ", ";
		COUT << crt;
		return COUT;
	}

	// Methods I added below
	Kupac(const Kupac& kupac) 
		: Osoba(kupac)
		, _emailAdresa { GetNizKaraktera(kupac.getEmail()) }
		, _bodovi { kupac.getBodovi() }
		, _kupovine{ new Rjecnik<float, ZadovoljstvoKupca>{ kupac.getKupovine() } }
	{}

	Kupac& operator=(const Kupac& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _emailAdresa;

		Osoba::operator=(rhs);
		_emailAdresa = GetNizKaraktera(rhs.getEmail());
		_bodovi = rhs.getBodovi();
		*_kupovine = rhs.getKupovine();

		return *this;
	}

	[[nodiscard]] const char* getEmail() const noexcept { 
		return _emailAdresa; 
	}

	[[nodiscard]] const Rjecnik<float, ZadovoljstvoKupca>& getKupovine() const noexcept { 
		return *_kupovine; 
	}

	[[nodiscard]] const std::vector<int>& getBodovi() const noexcept { 
		return _bodovi; 
	}

	[[nodiscard]] int getBodoviUkupno() const noexcept {
		return std::accumulate(std::begin(_bodovi), std::end(_bodovi), 0);
	}

	void DodajKupovinu(const float cijena, const ZadovoljstvoKupca& zadovoljstvoKupca) {
		if (cijena <= 0) {
			return;
		}

		_kupovine->AddElement(cijena, zadovoljstvoKupca);

		const int bodovi = cijena / 10;

		if (!bodovi) {
			return;
		}

		_bodovi.push_back(bodovi);

		if (bodovi < 5) {
			return;
		}

		sendMail();
	}

	void Info() {
		std::cout << *this;
	}

	void SacuvajBodove() {
		const std::string filePath{ std::string("./") + getEmail() + ".txt" };

		std::ofstream file{ filePath, std::ios::out | std::ios::app };

		for (const auto& bod : _bodovi) {
			file << bod << '\n';
		}
	}

	void UcitajBodove() {
		const std::string filePath{ std::string("./") + getEmail() + ".txt" };

		std::ifstream file{ filePath };

		if (!file.is_open()) {
			return;
		}

		std::string line{};

		while (std::getline(file, line)) {
			try {
				_bodovi.push_back(std::stoi(line));
			}
			catch (const std::exception& err) {
				// std::cout << "Error -> " << err.what() << '\n';
			}
		}
	}

	Rjecnik<Karakteristike, const char*> GetKupovineByKomentar(const std::string& komentar) {
		Rjecnik<Karakteristike, const char*> temp{};
		
		for (int i = 0; i < _kupovine->getTrenutno(); ++i) {
			const auto& zadovoljstvoKupca{ _kupovine->getElement2(i) };
			const auto& komentariKarakteristike{ zadovoljstvoKupca.getKomentareKarakteristika() };

			for (int i = 0; i < komentariKarakteristike.getTrenutno(); ++i) {
				if (std::string(komentariKarakteristike.getElement2(i)).find(komentar) != std::string::npos) {
					temp.AddElement(
						komentariKarakteristike.getElement1(i), 
						komentariKarakteristike.getElement2(i)
					);
				}
			}
		}

		return temp;
	}

private:
	void sendMail() const {
		std::thread emailThread{
			[&]() {
				std::cout << "\nTo: " << getEmail() << '\n';
				std::cout << "Subject: Osvareni bodovi\n\n";
				std::cout << "Postovani\n\n";
				std::cout << "Prilikom posljednje kupovine ste ostvarili " << getBodovi().back() << " bodova, tako";
				std::cout << " da trenutno vas ukupan broj bodova iznosi " << getBodoviUkupno() << ".\n";
				std::cout << "Zahvaljujemo vam na kupovini.\nPuno pozdrava\n";
			}
		};

		emailThread.join();
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Nabrojite i ukratko pojasnite osnovne razlike izmedju list i vector klase?\n";
	return "Odgovor -> Vektor cuva niz, sto znaci da su elementi jedni za drugim u memoriji, list-a cuva pokazivac "
		"na sljedeci element, sto znaci da elementi nisu jedni za drugim u memoriji, zbog cega list nema operator[]"
		" dok vektor ima. Vektor moze imati potencijalno memorije alocirane unapred da ne mora vise puta alocirati "
		"i dealocirati memoriju kod manjih dodavanja. Zbog ovoga takoder iteratori dobiveni od list-e vazi sve dok se "
		"ne dealocira, dok od vektora ne vaze jer je moguce da nakon prosirenja taj iterator pokazuje na dealocirani "
		"blok memorije. Pristup individualnom elementu list-e je skupo dok kod vektora nije zbog prijasnje navedenog "
		"nacina na koji se njihovi clanovi cuvaju. U list-e je jeftinije dodavati element nego u vektor.";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite opcije vezane za preslikavanje (vrijednosti, referenci, dostupnost) parametara prilikom koristenja lambda funkcija?\n";
	return "Odgovor -> Preslikavanje parametara po vrijednosti [=] znaci da sve varijable koje spominjemo u tijelu lambde ce biti kopirane "
		" po vrijednosti, modificiranje njih nece dovesti do promjene orginala. Preslikavanje parametara po referenci [&] znaci da sve "
		" varijable koje spominjemo u tijelu lambde ce biti kopirane po referenci, modificiranje njih ce dovesti do promjene orginala. "
		" Preslikavanje parametara po dostupnosti znaci da mozemo u [] izlistati koje varijable zelimo prenjeti u lambdu i kako, npr."
		" [&var1, var2] ovdje je var1 po referenci preslikano, dok je var2 po vrijednosti.";
	// Nisam siguran sta je dostupnost jer prevod na nas jezik inace goes smoothly, pa sam predpostavio da je to kada se uradi nesto na fazon
	// [&variable, variable2]
}

void main() {

	cout << PORUKA;
	cin.get();

	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();

	const int rjecnikTestSize = 9;
	Rjecnik<int, int> rjecnik1(false);
	for (int i = 0; i < rjecnikTestSize - 1; i++)
		rjecnik1.AddElement(i, i);//dodaje vrijednosti u rjecnik

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 ili T2), metoda AddElement treba baciti objekat tipa exception
		rjecnik1.AddElement(3, 3);
	}
	catch (exception& err) {
		cout << err.what() << crt;
	}
	rjecnik1.AddElement(9, 9);

	cout << rjecnik1 << crt;

	/*
	* metoda prihvata indekse lokacije, te vraća elemente koji se u rjecniku nalaze na proslijedjenim lokacijama (ukljucujuci i te lokacije)
	*/
	Rjecnik<int, int> rjecnik2 = rjecnik1(2, 5);
	/*clanovi objekta rjecnik2 bi trebali biti:
	2 2
	3 3
	4 4
	5 5
	*/
	cout << rjecnik2 << crt;


	const int maxKupaca = 3;
	Osoba* kupci[maxKupaca];
	kupci[0] = new Kupac("Denis Music", Datum(12, 1, 1980), "denis@fit.ba");
	kupci[1] = new Kupac("Jasmin Azemovic", Datum(12, 2, 1980), "jasmin@fit.ba");
	kupci[2] = new Kupac("Adel Handzic", Datum(12, 3, 1980), "adel@edu.fit.ba");

	ZadovoljstvoKupca zadovoljstvoKupca(7);
	zadovoljstvoKupca.DodajKomentarKarakteristike(NARUDZBA, "Nismo mogli odabrati sve potrebne opcije");
	zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");

	try {
		//karakteristika kvalitet je vec komentarisana
		zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");
	}
	catch (exception& err) {
		cout << err.what() << crt;
	}

	zadovoljstvoKupca.DodajKomentarKarakteristike(PAKOVANJE, "Pakovanje je bio osteceno");
	zadovoljstvoKupca.DodajKomentarKarakteristike(ISPORUKA, "Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana");


	Kupac* denis = dynamic_cast<Kupac*>(kupci[0]);
	/*za svakih 10KM kupcu se dodaje 1 bod, pa ce tako kupovina od 128KM kupcu donijeti 12 bodova*/
	denis->DodajKupovinu(128, zadovoljstvoKupca);
	cout << "Ukupno bodova -> " << denis->GetBodoviUkupno();//12 bodova


	ZadovoljstvoKupca zadovoljstvoKupca2(4);
	zadovoljstvoKupca2.DodajKomentarKarakteristike(KVALITET, "Jako lose, proizvod ostecen");
	denis->DodajKupovinu(81, zadovoljstvoKupca2);

	cout << "Ukupno bodova -> " << denis->GetBodoviUkupno();//20 bodova

	/*prilikom svake kupovine, ukoliko je kupac ostvario vise od 5 bodova, potrebno je, u zasebnom thread-u (nakon 3 sekunde), poslati email sa sljedecim sadrzajem:

	  To: denis@fit.ba;
	  Subject: Osvareni bodovi

	  Postovani,

	  Prilikom posljednje kupovine ste ostvarili 8 bodova, tako da trenutno vas ukupan broj bodova iznosi 20.

	  Zahvaljujemo vam na kupovini.
	  Puno pozdrava
  */


  //ispisuje sve podatke o kupcu i njegovim kupovinama.
	denis->Info();
	/* Primjer ispisa:
		-------------------------------------------
		Denis Music 12.1.1980 denis@fit.ba
		KUPOVINE ->
		-------------------------------------------
		Iznos racuna: 128KM, zadovoljstvo kupca: 7
				NARUDZBA - Nismo mogli odabrati sve potrebne opcije
				KVALITET - Kvalitet je ocekivan
				PAKOVANJE - Pakovanje je bio osteceno
				ISPORUKA - Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana
		-------------------------------------------
		Iznos racuna: 81KM, zadovoljstvo kupca: 4
				KVALITET - Jako lose, proizvod ostecen
		-------------------------------------------
		BODOVI -> 12, 8,
		-------------------------------------------
   */
   /*metoda SacuvajBodove treba sve clanove vector-a _bodovi upisati u fajl(ignorisuci ranije dodate/postojece vrijednosti u fajlu) pod nazivom emailKorisnika.txt npr. denis@fit.ba.txt.
   na osnovu trenutnog stanja objekta, sadrzaj fajla denis@fit.ba.txt bi trebao biti sljedeci:
   12
   8

   nakon spasavanja u fajl, sadrzaj vector-a ostaje nepromijenjen.
   */
	denis->SacuvajBodove();
	//metoda UcitajBodove ucitava sadrzaj fajla pod nazivom emailKorisnika.txt i njegove vrijednosti pohranjuje/dodaje u vector _bodovi (zadrzavajuci postojece bodove).  
	denis->UcitajBodove();
	//metoda GetKupovineByKomentar treba da pronadje i vrati sve karakteristike proizvoda i komentare kupaca koji sadrze vrijednost proslijedjenog parametra
	Rjecnik<Karakteristike, const char*> osteceniProizvodi = denis->GetKupovineByKomentar("ostecen");
	cout << crt << "Rezultat pretrage -> " << crt << osteceniProizvodi << crt;

	/*Ocekivani ispis:
		-------------------------------------------
		Rezultat pretrage ->
		-------------------------------------------
		PAKOVANJE Pakovanje je bio osteceno
		KVALITET Jako lose, proizvod ostecen
		-------------------------------------------
	*/

	for (size_t i = 0; i < maxKupaca; i++)
		delete kupci[i], kupci[i] = nullptr;

	cin.get();
	system("pause>0");
}