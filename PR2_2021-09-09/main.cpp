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

// Headers I included below
#include<iostream>
#include<thread>
#include<regex>
#include<string>
#include<vector>
#include<iomanip>
#include<array>
#include<numeric>
// Headers I included above
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
const int brojTehnika = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

// Functions I defined below
[[nodiscard]] bool ValidirajLozinku(const std::string& password) {
	if (password.size() < 7) {
		return false;
	}

	std::regex atLeast1UpperCaseCheck{ "[A-Z]" };
	std::regex atLeast1LowerCaseCheck{ "[a-z]" };
	std::regex atLeast1DigitCheck{ "\\d" };
	std::regex atLeast1SpecialCharCheck{ "\\W" };

	return std::regex_search(password, atLeast1UpperCaseCheck)
		&& std::regex_search(password, atLeast1LowerCaseCheck)
		&& std::regex_search(password, atLeast1DigitCheck)
		&& std::regex_search(password, atLeast1SpecialCharCheck);
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

template<class T1, class T2, int max = 10>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int* _trenutno;
public:
	Kolekcija() { _trenutno = new int(0); }
	~Kolekcija() {
		clearArrays();
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

	// Methods I added below
	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno{ new int{ kolekcija.getTrenutno() } }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ kolekcija.getElement1(i) };
			_elementi2[i] = new T2{ kolekcija.getElement2(i) };
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearArrays();

		*_trenutno = rhs.getTrenutno();

		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ rhs.getElement1(i) };
			_elementi2[i] = new T2{ rhs.getElement2(i) };
		}

		return *this;
	}

	[[nodiscard]] int getTrenutno() const noexcept { 
		return *_trenutno; 
	}

	void AddElement(const T1& element1, const T2& element2) {
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

	void RemoveAt(const int index) {
		if (index < 0 || index >= getTrenutno()) {
			return;
		}
		
		delete _elementi1[index];
		delete _elementi2[index];

		--(*_trenutno);

		for (int i = index; i < getTrenutno(); ++i) {
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}

		_elementi1[getTrenutno()] = nullptr;
		_elementi2[getTrenutno()] = nullptr;
	}

	T2& operator[](const T1& element1) {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (element1 == getElement1(i)) {
				return getElement2(i);
			}
		}
	}

