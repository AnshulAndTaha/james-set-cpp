#include <iostream>
#include <cmath>

int tetrate(int base, int height) {
    if(height < 0) return -1;
    if(height == 0) return 1;

    int result = base;
    for(int i = 1; i < height; i++) result = std::pow(result, base);
    return result;
}

int main() {
    std::cout << tetrate(3, 2) << std::endl;
    return 0;
}