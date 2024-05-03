#include<iostream>
using namespace std;

// Headers I included below
#include<numeric>
#include<regex>
#include<thread>

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
const int brojTehnika = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

// Functions I made below

[[nodiscard]] const char* getPojasAsText(const Pojas& pojas) noexcept {
	switch (pojas) {
	case Pojas::BIJELI:
		return "BIJELI";
	case Pojas::ZUTI:
		return "ZUTI";
	case Pojas::NARANDZASTI:
		return "NARANDZASTI";
	case Pojas::ZELENI:
		return "ZELENI";
	case Pojas::PLAVI:
		return "PLAVI";
	case Pojas::SMEDJI:
		return "SMEDJI";
	case Pojas::CRNI:
		return "CRNI";
	default:
		return "Pojas ne postoji";
	}
}

std::ostream& operator<<(std::ostream& os, const Pojas& pojas) {
	os << getPojasAsText(pojas);

	return os;
}

/*
	za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
	-   najmanje 7 znakova
	-   velika i mala slova
	-   najmanje jedan broj
	-   najmanje jedan specijalni znak
*/
[[nodiscard]] bool ValidirajLozinku(const std::string& password) noexcept {
	if (password.size() < 7) {
		return false;
	}

	std::regex uppercaseCheck{ "[A-Z]+" };
	std::regex lowercaseCheck{ "[a-z]+" };
	std::regex atLeast1NumCheck{ "[0-9]+" };
	std::regex specialCharacterCheck{ "\\W" };

	return std::regex_search(password, uppercaseCheck)
		&& std::regex_search(password, lowercaseCheck)
		&& std::regex_search(password, atLeast1NumCheck)
		&& std::regex_search(password, specialCharacterCheck);
}

// Functions I made above

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}

template<class T1, class T2, int max = 10>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int* _trenutno;
public:
	Kolekcija() { _trenutno = new int(0); }
	~Kolekcija() {

		for (size_t i = 0; i < *_trenutno; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
		delete _trenutno; _trenutno = nullptr;
	}

	T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
	int getTrenutno() { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Below methods I made

	[[nodiscard]] int getTrenutno() const noexcept { 
		return *_trenutno; 
	}

	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno{ new int { kolekcija.getTrenutno() } }
	{
		for (int i = 0; i < *_trenutno; ++i) {
			_elementi1[i] = new T1{ kolekcija.getElement1(i) };
			_elementi2[i] = new T2{ kolekcija.getElement2(i) };
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		if (this == &rhs) {
			return *this;
		}

		for (int i = 0; i < getTrenutno(); ++i) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}

		delete _trenutno;
		_trenutno = new int{ rhs.getTrenutno() };

		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ rhs.getElement1(i) };
			_elementi2[i] = new T2{ rhs.getElement2(i) };
		}

		return *this;
	}

	void AddElement(const T1 & element1, const T2 & element2) {
		if (getTrenutno() == max) {
			throw std::runtime_error("Maximalni broj elemenata dostignut");
		}

		_elementi1[getTrenutno()] = new T1{ element1 };
		_elementi2[getTrenutno()] = new T2{ element2 };

		++(*_trenutno);
	}

	void AddElement(const T1& element1, const T2& element2, const int index) {
		if (getTrenutno() == max) {
			throw std::runtime_error("Maximalni broj elemenata dostignut");
		}
		else if (index < 0 || index >= getTrenutno()) {
			// An exception could be thrown here
			// Because text didn't say I should I will not
			return;
		}

		for (int i = getTrenutno(); i > index; --i) {
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}

		_elementi1[index] = new T1{ element1 };
		_elementi2[index] = new T2{ element2 };

		++(*_trenutno);
	}

	void RemoveAt(const int index) noexcept {
		// An exception could be thrown here
		// Because text didn't say I should I will not
		if (index < 0 || index >= getTrenutno()) {
			return;
		}

		delete _elementi1[index];
		delete _elementi2[index];

		for (int i = index; i < getTrenutno() - 1; ++i) {
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}

		_elementi1[getTrenutno() - 1] = nullptr;
		_elementi2[getTrenutno() - 1] = nullptr;

		--(*_trenutno);
	}

	T2& operator[](const T1& element1) {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (element1 == getElement1(i)) {
				return getElement2(i);
			}
		}
		// An exception could be thrown here
		// Because text didn't say I should I will not
	}
};
class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int{ dan };
		_mjesec = new int{ mjesec };
		_godina = new int{ godina };
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
		: _dan { new int { datum.getDan() } }
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

	[[nodiscard]] int64_t getDatumAsInt() const noexcept {
		int godine{ getGodina() };
		const int mjeseci{ getMjesec() };

		int64_t total{ getDan() + 365LL * godine };

		if (mjeseci <= 2) {
			--godine;
		}

		total += (godine / 4LL + godine / 400LL - godine / 100LL);

		total += [&]() {
			constexpr int monthsOfTheYear[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			return std::accumulate(monthsOfTheYear, monthsOfTheYear + mjeseci - 1, 0);
		}();

		return total;
	}

	[[nodiscard]] int64_t operator-(const Datum& rhs) const noexcept {
		return getDatumAsInt() - rhs.getDatumAsInt();
	}

	[[nodiscard]] bool operator==(const Datum& rhs) const noexcept {
		return getDan() == rhs.getDan()
			&& getMjesec() == rhs.getMjesec()
			&& getGodina() == rhs.getGodina();
	}

	[[nodiscard]] bool operator!=(const Datum& rhs) const noexcept {
		return !(*this == rhs);
	}
};

