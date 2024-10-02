#include<iostream>
using namespace std;

// Headers I included below
#include<vector>
#include<regex>
#include<string>
#include<sstream>
#include<thread>
#include<iomanip>
// Headers I included above

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* crt = "\n-------------------------------------------\n";
const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;

// Functions I defined below

// Functions I defined above

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }
	~Kolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi1 = nullptr;
	}
	T1* getElementi1Pok() { return _elementi1; }
	T2* getElementi2Pok() { return _elementi2; }
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }

	friend ostream& operator<<(ostream& COUT, Kolekcija<T1, T2>& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno{ kolekcija.getTrenutno() }
		, _elementi1{ new T1[kolekcija.getTrenutno()] {} }
		, _elementi2{ new T2[kolekcija.getTrenutno()] {} }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = kolekcija.getElement1(i);
			_elementi2[i] = kolekcija.getElement2(i);
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		*_trenutno = rhs.getTrenutno();

		T1* const temp1{ new T1[getTrenutno()] {} };
		T2* const temp2{ new T2[getTrenutno()] {} };

		for (int i = 0; i < getTrenutno(); ++i) {
			temp1[i] = rhs.getElement1(i);
			temp2[i] = rhs.getElement2(i);
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		return *this;
	}

	Kolekcija& operator=(Kolekcija&& rhs) noexcept {
		const int tempTrenutno{ rhs.getTrenutno() };
		rhs._trenutno = 0;
		_trenutno = tempTrenutno;

		T1* const temp1{ std::exchange(rhs._elementi1, nullptr) };
		T2* const temp2{ std::exchange(rhs._elementi2, nullptr) };

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		return *this;
	}

	void AddElement(const T1& element1, const T2& element2) {
		T1* const temp1{ new T1[getTrenutno() + 1] {} };
		T2* const temp2{ new T2[getTrenutno() + 1] {} };

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

		++_trenutno;
	}
	
	[[nodiscard]] const T1& getElement1(const std::size_t index) const noexcept { 
		return _elementi1[index]; 
	}

	[[nodiscard]] const T2& getElement2(const std::size_t index) const noexcept {
		return _elementi2[index];
	}

	[[nodiscard]] int getTrenutno() const noexcept { 
		return _trenutno; 
	}
};
class Poglavlje {
	char* _naslov;
	char* _sadrzaj;
	bool _prihvaceno;
	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
public:
	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
		:_ocjena(0), _prihvaceno(false) {
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}
	~Poglavlje() {
		delete[] _naslov; _naslov = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Poglavlje& obj) {
		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
			return COUT;
		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
		if (obj._prihvaceno)
			COUT << "Ocjena: " << obj._ocjena << endl;;
		return COUT;
	}
	char* GetNaslov() { return _naslov; }
	char* GetSadrzaj() { return _sadrzaj; }
	bool GetPrihvaceno() { return _prihvaceno; }
	int GetOcjena() { return _ocjena; }

	// Methods I added below
	Poglavlje(const Poglavlje& poglavlje)
		: _naslov { AlocirajNizKaraktera(poglavlje.getNaslov()) }
		, _sadrzaj { AlocirajNizKaraktera(poglavlje.getSadrzaj()) }
		, _ocjena { poglavlje.getOcjena() }
		, _prihvaceno { poglavlje.getPrihvaceno() }
	{}

	Poglavlje& operator=(const Poglavlje& rhs) {
		_ocjena = rhs.getOcjena();
		_prihvaceno = rhs.getPrihvaceno();

		char* const tempNaslov{ AlocirajNizKaraktera(rhs.getNaslov()) };
		char* const tempSadrzaj{ AlocirajNizKaraktera(rhs.getSadrzaj()) };

		delete[] _naslov;
		delete[] _sadrzaj;

		_naslov = tempNaslov;
		_sadrzaj = tempSadrzaj;

		return *this;
	}

	[[nodiscard]] const char* getNaslov() const noexcept { 
		return _naslov; 
	}

	[[nodiscard]] const char* getSadrzaj() const noexcept { 
		return _sadrzaj; 
	}

	[[nodiscard]] bool getPrihvaceno() const noexcept { 
		return _prihvaceno; 
	}

	[[nodiscard]] int getOcjena() const noexcept { 
		return _ocjena; 
	}

