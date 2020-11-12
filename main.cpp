#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// DANE GLOBALNE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
struct Adresat {
    string imie = "", nazwisko = "", e_mail = "", adres = "", numerTelefonu = "";
    int idAdresata = 0;
};
struct Uzytkownik {
    string nazwaUzytkownika = "", hasloUzytkownika = "";
    int idUzytkownika = 0;
};
const string nazwaPlikuZUzytkownikami = "Uzytkownicy.txt";
const string nazwaPlikuZAdresatami = "Adresaci.txt";
const string nazwaPlikuTymczasowego = "Adresaci_tymczasowy.txt";
const char separator = '|';
// FUNKCJE OPISOWE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void wyswietlMenuLogowania() {
    system("cls");
    cout << "PANEL UZYTKOWNIKA:" << endl;
    cout << "1. Logowanie." << endl;
    cout << "2. Rejestracja." << endl;
    cout << "0. Zakoncz program." << endl << endl;
    cout << "Tw\242j wyb\242r:" << endl;
}
void wyswietlMenuGlowne() {
    system("cls");
    cout << "MENU GLOWNE:" << endl;
    cout << "1. Dodaj adresata." << endl;
    cout << "2. Wyszukaj po imieniu." << endl;
    cout << "3. Wyszukaj po nazwisku." << endl;
    cout << "4. Wy\230wietl wszystkich adresat\242w." << endl;
    cout << "5. Usu\344 adresata." << endl;
    cout << "6. Edytuj adresata." << endl;
    cout << "7. Zmien haslo." << endl;
    cout << "0. Wyloguj sie" << endl << endl;
    cout << "Tw\242j wyb\242r:" << endl;
}
void wyswietlMenuUsuwania() {
    system("cls");
    cout << "Wybierz opcj\251 usuwania:" << endl;
    cout << "1. Usu\344 pojedy\344czego adresata." << endl;
    cout << "2. Usu\344 wszystkich adresatow." << endl;
    cout << "9. Powr\242t." << endl;
}
void wyswietlMenuEdycji() {
    cout << endl << "Wybierz element, kt\242ry chcesz edytowa\206:" << endl;
    cout << "1. Imi\251." << endl;
    cout << "2. Nazwisko." << endl;
    cout << "3. Numer telefonu." << endl;
    cout << "4. E-mail." << endl;
    cout << "5. Adres." << endl;
    cout << "0. Powr\242t." << endl;
}
void wyswietlIntro() {
    cout << "###########################" << endl;
    cout << "## KSIAZKA ADRESOWA v3.0 ##" << endl;
    cout << "###########################" << endl << endl;
    Sleep(1500);
    cout << "Naci\230nij dowolny klawisz, aby kontynuowac..." << endl;
    getch();
}
//FUNKCJE POMOCNICZNE I WYBORU @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void zamienPierwszaLitereNaDuzaAReszteNaMala (string &wyraz) {
    wyraz[0] = toupper(wyraz[0]);
    for (int i = 1; i < wyraz.length(); i++) {
        wyraz[i] = tolower(wyraz[i]);
    }
}
string wczytajLinie() {
    string linia = "";
    cin.clear();
    cin.sync();
    getline(cin, linia);
    zamienPierwszaLitereNaDuzaAReszteNaMala(linia);
    return linia;
}
void wyswietlOpcjePowrotuDoMenuGlownego() {
    cout << "Naci\230nij dowolny klawisz, aby powr\242cic do menu g\210\242wnego..." << endl;
    getch();
}
void wyswietlOpcjePowrotuDoMenuUsuwania() {
    cout << "Naci\230nij dowolny klawisz, aby powr\242cic do menu usuwania..." << endl;
    getch();
}
void wyswietlInformacjeOPustejKsiazceAdresowej() {
    system("cls");
    cout << "Ksi\245\276ka adresowa jest pusta! :-(" << endl << endl;
    wyswietlOpcjePowrotuDoMenuGlownego();
}
void wyswietlInformacjeOWylogowaniu() {
    cout << "Zostales wylogowany!" << endl << endl;
    cout << "Naci\230nij dowolny klawisz, aby powr\242cic do menu logowania..." << endl;
    getch();;
}
bool zapytajOMozliwoscPonownegoWykonania() {
    int wybranaOpcja;

    cout << "1. TAK" << endl;
    cout << "2. NIE" << endl << endl;

    do {
        cin.clear();
        cin.sync();
        cin >> wybranaOpcja;
        if (!(cin.fail())) {
            switch (wybranaOpcja) {
            case 1:
                return true;
            case 2:
                return false;
            default:
                cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
                Sleep(1500);
            }
        } else {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        }
    } while(true);
}
bool poprosOPotwierdzenie() {
    int wybranyZnak;

    cout << "Czy jeste\230 tego pewien? (Wci\230nij t, \276eby potwierdzi\206)" << endl;
    wybranyZnak = getch();
    if (wybranyZnak == 'T' || wybranyZnak == 't') {
        return true;
    } else {
        return false;
    }
}
int wyznaczIdOstatniegoAdresataWPliku() {
    fstream adresaci;
    string linia;
    int idOstatniegoAdresataWPliku = 0;

    adresaci.open(nazwaPlikuZAdresatami.c_str(), ios::in);
    if(adresaci.good()) {
        cin.ignore();
        while(!adresaci.eof()) {
            getline(adresaci, linia);
            if(!linia.empty()) {
                linia = linia[0];
                idOstatniegoAdresataWPliku = atoi(linia.c_str());
            }
        }
    }
    adresaci.close();
    return idOstatniegoAdresataWPliku;
}
//FUNKCJE GLOWNE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void wczytajListeUzytkownikow(vector<Uzytkownik> &listaUzytkownikow) {
    fstream uzytkownicy;
    string wczytanaLinia;
    Uzytkownik wczytanyUzytkownik;
    vector<string> daneUzytkownika;

    uzytkownicy.open(nazwaPlikuZUzytkownikami.c_str(), ios::in);

    if(!uzytkownicy.good()) {
        return;
    }

    uzytkownicy.clear();
    uzytkownicy.seekg(0, ios::beg);

    while(getline(uzytkownicy, wczytanaLinia, separator)) {
        daneUzytkownika.push_back(wczytanaLinia);

        if (daneUzytkownika.size() >= 3) {
            wczytanyUzytkownik.idUzytkownika = atoi(daneUzytkownika[0].c_str());
            wczytanyUzytkownik.nazwaUzytkownika = daneUzytkownika[1];
            wczytanyUzytkownik.hasloUzytkownika = daneUzytkownika[2];

            listaUzytkownikow.push_back(wczytanyUzytkownik);
            daneUzytkownika.clear();
        }
    }
    uzytkownicy.close();
}
void wczytajListeKontaktow(vector<Adresat> &listaAdresatow, int idZalogowanegoUzytkownika) {
    fstream adresaci;
    string wczytanaLinia;
    int wczytaneId;
    Adresat wczytanyAdresat;
    vector<string> daneAdresata;

    adresaci.open(nazwaPlikuZAdresatami.c_str(), ios::in);

    if(!adresaci.good()) {
        return;
    }

    adresaci.clear();
    adresaci.seekg(0, ios::beg);

    while (getline(adresaci, wczytanaLinia, separator)) {
        daneAdresata.push_back(wczytanaLinia);

        if (daneAdresata.size() >= 7) {
            wczytanyAdresat.idAdresata = atoi(daneAdresata[0].c_str());
            wczytaneId = atoi(daneAdresata[1].c_str());
            wczytanyAdresat.imie = daneAdresata[2];
            wczytanyAdresat.nazwisko = daneAdresata[3];
            wczytanyAdresat.numerTelefonu = daneAdresata[4];
            wczytanyAdresat.e_mail = daneAdresata[5];
            wczytanyAdresat.adres = daneAdresata[6];

            if (wczytaneId == idZalogowanegoUzytkownika) {
                listaAdresatow.push_back(wczytanyAdresat);
            }
            daneAdresata.clear();
        }
    }
    adresaci.close();
}
void zapiszNowegoAdresataDoPliku(Adresat adresatDoZapisania, int idZalogowanegoUzytkownika) {
    fstream adresaci;

    adresaci.open(nazwaPlikuZAdresatami.c_str(), ios::out | ios::app);

    adresaci << adresatDoZapisania.idAdresata << separator;
    adresaci << idZalogowanegoUzytkownika << separator;
    adresaci << adresatDoZapisania.imie << separator;
    adresaci << adresatDoZapisania.nazwisko << separator;
    adresaci << adresatDoZapisania.numerTelefonu << separator;
    adresaci << adresatDoZapisania.e_mail << separator;
    adresaci << adresatDoZapisania.adres << separator;
    adresaci << endl;

    adresaci.close();
}
void dodajAdresata(vector<Adresat> &listaAdresatow, int idZalogowanegoUzytkownika) {
    Adresat nowyAdresat;

    system("cls");
    nowyAdresat.idAdresata = wyznaczIdOstatniegoAdresataWPliku() + 1;
    cout << "Podaj imi\251:" << endl;
    nowyAdresat.imie = wczytajLinie();
    cout << "Podaj nazwisko:" << endl;
    nowyAdresat.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu:" << endl;
    nowyAdresat.numerTelefonu = wczytajLinie();
    cout << "Podaj adres e-mail:" << endl;
    nowyAdresat.e_mail = wczytajLinie();
    cout << "Podaj adres zamieszkania:" << endl;
    nowyAdresat.adres = wczytajLinie();

    listaAdresatow.push_back(nowyAdresat);
    zapiszNowegoAdresataDoPliku(nowyAdresat, idZalogowanegoUzytkownika);

    cout << "Kontakt zosta\210 dodany!" << endl;
    Sleep(1500);
}
void wyswietlAdresata(Adresat adresatDoWyswietlenia) {
    cout << adresatDoWyswietlenia.idAdresata << endl;
    cout << adresatDoWyswietlenia.imie << " ";
    cout << adresatDoWyswietlenia.nazwisko << endl;
    cout << adresatDoWyswietlenia.numerTelefonu << endl;
    cout << adresatDoWyswietlenia.e_mail << endl;
    cout << adresatDoWyswietlenia.adres << endl << endl;
}
void wyszukajPoImieniu(vector<Adresat> &listaAdresatow) {
    string wczytaneImie = "";
    int iloscZnalezionychKontaktow = 0;
    bool czyChceszWyszukacPonownie = true;

    do {
        system("cls");
        cout << "Z jakim imieniem chcesz wy\230wietli\206 kontakty?" << endl;
        cin.clear();
        cin.sync();
        cin >> wczytaneImie;
        zamienPierwszaLitereNaDuzaAReszteNaMala(wczytaneImie);
        cout << endl;

        for (int i = 0; i < listaAdresatow.size(); i++) {
            if (listaAdresatow[i].imie == wczytaneImie) {
                wyswietlAdresata(listaAdresatow[i]);
                iloscZnalezionychKontaktow++;
            }
        }
        if (iloscZnalezionychKontaktow == 0) {
            cout << "Nie znaleziono kontakt\242w, zawieraj\245cych podane imi\251! :-(" << endl << endl;
        }
        cout << "Czy chcesz wyszukac ponownie?" << endl;
        czyChceszWyszukacPonownie = zapytajOMozliwoscPonownegoWykonania();
        iloscZnalezionychKontaktow = 0;
    } while (czyChceszWyszukacPonownie);
    wyswietlOpcjePowrotuDoMenuGlownego();
}
void wyszukajPoNazwisku(vector<Adresat> &listaAdresatow) {
    string wczytaneNazwisko = "";
    int iloscZnalezionychKontaktow = 0;
    bool czyChceszWyszukacPonownie = true;

    do {
        system("cls");
        cout << "Z jakim imieniem chcesz wy\230wietli\206 kontakty?" << endl;
        cin.clear();
        cin.sync();
        cin >> wczytaneNazwisko;
        zamienPierwszaLitereNaDuzaAReszteNaMala(wczytaneNazwisko);
        cout << endl;

        for (int i = 0; i < listaAdresatow.size(); i++) {
            if (listaAdresatow[i].nazwisko == wczytaneNazwisko) {
                wyswietlAdresata(listaAdresatow[i]);
                iloscZnalezionychKontaktow++;
            }
        }
        if (iloscZnalezionychKontaktow == 0) {
            cout << "Nie znaleziono kontakt\242w, zawieraj\245cych podane nazwisko! :-(" << endl << endl;
        }
        cout << "Czy chcesz wyszuka\206 ponownie?" << endl;
        czyChceszWyszukacPonownie = zapytajOMozliwoscPonownegoWykonania();
        iloscZnalezionychKontaktow = 0;
    } while (czyChceszWyszukacPonownie);
    wyswietlOpcjePowrotuDoMenuGlownego();
}
void wyswietlWszystkichAdresatow(vector<Adresat> &listaAdresatow) {
    system("cls");
    for (int i = 0; i < listaAdresatow.size(); i++) {
        wyswietlAdresata(listaAdresatow[i]);
    }
    wyswietlOpcjePowrotuDoMenuGlownego();
}
bool sprawdzCzyDotyczyAdresata (vector<int> listaIdAdresatow, int idWczytanegoAdresata) {
    for (int i = 0; i < listaIdAdresatow.size(); i++) {
        if (listaIdAdresatow[i] == idWczytanegoAdresata) {
            return true;
        }
    }
    return false;
}
void aktualizujPlikPoUsunieciu(vector<int> listaIdAdresatowDoUsuniecia) {
    fstream adresaci, adresaciTymczasowy;
    string wczytanaLinia, pozostaloscZaWczytanymAdresatem;
    int idWczytanegoAdresata;
    vector<string> daneAdresata;

    adresaci.open(nazwaPlikuZAdresatami.c_str(), ios::in);
    adresaciTymczasowy.open(nazwaPlikuTymczasowego.c_str(), ios::out);

    if (adresaci.good()) {
        adresaci.clear();
        adresaci.seekg(0, ios::beg);

        while (getline(adresaci, wczytanaLinia, separator)) {
            daneAdresata.push_back(wczytanaLinia);

            if (daneAdresata.size() >= 7) {
                getline(adresaci, pozostaloscZaWczytanymAdresatem);
                idWczytanegoAdresata = atoi(daneAdresata[0].c_str());
                if (!sprawdzCzyDotyczyAdresata(listaIdAdresatowDoUsuniecia, idWczytanegoAdresata)) {
                    adresaciTymczasowy << daneAdresata[0] << separator;
                    adresaciTymczasowy << daneAdresata[1] << separator;
                    adresaciTymczasowy << daneAdresata[2] << separator;
                    adresaciTymczasowy << daneAdresata[3] << separator;
                    adresaciTymczasowy << daneAdresata[4] << separator;
                    adresaciTymczasowy << daneAdresata[5] << separator;
                    adresaciTymczasowy << daneAdresata[6] << separator;
                    adresaciTymczasowy << endl;
                }
                daneAdresata.clear();
            }
        }
    }
    adresaci.close();
    adresaciTymczasowy.close();
    remove(nazwaPlikuZAdresatami.c_str());
    rename(nazwaPlikuTymczasowego.c_str(), nazwaPlikuZAdresatami.c_str());
}
void usunPojedynczegoAdresata(vector<Adresat> &listaAdresatow) {
    int idAdresataDoUsuniecia;
    bool czyChceszUsunacKolejnegoAdresata = true;
    bool czyZnalezionoAdresata;
    vector<int> listaIdAdresatowDoUsuniecia;

    do {
        czyZnalezionoAdresata = false;
        system("cls");
        cout << "Podaj ID adresata, kt\242rego chcesz usun\245\206:" << endl;
        cin.clear();
        cin.sync();
        cin >> idAdresataDoUsuniecia;

        if(cin.fail()) {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        } else {
            for (int i = 0; i < listaAdresatow.size(); i++) {
                if (listaAdresatow[i].idAdresata == idAdresataDoUsuniecia) {
                    system("cls");
                    czyZnalezionoAdresata = true;
                    cout << "Adresat, kt\242rego chcesz usun\245\206 to:" << endl << endl;
                    wyswietlAdresata(listaAdresatow[i]);
                    if (poprosOPotwierdzenie()) {
                        listaIdAdresatowDoUsuniecia.push_back(idAdresataDoUsuniecia);
                        listaAdresatow.erase(listaAdresatow.begin() + i);
                        cout << endl << "Adresat zosta\210 usuni\251ty!" << endl << endl;
                        Sleep(1500);
                    } else {
                        cout << "Anulowano usuwanie adresata!" << endl << endl;
                        Sleep(1500);
                    }
                }
            }
            if (!czyZnalezionoAdresata) {
                cout << "Adresat o podanym ID nie istnieje!" << endl << endl;
                Sleep(1500);
            }
            cout << "Czy chcesz usun\245\206 kolejnego adresata?" << endl;
            czyChceszUsunacKolejnegoAdresata = zapytajOMozliwoscPonownegoWykonania();
        }
    } while(czyChceszUsunacKolejnegoAdresata);
    aktualizujPlikPoUsunieciu(listaIdAdresatowDoUsuniecia);
    wyswietlOpcjePowrotuDoMenuUsuwania();
}
void usunAdresata(vector<Adresat> &listaAdresatow) {
    int wybranaOpcja;
    vector<int> listaIdAdresatowDoUsuniecia;

    do {
        wyswietlMenuUsuwania();
        cin.clear();
        cin.sync();
        cin >> wybranaOpcja;
        if(cin.fail()) {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        } else {
            switch (wybranaOpcja) {
            case 1:
                usunPojedynczegoAdresata(listaAdresatow);
                break;
            case 2:
                if(poprosOPotwierdzenie()) {
                    for (int i = 0; i < listaAdresatow.size(); i++) {
                        listaIdAdresatowDoUsuniecia.push_back(listaAdresatow[i].idAdresata);
                    }
                    listaAdresatow.clear();
                    aktualizujPlikPoUsunieciu(listaIdAdresatowDoUsuniecia);
                    cout << endl << "Ksi\245\276ka adresowa zosta\210a wyczyszczona!" << endl << endl;
                    wyswietlOpcjePowrotuDoMenuGlownego();
                    return;
                } else {
                    cout << "Anulowano czyszczenie ksi\245\276ki!" << endl << endl;
                    wyswietlOpcjePowrotuDoMenuGlownego();
                    return;
                }
            case 9:
                wyswietlOpcjePowrotuDoMenuGlownego();
                return;
            default:
                cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
                Sleep(1500);
            }
        }
    } while(true);
}
void aktualizujPlikPoEdycji (vector<Adresat> &listaAdresatow, vector<int> listaIdAdresatowDoEdycji) {
    fstream adresaci, adresaciTymczasowy;
    string wczytanyElement, pozostaloscZaWczytanymAdresatem;
    int idWczytanegoAdresata;
    vector<string> daneAdresata;

    adresaci.open(nazwaPlikuZAdresatami.c_str(), ios::in);
    adresaciTymczasowy.open(nazwaPlikuTymczasowego.c_str(), ios::out);

    if (adresaci.good()) {
        adresaci.clear();
        adresaci.seekg(0, ios::beg);

        while (getline(adresaci, wczytanyElement, separator)) {
            daneAdresata.push_back(wczytanyElement);

            if (daneAdresata.size() >= 7) {
                getline(adresaci, pozostaloscZaWczytanymAdresatem);
                idWczytanegoAdresata = atoi(daneAdresata[0].c_str());
                if (!sprawdzCzyDotyczyAdresata(listaIdAdresatowDoEdycji, idWczytanegoAdresata)) {
                    adresaciTymczasowy << daneAdresata[0] << separator;
                    adresaciTymczasowy << daneAdresata[1] << separator;
                    adresaciTymczasowy << daneAdresata[2] << separator;
                    adresaciTymczasowy << daneAdresata[3] << separator;
                    adresaciTymczasowy << daneAdresata[4] << separator;
                    adresaciTymczasowy << daneAdresata[5] << separator;
                    adresaciTymczasowy << daneAdresata[6] << separator;
                    adresaciTymczasowy << endl;
                } else {
                    for (int j = 0; j < listaAdresatow.size(); j++) {
                        if (idWczytanegoAdresata == listaAdresatow[j].idAdresata) {
                            adresaciTymczasowy << listaAdresatow[j].idAdresata << separator;
                            adresaciTymczasowy << daneAdresata[1] << separator;
                            adresaciTymczasowy << listaAdresatow[j].imie << separator;
                            adresaciTymczasowy << listaAdresatow[j].nazwisko << separator;
                            adresaciTymczasowy << listaAdresatow[j].numerTelefonu << separator;
                            adresaciTymczasowy << listaAdresatow[j].e_mail << separator;
                            adresaciTymczasowy << listaAdresatow[j].adres << separator;
                            adresaciTymczasowy << endl;
                            break;
                        }
                    }
                }
                daneAdresata.clear();
            }
        }
    }
    adresaci.close();
    adresaciTymczasowy.close();
    remove(nazwaPlikuZAdresatami.c_str());
    rename(nazwaPlikuTymczasowego.c_str(), nazwaPlikuZAdresatami.c_str());

}
void edycjaWybranegoAdresata(Adresat &edytowanyAdresat) {
    int wybranaOpcja;
    string wczytanyElement = "";
    bool czyChceszEdytowacKolejnyElement = true;

    do {
        system("cls");
        cout << "Adresat, kt\242rego chcesz edytowa\206 to:" << endl << endl;
        wyswietlAdresata(edytowanyAdresat);
        wyswietlMenuEdycji();
        cin.clear();
        cin.sync();
        cin >> wybranaOpcja;
        if(cin.fail()) {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);

        } else {
            system("cls");
            switch(wybranaOpcja) {
            case 1:
                cout << "Podaj nowe imie\251:" << endl;
                cin >> wczytanyElement;
                zamienPierwszaLitereNaDuzaAReszteNaMala(wczytanyElement);
                edytowanyAdresat.imie = wczytanyElement;
                cout << "Imi\251 zosta\210o zaktualizowane!" << endl;
                Sleep(1500);
                break;
            case 2:
                cout << "Podaj nowe nazwisko:" << endl;
                cin >> wczytanyElement;
                zamienPierwszaLitereNaDuzaAReszteNaMala(wczytanyElement);
                edytowanyAdresat.nazwisko = wczytanyElement;
                cout << "Nazwisko zosta\210o zaktualizowane!" << endl;
                Sleep(1500);
                break;
            case 3:
                cout << "Podaj nowy numer telefonu:" << endl;
                cin >> wczytanyElement;
                zamienPierwszaLitereNaDuzaAReszteNaMala(wczytanyElement);
                edytowanyAdresat.numerTelefonu = wczytanyElement;
                cout << "Numer telefonu zosta\210 zaktualizowany!" << endl;
                Sleep(1500);
                break;
            case 4:
                cout << "Podaj nowy adres e-mail:" << endl;
                cin >> wczytanyElement;
                zamienPierwszaLitereNaDuzaAReszteNaMala(wczytanyElement);
                edytowanyAdresat.e_mail = wczytanyElement;
                cout << "Adres e-mail zosta\210 zaktualizowany!" << endl;
                Sleep(1500);
                break;
            case 5:
                cout << "Podaj nowy adres zamieszkania:" << endl;
                cin >> wczytanyElement;
                zamienPierwszaLitereNaDuzaAReszteNaMala(wczytanyElement);
                edytowanyAdresat.adres = wczytanyElement;
                cout << "Adres zamieszkania zosta\210 zaktualizowany!" << endl;
                Sleep(1500);
                break;
            case 0:
                cout << "Anulowano edycje adresata!" << endl;
                Sleep(1500);
                return;
            default:
                cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
                Sleep(1500);
            }
            cout << endl << "Czy chcesz edytowa\206 kolejny element?" << endl;
            czyChceszEdytowacKolejnyElement = zapytajOMozliwoscPonownegoWykonania();
        }
    } while(czyChceszEdytowacKolejnyElement);
}
void edytujAdresata (vector<Adresat> &listaAdresatow, char separator) {
    int idAdresataDoEdycji;
    bool czyChceszEdytowacKolejnegoAdresata = true;
    bool czyZnalezionoAdresata = false;
    vector<int>listaIdAdresatowDoEdycji;

    do {
        czyZnalezionoAdresata = false;
        system("cls");
        cout << "Podaj ID adresata, kt\242rego chcesz edytowa\206:" << endl;
        cin.clear();
        cin.sync();
        cin >> idAdresataDoEdycji;
        if(cin.fail()) {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        } else {
            for (int i = 0; i < listaAdresatow.size(); i++) {
                if (listaAdresatow[i].idAdresata == idAdresataDoEdycji) {
                    czyZnalezionoAdresata = true;
                    listaIdAdresatowDoEdycji.push_back(idAdresataDoEdycji);
                    edycjaWybranegoAdresata(listaAdresatow[i]);
                }
            }
            if (!czyZnalezionoAdresata) {
                cout << "Adresat o podanym ID nie istnieje!" << endl << endl;
                Sleep(1500);
            }
            cout << "Czy chcesz edytowa\206 kolejnego adresata?" << endl;
            czyChceszEdytowacKolejnegoAdresata = zapytajOMozliwoscPonownegoWykonania();
        }
    } while(czyChceszEdytowacKolejnegoAdresata);
    aktualizujPlikPoEdycji(listaAdresatow, listaIdAdresatowDoEdycji);
    wyswietlOpcjePowrotuDoMenuGlownego();
}
void aktualizujPlikPoZmianieHasla(vector<Uzytkownik> &listaUzytkownikow, int iloscUzytkownikow) {
    fstream uzytkownicy;

    uzytkownicy.open(nazwaPlikuZUzytkownikami.c_str(), ios::out);
    for (int i = 0; i < iloscUzytkownikow; i++) {
        uzytkownicy << listaUzytkownikow[i].idUzytkownika << separator;
        uzytkownicy << listaUzytkownikow[i].nazwaUzytkownika << separator;
        uzytkownicy << listaUzytkownikow[i].hasloUzytkownika << separator;
        uzytkownicy << endl;
    }
    uzytkownicy.close();
}
void zmienHaslo(int idZalogowanegoUzytkownika) {
    string noweHaslo, noweHasloDrugiRaz;
    int iloscUzytkownikow;
    vector<Uzytkownik> listaUzytkownikow;

    wczytajListeUzytkownikow(listaUzytkownikow);
    iloscUzytkownikow = listaUzytkownikow.size();

    for (int i = 0; i < iloscUzytkownikow; i++) {
        if (listaUzytkownikow[i].idUzytkownika == idZalogowanegoUzytkownika) {
            system("cls");
            cout << "ZMIANA HASLA:" << endl << endl;
            cout << "Podaj nowe haslo:" << endl;
            cin.clear();
            cin.sync();
            cin >> noweHaslo;
            cout << endl << "Powtorz nowe haslo:" << endl;
            cin.clear();
            cin.sync();
            cin >> noweHasloDrugiRaz;
            if (noweHaslo == noweHasloDrugiRaz) {
                listaUzytkownikow[i].hasloUzytkownika = noweHaslo;
                aktualizujPlikPoZmianieHasla(listaUzytkownikow, iloscUzytkownikow);
                cout << "Haslo zostalo zmienione" << endl;
            } else {
                cout << "Podane hasla nie sa jednakowe!" << endl << endl;
            }
            break;
        }
    }
    wyswietlOpcjePowrotuDoMenuGlownego();
}
int otworzMenuGlowne(int idZalogowanegoUzytkownika) {
    int wybranaOpcja;
    vector<Adresat> listaAdresatow;

    wczytajListeKontaktow(listaAdresatow, idZalogowanegoUzytkownika);

    do {
        wyswietlMenuGlowne();
        cin.clear();
        cin.sync();
        cin >> wybranaOpcja;
        if(cin.fail()) {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        } else {
            switch (wybranaOpcja) {
            case 1:
                dodajAdresata(listaAdresatow, idZalogowanegoUzytkownika);
                break;
            case 2:
                if (listaAdresatow.empty()) {
                    wyswietlInformacjeOPustejKsiazceAdresowej();
                } else {
                    wyszukajPoImieniu(listaAdresatow);
                }
                break;
            case 3:
                if (listaAdresatow.empty()) {
                    wyswietlInformacjeOPustejKsiazceAdresowej();
                } else {
                    wyszukajPoNazwisku(listaAdresatow);
                }
                break;
            case 4:
                if (listaAdresatow.empty()) {
                    wyswietlInformacjeOPustejKsiazceAdresowej();
                } else {
                    wyswietlWszystkichAdresatow(listaAdresatow);
                }
                break;
            case 5:
                if (listaAdresatow.empty()) {
                    wyswietlInformacjeOPustejKsiazceAdresowej();
                } else {
                    usunAdresata(listaAdresatow);
                }
                break;
            case 6:
                if (listaAdresatow.empty()) {
                    wyswietlInformacjeOPustejKsiazceAdresowej();
                } else {
                    edytujAdresata(listaAdresatow, separator);
                }
                break;
            case 7:
                zmienHaslo(idZalogowanegoUzytkownika);
                break;
            case 9:
                break;
            case 0:
                wyswietlInformacjeOWylogowaniu();
                return 0;
            default:
                cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
                Sleep(1500);
            }
        }
    } while(true);
}
int zalogujUzytkownika(vector<Uzytkownik> &listaUzytkownikow) {
    string nazwa = "", haslo = "";
    int iloscUzytkownikow = listaUzytkownikow.size();

    system("cls");
    cout << "LOGOWANIE:" << endl;
    cout << "Podaj swoj login:" << endl;
    cin.clear();
    cin.sync();
    cin >> nazwa;

    for(int i = 0; i < iloscUzytkownikow; i++) {
        if (listaUzytkownikow[i].nazwaUzytkownika == nazwa) {
            for (int j = 0; j < 3; j++) {
                cout << "Podaj haslo:" << endl;
                cin.clear();
                cin.sync();
                cin >> haslo;
                if (listaUzytkownikow[i].hasloUzytkownika == haslo) {
                    cout << "Zalogowano pomyslnie. " << endl;
                    Sleep(1500);
                    return listaUzytkownikow[i].idUzytkownika;
                } else {
                    cout << "Podano niepoprawne haslo. Sprobuj jeszcze raz! (pozosta³o " << 2 - j << " prob)" << endl << endl;
                    Sleep(500);
                }
            }
            cout << "Dostep zablokowany!" << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "Uzytkownik z podanym loginem nie istnieje!" << endl;
    Sleep(1500);
    return 0;
}
void zapiszUzytkownikaDoPliku(Uzytkownik uzytkownikDoZapisania) {
    fstream uzytkownicy;

    uzytkownicy.open(nazwaPlikuZUzytkownikami.c_str(), ios::out | ios::app);

    uzytkownicy << uzytkownikDoZapisania.idUzytkownika << separator;
    uzytkownicy << uzytkownikDoZapisania.nazwaUzytkownika << separator;
    uzytkownicy << uzytkownikDoZapisania.hasloUzytkownika << separator;
    uzytkownicy << endl;

    uzytkownicy.close();
}
void zarejestrujUzytkownika(vector<Uzytkownik> &listaUzytkownikow) {
    string nazwa, haslo;
    int iloscUzytkownikow = listaUzytkownikow.size();
    Uzytkownik nowyUzytkownik;

    system("cls");
    cout << "REJESTRACJA:" << endl;
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin.clear();
    cin.sync();
    cin >> nazwa;

    for (int i = 0; i < iloscUzytkownikow; i++) {
        if (listaUzytkownikow[i].nazwaUzytkownika == nazwa) {
            cout << "Uzytkownik o podanym loginem juz istnieje! Wpisz inna nazwe uzytkownika:" << endl;
            cin.clear();
            cin.sync();
            cin >> nazwa;
            i = -1;
        }
    }
    cout << "Podaj haslo:" << endl;
    cin.clear();
    cin.sync();
    cin >> haslo;
    nowyUzytkownik.nazwaUzytkownika = nazwa;
    nowyUzytkownik.hasloUzytkownika = haslo;
    if (iloscUzytkownikow == 0) {
        nowyUzytkownik.idUzytkownika = 1;
    } else {
        nowyUzytkownik.idUzytkownika = listaUzytkownikow[iloscUzytkownikow - 1].idUzytkownika + 1;
    }
    zapiszUzytkownikaDoPliku(nowyUzytkownik);
    listaUzytkownikow.push_back(nowyUzytkownik);
    cout << "Konto zostalo zalozone!" << endl;
    Sleep(1500);
}
int otworzPanelLogowania() {
    vector<Uzytkownik> listaUzytkownikow;
    int wybranaOpcja;

    wczytajListeUzytkownikow(listaUzytkownikow);

    do {
        wyswietlMenuLogowania();
        cin.clear();
        cin.sync();
        cin >> wybranaOpcja;

        if(cin.fail()) {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        } else {
            switch (wybranaOpcja) {
            case 1:
                return zalogujUzytkownika(listaUzytkownikow);
            case 2:
                zarejestrujUzytkownika(listaUzytkownikow);
                break;

            case 0:
                exit(0);
            default:
                cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
                Sleep(1500);
            }
        }
    } while(true);
}
int main() {
    int idZalogowanegoUzytkownika = 0;
    wyswietlIntro();
    do {
        idZalogowanegoUzytkownika = otworzPanelLogowania();
        if (idZalogowanegoUzytkownika != 0) {
            idZalogowanegoUzytkownika = otworzMenuGlowne(idZalogowanegoUzytkownika);
        }
    } while(true);
}
