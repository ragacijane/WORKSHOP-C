//GLOBALNE PROMENJIVE
ako je globalna prikrivena lokalnom, globalnu dohvatamo sa :

//TIPOVI NABRAJANJA
enum SemaforPesaci {CRVENO, ZELENO};
enum SemaforVozila {ZELENO,CRVENO,ZUTO};//GRESKA JER JE DOSEG VAN UGLASTIH

enum struct SemaforPesaci{CRVENO,ZELENO};//moze i class
enum struct SemaforVozila{ZELENO, CRVENO, ZUTO};//SADA MOZE, JER JE DOSEG DO UGLASTIH

SemaforPesaci semP = SemaforPesaci::CRVENO;
SemaforVozila semV = ZUTO;//Greska, nije u dosegu, mora se prosiriti doseg imena

int i = (int)SemaforVozila::ZUTO;//obavezna eksplicitna konverzija zbog modifikatora struct/class

 //bezimena UNIJA
union (int i, double d; char *pc};//promenjive se ponašaju kao globalni
i = 55; d = 123.5; pc = "ABC";

//MUTABLE

struct X {
	int a;
	mutable int b;
};
int main() {
	X x1, ;
	const X x2;
	x1.a = 1;
	x1.b = 2;
	x2.a = 3;//greška jer je a const
	x2.b = 4;//zbog mutable b, dozvoljeno
}

//DINAMIČKI
ako nema dovoljno prostora baza se izuzetak bad_alloc(zaglavnje <new>)
ili X *x = new (nothrow)X; //ako nema prostora, neće se baciti izuzetak već će biti nullptr

Tacka *pt = new Tacka[10]; // za niz
delete [] pt;

//REFERENCE na lvrednost
void f(int i, int &j) {//i po vrednosti, j po referenci
	i++; //stvarni argument se neće promeniti
	j++;//stvarni argument će se promeniti
}

	//referenca se inicijalizuje i više se ne može promeniti

int i = 1;
int &j = 1; //j upućuje na i
i = 3; j = 5; //u oba sluč se menja i
int *p = &j; //isto što i &i
j += 1; //isto što i i+=1;
int k = j; //posredan pristup do i preko reference ~ ne treba &
int m = *p //-||- preko pokazivača ~ mora zvezdica

int &j = *new int(2);		//j upucuje na dinamički objekat 2
int *p = &j;				//p je pokazivač na isti objekati;
(*p)++; j++;				//objekat je 3, pa 4
delete &j;					// isto što i delete p

ne postoje nizovi referenci, pokazivaci na reference ni reference na reference	
ali referenca na pokazivac je dozvoljena int i = 5, *p = &i, *&rp = p;

int& f(int &i){int &r = *new int(i); return r;}
int& f(int &i) { return *new int(i); }
int& f(int &i) { return i; }

int& f(int &i) { int r = i; return r; }//GRESKA VRAĆA SE LOKALNA PROMENJIVA KOJA JE NA STEKU
int& f(int i) { return i; }// GRESKA i je preneto po vrednosti i sada je ono je kopija na steku
int& f(int &i) { int r = *new int(i), return r; }//GRESKA R JE PROMENJIVA NA STEKU
int& f(int &i) { int j = i, &r = j; return r; }//GRESKA referenca na promenjivi objekat na steku

//FOR EACH petlja
for (int &k : niz)//menja se element niza
for (int k : niz)//ne menja se element niza

//REFERENCE na dvrednost
&&

int i = 1; //i je promenjiv podatak
const int ci = i; //ci je nepromenjiv podatak
int && rd1 = i; // GRESKA i je promenjiva lvrednost
int && rd2=ci;// GRESKA ci je nepromenjiva l vrednost
int && rd3 = i + 1;// i+1 je promenjiva d vrednost
int && rd4 = 10;// nepromenjiva d vrednost
rd3++; rd4++;// rd3=3, rd4=11

int i = 1;					//i je promenjiv podatak
const int ci = i;			//ci je nepromenjiv podatak
const int && rd1 = i;		// GRESKA i je promenjiva lvrednost
const int && rd2 = ci;		// GRESKA ci je nepromenjiva l vrednost
const int && rd3 = i + 1;	// i+1 je promenjiva d vrednost
const int && rd4 = 10;		// nepromenjiva d vrednost
rd3++; rd4++;				// GRESKa jer su refenerence na nepromenjive vrednosti

void povecaj(int && a) {a++;}
int x = 1;
povecaj(x + 1);//x+1 je dvrednost, a==3
povecaj(x);//GRESKa x je lvrednost