class Tehnika {
	char* _naziv;
	//int se odnosi na ocjenu u opsegu od 1 – 5, a Datum na datum kada je ocijenjena odredjena tehnika 
	Kolekcija<int, Datum*, brojTehnika>* _ocjene;
public:
	Tehnika(const char* naziv) {
		_naziv = GetNizKaraktera(naziv);
		// Changed line below from nullptr to what it is
		_ocjene = new Kolekcija<int, Datum*, brojTehnika>;
	}
	~Tehnika() {
		delete[] _naziv; _naziv = nullptr;

		// Added for loop below
		for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
			delete _ocjene->getElement2(i);
		}

		delete _ocjene; _ocjene = nullptr;
	}
	char* GetNaziv() { return _naziv; }
	Kolekcija<int, Datum*, brojTehnika>& GetOcjene() { return *_ocjene; }

	// Methods I defined below
	[[nodiscard]] const char* getNaziv() const noexcept { 
		return _naziv; 
	}

	[[nodiscard]] const Kolekcija<int, Datum*, brojTehnika>& getOcjene() const noexcept { 
		return *_ocjene; 
	}

	Tehnika(const Tehnika& tehnika)
		: _naziv { GetNizKaraktera(tehnika.getNaziv()) }
		, _ocjene { new Kolekcija<int, Datum*, brojTehnika> {}}
	{
		const auto& ocjene{ tehnika.getOcjene() };
		for (int i = 0; i < ocjene.getTrenutno(); ++i) {
			_ocjene->AddElement(
				ocjene.getElement1(i),
				new Datum(*ocjene.getElement2(i))
			);
		}
	}

	Tehnika& operator=(const Tehnika& rhs) {
		char* const tempNaziv{ GetNizKaraktera(rhs.getNaziv()) };
		auto const tempOcjene{ new Kolekcija<int, Datum*, brojTehnika> {} };

		const auto& ocjene{ rhs.getOcjene() };
		for (int i = 0; i < ocjene.getTrenutno(); ++i) {
			tempOcjene->AddElement(
				ocjene.getElement1(i),
				new Datum(*ocjene.getElement2(i))
			);
		}

		delete[] _naziv;
		// Added for loop below
		for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
			delete _ocjene->getElement2(i);
		}
		delete _ocjene;

		_naziv = tempNaziv;
		_ocjene = tempOcjene;

		return *this;
	}

	/*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise navrata.
		-   razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
		-   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
	*/
	bool AddOcjena(const int ocjena, const Datum& datumPolaganja) noexcept {
		const int zadnjiIndex{ _ocjene->getTrenutno() - 1 };

		if (zadnjiIndex < 0) {
			_ocjene->AddElement(ocjena, new Datum(datumPolaganja));
			return true;
		}

		const auto& zadnjiDatum{ *_ocjene->getElement2(zadnjiIndex) };
		const auto brojDanaIzmeduDatuma{ datumPolaganja - zadnjiDatum };

		if (brojDanaIzmeduDatuma < 3) {
			return false;
		}

		_ocjene->AddElement(ocjena, new Datum(datumPolaganja));
		return true;
	}

	/* ispisuje: naziv tehnike, ocjene (zajedno sa datumom) i prosjecnu ocjenu za tu tehniku
   ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0*/
	friend std::ostream& operator<<(std::ostream& os, const Tehnika& tehnika) {
		os << tehnika.getNaziv() << ":\n";
		
		const auto& ocjeneIDatum{ tehnika.getOcjene() };

		for (int i = 0; i < ocjeneIDatum.getTrenutno(); ++i) {
			os << '\t' << ocjeneIDatum.getElement1(i) << " - ";
			os << *ocjeneIDatum.getElement2(i) << '\n';
		}

		return os;
	}

	[[nodiscard]] bool DaLiSuJednakeOcjeneIDatum(const Kolekcija<int, Datum*, brojTehnika>& ocjene) const noexcept {
		if (ocjene.getTrenutno() != _ocjene->getTrenutno()) {
			return false;
		}

		for (int i = 0; i < ocjene.getTrenutno(); ++i) {
			if (ocjene.getElement1(i) != _ocjene->getElement1(i)) {
				return false;
			} else if (*ocjene.getElement2(i) != *_ocjene->getElement2(i)) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]] bool operator==(const Tehnika& rhs) const noexcept {
		return !std::strcmp(getNaziv(), rhs.getNaziv())
			&& DaLiSuJednakeOcjeneIDatum(rhs.getOcjene());
	}

	[[nodiscard]] double getAverageGrade() const noexcept {
		const int size{ _ocjene->getTrenutno() };

		if (!size) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (int i = 0; i < size; ++i) {
			sum += _ocjene->getElement1(i);
		}

		return sum / size;
	}
};

