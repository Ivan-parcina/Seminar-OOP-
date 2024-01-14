#include "TicTacToe.h"

// Implementacije Ploca
Ploca::Ploca() : velPloce(9), ploca(velPloce, std::vector<char>(velPloce, ' ')) {}

void Ploca::ispisiPlocu() const {
    system("cls");
    for (int i = 0; i < velPloce; i++) {
        for (int j = 0; j < velPloce; j++) {
            if (j == 0 || j == velPloce - 1)
                std::cout << ' ';
            std::cout << ploca[i][j];
            if (j != velPloce - 1 && (j + 1) % (velPloce / 3) == 0) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i != velPloce - 1 && (i + 1) % (velPloce / 3) == 0) {
            for (int j = 0; j < velPloce + 8; j++) {
                std::cout << "-";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void Ploca::resetPloca() {
    std::fill(ploca.begin(), ploca.end(), std::vector<char>(velPloce, ' '));
}

bool Ploca::odabirPozicije(int pozicija, char znak) {
    if (pozicija >= 1 && pozicija <= 9) {
        int red = (pozicija - 1) / 3 * 3 + 1;
        int stup = ((pozicija - 1) % 3) * 3 + 1;

        if (ploca[red][stup] == ' ') {
            ploca[red][stup] = znak;
            return true;
        }
    }
    return false;
}

bool Ploca::provjeriPobjednika() {
    for (int i = 1; i <= 7; i += 3) {
        // provjera redova
        if (ploca[i][1] == ploca[i][4] && ploca[i][4] == ploca[i][7] && ploca[i][1] != ' ') {
            return true;
        }
        // provjera stupaca
        if (ploca[1][i] == ploca[4][i] && ploca[4][i] == ploca[7][i] && ploca[1][i] != ' ') {
            return true;
        }
    }
    // provjera obe dijagonale
    if (((ploca[1][1] == ploca[4][4] && ploca[4][4] == ploca[7][7]) ||
        (ploca[1][7] == ploca[4][4] && ploca[4][4] == ploca[7][1])) &&
        ploca[4][4] != ' ') {
        return true;
    }
    return false;
}

bool Ploca::provjeraPuna() {
    for (int i = 1; i <= 7; i += 3) {
        for (int j = 1; j <= 7; j += 3) {
            if (ploca[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Implementacije Igrac
Igrac::Igrac(char z) : znak(z), bodovi(0) {}

char Igrac::vratiZnak() {
    return znak;
}

int Igrac::vratiBodove() {
    return bodovi;
}

void Igrac::dodajBodovi() {
    bodovi += 100;
}

// Implementacije IgracX
IgracX::IgracX() : Igrac('X') {}

void IgracX::potez(Ploca& ploca) {
    int pozicija;
    std::cout << "Igrac X: unesite poziciju(1-9): ";
    std::cin >> pozicija;
    while (!ploca.odabirPozicije(pozicija, vratiZnak())) {
        std::cout << "Pogresan unos. Molim Vas unesite ponovno: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> pozicija;
    }
}

// Implementacije IgracO
IgracO::IgracO() : Igrac('O') {}

void IgracO::potez(Ploca& ploca) {
    int pozicija;
    std::cout << "Igrac O: unesite poziciju(1-9): ";
    std::cin >> pozicija;
    while (!ploca.odabirPozicije(pozicija, vratiZnak())) {
        std::cout << "Pogresan unos. Molim Vas unesite ponovno: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> pozicija;
    }
}

// Implementacije Racunalo
Racunalo::Racunalo() : Igrac('O') {}

void Racunalo::potez(Ploca& ploca) {
    srand(static_cast<unsigned>(time(0)));
    int pozicija;
    do {
        pozicija = rand() % 9 + 1;
    } while (!ploca.odabirPozicije(pozicija, vratiZnak()));
}

// Implementacije Igra
Igra::Igra() : trenutniIgrac(&igracX) {}

void Igra::promijeniIgracVsIgrac() {
    if (trenutniIgrac == &igracX) {
        trenutniIgrac = &igracO;
    }
    else {
        trenutniIgrac = &igracX;
    }
}

void Igra::promijeniIgracVsRacunalo() {
    if (trenutniIgrac == &igracX) {
        trenutniIgrac = &racunalo;
    }
    else {
        trenutniIgrac = &igracX;
    }
}

void Igra::ispisiPobjednika() {
    if (trenutniIgrac == &racunalo) {
        std::cout << "Racunalo pobjeduje. +100 bodova." << std::endl;
    }
    else {
        std::cout << "Igrac " << trenutniIgrac->vratiZnak() << " pobjeduje. +100 bodova." << std::endl;
    }
    trenutniIgrac->dodajBodovi();
}

void Igra::rezultat() {
    std::vector<Igrac*> igraci = { &igracX, &igracO, &racunalo };
    auto maxIgrac = std::max_element(igraci.begin(), igraci.end(), [](Igrac* a, Igrac* b) {
        return a->vratiBodove() < b->vratiBodove();
        });
    int maxBodovi = (*maxIgrac)->vratiBodove();
    bool nerjeseno = false;
    for (Igrac* igrac : igraci) {
        if (igrac->vratiBodove() == maxBodovi && igrac != *maxIgrac) {
            nerjeseno = true;
        }
    }
    std::cout << "Zavrsni rezultat: ";
    if (nerjeseno) {
        std::cout << "Nerjeseno" << std::endl;
    }
    else {
        if (*maxIgrac == &racunalo) {
            std::cout << "Racunalo";
        }
        else {
            std::cout << "Igrac " << (*maxIgrac)->vratiZnak();
        }
        std::cout << " pobjeduje sa " << (*maxIgrac)->vratiBodove() << " bodova" << std::endl;
    }
}

void Igra::Igraj() {
    int broj;
    char odgovor;
    std::cout << "1: Igrac vs Igrac" << std::endl;
    std::cout << "2: Igrac vs Racunalo" << std::endl;
    std::cout << "Odaberite nacin igre(1 ili 2): ";
    std::cin >> broj;
    while (broj != 1 && broj != 2) {
        system("cls");
        std::cout << "1: Igrac vs Igrac" << std::endl;
        std::cout << "2: Igrac vs Racunalo" << std::endl;
        std::cout << "Pogresan unos. Unesite 1 ili 2." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> broj;
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
                std::cout << "Nerjeseno." << std::endl;
            }
            std::cout << "Zelite li nastaviti(y/n): ";
            std::cin >> odgovor;
            while (odgovor != 'y' && odgovor != 'n') {
                std::cout << "Pogresan unos. Unesite y ili n.";
                std::cin >> odgovor;
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

int main() {
    Igra TicTacToe;
    TicTacToe.Igraj();

    return 0;
}
