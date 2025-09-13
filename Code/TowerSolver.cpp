#include "TowerSolver.h"

// n Ч к≥льк≥сть диск≥в
// from Ч початковий стрижень (0, 1 або 2)
// to Ч к≥нцевий стрижень
// aux Ч допом≥жний стрижень
// moves Ч вектор пар, що представл€ють рух диск≥в: (зв≥дки, куди)


// рекурсивний розвТ€зок ’анойськоњ веж≥
void TowerSolver::solveHanoi(int n, int from, int to, int aux, std::vector<std::pair<int, int>>& moves) 
{
    if (n == 1) 
    {
        // базовий випадок - просто переносимо диск
        moves.push_back({ from, to });
        return;
    }

    // крок 1 - перем≥стити n-1 диск≥в на допом≥жний стрижень
    solveHanoi(n - 1, from, aux, to, moves);

    // крок 2 - перем≥стити найб≥льший диск на ц≥льовий стрижень
    moves.push_back({ from, to });

    // крок 3 - перем≥стити n-1 диск≥в з допом≥жного на ц≥льовий
    solveHanoi(n - 1, aux, to, from, moves);
}

