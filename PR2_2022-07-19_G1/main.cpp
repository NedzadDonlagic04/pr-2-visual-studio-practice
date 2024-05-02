#include <iostream>
using namespace std;

// Headers I included below
#include<vector>
#include<numeric>
#include<thread>
#include<fstream>
#include<regex>
#include<string>

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

// Functions I made below

[[nodiscard]] bool isStrValidInt(const std::string& str) noexcept {
	std::regex isIntValidation{ "^-?\\d+$" };

	return std::regex_search(str, isIntValidation);
}

[[nodiscard]] const char* getKarakteristikeAsText(const Karakteristike& karakteristika) noexcept {
	switch (karakteristika) {
	case Karakteristike::NARUDZBA:
		return "NARUDZBA";
	case Karakteristike::KVALITET:
		return "KVALITET";
	case Karakteristike::PAKOVANJE:
		return "PAKOVANJE";
	case Karakteristike::ISPORUKA:
		return "ISPORUKA";
	default:
		return "Karakteristika ne postoji\n";
	}
}

std::ostream& operator<<(std::ostream& os, const Karakteristike& karakteristika) {
	os << getKarakteristikeAsText(karakteristika);

	return os;
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

template<class T1, class T2>
class Rjecnik {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Rjecnik(bool omoguciDupliranje = true) {
		_omoguciDupliranje = omoguciDupliranje;
		_trenutno = 0;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
	}
	~Rjecnik() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Rjecnik& obj) {
		for (size_t i = 0; i < obj._trenutno; i++) {
			COUT << obj.getElement1(i) << " " << obj.getElement2(i);

			/*
				Moved endl to if because in main a comment makes it look like the
				extra endl at the end shouldn't be there
			*/
			if (i + 1 != obj._trenutno) {
				COUT << endl;
			}
		}
		return COUT;
	}

	// Methods I added below
	Rjecnik(const Rjecnik& rijecnik)
		: _omoguciDupliranje { rijecnik._omoguciDupliranje }
		, _trenutno { rijecnik.getTrenutno() }
		, _elementi1 { new T1[rijecnik.getTrenutno()] }
		, _elementi2 { new T2[rijecnik.getTrenutno()] }
	{
		for (int i = 0; i < rijecnik.getTrenutno(); ++i) {
			_elementi1[i] = rijecnik.getElement1(i);
			_elementi2[i] = rijecnik.getElement2(i);
		}
	}

	Rjecnik& operator=(Rjecnik&& rhs) {
		bool tempOmoguciDupliranje{ std::exchange(rhs._omoguciDupliranje, true) };
		int tempTrenutno{ std::exchange(rhs._trenutno, 0) };
		T1* const tempElementi1{ std::exchange(rhs._elementi1, new T1[rhs._trenutno]) };
		T2* const tempElementi2{ std::exchange(rhs._elementi2, new T2[rhs._trenutno]) };

		_omoguciDupliranje = tempOmoguciDupliranje;
		_trenutno = tempTrenutno;
		_elementi1 = tempElementi1;
		_elementi2 = tempElementi2;

		return *this;
	}

	Rjecnik& operator=(const Rjecnik& rhs) {
		_omoguciDupliranje = rhs._omoguciDupliranje;
		_trenutno = rhs.getTrenutno();

		T1* const tempElementi1{ new T1[getTrenutno()] };
		T2* const tempElementi2{ new T2[getTrenutno()] };

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

	void AddElement(const T1& element1, const T2& element2) {
		if (!_omoguciDupliranje && DaLiElementPostoji(element1, element2)) {
			throw std::runtime_error("Dupliciranje elemenata nije dozvoljeno");
		}

		T1* const tempElementi1{ new T1[getTrenutno() + 1] };
		T2* const tempElementi2{ new T2[getTrenutno() + 1] };

		for (int i = 0; i < getTrenutno(); ++i) {
			tempElementi1[i] = getElement1(i);
			tempElementi2[i] = getElement2(i);
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = tempElementi1;
		_elementi2 = tempElementi2;

		_elementi1[getTrenutno()] = element1;
		_elementi2[getTrenutno()] = element2;

		++_trenutno;
	}

	[[nodiscard]] bool DaLiElementPostoji(const T1& element1, const T2& element2) const noexcept {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (getElement1(i) == element1 || getElement2(i) == element2) {
				return true;
			}
		}
		
		return false;
	}

	Rjecnik operator()(int start, const int end) {
		Rjecnik<T1, T2> temp{ _omoguciDupliranje };

		if (start < 0 || start >= getTrenutno() || end < 0 || end >= getTrenutno()) {
			return temp;
		}

		for (; start <= end; ++start) {
			temp.AddElement(getElement1(start), getElement2(start));
		}

		return temp;
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
	[[nodiscard]] int getOcjena() const noexcept { 
		return _ocjena; 
	}

	[[nodiscard]] const Rjecnik<Karakteristike, const char*>& getKomentareKarakteristika() const noexcept {
		return _komentariKarakteristika; 
	}

	ZadovoljstvoKupca(const ZadovoljstvoKupca& zadovoljstvoKupca)
		: _ocjena{ zadovoljstvoKupca.getOcjena() }
	{
		const auto& komentariKarakteristike{ zadovoljstvoKupca.getKomentareKarakteristika() };
		for (int i = 0; i < komentariKarakteristike.getTrenutno(); ++i) {
			_komentariKarakteristika.AddElement(
				komentariKarakteristike.getElement1(i),
				GetNizKaraktera(komentariKarakteristike.getElement2(i))
			);
		}
	}

	ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& rhs) {
		_ocjena = rhs.getOcjena();

		Rjecnik<Karakteristike, const char*> tempKomentariKarakteristika{};

		const auto& komentariKarakteristike{ rhs.getKomentareKarakteristika() };
		for (int i = 0; i < komentariKarakteristike.getTrenutno(); ++i) {
			tempKomentariKarakteristika.AddElement(
				komentariKarakteristike.getElement1(i),
				GetNizKaraktera(komentariKarakteristike.getElement2(i))
			);
		}

		_komentariKarakteristika = std::move(tempKomentariKarakteristika);

		return *this;
	}

	~ZadovoljstvoKupca() {
		for (int i = 0; i < _komentariKarakteristika.getTrenutno(); ++i) {
			delete[] _komentariKarakteristika.getElement2(i);
		}
	}

	[[nodiscard]] bool operator==(const ZadovoljstvoKupca& rhs) {
		return getOcjena() == rhs.getOcjena() 
			&& DaLiSuKomentariKarakteristikaJednaki(rhs.getKomentareKarakteristika());
	}

	[[nodiscard]] bool DaLiSuKomentariKarakteristikaJednaki(
		const Rjecnik<Karakteristike, const char*>& komentariKarakteristika
	) const noexcept {
		if (komentariKarakteristika.getTrenutno() != _komentariKarakteristika.getTrenutno()) {
			return false;
		}

		for (int i = 0; i < _komentariKarakteristika.getTrenutno(); ++i) {
			if (_komentariKarakteristika.getElement1(i) != komentariKarakteristika.getElement1(i)) {
				return false;
			}
			else if (!std::strcmp(_komentariKarakteristika.getElement2(i), komentariKarakteristika.getElement2(i))) {
				return false;
			}
		}

		return true;
	}

	friend std::ostream& operator<<(std::ostream& os, const ZadovoljstvoKupca& zadovoljstvoKupca) {
		os << zadovoljstvoKupca.getOcjena() << '\n';

		const auto& komentariKarakteristika{ zadovoljstvoKupca.getKomentareKarakteristika() };

		for (int i = 0; i < komentariKarakteristika.getTrenutno(); ++i) {
			os << '\t' << komentariKarakteristika.getElement1(i) << " - ";
			os << komentariKarakteristika.getElement2(i);

			if (i + 1 != komentariKarakteristika.getTrenutno()) {
				os << '\n';
			}
		}

		return os;
	}

	void DodajKomentarKarakteristike(const Karakteristike& karakteristika, const char* const komentar) {
		if (DaLiJeKarakteristikaKomentarisana(karakteristika)) {
			throw std::runtime_error("Karakteristika vec komentarisana");
		}

		_komentariKarakteristika.AddElement(karakteristika, GetNizKaraktera(komentar));
	}

	[[nodiscard]] bool DaLiJeKarakteristikaKomentarisana(const Karakteristike& karakteristika) const noexcept {
		for (int i = 0; i < _komentariKarakteristika.getTrenutno(); ++i) {
			if (_komentariKarakteristika.getElement1(i) == karakteristika) {
				return true;
			}
		}

		return false;
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
	~Kupac()
	{
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

	void Info() override {
		std::cout << crt << getImePrezime() << ' ' << getDatumRodjenja() << ' ' << getEmail() << '\n';
		std::cout << "KUPOVINE -> " << crt;

		for (int i = 0; i < _kupovine->getTrenutno(); ++i) {
			std::cout << "Iznost racuna: " << _kupovine->getElement1(i);
			std::cout << "KM, zadovoljstvo kupca: " << _kupovine->getElement2(i);
			std::cout << crt;
		}

		std::cout << "BODOVI -> ";
		for (const auto& bod : _bodovi) {
			std::cout << bod << ", ";
		}

		std::cout << crt;
	}

	void DodajKupovinu(const float cijena, const ZadovoljstvoKupca& zadovoljstvoKupca) noexcept {
		const int bodovi = cijena / 10;

		_kupovine->AddElement(cijena, zadovoljstvoKupca);
		
		if (!bodovi) {
			return;
		}
		
		_bodovi.push_back(bodovi);

		if (bodovi <= 5) {
			return;
		}

		SendEmail();
	}

	void SacuvajBodove() const noexcept {
		const std::string fileName { getEmail() + std::string(".txt")};
	
		std::ofstream bodoviFile{ fileName, std::fstream::app };

		if (!bodoviFile.is_open()) {
			return;
		}

		for (const auto& bod : _bodovi) {
			bodoviFile << bod << '\n';
		}
	}

	void UcitajBodove() noexcept {
		const std::string fileName{ getEmail() + std::string(".txt") };

		std::ifstream bodoviFile{ fileName };

		if (!bodoviFile.is_open()) {
			return;
		}

		std::string line{};

		// If the regex isn't written right inside the function isStrValidInt
		// something will probably break
		while (std::getline(bodoviFile, line)) {
			if (isStrValidInt(line)) {
				_bodovi.push_back(std::stoll(line));
			}
		}
	}

	[[nodiscard]] Rjecnik<Karakteristike, const char*> GetKupovineByKomentar(const char* const dioKomentara) const noexcept {
		Rjecnik<Karakteristike, const char*> temp{};

		for (int i = 0; i < _kupovine->getTrenutno(); ++i) {
			const auto& komentarKarakteristike{ 
				_kupovine->getElement2(i).getKomentareKarakteristika() 
			};

			for (int ii = 0; ii < komentarKarakteristike.getTrenutno(); ++ii) {
				if (std::strstr(komentarKarakteristike.getElement2(ii), dioKomentara)) {
					temp.AddElement(
						komentarKarakteristike.getElement1(ii),
						GetNizKaraktera(komentarKarakteristike.getElement2(ii))
					);
				}
			}
		}
		
		return temp;
	}

private:
	void SendEmail() {
		/*
			Mutex isn't needed here because join is called right after
			the thread is created and since nothing else is changing
			data in between this is fine
			std::cout is also thread safe
		*/
		std::thread email{
			[&]() {
				std::this_thread::sleep_for(std::chrono::seconds(3));

				std::cout << crt;
				std::cout << "TO: " << getEmail() << ";\nSubject: Ostvareni bodovi\n\n";
				std::cout << "Postovani,\n\nPrilikom posljednje kupovine ste ostvarili ";
				std::cout << _bodovi.back() << " bodova tako da trenutno vas ukupan broj ";
				std::cout << "bodova iznosi " << getBodoviUkupno() << "\n\nZahvaljujemo vam na kupovini.";
				std::cout << "\nPuno pozdrava";
				std::cout << crt;
			}
		};

		email.join();
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Nabrojite i ukratko pojasnite osnovne razlike izmedju list i vector klase?\n";
	return "Odgovor -> Vektor spasava elemente u nizu, sto znaci da je svaki element jedan za drugim u memoriji, liste spasavaju pointer na "
		"sljedeci element, sto znaci da elementi nisu jedan za drugim u memoriji. Vektor moze zauzeti vise memorije unapred u slucaju dodavanja "
		" novih elemenata dok list to ne radi. Svaki elementu vektor klasi zahtjeva memorije samo za sebe, svaki element u list klasi zahtjeva "
		" memorije za sebe i za pokazivac na prijasnji i sljedeci element. Insertovanje novog elementa (igdje sem na kraju) u list-i je mnogo "
		" jeftinije nego u vektor zbog prijasnje navedenih osobina, ali zato pristup u vektor je mnogo jeftiniji nego u liste, posto je vektor "
		" niz uzme se pocetak niza i doda offset dok lista mora proci od pocetka kroz sve clanove dok ne dode do trazenog. ";
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