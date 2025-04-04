#include "gestione_processi.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>

// Function to load processes from a file
void caricaProcessiDaFile(const std::string &filename, std::vector<UserProcess> &userProcesses, std::vector<SystemProcess> &systemProcesses) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Errore: impossibile aprire il file " << filename << "\n";
        return;
    }

    std::unordered_set<std::string> processNomi; // To track duplicate names
    std::string line;

    while (getline(file, line)) {
        std::istringstream ss(line);
        char tipo;
        int pid, istruzioni, priorita, tempoArrivo;
        std::string nome;

        ss >> tipo >> pid >> istruzioni >> priorita >> tempoArrivo >> nome;

        if (processNomi.count(nome)) {
            std::cerr << "Errore: Processo con nome duplicato (" << nome << ") ignorato.\n";
            continue;
        }

        if (tipo == 'U') {
            if (istruzioni <= 0) {
                std::cerr << "Errore: Numero di istruzioni negativo (" << istruzioni << ") per il processo " << nome << ", processo ignorato.\n";
                continue;
            }
            userProcesses.emplace_back(pid, istruzioni, priorita, tempoArrivo, nome);
        } 
        else if (tipo == 'S') {
            systemProcesses.emplace_back(pid, istruzioni, priorita, tempoArrivo, nome);
        } 
        else {
            std::cerr << "Errore: Tipo di processo non riconosciuto ('" << tipo << "') per " << nome << ", processo ignorato.\n";
            continue;
        }

        processNomi.insert(nome);
    }
}

// Function to sort processes
void ordinaProcessi(std::vector<UserProcess> &userProcesses, std::vector<SystemProcess> &systemProcesses) {
    std::sort(userProcesses.begin(), userProcesses.end(), [](const UserProcess &a, const UserProcess &b) {
        return a.getIstruzioni() < b.getIstruzioni();
    });

    std::sort(systemProcesses.begin(), systemProcesses.end(), [](const SystemProcess &a, const SystemProcess &b) {
        return a.getPriorita() > b.getPriorita();
    });
}

// Function to print process statistics
void stampaStatistiche(const std::vector<UserProcess> &userProcesses, const std::vector<SystemProcess> &systemProcesses) {
    if (userProcesses.empty() && systemProcesses.empty()) {
        std::cout << "Nessun processo da analizzare.\n";
        return;
    }

    int totaleUtente = 0, totaleSistema = 0;
    int attesaMassima = 0;
    UserProcess processoEfficiente(0, 1, 1, 0, "N/A");
    SystemProcess processoAttesaMax(0, 1, 1, 0, "N/A");

    for (const auto &p : userProcesses) {
        totaleUtente += p.calcolaTempoCompletamento(p.calcolaTempoAttesa(0));
        if (p.calcolaEfficienza() > processoEfficiente.calcolaEfficienza()) {
            processoEfficiente = p;
        }
    }

    for (const auto &p : systemProcesses) {
        totaleSistema += p.calcolaTempoCompletamento(p.calcolaTempoAttesa(0));
        if (p.calcolaTempoAttesa(0) > attesaMassima) {
            attesaMassima = p.calcolaTempoAttesa(0);
            processoAttesaMax = p;
        }
    }

    int tempoTotale = totaleUtente + totaleSistema;
    float percentualeUtente = (tempoTotale > 0) ? (static_cast<float>(totaleUtente) / tempoTotale) * 100 : 0;
    float percentualeSistema = 100 - percentualeUtente;

    std::cout << "\nStatistiche Processi:\n";
    std::cout << "- Tempo totale processi utente: " << percentualeUtente << "%\n";
    std::cout << "- Tempo totale processi di sistema: " << percentualeSistema << "%\n";
    std::cout << "- Processo più efficiente: [" << processoEfficiente.getPid() << "] " << processoEfficiente.getNome() 
              << " (Efficienza: " << processoEfficiente.calcolaEfficienza() << ")\n";
    std::cout << "- Processo con tempo di attesa massimo: [" << processoAttesaMax.getPid() << "] " << processoAttesaMax.getNome() 
              << " (Attesa: " << attesaMassima << ")\n";
}
