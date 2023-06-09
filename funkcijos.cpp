#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "funkcijos.h"
#include "vector.h"
#include <chrono>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <list>
#include <deque>
#include <filesystem>
#include <iterator>
#define _CRT_SECURE_NO_WARNINGS


/**
 * Generate student data and save it to a file.
 * Let the user choose action: generate a new file or work with an existing one. Then let the user choose the file.
 * @return The name of the generated file.
 */
std::string generavimas()
{
    std::string failo_pavadinimas;
    int choice, studentu_skaicius;
    std::string testas;

    while (true) 
    {
        std::cout << "Iveskite 1, jei norite generuoti studentu faila, iveskite 2, jei norite atlikti veiksmus su esamu failu, arba 3, jei norite iseiti: ";
        std::cin >> choice;

        try 
        {
            if (std::cin.fail()) 
            {
                throw std::runtime_error("Klaida: blogas pasirinkimas. Pasirinkite 1, 2 arba 3");
            }

            if (choice == 1) 
            {
                std::cout << "Kiek bus studentu? ";
                std::cin >> studentu_skaicius;

                try {
                    if (std::cin.fail() || studentu_skaicius <= 0) 
                    {
                        throw std::runtime_error("Klaida: neteisingai ivestas studentu skaicius");
                    }

                    testas = generuoti(studentu_skaicius);
                    failo_pavadinimas = "stud" + std::to_string(studentu_skaicius) + ".txt";

                    std::ofstream out_file(failo_pavadinimas);

                    if (!out_file.is_open()) 
                    {
                        throw std::runtime_error("Klaida: nepavyko sukurti failo");
                    }

                    out_file << testas;
                    out_file.close();
                    
                    break;
                }
                catch (const std::runtime_error& e) 
                {
                    std::cout << e.what() << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            else if (choice == 2) 
            {
                std::cout << "Esami failai:\n";

                for (const auto& entry : std::filesystem::directory_iterator(".")) 
                {
                    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                        std::cout << entry.path().filename() << std::endl;
                    }
                }


                std::cout << "Iveskite failo pavadinima: ";
                std::cin >> failo_pavadinimas;

                std::ifstream in_file(failo_pavadinimas);

                if (!in_file) 
                {
                    throw std::runtime_error("Klaida: failas " + failo_pavadinimas + " neegzistuoja");
                }

                in_file.close();
                
                
                
                break;
            }

            else if (choice == 3) 
            {
                std::cout << "Programa baige darba";
                exit(0);
            }

            else 
            {
                throw std::runtime_error("Klaida: blogas pasirinkimas. Pasirinkite 1, 2 arba 3");
            }
        }
        catch (const std::runtime_error& e) 
        {
            std::cout << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return failo_pavadinimas;
}

/**
 * Calculate the average value from a vector of integers.
 *
 * @param nd_vec The vector of integers.
 * @return The average value.
 */
float count_vid(const std::vector<int> &nd_vec)
{
    float temp = 0;
    for(auto &pazymys:nd_vec)
    {
        temp += pazymys;
    }
    return temp/float(nd_vec.size());
}

/**
 * Calculate the median value from a vector of integers.
 *
 * @param nd_vec The vector of integers.
 * @return The median value.
 */
float count_med(std::vector<int> &nd_vec)
{
    std::sort(nd_vec.begin(), nd_vec.end());
    if(nd_vec.size() % 2 != 0)
    {
        return nd_vec.at((nd_vec.size() - 1) / 2);
    }
    else
    {
        return (float(nd_vec.at((nd_vec.size()/2) - 1)) + float(nd_vec.at(nd_vec.size()/2))) / 2;
    }
}


/**
 * Compare two instances of the studentas class.
 *
 * @param s1 The first studentas object.
 * @param s2 The second studentas object.
 * @return True if s1 is considered "smaller" than s2, false otherwise.
 */
bool compare(const studentas& s1, const studentas& s2) {
    if(s1.getPavarde() == s2.getPavarde())
    {
        return s1.getVardas() < s2.getVardas();
    }
    else
    {
        return s1.getPavarde() < s2.getPavarde();
    }
}

/**
 * Generate a string with student data.
 *
 * @param count The number of students to generate.
 * @return The generated string.
 */
std::string generuoti(int count)
{
    Timer generate_timer;
    generate_timer.start();

    std::string failas;
    std::string temp_vardas = "Vardas";
    std::string temp_pavarde = "Pavarde";
    srand((unsigned) time(NULL));
    
    
    const int vardas_width = 25;
    const int pazymys_width = 8;
    const int line_width = (vardas_width * 2) + (pazymys_width * 7) + pazymys_width + 1;
    
    
    char header[line_width + 1];
    std::sprintf(header, "%-*s%-*s", vardas_width, "Vardas", vardas_width, "Pavarde");
    for(int i = 1; i <= 7; i++) 
    {
        std::sprintf(header + strlen(header), "%-*s", pazymys_width, ("ND" + std::to_string(i)).c_str());
    }
    std::sprintf(header + strlen(header), "%-*s\n", pazymys_width, "Egz.");
    failas += header;
    
    
    for(int i = 0; i < count; i++)
    {
        char line[line_width + 1];
        std::string vardas = temp_vardas + std::to_string(i+1);
        std::string pavarde = temp_pavarde + std::to_string(i+1);
        std::sprintf(line, "%-*s%-*s", vardas_width, vardas.c_str(), vardas_width, pavarde.c_str());
        
        
        for(int j = 0; j < 7; j++) 
        {
            int random = rand() % 10 + 1;
            std::sprintf(line + strlen(line), "%-*d", pazymys_width, random);
        }
        
    
        int random = rand() % 10 + 1;
        std::sprintf(line + strlen(line), "%-*d\n", pazymys_width, random);
        failas += line;
    }
    generate_timer.stop();
    std::cout << "Generavimas uztruko " << generate_timer.elapsed() << " sec" << std::endl;
    return failas;

    
}

/**
 * Calculate the final grade from a vector of integers and an exam score.
 *
 * @param nd_vec The vector of integers.
 * @param egz The exam score.
 * @return The final grade.
 */
float countGalutinis(const std::vector<int>& nd_vec, int egz) 
    {
        return 0.4 * count_vid(nd_vec) + 0.6 * egz;
    }