private:
	void clearArrays() {
		for (size_t i = 0; i < *_trenutno; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
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

	[[nodiscard]] int64_t toInt64() const noexcept {
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
				std::begin(daysPerMonth),
				std::begin(daysPerMonth) + mjesec - 1,
				0
			);
		}();

		return total;
	}

	[[nodiscard]] int64_t operator-(const Datum& rhs) const noexcept {
		return toInt64() - rhs.toInt64();
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
	//int se odnosi na ocjenu u opsegu od 1 � 5, a Datum na datum kada je ocijenjena odredjena tehnika 
	Kolekcija<int, Datum*, brojTehnika>* _ocjene;
public:
	Tehnika(const char* naziv) {
		_naziv = GetNizKaraktera(naziv);
		_ocjene = new Kolekcija<int, Datum*, brojTehnika>{};
	}
	~Tehnika() {
		clearResources();
	}
	char* GetNaziv() { return _naziv; }
	Kolekcija<int, Datum*, brojTehnika>& GetOcjene() { return *_ocjene; }

	// Methods I added below
	Tehnika(const Tehnika& tehnika)
		: _naziv { GetNizKaraktera(tehnika.getNaziv()) }
		, _ocjene { tehnika.getOcjeneCopy() }
	{}

	Tehnika& operator=(const Tehnika& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearResources();

		_naziv = GetNizKaraktera(rhs.getNaziv());
		_ocjene = rhs.getOcjeneCopy();

		return *this;
	}

	[[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
		return ocjena >= 1 && ocjena <= 5;
	}

	[[nodiscard]] const char* getNaziv() const noexcept { 
		return _naziv; 
	}

	[[nodiscard]] const Kolekcija<int, Datum*, brojTehnika>& getOcjene() const noexcept { 
		return *_ocjene; 
	}

	[[nodiscard]] Kolekcija<int, Datum*, brojTehnika>* getOcjeneCopy() const {
		Kolekcija<int, Datum*, brojTehnika>* temp{
			new Kolekcija<int, Datum*, brojTehnika> {}
		};

		for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
			temp->AddElement(
				_ocjene->getElement1(i),
				new Datum { *_ocjene->getElement2(i) }
			);
		}

		return temp;
	}

	[[nodiscard]] double getAverage() const noexcept {
		const int size{ _ocjene->getTrenutno() };

		if (!size) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
			sum += _ocjene->getElement1(i);
		}

		return sum / size;
	}

	friend std::ostream& operator<<(std::ostream& os, const Tehnika& tehnika) {
		os << "Naziv tehnike: " << std::quoted(tehnika.getNaziv()) << '\n';
		os << "Ocjene - datum ocjene:\n";

		const auto& ocjene{ tehnika.getOcjene() };
		for (int i = 0; i < ocjene.getTrenutno(); ++i) {
			os << '\t' << ocjene.getElement1(i) << " - ";
			os << *ocjene.getElement2(i) << '\n';
		}

		const auto& originalPrecision{ os.precision() };
		os << std::setprecision(2) << std::fixed;

		os << "Prosjek ocjena -> " << tehnika.getAverage() << '\n';

		os << std::setprecision(originalPrecision);
		os.unsetf(std::ios::fixed);

		return os;
	}

	[[nodiscard]] bool daLiJeDatumValidan(const Datum& datumOcjene) const noexcept {
		const int size{ _ocjene->getTrenutno() };

		if (!size) {
			return true;
		}

		const auto& zadnjiDatum{ *_ocjene->getElement2(size - 1) };

		return (datumOcjene - zadnjiDatum) >= 3;
	}

	bool AddOcjena(const int ocjena, const Datum& datumOcjene) {
		if (!daLiJeOcjenaValidna(ocjena)) {
			return false;
		}
		else if (!daLiJeDatumValidan(datumOcjene)) {
			return false;
		}

		_ocjene->AddElement(ocjena, new Datum{ datumOcjene });

		return true;
	}

	[[nodiscard]] bool daLiSuOcjeneIDatumiIsti(
		const Kolekcija<int, Datum*, brojTehnika>& ocjene
	) const noexcept {
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
			&& daLiSuOcjeneIDatumiIsti(rhs.getOcjene());
	}

	[[nodiscard]] bool operator!=(const Tehnika& rhs) const noexcept {
		return !(*this == rhs);
	}

