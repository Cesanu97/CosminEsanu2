#include "gestione_processi.h"

int main() {
    std::vector<UserProcess> userProcesses;
    std::vector<SystemProcess> systemProcesses;
    
    // Header, CODE WRITTEN WITH CODESPACE
    std::cout << "--------------------------------------------\n";
    std::cout << " Programma di simulazione processi\n";
    std::cout << " Cosmin Esanu\n";
    std::cout << " Eseguito con Codespace di GitHub\n";
    std::cout << "--------------------------------------------\n";

    caricaProcessiDaFile("processes.txt", userProcesses, systemProcesses);
    ordinaProcessi(userProcesses, systemProcesses);

    int tempoCumulativo = 0;
    float totaleAttesaUser = 0, totaleAttesaSystem = 0;

    std::cout << "\n--- Elenco Processi ---\n";

    for (auto &p : userProcesses) {
        int attesa = std::max(0, tempoCumulativo - p.getTempoArrivo());
        int completamento = attesa + p.getIstruzioni();
        totaleAttesaUser += attesa;

        p.stampaInformazioni(attesa, completamento);
        tempoCumulativo = completamento;
    }

    for (auto &p : systemProcesses) {
        int attesa = std::max(0, tempoCumulativo - p.getTempoArrivo());
        int completamento = attesa + p.getIstruzioni();
        totaleAttesaSystem += attesa;

        p.stampaInformazioni(attesa, completamento);
        tempoCumulativo = completamento;
    }

    float attesaMediaUser = userProcesses.empty() ? 0 : totaleAttesaUser / userProcesses.size();
    float attesaMediaSystem = systemProcesses.empty() ? 0 : totaleAttesaSystem / systemProcesses.size();

    std::cout << "\nStatistiche Processi:\n";
    std::cout << "Tempo medio attesa Utente: " << attesaMediaUser << "\n";
    std::cout << "Tempo medio attesa Sistema: " << attesaMediaSystem << "\n";

    return 0;
}
