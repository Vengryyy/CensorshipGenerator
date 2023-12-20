#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include "words.h"

std::string catchRandomCensored(std::vector<std::string>& censored)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, censored.size() - 1);
    int index = distr(gen);
    std::string censoredToReturn = std::move(censored[index]);
    censored.erase(censored.begin() + index);
    return censoredToReturn;
}

int main()
{
    std::setlocale(LC_ALL, "ru-RU");

    while (true)
    {
        int countOfCensored;
        std::cout << "Введите кол-во словосочетаний (Не рекомендуется вводить более 100000000): ";
        std::cin >> countOfCensored;

        if (countOfCensored <= 0)
        {
            std::cout << "Некорректное значение. Пожалуйста, введите положительное число." << std::endl;
            continue;
        }

        std::vector<std::string> censoredNew;
        censoredNew.reserve(countOfCensored);

        std::vector<std::string> censoredClone = censoredOriginal;
        censoredClone.reserve(countOfCensored * censoredOriginal.size());

        while (censoredClone.size() < countOfCensored)
        {
            for (const auto& censored : censoredOriginal)
            {
                censoredClone.emplace_back(censored);
            }
        }

        std::shuffle(censoredClone.begin(), censoredClone.end(), std::mt19937(std::random_device()()));

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 10);

        for (int i = 0; i < countOfCensored; i++)
        {
            std::string end;
            int choice = distr(gen);
            if (choice < 5)
                if (choice < 3)
                    end = ". ты ";
                else end = ", ";
            else if (choice < 7)
            {
                std::vector<std::string> censoredAdvancedClone = censoredOriginalAdvanced;
                std::uniform_int_distribution<> distr2(0, censoredAdvancedClone.size()-1);
                end = " " + censoredAdvancedClone[distr2(gen)] + ", ";
            }
            else end = ", ";
            if (i != countOfCensored-1)
                std::cout << censoredNew.emplace_back(catchRandomCensored(censoredClone)) << end;
            else
                std::cout << censoredNew.emplace_back(catchRandomCensored(censoredClone)) << ' ';
        }

        std::cout << std::endl;
    }

    return 0;
}
