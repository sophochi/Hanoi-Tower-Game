#pragma once
#include <vector>

class TowerSolver 
{
public:
    // «бер≥гаЇ рекурсивн≥ кроки у вектор (зв≥дки, куди)
    static void solveHanoi(int n, int from, int to, int aux, std::vector<std::pair<int, int>>& moves);
};
