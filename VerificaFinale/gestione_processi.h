#ifndef GESTIONE_PROCESSI_H
#define GESTIONE_PROCESSI_H

#include "processi.h"
#include <vector>
#include <string>
#include <unordered_set>

void caricaProcessiDaFile(const std::string &filename, std::vector<UserProcess> &userProcesses, std::vector<SystemProcess> &systemProcesses);
void stampaStatistiche(const std::vector<UserProcess> &userProcesses, const std::vector<SystemProcess> &systemProcesses);
void ordinaProcessi(std::vector<UserProcess> &userProcesses, std::vector<SystemProcess> &systemProcesses);

#endif
