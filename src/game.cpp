#include "game.hpp"

// Konstruktor firmy
Firma::Firma() : stan_konta_(50000.0) { // Początkowe środki firmy
    // Dodanie początkowych pracowników
    pracownicy_.emplace_back(std::make_unique<Inzynier>("Inzynier Mamon", 5000.0, "SIMR"));
    pracownicy_.emplace_back(std::make_unique<Magazynier>("Mag-a-zynier", 3000.0, true));
    pracownicy_.emplace_back(std::make_unique<Marketer>("Menager marketingu", 4000.0, 150));
    pracownicy_.emplace_back(std::make_unique<Robotnik>("Robotnik", 3500.0, 42.5));
}
// Zatrudnianie nowego pracownika
void Firma::zatrudnij(std::unique_ptr<Pracownik> pracownik){
    pracownicy_.push_back(std::move(pracownik));
}
// Zaciąganie kredytu
void Firma::wezKredyt(double kwota, int czas_splaty){
    kredyty_.emplace_back(std::make_unique<Kredyt>(kwota, czas_splaty));
    stan_konta_ += kwota; // Kwota kredytu zwiększa stan konta
}
// Wypłacanie wynagrodzeń
void Firma::zaplacWynagrodzenie(){
    double suma = 0.0;
    for (const auto& pracownik : pracownicy_) {
        suma += pracownik->getWynagrodzenie();
    }
    stan_konta_ -= suma;
}
// Spłata rat kredytów
void Firma::splacRaty(){
    for (auto it = kredyty_.begin(); it != kredyty_.end();) {
        if ((*it)->splacRate()) {
            it = kredyty_.erase(it); // Usuń kredyt, gdy wszystkie raty zostaną spłacone
        } else {
            stan_konta_ -= (*it)->getRate();
            it++;
        }
    }
}
// Obliczanie przychodu
double Firma::obliczPrzychod() const {
    int liczba_inz = 0, liczba_mag = 0, liczba_markt = 0, liczba_rob = 0;

    for (const auto& pracownik : pracownicy_) {
        if (dynamic_cast<Inzynier*>(pracownik.get())) liczba_inz++;
        else if (dynamic_cast<Magazynier*>(pracownik.get())) liczba_mag++;
        else if (dynamic_cast<Marketer*>(pracownik.get())) liczba_markt++;
        else if (dynamic_cast<Robotnik*>(pracownik.get())) liczba_rob++;
    }

    int pojemnosc_magazynu = liczba_mag * CMag;
    int popyt = liczba_markt * CMkt;
    int teoretyczna_produkcja = liczba_rob * CR;
    int faktyczna_produkcja = std::min(teoretyczna_produkcja, pojemnosc_magazynu);
    int liczba_sprzedanych = std::min(popyt, faktyczna_produkcja);

    double cena_produktu = liczba_inz * CI;
    return liczba_sprzedanych * cena_produktu;
}
// Pobranie przychodów i aktualizacja stanu konta
void Firma::otrzymajPrzychod(){
    double przychod = obliczPrzychod();
    stan_konta_ += przychod;
    historia_przychodow_.push_back(przychod);

    // Utrzymuj historię ostatnich HISTORY_MONTHS miesięcy
    if (historia_przychodow_.size() > HISTORY_MONTHS) {
        historia_przychodow_.erase(historia_przychodow_.begin());
    }
}
// Obliczanie wartości firmy
double Firma::wartoscFirmy() const {
    if (historia_przychodow_.empty()) return 0.0;

    double suma = 0.0;
    for (double przychod : historia_przychodow_) {
        suma += przychod;
    }
    return suma / historia_przychodow_.size();
}
// Wyświetlanie listy pracowników
void Firma::drukujPracownikow() const {
    for (const auto& pracownik : pracownicy_) {
        pracownik->print();
    }
}
