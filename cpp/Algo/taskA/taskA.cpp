#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
    std::string pattern, str;
    std::vector<size_t> entries;
    std::vector<size_t> z;
    size_t left, right, pos;
    size_t m, count;

    void add(char ch) {
        str += ch;
        count++;
    }

    char get(size_t shift) {
        char ch;

        ch = str[pos + shift - m ];
        std::cout << shift << std::endl;

        return ch;
    }

    bool isComplete() {
        return (pos - m == count);
    }

    
public:
    Solution(std::string &pattern) : pattern(pattern), m(pattern.length()), count(0) {
        str = "";
    }

    void solve() {
        char ch;
        z.resize(m);
        z[0] = 0;
        pos = 1, left = 0, right = 0;
        size_t z_value = 0;
        

        while (!isComplete()) {
            std::cout << "pos | left | right = " << pos << " | " << left << " | " << right << std::endl;
            
            if (pos <= right) {
                z_value = std::min(right - pos + 1, z[pos - left]);
            } else {
                z_value = 0;
            }
            while (true) {
                if (pos + z_value < m) {
                    std::cout << "p[" << z_value << "]=" << pattern[z_value] << std::endl;
                    if (pattern[z_value] == pattern[pos + z_value] && z_value < m) {
                        z_value++;
                    } else {
                        break;
                    }
                } else {
                    if (z_value == m) {
                        //break;
                    }
                    if (std::cin >> ch) {
                        add(ch);
                    } 

                    std::cout << "t[" << pos + z_value << "]=" << ch << std::endl;
                    if (pattern[z_value] == get(z_value) && z_value < m) {
                        z_value++;
                    } else {
                        break;
                    }
                }  
            }
            std::cout << "z[" << pos << "]=" << z_value << std::endl;
            if (pos < m) {
                z[pos] = z_value;
            }

            if (pos + z_value - 1 > right) {
                left = pos;
                right = pos + z_value - 1;
                
            }

            

            if (pos >= m && z_value == m) {
                entries.push_back(pos - m);
            }
        
            pos++;
        
        }

    }

    void print() {
        for (auto i : entries) {
            std::cout << i << ' ';
        }
    }
};



int main() {
    freopen("input.txt", "r", stdin);
    std::string pattern;
    std::cin >> pattern;

    Solution solution(pattern);
    solution.solve();
    
    solution.print();
}
