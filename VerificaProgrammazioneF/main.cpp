#include <iostream>
#include <vector>
#include "PersonPlayer.h"

int main() {
    std::vector<Player> players;
    
    // Leggiamo i giocatori dal file
    int playersRead = readPlayersFromFile(players, "giocatori.txt");
    
    std::cout << "\n--- Squadra ---\n" << std::endl;

    // Stampa dei dati di tutti i giocatori
    for (const auto& player : players) {
        player.print();
        std::cout << std::endl;
    }

    // Determina il miglior marcatore
    Player best = bestScorer(players);
    std::cout << "Il miglior marcatore della squadra è: " << best.getFullName()
              << " con " << best.getPointsPerGame() << " punti a partita." << std::endl;

    return 0;
}
