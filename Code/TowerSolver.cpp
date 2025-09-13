#include "TowerSolver.h"

// n � ������� �����
// from � ���������� �������� (0, 1 ��� 2)
// to � ������� ��������
// aux � ��������� ��������
// moves � ������ ���, �� ������������� ��� �����: (�����, ����)


// ����������� �������� ��������� ���
void TowerSolver::solveHanoi(int n, int from, int to, int aux, std::vector<std::pair<int, int>>& moves) 
{
    if (n == 1) 
    {
        // ������� ������� - ������ ���������� ����
        moves.push_back({ from, to });
        return;
    }

    // ���� 1 - ���������� n-1 ����� �� ��������� ��������
    solveHanoi(n - 1, from, aux, to, moves);

    // ���� 2 - ���������� ��������� ���� �� �������� ��������
    moves.push_back({ from, to });

    // ���� 3 - ���������� n-1 ����� � ���������� �� ��������
    solveHanoi(n - 1, aux, to, from, moves);
}

