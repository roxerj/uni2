#include "funkcijos.h"
#include "vector.h"
#include <vector>

int main() {
    // std::vector<int> stdVec = {1, 2, 3};
    // myVector<int> myVec = {1, 2, 3};
    // myVector<studentas> studentVec;
    // studentVec.emplace_back("Vardas", "Pavarde", 6);
    // studentVec.print();

    // stdVec.emplace_back(4);

    // myVec.emplace_back(4);
 
    // for(int i = 0; i < stdVec.size(); i++)
    // {
    //     std::cout << stdVec[i] << " ";
    // }
    // std::cout << std::endl;
    // myVec.print();
    studentas s1("John", "Doe");
    studentas s2("Alice", "Doe");
    std::cout << compare(s1, s2) << std::endl;
    std::cout << compare(s2, s1);

    return 0;
}
