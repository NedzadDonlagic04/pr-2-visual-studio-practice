#include <iostream>
using namespace std;
const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI METODA (SVE ISTO VAZI I ZA FUNKCIJE), TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI "
"ONIMA KOJI SU KORISTENI U TESTNOM CODE - U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU."
"OSTALE POMOCNE METODE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U METODAMA U KOJIMA JE TO NAZNACENO.\n"
"6. SVE METODE POZVANE U MAIN-U ZADATKA TREBAJU POSTOJATI. UKOLIKO NISTE ZADOVOLJNI IMPLEMENTACIJOM"
"POTREBNO JE DA IMPLEMENTIRATE BAREM TIJELO TIH METODA (METODA MOZE BITI PRAZNA),"
"A AKO METODA TREBA VRATITI NEKI PODATAK ONDA MOZETE VRATITI BILO KOJU TJ.ZELJENU VRIJEDNOST ZAHTIJEVANOG TIPA.!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRAJTE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA npr.IB150051.docx)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11.ZA POTREBE TESTIRANJA, U MAIN-U, BUDITE SLOBODNI DODATI TESTNIH PODATAKA(POZIVA METODA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12.ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022 I RJESENJE TESTIRAJTE U OBA MODA(F5 i Ctrl + F5)!\n"
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJEŠENJE KOPIRALI U ADEKVATAN FOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";

// Headers I included below
#include<string>
#include<regex>
#include<sstream>
#include<thread>
#include<iomanip>
#include<numeric>
// Headers I included above

enum Drzava { ENGLESKA, SPANIJA, HOLANDIJA, FRANCUSKA, BOSNA_I_HERCEGOVINA };

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}

// Functions I added below
std::ostream& operator<<(std::ostream& os, Drzava drzava) {
	switch (drzava) {
	case Drzava::ENGLESKA:
		os << "ENGLESKA";
		break;
	case Drzava::SPANIJA:
		os << "SPANIJA";
		break;
	case Drzava::HOLANDIJA:
		os << "HOLANDIJA";
		break;
	case Drzava::FRANCUSKA:
		os << "FRANCUSKA";
		break;
	case Drzava::BOSNA_I_HERCEGOVINA:
		os << "BOSNA_I_HERCEGOVINA";
		break;
	default:
		os << "Drzava ne postoji";
	}

	return os;
}

[[nodiscard]] unsigned int getDigitCount(int num) {
	unsigned int counter{ 0 };

	do {
		++counter;
		num /= 10;
	} while (num);

	return counter;
}

[[nodiscard]] char* GenerisiID(const int num, const unsigned int maxDigitsInId = 4) {
	const unsigned int digitsCount{ getDigitCount(num) };

	if (maxDigitsInId < digitsCount) {
		return nullptr;
	}

	const unsigned int leadingZerosCount{ maxDigitsInId - digitsCount };
	std::ostringstream idBuffer{};

	idBuffer << "ID#" << std::string(leadingZerosCount, '0');
	if (leadingZerosCount) {
		idBuffer << '-';
	}
	idBuffer << num;

	return GetNizKaraktera(idBuffer.str().c_str());
}

[[nodiscard]] std::regex GenerateRegexForID(const unsigned int digitsCount, const unsigned int maxDigitsInId = 4) {
	if (maxDigitsInId < digitsCount || !digitsCount) {
		return {};
	}

	const unsigned int leadingZerosCount{ maxDigitsInId - digitsCount };
	std::ostringstream regexForIDBuffer{};

	regexForIDBuffer << "ID#" << std::string(leadingZerosCount, '0');
	if (leadingZerosCount) {
		regexForIDBuffer << '-';
	}
	regexForIDBuffer << "[1-9][0-9]{" << digitsCount - 1 << "}";

	// Debugging 
	// std::cout << regexForIDBuffer.str() << '\n';
	
	return std::regex{ regexForIDBuffer.str() };
}

[[nodiscard]] bool ValidirajID(const std::string& id, const unsigned int maxDigitInId = 4) {
	std::regex idValidation{};
	for (unsigned int i = 1; i <= maxDigitInId; ++i) {
		idValidation = GenerateRegexForID(i, maxDigitInId);
		if (std::regex_match(id, idValidation)) {
			return true;
		}
	}

	return false;
}
// Functions I added above

