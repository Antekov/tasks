#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
    std::string pattern, str, buffer;
    std::vector<size_t> entries;
    std::vector<size_t> z;
    size_t left, right, pos;
    size_t m; 
    int count;
    int buffer_size;

    void add(char ch) {
        //str += ch;
        count++;

        if (buffer.length() < buffer_size) {
            buffer += ch;
        } else {
            buffer[count % buffer_size] = ch;
        }

        //std::cout << str << std::endl;
        //std::cout << buffer << std::endl;
    }

    char get(size_t shift) {
        char ch;

        size_t needed_pos = shift;

        ch = str[needed_pos];
        

        return ch;
    }

    char getc(size_t shift) {
        char ch;

        if (shift < buffer_size) {
            return buffer[shift];
        }

        ch = buffer[(shift + 1) % buffer_size];
        
        return ch;
    }

    bool isComplete() {
        return (pos > count);
    }

    
public:
    Solution(std::string &pattern) : 
        pattern(pattern), 
        str(pattern),
        buffer(pattern),
        m(pattern.length()), 
        count(m),
        buffer_size(m+1) {}

    void solve() {
        char ch;
        z.resize(m);
        z[0] = 0;
        pos = 1, left = 0, right = 0;
        size_t z_value = 0;
        

        while (!isComplete()) {
            //std::cout << "pos | left | right | count = " << pos << " | " << left << " | " << right << " | " << count << std::endl;
            
            if (pos <= right) {
                z_value = std::min(right - pos + 1, z[pos - left]);
            } else {
                z_value = 0;
            }
            while (true) {
                if (pos + z_value < m) {
                    //std::cout << "p[" << z_value << "]=" << pattern[z_value] << std::endl;
                    if (pattern[z_value] == pattern[pos + z_value] && z_value < m) {
                        z_value++;
                    } else {
                        break;
                    }
                } else {
                    
                    if (pos + z_value >= count - 1)
                        if (std::cin >> ch) {
                            add(ch);
                        }

                    
                    //std::cout << " get[" << pos + z_value << "]=" << get(pos + z_value) << std::endl;
                    //std::cout << "getc[" << pos + z_value << "]=" << getc(pos + z_value) << std::endl;
                    if (pos + z_value < count && pattern[z_value] == getc(pos + z_value) && z_value < m) {
                        z_value++;
                    } else {
                        break;
                    }
                }  
            }
            //std::cout << "z[" << pos << "]=" << z_value << std::endl;
            
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
