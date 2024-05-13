#include <iostream>
using namespace std;

// Headers I included below

#include<string>
#include<vector>
#include<regex>
#include<iomanip>
#include<numeric>
#include<array>
#include<thread>

// Headers I included above

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
const int brojTehnika = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";
char* GetNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

// Constans I defined below

const std::string& invalidPasswordValue{ "<VRIJEDNOST_NIJE_VALIDNA>" };

// Constans I defined above

// Functions I defined below
/*
	za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
	- najmanje 7 znakova
	- velika i mala slova
	- najmanje jedan broj
   - najmanje jedan specijalni znak
*/

[[nodiscard]] bool ValidirajLozinku(const std::string& password) {
	if (password.size() < 7) {
		return false;
	}

	std::regex upperCaseCheck{ "[A-Z]+" };
	std::regex lowerCaseCheck{ "[a-z]+" };
	std::regex specialCharsCheck{ "\\W+" };
	std::regex numberChecks{ "[0-9]+" };

	return std::regex_search(password, upperCaseCheck)
		&& std::regex_search(password, lowerCaseCheck)
		&& std::regex_search(password, specialCharsCheck)
		&& std::regex_search(password, numberChecks);
}

[[nodiscard]] const char* getPojasAsCStr(const Pojas& pojas) noexcept {
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
	os << getPojasAsCStr(pojas);

	return os;
}

// Functions I defined above

