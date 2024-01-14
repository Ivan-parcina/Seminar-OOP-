#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

class Ploca {
private:
    int velPloce;
    std::vector<std::vector<char>> ploca;

public:
    Ploca();
    void ispisiPlocu() const;
    void resetPloca();
    bool odabirPozicije(int pozicija, char znak);
    bool provjeriPobjednika();
    bool provjeraPuna();
};

class Igrac {
protected:
    char znak;
    int bodovi;

public:
    Igrac(char z);
    virtual void potez(Ploca& ploca) = 0;
    char vratiZnak();
    int vratiBodove();
    void dodajBodovi();
};

class IgracX : public Igrac {
public:
    IgracX();
    void potez(Ploca& ploca) override;
};

class IgracO : public Igrac {
public:
    IgracO();
    void potez(Ploca& ploca) override;
};

class Racunalo : public Igrac {
public:
    Racunalo();
    void potez(Ploca& ploca) override;
};

class Igra {
private:
    Ploca ploca;
    Igrac* trenutniIgrac;
    IgracX igracX;
    IgracO igracO;
    Racunalo racunalo;

public:
    Igra();
    void promijeniIgracVsIgrac();
    void promijeniIgracVsRacunalo();
    void ispisiPobjednika();
    void rezultat();
    void Igraj();
};
