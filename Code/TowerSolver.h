#pragma once
#include <vector>

class TowerSolver 
{
public:
    // ������ ��������� ����� � ������ (�����, ����)
    static void solveHanoi(int n, int from, int to, int aux, std::vector<std::pair<int, int>>& moves);
};
