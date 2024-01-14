Igra Križić-Kružić(TicTacToe)

Ovo je jednostavna igra Križić-Kružić implementirana u C++ konzolnoj aplikaciji.

Kako igrati:

Potrebno je odabrati način igre:

1: Igrač vs Igrač: Dvije osobe izmjenjuju poteze.
2: Igrač vs Računalo: Jedna osoba igra protiv računala.

Tijekom igre:

Korisnici unose položaje (1-9) gdje žele postaviti svoj simbol.
Za računalo, potezi su automatizirani.
Igra završava kada postoji pobjednik, neriješeno ili kada odlučite završiti.

Značajke igre

Načini igre:

2 igrača igraju jedan protiv drugog.
Igrač igra protiv računala.

Bodovanje:

Svaki igrač akumulira bodove za pobjedu(Pobjeda nosi 100 bodova).
Računalo također može osvojiti bodove.

Resetiranje:

Nakon svake igre program pita korisnika želi li nastaviti igratič
Ako DA(y), odabire se resetiranje ploče i ponovno se igra.
Ako NE(n), igra završava i ispisuje se pobjednik(i njegovi bodovi) ili nerjeseno.

Kompilacija i izgradnja:

Igra je implementirana u C++.
Kod koristi standardne knjižnice, uključujući <iostream>, <vector>, <algorithm> i <ctime>.
Kompilirajte kod pomoću željenog C++ kompajlera.

Napomene:

Ploča igre prikazuje se u prozoru konzole.
Za provjeru unosa, igra provjerava valjani numerički unos unutar određenog raspona.
Potezi računala su automatizirani pomoću jednostavne slučajne selekcije.
Na kraju igre ako se odabere odgovor DA, onaj igrač koji je zadnji igrao, igra drugi u sljedećoj igri.