	[[nodiscard]] bool operator==(const Poglavlje& rhs) const noexcept {
		return !std::strcmp(getNaslov(), rhs.getNaslov())
			&& !std::strcmp(getSadrzaj(), rhs.getSadrzaj())
			&& getPrihvaceno() == rhs.getPrihvaceno()
			&& getOcjena() == rhs.getOcjena();
	}

	void setOcjena(const int ocjena) noexcept {
		if (!daLiJeOcjenaValidna(ocjena)) {
			return;
		}

		_ocjena = ocjena;
		_prihvaceno = true;
	}

	[[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
		return ocjena >= 6 && ocjena <= 10;
	}

	friend ostream& operator<<(ostream& os, const Poglavlje& poglavlje) {
		if (poglavlje.getNaslov() == nullptr || poglavlje.getSadrzaj() == nullptr)
			return os;
		os << '\n' << poglavlje.getNaslov() << '\n' << poglavlje.getSadrzaj() << '\n';
		if (poglavlje.getPrihvaceno())
			os << "Ocjena: " << poglavlje.getOcjena() << '\n';
		return os;
	}

	void dodajSadrzaj(const char* const sadrzajZaDodat, const char* const delimiter = " ") {
		const std::size_t newSize{
			std::strlen(getSadrzaj()) +
			std::strlen(delimiter) + 
			std::strlen(sadrzajZaDodat) +
			1
		};

		char* const noviSadrzaj{ new char[newSize] {} };
		
		strcat_s(noviSadrzaj, newSize, getSadrzaj());
		strcat_s(noviSadrzaj, newSize, delimiter);
		strcat_s(noviSadrzaj, newSize, sadrzajZaDodat);

		delete[] _sadrzaj;
		_sadrzaj = noviSadrzaj;
	}

	[[nodiscard]] std::size_t getDuzinaSadrzaja() const noexcept {
		return std::strlen(getSadrzaj());
	}
};

class ZavrsniRad {
	char* _tema;
	vector<Poglavlje> _poglavljaRada;
	string _datumOdbrane;
	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
public:
	ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
		_tema = AlocirajNizKaraktera(nazivTeme);
	}

	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
		_tema = AlocirajNizKaraktera(org._tema);
	}

	~ZavrsniRad() {
		delete[] _tema; _tema = nullptr;
	}
	char* GetNazivTeme()const { return _tema; }
	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
	string GetDatumOdbrane()const { return _datumOdbrane; }
	float GetOcjena() { return _konacnaOcjena; }
	void SetDatumOdbrane(string datumOdbrane) { _datumOdbrane = datumOdbrane; }

	friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj) {
		COUT << "Tema rada: " << obj._tema << endl;
		COUT << "Sadrzaj: " << endl;
		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
			COUT << obj._poglavljaRada[i] << endl;
		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
		return COUT;
	}

	// Methods I added below
	ZavrsniRad& operator=(const ZavrsniRad& zavrsniRad) {
		_konacnaOcjena = zavrsniRad.getOcjena();

		char* const tempTema{ AlocirajNizKaraktera(zavrsniRad.getNazivTeme()) };
		std::vector<Poglavlje> tempPoglavlja{ zavrsniRad.getPoglavlja() };
		std::string tempDatum{ zavrsniRad.getDatumOdbrane() };

		delete[] _tema;

		_tema = tempTema;
		_poglavljaRada = std::move(tempPoglavlja);
		_datumOdbrane = std::move(tempDatum);

		return *this;
	}

	[[nodiscard]] const char* getNazivTeme() const noexcept { 
		return _tema; 
	}

	[[nodiscard]] const std::vector<Poglavlje>& getPoglavlja() const noexcept { 
		return _poglavljaRada; 
	}

	[[nodiscard]] const std::string& getDatumOdbrane() const noexcept { 
		return _datumOdbrane; 
	}

	[[nodiscard]] float getOcjena() const noexcept { 
		return _konacnaOcjena; 
	}
	
	[[nodiscard]] bool operator==(const ZavrsniRad& rhs) const noexcept {
		return !std::strcmp(getNazivTeme(), rhs.getNazivTeme())
			&& getOcjena() == rhs.getOcjena()
			&& getDatumOdbrane() == rhs.getDatumOdbrane()
			&& getPoglavlja() == rhs.getPoglavlja();
	}
 
	[[nodiscard]] bool operator!=(const ZavrsniRad& rhs) const noexcept {
		return !(*this == rhs);
	}

	friend ostream& operator<<(ostream& os, const ZavrsniRad& zavrsniRad) {
		os << "Tema rada: " << zavrsniRad.getNazivTeme() << '\n';
		os << "Sadrzaj: " << '\n';
		const auto& poglavlja{ zavrsniRad.getPoglavlja() };
		for (const auto& poglavlje : poglavlja) {
			os << poglavlje << '\n';
		}
		os << "Datum odbrane rada: " << zavrsniRad.getDatumOdbrane() << '\n';
		os << " Ocjena: " << zavrsniRad.getOcjena() << '\n';
		return os;
	}

	[[nodiscard]] double getAverage() const noexcept {
		const auto& size{ _poglavljaRada.size() };

		if (!size) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (const auto& poglavlje : _poglavljaRada) {
			sum += poglavlje.getOcjena();
		}

		return sum / size;
	}

	[[nodiscard]] Poglavlje* getPoglavljeSaNazivom(const std::string& naziv) noexcept {
		auto poglavljeZaPronaci{
			std::find_if(
				std::begin(_poglavljaRada),
				std::end(_poglavljaRada),
				[&](const Poglavlje& poglavlje) {
					return naziv == poglavlje.getNaslov();
				}
			)
		};

		return (poglavljeZaPronaci == std::end(_poglavljaRada)) ? nullptr : &(*poglavljeZaPronaci);
	}

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja

	void DodajPoglavlje(const char* const nazivPoglavlja, const char* const sadrzajPoglavlja) {
		auto poglavlje{ getPoglavljeSaNazivom(nazivPoglavlja) };

		if (poglavlje) {
			poglavlje->dodajSadrzaj(sadrzajPoglavlja);
			return;
		}

		_poglavljaRada.push_back(Poglavlje{ nazivPoglavlja, sadrzajPoglavlja });
	}

	/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja, dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