template<class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max]{ nullptr };
	T2* _elementi2[max]{ nullptr };
	int* _trenutno;
public:
	Kolekcija() {
		_trenutno = new int{ 0 };
	}
	~Kolekcija() {
		clearArrays();
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija)const {
		return *_elementi1[lokacija];
	}
	T2& getElement2(int lokacija)const {
		return *_elementi2[lokacija];
	}
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno { new int { kolekcija.getTrenutno() } }
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

	void AddElement(const T1& element1, const T2& element2) {
		if (getTrenutno() == max) {
			return;
		}

		_elementi1[getTrenutno()] = new T1{ element1 };
		_elementi2[getTrenutno()] = new T2{ element2 };

		++(*_trenutno);
	}

	Kolekcija InsertAt(const int index, const T1& element1, const T2& element2) {
		if (getTrenutno() == max || index < 0 || index >= getTrenutno()) {
			return *this;
		}

		for (int i = getTrenutno(); i > index; --i) {
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}

		_elementi1[index] = new T1{ element1 };
		_elementi2[index] = new T2{ element2 };

		++(*_trenutno);

		return *this;
	}

	void RemoveAt(const int index) {
		if (getTrenutno() == 0 || index < 0 || index >= getTrenutno()) {
			return;
		}

		--(*_trenutno);

		for (int i = index; i < getTrenutno(); ++i) {
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}

		_elementi1[getTrenutno()] = nullptr;
		_elementi2[getTrenutno()] = nullptr;
	}

	Kolekcija* RemoveRange(const int start, const int end) {
		if (start < 0) {
			throw std::runtime_error("Start index nije u opsegu");
		}
		else if (end >= getTrenutno()) {
			throw std::runtime_error("End index nije u opsegu");
		}
		else if (start > end) {
			throw std::runtime_error("Start index je veci od end indexa");
			/*
				Posto komentar ima dio koji kaze "U slucaju da zahtijevani opseg ne postoji u kolekciji metoda treba baciti izuzetak"
				vjerujem da je naglaseno da se uzme u obzir da ne bude da se ide od 6 do 1
				Iako da se ovo proslijedi nece se nista desiti jer uslov for petlje ispod nece se ispuniti, so yeah
			*/
		}

		Kolekcija* temp{ new Kolekcija{} };

		for (int i = start; i <= end; ++i) {
			temp->AddElement(getElement1(start), getElement2(start));
			RemoveAt(start);
		}

		return temp;
	}

