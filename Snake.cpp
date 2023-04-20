#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <fstream>
using namespace std;

enum kierunek { STOP = 0, LEWO, PRAWO, GORA, DOL };
kierunek kier;

class Snake
{
private:
    char poziom_trudnosci;
    bool koniec_gry;
    bool nast_poz;
    bool wygrana;
    int numer_poziomu;

    int wyjscie_x, wyjscie_y;

    int szerokosc;
    int wysokosc;
    char** mapa;
    int x, y, owoc_x, owoc_y, wynik;
    int ogon_x[100], ogon_y[100];
    int dlugosc_ogona;

public:

    Snake()
    {
        this->koniec_gry = false;
        this->nast_poz = false;
        this->wygrana = false;
        this->numer_poziomu = 1;
        this->wyjscie_x = 10;
        this->wyjscie_y = 39;
        this->szerokosc = 22;
        this->wysokosc = 40;
        this->mapa;
        this->x = szerokosc / 2;
        this->y = szerokosc / 2;
        this->owoc_x;
        this->owoc_y;
        this->wynik = 0;
        ogon_x[100], ogon_y[100];
        this->dlugosc_ogona = 0;
        kier = STOP;
    }

    void generator()
    {
        mapa = new char* [szerokosc];
        for (int i = 0; i < szerokosc; i++)
        {
            mapa[i] = new char[wysokosc];
        }
    }

    void ekran_startowy()
    {
        cout << "Witaj w grze Snake!" << endl;
        cout << "Sterowanie:\t\t"; cout << "Elementy planszy: " << endl;
        cout << "w - gora\t\t"; cout << "# - Sciana, na latwym poziomie trudnosci gracz zostaje przeniesiony na przeciwna strone mapy," << endl;
        cout << "a - lewo\t\t"; cout << "zachowujac kierunek poruszania sie. Na poziomie trudnym trafienie w nia konczy gre." << endl;
        cout << "s - dol\t\t"; cout << "\t@ - Przeszkoda, trafienie w nia konczy gre." << endl;
        cout << "d - prawo\t\t"; cout << "S - Glowa weza, s - ogon weza." << endl;
        cout << "p - pauza\t\t"; cout << "o - Owoc za jego zjedzenie gracz otrzymuje 10 punktow." << endl;
        cout << "l - wyjdz z gry\t\t"; cout << "E - Przejscie na nastepny poziom, pokazuje sie po zdobyciu 50 punktow na poziom." << endl;
        cout << "\t\t\tWyjscie ostatniego poziomu oznacza wygrana." << endl << endl;
        cout << "Wybierz poziom trudnosci [l/t(latwy/trudny)]:";
        cin >> poziom_trudnosci;
        system("cls");
    }

    void zwyciestwo()
    {
        system("cls");
        cout << "Wygrales!" << endl;
        cout << "Wynik: " << wynik << endl;
    }

    void porazka()
    {
        system("cls");
        cout << "Przegrales, sprobuj ponownie!" << endl;
        cout << "Poziom: " << numer_poziomu << endl;
        cout << "Wynik: " << wynik << endl;
    }

    void wczytaj_mape()
    {
        nast_poz = false;
        ifstream plik;
        switch (numer_poziomu)
        {
        case 1:
            plik.open("level1.txt");
            break;
        case 2:
            plik.open("level2.txt");
            break;
        case 3:
            plik.open("level3.txt");
            break;
        case 4:
            plik.open("level4.txt");
            break;
        case 5:
            plik.open("level5.txt");
            break;
        }
        for (int i = 0; i < szerokosc; i++)
        {
            for (int j = 0; j < wysokosc; j++)
                plik >> mapa[i][j];
        }
        plik.close();
    }

    void clear_screen()
    {
        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }

    void owoc()
    {
        int ox, oy;
        do
        {
            ox = rand() % (szerokosc - 1) + 1;
            oy = rand() % (wysokosc - 1) + 1;
        } while (mapa[ox][oy] != '1');
        owoc_x = ox;
        owoc_y = oy;
    }

    void elementy()
    {
        for (int i = 0; i < szerokosc; ++i)
        {
            for (int j = 0; j < wysokosc; ++j)
            {

                if (i == x && j == y)
                {
                    if (mapa[i][j] != '#')
                    {
                        mapa[i][j] = 'S';
                    }
                }
                else if (i == owoc_x && j == owoc_y)
                {
                    mapa[i][j] = 'o';
                }
                else if (mapa[i][j] == '#')
                {
                    mapa[i][j] = '#';
                }
                else if (mapa[i][j] == '@')
                {
                    mapa[i][j] == '@';
                }
                else
                {
                    mapa[i][j] = '1';
                }

                for (int k = 0; k < dlugosc_ogona; k++)
                {
                    if (ogon_x[k] == i && ogon_y[k] == j)
                    {
                        mapa[i][j] = 's';
                    }
                }
            }
        }

        for (int i = 0; i < szerokosc; ++i)
        {
            for (int j = 0; j < wysokosc; ++j)
            {
                if (i == (szerokosc - 1) || i == 0)
                {
                    mapa[i][j] = '#';
                }
                else if (j == (wysokosc - 1) || j == 0)
                {
                    mapa[i][j] = '#';
                }
            }
        }

        if (wynik - 50 * numer_poziomu >= 0)
        {
            mapa[wyjscie_x][wyjscie_y] = 'E';
        }
    }