class Polaganje {
	Pojas _pojas;
	vector<Tehnika*> _polozeneTehnike;
public:
	Polaganje(Pojas pojas = BIJELI) {
		_pojas = pojas;
	}
	~Polaganje() {
		for (size_t i = 0; i < _polozeneTehnike.size(); i++) {
			delete _polozeneTehnike[i];
			_polozeneTehnike[i] = nullptr;
		}
	}
	vector<Tehnika*>& GetTehnike() { return _polozeneTehnike; }
	Pojas GetPojas() { return _pojas; }
	friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
		COUT << obj._pojas << endl;
		for (size_t i = 0; i < obj._polozeneTehnike.size(); i++)
			COUT << *obj._polozeneTehnike[i];
		return COUT;
	}

	// Methods I defined below
	[[nodiscard]] const std::vector<Tehnika*>& getTehnike() const noexcept { 
		return _polozeneTehnike; 
	}

	[[nodiscard]] Pojas getPojas() const noexcept { 
		return _pojas; 
	}

	Polaganje(const Pojas& pojas, const Tehnika& tehnika) 
		: _pojas { pojas }
	{
		_polozeneTehnike.push_back(new Tehnika{ tehnika });
	}

	Polaganje(const Polaganje& polaganje) 
		: _pojas{ polaganje.getPojas() }
	{
		for (const auto& tehnika : polaganje.getTehnike()) {
			_polozeneTehnike.push_back(new Tehnika{ *tehnika });
		}
	}

	Polaganje& operator=(const Polaganje& rhs) {
		_pojas = rhs.getPojas();

		std::vector<Tehnika*> tempPolozeneTehnike{};

		for (const auto& tehnika : rhs.getTehnike()) {
			tempPolozeneTehnike.push_back(new Tehnika{ *tehnika });
		}

		for (const auto& tehnika : _polozeneTehnike) {
			delete tehnika;
		}
		_polozeneTehnike.clear();

		_polozeneTehnike = std::move(tempPolozeneTehnike);

		return *this;
	}

	void addTehnika(const Tehnika& tehnika) {
		_polozeneTehnike.push_back(new Tehnika{ tehnika });
	}

	[[nodiscard]] bool daLiJeProsjekSvakeTehnikeIznad(const double average) const noexcept {
		if (average < 0.0) {
			return true;
		}

		for (const auto& polozenaTehnika : _polozeneTehnike) {
			if (polozenaTehnika->getAverageGrade() <= average) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]] double getAverage() const noexcept {
		return std::accumulate(
			std::begin(_polozeneTehnike),
			std::end(_polozeneTehnike),
			0.0,
			[](const double sum, const Tehnika* const tehnika) {
				return sum + tehnika->getAverageGrade();
			}
		);
	}
};

