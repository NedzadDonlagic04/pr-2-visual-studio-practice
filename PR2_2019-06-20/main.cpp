#include<iostream>
using namespace std;

// Headers I included below
#include<memory>
#include<string>
#include<vector>
#include<fstream>
#include<regex>
#include<iomanip>
#include<utility>
#include<thread>
#include<functional>
// Headers I included above

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";

enum Sortiranje { ASC, DESC };
enum Predmet { MATEMATIKA, FIZIKA, HEMIJA, GEOGRAFIJA, NOT_SET };
enum Razred { I = 1, II, III, IV };

// Functions I defined below
	/*
	koristeci regex, osigurati sljedeci format za broj telefona: +387(6X)XXX-XXX ili +387 6X XXX-XXX
	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
	*/
[[nodiscard]] bool ValidirajBrojTelefona(const std::string& phoneNum) {
	std::regex phoneNumValidation{ "^\\+387[\\(\\s]6\\d[\\)\\s]\\d{3}-\\d{3}$" };

	return std::regex_search(phoneNum, phoneNumValidation);
}

std::ostream& operator<<(std::ostream& os, const Razred& razred) {
	switch (razred) {
	case Razred::I:
		os << "I";
		break;
	case Razred::II:
		os << "II";
		break;
	case Razred::III:
		os << "III";
		break;
	case Razred::IV:
		os << "IV";
		break;
	default:
		os << "Razred ne postoji";
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const Predmet& predmet) {
	switch (predmet) {
	case Predmet::MATEMATIKA:
		os << "MATEMATIKA";
		break;
	case Predmet::FIZIKA:
		os << "FIZIKA";
		break;
	case Predmet::HEMIJA:
		os << "HEMIJA";
		break;
	case Predmet::GEOGRAFIJA:
		os << "GEOGRAFIJA";
		break;
	case Predmet::NOT_SET:
		os << "NOT_SET";
		break;
	default:
		os << "Predmet ne postoji";
	}

	return os;
}
// Functions I defined above

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
template <class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int _trenutnoElemenata;
	bool _dozvoliDupliranje;
	Sortiranje _sortiranje;
public:
	Kolekcija(Sortiranje sortiranje = ASC, bool dozvoliDupliranje = true) {
		_trenutnoElemenata = 0;
		_sortiranje = sortiranje;
		_dozvoliDupliranje = dozvoliDupliranje;
	}
	~Kolekcija() {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
	int GetTrenutno() const { return _trenutnoElemenata; }
	int GetMax() const { return max; }

	T1& GetElement1(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi1[lokacija];
	}
	T2& GetElement2(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi2[lokacija];
	}
	void SetElement2(int lokacija, T2 ele2) {
		*_elementi2[lokacija] = ele2;
	}
	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Kolekcija(const Kolekcija& kolekcija)
		: _trenutnoElemenata{ kolekcija.GetTrenutno() }
		, _dozvoliDupliranje{ kolekcija._dozvoliDupliranje }
		, _sortiranje{ kolekcija._sortiranje }
	{
		for (int i = 0; i < GetTrenutno(); ++i) {
			_elementi1[i] = new T1{ kolekcija.GetElement1(i) };
			_elementi2[i] = new T2{ kolekcija.GetElement2(i) };
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		if (this == &rhs) {
			return *this;
		}

		for (int i = 0; i < GetTrenutno(); ++i) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}

		_trenutnoElemenata = rhs.GetTrenutno();
		_sortiranje = rhs._sortiranje;
		_dozvoliDupliranje = rhs._dozvoliDupliranje;

		for (int i = 0; i < GetTrenutno(); ++i) {
			_elementi1[i] = new T1{ rhs.GetElement1(i) };
			_elementi2[i] = new T2{ rhs.GetElement2(i) };
		}

		return *this;
	}

	[[nodiscard]] bool daLiElementPostoji(const T1& element1, const T2& element2) const noexcept {
		for (int i = 0; i < GetTrenutno(); ++i) {
			if (element1 == GetElement1(i) && element2 == GetElement2(i)) {
				return true;
			}
		}

		return false;
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (!_dozvoliDupliranje && daLiElementPostoji(element1, element2)) {
			throw std::runtime_error("Dupliranje nije dozvoljeno");
		}

		_elementi1[GetTrenutno()] = new T1{ element1 };
		_elementi2[GetTrenutno()] = new T2{ element2 };

		++_trenutnoElemenata;
		
		sortirajPoT1();
	}

	void sortirajPoT1() noexcept {
		auto swapFunction{ getSwapFunction() };

		bool continueSorting{};
		int size{ GetTrenutno() };

		do {
			continueSorting = false;

			for (int i = 0; i < size - 1; ++i) {
				continueSorting = swapFunction(i, i + 1);
			}

			--size;
		} while (continueSorting);
	}

private:
	[[nodiscard]] std::function<bool(const int, const int)> getSwapFunction() const {
		std::function<bool(const int, const int)> swapAsc{
			[&](const int index1, const int index2) {
				auto& el1 { GetElement1(index1) };
				auto& el2 { GetElement1(index2) };

				if (el1 > el2) {
					std::swap(el1, el2);
					std::swap(GetElement2(index1), GetElement2(index2));
					return true;
				}
				return false;
			}
		};

		std::function<bool(const int, const int)> swapDesc{
			[&](const int index1, const int index2) {
				auto& el1 { GetElement1(index1) };
				auto& el2 { GetElement1(index2) };

				if (el1 < el2) {
					std::swap(el1, el2);
					std::swap(GetElement2(index1), GetElement2(index2));
					return true;
				}
				return false;
			}
		};

		return (_sortiranje == Sortiranje::ASC) ? swapAsc : swapDesc;
	}
};

class Aktivnost {
	shared_ptr<Razred> _razred;
	string _opis;
	int _ocjena;//1-5
public:
	Aktivnost(Razred razred = I, int ocjena = 0, string opis = not_set) {
		_ocjena = ocjena;
		_opis = opis;
		_razred = make_shared<Razred>(razred);
	}
	int  GetOcjenu() const { return _ocjena; }
	string GetOpis() const { return _opis; }
	Razred GetRazred() const { return *_razred; }

	friend ostream& operator<<(ostream& COUT, const Aktivnost& obj) {
		COUT << *obj._razred << " " << obj._ocjena << " " << obj._opis << endl;
		return COUT;
	}

	// Methods I added below
	Aktivnost(const Aktivnost& aktivnost)
		: _razred { std::make_shared<Razred>(aktivnost.getRazred()) }
		, _ocjena { aktivnost.getOcjenu() }
		, _opis { aktivnost.getOpis() }
	{}

	Aktivnost& operator=(const Aktivnost& rhs) {
		_razred = std::make_shared<Razred>(rhs.getRazred());
		_ocjena = rhs.getOcjenu();
		_opis = rhs.getOpis();

		return *this;
	}

	[[nodiscard]] static bool daLiJeOcjenaValidna(const int ocjena) noexcept {
		return ocjena >= 1 && ocjena <= 5;
	}

	[[nodiscard]] int getOcjenu() const noexcept { 
		return _ocjena; 
	}

	[[nodiscard]] const std::string getOpis() const noexcept { 
		return _opis; 
	}

	[[nodiscard]] const Razred& getRazred() const noexcept { 
		return *_razred; 
	}

	[[nodiscard]] bool operator==(const Aktivnost& rhs) const noexcept {
		return getOcjenu() == rhs.getOcjenu()
			&& getOpis() == rhs.getOpis()
			&& getRazred() == rhs.getRazred();
	}

	[[nodiscard]] bool operator!=(const Aktivnost& rhs) const noexcept {
		return !(*this == rhs);
	}
};

class Polaznik {
protected:
	char* _imePrezime;
	string _brojTelefona;
public:
	Polaznik(string imePrezime, string brojTelefona) : _imePrezime(AlocirajNizKaraktera(imePrezime.c_str())) {
		_brojTelefona = (ValidirajBrojTelefona(brojTelefona))? brojTelefona : not_set;
	}
	~Polaznik() { delete[] _imePrezime; }
	char* GetImePrezime() { return _imePrezime; }
	string GetTelefon() { return _brojTelefona; }
	virtual void PredstaviSe() = 0;

	// Methods I added below
	Polaznik(const Polaznik& polaznik)
		: _imePrezime { AlocirajNizKaraktera(polaznik.getImePrezime()) }
		, _brojTelefona { polaznik.getTelefon() }
	{}

	Polaznik& operator=(const Polaznik& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _imePrezime;

		_imePrezime = AlocirajNizKaraktera(rhs.getImePrezime());
		_brojTelefona = rhs.getTelefon();

		return *this;
	}
	
	[[nodiscard]] const char* getImePrezime() const noexcept { 
		return _imePrezime; 
	}

	[[nodiscard]] const std::string& getTelefon() const noexcept { 
		return _brojTelefona; 
	}

	friend std::ostream& operator<<(std::ostream& os, const Polaznik& polaznik) {
		os << "Ime prezime: " << std::quoted(polaznik.getImePrezime()) << '\n';
		os << "Broj telefona: " << std::quoted(polaznik.getTelefon());

		return os;
	}

};

class Ucenik : public Polaznik {
	Kolekcija<Predmet, Aktivnost, 16>* _aktivnosti;
public:
	~Ucenik() { delete _aktivnosti; _aktivnosti = nullptr; }
	Kolekcija<Predmet, Aktivnost, 16>& GetAktivnosti() { return *_aktivnosti; };
	friend ostream& operator<<(ostream& COUT, const Ucenik& n)
	{
		COUT << static_cast<const Polaznik&>(n) << '\n';
		COUT << "Predmet - aktivnost:\n";

		const auto& aktivnost{ n.getAktivnosti() };
		for (int i = 0; i < aktivnost.GetTrenutno(); ++i) {
			COUT << aktivnost.GetElement1(i) << " - ";
			COUT << aktivnost.GetElement2(i);

			if (i + 1 != aktivnost.GetTrenutno()) {
				COUT << '\n';
			}
		}

		return COUT;
	}

	// Methods I added below
	Ucenik(string imePrezime, string brojTelefona)
		: Polaznik(imePrezime, brojTelefona)
		, _aktivnosti { new Kolekcija<Predmet, Aktivnost, 16> }
	{}

	Ucenik(const Ucenik& ucenik)
		: Polaznik(ucenik)
		, _aktivnosti{ new Kolekcija<Predmet, Aktivnost, 16>{ ucenik.getAktivnosti() } }
	{}

	Ucenik& operator=(const Ucenik& rhs) {
		if (this == &rhs) {
			return *this;
		}
		
		Polaznik::operator=(rhs);

		delete _aktivnosti;
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>{ rhs.getAktivnosti() };

		return *this;
	}

	[[nodiscard]] const Kolekcija<Predmet, Aktivnost, 16>& getAktivnosti() const noexcept {
		return *_aktivnosti; 
	}

	void PredstaviSe() override {
		std::cout << *this;
	}

	[[nodiscard]] int getBrojAktivnostiZaRazred(const Razred& razred) const noexcept {
		int counter{ 0 };

		for (int i = 0; i < _aktivnosti->GetTrenutno(); ++i) {
			if (_aktivnosti->GetElement2(i).getRazred() == razred) {
				++counter;
			}
		}

		return counter;
	}

	[[nodiscard]] bool daLiJeUslovZaDodavanjeAktivnostiIspunjen(
		const Predmet& predmet, 
		const Aktivnost& aktivnost
	) const noexcept {
		const auto& trenutniRazred{ aktivnost.getRazred() };
		const int brojAktivnost{ getBrojAktivnostiZaRazred(trenutniRazred) };

		if (brojAktivnost == 4) {
			return false;
		}

		for (int i = 0; i < _aktivnosti->GetTrenutno(); ++i) {
			const auto& trenutniPredmet{ _aktivnosti->GetElement1(i) };
			const auto& trenutnaAktivnost{ _aktivnosti->GetElement2(i) };

			if (trenutnaAktivnost == aktivnost && trenutniPredmet == predmet) {
				return false;
			}
		}

		return true;
	}

	bool dodajAktivnost(const Predmet& predmet, const Aktivnost& aktivnost) {
		if (!daLiJeUslovZaDodavanjeAktivnostiIspunjen(predmet, aktivnost)) {
			return false;
		}

		_aktivnosti->AddElement(predmet, aktivnost);
		return true;
	}

	[[nodiscard]] double getAverage() const noexcept {
		const int size{ _aktivnosti->GetTrenutno() };

		if (!size) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (int i = 0; i < size; ++i) {
			sum += _aktivnosti->GetElement2(i).getOcjenu();
		}

		return sum / size;
	}
};

class Skola {
	char* _naziv;
	vector<Ucenik> _ucenici;
public:
	Skola(const char* naziv = nullptr) {
		_naziv = AlocirajNizKaraktera(naziv);
	}
	~Skola() {
		delete[] _naziv; _naziv = nullptr;
	}
	char* GetNaziv()const { return _naziv; }
	vector<Ucenik>& GetUcenici() { return _ucenici; };

	friend ostream& operator<<(ostream& COUT, Skola& obj) {
		COUT << "Skola: " << obj._naziv << endl;
		COUT << "Ucenici: " << endl;
		for (size_t i = 0; i < obj._ucenici.size(); i++)
			COUT << obj._ucenici[i] << endl;
		return COUT;
	}

	// Methods I added below
	Skola(const Skola& skola)
		: _naziv { AlocirajNizKaraktera(skola.getNaziv()) }
		, _ucenici { skola.getUcenici() }
	{}

	Skola& operator=(const Skola& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _naziv;

		_naziv = AlocirajNizKaraktera(rhs.getNaziv());
		_ucenici = rhs.getUcenici();

		return *this;
	}

	[[nodiscard]] const char* getNaziv() const noexcept { 
		return _naziv; 
	}

	[[nodiscard]] const std::vector<Ucenik>& getUcenici() const noexcept { 
		return _ucenici; 
	}

	[[nodiscard]] bool daLiUcenikSaIstimImenomIliBrojemPostoji(
		const std::string& imePrezime, 
		const std::string& brojTelefona
	) const noexcept {
		auto ucenikZaPronaci{
			std::find_if(
				std::cbegin(_ucenici),
				std::cend(_ucenici),
				[&](const Ucenik& ucenik) {
					return ucenik.getImePrezime() == imePrezime || ucenik.getTelefon() == brojTelefona;
				}
			)
		};

		return ucenikZaPronaci != std::cend(_ucenici);
	}

	void operator()(const std::string& imePrezime, const std::string& brojTelefona) {
		if (daLiUcenikSaIstimImenomIliBrojemPostoji(imePrezime, brojTelefona)) {
			throw std::runtime_error("Ucenik sa imenom i prezimenom ili brojem telefona vec postoji");
		}

		_ucenici.push_back(Ucenik{ imePrezime, brojTelefona });
	}

	[[nodiscard]] Ucenik* getUcenikZaIme(const std::string& imePrezime) noexcept {
		auto ucenikZaPronaci{
			std::find_if(
				std::begin(_ucenici),
				std::end(_ucenici),
				[&](const Ucenik& ucenik) {
					return ucenik.getImePrezime() == imePrezime;
				}
			)
		};

		return (ucenikZaPronaci != std::end(_ucenici))? &(*ucenikZaPronaci) : nullptr;
	}

	bool DodajAktivnost(const std::string& imePrezime, const Predmet& predmet, const Aktivnost& aktivnost) {
		auto postojeciUcenik{ getUcenikZaIme(imePrezime) };

		if (!postojeciUcenik) {
			return false;
		}

		return postojeciUcenik->dodajAktivnost(predmet, aktivnost);
	}

	[[nodiscard]] std::pair<Polaznik*, float> GetNajboljegUcenika() noexcept {
		const auto& size{ _ucenici.size() };

		if (!size) {
			return std::make_pair(nullptr, 0.0f);
		}

		auto najboljiPolaznik{ &_ucenici[0] };

		for (std::size_t i = 1; i < size; ++i) {
			if (_ucenici[i].getAverage() > najboljiPolaznik->getAverage()) {
				najboljiPolaznik = &_ucenici[i];
			}
		}

		return std::make_pair(najboljiPolaznik, najboljiPolaznik->getAverage());
	}

	bool SpasiUFajl(const std::string& fileName, const bool deletePreviousFileContent = false) const {
		const std::string fullPath{ "./ " + fileName };

		const auto fileMode { 
			std::ios::out | 
			std::ios::in  | 
			((deletePreviousFileContent) ? std::ios::trunc : 0) 
		};

		std::fstream file{ fullPath, fileMode };

		if (!file.is_open()) {
			return false;
		}

		writeUceniciIntoFile(file);
		printUceniciFromFile(file);

		return true;
	}
private:
	void writeUceniciIntoFile(std::fstream& file) const {
		for (const auto& ucenik : _ucenici) {
			file << ucenik << '\n';
		}
	}

	void printUceniciFromFile(std::fstream& file) const {
		file.seekg(0);

		std::string line{};

		while (std::getline(file, line)) {
			std::cout << line << '\n';
		}
	}
};

int main() {
	Kolekcija<int, int, 10> kolekcija1(DESC, false);
	try {
		kolekcija1.AddElement(1, 2);
		//dupliranje elemenata nije dozvoljeno
		kolekcija1.AddElement(1, 2);
	}
	catch (exception& ex) {
		cout << ex.what();
	}

	/*nakon svakog dodavanja, elemente sortirati prema T1 i vrijednosti atributa _sortiranje*/
	for (size_t i = 1; i < kolekcija1.GetMax() - 1; i++)
		kolekcija1.AddElement(rand(), rand());

	cout << kolekcija1 << endl;

	try {
		//prekoracen maksimalan broj elemenata
		kolekcija1.AddElement(rand(), rand());
	}
	catch (exception& ex) {
		cout << ex.what();
	}
	cout << kolekcija1 << endl;

	Kolekcija<int, int, 10> kolekcija2(kolekcija1);
	cout << kolekcija2 << endl;

	Skola gimnazijaMostar("GIMNAZIJA MOSTAR");
	//dodaje novog ucenika u skolu
	gimnazijaMostar("Jasmin Azemovic", "+387(61)111-222");
	gimnazijaMostar("Adel Handzic", "+387(61)333-444");

	/*
	koristeci regex, osigurati sljedeci format za broj telefona: +387(6X)XXX-XXX ili +387 6X XXX-XXX
	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
	*/
	gimnazijaMostar("Telefon NotValidFormat", "387 61)333-444");

	try
	{
		/*onemoguciti dodavanje ucenika sa istim imenom i prezimenom ili brojem telefona*/
		gimnazijaMostar("Adel Handzic", "+387(61)333-444");
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}

	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Priprema za takmicenje iz Matematije koje se odrzava u Konjicu 07.02.2019")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*na nivou svakog razreda se mogu evidentirati maksimalno 4 aktivnosti, a takodjer, na nivou razreda se ne smiju ponavljati aktivnosti iz istog predmeta*/
	if (!gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Aktivnosti iz matematike")))
		cout << "Aktivnost nije uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", HEMIJA, Aktivnost(I, 5, "Priprema otopina za vjezbe iz predmeta Hemija")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", FIZIKA, Aktivnost(I, 4, "Analiza stepena apsorpcije materijala ")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*u slucaju da je ucenik uspjesno (ocjenom vecom od 1) realizovao aktivnosti na nivou odredjenog razreda, te posjeduje validan broj telefona,
	u okviru zasebnog thread-a se salje SMS sa sadrzajem "Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X"*/
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", GEOGRAFIJA, Aktivnost(I, 4, "Izrada 5 reljefa Mostara")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Adel Handzic", MATEMATIKA, Aktivnost(I, 5, "Izrada skripte na temu integralni racun")))
		cout << "Aktivnost uspjesno dodana" << endl;

	//ispisuje sve ucenike i njihove aktivnosti
	cout << gimnazijaMostar << endl;


	pair<Polaznik*, float> par = gimnazijaMostar.GetNajboljegUcenika();
	cout << "Najbolji ucenik je " << par.first->GetImePrezime() << " sa prosjekom " << par.second << endl;

	/*U fajl (npr. Gimnazija.txt) upisati podatke (podatke upisati kao obicni tekst) o skoli i svim ucenicima.
	Nakon upisa, potrebno je ispisati sadrzaj fajla. Parametar tipa bool oznacava da li ce ranije dodani sadrzaj fajla prethodno biti pobrisan*/

	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt"))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;
	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt", true))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;

	cin.get();
	system("pause>0");
	return 0;
}