template<class T1, class T2, int max = 10>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int* _trenutno;
public:
	Kolekcija() {
		_trenutno = new int{ 0 };
	}
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

	// Methods I added below
	
	Kolekcija(const Kolekcija& kolekcija) 
		: _trenutno{ new int { kolekcija.getTrenutno() } }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ kolekcija.getElement1(i) };
			_elementi2[i] = new T2{ kolekcija.getElement2(i) };
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		if (this == &rhs) return *this;

		for (int i = 0; i < getTrenutno(); ++i) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}

		*_trenutno = rhs.getTrenutno();

		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ rhs.getElement1(i) };
			_elementi2[i] = new T2{ rhs.getElement2(i) };
		}

		return *this;
	}

	Kolekcija& operator=(Kolekcija&& rhs) noexcept {
		if (this == &rhs) return *this;

		for (int i = 0; i < getTrenutno(); ++i) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}

		delete _trenutno;
		_trenutno = std::exchange(rhs._trenutno, new int{ 0 });

		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = std::exchange(rhs._elementi1[i], nullptr);
			_elementi2[i] = std::exchange(rhs._elementi2[i], nullptr);
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
		else if (index < 0 || index > getTrenutno()) {
			// Exception could be thrown here
			// Not specified so I won't
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
		if (index < 0 || index > getTrenutno()) {
			// Exception could be thrown here
			// Not specified so I won't
			return;
		}

		delete _elementi1[index];
		delete _elementi2[index];

		for (int i = index; i < getTrenutno() - 1; ++i) {
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}

		--(*_trenutno);

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
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}

	// Methods I defined below

	Datum(const Datum& datum)
		: _dan { new int { datum.getDan() } }
		, _mjesec { new int { datum.getMjesec() } }
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

	[[nodiscard]] int getDan() const noexcept {
		return *_dan;
	}

	[[nodiscard]] int getMjesec() const noexcept {
		return *_mjesec;
	}

	[[nodiscard]] int getGodina() const noexcept {
		return *_godina;
	}

	[[nodiscard]] int64_t getDatumAsDays() const noexcept {
		int64_t total{ 0 };

		const int mjesec{ getMjesec() };
		int godina{ getGodina() };

		total += getDan();
		total += 365LL * godina;

		if (mjesec <= 2) {
			--godina;
		}

		total += (godina / 4LL + godina / 400LL - godina / 100LL);

		total += [&]() {
			constexpr std::array<int, 12>brojDanaUMjesecima{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			
			return std::accumulate(
				std::begin(brojDanaUMjesecima),
				std::begin(brojDanaUMjesecima) + mjesec - 1,
				0
			);
		}();

		return total;
	}

	[[nodiscard]] int64_t operator-(const Datum& rhs) const noexcept {
		return getDatumAsDays() - rhs.getDatumAsDays();
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
	Kolekcija<int, Datum*, brojTehnika> _ocjene;
public:
	Tehnika(const char* naziv) {
		_naziv = GetNizKaraktera(naziv);
	}
	~Tehnika() {
		delete[] _naziv; _naziv = nullptr;
		for (int i = 0; i < _ocjene.getTrenutno(); ++i) {
			delete _ocjene.getElement2(i);
		}
	}
	char* GetNaziv() { return _naziv; }
	Kolekcija<int, Datum*, brojTehnika>& GetOcjene() { return _ocjene; }

	// Methods I defined below

	Tehnika(const Tehnika& tehnika)
		: _naziv{ GetNizKaraktera(tehnika.getNaziv()) }
	{
		const auto& ocjene{ tehnika.getOcjene() };
		for (int i = 0; i < ocjene.getTrenutno(); ++i) {
			_ocjene.AddElement(
				ocjene.getElement1(i),
				new Datum { *ocjene.getElement2(i) }
			);
		}
	}

	Tehnika& operator=(const Tehnika& rhs) {
		char* const tempNaziv{ GetNizKaraktera(rhs.getNaziv()) };
		Kolekcija<int, Datum*, brojTehnika> tempOcjene{};

		const auto& ocjene{ rhs.getOcjene() };
		for (int i = 0; i < ocjene.getTrenutno(); ++i) {
			tempOcjene.AddElement(
				ocjene.getElement1(i),
				new Datum{ *ocjene.getElement2(i) }
			);
		}

		delete[] _naziv;
		_naziv = tempNaziv;

		_ocjene = std::move(tempOcjene);

		return *this;
	}

	[[nodiscard]] const char* getNaziv() const noexcept {
		return _naziv;
	}

	[[nodiscard]] const Kolekcija<int, Datum*, brojTehnika>& getOcjene() const noexcept {
		return _ocjene;
	}

	[[nodiscard]] bool daLiJeRazmakIzmeduPolaganjaDovoljan(const Datum& datumPolaganja) const noexcept {
		const int lastIndex{ _ocjene.getTrenutno() - 1 };

		if (lastIndex == -1) {
			return true;
		}

		const auto& zadnjiDatum{ *_ocjene.getElement2(lastIndex) };

		return (datumPolaganja - zadnjiDatum) >= 3;
	}

	[[nodiscard]] bool daLiJeOcjenaUredu(const int ocjena) const noexcept {
		return ocjena >= 1 && ocjena <= 5;
	}

	/*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise
	navrata.
	 - razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
	 - nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec
	evidentirane (bez obzira sto je stariji od 3 dana)
	 */
	bool AddOcjena(const int ocjena, const Datum& datumPolaganja) {
		if (!daLiJeRazmakIzmeduPolaganjaDovoljan(datumPolaganja) || !daLiJeOcjenaUredu(ocjena)) {
			return false;
		}

		_ocjene.AddElement(
			ocjena,
			new Datum { datumPolaganja }
		);

		return true;
	}

	[[nodiscard]] double getAverageGrade() const noexcept {
		const int size{ _ocjene.getTrenutno() };
		
		if (!size) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (int i = 0; i < size; ++i) {
			sum += _ocjene.getElement1(i);
		}

		return sum / size;
	}

	friend std::ostream& operator<<(std::ostream& os, const Tehnika& tehnika) {
		os << "Tehnika: " << tehnika.getNaziv() << '\n';
		os << "Ocjene i datum polaganja:\n";

		const auto& ocjene{ tehnika.getOcjene() };

		for (int i = 0; i < ocjene.getTrenutno(); ++i) {
			os << '\t' << ocjene.getElement1(i) << " - ";
			os << *ocjene.getElement2(i) << '\n';
		}

		os << "Prosjecna ocjena: " << tehnika.getAverageGrade() << '\n';

		return os;
	}

	[[nodiscard]] bool areGradesTheSame(const Kolekcija<int, Datum*, brojTehnika>& ocjene) const noexcept {
		for (int i = 0; i < _ocjene.getTrenutno(); ++i) {
			if (_ocjene.getElement1(i) != ocjene.getElement1(i)) {
				return false;
			}
			else if (*_ocjene.getElement2(i) != *ocjene.getElement2(i)) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]] bool operator==(const Tehnika& rhs) const noexcept {
		return !std::strcmp(getNaziv(), rhs.getNaziv())
			&& areGradesTheSame(rhs.getOcjene());
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

	// Methods I added
	Polaganje(const Pojas& pojas, const Tehnika& tehnika)
		: _pojas { pojas }
	{
		_polozeneTehnike.push_back(new Tehnika{ tehnika });
	}

	Polaganje(const Polaganje& polaganje)
		: _pojas{ polaganje.getPojas() }
	{
		const auto& polozeneTehnike{ polaganje.getTehnike() };
		for (const auto& polozenaTehnika : polozeneTehnike) {
			_polozeneTehnike.push_back(new Tehnika{ *polozenaTehnika });
		}
	}

	Polaganje& operator=(const Polaganje& rhs) {
		_pojas = rhs.getPojas();

		std::vector<Tehnika*> tempPolozeneTehnike{};

		const auto& polozeneTehnike{ rhs.getTehnike() };
		for (const auto& polozenaTehnika : polozeneTehnike) {
			tempPolozeneTehnike.push_back(new Tehnika{ *polozenaTehnika });
		}

		for (const auto& polozenaTehnika : _polozeneTehnike) {
			delete polozenaTehnika;
		}

		_polozeneTehnike = std::move(tempPolozeneTehnike);

		return *this;
	}

	[[nodiscard]] const std::vector<Tehnika*>& getTehnike() const noexcept { 
		return _polozeneTehnike; 
	}

	[[nodiscard]] Pojas getPojas() const noexcept { 
		return _pojas; 
	}

	[[nodiscard]] bool daLiTehnikaPostoji(const Tehnika& tehnika) const noexcept {
		const auto& postojecaTehnika{
			std::find_if(
				std::begin(_polozeneTehnike),
				std::end(_polozeneTehnike),
				[&](const Tehnika* const trenutnaTehnika) {
						return tehnika == *trenutnaTehnika;
					}
			)
		};

		return postojecaTehnika != std::end(_polozeneTehnike);
	}

	void dodajTehniku(const Tehnika& tehnika) {
		_polozeneTehnike.push_back(new Tehnika{ tehnika });
	}

	[[nodiscard]] bool daLiJeProsjekSvakeTehnikeVeciOd(const double average) const noexcept {
		for (const auto& polozenaTehnika : _polozeneTehnike) {
			if (polozenaTehnika->getAverageGrade() <= average) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]] double getAverage() const noexcept {
		if (!_polozeneTehnike.size()) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (const auto& polozenaTehnika : _polozeneTehnike) {
			sum += polozenaTehnika->getAverageGrade();
		}

		return sum / _polozeneTehnike.size();
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
		_lozinka = ValidirajLozinku(lozinka)? lozinka : invalidPasswordValue;//inicijalizirati na nacin zahtijevan u zadatku
	}
	virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
	string GetEmail() { return _emailAdresa; }
	string GetLozinka() { return _lozinka; }
	char* GetImePrezime() { return _imePrezime; }

	// Methods I added below

	Korisnik(const Korisnik& korisnik)
		: _imePrezime { GetNizKaraktera(korisnik.getImePrezime()) }
		, _emailAdresa { korisnik.getEmailAdresa() }
		, _lozinka { korisnik.getLozinka() }
	{}

	Korisnik& operator=(const Korisnik& rhs) {
		char* const tempImePrezime{ GetNizKaraktera(rhs.getImePrezime()) };
		std::string tempEmailAdresa{ rhs.getEmailAdresa() };
		std::string tempLozinka{ rhs.getLozinka() };

		delete[] _imePrezime;

		_imePrezime = tempImePrezime;
		_emailAdresa = std::move(tempEmailAdresa);
		_lozinka = std::move(tempLozinka);

		return *this;
	}

	[[nodiscard]] const char* getImePrezime() const noexcept {
		return _imePrezime;
	}

	[[nodiscard]] const std::string& getEmailAdresa() const noexcept {
		return _emailAdresa;
	}

	[[nodiscard]] const std::string& getLozinka() const noexcept {
		return _lozinka;
	}
};
class KaratePolaznik : public Korisnik {
	vector<Polaganje*> _polozeniPojasevi;
public:
	KaratePolaznik(const char* imePrezime, string emailAdresa, string lozinka)
		: Korisnik(imePrezime, emailAdresa, lozinka)
	{}
	~KaratePolaznik() {
		cout << crt << "DESTRUKTOR -> KaratePolaznik" << crt;
		for (size_t i = 0; i < _polozeniPojasevi.size(); i++) {
			delete _polozeniPojasevi[i];
			_polozeniPojasevi[i] = nullptr;
		}
	}
	friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
		COUT << obj.GetImePrezime() << " " << obj.GetEmail() << " " <<
			obj.GetLozinka() << endl;
		for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
			COUT << *obj._polozeniPojasevi[i];
		return COUT;
	}
	vector<Polaganje*>& GetPolozeniPojasevi() { return _polozeniPojasevi; }

	// Methods I added

	KaratePolaznik(const KaratePolaznik& karatePolaznik)
		: Korisnik(karatePolaznik)
	{
		const auto& polozeniPojasevi{ karatePolaznik.getPolozeniPojasevi() };
		for (const auto polozeniPojas : polozeniPojasevi) {
			_polozeniPojasevi.push_back(new Polaganje{ *polozeniPojas });
		}
	}

	KaratePolaznik& operator=(const KaratePolaznik& rhs) {
		Korisnik::operator=(rhs);

		std::vector<Polaganje*> tempPolozeniPojasevi{};

		const auto& polozeniPojasevi{ rhs.getPolozeniPojasevi() };
		for (const auto polozeniPojas : polozeniPojasevi) {
			_polozeniPojasevi.push_back(new Polaganje{ *polozeniPojas });
		}

		for (const auto polozeniPojas : _polozeniPojasevi) {
			delete polozeniPojas;
		}

		_polozeniPojasevi = std::move(tempPolozeniPojasevi);

		return *this;
	}

	[[nodiscard]] const std::vector<Polaganje*>& getPolozeniPojasevi() const noexcept { 
		return _polozeniPojasevi; 
	}

	/*
		svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju
		tehnike)
		 sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju
		unutar istog objekta tipa Polaganje,
		 tom prilikom onemoguciti:
		 - dodavanje istih (moraju biti identicne vrijednosti svih atributa)
		tehnika na nivou jednog pojasa,
		 - dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane
		najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
		 (onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3
		tehnike za ZUTI pojas i njihov prosjek je veci od 3.5)
		 funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	[[nodiscard]] Polaganje* getPojas(const Pojas& pojas) {
		auto pronadenoPolaganje{ std::find_if(
				std::begin(_polozeniPojasevi),
				std::end(_polozeniPojasevi),
				[&](const Polaganje* const polaganje) {
					return pojas == polaganje->getPojas();
				}
			)
		};

		return (pronadenoPolaganje != std::end(_polozeniPojasevi))? *pronadenoPolaganje : nullptr;
	}

	[[nodiscard]] const Polaganje* const getPojas(const Pojas& pojas) const {
		auto pronadenoPolaganje{ std::find_if(
				std::begin(_polozeniPojasevi),
				std::end(_polozeniPojasevi),
				[&](const Polaganje* const polaganje) {
					return pojas == polaganje->getPojas();
				}
			)
		};

		return (pronadenoPolaganje != std::end(_polozeniPojasevi)) ? *pronadenoPolaganje : nullptr;
	}

	[[nodiscard]] bool daLiJeIspunjenUslovZaDodavanjeNovogPojasa(const Pojas& pojas) const noexcept {
		if (!_polozeniPojasevi.size()) {
			return true;
		}

		const auto& lastPojas{ *_polozeniPojasevi.back() };

		if (lastPojas.getPojas() + 1 != pojas) {
			return false;
		}
		else if (lastPojas.getTehnike().size() < 3 || lastPojas.daLiJeProsjekSvakeTehnikeVeciOd(3.5)) {
			return false;
		}
	}

	bool AddTehniku(const Pojas& pojas, const Tehnika& tehnika) {
		auto postojeciPojas{ getPojas(pojas) };

		if (postojeciPojas) {
			if (postojeciPojas->daLiTehnikaPostoji(tehnika)) {
				return false;
			}
			postojeciPojas->dodajTehniku(tehnika);
			sendMail(pojas, tehnika);
			return true;
		}
		else if (!daLiJeIspunjenUslovZaDodavanjeNovogPojasa(pojas)) {
			return false;
		}

		_polozeniPojasevi.push_back(new Polaganje{ pojas, tehnika });

		sendMail(pojas, tehnika);
		return true;
	}

	[[nodiscard]] double getAverageForPojas(const Pojas& pojas) const noexcept {
		const auto& postojeciPojas{ getPojas(pojas) };

		if (!postojeciPojas) {
			return 0.0;
		}

		return postojeciPojas->getAverage();
	}

	[[nodiscard]] double getAverage() const noexcept {
		if (!_polozeniPojasevi.size()) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (const auto& polozeniPojas : _polozeniPojasevi) {
			sum += polozeniPojas->getAverage();
		}

		return sum / _polozeniPojasevi.size();
	}

private:
	/*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje
		email sa porukom:
		 FROM:info@karate.ba
		 TO: emailKorisnika
		 Postovani ime i prezime, evidentirana vam je thenika X za Y pojas.
		Dosadasnji uspjeh (prosjek ocjena)
		 na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima
		iznosi Z.
		Fakultet informacijskih tehnologija
		Pismeni dio ispita
		Pozdrav.
		 KARATE Team.
		 slanje email poruka implemenitrati koristeci zasebne thread-ove.
	*/

	void sendMail(const Pojas& pojas, const Tehnika& tehnika) const {
		std::thread emailThread{
			[&]() {
				const auto& defaultPrecision { std::cout.precision() };

				std::cout << std::setprecision(2);
				std::cout << std::fixed;

				std::cout << "FROM:info@karate.ba\n";
				std::cout << "TO: " << getEmailAdresa() << '\n';
				std::cout << "Postovani " << getImePrezime() << ", evidentirana vam je thenika ";
				std::cout << tehnika.getNaziv() << " za " << pojas << " pojas\nDosadasnji uspjeh (prosjek ocjena)";
				std::cout << " na pojasu " << pojas << " iznosi " << getAverageForPojas(pojas);
				std::cout << ", a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi " << getAverage() << ".\n";
				std::cout << "Fakultet informacijskih tehnologija\nPismeni dio ispita\nPozdrav.\nKARATE Team.\n";

				std::cout << std::setprecision(defaultPrecision);
				std::cout.unsetf(std::ios::fixed);
			}
		};

		emailThread.join();
	}
};
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite ulogu operatora const_cast?\n";
	return "Odgovor -> Operator const_cast moze dodati ili smaketi const na nekoj varijabli, ali modificiranje varijable takve je "
		"jedino validno u slucaju da orginalni objekat nije const. Npr. ako imamo neki objekat a koji je const, smaketi const sa njega "
		"sa const cast i modificiranje njega bi dovelo do nedefinisanog ponasanja. Da je a bio objekat koji nije const, i ima referencu "
		"b koja jest const, smaketi const sa b i modificiranje njega je ok.";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Ukratko opisite redoslijed kreiranja objekta bazne klase u slucaju visestrukog nasljedjivanja(prilikom instanciranja objekta najizvedenije klase), te koja su moguca rjesenja najznacajnijih problema ubtom kontekstu ? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const std::string& PORUKA{ "Nisam siguran zasto ova varijabla nije bila definisana na pocetku zadatka, niti sta predstavlja\n" };
void main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	Datum datum19062020(19, 6, 2020),
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
	/*uklanja par (T1 i T2) iz kolekcije koji se nalazi na lokaciji sa
   proslijedjenim indeksom.
	nakon uklanjanja vrijednosti onemoguciti pojavu praznog prostora unutar
   kolekcije tj.
	pomjeriti sve elemente koji se nalaze nakon proslijedjene lokacije za
   jedno mjesto unazad
	npr. ako unutar kolekcije postoje elementi
	0 0
	1 1
	2 2
	3 3
	nakon uklanjanja vrijednosti na lokaciji 1, sadrzaj kolekcije ce biti
   sljedeci
	0 0
	2 2
	3 3
	*/
	cout << kolekcija1 << crt;
	kolekcija1.AddElement(9, 9, 2);
	/*funkciji AddElement se, kao treci parametar, moze proslijediti i
   lokacija na koju se dodaju
	nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene
   za jedno mjesto unaprijed
	u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje
   elementi
	0 0
	1 1
	2 2
	3 3
	nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce
   biti sljedeci
	0 0
	9 9
	1 1
	2 2
   3 3
	*/
	cout << kolekcija1 << crt;
	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija1 << crt;
	//na osnovu vrijednosti T2 mijenja vrijednost T1.
	kolekcija1[9] = 2;
	/* npr.ako unutar kolekcije postoje elementi:
	0 0
	9 9
	1 1
	2 2
	3 3
	nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
	0 0
	2 9
	1 1
	2 2
	3 3
	*/
	Tehnika choku_zuki("choku_zuki"),
		gyaku_zuki("gyaku_zuki"),
		kizami_zuki("kizami_zuki"),
		oi_zuki("oi_zuki");
	/*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise
   navrata.
	- razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
	- nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec
   evidentirane (bez obzira sto je stariji od 3 dana)
	*/
	if (choku_zuki.AddOcjena(1, datum19062020))
		cout << "Ocjena evidentirana!" << endl;
	if (!choku_zuki.AddOcjena(5, datum20062020))
		cout << "Ocjena NIJE evidentirana!" << endl;
	if (choku_zuki.AddOcjena(5, datum30062020))
		cout << "Ocjena evidentirana!" << endl;
	// ispisuje: naziv tehnike, ocjene (zajedno sa datumom) i prosjecnu ocjenu za tu tehniku
		// ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0
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
	- najmanje 7 znakova
	- velika i mala slova
	- najmanje jedan broj
   - najmanje jedan specijalni znak
	za provjeru validnosti lozinke koristiti globalnu funkciju
   ValidirajLozinku, a unutar nje regex metode.
	validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u
   slucaju da nije validna
	postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
	*/
	Korisnik* jasmin = new KaratePolaznik("Jasmin Azemovic",
		"jasmin@karate.ba", "j@sm1N*");
	Korisnik* adel = new KaratePolaznik("Adel Handzic", "adel@edu.karate.ba",
		"4Ade1*H");
	Korisnik* lozinkaNijeValidna = new KaratePolaznik("John Doe",
		"john.doe@google.com", "johndoe");
	/*
	svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju
   tehnike)
	sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju
   unutar istog objekta tipa Polaganje,
	tom prilikom onemoguciti:
	- dodavanje istih (moraju biti identicne vrijednosti svih atributa)
   tehnika na nivou jednog pojasa,
	- dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane
   najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
	(onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3
   tehnike za ZUTI pojas i njihov prosjek je veci od 3.5)
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
		if (jasminPolaznik->AddTehniku(ZUTI, kizami_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		if (jasminPolaznik->AddTehniku(ZUTI, oi_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		if (jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		//ne treba dodati choku_zuki jer je vec dodana za zuti pojas
		if (!jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
			cout << "Tehnika NIJE uspjesno dodana!" << crt;
		//ispisuje sve dostupne podatke o karate polazniku
		cout << *jasminPolaznik << crt;
	}
	/*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje
   email sa porukom:
	FROM:info@karate.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirana vam je thenika X za Y pojas.
   Dosadasnji uspjeh (prosjek ocjena)
	na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima
   iznosi Z.
   Fakultet informacijskih tehnologija
   Pismeni dio ispita
   Pozdrav.
	KARATE Team.
	slanje email poruka implemenitrati koristeci zasebne thread-ove.
	*/
	//osigurati da se u narednim linijama poziva i destruktor klase KaratePolaznik
	delete jasmin;
	delete adel;
	delete lozinkaNijeValidna;
	cin.get();
	system("pause>0");
}