#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

struct Adresat {
    string imie = "", nazwisko = "", e_mail = "", adres = "", numerTelefonu = "";
    int idUzytkownika = 0;
};

void wyswietlMenuGlowne() {
    system("cls");
    cout << "KSIAZKA ADRESOWA v2.0" << endl << endl;
    cout << "MENU GLOWNE:" << endl;
    cout << "1. Dodaj adresata." << endl;
    cout << "2. Wyszukaj po imieniu." << endl;
    cout << "3. Wyszukaj po nazwisku." << endl;
    cout << "4. Wy\230wietl wszystkich adresat\242w." << endl;
    cout << "5. Usu\344 adresata." << endl;
    cout << "6. Edytuj adresata." << endl;
    cout << "9. Zako\344cz program." << endl;
    cout << "Tw\242j wyb\242r:" << endl;
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

void wyswietlMenuUsuwania() {
    system("cls");
    cout << "Wybierz opcj\251 usuwania:" << endl;
    cout << "1. Usu\344 pojedy\344czy kontakt." << endl;
    cout << "2. Usu\344 wszystkie kontakty." << endl;
    cout << "9. Powr\242t." << endl;
}

void wyswietlMenuEdycji() {
    cout << endl << "Wybierz element, kt\242ry chcesz edytowa\206:" << endl;
    cout << "1. Imi\251." << endl;
    cout << "2. Nazwisko." << endl;
    cout << "3. Numer telefonu." << endl;
    cout << "4. E-mail." << endl;
    cout << "5. Adres." << endl;
    cout << "9. Powr\242t." << endl;
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

void wczytajListeKontaktow(vector<Adresat> &listaAdresatow, int &IdOstatniegoUzytkownika, char separator) {
    fstream ksiazkaAdresowa;
    string wczytanaLinia;
    Adresat wczytanyAdresat;
    vector<string> daneAdresata;

    ksiazkaAdresowa.open("ksiazkaAdresowa.txt", ios::in);

    if(ksiazkaAdresowa.good() == false) {
        return;
    }

    ksiazkaAdresowa.clear();
    ksiazkaAdresowa.seekg(0, ios::beg);

    while (getline(ksiazkaAdresowa, wczytanaLinia, separator)) {
        daneAdresata.push_back(wczytanaLinia);

        if (daneAdresata.size() >= 6) {
            wczytanyAdresat.idUzytkownika = atoi(daneAdresata[0].c_str());
            wczytanyAdresat.imie = daneAdresata[1];
            wczytanyAdresat.nazwisko = daneAdresata[2];
            wczytanyAdresat.numerTelefonu = daneAdresata[3];
            wczytanyAdresat.e_mail = daneAdresata[4];
            wczytanyAdresat.adres = daneAdresata[5];

            listaAdresatow.push_back(wczytanyAdresat);
            IdOstatniegoUzytkownika = wczytanyAdresat.idUzytkownika;
            daneAdresata.clear();
        }
    }
    ksiazkaAdresowa.close();
}

string wczytajLinie() {
    string linia = "";
    cin.clear();
    cin.sync();
    getline(cin, linia);
    return linia;
}

void zapiszNowegoAdresataDoPliku(Adresat adresatDoZapisania, char separator) {
    fstream ksiazkaAdresowa;

    ksiazkaAdresowa.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    ksiazkaAdresowa << adresatDoZapisania.idUzytkownika << separator;
    ksiazkaAdresowa << adresatDoZapisania.imie << separator;
    ksiazkaAdresowa << adresatDoZapisania.nazwisko << separator;
    ksiazkaAdresowa << adresatDoZapisania.numerTelefonu << separator;
    ksiazkaAdresowa << adresatDoZapisania.e_mail << separator;
    ksiazkaAdresowa << adresatDoZapisania.adres << separator;
    ksiazkaAdresowa << endl;

    ksiazkaAdresowa.close();
}

void dodajAdresata(vector<Adresat> &listaAdresatow, int &IdOstatniegoUzytkownika, char separator) {
    Adresat nowyAdresat;

    system("cls");
    nowyAdresat.idUzytkownika = IdOstatniegoUzytkownika + 1;
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
    zapiszNowegoAdresataDoPliku(nowyAdresat, separator);
    IdOstatniegoUzytkownika++;

    cout << "Kontakt zosta\210 dodany!" << endl;
    Sleep(1500);
}

void wyswietlAdresata(Adresat adresatDoWyswietlenia) {
    cout << adresatDoWyswietlenia.idUzytkownika << endl;
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

void aktualizujPlik(vector<Adresat> &listaAdresatow, char separator) {
    fstream ksiazkaAdresowa;

    ksiazkaAdresowa.open("ksiazkaAdresowa.txt", ios::out);

    for (int i = 0; i < listaAdresatow.size(); i++) {
        ksiazkaAdresowa << listaAdresatow[i].idUzytkownika << separator;
        ksiazkaAdresowa << listaAdresatow[i].imie << separator;
        ksiazkaAdresowa << listaAdresatow[i].nazwisko << separator;
        ksiazkaAdresowa << listaAdresatow[i].numerTelefonu << separator;
        ksiazkaAdresowa << listaAdresatow[i].e_mail << separator;
        ksiazkaAdresowa << listaAdresatow[i].adres << separator;
        ksiazkaAdresowa << endl;
    }

    ksiazkaAdresowa.close();
}

void usunPojedynczegoAdresata(vector<Adresat> &listaAdresatow, char separator) {
    int idAdresataDoUsuniecia;
    bool czyChceszUsunacKolejnegoAdresata = true;
    bool czyZnalezionoAdresata;

    do {
        czyZnalezionoAdresata = false;
        system("cls");
        cout << "Podaj ID adresata, kt\242rego chcesz usun\245\206:" << endl;
        cin.clear();
        cin.sync();
        cin >> idAdresataDoUsuniecia;
        if(!(cin.fail())) {
            for (int i = 0; i < listaAdresatow.size(); i++) {
                if (listaAdresatow[i].idUzytkownika == idAdresataDoUsuniecia) {
                    system("cls");
                    czyZnalezionoAdresata = true;
                    cout << "Adresat, kt\242rego chcesz usun\245\206 to:" << endl << endl;
                    wyswietlAdresata(listaAdresatow[i]);
                    if (poprosOPotwierdzenie()) {
                        listaAdresatow.erase(listaAdresatow.begin() + i);
                        aktualizujPlik(listaAdresatow, separator);
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
        } else {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        }
    } while(czyChceszUsunacKolejnegoAdresata);
    wyswietlOpcjePowrotuDoMenuUsuwania();
}

void usunAdresata(vector<Adresat> &listaAdresatow, int &IdOstatniegoUzytkownika, char separator) {
    int wybranaOpcja;
    int iloscUzytkownikow;

    do {
        wyswietlMenuUsuwania();
        cin.clear();
        cin.sync();
        cin >> wybranaOpcja;
        if(!(cin.fail())) {
            switch (wybranaOpcja) {
            case 1:
                usunPojedynczegoAdresata(listaAdresatow, separator);
                iloscUzytkownikow = listaAdresatow.size();
                IdOstatniegoUzytkownika = listaAdresatow[iloscUzytkownikow - 1].idUzytkownika;
                break;
            case 2:
                if(poprosOPotwierdzenie()) {
                    listaAdresatow.clear();
                    aktualizujPlik(listaAdresatow, separator);
                    IdOstatniegoUzytkownika = listaAdresatow.size();
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
        } else {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        }
    } while(true);
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
        if(!(cin.fail())) {
            system("cls");
            switch(wybranaOpcja) {
            case 1:
                cout << "Podaj nowe imie\251:" << endl;
                cin >> wczytanyElement;
                edytowanyAdresat.imie = wczytanyElement;
                cout << "Imi\251 zosta\210o zaktualizowane!" << endl;
                Sleep(1500);
                break;
            case 2:
                cout << "Podaj nowe nazwisko:" << endl;
                cin >> wczytanyElement;
                edytowanyAdresat.nazwisko = wczytanyElement;
                cout << "Nazwisko zosta\210o zaktualizowane!" << endl;
                Sleep(1500);
                break;
            case 3:
                cout << "Podaj nowy numer telefonu:" << endl;
                cin >> wczytanyElement;
                edytowanyAdresat.numerTelefonu = wczytanyElement;
                cout << "Numer telefonu zosta\210 zaktualizowany!" << endl;
                Sleep(1500);
                break;
            case 4:
                cout << "Podaj nowy adres e-mail:" << endl;
                cin >> wczytanyElement;
                edytowanyAdresat.e_mail = wczytanyElement;
                cout << "Adres e-mail zosta\210 zaktualizowany!" << endl;
                Sleep(1500);
                break;
            case 5:
                cout << "Podaj nowy adres zamieszkania:" << endl;
                cin >> wczytanyElement;
                edytowanyAdresat.adres = wczytanyElement;
                cout << "Adres zamieszkania zosta\210 zaktualizowany!" << endl;
                Sleep(1500);
                break;
            case 9:
                cout << "Anulowano edycje adresata!" << endl;
                Sleep(1500);
                return;
            default:
                cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
                Sleep(1500);
            }
            cout << endl << "Czy chcesz edytowa\206 kolejny elelemt?" << endl;
            czyChceszEdytowacKolejnyElement = zapytajOMozliwoscPonownegoWykonania();
        } else {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        }
    } while(czyChceszEdytowacKolejnyElement);
}

void edytujAdresata (vector<Adresat> &listaAdresatow, char separator) {
    int idAdresataDoEdycji;
    bool czyChceszEdytowacKolejnegoAdresata = true;
    bool czyZnalezionoAdresata = false;

    do {
        system("cls");
        cout << "Podaj ID adresata, kt\242rego chcesz edytowa\206:" << endl;
        cin.clear();
        cin.sync();
        cin >> idAdresataDoEdycji;
        if(!(cin.fail())) {
            for (int i = 0; i < listaAdresatow.size(); i++) {
                if (listaAdresatow[i].idUzytkownika == idAdresataDoEdycji) {
                    czyZnalezionoAdresata = true;
                    edycjaWybranegoAdresata(listaAdresatow[i]);
                    aktualizujPlik(listaAdresatow, separator);
                }
            }
            if (!czyZnalezionoAdresata) {
                cout << "Adresat o podanym ID nie istnieje!" << endl << endl;
                Sleep(1500);
            }
            cout << "Czy chcesz edytowa\206 kolejnego adresata?" << endl;
            czyChceszEdytowacKolejnegoAdresata = zapytajOMozliwoscPonownegoWykonania();
        } else {
            cout << endl << "Podano niepoprawn\245 warto\230\206! Wpisz jeszcze raz!" << endl;
            Sleep(1500);
        }
    } while(czyChceszEdytowacKolejnegoAdresata);
    wyswietlOpcjePowrotuDoMenuGlownego();
}

int main() {
    int IdOstatniegoUzytkownika = 0;
    int wybranaOpcja;
    char separator = '|';
    vector<Adresat> listaAdresatow;

    wczytajListeKontaktow(listaAdresatow, IdOstatniegoUzytkownika, separator);

    do {
        wyswietlMenuGlowne();
        cin.clear();
        cin.sync();
        cin >> wybranaOpcja;
        if(!(cin.fail())) {
            switch (wybranaOpcja) {
            case 1:
                dodajAdresata(listaAdresatow, IdOstatniegoUzytkownika, separator);
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
                    usunAdresata(listaAdresatow, IdOstatniegoUzytkownika, separator);
                }
                break;
            case 6:
                if (listaAdresatow.empty()) {
                    wyswietlInformacjeOPustejKsiazceAdresowej();
                } else {
                    edytujAdresata(listaAdresatow, separator);
                }
                break;
            case 9:
                exit(0);
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
