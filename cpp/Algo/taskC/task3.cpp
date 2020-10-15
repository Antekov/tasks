#include <iostream>
#include <vector>

using namespace std;

// a-z
int const ALPHABET_SIZE = 26;

/** Структура вершины бора */
struct Vertex {
    /** Исходящие вершины */
    int edges[ALPHABET_SIZE];
    /** Переходы автомата из данной вершины */
    int edgeMove[ALPHABET_SIZE];
    /** Суффиксная ссылка из данной вершины */
    int link;
    /** Родительская вершина */
    int parent;
    /** Символ на ребре родитель - данная вершина */
    char parentSymbol;
    /** Флаг, является ли вершина концом шаблона */
    bool isLeaf;
    /** Шаблоны, с которыми связана данная вершина */
    vector<int> patternIndexes;

    /**
     * Создает вершину бора без исходящих вершин и суффиксных сыллок, не являющуюся концом шаблона.
     *
     * @param parent индекс родителя.
     * @param parentSymbol символ на ребре родитель - данная вершина.
     */
    Vertex(int parent, char parentSymbol) :
        parentSymbol(parentSymbol), 
        parent(parent), link(-1), isLeaf(false)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            edges[i] = -1;
            edgeMove[i] = -1;
        }
    }
};
        

class Automat {
public:
    /**
     * Автомат Ахо-Корасик для поиска частей шаблона без "?" из шаблона.
     *
     * @param pattern шаблон, состоящая из символов a-z и символов ?
     */
    Automat(const string & pattern);

    /**
     * Печатает индексы вхождения маски в тексте.
     *
     * @param text текст, в котором нужно найти вхождения.
     */
    void printMatchPositions(const string & text);

private:
    /**
     * Добавляет шаблон в бор. Использует поле #pattern
     *
     * @param subpatternPos пара <int, int> начало и конец строки включительно.
     * @param pattIndex номер шаблона.
     */
    void addPattern(const pair<int, int> & subpatternPos, int pattIndex);

    /**
     * Находит подшаблоны без символов ? в маске. Записывает результат в поле #subpatternpoitions_
     *
     * @param pattern маска.
     */
    void findSubpatternPositions(const string & pattern);

    int getSuffixLink(int index);
    int getLink(int index, char ch);

    /** Шаблон, для которого ищутся совпадения */
    string pattern;
    /** Вектор вершин бора */
    vector<Vertex> bohr;
    /** Вектор пар начало-конец подшаблона без символов "?" в шаблоне */
    vector<pair<int, int>> subpatternPositions;
};


Automat::Automat(const string & pattern) : 
    bohr(1, Vertex(0, -1)), pattern(pattern)
{
    bohr[0].link = 0;

    findSubpatternPositions(pattern);

    for (int i = 0; i < subpatternPositions.size(); i++) {
        addPattern(subpatternPositions[i], i);
    }
}


void Automat::addPattern(const pair<int, int> & subpatternPos, int pattIndex) {
    int currentVertex = 0;
    for (int i = subpatternPos.first; i <= subpatternPos.second; i++) {
        char ch = pattern[i] - 'a';
        if (bohr[currentVertex].edges[ch] == -1) {
            bohr.push_back(Vertex(currentVertex, ch));
            bohr[currentVertex].edges[ch] = (int)(bohr.size() - 1);
        }
        currentVertex = bohr[currentVertex].edges[ch];
    }
    bohr[currentVertex].isLeaf = true;
    bohr[currentVertex].patternIndexes.push_back(pattIndex);
}


int Automat::getSuffixLink(int index) {
    if (bohr[index].link == -1) {
        // Если суффиксная ссылка не определена 
        if (bohr[index].parent == 0) {
            // и вершина - потомок корня - задаем суффиксную ссылку, как ссылку на корень
            bohr[index].link = 0;
        } else {
            // иначе рекурсивно ищем суффиксную ссылку
            bohr[index].link = getLink(getSuffixLink(bohr[index].parent), bohr[index].parentSymbol);
        }
    }
    return bohr[index].link;
}


void Automat::findSubpatternPositions(const string &pattern) {
    pair<int, int> currentSubpatternPos;
    if (isalpha(pattern[0])) {
        currentSubpatternPos.first = 0;
    }
    if (pattern[1] == '?' && isalpha(pattern[0])) {
        currentSubpatternPos.second = 0;
        subpatternPositions.push_back(currentSubpatternPos);
    }

    for (int i = 1; i < pattern.length() - 1; i++) {
        if (pattern[i - 1] == '?' && isalpha(pattern[i])) {
            currentSubpatternPos.first = i;
        }
        if (pattern[i + 1] == '?' && isalpha(pattern[i])) {
            currentSubpatternPos.second = i;
            subpatternPositions.push_back(currentSubpatternPos);
        }
    }

    if (pattern[pattern.length() - 2] == '?' && isalpha(pattern[pattern.length() - 1])) {
        currentSubpatternPos.first = (int)pattern.length() - 1;
    }
    if (isalpha(pattern[pattern.length() - 1])) {
        currentSubpatternPos.second = (int)(pattern.length() - 1);
        subpatternPositions.push_back(currentSubpatternPos);
    }
}


int Automat::getLink(int index, char ch) {
    if (bohr[index].edgeMove[ch] == -1) {
        if (bohr[index].edges[ch] != -1) {
            bohr[index].edgeMove[ch] = bohr[index].edges[ch];
        } else if (index == 0) {
            bohr[index].edgeMove[ch] = 0;
        } else {
            bohr[index].edgeMove[ch] = getLink(getSuffixLink(index), ch);
        }
    }
    return bohr[index].edgeMove[ch];
}


void Automat::printMatchPositions(const string &text) {
    vector<int> matches(text.length());
    int v = 0;
    // Ищем вхождения всех подшаблонов и увеличиваем счетчик matches в индексе,
    // соответвующем началу маски.
    for (int i = 0; i < text.length(); i++) {
        v = getLink(v, text[i] - 'a');
        int u = v;
        do {
            if (bohr[u].isLeaf) {
                for (int index = 0; index < bohr[u].patternIndexes.size(); index++) {
                    int startIndex = i - subpatternPositions[bohr[u].patternIndexes[index]].second
                                     + subpatternPositions[bohr[u].patternIndexes[index]].first;

                    if ((startIndex - subpatternPositions[bohr[u].patternIndexes[index]].first >= 0) &&
                        (startIndex - subpatternPositions[bohr[u].patternIndexes[index]].first +
                         pattern.length() - 1 < text.length())) {
                        matches[startIndex - subpatternPositions[bohr[u].patternIndexes[index]].first]++;
                    }
                }
            }
            u = getSuffixLink(u);
        } while (u != 0);
    }

    // Если индекс равен количеству подшаблонов, он является вхождением подстроки
    vector<int> result;
    for (int i = 0; i < matches.size(); i++) {
        if (matches[i] == subpatternPositions.size()) {
            cout << i << ' ';
        }
    }
}


int main() {
    string pattern, text;
    cin.sync_with_stdio(false);
    cin.tie(NULL);
    cin >> pattern >> text;

    Automat Automat(pattern);

    Automat.printMatchPositions(text);
    
    return 0;
}