#include<iostream>
using namespace std;

#include<tuple>

/*
1. BROJ I VRSTA PARAMETARA MORAJU BITI IDENTICNI KAO U PRIMJERIMA. U SUPROTNOM SE RAD NECE BODOVATI
2. STAVITE KOMENTAR NA DIJELOVE CODE-A KOJE NE BUDETE IMPLEMENTIRALI
3. KREIRAJTE .DOC FAJL SA VAŠIM BROJEM INDEKSA ( NPR. IB160061.DOC BEZ IMENA I PREZIMENA), TE NA KRAJU ISPITA U NJEGA KOPIRAJTE RJEŠENJA VAŠIH ZADATAKA. NE PREDAVATI .TXT ILI .CPP FAJLOVE
4. TOKOM IZRADE ISPITA NIJE DOZVOLJENO KORIŠTENJE HELP-A
5. TOKOM IZRADE ISPITA MOGU BITI POKRENUTA SAMO TRI PROGRAMA: PDF READER (ISPITNI ZADACI), MS VISUAL STUDIO, MS WORD (U KOJI CETE KOPIRATI VAŠA RJEŠENJA)
6. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAĐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
*/

const char* not_set = "NEMA_VRIJEDNOST";
const char* crt = "\n-------------------------------------------\n";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;
const int max_zavrsnih = 30;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

struct Poglavlje {
	char* _naslov;
	char* _sadrzaj;
	bool _prihvaceno;
	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
	void Unos(const char* naslov = nullptr, const char* sadrzaj = nullptr) {
		_ocjena = 0; _prihvaceno = false;
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}
	void Dealociraj() {
		delete[] _naslov; _naslov = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	void Ispis() {
		if (_naslov == nullptr || _sadrzaj == nullptr)
			return;
		cout << endl << "Poglavlje -> " << _naslov << endl << _sadrzaj << endl;
		if (_prihvaceno)
			cout << "Ocjena: " << _ocjena << endl;;
	}
	void OcijeniPoglavlje(int ocjena) {
		_ocjena = ocjena;
		// Modified line below
		_prihvaceno = _ocjena > 5 && ocjena <= 10;
	}

	// My additions start here

	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr) {
		_ocjena = 0; _prihvaceno = false;
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}

	void DodajNaKrajSadrzaja(const char* const sadrzaj, const char* const delimiter = " ") {
		const std::size_t newSize{
			std::strlen(_sadrzaj)
			+ std::strlen(delimiter)
			+ std::strlen(sadrzaj)
			+ 1
		};
		char* const newSadrzaj{ new char[newSize] {} };

		strcat_s(newSadrzaj, newSize, _sadrzaj);
		strcat_s(newSadrzaj, newSize, delimiter);
		strcat_s(newSadrzaj, newSize, sadrzaj);

		delete[] _sadrzaj;

		_sadrzaj = newSadrzaj;
	}

	Poglavlje& operator=(const Poglavlje& rhs) {
		char* const tempNaslov{ AlocirajNizKaraktera(rhs._naslov) };
		char* const tempSadrzaj{ AlocirajNizKaraktera(rhs._sadrzaj) };

		_ocjena = rhs._ocjena;
		_prihvaceno = rhs._prihvaceno;

		delete[] _naslov;
		delete[] _sadrzaj;

		_naslov = tempNaslov;
		_sadrzaj = tempSadrzaj;

		return *this;
	}
};

struct ZavrsniRad {
	char* _brojIndeksa;
	char* _tema;
	Poglavlje* _poglavljaRada;
	int _trenutnoPoglavlja;
	char* _datumOdbrane;
	float _konacnaOcjena; //konacna ocjena zavrsnog rada predstavlja prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane

	void Unos(const char* brojIndeksa, const char* nazivTeme = nullptr) {
		_konacnaOcjena = 0;
		_brojIndeksa = AlocirajNizKaraktera(brojIndeksa);
		_tema = AlocirajNizKaraktera(nazivTeme);
		_datumOdbrane = AlocirajNizKaraktera(not_set);
		// I added lines below
		_trenutnoPoglavlja = 0;
		_poglavljaRada = new Poglavlje[_trenutnoPoglavlja];
	}
	void Dealociraj() {
		delete[] _tema; _tema = nullptr;
		delete[] _datumOdbrane; _datumOdbrane = nullptr;
		delete[] _brojIndeksa; _brojIndeksa = nullptr;
		for (size_t i = 0; i < _trenutnoPoglavlja; i++)
			_poglavljaRada[i].Dealociraj();
		delete[] _poglavljaRada; _poglavljaRada = nullptr;
	}
	void Ispis() {
		cout << "Tema rada: " << _tema << endl;
		cout << "Sadrzaj: " << endl;
		for (size_t i = 0; i < _trenutnoPoglavlja; i++)
			_poglavljaRada[i].Ispis();
		cout << "Datum odbrane rada: " << _datumOdbrane << endl << " Ocjena: " << _konacnaOcjena << endl;
	}

	// My additions start here

	ZavrsniRad(const char* brojIndeksa = nullptr, const char* nazivTeme = nullptr)
		: _brojIndeksa{ AlocirajNizKaraktera(brojIndeksa) }
		, _tema{ AlocirajNizKaraktera(nazivTeme) }
		, _datumOdbrane{ AlocirajNizKaraktera(not_set) }
		, _konacnaOcjena{ 0.0f }
	{
		_trenutnoPoglavlja = 0;
		_poglavljaRada = new Poglavlje[_trenutnoPoglavlja];
	}

	ZavrsniRad(const ZavrsniRad& zavrsniRad)
		: _brojIndeksa{ AlocirajNizKaraktera(zavrsniRad._brojIndeksa) }
		, _tema{ AlocirajNizKaraktera(zavrsniRad._tema) }
		, _datumOdbrane{ AlocirajNizKaraktera(zavrsniRad._datumOdbrane) }
		, _konacnaOcjena{ 0.0f }
	{
		_trenutnoPoglavlja = zavrsniRad._trenutnoPoglavlja;
		_poglavljaRada = new Poglavlje[_trenutnoPoglavlja];

		for (int i = 0; i < _trenutnoPoglavlja; ++i) {
			_poglavljaRada[i] = zavrsniRad._poglavljaRada[i];
		}
	}

	void DodajPoglavlje(const char* const naslovPoglavlja, const char* const sadrzaj) {
		const auto postojecePoglavlje{ DaLiPoglavljePostoji(naslovPoglavlja) };

		if (postojecePoglavlje) {
			postojecePoglavlje->DodajNaKrajSadrzaja(sadrzaj);
			return;
		}

		Poglavlje* const tempPoglavlja{ new Poglavlje[_trenutnoPoglavlja + 1] {} };

		for (int i = 0; i < _trenutnoPoglavlja; ++i) {
			tempPoglavlja[i] = _poglavljaRada[i];
		}

		tempPoglavlja[_trenutnoPoglavlja].Unos(naslovPoglavlja, sadrzaj);

		delete[] _poglavljaRada;
		_poglavljaRada = tempPoglavlja;

		++_trenutnoPoglavlja;
	}

	[[nodiscard]] Poglavlje* DaLiPoglavljePostoji(const char* const naslovPoglavlja) noexcept {
		for (int i = 0; i < _trenutnoPoglavlja; ++i) {
			if (!std::strcmp(_poglavljaRada[i]._naslov, naslovPoglavlja)) {
				return _poglavljaRada + i;
			}
		}

		return nullptr;
	}

	void OcijeniPoglavlje(const char* const naslovPoglavlja, const int ocjena) {
		const auto postojecePoglavlje{ DaLiPoglavljePostoji(naslovPoglavlja) };

		if (postojecePoglavlje) {
			postojecePoglavlje->OcijeniPoglavlje(ocjena);

			if (!postojecePoglavlje->_prihvaceno) {
				throw std::invalid_argument("Ocjena nije validna, treba biti u rangu od 5 - 10");
			}

			return;
		}

		throw std::invalid_argument("Dato poglavlje ne postoji!");
	}

	void PostaviDatumOdbrane(const char* const datumOdbrane) noexcept {
		delete[] _datumOdbrane;
		_datumOdbrane = AlocirajNizKaraktera(datumOdbrane);
	}

	void IzracunajProsjecnuOcjenu() noexcept {
		float prosjek{ 0.0f };

		for (int i = 0; i < _trenutnoPoglavlja; ++i) {
			prosjek += _poglavljaRada[i]._ocjena;
		}

		_konacnaOcjena = (_trenutnoPoglavlja) ? prosjek / _trenutnoPoglavlja : 0.0f;
	}
};

