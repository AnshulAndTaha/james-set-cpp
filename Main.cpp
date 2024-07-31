#include <iostream>
#include <cmath>
#include <vector>

using std::vector;

// GLOBAL VARIABLES
vector<vector<int>> populations {};
vector<int> alienNumbers {};

int tetrate(int base, int height) {
    if(height < 0) return -1;
    if(height == 0) return 1;

    int result = base;
    for(int i = 1; i < height; i++) result = std::pow(result, base);
    return result;



vector<int> domesticOperations(vector<int> population) {
    vector<int> domesticOps = {};
    for(int num : population) {
        domesticOps.push_back(num + num);
        domesticOps.push_back(num * num);
        domesticOps.push_back(std::pow(num, num));
        domesticOps.push_back(tetrate(num, num));
    }
    return domesticOps;
}

vector<int> foreignOperations(vector<int> population) {
    vector<int> foreignOps = {};
    for(int i = 0; i < population.size(); i++) {
        for(int j = i + 1; j < population.size(); j++) {
            foreignOps.push_back(population[i] + population[j]);
            foreignOps.push_back(population[i] * population[j]);
            foreignOps.push_back(std::pow(population[i], population[j]));
            foreignOps.push_back(std::pow(population[j], population[i]));
            foreignOps.push_back(tetrate(population[i], population[j]));
            foreignOps.push_back(tetrate(population[j], population[i]));
        }
    }
    return foreignOps;
}

void printCycle(int idx) {
    std::cout << "\nCycle #" << idx << "\nPopulation: ";
    for(int num : populations[idx - 1]) std::cout << num << ", ";
    std::cout << "\nAlien: " << alienNumbers[idx - 1] << "\n";
}

void printResult(){
    for(int i = 1; i <= populations.size(); i++) printCycle(i);
}

int main() {
    printResult();
    return 0;
}