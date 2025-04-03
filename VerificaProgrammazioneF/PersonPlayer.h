#ifndef PERSON_PLAYER_H
#define PERSON_PLAYER_H

#include <string>
#include <vector>

// Classe base Person
class Person {
public:
    std::string name;
    std::string surname;

    Person(const std::string& n, const std::string& s);
    std::string getFullName() const;
};

// Classe derivata Player
class Player : public Person {
public:
    int number;
    float pointsPerGame;
    float reboundsPerGame;
    float assistsPerGame;

    static int totalPlayersRead;

    Player(const std::string& n, const std::string& s, int num, float ppg, float rpg, float apg);
    void print() const;
    float getPointsPerGame() const;

    static int getTotalPlayersRead();
};

// Funzione per leggere i giocatori dal file
int readPlayersFromFile(std::vector<Player>& players, const std::string& filename);

// Funzione per trovare il miglior marcatore
Player bestScorer(const std::vector<Player>& players);

#endif // PERSON_PLAYER_H
