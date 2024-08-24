#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

ifstream inp;
ofstream outp;

char c[30][21];
int n[30][21];
int highscore;
int contr, tuk = 0, score = 0, t = 0, bt = 0, birdx = 0, birdy = 0;
bool err;

void game();
void screen();
void pipes();
void bird();
bool gameover();
void checkscore();
void help();
void menu();
void endgame();
void credits();

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    system("cls");
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    srand(time(0));
    inp.open("options.txt"); // Ensure the file is in the same directory or provide the correct path
    if (inp.is_open()) {
        inp >> highscore;
        inp.close();
        err = false;
    } else {
        highscore = 0;
        err = true;
    }

    int a = 0;
    char sl;
    while (1) {
        if (a > 0) {
            score = 0;
            cout << "Do you want to play again? [y/n] ";
            cin >> sl;
            if (sl == 'n') break;
        }
        menu();
        cin >> sl;
        switch (sl) {
            case '1':
                game();
                break;
            case '2':
                help();
                break;
            case '3':
                credits();
                break;
            case '4':
                goto quit;
                break;
            default:
                break;
        }
        a++;
    }

quit:
    cout << "I quit.";
    return 0;
}

void game() {
    int x, y;
    char s;
    for (y = 0; y < 21; y++) {
        for (x = 0; x < 30; x++) {
            if (y < 20) {
                c[x][y] = ' ';
                n[x][y] = 0;
            }
            if (y == 20) {
                c[x][y] = '-';
                n[x][y] = 2;
            }
        }
    }
    c[10][10] = '*';
    screen();
    while (1) {
        s = '~';
        Sleep(200);
        t++;
        if (_kbhit()) {
            s = _getch();
            if (s != '~') tuk = 1;
        }
        for (x = 0; x < 30; x++) {
            c[x][20] = '-';
            n[x][20] = 2;
        }
        bird();
        checkscore();
        if (gameover()) break;
        pipes();
        if (score > highscore) highscore = score;
        screen();
        if (tuk > 0) tuk++;
        if (tuk == 3) tuk = 0;
    }
    if (score > highscore) highscore = score;
    if (!err) {
        outp.open("options.txt");
        outp << highscore;
        outp.close();
    }
    screen();
    endgame();
}

void screen() {
    clearScreen();
    int x, y;
    for (y = 0; y < 21; y++) {
        for (x = 0; x < 30; x++) {
            cout << c[x][y];
        }
        cout << endl;
    }
    cout << endl;
    cout << "Your Score: " << score << "  High Score: " << highscore << endl;
}

void pipes() {
    int x, y, r;
    if (t == 10) {
        r = (rand() % 11) + 5;
        for (y = 0; y < 20; y++) {
            c[29][y] = '|';
            n[29][y] = 2;
        }
        c[29][r - 1] = ' ';
        c[29][r] = ' ';
        c[29][r + 1] = ' ';
        n[29][r - 1] = 0;
        n[29][r] = 0;
        n[29][r + 1] = 0;
        t = 0;
    }
    for (y = 0; y < 20; y++) {
        for (x = 0; x < 30; x++) {
            if (c[x][y] == '|') {
                if (x > 0) {
                    c[x - 1][y] = '|';
                    n[x - 1][y] = 2;
                    c[x][y] = ' ';
                    n[x][y] = 0;
                } else {
                    c[x][y] = ' ';
                    n[x][y] = 0;
                }
            }
        }
    }
}

void bird() {
    int x, y;
    if (tuk > 0) {
        bt = 0;
        for (y = 0; y < 20; y++) {
            for (x = 0; x < 30; x++) {
                if (c[x][y] == '*') {
                    if (y > 0) {
                        c[x][y - 1] = '*';
                        c[x][y] = ' ';
                        birdx = x;
                        birdy = y - 1;
                        return;
                    }
                }
            }
        }
    } else {
        bt++;
        for (y = 0; y < 20; y++) {
            for (x = 0; x < 30; x++) {
                if (c[x][y] == '*') {
                    if (y < 20) {
                        if (bt < 3) {
                            c[x][y + 1] = '*';
                            c[x][y] = ' ';
                            birdx = x;
                            birdy = y + 1;
                            return;
                        } else if (bt > 2 && bt < 5) {
                            c[x][y + 2] = '*';
                            c[x][y] = ' ';
                            birdx = x;
                            birdy = y + 2;
                            return;
                        } else if (bt > 4) {
                            c[x][y + 3] = '*';
                            c[x][y] = ' ';
                            birdx = x;
                            birdy = y + 3;
                            return;
                        }
                    }
                }
            }
        }
    }
}

bool gameover() {
    if (birdy >= 20) return true;
    if (n[birdx][birdy] == 2) return true;
    return false;
}

void checkscore() {
    if (birdx == 1) score++;
}

void help() {
    clearScreen();
    cout << "Welcome to Flappy Bird!\n";
    cout << "Controls:\n";
    cout << "Press any key to make the bird fly up.\n";
    cout << "Avoid the pipes and ground to keep scoring points.\n";
    cout << "Press any key to return to the menu...\n";
    _getch();
}

void menu() {
    clearScreen();
    cout << "Flappy Bird\n";
    cout << "1. Play\n";
    cout << "2. Help\n";
    cout << "3. Credits\n";
    cout << "4. Quit\n";
    cout << "Enter your choice: ";
}

void endgame() {
    clearScreen();
    cout << "Game Over!\n";
    cout << "Your final score is: " << score << endl;
    cout << "Press any key to return to the menu...\n";
    _getch();
}

void credits() {
    clearScreen();
    cout << "Flappy Bird Game\n";
    cout << "Created by HAKERIS1010\n";
    cout << "Press any key to return to the menu...\n";
    _getch();
}
