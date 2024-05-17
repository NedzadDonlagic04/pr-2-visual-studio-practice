// Headers I included below
#include<iostream>
#include<vector>
#include<array>
#include<numeric>
#include<string>
#include<regex>
#include<thread>
#include<functional>
#include<iomanip>
// Headers I included above
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
enum SortirajPo { T1, T2 };

// Constants I defined below
const std::string notSetEmail{ "notSet@edu.fit.ba" };
// Constants I defined above

// Functions I defined below
[[nodiscard]] int countStrInStr(const std::string& toFind, const std::string& src) {
	std::regex strToFindRegex{ toFind };

	std::sregex_iterator start{ src.begin(), src.end(), strToFindRegex };
	std::sregex_iterator end{};

	return std::distance(start, end);
}
	/*
	email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	za provjeru koristiti regex
	*/
[[nodiscard]] bool validateEmail(const std::string& email) {
	std::regex emailValidation{ "^[a-zA-Z]+@(outlook.com|edu.fit.ba)$" };

	return std::regex_search(email, emailValidation);
}

std::ostream& operator<<(std::ostream& os, const eRazred& razred) {
	switch (razred) {
	case eRazred::PRVI:
		os << "PRVI";
		break;
	case eRazred::DRUGI:
		os << "DRUGI";
		break;
	case eRazred::TRECI:
		os << "TRECI";
		break;
	case eRazred::CETVRTI:
		os << "CETVRTI";
		break;
	default:
		os << "Razred ne postoji";
	}

	return os;
}
// Functions I defined above

char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno{ 0 };
	bool _omoguciDupliranje;
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_omoguciDupliranje = omoguciDupliranje;
	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno{ kolekcija.getTrenutno() }
		, _omoguciDupliranje{ kolekcija._omoguciDupliranje }
		, _elementi1{ new T1[kolekcija.getTrenutno()] {} }
		, _elementi2{ new T2[kolekcija.getTrenutno()] {} }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = kolekcija.getElement1(i);
			_elementi2[i] = kolekcija.getElement2(i);
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		_trenutno = rhs.getTrenutno();
		_omoguciDupliranje = rhs._omoguciDupliranje;

		T1* const tempElementi1{ new T1[rhs.getTrenutno()] {} };
		T2* const tempElementi2{ new T2[rhs.getTrenutno()] {} };

		for (int i = 0; i < getTrenutno(); ++i) {
			tempElementi1[i] = rhs.getElement1(i);
			tempElementi2[i] = rhs.getElement2(i);
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = tempElementi1;
		_elementi2 = tempElementi2;

		return *this;
	}

	Kolekcija& operator=(Kolekcija&& rhs) noexcept {
		_trenutno = std::exchange(rhs._trenutno, 0);
		_omoguciDupliranje = std::exchange(rhs._omoguciDupliranje, true);

		T1* const tempElementi1{ std::exchange(rhs._elementi1, nullptr) };
		T2* const tempElementi2{ std::exchange(rhs._elementi2, nullptr) };

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = tempElementi1;
		_elementi2 = tempElementi2;

		return *this;
	}

	[[nodiscard]] int getTrenutno() const noexcept {
		return _trenutno;
	}

	[[nodiscard]] bool daLiElementPostoji(const T1& element1, const T2& element2) const noexcept {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (getElement1(i) == element1 && getElement2(i) == element2) {
				return true;
			}
		}

		return false;
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (!_omoguciDupliranje && daLiElementPostoji(element1, element2)) {
			throw std::runtime_error("Dupliranje elemenata nije dozvoljeno");
		}

		T1* const tempElementi1{ new T1[getTrenutno() + 1] {} };
		T2* const tempElementi2{ new T2[getTrenutno() + 1] {} };

		for (int i = 0; i < getTrenutno(); ++i) {
			tempElementi1[i] = getElement1(i);
			tempElementi2[i] = getElement2(i);
		}

		tempElementi1[getTrenutno()] = element1;
		tempElementi2[getTrenutno()] = element2;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = tempElementi1;
		_elementi2 = tempElementi2;

		++_trenutno;
	}

	void SortirajRastuci(const SortirajPo& sortirajPo) {
		auto swapFunction{ getSwapFunction(sortirajPo) };

		bool keepSorting{};
		int size{ getTrenutno() };

		do {
			keepSorting = false;

			for (int i = 0; i < size - 1; ++i) {
				keepSorting = swapFunction(i, i + 1);
			}

			--size;
		} while (keepSorting);
	}