private:
	void clearResources() noexcept {
		delete[] _naziv; _naziv = nullptr;
		for (int i = 0; i < _ocjene->getTrenutno(); ++i) {
			delete _ocjene->getElement2(i);
		}
		delete _ocjene; _ocjene = nullptr;
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
		clearResources();
	}
	vector<Tehnika*>& GetTehnike() { return _polozeneTehnike; }
	Pojas GetPojas() { return _pojas; }
	friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
		COUT << obj._pojas << endl;
		for (size_t i = 0; i < obj._polozeneTehnike.size(); i++)
			COUT << *obj._polozeneTehnike[i];
		return COUT;
	}

	// Methods I added below
	Polaganje(const Polaganje& polaganje)
		: _pojas { polaganje.getPojas() }
		, _polozeneTehnike { polaganje.getTehnikeCopy() }
	{}

	Polaganje(Pojas pojas, const Tehnika& tehnika)
		: _pojas{ pojas }
	{
		_polozeneTehnike.push_back(new Tehnika{ tehnika });
	}

	Polaganje& operator=(const Polaganje& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearResources();

		_pojas = rhs.getPojas();
		_polozeneTehnike = rhs.getTehnikeCopy();

		return *this;
	}

	[[nodiscard]] const std::vector<Tehnika*>& getTehnike() const noexcept { 
		return _polozeneTehnike; 
	}
	
	[[nodiscard]] const Pojas& getPojas() const noexcept { 
		return _pojas; 
	}

	[[nodiscard]] std::vector<Tehnika*> getTehnikeCopy() const {
		std::vector<Tehnika*> temp{};

		for (const auto& tehnika : _polozeneTehnike) {
			temp.push_back(new Tehnika{ *tehnika });
		}

		return temp;
	}

	[[nodiscard]] std::size_t getBrojTehnika() const noexcept {
		return _polozeneTehnike.size();
	}

	[[nodiscard]] double getAverage() const noexcept {
		const auto& size{ _polozeneTehnike.size() };

		if (!size) {
			return 0.0;
		}

		return std::accumulate(
			std::begin(_polozeneTehnike),
			std::end(_polozeneTehnike),
			0.0,
			[](const double sum, const Tehnika* const tehnika) {
				return sum + tehnika->getAverage();
			}
		) / size;
	}

	[[nodiscard]] bool daLiTehnikaPostoji(const Tehnika& tehnikaZaProvjeriti) const noexcept {
		for (const auto& tehnika : _polozeneTehnike) {
			if (tehnikaZaProvjeriti == *tehnika) {
				return true;
			}
		}

		return false;
	}

	void dodajTehniku(const Tehnika& tehnika) {
		_polozeneTehnike.push_back(new Tehnika{ tehnika });
	}