private:
	void clearArrays() {
		for (size_t i = 0; i < *_trenutno; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
};
class Vrijeme {
	int* _sat, * _minuta, * _sekunda;
public:
	Vrijeme(int sat = 10, int minuta = 0, int sekunda = 0) {
		_sat = new int(sat);
		_minuta = new int(minuta);
		_sekunda = new int(sekunda);
	}
	~Vrijeme() {
		delete _sat; _sat = nullptr;
		delete _minuta; _minuta = nullptr;
		delete _sekunda; _sekunda = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Vrijeme& obj) {
		COUT << *obj._sat << ":" << *obj._minuta << ":" << *obj._sekunda;
		return COUT;
	}

	// Methods I added below
	Vrijeme(const Vrijeme& vrijeme)
		: _sat{ new int{ vrijeme.getSat() } }
		, _minuta{ new int{ vrijeme.getMinuta() } }
		, _sekunda{ new int{ vrijeme.getSekunda() } }
	{}

	Vrijeme& operator=(const Vrijeme& rhs) noexcept {
		*_sat = rhs.getSat();
		*_minuta = rhs.getMinuta();
		*_sekunda = rhs.getSekunda();

		return *this;
	}

	[[nodiscard]] int getSat() const noexcept {
		return *_sat;
	}

	[[nodiscard]] int getMinuta() const noexcept {
		return *_minuta;
	}

	[[nodiscard]] int getSekunda() const noexcept {
		return *_sekunda;
	}

	[[nodiscard]] int toInt() const noexcept {
		return getSekunda() + getMinuta() * 60 + getSat() * 3600;
	}

	[[nodiscard]] bool operator==(const Vrijeme& rhs) const noexcept {
		return getSat() == rhs.getSat()
			&& getMinuta() == rhs.getMinuta()
			&& getSekunda() == rhs.getSekunda();
	}

	[[nodiscard]] bool operator!=(const Vrijeme& rhs) const noexcept {
		return !(*this == rhs);
	}

	[[nodiscard]] bool operator>=(const Vrijeme& rhs) const noexcept {
		return toInt() >= rhs.toInt();
	}

	[[nodiscard]] bool operator<=(const Vrijeme& rhs) const noexcept {
		return toInt() <= rhs.toInt();
	}
};
class Pogodak {
	Vrijeme _vrijemePogotka;
	char* _napomena;
public:
	Pogodak(Vrijeme vrijeme, const char* napomena) :
		_vrijemePogotka(vrijeme)
	{
		_napomena = GetNizKaraktera(napomena);
	}
	~Pogodak()
	{
		delete[] _napomena; _napomena = nullptr;
	}
	Vrijeme GetVrijemePogotka() { return _vrijemePogotka; }
	char* GetNapomena() { return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
	}

	// Methods I added below
	Pogodak(const Pogodak& pogodak) 
		: _vrijemePogotka { pogodak.getVrijemePogotka() }
		, _napomena { GetNizKaraktera(pogodak.getNapomena()) }
	{}

	Pogodak& operator=(const Pogodak& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _napomena;

		_vrijemePogotka = rhs.getVrijemePogotka();
		_napomena = GetNizKaraktera(rhs.getNapomena());

		return *this;
	}

	[[nodiscard]] const Vrijeme& getVrijemePogotka() const noexcept { 
		return _vrijemePogotka; 
	}

	[[nodiscard]] const char* getNapomena() const { 
		return _napomena; 
	}

	[[nodiscard]] bool operator==(const Pogodak& rhs) const noexcept {
		return getVrijemePogotka() == rhs.getVrijemePogotka()
			&& std::strcmp(getNapomena(), rhs.getNapomena()) == 0;
	}

	[[nodiscard]] bool operator!=(const Pogodak& rhs) const noexcept {
		return !(*this == rhs);
	}
};

class Igrac {
	static int _id;
	char* _ID; // za inicijalizaciju _ID-a iskoristiti funkciju GenerisiID i vrijednost statickog clana _id
	char* _imePrezime;
	vector<Pogodak> _pogoci;
public:
	Igrac(const char* imePrezime) 
		: _ID { GenerisiID(_id++) }
	{
		_imePrezime = GetNizKaraktera(imePrezime);
	}
	~Igrac() {
		clearResources();
	}
	char* GetImePrezime() { return _imePrezime; }
	char* GetID() { return _ID; }
	vector<Pogodak>& GetPogoci() { return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << *obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			cout << obj._pogoci[i] << endl;
		return COUT;
	}

	// Methods I added below

	Igrac(const Igrac& igrac)
		: _ID { GetNizKaraktera(igrac.getID()) }
		, _imePrezime { GetNizKaraktera(igrac.getImePrezime()) }
		, _pogoci { igrac.getPogoci() }
	{}

	Igrac& operator=(const Igrac& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearResources();

		_ID = GetNizKaraktera(rhs.getID());
		_imePrezime = GetNizKaraktera(rhs.getImePrezime());
		_pogoci = rhs.getPogoci();

		return *this;
	}

	[[nodiscard]] const char* getImePrezime() const noexcept { 
		return _imePrezime; 
	}

	[[nodiscard]] const char* getID() const noexcept { 
		return _ID; 
	}

	[[nodiscard]] const std::vector<Pogodak>& getPogoci() const noexcept { 
		return _pogoci; 
	}

	[[nodiscard]] bool operator==(const Igrac& rhs) const noexcept {
		return std::strcmp(getID(), rhs.getID()) == 0;
	}

	[[nodiscard]] bool operator!=(const Igrac& rhs) const noexcept {
		return !(*this == rhs);
	}

	[[nodiscard]] bool operator==(const std::string& idIliImeIgraca) const noexcept {
		return getID() == idIliImeIgraca || getImePrezime() == idIliImeIgraca;
	}

	[[nodiscard]] bool operator!=(const std::string& idIliImeIgraca) const noexcept {
		return !(*this == idIliImeIgraca);
	}

	[[nodiscard]] bool daLiJePogodakDodan(const Pogodak& pogodakZaPronaci) {
		auto pronadeniPogodak{
			std::find_if(
				std::begin(getPogoci()),
				std::end(getPogoci()),
				[&](const Pogodak& pogodak) {
						return pogodak == pogodakZaPronaci;
				}
			)
		};

		return pronadeniPogodak != std::end(getPogoci());
	}

	void AddPogodak(const Pogodak& pogodak) {
		_pogoci.push_back(pogodak);
	}

	[[nodiscard]] const Pogodak& getZadnjiPogodak() const noexcept {
		return _pogoci.back();
	}

	[[nodiscard]] std::size_t getBrojPogodaka() const noexcept {
		return _pogoci.size();
	}

	[[nodiscard]] bool daLiJePogodakPostignutUIntervalu(
		const Vrijeme& start, 
		const Vrijeme& end
	) const noexcept {
		auto pronadeniPogodak{
			std::find_if(
				std::begin(getPogoci()),
				std::end(getPogoci()),
				[&](const Pogodak& pogodak) {
						return pogodak.getVrijemePogotka() >= start && pogodak.getVrijemePogotka() <= end;
				}
			)
		};

		return pronadeniPogodak != std::end(getPogoci());
	}

private:
	void clearResources() {
		delete[] _ID; _ID = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;
	}
};
int Igrac::_id = 1;

class Reprezentacija {
	Drzava _drzava;
	vector<Igrac> _igraci;
public:
	Reprezentacija(Drzava drzava) {
		_drzava = drzava;
	}
	Drzava GetDrzava() { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }

	// Methods I added below
	Reprezentacija(const Reprezentacija& reprezentacija) = default;

	Reprezentacija& operator=(const Reprezentacija& rhs) {
		if (this == &rhs) {
			return *this;
		}

		_drzava = rhs.getDrzava();
		_igraci = rhs.getIgraci();

		return *this;
	}
	
	[[nodiscard]] Drzava getDrzava() const noexcept { 
		return _drzava; 
	}
	
	[[nodiscard]] const std::vector<Igrac>& getIgraci() const noexcept { 
		return _igraci; 
	}

	[[nodiscard]] bool daLiIgracPostojiUReprezentaciji(const Igrac& igracZaPronaci) const noexcept {
		auto pronadeniIgrac{
			std::find(
				std::begin(getIgraci()),
				std::end(getIgraci()),
				igracZaPronaci
			)
		};

		return pronadeniIgrac != std::end(getIgraci());
	}

	void AddIgrac(const Igrac& igrac) {
		if (daLiIgracPostojiUReprezentaciji(igrac)) {
			throw std::runtime_error("Igrac vec dodan u reprezentaciju");
		}

		_igraci.push_back(igrac);
	}

	[[nodiscard]] bool operator==(const Reprezentacija& rhs) const noexcept {
		return getDrzava() == rhs.getDrzava()
			&& getIgraci() == rhs.getIgraci();
	}

	[[nodiscard]] bool operator!=(const Reprezentacija& rhs) const noexcept {
		return !(*this == rhs);
	}

	[[nodiscard]] std::size_t getBrojPogodaka() const noexcept {
		return std::accumulate(
			std::begin(_igraci),
			std::end(_igraci),
			std::size_t{},
			[](const std::size_t sum, const Igrac& igrac) {
				return sum + igrac.getBrojPogodaka();
			}
		);
	}

	[[nodiscard]] Igrac* getIgracByIDOrName(const std::string& idIliImeIgraca) noexcept {
		auto pronadeniIgrac{
			std::find(
				std::begin(_igraci),
				std::end(_igraci),
				idIliImeIgraca
			)
		};

		if (pronadeniIgrac != std::end(getIgraci())) {
			return &(*pronadeniIgrac);
		}

		return nullptr;
	}

	[[nodiscard]] std::vector<Igrac*> operator()(const Vrijeme& start, const Vrijeme& end) {
		std::vector<Igrac*> temp{};

		for (auto& igrac : _igraci) {
			if (igrac.daLiJePogodakPostignutUIntervalu(start, end)) {
				temp.push_back(&igrac);
			}
		}

		return temp;
	}
};

class Prventstvo {
	Kolekcija<Reprezentacija, Reprezentacija, 20> _utakmice;
public:
	Kolekcija<Reprezentacija, Reprezentacija, 20>& GetUtakmice() {
		return _utakmice;
	}

	// Methods I added below
	Prventstvo() = default;
	Prventstvo(const Prventstvo& prventstvo) = default;
	Prventstvo& operator=(const Prventstvo& rhs) = default;

	[[nodiscard]] const Kolekcija<Reprezentacija, Reprezentacija, 20>& getUtakmice() const noexcept {
		return _utakmice;
	}

	[[nodiscard]] bool daLiSuReprezentacijeVecSusreleSe(
		const Reprezentacija& reprezentacija1ZaPronaci, 
		const Reprezentacija& reprezentacija2ZaPronaci
	) const noexcept {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			const auto& reprezentacija1{ _utakmice.getElement1(i) };
			const auto& reprezentacija2{ _utakmice.getElement2(i) };

			if (reprezentacija1ZaPronaci == reprezentacija1 && reprezentacija2ZaPronaci == reprezentacija2) {
				return true;
			}
			else if (reprezentacija1ZaPronaci == reprezentacija2 && reprezentacija2ZaPronaci == reprezentacija1) {
				return true;
			}
		}

		return false;
	}

	void AddUtakmicu(
		const Reprezentacija& reprezentacija1, 
		const Reprezentacija& reprezentacija2
	) {
		if (daLiSuReprezentacijeVecSusreleSe(reprezentacija1, reprezentacija2)) {
			throw std::runtime_error("Reprezentacije su se vec jednom susrele na ovom prvenstvu");
		}

		_utakmice.AddElement(reprezentacija1, reprezentacija2);
	}

	[[nodiscard]] Reprezentacija* getReprezentacijaForDrzava(Drzava drzava) const noexcept {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			auto& reprezentacija1{ _utakmice.getElement1(i) };
			auto& reprezentacija2{ _utakmice.getElement2(i) };

			if (reprezentacija1.getDrzava() == drzava) {
				return &reprezentacija1;
			}
			else if (reprezentacija2.getDrzava() == drzava) {
				return &reprezentacija2;
			}
		}

		return nullptr;
	}

	[[nodiscard]] Igrac* getIgracByIDOrNameFromReprezentacije(
		const std::string& idIliImeIgraca,
		Reprezentacija& reprezentacija1,
		Reprezentacija& reprezentacija2
	) noexcept {
		auto igrac1 { reprezentacija1.getIgracByIDOrName(idIliImeIgraca) };
		
		if (igrac1) {
			return igrac1;
		}
		
		auto igrac2{ reprezentacija2.getIgracByIDOrName(idIliImeIgraca) };
		return igrac2;
	}

	bool AddPogodak(
		Drzava drzava1, 
		Drzava drzava2, 
		const std::string& idIliImeIgraca, 
		const Pogodak& pogodak
	) {
		auto reprezentacija1{ getReprezentacijaForDrzava(drzava1) };
		auto reprezentacija2{ getReprezentacijaForDrzava(drzava2) };

		if (!reprezentacija1 || !reprezentacija2) {
			return false;
		}

		auto igrac{ 
			getIgracByIDOrNameFromReprezentacije(idIliImeIgraca, *reprezentacija1, *reprezentacija2) 
		};

		if (igrac) {
			if (igrac->daLiJePogodakDodan(pogodak)) {
				return false;
			}

			igrac->AddPogodak(pogodak);
			sendMail(*igrac, *reprezentacija1, *reprezentacija2);
			return true;
		}

		return false;
	}

	[[nodiscard]] static std::string getPlayersWhoScoredGoalsForReprezentacije(
		const Reprezentacija& reprezentacija1,
		const Reprezentacija& reprezentacija2
	) {
		const auto& igraci1{ reprezentacija1.getIgraci() };
		const auto& igraci2{ reprezentacija2.getIgraci() };

		std::string playerNamesSideBySide{};

		for (const auto& igrac : igraci1) {
			for (std::size_t i = 0; i < igrac.getBrojPogodaka(); ++i) {
				playerNamesSideBySide += igrac.getImePrezime();
				playerNamesSideBySide += '\n';
			}
		}

		std::size_t endLinePos{ playerNamesSideBySide.find('\n') };
		for (const auto& igrac : igraci2) {
			for (std::size_t i = 0; i < igrac.getBrojPogodaka(); ++i) {
				if (endLinePos != std::string::npos) {
					playerNamesSideBySide.insert(endLinePos, std::string(" ") + igrac.getImePrezime());
					endLinePos = playerNamesSideBySide.find('\n', endLinePos + 1);
					continue;
				}

				playerNamesSideBySide += igrac.getImePrezime();
				playerNamesSideBySide += '\n';
			}
		}

		// To remove the unnecessary '\n' at the end
		if (!playerNamesSideBySide.empty()) {
			playerNamesSideBySide.pop_back();
		}

		return playerNamesSideBySide;
	}

	friend std::ostream& operator<<(std::ostream& os, const Prventstvo& prventstvo) {
		const auto& utakmice{ prventstvo.getUtakmice() };

		for (int i = 0; i < utakmice.getTrenutno(); ++i) {
			const auto& reprezentacija1{ utakmice.getElement1(i) };
			const auto& reprezentacija2{ utakmice.getElement2(i) };

			os << crt;
			os << reprezentacija1.getDrzava() << ' ' << reprezentacija1.getBrojPogodaka();
			os << " : ";
			os << reprezentacija2.getDrzava() << ' ' << reprezentacija2.getBrojPogodaka();
			os << crt;

			os << Prventstvo::getPlayersWhoScoredGoalsForReprezentacije(reprezentacija1, reprezentacija2);
			os << crt;
		}

		return os;
	}

	[[nodiscard]] std::vector<Igrac*> operator()(const Vrijeme& start, const Vrijeme& end) {
		std::vector<Igrac*> temp{};

		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			auto& reprezentacija1{ _utakmice.getElement1(i) };
			auto& reprezentacija2{ _utakmice.getElement2(i) };

			auto igraciReprezentacije1{ reprezentacija1(start, end) };
			auto igraciReprezentacije2{ reprezentacija2(start, end) };

			temp.insert(
				std::end(temp), 
				std::begin(igraciReprezentacije1), 
				std::end(igraciReprezentacije1)
			);

			temp.insert(
				std::end(temp),
				std::begin(igraciReprezentacije2),
				std::end(igraciReprezentacije2)
			);
		}

		return temp;
	}

