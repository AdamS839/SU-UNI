#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Position{
    int x, y, dist;
};

bool operator==(Position const &p1, Position const &p2){
    return p1.x == p2.x && p1.y == p2.y;
}

bool validStep(int n, Position const &p){
    return p.x >= 0 && p.x < n && p.y >= 0 && p.y < n;
}

int minSteps(int n, Position const &start, Position const &end){
    std::queue<Position> pos;
    std::vector<std::vector<bool>> visited(n);

    std::fill(visited.begin(), visited.end(), std::vector<bool>(n, false));
    pos.push({start.x, start.y, 0});

    while(!pos.empty()){
        Position curr = pos.front();
        pos.pop();
        if (curr == end) return curr.dist;
        if (visited[curr.x][curr.y]) continue;
        visited[curr.x][curr.y] = true;
        for (int i = -2; i <= 2; ++i){
            for (int j = -2; j <= 2; ++j){
                if (i != 0 && j != 0 && abs(i) != abs(j)){
                    Position p{curr.x+i, curr.y+j, curr.dist+1};
                    if (validStep(n, p)){
                        pos.push(std::move(p));
                    }
                }
            }
        }
    }
    return -1;
}


int main() {

    int n = 3;
    Position start{0,0};
    Position end{1,0};
    std::cout << minSteps(n, start, end) << std::endl;

    return 0;
}