    void plansza()
    {
        clear_screen();
        for (int i = 0; i < szerokosc; ++i)
        {
            for (int j = 0; j < wysokosc; ++j)
            {

                if (mapa[i][j] == '1')
                {
                    cout << ' ';
                }
                else
                {
                    cout << mapa[i][j];
                }

            }

            cout << endl;
        }

        cout << "Sterowanie: \t";   cout << "Wynik: " << wynik << endl;
        cout << "w - gora\t";       cout << "Poziom: " << numer_poziomu << endl;
        cout << "a - lewo\t";       cout << "Poziom trudnosci: ";
        if (poziom_trudnosci == 'l') cout << "latwy" << endl;
        else cout << "trudny" << endl;

        cout << "s - dol" << endl;
        cout << "d - prawo" << endl;
        cout << "p - pauza" << endl;
        cout << "l - wyjdz z gry" << endl;

    }

    void Input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                if (kier != PRAWO) kier = LEWO;
                break;
            case 'd':
                if (kier != LEWO) kier = PRAWO;
                break;
            case 'w':
                if (kier != DOL) kier = GORA;
                break;
            case 's':
                if (kier != GORA) kier = DOL;
                break;
            case 'p':
                kier = STOP;
                break;
            case 'l':
                koniec_gry = true;
                break;
            }
        }
    }

    void Zdarzenia()
    {
        int pop_x = ogon_x[0];
        int pop_y = ogon_y[0];
        int pop_2x, pop_2y;
        ogon_x[0] = x;
        ogon_y[0] = y;
        for (int i = 1; i < dlugosc_ogona; i++)
        {
            pop_2x = ogon_x[i];
            pop_2y = ogon_y[i];
            ogon_x[i] = pop_x;
            ogon_y[i] = pop_y;
            pop_x = pop_2x;
            pop_y = pop_2y;
        }

        switch (kier)
        {
        case LEWO:
            y--;
            break;
        case PRAWO:
            y++;
            break;
        case GORA:
            x--;
            break;
        case DOL:
            x++;
            break;
        default:
            break;
        }

        //uderzenie w œciane
        if (poziom_trudnosci == 't')
        {
            if (mapa[x][y] == '#' || mapa[x][y] == '@')
            {
                koniec_gry = true;
                cout << "Koniec gry!";
            }
        }

        //tryb ³atwy
        if (poziom_trudnosci == 'l')
        {
            if (x == szerokosc) x = 1; else if (x == 0) x = szerokosc - 1;
            if (y == wysokosc) y = 1; else if (y == 0) y = wysokosc - 1;
            if (mapa[x][y] == '@')
            {
                koniec_gry = true;
                cout << "Koniec gry!";
            }
        }

        //zjedzenie ogona
        for (int i = 0; i < dlugosc_ogona; i++)
        {
            if (ogon_x[i] == x && ogon_y[i] == y)
            {
                koniec_gry = true;
                cout << "Koniec gry!";
            }
        }

        if (x == owoc_x && y == owoc_y)
        {
            wynik += 10;
            dlugosc_ogona++;
            owoc();
        }

        if (x == wyjscie_x && y == wyjscie_y)
        {
            if (mapa[wyjscie_x][wyjscie_y] == 'E' && kier == PRAWO)
            {
                nast_poz = true;
                numer_poziomu++;
                y = 1;
            }

        }
        if (numer_poziomu == 6)
        {
            wygrana = true;
        }
    }



    void Rozgrywka()
    {
        ekran_startowy();
        generator();
        wczytaj_mape();
        owoc();
        while (koniec_gry == false && wygrana == false)
        {
            elementy();
            plansza();
            Input();
            Zdarzenia();

            if (nast_poz == true)
            {
                wczytaj_mape();
                owoc();
            }

            if (kier == GORA || kier == DOL)
            {
                Sleep(40);
            }
            else
            {
                Sleep(25);
            }
        }
        if (koniec_gry == true)
        {
            porazka();
        }
        if (wygrana == true)
        {
            zwyciestwo();
        }
    }

    ~Snake()
    {
        for (int i = 0; i < szerokosc; i++)
        {
            mapa[i] = new char[wysokosc];
        }
        delete[] mapa;
    }
};

int main(void)
{
    srand((unsigned)time(NULL));
    Snake waz;
    waz.Rozgrywka();

    return 0;
}