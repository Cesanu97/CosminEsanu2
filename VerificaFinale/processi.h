#ifndef PROCESSI_H
#define PROCESSI_H

#include <iostream>
#include <string>

// Abstract base class for processes
class Process {
protected:
    int pid;
    int istruzioni;
    int priorita;
    int tempoArrivo;
    std::string nome;

public:
    Process(int p, int i, int pr, int ta, std::string n)
        : pid(p), istruzioni(i), priorita(pr), tempoArrivo(ta), nome(n) {}

    virtual int calcolaTempoAttesa(int tempoCumulativo) const = 0;
    virtual int calcolaTempoCompletamento(int tempoAttesa) const = 0;
    virtual void stampaInformazioni(int tempoAttesa, int tempoCompletamento) const = 0;

    int getPid() const { return pid; }
    int getIstruzioni() const { return istruzioni; }
    int getPriorita() const { return priorita; }
    int getTempoArrivo() const { return tempoArrivo; }
    std::string getNome() const { return nome; }

    virtual ~Process() {}
};

// User process class
class UserProcess : public Process {
public:
    UserProcess(int p, int i, int pr, int ta, std::string n)
        : Process(p, i, pr, ta, n) {}

    int calcolaTempoAttesa(int tempoCumulativo) const override;
    int calcolaTempoCompletamento(int tempoAttesa) const override;
    float calcolaEfficienza() const;
    bool richiedeUI() const;

    void stampaInformazioni(int tempoAttesa, int tempoCompletamento) const override;
};

// System process class
class SystemProcess : public Process {
public:
    SystemProcess(int p, int i, int pr, int ta, std::string n)
        : Process(p, i, pr, ta, n) {}

    int calcolaTempoAttesa(int tempoCumulativo) const override;
    int calcolaTempoCompletamento(int tempoAttesa) const override;
    bool isCritico() const;
    float calcolaCostoCPU() const;

    void stampaInformazioni(int tempoAttesa, int tempoCompletamento) const override;
};

#endif