//INLINE FUNKCIJE
inline int inc(int i) {return i + 1;}
metod klase cije je telo napisano unutar definicije klase, to je inline funkcija

//PODRAZUMEVANA VREDNOST ARGUMENTA SA DESNA NA LEVO

//PRISTUP ELEMENTIMA
isto vazi i za pokazivace
int& elem(int *a, int i) {
	return a[i];
}
const int& elem(const int *a, int i) {
	return a[i];
}
int a[20], i = 10;
const int b[20] = { 0 };
elem(a, i) = 1;		//OK poziva se prva
elem(b, i) = 1;		//GRESKA funkcija vraća konstantu nepromenjivu lvrednost ~poziva se druga
int x = elem(b, i);

poboljšane funkcije 
const int& elem(const int *a, int i) {
	return elem((int*)a, i);
}

//cast operatori predavanje 7 30:00

	//KLASE i OBJEKTI
//inspektor i mutator
class X {
public:
	int citaj()const { return i; }
	int pisi(int j = 0) { int t = i; i = j; return t; }
private:
	int i;
};
X x; const X cx;
x.citaj();		// OK inspektor promenjivog obj
x.pisi();		//OK mutator promenjivog obj
cx.citaj();		//OK inspektor nepromenjivog obj
cx.pisi();		//GRESKA mutator nepromenjivog obj

//VOLATILE

class X {
public:
	X() { kraj = false; }
	int f() volatile {					// da nije volatile, moguca je optimizacija 
		while (!kraj) {/*...*/ }		//if(!kraj)while(){/*...*/} jer se u telu(...) ne menja kraj
	}
	void zavrseno() { kraj = true; }
private:
	bool kraj;
}

volatila ~ za nepostojane i promenjive
const volatile ~ za sve-promenjive, nepromenjive i nepostojane obj

//MODIFIKATORI & I &&
tip tekućeg objekta
class X {
public:
	int f() & { return 1; }			//lvrednost
	int f() const & { return 2; }	//const lvrednost
	int f() && { return 3; }		//dvrednost
};
X x1;
const X x2 = x1;
int i = x1.f();
int j = x2.f();
int k = X().f();

//KONSTRUKTORI
za poziv PK nije dozvoljeno() jer će se smatrati pozivom funkcije
//inicijalizatori 
class YY {
public: YY(int j) { ... };
}
class XX {
	YY y; int i = 0;
public:
	XX(int);
};
XX:XX(int k) : y(k + 1), i(k - 1) {...}		//inicijalizacija pre tela funkcije

class Kontejner {
public:
	Kontejner() : deo(this) { ... }
private:
	Deo de;
};
class Deo {
public:
	Deo(Kontejner* kontejner) :mojKontejner(kontejner) { ... }
private: Kontejner* mojKontejner;
}
//delegirajući
class T {
public:
	T(int i) {}
	T() :T(1) {}			//delegirajući : T(), ciljni T(int)
	T(char c) : T(0.5) {}	//GRESKa jer dolazi do rekurzije
	T(double) : T('a') {}
}

//eksplicitni poziv konstruktora
c2 = c1 + Kompleksni(1.4, 5.6);

//KOPIRAJUCI KONSTRUKTOR			pravi duboku kopiju- pravi novi objekat iste klase koji inicijalizuje starim objektom 

X(const X&) = delete;		//zabrana kopiranja
ili = default

class XX {
public:
	XX(int);
	XX(const XX&);			//kopirajuci konstruktor
};
XX f(XX x1) {
	XX x2 = x1;				//poziv KK za x2
	return x2;				//poziv KK za privremeni objekat u koji se smesta rez,jer funkcija vraća dvrednost
}
void g() {
	XX xa = 3, xb = 1;
	xa = f(xb);				//poziva se KK za x1, a u xa se prepisuje privremeni objekat rezultata
							//ili se poziva XX:operator= ako je definisan
}


//PREMESTAJUCI KONSTRUKTOR predavanje 10 i konverzioni konstruktor

//premestajuci pravi plitku kopiju, ne pravi novi objekat vec preuzima vrednosti objekta koji je pri kraju zivota


//DESTRUKTOR
~ ime
//PRIMER KONSTRUKTIORA I DESTRUKTORA

