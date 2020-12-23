#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>
#include <vector>

class TaskOne
{
public:
    static constexpr int rad = 8, kol = 8;

    char brett[rad][kol]{};

    int hS = 0, sS = 0;

    bool spill = true, hvit = true, svart = true, sjakkMatt = false, sjakk2 = false;

    char blank = ' ', svartL = 'l', svartK = 'k', svartB = 'b', hvitL = 'L', hvitK = 'K', hvitB = 'B';
public:
    void sjakk()
    {
        nyttBrett();

        while (spill == true)
        {
            visBrett();

            if (hvit == true)
            {
                std::cout << "\nDet er hvit spiller sin tur.\n";

                spillSekvens(hvitB, hvitL, hvitK, svartB, svartL, svartK);
                hvit = false;
                svart = true;
            }
            else if (svart == true)
            {
                std::cout << "\nDet er svart spiller sin tur.\n";

                spillSekvens(svartB, svartL, svartK, hvitB, hvitL, hvitK);
                svart = false;
                hvit = true;
            }
        }
    }

    void spillSekvens(char dinB, char dinL, char dinK, char motB, char motL, char motK)
    {
        char svar[2]{}, svar2[2]{};
        bool trekk = false;

        int tall = 0, bokstav = 0, tall2 = 10, bokstav2 = 10;

        while (trekk == false)
        {
            sjakk2 = sjekkSjakk(svar, svar2, dinB, dinL, dinK, motB, motL, motK);

            sjakkMatt = sjekkSjakkMatt();

            if (hvit == true && sjakk2 == true)
            {
                std::cout << "Svart spiller er i sjakk\n";
            }
            else if (svart == true && sjakk2 == true)
            {
                std::cout << "Hvit spiller er i sjakk\n";
            }

            /* Velger spillerens brikke som ønskes å flyttes. */
            brikkeValg(svar, tall, bokstav, dinB, dinL, dinK);

            /* Sjekker om plassering spilleren ønsker å flytte sin brikke er motstanderens
            eller om den er blank. */
            plassering(svar2, tall2, bokstav2, motB, motL, motK);

            if (brett[tall][bokstav] == dinK)
            {
                trekk = flyttKonge(svar, svar2, dinB, dinL, dinK, motB, motL, motK);
            }
            else if (brett[tall][bokstav] == dinB)
            {
                trekk = flyttBonde(svar, svar2, dinB, dinL, dinK, motB, motL, motK);
            }
            else if (brett[tall][bokstav] == dinL)
            {
                trekk = flyttLoeper(svar, svar2, dinB, dinL, dinK, motB, motL, motK);
            }

            sjakk2 = sjekkSjakk(svar, svar2, dinB, dinL, dinK, motB, motL, motK);

            sjakkMatt = sjekkSjakkMatt();

            if (hvit == true && sjakk2 == true)
            {
                std::cout << "Svart spiller er i sjakk\n";
            }
            else if (svart == true && sjakk2 == true)
            {
                std::cout << "Hvit spiller er i sjakk\n";
            }
        }
    }

    void brikkeValg(char valg[], int &rad, int &kol, char dinB, char dinL, char dinK)
    {
        std::cout << "\nVennligst velg brikken som skal flyttes.\n";

        while (!(brett[rad][kol] == dinB || brett[rad][kol] == dinL || brett[rad][kol] == dinK))
        {
            valg[0] = blank;
            valg[1] = blank;

            while (!(valg[0] <= '8' && valg[0] >= '1' && valg[1] >= 'a' && valg[1] <= 'h'))
            {
                std::cin >> valg[0];
                std::cin >> valg[1];
                std::cin.ignore(32767, '\n');
                std::cin.clear();
            }
            
            charTilInt(valg, rad, kol); 
        }
    }