//parametri:nazivPoglavlja, ocjena
	void OcijeniPoglavlje(const char* const nazivPoglavlja, const int ocjena) {
		if (!Poglavlje::daLiJeOcjenaValidna(ocjena)) {
			throw std::runtime_error("Ocjena nije validna");
		}

		auto poglavlje{ getPoglavljeSaNazivom(nazivPoglavlja) };

		if (!poglavlje) {
			throw std::runtime_error("Poglavlje sa tim nazivom ne postoji");
		}

		poglavlje->setOcjena(ocjena);
	}
	
	[[nodiscard]] bool daLiJeMinBrojPoglavljaIspunjen() const noexcept {
		return _poglavljaRada.size() >= min_polgavlja;
	}

	[[nodiscard]] bool daLiSvakoPoglavljeImaMinBrojKaraktera() const noexcept {
		auto poglavljeZaPronaci{
			std::find_if(
				std::cbegin(_poglavljaRada),
				std::cend(_poglavljaRada),
				[&](const Poglavlje& poglavlje) {
						return poglavlje.getDuzinaSadrzaja() < min_karaktera_po_poglavlju;
					}
			)
		};

		return poglavljeZaPronaci == std::end(_poglavljaRada);
	}

	//		1. zavrsni rad ima broj poglavlja veci od minimalnog
	//		2. svako poglavlje ima broj karaktera veci od minimalnog
	//		3. svako poglavlje je prihvaceno/odobreno
	[[nodiscard]] bool daLiJeIspunjenUslovZakazivanjaOdbrane() const noexcept {
		return daLiJeMinBrojPoglavljaIspunjen() && daLiSvakoPoglavljeImaMinBrojKaraktera();
	}

	void izracunajKonacnuOcjenu() noexcept {
		float sum{ 0.0 };

		for (const auto& poglavlje : _poglavljaRada) {
			sum += poglavlje.getOcjena();
		}

		const auto& size{ _poglavljaRada.size() };
		_konacnaOcjena = (size) ? sum / size : 0.0f;
	}

	void zakaziOdbranu(const std::string& datumOdbrane) noexcept {
		SetDatumOdbrane(datumOdbrane);
		izracunajKonacnuOcjenu();
	}
};