struct Nastavnik {
	char* _imePrezime;
	ZavrsniRad* _teme[max_zavrsnih] = { nullptr };
	// My addition so I can keep track of how many members are inside the array
	int _trenutno{ 0 };

	void Unos(const char* imePrezime) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}
	void Dealociraj() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < max_zavrsnih; i++)
		{
			if (_teme[i] != nullptr) {
				_teme[i]->Dealociraj();
				delete _teme[i];
			}
		}
	}
	void Ispis() {
		cout << crt << _imePrezime << crt;
		for (size_t i = 0; i < _trenutno; i++)
			_teme[i]->Ispis();
	}

	// My additions start here

	Nastavnik(const char* imePrezime = nullptr)
		: _imePrezime{ AlocirajNizKaraktera(imePrezime) }
	{}

	bool DodajZavrsniRad(const ZavrsniRad& zavrsniRad) {
		if (_trenutno == max_zavrsnih) {
			return false;
		}
		else if (DaLiStudentImaZavrsniRadKodNastanika(zavrsniRad._brojIndeksa)) {
			return false;
		}
		else if (DaLiSeRadPonavlja(zavrsniRad._tema)) {
			return false;
		}

		_teme[_trenutno] = new ZavrsniRad{ zavrsniRad };

		++_trenutno;
		return true;
	}

	[[nodiscard]] ZavrsniRad* DaLiStudentImaZavrsniRadKodNastanika(const char* const brojIndeksa) noexcept {
		for (int i = 0; i < _trenutno; ++i) {
			if (!std::strcmp(_teme[i]->_brojIndeksa, brojIndeksa)) {
				return _teme[i];
			}
		}

		return nullptr;
	}

	[[nodiscard]] bool DaLiSeRadPonavlja(const char* const tema) const noexcept {
		for (int i = 0; i < _trenutno; ++i) {
			if (!std::strcmp(_teme[i]->_tema, tema)) {
				return true;
			}
		}

		return false;
	}

	[[nodiscard]] ZavrsniRad* ZakaziOdbranuRada(
		const char* const brojIndeksa,
		const char* const datumOdbrane)
		noexcept {
		auto zavrsniRadStudenta{ DaLiStudentImaZavrsniRadKodNastanika(brojIndeksa) };
		if (!zavrsniRadStudenta || !DaLiImaBrojPoglavljaVeciOdMin(zavrsniRadStudenta)) {
			return nullptr;
		}
		else if (!DaLiSvakoPoglavljeImaMinDuzinuSadrzaja(zavrsniRadStudenta)) {
			return nullptr;
		}
		else if (!DaLiJeSvakoPoglavljePrihvaceno(zavrsniRadStudenta)) {
			return nullptr;
		}

		zavrsniRadStudenta->PostaviDatumOdbrane(datumOdbrane);
		zavrsniRadStudenta->IzracunajProsjecnuOcjenu();

		return zavrsniRadStudenta;
	}

	[[nodiscard]] bool DaLiImaBrojPoglavljaVeciOdMin(
		const ZavrsniRad* const zavrsniRad
	) const noexcept {
		return zavrsniRad->_trenutnoPoglavlja >= min_polgavlja;
	}

	[[nodiscard]] bool DaLiSvakoPoglavljeImaMinDuzinuSadrzaja(
		const ZavrsniRad* const zavrsniRad
	) const noexcept {
		for (int i = 0; i < zavrsniRad->_trenutnoPoglavlja; ++i) {
			if (std::strlen(zavrsniRad->_poglavljaRada[i]._sadrzaj) < min_karaktera_po_poglavlju) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]] bool DaLiJeSvakoPoglavljePrihvaceno(
		const ZavrsniRad* const zavrsniRad
	) const noexcept {
		for (int i = 0; i < zavrsniRad->_trenutnoPoglavlja; ++i) {
			if (!zavrsniRad->_poglavljaRada[i]._prihvaceno) {
				return false;
			}
		}

		return true;
	}
};

