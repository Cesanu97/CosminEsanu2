#include "PersonPlayer.h"
#include <iostream>
#include <fstream>
#include <sstream>

int Player::totalPlayersRead = 0;  // Inizializzazione della variabile statica

// Implementazione della classe Person
Person::Person(const std::string& n, const std::string& s) : name(n), surname(s) {}

std::string Person::getFullName() const {
    return name + " " + surname;
}

// Implementazione della classe Player
Player::Player(const std::string& n, const std::string& s, int num, float ppg, float rpg, float apg)
    : Person(n, s), number(num), pointsPerGame(ppg), reboundsPerGame(rpg), assistsPerGame(apg) {
    totalPlayersRead++;
}

void Player::print() const {
    std::cout << "Nome: " << getFullName() << std::endl;
    std::cout << "Numero di maglia: " << number << std::endl;
    std::cout << "Punti per partita: " << pointsPerGame << std::endl;
    std::cout << "Rimbalzi per partita: " << reboundsPerGame << std::endl;
    std::cout << "Assist per partita: " << assistsPerGame << std::endl;
}

float Player::getPointsPerGame() const {
    return pointsPerGame;
}

int Player::getTotalPlayersRead() {
    return totalPlayersRead;
}

// Funzione per leggere i giocatori dal file
int readPlayersFromFile(std::vector<Player>& players, const std::string& filename) {
    std::ifstream file(filename);
    int playersReadThisCall = 0;

    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file: " << filename << std::endl;
        return 0;  // Nessun giocatore letto
    }

    std::string line;
    while (std::getline(file, line) && players.size() < 5) {
        std::istringstream stream(line);
        std::string name, surname;
        int number;
        float points, rebounds, assists;

        stream >> name >> surname >> number >> points >> rebounds >> assists;

        Player newPlayer(name, surname, number, points, rebounds, assists);
        players.push_back(newPlayer);
        playersReadThisCall++;
    }
    file.close();

    std::cout << "Totale giocatori letti: " << Player::getTotalPlayersRead() << std::endl;
    return playersReadThisCall;
}

// Funzione per determinare il miglior marcatore
Player bestScorer(const std::vector<Player>& players) {
    Player best = players[0];

    for (const auto& player : players) {
        if (player.getPointsPerGame() > best.getPointsPerGame()) {
            best = player;
        }
    }

    return best;
}