    void plassering(char valg2[], int &rad2, int &kol2, char motB, char motL, char motK)
    {
        rad2 = 10;
        kol2 = 10;

        std::cout << "Vennligst velg hvor du vil plassere brikken\n";

        while (!(brett[rad2][kol2] == motB || brett[rad2][kol2] == motL || brett[rad2][kol2] == motK ||
            brett[rad2][kol2] == blank))
        {
            valg2[0] = blank;
            valg2[1] = blank;

            while (!(valg2[0] <= '8' && valg2[0] >= '1' && valg2[1] >= 'a' && valg2[1] <= 'h'))
            {
                std::cin >> valg2[0];
                std::cin >> valg2[1];
                std::cin.ignore(32767, '\n');
                std::cin.clear();
            }
            
            charTilInt(valg2, rad2, kol2);
        }
    }

    bool flyttKonge(char fra[2], char til[2], char dinB, char dinL, char dinK, char motB, char motL, char motK)
    {
        int rad = 0, kol = 0, rad2 = 0, kol2 = 0;
        
        bool repeat = true;

        charTilInt(fra, rad, kol);
        charTilInt(til, rad2, kol2);

        while (repeat == true)
        {
            if (&brett[rad2][kol2] == &brett[rad][kol - 1] && brett[rad2][kol2] == blank || &brett[rad2][kol2] == &brett[rad][kol + 1] && brett[rad2][kol2] == blank ||
                &brett[rad2][kol2] == &brett[rad - 1][kol] && brett[rad2][kol2] == blank || &brett[rad2][kol2] == &brett[rad + 1][kol] && brett[rad2][kol2] == blank ||
                &brett[rad2][kol2] == &brett[rad + 1][kol + 1] && brett[rad2][kol2] == blank || &brett[rad2][kol2] == &brett[rad + 1][kol - 1] && brett[rad2][kol2] == blank ||
                &brett[rad2][kol2] == &brett[rad - 1][kol - 1] && brett[rad2][kol2] == blank || &brett[rad2][kol2] == &brett[rad - 1][kol + 1] && brett[rad2][kol2] == blank)
            {
                brett[rad2][kol2] = dinK;
                brett[rad][kol] = blank;

                repeat = false;

                return(true);
            }
            else if (brett[rad2][kol2] == motB || brett[rad2][kol2] == motK || brett[rad2][kol2] == motL)
            {
                brett[rad2][kol2] = dinK;
                brett[rad][kol] = blank;

                repeat = false;

                return(true);
            }
            else
            {
                plassering(til, rad2, kol2, motB, motL, motK);
            }
        }
    }

    bool flyttBonde(char fra[2], char til[2], char dinB, char dinL, char dinK, char motB, char motL, char motK)
    {
        int rad = 0, kol = 0, rad2 = 0, kol2 = 0;

        bool repeat = true;

        charTilInt(fra, rad, kol);
        charTilInt(til, rad2, kol2);

        while (repeat == true)
        {
            if (hvit == true)
            {
                if (&brett[rad2][kol2] == &brett[1 + 2][kol] && brett[rad2][kol2] == blank)
                {
                    brett[rad2][kol2] = dinB;
                    brett[rad][kol] = blank;

                    return(true);
                    repeat = false;
                }
                else if (&brett[rad2][kol2] == &brett[rad + 1][kol] && brett[rad2][kol2] == blank)
                {
                    brett[rad2][kol2] = dinB;
                    brett[rad][kol] = blank;

                    return(true);
                    repeat = false;
                }
                else if (brett[rad2][kol2] == brett[rad + 1][kol + 1] && brett[rad2][kol2] == motB || brett[rad2][kol2] == brett[rad + 1][kol - 1] && brett[rad2][kol2] == motB ||
                    brett[rad2][kol2] == brett[rad + 1][kol + 1] && brett[rad2][kol2] == motL || brett[rad2][kol2] == brett[rad + 1][kol - 1] && brett[rad2][kol2] == motL ||
                    brett[rad2][kol2] == brett[rad + 1][kol + 1] && brett[rad2][kol2] == motK || brett[rad2][kol2] == brett[rad + 1][kol - 1] && brett[rad2][kol2] == motK)
                {
                    brett[rad2][kol2] = dinB;
                    brett[rad][kol] = blank;

                    return(true);
                    repeat = false;
                }
                else
                {
                    plassering(til, rad2, kol2, motB, motL, motK);
                }
            }
            else if (svart == true)
            {
                if (&brett[rad2][kol2] == &brett[6 - 2][kol] && brett[rad2][kol2] == blank)
                {
                    brett[rad2][kol2] = dinB;
                    brett[rad][kol] = blank;

                    return(true);
                    repeat = false;
                }
                else if (&brett[rad2][kol2] == &brett[rad - 1][kol] && brett[rad2][kol2] == blank)
                {
                    brett[rad2][kol2] = dinB;
                    brett[rad][kol] = blank;

                    return(true);
                    repeat = false;
                }
                else if (brett[rad2][kol2] == brett[rad - 1][kol - 1] && brett[rad2][kol2] == motB || brett[rad2][kol2] == brett[rad - 1][kol + 1] && brett[rad2][kol2] == motB ||
                    brett[rad2][kol2] == brett[rad - 1][kol - 1] && brett[rad2][kol2] == motL || brett[rad2][kol2] == brett[rad - 1][kol + 1] && brett[rad2][kol2] == motL ||
                    brett[rad2][kol2] == brett[rad - 1][kol - 1] && brett[rad2][kol2] == motK || brett[rad2][kol2] == brett[rad - 1][kol + 1] && brett[rad2][kol2] == motK)
                {
                    brett[rad2][kol2] = dinB;
                    brett[rad][kol] = blank;

                    return(true);
                    repeat = false;
                }
                else
                {
                    plassering(til, rad2, kol2, motB, motL, motK);
                }
            }
        }
    }