class Osoba {
protected:
	string _imePrezime;
public:
	Osoba(string imePrezime) : _imePrezime(imePrezime) {}
	string GetImePrezime() { return _imePrezime; }
	virtual void Info() = 0;

	// Methods I added below
	[[nodiscard]] const std::string& getImePrezime() const noexcept {
		return _imePrezime;
	}

	friend std::ostream& operator<<(std::ostream& os, const Osoba& osoba) {
		os << "Ime prezime: " << std::quoted(osoba.getImePrezime());

		return os;
	}
};

class Nastavnik : public Osoba {
	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
	Kolekcija<string, ZavrsniRad> _teme;
public:
	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };

	// Methods I added below
	Nastavnik(const std::string imePrezime)
		: Osoba(imePrezime)
	{}
	
	Nastavnik(const Nastavnik& nastavnik)
		: Osoba(nastavnik)
		, _teme { nastavnik.getTeme() }
	{}

	Nastavnik& operator=(const Nastavnik& rhs) {
		Osoba::operator=(rhs);

		Kolekcija<string, ZavrsniRad> tempTeme{ rhs.getTeme() };

		_teme = std::move(tempTeme);

		return *this;
	}

	[[nodiscard]] const Kolekcija<string, ZavrsniRad>& getTeme() const noexcept { 
		return _teme; 
	}

	void Info() override {
		std::cout << *this << '\n';
	}

	friend std::ostream& operator<<(std::ostream& os, const Nastavnik& nastavnik) {
		os << static_cast<const Osoba&>(nastavnik) << '\n';
		os << "Teme: \n";

		const auto& teme{ nastavnik.getTeme() };
		for (int i = 0; i < teme.getTrenutno(); ++i) {
			os << teme.getElement1(i) << " - " << teme.getElement2(i);

			if (i + 1 != teme.getTrenutno()) {
				os << '\n';
			}
		}

		return os;
	}

	[[nodiscard]] bool daLiJeZavrsniRadVecDodjeljenNekom(const ZavrsniRad& zavrsniRad) const noexcept {
		for (int i = 0; i < _teme.getTrenutno(); ++i) {
			if (_teme.getElement2(i) == zavrsniRad) {
				return true;
			}
		}

		return false;
	}

	[[nodiscard]] bool daLiStudentVecImaZavrsniRad(const std::string& brojIndeksa) const noexcept {
		for (int i = 0; i < _teme.getTrenutno(); ++i) {
			if (_teme.getElement1(i) == brojIndeksa) {
				return true;
			}
		}

		return false;
	}

	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu. zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
	sprijeciti dodavanje zavrsnih radova sa istom temom*/
	//parametri: brojIndeksa, zavrsniRad
	bool DodajZavrsniRad(const std::string& brojIndeksa, const ZavrsniRad& zavrsniRad) {
		if (daLiStudentVecImaZavrsniRad(brojIndeksa)) {
			return false;
		}
		else if (daLiJeZavrsniRadVecDodjeljenNekom(zavrsniRad)) {
			return false;
		}

		_teme.AddElement(brojIndeksa, zavrsniRad);
		return true;
	}

	[[nodiscard]] ZavrsniRad* getZavrsniRadZaStudenta(const std::string& brojIndeksa) noexcept {
		for (int i = 0; i < _teme.getTrenutno(); ++i) {
			if (_teme.getElement1(i) == brojIndeksa) {
				return &_teme.getElement2(i);
			}
		}

		return nullptr;
	}

	//	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
	//	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
	//		1. zavrsni rad ima broj poglavlja veci od minimalnog
	//		2. svako poglavlje ima broj karaktera veci od minimalnog
	//		3. svako poglavlje je prihvaceno/odobreno
	//	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
	//	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
	//*/

	ZavrsniRad* ZakaziOdbranuRada(const std::string& brojIndeksa, const std::string& datumOdbrane) {
		auto zavrsniRadStudenta{ getZavrsniRadZaStudenta(brojIndeksa) };

		if (!zavrsniRadStudenta) {
			return nullptr;
		}
		else if (!zavrsniRadStudenta->daLiJeIspunjenUslovZakazivanjaOdbrane()) {
			return nullptr;
		}

		zavrsniRadStudenta->zakaziOdbranu(datumOdbrane);
		return zavrsniRadStudenta;
	}

	std::string sendMailsToStudentWithAverageAbove(const double prosjek) const {
		std::string allEmailsContent{};

		for (int i = 0; i < _teme.getTrenutno(); ++i) {
			if (_teme.getElement2(i).getAverage() > prosjek) {
				allEmailsContent += sendEmail(
					_teme.getElement1(i), 
					_teme.getElement2(i)
				);
			}
		}

		return allEmailsContent;
	}