class Korisnik {
	char* _imePrezime;
	string _emailAdresa;
	string _lozinka;
public:
	Korisnik(const char* imePrezime, string emailAdresa, string lozinka)
	{
		_imePrezime = GetNizKaraktera(imePrezime);
		_emailAdresa = emailAdresa;
		_lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
	}
	virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
	string GetEmail() { return _emailAdresa; }
	string GetLozinka() { return _lozinka; }
	char* GetImePrezime() { return _imePrezime; }

	// Methods I defined below
	[[nodiscard]] const std::string& getEmail() const noexcept { 
		return _emailAdresa; 
	}

	[[nodiscard]] const std::string& getLozinka() const noexcept { 
		return _lozinka; 
	}

	[[nodiscard]] const char* getImePrezime() const noexcept { 
		return _imePrezime; 
	}

	Korisnik(const Korisnik& korisnik)
		: _imePrezime { GetNizKaraktera(korisnik.getImePrezime()) }
		, _emailAdresa { korisnik.getEmail() }
		, _lozinka { korisnik.getLozinka() }
	{}

	Korisnik& operator=(const Korisnik& rhs) {
		char* const tempImePrezime{ GetNizKaraktera(rhs.getImePrezime()) };
		std::string tempEmailAdresa{ rhs.getEmail() };
		std::string tempLozinka{ rhs.getLozinka() };

		delete[] _imePrezime;

		_imePrezime = tempImePrezime;
		_emailAdresa = std::move(tempEmailAdresa);
		_lozinka = std::move(tempLozinka);

		return *this;
	}
};

class KaratePolaznik : public Korisnik {
	vector<Polaganje> _polozeniPojasevi;
public:
	KaratePolaznik(const char* imePrezime, string emailAdresa, string lozinka)
		: Korisnik(imePrezime, emailAdresa, lozinka)
	{}
	~KaratePolaznik() override {
		cout << crt << "DESTRUKTOR -> KaratePolaznik" << crt;
	}
	friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
		COUT << obj.GetImePrezime() << " " << obj.GetEmail() << " " << obj.GetLozinka() << endl;
		for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
			COUT << obj._polozeniPojasevi[i];
		return COUT;
	}
	vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }

	// Methods I defined below
	[[nodiscard]] const vector<Polaganje>& getPolozeniPojasevi() const noexcept { 
		return _polozeniPojasevi; 
	}

	KaratePolaznik(const KaratePolaznik& karatePolaznik)
		: Korisnik(karatePolaznik)
		, _polozeniPojasevi{ karatePolaznik.getPolozeniPojasevi() }
	{}

	KaratePolaznik& operator=(const KaratePolaznik& rhs) {
		Korisnik::operator=(rhs);

		vector<Polaganje> tempPolozeniPojasevi{ rhs.getPolozeniPojasevi() };

		_polozeniPojasevi = std::move(tempPolozeniPojasevi);

		return *this;
	}

	bool AddTehniku(const Pojas& pojas, const Tehnika& tehnika) {
		if (!_polozeniPojasevi.size()) {
			DodajNoviPojasITehniku(pojas, tehnika);
			return true;
		}

		auto postojeciPojas{
			std::find_if(
				std::begin(_polozeniPojasevi),
				std::end(_polozeniPojasevi),
				[&](const Polaganje& polaganje) {
					return polaganje.getPojas() == pojas;
				}
			)
		};

		if (postojeciPojas != std::end(_polozeniPojasevi)) {
			const auto& postojeceTehnike{ postojeciPojas->getTehnike() };
			const auto identicnaTehnika{
					std::find_if(
					std::begin(postojeceTehnike),
					std::end(postojeceTehnike),
					[&](const Tehnika* const& currentTehnika) {
						return *currentTehnika == tehnika;
					}
				)
			};

			if (identicnaTehnika != std::end(postojeceTehnike)) {
				return false;
			}

			DodajTehnikuZaPostojeciPojas(*postojeciPojas, tehnika);
			return true;
		}
		else if (!DaLiJeIspunjenUslovZaDodavanjeNovogPojasa(pojas)) {
			return false;
		}

		DodajNoviPojasITehniku(pojas, tehnika);
		return true;
	}

	[[nodiscard]] bool DaLiJeIspunjenUslovZaDodavanjeNovogPojasa(const Pojas& pojas) const noexcept {
		if (!_polozeniPojasevi.size()) {
			return true;
		}

		const auto& zadnjiPojas{ _polozeniPojasevi.back() };
		
		return zadnjiPojas.getPojas() + 1 == pojas
			&& zadnjiPojas.getTehnike().size() >= 3
			&& zadnjiPojas.daLiJeProsjekSvakeTehnikeIznad(3.5);
	}

	[[nodiscard]] double getAverage() const noexcept {
		return std::accumulate(
			std::begin(_polozeniPojasevi),
			std::end(_polozeniPojasevi),
			0.0,
			[](const double sum, const Polaganje& polaganje) {
				return sum + polaganje.getAverage();
			}
		);
	}

