#include "game.hpp"

void menu(){
    std::cout << "\nDostępne komendy:\n";
    std::cout << "lp - Wylistuj pracowników\n";
    std::cout << "zinz - Zatrudnij inżyniera\n";
    std::cout << "zmag - Zatrudnij magazyniera\n";
    std::cout << "zmkt - Zatrudnij marketera\n";
    std::cout << "zrob - Zatrudnij robotnika\n";
    std::cout << "kred - Weź kredyt\n";
    std::cout << "kt - Zakończ turę\n";
    std::cout << "exit - Wyjdź z gry\n";
}

int main(){
    Firma firma;
    menu();

    while (true){
        std::cout << "\nTwoja firma:\n";
        std::cout << "Stan konta: " << firma.getStanKonta() << " PLN\n";
        std::cout << "Wartość firmy: " << firma.wartoscFirmy() << " PLN\n";

        std::string cmd;
        std::cout << "\nPodaj komendę: ";
        std::cin >> cmd;

        if (cmd == "lp"){
            firma.drukujPracownikow();
        } else if (cmd == "zinz"){
            firma.zatrudnij(std::make_unique<Inzynier>("Inzynier MELu", 5000.0, "MEiL"));
        } else if (cmd == "zmag"){
            firma.zatrudnij(std::make_unique<Magazynier>("Operator wozka widlowego", 3000.0, true));
        } else if (cmd == "zmkt"){
            firma.zatrudnij(std::make_unique<Marketer>("Copy-writer", 4000.0, 200));
        } else if (cmd == "zrob"){
            firma.zatrudnij(std::make_unique<Robotnik>("Wysokiej klasy fachowiec", 3500.0, 43.0)); //i nawet dostaje jesc
        } else if (cmd == "kred"){
            double kwota_kredytu;
            int czas_na_splate;
            std::cout << "Podaj kwotę kredytu: ";
            std::cin >> kwota_kredytu;
            std::cout << "Podaj czas spłaty (w miesiącach): ";
            std::cin >> czas_na_splate;
            firma.wezKredyt(kwota_kredytu, czas_na_splate);
        } else if (cmd == "kt"){
            firma.zaplacWynagrodzenie();
            firma.splacRaty();
            firma.otrzymajPrzychod();

            if (firma.getStanKonta() < 0){
                std::cout << "Twoja firma zbankrutowała!\n";
                break;
            } else if (firma.wartoscFirmy() > 100000.0){
                std::cout << "Gratulacje! Osiągnąłeś sukces ekonomiczny!\n";
                break;
            }
        } else if (cmd == "exit"){
            break;
        } else{
            std::cout << "Nieznana komenda!\n";
        }
    }

    return 0;
}
