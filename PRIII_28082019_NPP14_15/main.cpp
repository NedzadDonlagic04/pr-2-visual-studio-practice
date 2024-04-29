#include<iostream>
using namespace std;

#include<vector>
#include<functional>
#include<regex>
#include<numeric>
#include<thread>

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
enum SortirajPo { T1, T2 };
const std::string defaultEmail{ "notSet@edu.fit.ba" };

char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

// Some global functions I made below

[[nodiscard]] const char* GetERazredKaoStr(const eRazred& razred) {
	switch (razred) {
	case eRazred::PRVI:
		return "PRVI";
	case eRazred::DRUGI:
		return "DRUGI";
	case eRazred::TRECI:
		return "TRECI";
	case eRazred::CETVRTI:
		return "CETVRTI";
		
	}
}

std::ostream& operator<<(std::ostream& os, const eRazred& razred) {
	os << GetERazredKaoStr(razred);

	return os;
}

[[nodiscard]] bool JeLiValidnaEmailAdresa(const std::string& email) {
	std::regex outlookCheck{ "@outlook.com$" };
	std::regex eduFitCheck{ "@edu.fit.ba$" };

	return std::regex_search(email, outlookCheck)
		|| std::regex_search(email, eduFitCheck);
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_trenutno = 0;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
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

	// From here on out are things I defined myself
	int getTrenutno() const { return _trenutno; }

	void AddElement(const T1& element1, const T2& element2) {
		if (!_omoguciDupliranje && DaLiElementPostojiUKolekciji(element1, element2)) {
			throw std::invalid_argument("Element vec postoji");
		}

		T1* const tempElementi1{ new T1[_trenutno + 1] };
		T2* const tempElementi2{ new T2[_trenutno + 1] };

		for (int i = 0; i < _trenutno; ++i) {
			tempElementi1[i] = getElement1(i);
			tempElementi2[i] = getElement2(i);
		}

		tempElementi1[_trenutno] = element1;
		tempElementi2[_trenutno] = element2;

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = tempElementi1;
		_elementi2 = tempElementi2;
		++_trenutno;
	}

	[[nodiscard]] bool DaLiElementPostojiUKolekciji(const T1& element1, const T2& element2) const noexcept {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (getElement1(i) == element1 && getElement2(i) == element2) {
				return true;
			}
		}

		return false;
	}

	void SortirajRastuci(const SortirajPo& sortirajPo) {
		auto swapFunction{ getSwapFunction(sortirajPo) };

		for (int i = 0; i < getTrenutno() - 1; ++i) {
			for (int ii = 0; ii < getTrenutno() - 1 - i; ++ii) {
				swapFunction(ii, ii + 1);
			}
		}
	}

	Kolekcija(const Kolekcija& kolekcija)
		: _omoguciDupliranje { kolekcija._omoguciDupliranje }
		, _trenutno { kolekcija._trenutno }
	{
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		for (int i = 0; i < _trenutno; ++i) {
			_elementi1[i] = kolekcija.getElement1(i);
			_elementi2[i] = kolekcija.getElement2(i);
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		_omoguciDupliranje = rhs._omoguciDupliranje;
		_trenutno = rhs._trenutno;

		T1* const tempElementi1{ new T1[_trenutno] };
		T2* const tempElementi2{ new T2[_trenutno] };

		for (int i = 0; i < _trenutno; ++i) {
			tempElementi1[i] = rhs.getElement1(i);
			tempElementi2[i] = rhs.getElement2(i);
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = tempElementi1;
		_elementi2 = tempElementi2;

		return *this;
	}

	[[nodiscard]] bool DaLiElement1PostojiUKolekciji(const T1& element1) const noexcept {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (getElement1(i) == element1) {
				return true;
			}
		}

		return false;
	}
private:
	[[nodiscard]] std::function<void(const int, const int)> getSwapFunction(
		const SortirajPo& sortirajPo
	) const noexcept {
		std::function<void(const int, const int)> swapT1{
			[&](const int index1, const int index2) {
				auto& el1{ getElement1(index1) };
				auto& el2{ getElement1(index2) };

				if (el1 > el2) {
					std::swap(el1, el2);
					std::swap(getElement2(index1), getElement2(index2));
				}
			}
		};

		std::function<void(const int, const int)> swapT2{
			[&](const int index1, const int index2) {
				auto& el1{ getElement2(index1) };
				auto& el2{ getElement2(index2) };

				if (el1 > el2) {
					std::swap(el1, el2);
					std::swap(getElement1(index1), getElement1(index2));
				}
			}
		};

		return (sortirajPo == SortirajPo::T1) ? swapT1 : swapT2;
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

	// From here on out are things I defined myself

	DatumVrijeme& operator=(const DatumVrijeme& rhs) {
		int* const tempDan{ new int { rhs.GetDan() } };
		int* const tempMjesec{ new int { rhs.GetMjesec() } };
		int* const tempGodina{ new int { rhs.GetGodina() } };
		int* const tempSati{ new int { rhs.GetSati() } };
		int* const tempMinuti{ new int { rhs.GetMinuti() } };
		
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

	[[nodiscard]] int GetDan() const {
		return *_dan;
	}
	
	[[nodiscard]] int GetMjesec() const {
		return *_mjesec;
	}

	[[nodiscard]] int GetGodina() const {
		return *_godina;
	}

	[[nodiscard]] int GetSati() const {
		return *_sati;
	}

	[[nodiscard]] int GetMinuti() const {
		return *_minuti;
	}

	[[nodiscard]] int64_t GetDatumKaoDani() const noexcept {
		int64_t total{ 0 };

		int godine{ GetGodina() };
		const int mjesec{ GetMjesec() };

		total += GetDan() + godine * 365;

		if (mjesec <= 2) {
			--godine;
		}

		total += (godine % 4 + godine % 400 - godine % 100);

		total += [&]() {
			constexpr int mjeseci[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			return std::accumulate(mjeseci, mjeseci + mjesec - 1, 0);
		}();

		return total;
	}

	[[nodiscard]] int64_t GetDatumKaoMinute() const noexcept {
		return GetDaniKaoMinute(GetDatumKaoDani()) + GetSatiKaoMinute(GetSati()) + GetMinuti();
	}

	[[nodiscard]] int64_t GetRazlikaUMinutama(const DatumVrijeme& datumVrijeme) const noexcept {
		return GetDatumKaoMinute() - datumVrijeme.GetDatumKaoMinute();
	}

	[[nodiscard]] static int64_t GetDaniKaoMinute(const int64_t dani) noexcept {
		return dani * 24LL * 60LL;
	}

	[[nodiscard]] static int64_t GetSatiKaoMinute(const int64_t sati) noexcept {
		return sati * 60LL;
	}

	[[nodiscard]] bool operator==(const DatumVrijeme& rhs) const noexcept {
		return GetDan() == rhs.GetDan()
			&& GetMjesec() == rhs.GetMjesec()
			&& GetGodina() == rhs.GetGodina()
			&& GetSati() == rhs.GetSati()
			&& GetMinuti() == rhs.GetMinuti();
	}

	[[nodiscard]] bool operator>=(const DatumVrijeme& rhs) const noexcept {
		return GetDatumKaoMinute() >= rhs.GetDatumKaoMinute();
	}

	[[nodiscard]] bool operator<=(const DatumVrijeme& rhs) const noexcept {
		return GetDatumKaoMinute() <= rhs.GetDatumKaoMinute();
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

	// From here on out are things I defined myself
	const string& GetNapomena() const { return _napomena; }
	const char* GetNaziv() const { return _naziv; }
	int GetOcjena() const { return _ocjena; }

	Predmet(const Predmet& predmet) 
		: _naziv { Alociraj(predmet.GetNaziv()) }
		, _ocjena { predmet.GetOcjena() }
		, _napomena { predmet.GetNapomena() }
	{}

	Predmet& operator=(const Predmet& rhs) {
		char* const tempNaziv{ Alociraj(rhs.GetNaziv()) };
		std::string tempNapomena{ rhs.GetNapomena() };

		delete[] _naziv;

		_naziv = tempNaziv;
		_ocjena = rhs.GetOcjena();
		_napomena = std::move(tempNapomena);

		return *this;
	}

	[[nodiscard]] bool operator==(const Predmet& rhs) {
		return !std::strcmp(GetNaziv(), rhs.GetNaziv())
			&& GetOcjena() == rhs.GetOcjena()
			&& GetNapomena() == rhs.GetNapomena();
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
	// From here on out are things I defined myself
	const Kolekcija<Predmet, DatumVrijeme>& GetPredmeti() const { return _predmeti; }
	eRazred GetERazred() const { return *_razred; }

	Uspjeh(const eRazred& razred, const Predmet& predmet, const DatumVrijeme& datumVrijeme) 
		: _razred{ new eRazred { razred } }
	{
		_predmeti.AddElement(predmet, datumVrijeme);
	}

	Uspjeh(const Uspjeh& uspjeh) 
		: _razred { new eRazred{ uspjeh.GetERazred() }}
		, _predmeti { uspjeh.GetPredmeti() }
	{}

	Uspjeh& operator=(const Uspjeh& rhs) {
		*_razred = rhs.GetERazred();
		_predmeti = rhs.GetPredmeti();

		return *this;
	}

	[[nodiscard]] bool DaLiPredmetPostoji(const Predmet& predmet) const noexcept {
		for (int i = 0; i < _predmeti.getTrenutno(); ++i) {
			if (_predmeti.getElement1(i) == predmet) {
				return true;
			}
		}

		return false;
	}

	[[nodiscard]] bool DaLiJeProsloDovoljnoVremenaOdZadnjegDodavanja(
		const DatumVrijeme& datumVrijeme
	) const noexcept {
		const auto& zadnjiDatumVrijeme{
			_predmeti.getElement2(_predmeti.getTrenutno() - 1)
		};


		return datumVrijeme.GetRazlikaUMinutama(zadnjiDatumVrijeme) >= 5;
	}

	[[nodiscard]] double GetProsjek() const noexcept {
		double prosjek{ 0.0 };
		const int brojPredmeta{ _predmeti.getTrenutno() };

		for (int i = 0; i < brojPredmeta; ++i) {
			prosjek += _predmeti.getElement1(i).GetOcjena();
		}

		return (brojPredmeta)? prosjek / brojPredmeta : prosjek; 
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
		_emailAdresa = (JeLiValidnaEmailAdresa(emailAdresa))? emailAdresa : defaultEmail;
		_brojTelefona = brojTelefona;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		for (const auto& uspjeh : obj._uspjeh) {
			COUT << uspjeh << '\n';
		}
		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }

	// From here on out are things I defined myself
	const vector<Uspjeh>& const GetUspjeh() const { return _uspjeh; }
	const string& GetEmail() const { return _emailAdresa; }
	const string& GetBrojTelefona() const { return _brojTelefona; }
	const char* GetImePrezime() const { return _imePrezime; }

	Kandidat(const Kandidat& kandidat) 
		: _imePrezime { Alociraj(kandidat.GetImePrezime()) }
		, _emailAdresa { kandidat.GetEmail() }
		, _brojTelefona { kandidat.GetBrojTelefona() }
	{}

	Kandidat& operator=(const Kandidat& rhs) {
		char* const tempImePrezime{ Alociraj(rhs.GetImePrezime()) };
		std::string tempEmailAdresa{ rhs.GetEmail() };
		std::string tempBrojTelefona{ rhs.GetBrojTelefona() };

		delete[] _imePrezime;

		_imePrezime = tempImePrezime;
		_emailAdresa = std::move(tempEmailAdresa);
		_brojTelefona = std::move(tempBrojTelefona);

		return *this;
	}

	bool AddPredmet(const eRazred& razred, const Predmet& predmet, const DatumVrijeme& datumVrijeme) {
		auto postojeciRazred{
			std::find_if(
				std::begin(_uspjeh),
				std::end(_uspjeh),
				[&](const Uspjeh& uspjeh) {
					return uspjeh.GetERazred() == razred;
				}
			)
		};
		
		if (!_uspjeh.size() || postojeciRazred == std::end(_uspjeh)) {
			_uspjeh.push_back(Uspjeh{ razred, predmet, datumVrijeme });
			PosaljiEmail(_uspjeh.back());
			return true;
		}

		if (postojeciRazred->DaLiPredmetPostoji(predmet)) {
			return false;
		}
		else if (!postojeciRazred->DaLiJeProsloDovoljnoVremenaOdZadnjegDodavanja(datumVrijeme)) {
			return false;
		}

		postojeciRazred->GetPredmeti()->AddElement(predmet, datumVrijeme);
		PosaljiEmail(*postojeciRazred);

		return true;
	}

	[[nodiscard]] int BrojPonavljanjaRijeci(const std::string& rijec) const noexcept {
		std::regex rijecZaPronaci{ rijec };
		int counter{ 0 };

		for (const auto& uspjeh : _uspjeh) {
			const auto& predmeti{ uspjeh.GetPredmeti() };
			
			for (int i = 0; i < predmeti.getTrenutno(); ++i) {
				const auto& napomena{ predmeti.getElement1(i).GetNapomena() };
				
				const auto pronadeneRijeci{
					std::sregex_iterator(
						std::begin(napomena), 
						std::end(napomena), 
						rijecZaPronaci
					)
				};
				const auto kraj{ std::sregex_iterator() };

				counter += std::distance(pronadeneRijeci, kraj);
			}
		}

		return counter;
	}

	[[nodiscard]] std::vector<Predmet> operator()(
		const DatumVrijeme& OD, 
		const DatumVrijeme& DO
	) const noexcept {
		std::vector<Predmet> predmetiUIntervalu{};
		auto daLiJePredmetDodanUIntervalu{
			[&](const DatumVrijeme& datumVrijeme) {
				return datumVrijeme >= OD && datumVrijeme <= DO;
			}
		};

		for (const auto& uspjeh : _uspjeh) {
			const auto& predmeti{ uspjeh.GetPredmeti() };
			
			for (int i = 0; i < predmeti.getTrenutno(); ++i) {
				if (daLiJePredmetDodanUIntervalu(predmeti.getElement2(i))) {
					predmetiUIntervalu.push_back(predmeti.getElement1(i));
				}
			}
		}

		return predmetiUIntervalu;
	}

	[[nodiscard]] Uspjeh* operator[](const eRazred& razred) {
		for (auto& uspjeh : _uspjeh) {
			if (*uspjeh.GetERazred() == razred) {
				return &uspjeh;
			}
		}

		return nullptr;
	}

private:
	void PosaljiSMS(const eRazred& razred, const double prosjek) const noexcept {
		std::thread posaljiSMS{
			[&]() {
				std::cout << "Svaka cast za uspjeh " << prosjek << " u " << razred << " razredu\n";
			}
		};
		posaljiSMS.join();
	}

	void PosaljiEmail(const Uspjeh& uspjeh) const noexcept {
		std::thread posaljiEmail{
			[&]() {
				std::cout << "FROM:info@edu.fit.ba\nTO: " << GetEmail() << "\n\n";
				std::cout << "Postovani " << GetImePrezime() << ", evidentirali ste uspjeh ";
				std::cout << "za " << uspjeh.GetERazred() << ".\nPozdrav.\nFIT Team.\n";
			}
		};
		posaljiEmail.join();

		const double prosjek{ uspjeh.GetProsjek() };

		if (prosjek > 4.5) {
			PosaljiSMS(uspjeh.GetERazred(), prosjek);
		}
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