private:
	void DodajNoviPojasITehniku(const Pojas& pojas, const Tehnika& tehnika) noexcept {
		_polozeniPojasevi.push_back(Polaganje{ pojas, tehnika });
		sendMail(_polozeniPojasevi.back(), tehnika.getNaziv());
	}

	void DodajTehnikuZaPostojeciPojas(Polaganje& polaganje, const Tehnika& tehnika) noexcept {
		polaganje.addTehnika(tehnika);
		sendMail(polaganje, tehnika.getNaziv());
	}

	/*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
		FROM:info@karate.ba
		TO: emailKorisnika
		Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
		na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
		Pozdrav.
		KARATE Team.
		slanje email poruka implemenitrati koristeci zasebne thread-ove.
	*/
	void sendMail(const Polaganje& polaganje, const char* const nazivTehnike) const noexcept {
		std::thread emailThread{
			[&]() {
				std::cout << "\nFROM:info@karate.ba\n";
				std::cout << "TO: " << getEmail() << '\n';
				std::cout << "Postovani " << getImePrezime() << ", evidentirana vam je tehnika " << nazivTehnike;
				std::cout << " za " << polaganje.getPojas() << " pojas. Dosadasnji uspjeh na pojasu ";
				std::cout << polaganje.getPojas() << " iznosi " << polaganje.getAverage() << ", a ukupni ";
				std::cout << "uspjeh (prosjek ocjena) na svim pojasevim iznosi " << getAverage() << ".\n";
				std::cout << "Pozdrav.\n";
				std::cout << "KARATE Team.\n\n";
			}
		};

		emailThread.join();
	}
};