private:
	[[nodiscard]] std::function<bool(const int, const int)> getSwapFunction(
		const SortirajPo& sortirajPo
	) const {
		std::function<bool(const int, const int)> sortirajPoT1{
			[&](const int index1, const int index2) {
				auto& el1 { getElement1(index1) };
				auto& el2 { getElement1(index2) };

				if (el1 > el2) {
					std::swap(el1, el2);
					std::swap(getElement2(index1), getElement2(index2));
					return true;
				}

				return false;
			}
		};

		std::function<bool(const int, const int)> sortirajPoT2{
			[&](const int index1, const int index2) {
				auto& el1 { getElement2(index1) };
				auto& el2 { getElement2(index2) };

				if (el1 > el2) {
					std::swap(el1, el2);
					std::swap(getElement1(index1), getElement1(index2));
					return true;
				}

				return false;
			}
		};

		return (SortirajPo::T1 == sortirajPo) ? sortirajPoT1 : sortirajPoT2;
	}
};

class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
	DatumVrijeme(const DatumVrijeme& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}

	// Methods I added below
	DatumVrijeme& operator=(const DatumVrijeme& rhs) {
		int* const tempDan{ new int { rhs.getDan() } };
		int* const tempMjesec{ new int { rhs.getMjesec() } };
		int* const tempGodina{ new int { rhs.getGodina() } };
		int* const tempSati{ new int { rhs.getSati() } };
		int* const tempMinuti{ new int { rhs.getMinuti() } };

		delete _dan;
		delete _mjesec;
		delete _godina;
		delete _sati;
		delete _minuti;

		_dan = tempDan;
		_mjesec = tempMjesec;
		_godina = tempGodina;
		_sati = tempSati;
		_minuti = tempMinuti;

		return *this;
	}

	[[nodiscard]] int64_t getDatumAsDays() const noexcept {
		int64_t total{ 0 };

		const int mjesec{ getMjesec() };
		int godine{ getGodina() };

		total += getDan();
		total += (365LL * godine);

		if (mjesec <= 2) {
			--godine;
		}

		total += (godine / 4LL + godine / 400LL - godine / 100LL);

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

	[[nodiscard]] static int64_t convertDaysToMinutes(const int64_t days) noexcept {
		return days * 24 * 60;
	}

	[[nodiscard]] int64_t getTimeAsMinutes() const noexcept {
		return getSati() * 60 + getMinuti();
	}

	[[nodiscard]] int64_t getDatumVrijemeAsMinuti() const noexcept {
		return getTimeAsMinutes() + convertDaysToMinutes(getDatumAsDays());
	}

	[[nodiscard]] int64_t operator-(const DatumVrijeme& rhs) const noexcept {
		return getDatumVrijemeAsMinuti() - rhs.getDatumVrijemeAsMinuti();
	}

	[[nodiscard]] bool operator>=(const DatumVrijeme& rhs) const noexcept {
		return getDatumVrijemeAsMinuti() >= rhs.getDatumVrijemeAsMinuti();
	}

	[[nodiscard]] bool operator<=(const DatumVrijeme & rhs) const noexcept {
		return getDatumVrijemeAsMinuti() <= rhs.getDatumVrijemeAsMinuti();
	}

	[[nodiscard]] bool operator==(const DatumVrijeme& rhs) {
		return getDan() == rhs.getDan()
			&& getMjesec() == rhs.getMjesec()
			&& getGodina() == rhs.getGodina()
			&& getSati() == rhs.getSati()
			&& getMinuti() == rhs.getMinuti();
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

	[[nodiscard]] int getSati() const noexcept {
		return *_sati;
	}

	[[nodiscard]] int getMinuti() const noexcept {
		return *_minuti;
	}
};

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}

	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() { return _naziv; }
	int GetOcjena() { return _ocjena; }

	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}

	// Methods I added below
	Predmet(const Predmet& predmet)
		: _naziv { Alociraj(predmet.getNaziv()) }
		, _napomena { predmet.getNapomena() }
		, _ocjena { predmet.getOcjena() }
	{}

	Predmet& operator=(const Predmet& rhs) {
		_ocjena = rhs.getOcjena();

		char* const tempNaziv{ Alociraj(rhs.getNaziv()) };
		std::string tempNapomena{ rhs.getNapomena() };
		
		delete[] _naziv;

		_naziv = tempNaziv;
		_napomena = std::move(tempNapomena);

		return *this;
	}

	[[nodiscard]] bool operator==(const Predmet& rhs) const noexcept {
		return !std::strcmp(getNaziv(), rhs.getNaziv())
			&& getNapomena() == rhs.getNapomena()
			&& getOcjena() == rhs.getOcjena();
	}

	[[nodiscard]] const std::string& getNapomena() const noexcept { 
		return _napomena; 
	}

	[[nodiscard]] const char* getNaziv() const noexcept { 
		return _naziv; 
	}

	[[nodiscard]] int getOcjena() const noexcept { 
		return _ocjena; 
	}

};