private:
	[[nodiscard]] std::string createEmail(const std::string& brojIndeksa, const ZavrsniRad& zavrsniRad) const {
		std::ostringstream emailBuffer{};

		emailBuffer << "Postovani " << brojIndeksa << ", uzimajuci u obzir cinjenicu da ste kod mentora ";
		emailBuffer << getImePrezime() << " uspjesno odbranili rad sa ocjenom " << zavrsniRad.getOcjena();
		emailBuffer << " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu";
		emailBuffer << " u na FIT - u 03.07.2019.godine.\n";

		return emailBuffer.str();
	}

	std::string sendEmail(const std::string& brojIndeksa, const ZavrsniRad& zavrsniRad) const {
		const std::string emailContent{ createEmail(brojIndeksa, zavrsniRad) };
		std::thread emailThread{
			[&]() {
				std::cout << emailContent;
			}
		};

		emailThread.join();
		return emailContent;
	}
};

//
//	/*Funkcija PosaljiPozivZaDodjeluNagrada ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod odredjenog nastavnika/mentora
//	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem:
//	"Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 03.07.2019. godine."	.
//	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
//	cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 9.5) << endl;

std::string PosaljiPozivZaDodjeluNagrada(const Nastavnik* const* const nastavnici, const int max, const double prosjek) {
	std::string allEmailsContent{};

	for (int i = 0; i < max; ++i) {
		allEmailsContent += nastavnici[i]->sendMailsToStudentWithAverageAbove(prosjek);
	}

	return (allEmailsContent == "")? not_set : allEmailsContent;
}

int main() {
	cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
	cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;

	const int max = 4;
	Nastavnik* nastavnici[max];

	nastavnici[0] = new Nastavnik("Denis Music");
	nastavnici[1] = new Nastavnik("Zanin Vejzovic");
	nastavnici[2] = new Nastavnik("Jasmin Azemovic");
	nastavnici[3] = new Nastavnik("Emina Junuz");
	//parametri: naziv zavrsnog rada
	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
	ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti bežičnih računarskih mreža");
	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih ključeva");

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja
	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");
	multimedijalni.DodajPoglavlje("Zakljucak", "U ovom radu su predstavljeni osnovni koncepti i prakticna primjena...");

	try {
		/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja, dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
		//parametri:nazivPoglavlja, ocjena

		multimedijalni.OcijeniPoglavlje("Uvod", 8);
		multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
		multimedijalni.OcijeniPoglavlje("Teorija multimedije", 9);
		multimedijalni.OcijeniPoglavlje("Zakljucak", 7);
		multimedijalni.OcijeniPoglavlje("Naziv poglavlja ne postoji", 8);
	}
	catch (exception& err) {
		cout << "Greska -> " << err.what() << endl;
	}

	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu. zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
	sprijeciti dodavanje zavrsnih radova sa istom temom*/
	//parametri: brojIndeksa, zavrsniRad
	if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
		cout << "Zavrsni rad nije dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
		cout << "Zavrsni rad nije dodat!" << endl;
	if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
		cout << "Zavrsni rad uspjesno dodat!" << endl;

//	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
//	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
//		1. zavrsni rad ima broj poglavlja veci od minimalnog
//		2. svako poglavlje ima broj karaktera veci od minimalnog
//		3. svako poglavlje je prihvaceno/odobreno
//	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
//	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
//*/

//parametri: brojIndeksa, datumOdbrane
	ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
	nastavnici[0]->Info();

	/*Funkcija PosaljiPozivZaDodjeluNagrada ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod odredjenog nastavnika/mentora
	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem:
	"Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 03.07.2019. godine."	.
	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
	cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 9.5) << endl;

	for (int i = 0; i < max; i++) {
		delete nastavnici[i];
		nastavnici[i] = nullptr;
	}
	system("pause>0");
	return 0;
}