const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite ulogu operatora reinterpret_cast.\n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Ukratko opisite znacaj i vrste pametnih pokazivaca.\n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
void main() {

	//cout << PORUKA;
	//cin.get();

	//cout << GetOdgovorNaPrvoPitanje() << endl;
	//cin.get();
	//cout << GetOdgovorNaDrugoPitanje() << endl;
	//cin.get();

	Datum   datum19062020(19, 6, 2020),
		datum20062020(20, 6, 2020),
		datum30062020(30, 6, 2020),
		datum05072020(5, 7, 2020);

	int kolekcijaTestSize = 10;

	Kolekcija<int, int> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);

	cout << kolekcija1 << endl;

	try {
		/*metoda AddElement baca izuzetak u slucaju da se pokusa
		dodati vise od maksimalnog broja elemenata*/
		kolekcija1.AddElement(11, 11);
	}
	catch (exception& err) {
		cout << crt << "Greska -> " << err.what() << crt;
	}
	cout << kolekcija1 << crt;


	kolekcija1.RemoveAt(2);
	/*uklanja par (T1 i T2) iz kolekcije koji se nalazi na lokaciji sa proslijedjenim indeksom.
	nakon uklanjanja vrijednosti onemoguciti pojavu praznog prostora unutar kolekcije tj.
	pomjeriti sve elemente koji se nalaze nakon proslijedjene lokacije za jedno mjesto unazad
	npr. ako unutar kolekcije postoje elementi
	0 0
	1 1
	2 2
	3 3
	nakon uklanjanja vrijednosti na lokaciji 1, sadrzaj kolekcije ce biti sljedeci
	0 0
	2 2
	3 3
	*/

	cout << kolekcija1 << crt;

	kolekcija1.AddElement(9, 9, 2);
	/*funkciji AddElement se, kao treci parametar, moze proslijediti i lokacija na koju se dodaju
	nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene za jedno mjesto unaprijed
	u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje elementi
	0 0
	1 1
	2 2
	3 3
	nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce biti sljedeci
	0 0
	9 9
	1 1
	2 2
	3 3
	*/

	cout << kolekcija1 << crt;

	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija1 << crt;

	//na osnovu vrijednosti T1 mijenja vrijednost T2. 
	kolekcija1[9] = 2;
	/* npr.ako unutar kolekcije postoje elementi:
	0 0
	9 9
	1 1
	2 2
	3 3
	nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
	0 0
	9 2
	1 1
	2 2
	3 3
	*/

	Tehnika choku_zuki("choku_zuki"),
		gyaku_zuki("gyaku_zuki"),
		kizami_zuki("kizami_zuki"),
		oi_zuki("oi_zuki");

	/*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise navrata.
		-   razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
		-   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
	*/
	if (choku_zuki.AddOcjena(1, datum19062020))
		cout << "Ocjena evidentirana!" << endl;
	if (!choku_zuki.AddOcjena(5, datum20062020))
		cout << "Ocjena NIJE evidentirana!" << endl;
	if (choku_zuki.AddOcjena(5, datum30062020))
		cout << "Ocjena evidentirana!" << endl;

	/* ispisuje: naziv tehnike, ocjene (zajedno sa datumom) i prosjecnu ocjenu za tu tehniku
	   ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0*/
	cout << choku_zuki << endl;

	if (ValidirajLozinku("john4Do*e"))
		cout << "OK" << crt;
	if (!ValidirajLozinku("john4Doe"))
		cout << "Specijalni znak?" << crt;
	if (!ValidirajLozinku("jo*4Da"))
		cout << "7 znakova?" << crt;
	if (!ValidirajLozinku("4jo-hnoe"))
		cout << "Veliko slovo?" << crt;
	if (ValidirajLozinku("@john2Doe"))
		cout << "OK" << crt;

	/*
	za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
	-   najmanje 7 znakova
	-   velika i mala slova
	-   najmanje jedan broj
	-   najmanje jedan specijalni znak
	za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
	validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
	postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
	*/

	Korisnik* jasmin = new KaratePolaznik("Jasmin Azemovic", "jasmin@karate.ba", "j@sm1N*");
	Korisnik* adel = new KaratePolaznik("Adel Handzic", "adel@edu.karate.ba", "4Ade1*H");
	Korisnik* emailNijeValidan = new KaratePolaznik("John Doe", "john.doe@google.com", "johndoe");

	/*
	sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju unutar istog objekta tipa Polaganje,
	tom prilikom onemoguciti:
	- dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
	- dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
	(onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3 tehnike za ZUTI pojas ili njihov prosjek nije veci od 3.5)
	funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/

	//doraditi klase da nacin da omoguce izvrsenje naredne linije koda
	KaratePolaznik* jasminPolaznik = dynamic_cast<KaratePolaznik*>(jasmin);

	if (jasminPolaznik != nullptr) {
		if (jasminPolaznik->AddTehniku(ZUTI, gyaku_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		//ne treba dodati kizami_zuki jer ne postoje evidentirane 3 tehnike za ZUTI pojas
		if (!jasminPolaznik->AddTehniku(NARANDZASTI, kizami_zuki))
			cout << "Tehnika NIJE uspjesno dodana!" << crt;
		if (jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		//ne treba dodati choku_zuki jer je vec dodana za zuti pojas
		if (!jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
			cout << "Tehnika NIJE uspjesno dodana!" << crt;

		//ispisuje sve dostupne podatke o karate polazniku
		cout << *jasminPolaznik << crt;
	}

	/*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
	FROM:info@karate.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
	na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
	Pozdrav.
	KARATE Team.
	slanje email poruka implemenitrati koristeci zasebne thread-ove.
	*/

	//osigurati da se u narednim linijama poziva i destruktor klase KaratePolaznik
	delete jasmin;
	delete adel;
	delete emailNijeValidan;

	cin.get();
	system("pause>0");
}