class Uspjeh {
	eRazred* _razred;
	//formalni argument DatumVrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(eRazred razred) {
		_razred = new eRazred(razred);
	}
	~Uspjeh() { delete _razred; _razred = nullptr; }

	Kolekcija<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	eRazred* GetERazred() { return _razred; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << *obj._razred << " " << obj._predmeti << endl;
		return COUT;
	}

	// Methods I added below
	Uspjeh(const eRazred& razred, const Predmet& predmet, const DatumVrijeme& datumVrijemeDodavanja)
		: _razred{ new eRazred { razred } }
	{
		_predmeti.AddElement(predmet, datumVrijemeDodavanja);
	}

	Uspjeh(const Uspjeh& uspjeh) 
		: _razred { new eRazred { uspjeh.getERazred() } }
		, _predmeti { uspjeh.getPredmeti() }
	{}

	Uspjeh& operator=(const Uspjeh& rhs) {
		eRazred* const tempRazred{ new eRazred { rhs.getERazred() } };
		Kolekcija<Predmet, DatumVrijeme> tempPredmeti{ rhs.getPredmeti() };

		delete _razred;

		_razred = tempRazred;
		_predmeti = std::move(tempPredmeti);

		return *this;
	}

	[[nodiscard]] const Kolekcija<Predmet, DatumVrijeme>& getPredmeti() const noexcept { 
		return _predmeti; 
	}
	
	[[nodiscard]] const eRazred& getERazred() const noexcept { 
		return *_razred; 
	}

	[[nodiscard]] bool daLiPredmetVecPostoji(const Predmet& predmet) const noexcept {
		for (int i = 0; i < _predmeti.getTrenutno(); ++i) {
			if (predmet == _predmeti.getElement1(i)) {
				return true;
			}
		}

		return false;
	}

	[[nodiscard]] bool daLiJeDovoljnoVremenaProsloOdZadnjegDodavanja(
		const DatumVrijeme& datumVrijeme
	) const noexcept {
		const int size{ _predmeti.getTrenutno() };

		if (!size) {
			return true;
		}
		
		const auto& zadnjeVrijeme{ _predmeti.getElement2(size - 1) };

		return (datumVrijeme - zadnjeVrijeme) >= 5;
	}

	void dodajPredmet(const Predmet& predmet, const DatumVrijeme& datumVrijeme) {
		_predmeti.AddElement(predmet, datumVrijeme);
	}

	[[nodiscard]] double getAverage() const noexcept {
		const int size{ _predmeti.getTrenutno() };

		if (!size) {
			return 0.0;
		}

		double sum{ 0.0 };

		for (int i = 0; i < _predmeti.getTrenutno(); ++i) {
			sum += _predmeti.getElement1(i).getOcjena();
		}

		return sum / size;
	}
};