class TEkst {
public:
	Tekst() { niska = nullptr; }		//Podrazumevani
	Tekst(const char*);					//konverzioni
	Tekst(const Tekst&);				// kopirajuci
	Tekst(Tekst&&);						//premestajuci
	~Tekst();							//desktrukor
private:
	char *niska;
};
#include <cstring>
using namespace std;
Tekst::Tekst(const char* t){			//konverzioni
	niska = New char[strlen(t) + 1];
	strcpy(niska, t);
}
Tekst::Tekst(const Tekst& t) {			//kopirajuci
	niska = new char[strlen(t.niska) + 1];
	strcpy(niska, t.niska);
}
TekstTekst(Tekst&& t) {					//premestajuci
	niska = t.niska; 
	t.niska = nullptr;
}
Tekst::~Tekst() {						//destruktor
	delete[] niska; niska = nullptr;
}
int main() {
	Tekst a("pozdrab!"), b = a;			//pozvan je za a konverzioni, a za b kopirajuci
}
//KONSTRUKTORI DOPUNA
// 
//		Ako hocu da se objekti prave samo pomocu statickog ili nestatickog metoda, konstruktor ide u private sekciju
// 
//STATICKI ZAJEDNICKI ATRIBUTI

class X {
private:
	static int i;		//samo jedan za sve objekte
	int j;				//svaki objekat ima svoj j
}
obracanje int X::i = 5;

//STATICKI METODI		mogu da se pozivaju iako ne postoji objekat te klase 

classX{
	static int x;		//staticki atribut
			int y;
public:
	static int f(X);	//staticki metod(deklaracija)
	int g();
};

int X::X = 5;			//definicija statickog atributa

int X::f(X x1) {		//definicija statickog metoda
	int i = x;			//pristup statickom atributu X::x
	int j = y;			//GRESKA X::y nije staticki
	int k = x1.x;		// ovo moze
	return x1.x;		// ovo moze ali nije preporucljivo, izraz x1 se ne izracunava
}

int X::g() {			//nestaticka metoda~moze da koristi
	int i = x;			//i staticke atribute
	int j = y;			// i nestaticke atribute, this->y
	return j;
}

int main() {
	X xx;
	int p = X::f(xx);	//X::f moze neposredno bez objekta jer je static
	int q = X::g();		//GRESKA za X::g mora konkretan obj
	xx.g();				//moze
	p = xx.f(xx);		//Moze ali nije preporucljivo
}
//PRIJATELJSKE
class X {
	friend void g(int, X&);				//prijateljska globalna
	friend void Y::h();					//prijateljska metoda druge klase
	friend int o(X x) { return x.i); }	//definicija globalne f-je
	friend int p() { return i; 0 }		// Greska nepostoji this
	int i;
public:
	void f(int ip) { i = ip; }
};

void g(int k, X &x) { x.i = k }
int main() {
	X x; int j;
	x.f(5);								//postavljanje preko metoda
	g(6, x);							//postavljanje preko prijateljske funkcije
	j = o(x);							//citanje preko prijateljske funkcije
}
//pr 2
class X {
	friend Y;			//ako je klasa Y definisana ili deklarisana
	friend class Z;		//ako Z jos nije ni def ni dek
};

class Proizvod {
private:
	friend class Fabrika;
	proizvod();			//konstruktor je dostupan samo klasi fabrika
};

//UGNJEZDENE KLASE

int x, y;
class Spoljna {
public: int x, static int z;
		class Unutrasnja {
			void f(int i, spoljna *ps) {
				x = i;				//GRESKA nepoznat objekat klase Spoljnja
				spoljna::x = i;		//GRESKA isto
				z = i;				//OK pristup statickom clanu Spoljnja i da je u private
				::x = i;			//OK globalno x
				y = i;				//OK globalno y
				ps->x = i;			//OK pristupa se atributu x objekta na koji pokazuje ps Spoljnja::x objekta *ps
			}
		};
};
Unutrasnja u;						//GRESKa nije u dosegu
spoljnja::Unutrasnja u;				//OK

//LOKALNE KLASE čas 12 20:00
//pokazivač na člana klase čas 12

//PREKLAPANJE OPERATORA

Kompleksni::Kompleksni(double r = 0.0, double i = 0.0) :real(r), imag(i) {}	//podrazumevani kon
Kompleksni operator+ (Kompleksni c1, Kompleksni c2) {						//prvi nacin
	Kompleksni c;
	c.real = c1.real + c2.real;
	c.imag = c1.imag + c2.imag;
	return c;
}
Kompleksni operator-(kompleksni c1, Kompleksni c2) {						//drugi nacin
	return Kompleksni(c1.real - c2.real, c1.imag - c2.imag);
}
Kompleksni c1(1.0, 1.0), c2(2.0, 2.0), c3, c4;
c3 = c1 + c2;
c4 = c1 + c2;
 