    bool flyttLoeper(char fra[2], char til[2], char dinB, char dinL, char dinK, char motB, char motL, char motK)
    {
        int rad = 0, kol = 0, rad2 = 0, kol2 = 0;

        bool repeat = true;

        charTilInt(fra, rad, kol);
        charTilInt(til, rad2, kol2);

        while (repeat == true)
        {
            int n = abs(rad2 - rad);

            /* Ternary operator. kdir = -1 hvis kol2-kol er mindre enn 0, ellers er kdir lik 1. Hvis det logiske uttrykket er riktig får
            kdir verdien -1 ellers 1. */
            int kdir = (kol2 - kol < 0) ? (-1) : 1;

            int rdir = (rad2 - rad < 0) ? (-1) : 1;

            if (n != abs(kol2 - kol))
            {
                plassering(til, rad2, kol2, motB, motL, motK);
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    if (!(brett[rad + ((i + 1) * rdir)][kol + ((i + 1) * kdir)] == blank))
                    {
                        if (!((rad + ((i + 1) * rdir)) == rad2 && (kol + ((i + 1) * kdir)) == kol2))
                        {
                            plassering(til, rad2, kol2, motB, motL, motK);
                        }
                        else
                        {
                            if (brett[rad2][kol2] == motB || brett[rad2][kol2] == motL || brett[rad2][kol2] == motK)
                            {
                                brett[rad2][kol2] = dinL;
                                brett[rad][kol] = blank;

                                repeat = false;
                                return(true);
                            }
                            else
                            {
                                plassering(til, rad2, kol2, motB, motL, motK);
                            }
                        }
                    }
                    else if ((rad + ((i + 1) * rdir)) == rad2 && (kol + ((i + 1) * kdir)) == kol2)
                    {
                        brett[rad2][kol2] = dinL;
                        brett[rad][kol] = blank;

                        repeat = false;
                        return(true);
                    }
                }
            }
        }
    }

    bool sjekkSjakk(char fra[2], char til[2], char dinB, char dinL, char dinK, char motB, char motL, char motK)
    {
        std::vector <int> tall{ 0, 1, 2, 3, 4, 5, 6, 7 };

        for (int i = rad - 1; i >= 0; i--)
        {
            for (int j = 0; j < kol; j++)
            {
                if (hvit == true)
                {
                    if (brett[i][j] == motK && brett[i - 1][j - 1] == dinB || brett[i][j] == motK && brett[i - 1][j + 1] == dinB)
                    {
                        return(true);
                    }
                }
                else if (svart == true)
                {
                    if (brett[i][j] == motK && brett[i + 1][j - 1] == dinB || brett[i][j] == motK && brett[i + 1][j + 1] == dinB)
                    {
                        return(true);
                    }
                }

                if (brett[i][j] == motK && brett[i - 1][j - 1] == dinK || brett[i][j] == motK && brett[i - 1][j + 1] == dinK
                    || brett[i][j] == motK && brett[i + 1][j - 1] == dinK || brett[i][j] == motK && brett[i + 1][j + 1] == dinK
                    || brett[i][j] == motK && brett[i][j - 1] == dinK || brett[i][j] == motK && brett[i][j + 1] == dinK
                    || brett[i][j] == motK && brett[i - 1][j] == dinK || brett[i][j] == motK && brett[i + 1][j] == dinK)
                {
                    return(true);
                }

                for (int k = 0; k < kol; k++)
                {
                    if (brett[i][j] == motK && brett[i - tall[k]][j - tall[k]] == dinL || brett[i][j] == motK && brett[i - tall[k]][j + tall[k]] == dinL ||
                        brett[i][j] == motK && brett[i + tall[k]][j + tall[k]] == dinL || brett[i][j] == motK && brett[i + tall[k]][j - tall[k]] == dinL)
                    {
                        int rad2 = i, kol2 = j;
                        int rad = 0, kol = 0;

                        if (brett[i - tall[k]][j - tall[k]] == dinL)
                        {
                            rad = i - tall[k];
                            kol = j - tall[k];
                        }

                        if (brett[i - tall[k]][j + tall[k]] == dinL)
                        {
                            rad = i - tall[k];
                            kol = j + tall[k];
                        }

                        if (brett[i + tall[k]][j + tall[k]] == dinL)
                        {
                            rad = i + tall[k];
                            kol = j + tall[k];
                        }

                        if (brett[i + tall[k]][j - tall[k]] == dinL)
                        {
                            rad = i + tall[k];
                            kol = j - tall[k];
                        }

                        int n = abs(rad2 - rad);

                        int kdir = (kol2 - kol < 0) ? (-1) : 1;

                        int rdir = (rad2 - rad < 0) ? (-1) : 1;

                        for (int i = 0; i < n - 1; i++)
                        {
                            if (!(brett[rad + ((i + 1) * rdir)][kol + ((i + 1) * kdir)] == blank))
                            {
                                return(false);
                            }
                        }

                        return(true);
                    }
                }
            }
        }
    }

    bool sjekkSjakkMatt()
    {
        if (hvit == true && sjakk2 == true)
        {
            hS++;
        }
        else if (hvit == true && sjakk2 == false)
        {
            hS = 0;
        }
        else if (svart == true && sjakk2 == true)
        {
            sS++;
        }
        else if (hvit == true && sjakk2 == false)
        {
            sS = 0;
        }

        if (hvit == true && hS == 2)
        {
            std::cout << "Svart spiller er i sjakkmattmatt\n";
            exit(1);
        }
        else if (svart == true && sS == 2)
        {
            std::cout << "Hvit spiller er i sjakkmatt\n";
            exit(1);
        }
    }

    void visBrett()
    {
        int k = 8;

        std::cout << "  _______________\n";

        for (int i = rad-1; i >= 0; i--)
        {
            std::cout << k;
            k--;

            for (int j = 0; j < kol; j++)
            {
                std::cout << '|' << brett[i][j];
            }
            std::cout << '|' << std::endl;
        }
        std::cout << blank << "|a|b|c|d|e|f|g|h|\n";
    }

    void nyttBrett()
    {
        for (int i = 0; i < rad; i++)
        {
            for (int j = 0; j < kol; j++)
            {
                brett[i][j] = blank;
            }
        }

        brett[0][2] = hvitL;
        brett[0][5] = hvitL;
        brett[0][4] = hvitK;

        for (int i = 0; i < kol; i++)
        {
            brett[1][i] = hvitB;
        }

        brett[7][2] = svartL;
        brett[7][5] = svartL;
        brett[7][4] = svartK;

        for (int i = 0; i < kol; i++)
        {
            brett[6][i] = svartB;
        }
    }

    void charTilInt(char num[], int& rad, int& kol)
    {
        rad = num[0] - '0';
        rad -= 1;

        kol = num[1] - '0';
        kol -= 49;
    }
};

int main()
{
    TaskOne t1;
    t1.sjakk();
}