class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		_emailAdresa = (validateEmail(emailAdresa))? emailAdresa : notSetEmail;
		_brojTelefona = brojTelefona;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		std::ostream_iterator<Uspjeh> outputUspjehIterator{ std::cout, " "};
		std::copy(std::begin(obj._uspjeh), std::end(obj._uspjeh), outputUspjehIterator);

		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }

	// Methods I added below
	Kandidat(const Kandidat& kandidat)
		: _imePrezime { Alociraj(kandidat.getImePrezime()) }
		, _emailAdresa { kandidat.getEmail() }
		, _brojTelefona { kandidat.getBrojTelefona() }
		, _uspjeh { kandidat.getUspjeh() }
	{}

	Kandidat& operator=(const Kandidat& rhs) {
		char* const tempImePrezime{ Alociraj(rhs.getImePrezime()) };
		std::string tempEmail{ rhs.getEmail() };
		std::string tempBrojTelefona{ rhs.getBrojTelefona() };
		std::vector<Uspjeh> tempUspjeh{ rhs.getUspjeh() };

		delete[] _imePrezime;

		_imePrezime = tempImePrezime;
		_emailAdresa = std::move(tempEmail);
		_brojTelefona = std::move(tempBrojTelefona);
		_uspjeh = std::move(tempUspjeh);

		return *this;
	}

	[[nodiscard]] const std::vector<Uspjeh>& getUspjeh() const noexcept { 
		return _uspjeh; 
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

	[[nodiscard]] Uspjeh* getUspjehForRazred(const eRazred& razred) noexcept {
		auto uspjehZaRazred{
			std::find_if(
				std::begin(_uspjeh),
				std::end(_uspjeh),
				[&](const Uspjeh& uspjeh) {
					return uspjeh.getERazred() == razred;
				}
			)
		};

		return (uspjehZaRazred == std::end(_uspjeh)) ? nullptr : &(*uspjehZaRazred);
	}

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	bool AddPredmet(const eRazred& razred, const Predmet& predmet, const DatumVrijeme& datumVrijemeDodavanja) {
		auto uspjehZaRazred{ getUspjehForRazred(razred) };
		
		if (uspjehZaRazred) {
			if (uspjehZaRazred->daLiPredmetVecPostoji(predmet)) {
				return false;
			}
			else if (!uspjehZaRazred->daLiJeDovoljnoVremenaProsloOdZadnjegDodavanja(datumVrijemeDodavanja)) {
				return false;
			}

			uspjehZaRazred->dodajPredmet(predmet, datumVrijemeDodavanja);
			sendEmail(*uspjehZaRazred);
			return true;
		}

		_uspjeh.push_back(Uspjeh{ razred, predmet, datumVrijemeDodavanja });
		sendEmail(_uspjeh.back());
		return true;
	}

	[[nodiscard]] std::vector<Predmet> operator()(const DatumVrijeme& pocetak, const DatumVrijeme& kraj) {
		std::vector<Predmet> temp{};

		for (const auto& uspjeh : _uspjeh) {
			const auto& predmeti{ uspjeh.getPredmeti() };

			for (int i = 0; i < predmeti.getTrenutno(); ++i) {
				const auto& trenutniDatum{ predmeti.getElement2(i) };
				if (trenutniDatum >= pocetak && trenutniDatum <= kraj) {
					temp.push_back(predmeti.getElement1(i));
				}
			}
		}

		return temp;
	}

	[[nodiscard]] Uspjeh* operator[](const eRazred& razred) noexcept {
		return getUspjehForRazred(razred);
	}

	[[nodiscard]] int BrojPonavljanjaRijeci(const std::string& napomena) const {
		int counter{ 0 };

		for (const auto& uspjeh : _uspjeh) {
			const auto& predmeti{ uspjeh.getPredmeti() };

			for (int i = 0; i < predmeti.getTrenutno(); ++i) {
				counter += countStrInStr(napomena, predmeti.getElement1(i).getNapomena());
			}
		}

		return counter;
	}
private:
/*
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.

	ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
*/
	void sendEmail(const Uspjeh& uspjeh) const {
		std::thread emailThread{
			[&]() {
				std::cout << "FROM:info@edu.fit.ba\n";
				std::cout << "TO: " << getEmail() << '\n';
				std::cout << "Postovani " << getImePrezime() << ", evidentirali ste uspjeh za " << uspjeh.getERazred();
				std::cout << " razred.\n";
				std::cout << "Pozdrav\nFIT Team.\n";
			}
		};

		emailThread.join();

		if (uspjeh.getAverage() > 4.5) {
			sendSMS(uspjeh);
		}
	}

	void sendSMS(const Uspjeh& uspjeh) const {
		std::thread smsThread{
			[&]() {
				const auto& originalPrecision { std::cout.precision()};
				std::cout << std::setprecision(2) << std::fixed;

				std::cout << "Svaka cast za uspjeh " << uspjeh.getAverage() << " u " << uspjeh.getERazred() << " razredu.\n";
				
				std::cout << std::setprecision(originalPrecision);
				std::cout.unsetf(std::ios::fixed);
			}
		};

		smsThread.join();
	}
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR AE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEEILO GUBLJENJE URA?ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO?ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIENI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUEAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOANE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAEENO.
	7. IMATE POTPUNU SLOBODU DA U MAIN FUNKCIJI, ZA POTREBE TESTIRANJA, DODAJETE VISE POZIVA ILI SALJETE DRUGE VRIJEDNOSTI PARAMETARA
	****************************************************************************/

	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);

	const int kolekcijaTestSize = 9;
	Kolekcija<int, int> kolekcija1(false);
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, 20 - i);

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata, metoda AddElement baca izuzetak
		kolekcija1.AddElement(6, 15);
	}
	catch (exception& err) {
		cout << err.what() << endl;
	}
	cout << kolekcija1 << endl;

	//na osnovu vrijednosti parametra sortira clanove kolekcije u rastucem redoslijedu 
	kolekcija1.SortirajRastuci(SortirajPo::T2);
	cout << kolekcija1 << endl;


	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	cout << kolekcija3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << Matematika << endl;

	/*
	email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	za provjeru koristiti regex
	*/
	Kandidat jasmin("Jasmin Azemovic", "jasmin@outlook.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
	Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Fiziku jer nije proslo 5 minuta od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.

	ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	cout << "USPJEH ISPISATI KORISTECI OSTREAM_ITERATOR" << endl;
	cout << jasmin << endl;
	//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(DatumVrijeme(18, 06, 2019, 10, 15), DatumVrijeme(21, 06, 2019, 10, 10));
	for (size_t i = 0; i < jasminUspjeh.size(); i++)
		cout << jasminUspjeh[i] << endl;

	Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
	if (uspjeh_Irazred != nullptr)
		cout << *uspjeh_Irazred << endl;

	cin.get();
	system("pause>0");
}