NE MOZE . .* :: = : sizeof alignof typeid throw
= mora kao nestaticki metod
new, delete mora kao statički metod

Kompleksni operator!();								//metod, unarni operator !, nema argumente zbog this

friend Kompleksni operator~(Kompleksni);			// globalna prijat. f.ja, unarni operator ~

Kompleksni operator-(Kompleksni);					// Metod, binarni operator - , argument je desni

friend Kompleksni operator+(Kompleksni, Kompleksni);//glob prij fja levi,desni

//OPERATOR DODELE

X& X::operator=(const X &x) {
	if (&x != this) {}/*uništavaju se delovi starog /this;
				  formiraju se novi delovi;
				  kopira se sadržaj iz x*/
	return *this;
}
X& X::operator=(const X& x);//desni operand koji ne zelimo da menjamo- kopirajuca varijanta
X& X::operator=(X&& x);//referenca na d vrednost, premestajuca varijanta
//oba operatora vraćaju lvrednost
#include <cstring>
class Tekst {
public:
	TEkst(const char* niz);//konverzioni konstruktor
	Tekst(const Tekst& t) { kopirajt(t); }//kopirajuci konstruktor
	Tekst(Tekst&& t) { premesti(t); }//kopirajuci =
	Tekst & operator=(const Tekst&);//premestajuci =
	Tekst& operator=(Tekst&&); ((destruktor))
		~Tekst() { brisi(); }
private:
	char *niska;
	void kopiraj(const Tekst& t) {
		niska = new char[strlen(t.niska) + 1];//zauzimanje prostora
		strcpy(niska, t.niska);//kopiranje niske
	}
	void premesti(Tekst& t) {
		niska = t.niska; //premešta se iz t.niska u nisku, jer se t brise
		t.niska = nullptr;
	}
	void brisi() {
		delete[] niska;
		niska = nullptr;
	};
	Tekst& TEks::operator=(const Tekst&) {
		if (&t != this) {
			brisi(); //brisu se podaci iz this
			kopiraj(t); //kopiraju se iz t, t ne nestaje
		}
		return *this
	}
	Tekst& Tekst::operator=(Tekst&& t) {
		if (&t != this) {
			brisi();
			premesti(t);//premesta se iz t, t nestaje
		}
		return *this;
	}
	void main() {
		Tekst a("Pozdrav!"),// konverzioni konstruktor Tekst(const char*)
			b = a, //kopirajuci
			c = Tekst("123");//prvo eksplicitni konst koji poziva konverz, pa se poziva prem konst
		a = b;//ovo je dodela, kopirajuca dodela
		b = Tekst("ABC");//prvo konverzioni, pa premestajuca dodela jer nestaje
	}
}
	//PREKLAPANJE ++ --
	//PREKLAPANJE[] mora biti metod
	Tip& operator[](indeks);//za promenljive 
	const Tip& operator[] (indeks) const; //za nepromenljive
	//operator() kao ne staticki metod
	//operator -> mora biti metod
	struct X { int m };
	class Xptr {
		X *p;
		int bp;
	public:
		Cptr(X *px) :p(px), bp(0){}
		X& operator*() { bp++; return *p }
		X* operator->() { bp++; return p; }
	};
	void main() {
		X x;
		Xptr pp = &x;
		(*pp).m = 1;
		int i = pp->m;
	}
	//PREKLAPANJE CAST OPERATORA
	mora kao metod klase nema arg

		class X {
		public:
			operator int() { return 1; }
			explicit operator double() { return 2; }
	};
	int a = X();				//implicitno se poziva preko konstruktora a=1
	int b = (int)X();			//eksplicitni poziv konstruktora, privremeni objekat klase x b=1
	double c = (double)X();		//eksplicitan poziv double c=2
	double d = X();				//za dabl je kljucna rec explicit, tako da mora da se naglasi, pa će biti dve konverzije
	
								//d će dobiti int 1, pa će int u double d=1.0

	//NEW I DELETE PREKLAPANJE
	//preklapanje << i >>
#include <iostrem>
using namespace std:
	class Kompleksni {
	double real, imag;
	friend ostream operator<<(ostream&, const Kompleksni&);//deklaracija
	public:itd..
};
ostream& operator<<(ostream &os, const Kompleksni &c) {//definicija
	return os << "(" << c.real << "," << c.imag << ")";
}
	//OPERATORI NABRAJANJA

inline Dani operator+(Dani d, int k) {
	k = (int(d) + k) % 7;
	if (k > 0)k += 7;
	return Dani(k);
}
inline Dani&


//nasleđivanje 
 konstruktor se ne nasleđuje