private:
	void sendMail(
		const Igrac& igrac,
		const Reprezentacija& reprezentacija1,
		const Reprezentacija& reprezentacija2
	) const {
		std::thread emailThread{
			[&]() {
				// DON'T FORGET TO UNCOMMENT THIS
				// std::this_thread::sleep_for(2s);
				std::cout << "\nTo: " << igrac.getID() << "@euro2024.com\n";
				std::cout << "From: info@euro2024.com\n";
				std::cout << "Subject: Informacija\n";
				std::cout << "Postovani,\n";
				std::cout << "U " << igrac.getZadnjiPogodak().getVrijemePogotka() << " sati igrac " << igrac.getImePrezime();
				std::cout << " je zabiljezio svoj " << igrac.getBrojPogodaka() << '\n';
				std::cout << "pogodak na ovoj utakmici.\n";
				std::cout << "Trenutni rezultat je:\n";
				std::cout << reprezentacija1.getDrzava() << ' ' << reprezentacija1.getBrojPogodaka();
				std::cout << " : ";
				std::cout << reprezentacija2.getDrzava() << ' ' << reprezentacija2.getBrojPogodaka();
				std::cout << "\nPuno srece u nastavku susreta.\n\n";
			}
		};

		emailThread.join();
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite osnovne preduslove koji moraju biti ispunjeni da bi se realizovao polimorfizam(navesti kratki primjer) ? \n";
	return "Odgovor -> Da bi se realizovao polimorfizam potrebna je makar 1 metoda da bude deklarisana sa kljucnom rijeci virtual."
		"Recimo imamo klase Base i Derived, u klasi Base definisemo virtual void Info() {}, u klasi Derived definisemo "
		"void Info() override {} (naravno pored ovog je potrebno deklarisati virtualnim destruktor Base klase)."
		"Sada ako uzmemo Base* base = new Derived {}; i pozovemo base->Info(); imamo mogucnost pristupiti metodi Info"
		" iz najnasljedenije klase. Prednosti nasljedivanja su u tome sto nam dozvoljava da pomocu pokazivaca na baznu "
		" klasu imamo mogucnost da radimo sa svim objektima koji su je naslijedili, to moze dovesti do manje ponavljanja koda"
		"i fleksibilniji rad sa klasama. Takoder ako ta 1 metoda sto je virtual nije destruktor, potrebno ce biti i "
		"destruktor proglasiti virtual.";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite razloge koristenja kljucnih rijeci abstract i ciste virtualne metode, te razlike izmedju njih ? \n";
	return "Odgovor -> Koristenje kljucne rijeci abstract ili ciste virtualne metode dovodi do toga da se ne moze napraviti instanca "
		"te klase, najcesce ona sluzi kao baza u hirarhiji nasljedivanja. Dok su ciste virtualne metode dio standarda za C++, abstract "
		"kljucna rijec nije, uvedena je kao dio VSovog C++-a. Efektivno pruzaju istu uslugu, a to je da se ne moze napraviti instanca "
		"te klase dok se ne naslijedi, ciste virtualne metode bi zahtjevale implementaciju njihovu dok abstract samo zahtjeva nasljedivanje. "
		"Abstract se takoder moze koristiti na metode i klase, dok ciste virtualne metode su iskljucive za metode klase.";
}
void main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	/*
	Globalna funkcija GenerisiID vraca ID igraca (format: ID#00-ID) na
   osnovu int vrijednosti proslijedjene
	kao parametar. Funkcija generise ID sa maksimalno 4 cifre, ne
   racunajuci ostale, podrazumijevane, znakove.
	Podrazumijeva se da ce uvijek biti proslijedjena validna int
   vrijednost.
	*/
	cout << GenerisiID(3) << endl;//treba vratiti ID#000-3
	cout << GenerisiID(14) << endl;//treba vratiti ID#00-14
	cout << GenerisiID(156) << endl;//treba vratiti ID#0-156
	cout << GenerisiID(1798) << endl;//treba vratiti ID#1798

	//Za validaciju ID-a koristiti funkciju ValidirajID koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajID("ID#000-3"))
		cout << "ID VALIDAN" << endl;
	if (ValidirajID("ID#0-156"))
		cout << "ID VALIDAN" << endl;
	if (!ValidirajID("ID#120-3"))
		cout << "ID NIJE VALIDAN" << endl;
	if (!ValidirajID("ID#00-02"))
		cout << "ID NIJE VALIDAN" << endl;
	int kolekcijaTestSize = 9;
	Kolekcija<int, int, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju
	
	cout << kolekcija1 << crt;
	/* metoda InsertAt treba da doda vrijednosti drugog i treceg
   parametra na lokaciju koja je definisana prvim parametrom. Povratna
   vrijednost metode je objekat (pozivaoc metode, u konkretnom slucaju objekat
   kolekcija1) u okviru koga su, na definisanu lokaciju, dodati zahtijevani parametri.
	Nakon izvrsenja metode InsertAt, oba objekta, kolekcija1 i
   kolekcija2, bi trebali posjedovati sljedeci sadrzaj:
	10 10
	0 0
	1 1
	2 2
	* ....
	*/
	Kolekcija<int, int, 10> kolekcija2 = kolekcija1.InsertAt(0, 10, 10);
	cout << kolekcija2 << crt;
	/*Metoda RemoveRange prihvata lokacija OD i DO, te u tom opsegu
   uklanja sve elemente iz kolekcije. U slucaju da zahtijevani opseg ne
   postoji u kolekciji
	metoda treba baciti izuzetak. Na kraju, metoda treba da vrati
   pokazivac na novi objekat tipa kolekcija koji sadrzi samo uklonjene
   elemente*/
	Kolekcija<int, int, 10>* kolekcija3 = kolekcija1.RemoveRange(1, 3);
	cout << *kolekcija3 << endl;
	cout << kolekcija1 << crt;
	/*kolekcija3 bi trebala sadrzavati sljedece elemente:
	0 0
	1 1
	2 2
	dok bi kolekcija1 trebala sadrzavati sljedece elemente:
	10 10
	3 3
	4 4
	......
	*/
	kolekcija1 = *kolekcija3;
	cout << kolekcija1;
	Vrijeme
		prviPogodak201633(20, 16, 33),
		drugiPogodak202319(20, 23, 19),
		treciPogodak205108(20, 51, 8),
		cetvrtiPogodak210654(21, 6, 54);
	Igrac denis("Denis Music"), jasmin("Jasmin Azemovic"),
		goran("Goran Skondric"), adil("Adil Joldic");
	if (strcmp(denis.GetID(), "ID#000-1") == 0 && strcmp(jasmin.GetID(), "ID#000-2") == 0)
		cout << "ID se uspjesno generise!" << endl;
	Pogodak prviPogodak(prviPogodak201633, "podaci o prvom pogotku"),
		drugiPogodak(drugiPogodak202319, "podaci o drugom pogotku"),
		treciPogodak(treciPogodak205108, "podaci o trecem pogotku"),
		cetvrtiPogodak(cetvrtiPogodak210654, "podaci o cetvrtom pogotku");
	Reprezentacija BIH(BOSNA_I_HERCEGOVINA), ENG(ENGLESKA);
	BIH.AddIgrac(denis);
	BIH.AddIgrac(jasmin);
	ENG.AddIgrac(goran);
	ENG.AddIgrac(adil);
	try
	{
		//onemoguciti dodavanje istih igraca - provjeravati ID, baciti izuzetak
		BIH.AddIgrac(denis);
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	Prventstvo euro2024;
	euro2024.AddUtakmicu(BIH, ENG);
	try
	{
		//onemoguciti ponovne susrete drzave tokom istog prvenstva,baciti izuzetak
		euro2024.AddUtakmicu(BIH, ENG);
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	// omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "ID#000-1", prviPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//onemoguciti dodavanje istih pogodaka
	if (!euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Denis Music", prviPogodak))
		cout << "Pogodak NIJE uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "ID#000-2", drugiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Jasmin Azemovic", treciPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Goran Skondric", cetvrtiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;

	//nakon svakog evidentiranog pogotka, svim igracima te utakmice (pod pretpostavkom da su validne email adrese sa ID - ovima igraca),
	//u zasebnom thread-u, poslati email, u razmaku od 2 sekunde, sa sljedecim sadrzajem :
	/*
		To: ID#000-1@euro2024.com
		From: info@euro2024.com
		Subject: Informacija
		Postovani,
		U 20:35:16 sati igrac Jasmin Azemovic je zabiljezio svoj 1
		pogodak na ovoj utakmici.
		Trenutni rezultat je:
		BOSNA_I_HERCEGOVINA 2 : 0 ENGLESKA
		Puno srece u nastavku susreta.
		Neka bolji tim pobijedi.
	*/
	//ispisuje detaljnije informacije o susretu, kako je navedeno unarednom ispisu
		cout << euro2024;
	/*
	-------------------------------------------
	BOSNA_I_HERCEGOVINA 3 : 1 ENGLESKA
	-------------------------------------------
	Denis Music Goran Skondric
	Jasmin Azemovic
	Jasmin Azemovic
	-------------------------------------------
	*/
	//vraca sve igrace koji su na takmicenju postigli pogodak u vremenu koje se nalazi izmedju proslijedjenih vrijednosti
	 vector<Igrac*> igraci = euro2024(Vrijeme(20, 15, 15), Vrijeme(20,24, 15));

	 // Added std::cout below because I spent 30 minutes trying to figure out what was happening
	 // Because I forgor about the last for loop :)
	 std::cout << "\n\nIgraci koji su dali pogodak u intervalu ";
	 std::cout << Vrijeme(20, 15, 15) << " - " << Vrijeme(20, 24, 15) << " nalaze se ispod:\n";
	for (size_t i = 0; i < igraci.size(); i++)
		cout << igraci[i]->GetImePrezime() << endl;

	cin.get();
	system("pause>0");
}