private:
	void clearResources() noexcept {
		for (size_t i = 0; i < _polozeneTehnike.size(); i++) {
			delete _polozeneTehnike[i];
			_polozeneTehnike[i] = nullptr;
		}
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

	// Methods I added below
	Korisnik(const Korisnik& korisnik)
		: _imePrezime { GetNizKaraktera(korisnik.getImePrezime()) }
		, _emailAdresa { korisnik.getEmail() }
		, _lozinka { korisnik.getLozinka() }
	{}

	Korisnik& operator=(const Korisnik& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _imePrezime;

		_imePrezime = GetNizKaraktera(rhs.getImePrezime());
		_emailAdresa = rhs.getEmail();
		_lozinka = rhs.getLozinka();

		return *this;
	}

	[[nodiscard]] const std::string& getEmail() const noexcept { 
		return _emailAdresa; 
	}

	[[nodiscard]] const std::string& getLozinka() const noexcept { 
		return _lozinka; 
	}

	[[nodiscard]] const char* getImePrezime() const noexcept {
		return _imePrezime; 
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

	// Methods I added below
	KaratePolaznik(const KaratePolaznik& karatePolaznik)
		: Korisnik(karatePolaznik)
		, _polozeniPojasevi { karatePolaznik.getPolozeniPojasevi() }
	{}

	KaratePolaznik& operator=(const KaratePolaznik& rhs) {
		if (this == &rhs) {
			return *this;
		}

		Korisnik::operator=(rhs);
		_polozeniPojasevi = rhs.getPolozeniPojasevi();

		return *this;
	}

	friend ostream& operator<<(ostream& os, const KaratePolaznik& karatePolaznik) {
		os << karatePolaznik.getImePrezime() << " " << karatePolaznik.getEmail();
		os << " " << karatePolaznik.getLozinka() << '\n';
		for (const auto& polozeniPojas : karatePolaznik.getPolozeniPojasevi()) {
			os << polozeniPojas;
		}
		return os;
	}

	[[nodiscard]] const std::vector<Polaganje>& getPolozeniPojasevi() const noexcept { 
		return _polozeniPojasevi; 
	}

	[[nodiscard]] Polaganje* getPolaganjeForPojas(Pojas pojas) {
		auto polaganjeZaPronaci{
			std::find_if(
				std::begin(_polozeniPojasevi),
				std::end(_polozeniPojasevi),
				[&](const Polaganje& polaganje) {
						return polaganje.getPojas() == pojas;
				}
			)
		};

		return (polaganjeZaPronaci == std::end(_polozeniPojasevi)) ? nullptr : &(*polaganjeZaPronaci);
	}

	[[nodiscard]] bool daLiJeIspunjenUslovZaVisiPojas(Pojas pojas) {
		const auto& size{ _polozeniPojasevi.size() };

		if (!size) {
			return true;
		}

		const auto& zadnjiPojas{ _polozeniPojasevi.back() };

		return zadnjiPojas.getPojas() + 1 == pojas && zadnjiPojas.getBrojTehnika() > 3 && zadnjiPojas.getAverage() > 3.5;
	}

	bool AddTehniku(Pojas pojas, const Tehnika& tehnika) {
		auto polaganje{ getPolaganjeForPojas(pojas) };

		if (polaganje) {
			if (polaganje->daLiTehnikaPostoji(tehnika)) {
				return false;
			}

			polaganje->dodajTehniku(tehnika);
			sendMail(*polaganje);
			return true;
		}
		else if (!daLiJeIspunjenUslovZaVisiPojas(pojas)) {
			return false;
		}

		_polozeniPojasevi.push_back(Polaganje{ pojas, tehnika });
		sendMail(_polozeniPojasevi.back());
		return true;
	}

	[[nodiscard]] double getAverage() const noexcept {
		const auto& size{ _polozeniPojasevi.size() };

		if (!size) {
			return 0.0;
		}

		return std::accumulate(
			std::begin(_polozeniPojasevi),
			std::end(_polozeniPojasevi),
			0.0,
			[](const double sum, const Polaganje& polaganje) {
				return sum + polaganje.getAverage();
			}
		) / size;
	}
private:
	void sendMail(const Polaganje& polaganje) const {
		std::thread emailThread {
			[&]() {
				const auto& originalPrecision{ std::cout.precision() };
				std::cout << std::setprecision(2) << std::fixed;

				std::cout << "FROM:info@karate.ba\n";
				std::cout << "TO: " << getEmail() << '\n';
				std::cout << "Postovani " << getImePrezime() << ", evidentirana vam je thenika " << polaganje.getTehnike().back()->getNaziv();
				std::cout << " za " << polaganje.getPojas() << " pojas. Dosadasnji uspjeh (prosjek ocjena) na pojas\n";
				std::cout << polaganje.getPojas() << " iznosi " << polaganje.getAverage() << ", a ukupni uspjeh (prosjek ocjena) ";
				std::cout << "na svim pojasevima iznosi " << getAverage() << ".\n";
				std::cout << "Pozdrav.\n";
				std::cout << "KARATE Team.\n";

				std::cout << std::setprecision(originalPrecision);
				std::cout.unsetf(std::ios::fixed);
			}
		};

		emailThread.join();
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite ulogu operatora reinterpret_cast.\n";
	return "Odgovor -> reinterpret_cast operator kada pretvara jedan tip podatka u drugi samo tretira set bitova kao da su taj drugi tip podatka, "
		"za razliku od cast-a kao sto je static_cast koji ce promjeniti set bitova da vrijednost se pravilno predstavi u drugom tipu podatka."
		"Zbog cega je veoma lahko preko ovog cast-a doci do nedefinisanog ponasanja unutar programa. ";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Ukratko opisite znacaj i vrste pametnih pokazivaca.\n";
	return "Odgovor -> Pametni pokazivac je tip podatka koji pruza funkcionalnost pointera sa automatskim memory management. Kada se smart pointer"
		" vise ne koristi (ode izvan opsega ili pozivom metode kao sto je reset) memorija je dealocirana. Neki od tipova koji dodu kao dio "
		" standardne biblioteke su std::unique_ptr, std::shared_ptr, std::weak_ptr i std::auto_ptr.";
}
void main() {

	cout << PORUKA;
	cin.get();

	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();

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