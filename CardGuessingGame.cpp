/* Mergen Chinzorig
   July 19, 2025
   Week 6
   Final Project */

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

class MemoryMatchGame {
private:
    static const int MAX_WORDS = 50;
    string theme50Words[MAX_WORDS];
    int gridSize;
    int numPairs;
    int displayDelay;
    string faceTerm;
    string answerArray[8][8];
    string displayArray[8][8];
    bool revealed[8][8];
    steady_clock::time_point startTime;

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    string fixWord(const string& s) {
        string res;
        for (char ch : s)
            if (ch != ' ') res += ch;
        if (res.length() > 8) res = res.substr(0, 8);
        while (res.length() < 8) res += " ";
        return res;
    }

    void loadThemeWordsByName(const string& themeName) {
        if (themeName == "players") {
            faceTerm = fixWord("FOOTBALL");
            string sample[50] = {
                "Lionel Messi", "Cristiano Ronaldo", "Neymar Jr", "Luis Suarez", "Robert Lewandowski",
                "N'Golo Kante", "Luka Modric", "Mohamed Salah",
                "Sergio Aguero", "Gareth Bale", "Eden Hazard", "Kevin De Bruyne",
                "Raheem Sterling", "Antoine Griezmann", "Toni Kroos", "Paul Pogba",
                "Paulo Dybala", "Harry Kane", "Sadio Mane", "Riyad Mahrez",
                "David Alaba", "Thiago Alcantara", "Lorenzo Insigne", "Pierre Aubameyang",
                "Roberto Firmino", "Jadon Sancho", "Nabil Fekir", "Marcus Rashford",
                "Heung-min Son", "Dele Alli", "Ousmane Dembele", "Philippe Coutinho",
                "Zlatan Ibrahimvic", "Edinson Cavani", "Jerome Boateng", "Christian Pulisic",
                "Jan Vertonghen", "Karim Benzema", "Isco Alarcon", "Lucas Moura",
                "Joe Gomez", "Dani Alves", "Cesar Azpilicueta", "Thiago Silva",
                "Juan Bernat", "Marco Verratti", "Sergio Carrasco", "Dani Alves",
                "Rodrigo Moreno", "Joshua Kimmich"
            };
            for (int i = 0; i < 50; i++) theme50Words[i] = fixWord(sample[i]);
        } else if (themeName == "countries") {
            faceTerm = fixWord("COUNTRIES");
            string sample[50] = {
                "Brazil", "Argentina", "Germany", "France", "Spain", "Italy", "England",
                "Portugal", "Netherlands", "Belgium", "Uruguay", "Croatia", "Sweden", "Denmark",
                "Poland", "Colombia", "Mexico", "Chile", "Wales", "Switzerland", "Turkey", "Senegal",
                "Serbia", "Japan", "USA", "Norway", "Austria", "Ukraine", "Scotland",
                "Peru", "Iran", "SouthKore", "Iceland", "Morocco", "Egypt", "Algeria", "CostaRic",
                "Tunisia", "Ghana", "Cameroon", "Ecuador", "Bosnia", "Slovenia", "Slovakia",
                "Venezuela", "Honduras", "Greece", "Republic", "Montene"
            };
            for (int i = 0; i < 50; i++) theme50Words[i] = fixWord(sample[i]);
        } else if (themeName == "cars") {
            faceTerm = fixWord("CARS");
            string sample[50] = {
                "Toyota", "Honda", "Ford", "Chevrolet", "Nissan", "BMW", "Audi", "Tesla",
                "Hyundai", "Kia", "Mazda", "Subaru", "Volkswagen", "Volvo", "Jeep", "Dodge",
                "Ferrari", "Lamborghini", "Bentley", "Cadillac", "Chrysler", "Jaguar", "Mitsubishi",
                "AlfaRomeo", "Bugatti", "McLaren", "Pagani", "RollsRce", "Suzuki", "Infiniti",
                "Acura", "Mini", "Saab", "Peugeot", "Citroen", "Renault", "Fiat", "Skoda",
                "Isuzu", "Lexus", "Lincoln", "Maserati", "Opel", "Proton", "Seat", "Tata",
                "Vauxhall", "Yamaha", "Koenigsegg", "Pagani"
            };
            for (int i = 0; i < 50; i++) theme50Words[i] = fixWord(sample[i]);
        } else {
            faceTerm = fixWord("UNKNOWN");
            for (int i = 0; i < 50; i++) theme50Words[i] = fixWord("UNKNOWN");
        }
    }

    void selectThemeMenu() {
        clearScreen();
        cout << "=== Choose a Theme ===\n\n";
        string themeName;
        while (true) {
            cout << "Enter your theme (players, countries, cars): ";
            getline(cin, themeName);
            transform(themeName.begin(), themeName.end(), themeName.begin(), ::tolower);

            if (themeName == "players" || themeName == "countries" || themeName == "cars") {
                loadThemeWordsByName(themeName);
                break;
            }
            cout << "Sorry, theme not recognized. Please try again.\n";
        }
    }