[[nodiscard]] std::tuple<char*, float> PronadjiNajStudenta(
	Nastavnik** nastavnici, 
	const int brojNastavnika, 
	const float minimalnaKonacnaOcjena
) {
	for (int i = 0; i < brojNastavnika; ++i) {
		for (int ii = 0; ii < nastavnici[i]->_trenutno; ++ii) {
			if (nastavnici[i]->_teme[ii]->_konacnaOcjena >= minimalnaKonacnaOcjena) {
				return { 
					nastavnici[i]->_teme[ii]->_brojIndeksa,  
					nastavnici[i]->_teme[ii]->_konacnaOcjena 
				};
			}
		}
	}

	return { nullptr, 0.0f };
}

int main() {
	cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
	cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;

	const int max = 2;
	Nastavnik* nastavnici[max];

	nastavnici[0] = new Nastavnik; 	nastavnici[0]->Unos("Denis Music");
	nastavnici[1] = new Nastavnik; 	nastavnici[1]->Unos("Emina Junuz");

	ZavrsniRad multimedijalni;
	//parametri: brojIndeksa, tema
	multimedijalni.Unos("IB120021", "Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
	ZavrsniRad podrsa_operaterima;
	podrsa_operaterima.Unos("IB130031", "Sistem za podršku rada kablovskog operatera");
	ZavrsniRad analiza_sigurnosti;
	analiza_sigurnosti.Unos("IB140041", "Prakticna analiza sigurnosti bežičnih računarskih mreža");
	ZavrsniRad kriptografija;
	kriptografija.Unos("IB120021", "Primjena teorije informacija u procesu generisanja kriptografskih ključeva");

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzajem*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja

	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");

	//nazivPoglavlja, ocjena
	multimedijalni.OcijeniPoglavlje("Uvod", 8);


	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu. sprijeciti dodavanje zavrsnih radova sa istom temom kao i mogucnost da jedan student kod istog nastavnika posjeduje vise zavrsnih radova*/
	//brojIndeksa, zavrsniRad

	if (nastavnici[0]->DodajZavrsniRad(multimedijalni))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[0]->DodajZavrsniRad(podrsa_operaterima))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad(podrsa_operaterima))//dupliranje rada, onemoguciti dodavanje
		cout << "Zavrsni rad nije dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad(kriptografija)) //studentu vec dodijeljen rad, onemoguciti dodavanje
		cout << "Zavrsni rad nije dodat!" << endl;
	if (nastavnici[1]->DodajZavrsniRad(analiza_sigurnosti))
		cout << "Zavrsni rad uspjesno dodat!" << endl;


	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva
	izracunavanje konacne ocjene i definisanje datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio.
	Za zakazivanje odbrane rada moraju biti zadovoljeni sljedeci uslovi:
		1. zavrsni rad mora imati broj poglavlja veci od minimalnog
		2. svako poglavlje mora imati broj karaktera veci od minimalnog
		3. svako poglavlje mora biti prihvaceno/odobreno
	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazana odbrana.
	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
*/

//paramteri: brojIndeksa, datumOdbrane

	ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB120021", "25.09.2019");
	if (zr1 != nullptr)
		zr1->Ispis();

	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB180081", "25.09.2019");//student sa brojem indeksa IB180081 jos uvijek nije prijavio rad
	if (zr1 == nullptr)
		cout << "Odbrana ne moze biti zakazana!" << endl;

	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
	nastavnici[0]->Ispis();
	nastavnici[1]->Ispis();

	/*funkcija PronadjiNajStudenta ima zadatak da pronadje prvog studenta koji je zavrsni rad odbranio kod
	nastavnika/mentora, te tom prilikom ostvario (odnosi se na studenta) ocjenu vecu od proslijedjene (npr. 8.2)*/

	float prosjekStudenta = 0;
	char* indeksStudenta;
	//parametri PronadjiNajStudenta: nastavnici, brojNastavnika, minimalnaKonacnaOcjena
	tie(indeksStudenta, prosjekStudenta) = PronadjiNajStudenta(nastavnici, max, 8.2);
	if (indeksStudenta != nullptr)
		cout << crt << indeksStudenta << " -> " << prosjekStudenta << crt;

	for (int i = 0; i < max; i++) {
		nastavnici[i]->Dealociraj();
		delete nastavnici[i];
		nastavnici[i] = nullptr;
	}
		
	system("pause>0");
	return 0;
	
}