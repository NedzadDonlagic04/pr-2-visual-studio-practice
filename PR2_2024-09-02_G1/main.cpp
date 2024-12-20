#include <iostream>
using namespace std;
const char* PORUKA = "\n------------------------------------------------------------------------------ - \n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI METODA (SVE ISTO VAZI I ZA FUNKCIJE), TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI "
"ONIMA KOJI SU KORISTENI U TESTNOM CODE - U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. "
"OSTALE POMOCNE METODE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U METODAMA U KOJIMA JE TO NAZNACENO.\n"
"6. SVE METODE POZVANE U MAIN-U ZADATKA TREBAJU POSTOJATI. UKOLIKO NISTE ZADOVOLJNI IMPLEMENTACIJOM "
"POTREBNO JE DA IMPLEMENTIRATE BAREM TIJELO TIH METODA (METODA MOZE BITI PRAZNA), "
"A AKO METODA TREBA VRATITI NEKI PODATAK ONDA MOZETE VRATITI BILO KOJU TJ.ZELJENU VRIJEDNOST ZAHTIJEVANOG TIPA.!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRAJTE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA npr.IB150051.docx)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11.ZA POTREBE TESTIRANJA, U MAIN-U, BUDITE SLOBODNI DODATI TESTNIH PODATAKA(POZIVA METODA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12.ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022 I RJESENJE TESTIRAJTE U OBA MODA(F5 i Ctrl + F5)!\n"
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJE�ENJE KOPIRALI U ADEKVATAN FOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";

// Headers I included below
#include<string>
#include<regex>
#include<sstream>
#include<thread>
#include<iomanip>
#include<numeric>
#include<algorithm>
// Headers I included above

enum Drzava {
	ENGLESKA, SPANIJA, HOLANDIJA, FRANCUSKA, BOSNA_I_HERCEGOVINA
};

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

[[nodiscard]] int reverseNum(int num) noexcept {
	int reversedNum{ 0 };

	while (num != 0) {
		reversedNum = reversedNum * 10 + num % 10;
		num /= 10;
	}

	return reversedNum;
}

[[nodiscard]] char* GenerisiID(const std::string& fullName, int num) {
	std::string ID{};
	num = reverseNum(num);

	ID += std::toupper(fullName[0]);
	const std::size_t surnameInitialPos{ fullName.find(' ') + 1 };

	if (num < 10) {
		ID += "000";
	}
	else if (num < 100) {
		ID += "00";
	}
	else if (num < 1000) {
		ID += '0';
	}

	ID += std::toupper(fullName[surnameInitialPos]);
	ID += std::to_string(num);

	return GetNizKaraktera(ID.c_str());
}

[[nodiscard]] bool ValidirajID(const std::string& id) {
	std::regex oneDigitValidation{ "[A-Z]000[A-Z]\\d" };
	std::regex twoDigitValidation{ "[A-Z]00[A-Z]\\d{2}" };
	std::regex threeDigitValidation{ "[A-Z]0[A-Z]\\d{3}" };
	std::regex fourDigitValidation{ "[A-Z][A-Z]\\d{4}" };

	return std::regex_match(id, oneDigitValidation)
		|| std::regex_match(id, twoDigitValidation)
		|| std::regex_match(id, threeDigitValidation)
		|| std::regex_match(id, fourDigitValidation);
}
// Functions I added above

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max]{};
	T2 _elementi2[max]{};
	int* _trenutno;