    void selectDifficultyMenu() {
        int choice = 0;
        while (true) {
            cout << "\nSelect difficulty level:\n";
            cout << "1) Easy (4x4)\n2) Moderate (6x6)\n3) Difficult (8x8)\nEnter choice (1-3): ";
            if (cin >> choice) {
                if (choice == 1) {
                    gridSize = 4;
                    numPairs = 8;
                    break;
                } else if (choice == 2) {
                    gridSize = 6;
                    numPairs = 18;
                    break;
                } else if (choice == 3) {
                    gridSize = 8;
                    numPairs = 32;
                    break;
                }
            }
            cout << "Invalid choice, try again.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
    }

    void selectSpeedMenu() {
        int choice = 0;
        while (true) {
            cout << "\nSelect display speed for mismatched pairs:\n";
            cout << "1) 6 seconds (Easy)\n2) 4 seconds (Moderate)\n3) 2 seconds (Difficult)\nEnter choice (1-3): ";
            if (cin >> choice) {
                if (choice == 1) {
                    displayDelay = 6;
                    break;
                } else if (choice == 2) {
                    displayDelay = 4;
                    break;
                } else if (choice == 3) {
                    displayDelay = 2;
                    break;
                }
            }
            cout << "Invalid choice, try again.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
    }

    void shuffleAndAssignPairs() {
        for (int i = MAX_WORDS - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(theme50Words[i], theme50Words[j]);
        }
        for (int r = 0; r < gridSize; r++) {
            for (int c = 0; c < gridSize; c++) {
                answerArray[r][c] = "";
                displayArray[r][c] = faceTerm;
                revealed[r][c] = false;
            }
        }
        int totalCells = gridSize * gridSize;
        int positions[64];
        for (int i = 0; i < totalCells; i++)
            positions[i] = i;
        for (int i = totalCells - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(positions[i], positions[j]);
        }
        for (int i = 0; i < numPairs; i++) {
            int pos1 = positions[2 * i];
            int pos2 = positions[2 * i + 1];
            int r1 = pos1 / gridSize;
            int c1 = pos1 % gridSize;
            int r2 = pos2 / gridSize;
            int c2 = pos2 % gridSize;
            answerArray[r1][c1] = theme50Words[i];
            answerArray[r2][c2] = theme50Words[i];
        }
    }

    void displayBoard() {
        clearScreen();
        cout << "Memory Match Game - Theme Face Term: " << faceTerm << "\n\n  ";
        for (int c = 0; c < gridSize; c++)
            cout << "  " << c + 1 << "       ";
        cout << "\n";
        for (int r = 0; r < gridSize; r++) {
            cout << r + 1 << " ";
            for (int c = 0; c < gridSize; c++) {
                cout << "[" << displayArray[r][c] << "]";
            }
            cout << "\n";
        }
        cout << "\n";
        cout.flush();
    }

    void getUserSelection(int& row, int& col) {
        while (true) {
            cout << "Enter row (1-" << gridSize << "): ";
            string rowInput;
            getline(cin, rowInput);
            transform(rowInput.begin(), rowInput.end(), rowInput.begin(), ::tolower);

            if (rowInput == "instantwin") {
                unlockAll();
                displayBoard();
                auto endTime = steady_clock::now();
                auto elapsed = duration_cast<seconds>(endTime - startTime).count();
                cout << "Backdoor activated: You instantly won!\n";
                cout << "Total time: " << elapsed << " seconds\n";
                exit(0);
            }

            try {
                row = stoi(rowInput);
            } catch (...) {
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            cout << "Enter column (1-" << gridSize << "): ";
            string colInput;
            getline(cin, colInput);

            try {
                col = stoi(colInput);
            } catch (...) {
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if (row < 1 || row > gridSize || col < 1 || col > gridSize) {
                cout << "Invalid input, please enter numbers in range.\n";
                continue;
            }

            row -= 1;
            col -= 1;

            if (revealed[row][col]) {
                cout << "That card is already matched. Choose another.\n";
                continue;
            }
            if (displayArray[row][col] != faceTerm) {
                cout << "That card is currently revealed. Choose another.\n";
                continue;
            }

            break;
        }
    }

    void delaySeconds(int seconds) {
        this_thread::sleep_for(chrono::seconds(seconds));
    }

    bool isGameComplete() {
        for (int r = 0; r < gridSize; r++)
            for (int c = 0; c < gridSize; c++)
                if (!revealed[r][c])
                    return false;
        return true;
    }

public:
    MemoryMatchGame() {
        srand((unsigned int)time(nullptr));
    }

    void unlockAll() {
        for (int r = 0; r < gridSize; r++) {
            for (int c = 0; c < gridSize; c++) {
                revealed[r][c] = true;
                displayArray[r][c] = answerArray[r][c];
            }
        }
    }

    void start() {
        selectThemeMenu();
        selectDifficultyMenu();
        selectSpeedMenu();

        startTime = steady_clock::now();

        shuffleAndAssignPairs();

        while (true) {
            displayBoard();
            int r1, c1, r2, c2;
            cout << "Select FIRST card:\n";
            getUserSelection(r1, c1);
            displayArray[r1][c1] = answerArray[r1][c1];
            displayBoard();
            cout << "Select SECOND card:\n";
            getUserSelection(r2, c2);
            displayArray[r2][c2] = answerArray[r2][c2];
            displayBoard();
            if (answerArray[r1][c1] == answerArray[r2][c2]) {
                cout << "It's a MATCH!\n";
                revealed[r1][c1] = true;
                revealed[r2][c2] = true;
            } else {
                cout << "Not a match. Cards will be hidden in " << displayDelay << " seconds.\n";
                delaySeconds(displayDelay);
                displayArray[r1][c1] = faceTerm;
                displayArray[r2][c2] = faceTerm;
            }
            if (isGameComplete()) {
                displayBoard();
                auto endTime = steady_clock::now();
                auto elapsed = duration_cast<seconds>(endTime - startTime).count();
                cout << "Congratulations! You matched all pairs!\n";
                cout << "Total time: " << elapsed << " seconds\n";
                break;
            }
        }
    }
};

int main() {
    MemoryMatchGame game;
    game.start();
    return 0;
}