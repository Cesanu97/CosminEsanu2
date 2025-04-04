#include "processi.h"

// Calculate waiting time considering previous processes
int UserProcess::calcolaTempoAttesa(int tempoCumulativo) const {
    return std::max(0, tempoCumulativo - tempoArrivo);
}

// Calculate completion time
int UserProcess::calcolaTempoCompletamento(int tempoAttesa) const {
    return tempoAttesa + istruzioni;
}

// Efficiency is calculated as instructions / completion time
float UserProcess::calcolaEfficienza() const {
    return static_cast<float>(istruzioni) / calcolaTempoCompletamento(calcolaTempoAttesa(0));
}

// Checks if UI is required
bool UserProcess::richiedeUI() const {
    return (nome.find("gui") != std::string::npos || nome.find("window") != std::string::npos ||
            nome.find("browser") != std::string::npos);
}

// Print user process details
void UserProcess::stampaInformazioni(int tempoAttesa, int tempoCompletamento) const {
    std::cout << "Utente   [" << pid << "] " << nome
              << " | Arrivo: " << tempoArrivo
              << " | Attesa: " << tempoAttesa
              << " | Compl.: " << tempoCompletamento
              << " | Efficienza: " << calcolaEfficienza() << "\n";
}

// System process methods
int SystemProcess::calcolaTempoAttesa(int tempoCumulativo) const {
    return std::max(0, tempoCumulativo - tempoArrivo);
}

int SystemProcess::calcolaTempoCompletamento(int tempoAttesa) const {
    return tempoAttesa + istruzioni;
}

bool SystemProcess::isCritico() const {
    return (priorita > 7 || nome.find("kernel") != std::string::npos || nome.find("system") != std::string::npos);
}

float SystemProcess::calcolaCostoCPU() const {
    return (istruzioni * priorita) / 100.0;
}

// Print system process details
void SystemProcess::stampaInformazioni(int tempoAttesa, int tempoCompletamento) const {
    std::cout << "Sistema  [" << pid << "] " << nome
              << " | Arrivo: " << tempoArrivo
              << " | Attesa: " << tempoAttesa
              << " | Compl.: " << tempoCompletamento
              << " | Costo CPU: " << calcolaCostoCPU()
              << " | Critico: " << (isCritico() ? "Sì" : "No") << "\n";
}