public:
	~Kolekcija() {
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Kolekcija() {
		_trenutno = new int{ 0 };
	}

	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno{ new int { kolekcija.getTrenutno() } }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = kolekcija.getElement1(i);
			_elementi2[i] = kolekcija.getElement2(i);
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		*_trenutno = rhs.getTrenutno();
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = rhs.getElement1(i);
			_elementi2[i] = rhs.getElement2(i);
		}

		return *this;
	}

	T1 getElement1(int lokacija) const {
		return _elementi1[lokacija];
	}

	T2 getElement2(int lokacija) const {
		return _elementi2[lokacija];
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (getTrenutno() == max) {
			return;
		}

		_elementi1[getTrenutno()] = element1;
		_elementi2[getTrenutno()] = element2;

		++(*_trenutno);
	}

	Kolekcija InsertAt(const T1& element1, const T2& element2, const int index) {
		if (getTrenutno() == max || index < 0 || index > getTrenutno()) {
			return *this;
		}

		for (int i = getTrenutno(); i > index; --i) {
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}

		_elementi1[index] = element1;
		_elementi2[index] = element2;

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
	}

	Kolekcija RemoveRange(const int start, const int end) {
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

		Kolekcija removedElements{};

		for (int i = start; i <= end; ++i) {
			removedElements.AddElement(getElement1(start), getElement2(start));
			RemoveAt(start);
		}

		return removedElements;
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
	Vrijeme* _vrijemePogotka;
	char* _napomena;
public:
	Pogodak(Vrijeme vrijeme, const char* napomena) {
		_napomena = GetNizKaraktera(napomena);
		_vrijemePogotka = new Vrijeme(vrijeme);
	}
	~Pogodak() {
		delete[] _napomena; _napomena = nullptr;
		delete _vrijemePogotka; _vrijemePogotka = nullptr;
	}
	Vrijeme GetVrijemePogotka() { return *_vrijemePogotka; }
	char* GetNapomena() { return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << *obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
	}

	// Methods I added below
	Pogodak(const Pogodak& pogodak)
		: _vrijemePogotka{ new Vrijeme{ pogodak.getVrijemePogotka() } }
		, _napomena{ GetNizKaraktera(pogodak.getNapomena()) }
	{}

	Pogodak& operator=(const Pogodak& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _napomena;

		*_vrijemePogotka = rhs.getVrijemePogotka();
		_napomena = GetNizKaraktera(rhs.getNapomena());

		return *this;
	}

	[[nodiscard]] const Vrijeme& getVrijemePogotka() const noexcept {
		return *_vrijemePogotka;
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
	char* _ID; // za inicijalizaciju _ID-a iskoristiti funkciju GenerisiID tj.atributa _imePrezime(inicijala imena i prezimena) i statickog clana _id
	char* _imePrezime;
	vector<Pogodak*> _pogoci;
public:
	Igrac(const char* imePrezime) 
		: _ID{ GenerisiID(imePrezime, _id++) }
	{
		_imePrezime = GetNizKaraktera(imePrezime);
	}
	~Igrac() {
		clearResources();
	}
	char* GetImePrezime() { return _imePrezime; }
	char* GetID() { return _ID; }
	vector<Pogodak*>& GetPogoci() { return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			COUT << *obj._pogoci[i] << endl;
		return COUT;
	}

	// Methods I added below
	Igrac(const Igrac& igrac)
		: _ID{ GetNizKaraktera(igrac.getID()) }
		, _imePrezime{ GetNizKaraktera(igrac.getImePrezime()) }
		, _pogoci{ igrac.getPogociCopy() }
	{}

	Igrac& operator=(const Igrac& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearResources();

		_ID = GetNizKaraktera(rhs.getID());
		_imePrezime = GetNizKaraktera(rhs.getImePrezime());
		_pogoci = rhs.getPogociCopy();

		return *this;
	}

	[[nodiscard]] const char* getImePrezime() const noexcept {
		return _imePrezime;
	}

	[[nodiscard]] const char* getID() const noexcept {
		return _ID;
	}

	[[nodiscard]] const std::vector<Pogodak*>& getPogoci() const noexcept {
		return _pogoci;
	}

	[[nodiscard]] std::vector<Pogodak*> getPogociCopy() const noexcept {
		std::vector<Pogodak*> temp{};

		for (const auto& pogodak : _pogoci) {
			temp.push_back(new Pogodak(*pogodak));
		}

		return temp;
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
				std::cbegin(getPogoci()),
				std::cend(getPogoci()),
				[&](const Pogodak* const pogodak) {
						return *pogodak == pogodakZaPronaci;
				}
			)
		};

		return pronadeniPogodak != std::cend(getPogoci());
	}

	void AddPogodak(const Pogodak& pogodak) {
		_pogoci.push_back(new Pogodak{ pogodak });
	}

	[[nodiscard]] const Pogodak& getZadnjiPogodak() const noexcept {
		return *_pogoci.back();
	}

	[[nodiscard]] std::size_t getBrojPogodaka() const noexcept {
		return _pogoci.size();
	}

private:
	void clearResources() {
		delete[] _ID; _ID = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;
		for (auto& pogodak : _pogoci) {
			delete pogodak;
			pogodak = nullptr;
		}
	}
};
int Igrac::_id = 1;

class Reprezentacija {
	Drzava _drzava;
	vector<Igrac> _igraci;
public:
	Reprezentacija(Drzava drzava = BOSNA_I_HERCEGOVINA) {
		_drzava = drzava;
	}
	Drzava GetDrzava() { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }

	// Methods I added below
	Reprezentacija(const Reprezentacija& reprezentacija) = default;
	~Reprezentacija() = default;

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
				std::cbegin(getIgraci()),
				std::cend(getIgraci()),
				igracZaPronaci
			)
		};

		return pronadeniIgrac != std::cend(getIgraci());
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
			std::cbegin(_igraci),
			std::cend(_igraci),
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

	[[nodiscard]] std::vector<Igrac*> operator()(const std::size_t brojPogodaka) {
		std::vector<Igrac*> temp{};

		for (auto& igrac : _igraci) {
			if (igrac.getBrojPogodaka() >= brojPogodaka) {
				temp.push_back(&igrac);
			}
		}

		return temp;
	}

	[[nodiscard]] std::vector<std::reference_wrapper<const Igrac>> getIgraciThatScores() const {
		std::vector<std::reference_wrapper<const Igrac>> igraci{};

		for (auto& igrac : _igraci) {
			for (std::size_t i = 0; i < igrac.getBrojPogodaka(); ++i) {
				igraci.push_back(igrac);
			}
		}

		return igraci;
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
	~Prventstvo() = default;

	[[nodiscard]] const Kolekcija<Reprezentacija, Reprezentacija, 20>& getUtakmice() const noexcept {
		return _utakmice;
	}

	[[nodiscard]] bool daLiSuReprezentacijeVecSusreleSe(
		const Reprezentacija& reprezentacija1ZaPronaci,
		const Reprezentacija& reprezentacija2ZaPronaci
	) const noexcept {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			const Reprezentacija& reprezentacija1{ _utakmice.getElement1(i) };
			const Reprezentacija& reprezentacija2{ _utakmice.getElement2(i) };

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
		else if (reprezentacija1.getDrzava() == reprezentacija2.getDrzava()) {
			// No point in setting a match if the countries are the same
			return;
		}

		_utakmice.AddElement(reprezentacija1, reprezentacija2);
	}

	[[nodiscard]] Reprezentacija* getReprezentacijaForDrzava(Drzava drzava) noexcept {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			Reprezentacija& reprezentacija1{ _utakmice.getElement1(i) };
			Reprezentacija& reprezentacija2{ _utakmice.getElement2(i) };

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
		Igrac* igrac1{ reprezentacija1.getIgracByIDOrName(idIliImeIgraca) };

		if (igrac1) {
			return igrac1;
		}

		Igrac* igrac2{ reprezentacija2.getIgracByIDOrName(idIliImeIgraca) };
		return igrac2;
	}

	bool AddPogodak(
		Drzava drzava1,
		Drzava drzava2,
		const std::string& idIliImeIgraca,
		const Pogodak& pogodak
	) {
		Reprezentacija* reprezentacija1{ getReprezentacijaForDrzava(drzava1) };
		Reprezentacija* reprezentacija2{ getReprezentacijaForDrzava(drzava2) };

		if (!reprezentacija1 || !reprezentacija2) {
			return false;
		}
		else if (!daLiSuReprezentacijeVecSusreleSe(*reprezentacija1, *reprezentacija2)) {
			return false;
		}

		Igrac* igrac{
			getIgracByIDOrNameFromReprezentacije(idIliImeIgraca, *reprezentacija1, *reprezentacija2)
		};

		if (!igrac || igrac->daLiJePogodakDodan(pogodak)) {
			return false;
		}

		igrac->AddPogodak(pogodak);
		sendMail(*igrac, *reprezentacija1, *reprezentacija2);
		return true;
	}

	[[nodiscard]] static std::string getPlayersWhoScoredGoalsSideBySide(
		const std::vector<std::reference_wrapper<const Igrac>>& igraci1,
		const std::vector<std::reference_wrapper<const Igrac>>& igraci2
	) {
		std::string playerNamesSideBySide{};

		auto igrac1It{ std::cbegin(igraci1) };
		auto igrac2It{ std::cbegin(igraci2) };
		bool anyIgraci1Left{ igrac1It != std::cend(igraci1) };
		bool anyIgraci2Left{ igrac2It != std::cend(igraci2) };

		while (anyIgraci1Left || anyIgraci2Left) {
			if (anyIgraci1Left) {
				playerNamesSideBySide += igrac1It->get().getImePrezime();
				++igrac1It;
			}

			if (anyIgraci2Left) {
				playerNamesSideBySide += ((anyIgraci1Left) ? "\t" : "\t\t");
				playerNamesSideBySide += igrac2It->get().getImePrezime();
				++igrac2It;
			}

			playerNamesSideBySide += '\n';

			anyIgraci1Left = igrac1It != std::cend(igraci1);
			anyIgraci2Left = igrac2It != std::cend(igraci2);
		}


		if (!playerNamesSideBySide.empty()) {
			playerNamesSideBySide.pop_back();
		}

		return playerNamesSideBySide;
	}

	friend std::ostream& operator<<(std::ostream& os, const Prventstvo& prventstvo) {
		const auto& utakmice{ prventstvo.getUtakmice() };

		for (int i = 0; i < utakmice.getTrenutno(); ++i) {
			const Reprezentacija& reprezentacija1{ utakmice.getElement1(i) };
			const Reprezentacija& reprezentacija2{ utakmice.getElement2(i) };

			os << crt;
			os << '(' << reprezentacija1.getBrojPogodaka() << ") " << reprezentacija1.getDrzava();
			os << " : ";
			os << reprezentacija2.getDrzava() << " (" << reprezentacija2.getBrojPogodaka() << ')';
			os << crt;

			os << Prventstvo::getPlayersWhoScoredGoalsSideBySide(reprezentacija1.getIgraciThatScores(), reprezentacija2.getIgraciThatScores());
			os << crt;
		}

		return os;
	}

	[[nodiscard]] std::vector<Igrac*> operator()(const std::size_t brojPogodaka) {
		std::vector<Igrac*> temp{};

		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			Reprezentacija& reprezentacija1{ _utakmice.getElement1(i) };
			Reprezentacija& reprezentacija2{ _utakmice.getElement2(i) };

			auto igraciReprezentacije1{ reprezentacija1(brojPogodaka) };
			auto igraciReprezentacije2{ reprezentacija2(brojPogodaka) };

			temp.insert(
				std::cend(temp),
				std::cbegin(igraciReprezentacije1),
				std::cend(igraciReprezentacije1)
			);

			temp.insert(
				std::cend(temp),
				std::cbegin(igraciReprezentacije2),
				std::cend(igraciReprezentacije2)
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
				// DON'T FORGET TO UNCOMMENT THIS LINE BELOW
				std::this_thread::sleep_for(2s);
				std::cout << "\nTo: " << igrac.getID() << "@euro2024.com\n";
				std::cout << "From: info@euro2024.com\n";
				std::cout << "Subject: Informacija\n";
				std::cout << "Postovani,\n";
				std::cout << "U " << igrac.getZadnjiPogodak().getVrijemePogotka() << " sati igrac " << igrac.getImePrezime();
				std::cout << " je zabiljezio svoj " << igrac.getBrojPogodaka() << '\n';
				std::cout << "pogodak na ovoj utakmici.\n";
				std::cout << "Trenutni rezultat je:\n";
				std::cout << '(' << reprezentacija1.getBrojPogodaka() << ") " << reprezentacija1.getDrzava();
				std::cout << " : ";
				std::cout << reprezentacija2.getDrzava() << " (" << reprezentacija2.getBrojPogodaka() << ')';
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
	Globalna funkcija GenerisiID vraca ID igraca na osnovu vrijednosti
   proslijedjenih parametara. Funkcija generise
	ID sa maksimalno 4 cifre, ne racunajuci inicijale tj. prva slova
   imena i prezimena.
	Podrazumijeva se da ce uvijek biti proslijedjene validne
   vrijednosti parametara. Ukoliko se proslijede
	mala pocetna slova imena ili prezimena, potrebno ih je
   konvertovati u velika.
	U okviru generisanog ID-a, proslijedjena cjelobrojna vrijednost
   treba biti u obrnutom redoslijedu cifara.
	*/
	cout << GenerisiID("Denis Music", 3) << endl;//treba vratiti D000M3
	cout << GenerisiID("Jasmin Azemovic", 14) << endl;//treba vratiti J00A41
	cout << GenerisiID("Goran Skondric", 156) << endl;//treba vratiti G0S651
	cout << GenerisiID("emina junuz", 1798) << endl;//treba vratiti EJ8971

	//Za validaciju ID-a koristiti funkciju ValidirajID koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajID("D000M3"))
		cout << "ID VALIDAN" << endl;
	if (ValidirajID("J00A41"))
		cout << "ID VALIDAN" << endl;
	if (!ValidirajID("G00S651"))
		cout << "ID NIJE VALIDAN" << endl;
	if (!ValidirajID("Ej8971"))
		cout << "ID NIJE VALIDAN" << endl;
	int kolekcijaTestSize = 9;
	Kolekcija<int, int, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju
	cout << kolekcija1 << crt;
	/* metoda InsertAt treba da doda vrijednosti prvog i drugog
   parametra na lokaciju koja je definisana trecim parametrom. Povratna
   vrijednost metode je objekat (pozivaoc metode, u konkretnom slucaju objekat
   kolekcija1) u okviru koga su, na definisanu lokaciju, dodati
   zahtijevani parametri.
	Nakon izvrsenja metode InsertAt, oba objekta, kolekcija1 i
   kolekcija2, bi trebali posjedovati sljedeci sadrzaj:
	10 10
	0 0
	1 1
	2 2
	* ....
	*/
	Kolekcija<int, int, 10> kolekcija2 = kolekcija1.InsertAt(10, 10, 0);
	cout << kolekcija2 << crt;
	/*Metoda RemoveRange prihvata lokacija OD i DO, te u tom opsegu
   uklanja sve elemente iz kolekcije. U slucaju da zahtijevani opseg ne
   postoji u kolekciji metoda treba baciti izuzetak. Na kraju, metoda treba da vrati
   pokazivac na novi objekat tipa kolekcija koji sadrzi samo uklonjene
   elemente*/

	// A bit of a correction here
	// Komentar iznad trazi da se vrati pokazivac, medutim to je izgleda ostalo od
	// veoma slicnog roka

	Kolekcija<int, int, 10> kolekcija3 = kolekcija1.RemoveRange(1, 3);
	cout << kolekcija3 << endl;
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
	kolekcija1 = kolekcija3;
	cout << kolekcija1;
	Vrijeme
		prviPogodak201633(20, 16, 33),
		drugiPogodak202319(20, 23, 19),
		treciPogodak205108(20, 51, 8),
		cetvrtiPogodak210654(21, 6, 54);
	Igrac denis("Denis Music"), jasmin("Jasmin Azemovic"),
		goran("Goran Skondric"), adil("Adil Joldic");

	if (strcmp(denis.GetID(), "D000M1") == 0 && strcmp(jasmin.GetID(), "J000A2") == 0)
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
		BIH.AddIgrac(denis);//onemoguciti dodavanje istih igraca - provjeravati ID
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}

	//// To see output if sides were reversed comment the chunk above
	//// and uncomment chunk below
	//ENG.AddIgrac(denis);
	//ENG.AddIgrac(jasmin);
	//BIH.AddIgrac(goran);
	//BIH.AddIgrac(adil);
	//try
	//{
	//	//onemoguciti dodavanje istih igraca - provjeravati ID, baciti izuzetak
	//	ENG.AddIgrac(denis);
	//}
	//catch (exception& obj)
	//{
	//	cout << obj.what() << '\n';
	//}
	Prventstvo euro2024;
	euro2024.AddUtakmicu(BIH, ENG);
	try
	{
		euro2024.AddUtakmicu(BIH, ENG);//onemoguciti ponovne susrete drzava tokom istog prvenstva
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	//omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "D000M1", prviPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//onemoguciti dodavanje istih pogodaka
	if (!euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Denis Music", prviPogodak))
		cout << "Pogodak NIJE uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "J000A2", drugiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Jasmin Azemovic", treciPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Goran Skondric", cetvrtiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//nakon svakog evidentiranog pogotka, svim igracima te utakmice (pod pretpostavkom da su validne email adrese sa ID - ovima igraca),
	//u zasebnom thread-u, poslati email. u razmaku od 2 sekunde, sa sljedecim sadrzajem :
	/*
	To: D000M1@euro2024.com
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
	//ispisuje detaljnije informacije o susretu, kako je navedeno u narednom ispisu
	cout << euro2024;
	/*
	-------------------------------------------
	(3) BOSNA_I_HERCEGOVINA : ENGLESKA (1)
	-------------------------------------------
	Denis Music Goran Skondric
	Jasmin Azemovic
	Jasmin Azemovic
	-------------------------------------------
	*/
	//vraca sve igrace koji su na takmicenju postigli broj pogodaka koji je veci ili jednak proslijedjenoj vrijednosti
	vector<Igrac*> igraci = euro2024(2);
	for (size_t i = 0; i < igraci.size(); i++)
		cout << igraci[i]->GetImePrezime() << endl;
	cin.get();
	system("pause>0");
}