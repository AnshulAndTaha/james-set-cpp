#include <iostream>
#include <cmath>
#include <set>
#include <vector>

using std::set;
using std::vector;

int tetrate(int base, int height);

vector<int>& foreignOperations(const set<int>& population);
vector<int>& domesticOperations(const set<int>& population);

void updateSet(const vector<int>& foreignPopulation, const vector<int>& domesticPopulation, vector<set<int>> population);
void updateAlien(const vector<set<int>>& populations, const vector<int>& alienNumbers){};

void runCycle(vector<set<int>>* populations, vector<int> alienNumbers, int cycleCount){};
void printResult(const vector<set<int>>& populations, const vector<int>& alienNumbers){};

void insert(vector<int>& values, int value) {
    if(shouldSort) {
        for(int i = 0; i < values.size(); i++) {
            if(value < values[i]) {
                values.insert(values.begin() + i, value);
                return;
            }
        }
    }
    values.push_back(value);
}

// ADJUSTABLE PARAMETERS
int tetrationLimit = 1;
bool shouldSort = false;

int main() {
    vector<set<int>> populations = {};
    vector<int> alienNumbers = {};
    
    runCycle(&populations, alienNumbers, 1);
    
    printResult(populations, alienNumbers);

    return 0;
}


void runCycle(vector<set<int>>* populations, vector<int> alienNumbers, int cycleCount) {
    vector<int> sortedVals;
    for(int i = 0; i < cycleCount; i++) {
        updateSet(
            foreignOperations((*populations)[i]), 
            domesticOperations((*populations)[i]), 
            populations);
    }
}

void printResult(const vector<set<int>>& populations, const vector<int>& alienNumbers){
    int index = 1;
    vector<vector<int>> populationsVector = {};
    for(set<int> population : populations) {
        vector<int> popVals = {};
        for(int num : population) {
            if(popVals.size() == 0) {
                popVals.push_back(num);
            } else {
                bool unlocated = true;
                int bottom = 0;
                int top = popVals.size() - 1;
                int mid = (bottom + top) / 2;
                while(unlocated) {  
                    if(popVals[mid] > num) {
                        top = mid;
                        if(mid <= 0) {
                            popVals.emplace(popVals.begin());
                            unlocated = false;
                        } else if(popVals[mid-1] <= num) {
                            popVals.emplace(popVals.begin()+mid+1, num);
                            unlocated = false;
                        }
                    } else if(popVals[mid] < num) {
                        mid = bottom;
                        if(mid >= popVals.size() - 1){
                            popVals.push_back(num);
                            unlocated = false;
                        } else if(popVals[mid+1] <= num) {
                            popVals.emplace(popVals.begin()+mid+1, num);
                            unlocated = false;
                        }
                    } else popVals.emplace(popVals.begin()+mid, num);
                    mid = (top+bottom) / 2;
                }
            }
        }
        for(int n : popVals) {
            printf("Population %d: %d\n", index, n);
            printf("Alien %d: %d\n", index, alienNumbers[index - 1]);
            printf("\n");
        }
        index++;
    }
}

void updateSet(const vector<int>& foreignPopulation, const vector<int>& domesticPopulation, vector<set<int>>* populations){
    set<int> newPopulation;

    for(int num : foreignPopulation) newPopulation.insert(num);
    for(int num : domesticPopulation) newPopulation.insert(num);

    (*populations).push_back(newPopulation);
}

vector<int>& foreignOperations(const set<int>& population) {
    vector<int> popVals(population.begin(), population.end());
    vector<int> values = {};
    for(int i = 0; i < population.size(); i++) {
        for(int j = i + 1; j < population.size(); j++) {
            values.push_back(popVals[i] + popVals[j]);
            values.push_back(popVals[i] * popVals[j]);
            values.push_back(std::pow(popVals[i], popVals[j]));
            values.push_back(std::pow(popVals[j], popVals[i]));
            if(j > tetrationLimit) values.push_back(tetrate(i, j));
            if(i > tetrationLimit) values.push_back(tetrate(j, i));
        }
    }
    return values;
};

vector<int>& domesticOperations(const set<int>& population) {
    vector<int> values {};
    for(int num : population) {
        values.push_back(num + num);
        values.push_back(num * num);
        values.push_back(std::pow(num, num));
        if(num > tetrationLimit) values.push_back(tetrate(num, num));
    }
    return values;
};

int tetrate(int base, int height) {
    int result = base;
    for (int i = 1; i < height; i++) result = pow(base, result);
    return result;
}