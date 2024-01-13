#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>

using namespace std;

class Ploca {
private:
	int velPloce;
	vector<vector<char>> ploca;
public:
	Ploca() : ploca(velPloce, vector<char>(velPloce, ' ')), velPloce(9) {}
	void ispisiPlocu() const {
		system("cls");
		for (int i = 0; i < velPloce; i++) {
			for (int j = 0; j < velPloce; j++) {
				if (j == 0 || j == velPloce - 1)
					cout << ' ';
				cout << ploca[i][j];
				if (j != velPloce - 1 && (j + 1) % (velPloce / 3) == 0) {
					cout << " | ";
				}
			}
			cout << endl;
			if (i != velPloce - 1 && (i + 1) % (velPloce / 3) == 0) {
				for (int j = 0; j < velPloce + 8; j++) {
					cout << "-";
				}
				cout << endl;
			}
		}
		cout << endl;
	}
	void resetPloca() {
		fill(ploca.begin(), ploca.end(), vector<char>(velPloce, ' '));
	}
	bool odabirPozicije(int pozicija, char znak) {
		if (pozicija >= 1 && pozicija <= 9 ) {
			int red = (pozicija - 1) / 3 * 3 + 1;
			int stup = ((pozicija - 1) % 3) * 3 + 1;

			if (ploca[red][stup] == ' ') {
				ploca[red][stup] = znak;
				return true;
			}
		}
		return false;
	}
	bool provjeriPobjednika() {
		for (int i = 1; i <= 7; i+=3) {
			//provjera redova
			if (ploca[i][1] == ploca[i][4] && ploca[i][4] == ploca[i][7] && ploca[i][1] != ' ') {
				return true;
			}
			//provjera stupaca
			if (ploca[1][i] == ploca[4][i] && ploca[4][i] == ploca[7][i] && ploca[1][i] != ' ') {
				return true;
			}
		}
		//provjera obe dijagonale
		if (((ploca[1][1] == ploca[4][4] && ploca[4][4] == ploca[7][7]) || 
			(ploca[1][7] == ploca[4][4] && ploca[4][4] == ploca[7][1]))
			&& ploca[4][4] != ' ') {
			return true;
		}
		return false;
	}
	bool provjeraPuna() {
		for (int i = 1; i <= 7; i += 3){
			for (int j = 1; j <= 7; j += 3){
				if (ploca[i][j] == ' ') {
					return false;
				}
			}
		}
		return true;
	}
};

class Igrac {
protected:
	char znak;
	int bodovi;
public:
	Igrac(char z) : znak(z), bodovi(0){}
	virtual void potez(Ploca &ploca) = 0;
	char vratiZnak() { return znak; }
	int vratiBodove() { return bodovi; }
	void dodajBodovi() { bodovi += 100; }
};

class IgracX : public Igrac {
public:
	IgracX() : Igrac('X'){}
	void potez(Ploca& ploca) override {
		int pozicija;
		cout << "Igrac X: unesite poziciju(1-9): ";
		cin >> pozicija;
		while (!ploca.odabirPozicije(pozicija, vratiZnak())) {
			cout << "Pogresan unos. Molim Vas unesite ponovno: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> pozicija;
		}
	}
};

class IgracO : public Igrac {
public:
	IgracO() : Igrac('O') {}
	void potez(Ploca& ploca) override {
		int pozicija;
		cout << "Igrac O: unesite poziciju(1-9): ";
		cin >> pozicija;
		while (!ploca.odabirPozicije(pozicija, vratiZnak())) {
			cout << "Pogresan unos. Molim Vas unesite ponovno: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> pozicija;
		}
	}
};

class Racunalo : public Igrac {
public:
	Racunalo() : Igrac('O') {}
	void potez(Ploca& ploca) override {
		srand(time(0));
		int pozicija;
		do {
			pozicija = rand() % 9 + 1;
		} while (!ploca.odabirPozicije(pozicija, vratiZnak()));
	}
};

class Igra {
private:
	Ploca ploca;
	Igrac* trenutniIgrac;
	IgracX igracX;
	IgracO igracO;
	Racunalo racunalo;
public:
	Igra() :trenutniIgrac(&igracX) {}
	void promijeniIgracVsIgrac(){
		if (trenutniIgrac == &igracX) {
			trenutniIgrac = &igracO;
		}
		else{
			trenutniIgrac = &igracX;
		}
	}
	void promijeniIgracVsRacunalo() {
		if (trenutniIgrac == &igracX) {
			trenutniIgrac = &racunalo;
		}
		else {
			trenutniIgrac = &igracX;
		}
	}
	void ispisiPobjednika() {
		if (trenutniIgrac == &racunalo) {
			cout << "Racunalo pobjeduje. +100 bodova." << endl;
		}
		else {
			cout << "Igrac " << trenutniIgrac->vratiZnak() << " pobjeduje. +100 bodova." << endl;
		}
		trenutniIgrac->dodajBodovi();
	}
	void rezultat() {
		vector<Igrac*> igraci = { &igracX, &igracO, &racunalo };
		auto maxIgrac = max_element(igraci.begin(), igraci.end(), [] (Igrac* a, Igrac* b) {
			return a->vratiBodove() < b->vratiBodove();
		});
		int maxBodovi = (*maxIgrac)->vratiBodove();
		bool nerjeseno = false;
		for (Igrac* igrac : igraci) {
			if(igrac->vratiBodove() == maxBodovi && igrac != *maxIgrac){
				nerjeseno = true;
			}
		}
		cout << "Zavrsni rezultat: ";
		if (nerjeseno) {
			cout << "Nerjeseno" << endl;
		}
		else {
			if (*maxIgrac == &racunalo) {
				cout << "Racunalo";
			}
			else {
				cout << "Igrac " << (*maxIgrac)->vratiZnak();
			}
			cout << " pobjeduje sa " << (*maxIgrac)->vratiBodove() << " bodova" << endl;
		}
	}
	void Igraj() {
		int broj;
		char odgovor;
		cout << "1: Igrac vs Igrac" << endl;
		cout << "2: Igrac vs Racunalo" << endl;
		cout << "Odaberite nacin igre(1 ili 2): ";
		cin >> broj;
		while (broj != 1 && broj != 2) {
			system("cls");
			cout << "1: Igrac vs Igrac" << endl;
			cout << "2: Igrac vs Racunalo" << endl;
			cout << "Pogresan unos. Unesite 1 ili 2." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> broj;
		}
		while (true) {
			ploca.ispisiPlocu();
			trenutniIgrac->potez(ploca);
			if (ploca.provjeriPobjednika() || ploca.provjeraPuna()) {
				if (ploca.provjeriPobjednika()) {
					ploca.ispisiPlocu();
					ispisiPobjednika();
				}
				else if (ploca.provjeraPuna()) {
					ploca.ispisiPlocu();
					cout << "Nerjeseno." << endl;
				}
				cout << "Zelite li nastaviti(y/n): ";
				cin >> odgovor;
				while (odgovor != 'y' && odgovor != 'n') {
					cout << "Pogresan unos. Unesite y ili n.";
					cin >> odgovor;
				}
				if (odgovor == 'n') {
					rezultat();
					break;
				}
				else {
					ploca.resetPloca();
				}
			}
			if (broj == 1) {
				promijeniIgracVsIgrac();
			}
			else {
				promijeniIgracVsRacunalo();
			}
		}
	}
};

int main() {
	Igra TicTacToe;
	TicTacToe.Igraj();

	return 0;
}

