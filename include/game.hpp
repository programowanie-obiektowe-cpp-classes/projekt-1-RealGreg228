#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <random>

// Stałe dla pracowników
const int CI = 500;  // Cena produktu
const int CMag = 50; // Pojemność magazynu na pracownika
const int CMkt = 25; // Popyt generowany przez marketera
const int CR = 25;   // Produkcja na pracownika

// Liczba miesięcy do wyliczenia wartości firmy
const int HISTORY_MONTHS = 6;

// Klasa abstrakcyjna Pracownik
class Pracownik {
protected:
    std::string imie_;
    double wynagrodzenie_;
public:
    Pracownik(const std::string& imie, double wynagrodzenie)
        : imie_(imie), wynagrodzenie_(wynagrodzenie) {}

    virtual ~Pracownik() = default;

    virtual void print() const = 0;
    double getWynagrodzenie() const { return wynagrodzenie_; }
};

// Klasy pochodne Pracownik
class Inzynier : public Pracownik {
    std::string wydzial_;
public:
    Inzynier(const std::string& imie, double wynagrodzenie, const std::string& wydzial)
        : Pracownik(imie, wynagrodzenie), wydzial_(wydzial) {}

    void print() const override {
        std::cout << "Inz. " << imie_ << ", Wydzial: " << wydzial_
                  << ", Wynagrodzenie: " << wynagrodzenie_ << "\n";
    }
};

class Magazynier : public Pracownik {
    bool forklift_certified_; 
public:
    Magazynier(const std::string& imie, double wynagrodzenie, bool forklift)
        : Pracownik(imie, wynagrodzenie), forklift_certified_(forklift) {}

    void print() const override {
        std::cout << "Magazynier " << imie_ << ", Obsługa wózka: "
                  << (forklift_certified_ ? "Tak" : "Nie")
                  << ", Wynagrodzenie: " << wynagrodzenie_ << "\n";
    }
};

class Marketer : public Pracownik {
    int follows_;
public:
    Marketer(const std::string& imie, double wynagrodzenie, int follows)
        : Pracownik(imie, wynagrodzenie), follows_(follows) {}

    void print() const override {
        std::cout << "Marketer " << imie_ << ", Obserwujący: " << follows_
                  << ", Wynagrodzenie: " << wynagrodzenie_ << "\n";
    }
};

class Robotnik : public Pracownik {
    double but_;
public:
    Robotnik(const std::string& imie, double wynagrodzenie, double but)
        : Pracownik(imie, wynagrodzenie), but_(but) {}

    void print() const override {
        std::cout << "Robotnik " << imie_ << ", Rozmiar buta: " << but_
                  << ", Wynagrodzenie: " << wynagrodzenie_ << "\n";
    }
};

// Klasa Kredyt
class Kredyt {
    double dlug_;
    int pozostale_raty_;
    double rata_;

public:
    Kredyt(double dlug, int czas_splaty) : dlug_(dlug), pozostale_raty_(czas_splaty){
        rata_ = dlug / czas_splaty;
    }

    bool splacRate(){
        dlug_ -= rata_;
        pozostale_raty_--;
        return pozostale_raty_ <= 0;
    }

    double getRate() const { return rata_; }
    double getDlug() const { return dlug_; }
};

// Klasa Firma
class Firma {
    double stan_konta_;
    std::vector<std::unique_ptr<Pracownik>> pracownicy_;
    std::vector<std::unique_ptr<Kredyt>> kredyty_;
    std::vector<double> historia_przychodow_;

public:
    Firma();

    void zatrudnij(std::unique_ptr<Pracownik> pracownik);
    void wezKredyt(double kwota, int czas_splaty);
    void zaplacWynagrodzenie();
    void otrzymajPrzychod();
    void splacRaty();
    double obliczPrzychod() const;
    double getStanKonta() const { return stan_konta_; }
    double wartoscFirmy() const;
    void drukujPracownikow() const;
};
