#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>


class sparseTable
{
    struct Node {
        int stat = 0, index = 0;

        Node(int stat=0, int index=0): stat(stat), index(index) {}
        bool operator< (Node& other) { return stat < other.stat; }
    };
    
    typedef std::pair<Node, Node> Vertex;
   
    std::vector<std::vector<Vertex>> table;
    std::vector<int> logCeil;

    Vertex min(Vertex x, Vertex y);
    int exp2(int pow) { return (1 << pow); }

public:
    sparseTable(std::vector<int>& array);
    int getStat(int limitLeft, int limitRight);
};


sparseTable::Vertex sparseTable::min(Vertex x, Vertex y)
{
    std::vector<Node> sorted;
    sorted.push_back(x.first);
    sorted.push_back(x.second);
    sorted.push_back(y.first);
    sorted.push_back(y.second);

    std::sort(sorted.begin(), sorted.end());

    Vertex minVertex;

    minVertex.first = sorted[0];

    int i = 1;
    while(sorted[0].index == sorted[i].index) {
        i++;
    }

    minVertex.second = sorted[i];

    return minVertex;
}


sparseTable::sparseTable(std::vector<int>& array)
{
    for (int i = 0; i <= array.size(); i++) {
        logCeil.push_back((int)(ceil(log2(i))));
    }

    table.resize(logCeil[array.size()]);
    for(int i = 0; i < table.size(); i++) {
        table[i].resize(array.size(), {Node(2147483647, -1), Node(2147483647, -1)});
    }

    for(int i = 0; i < array.size(); i++) {
        table[0][i] = {Node(array[i], i), Node(array[i], i)};
    }

    for(int i = 1; i < table.size(); i++) {
        for(int j = 0; j < table[i].size() - exp2(i) + 1; j++) {
            table[i][j] = min(table[i - 1][j], table[i - 1][j + exp2(i - 1)]);
        }
    }
}

int sparseTable::getStat(int limitLeft, int limitRight)
{
    int log = logCeil[limitRight - limitLeft + 1] - 1;

    Vertex ans = min(table[log][limitLeft], table[log][limitRight - exp2(log) + 1]);

    return ans.second.stat;
}


int main()
{
    int seqSize, rangeAmount;
    std::cin >> seqSize >> rangeAmount;

    std::vector<int> sequence(seqSize);

    for (int i = 0; i < seqSize; i++)
    {
        std::cin >> sequence[i];
    }

    sparseTable sparseTable(sequence);

    for(int i = 0; i < rangeAmount; i++){
        int limitLeft, limitRight;
        std::cin >> limitLeft >> limitRight;

        limitLeft--;
        limitRight--;

        std::cout << sparseTable.getStat(limitLeft, limitRight) << std::endl;
    }

    return 0;
}