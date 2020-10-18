#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
    std::string pattern_, buffer_;
            
    size_t symbol_count_;
    size_t buffer_size_;

    void addSymbol(char ch) {
        symbol_count_++;

        if (buffer_.length() < buffer_size_) {
            buffer_ += ch;
        } else {
            buffer_[symbol_count_ % buffer_size_] = ch;
        }
    }

    char getSymbol(size_t index) {
        if (index < buffer_size_) {
            return buffer_[index];
        }

        return buffer_[(index + 1) % buffer_size_];
    }
    
public:
    Solution(std::string &pattern) : 
        pattern_(pattern),
        buffer_(pattern),
        symbol_count_(pattern.length()), 
        buffer_size_(pattern.length() + 1) {}

    std::vector<size_t> solve() {
        char ch;
        size_t z_value = 0;
        std::vector<size_t> z_function(pattern_.length());
        std::vector<size_t> entries;
        size_t left, right, pos;

        z_function[0] = 0;
        pos = 1;
        left = 0;
        right = 0;
        
        while (pos <= symbol_count_) {
            if (pos <= right) {
                z_value = std::min(right - pos + 1, z_function[pos - left]);
            } else {
                z_value = 0;
            }
            while (true) {
                if (pos + z_value < pattern_.length()) {
                    if (pattern_[z_value] == pattern_[pos + z_value] && z_value < pattern_.length()) {
                        z_value++;
                    } else {
                        break;
                    }
                } else {
                    if (pos + z_value >= symbol_count_ - 1) {
                        if (std::cin >> ch) {
                            addSymbol(ch);
                        }
                    }

                    if (pos + z_value < symbol_count_ && pattern_[z_value] == getSymbol(pos + z_value) && z_value < pattern_.length()) {
                        z_value++;
                    } else {
                        break;
                    }
                }  
            }
            
            if (pos < pattern_.length()) {
                z_function[pos] = z_value;
            }

            if (pos + z_value - 1 > right) {
                left = pos;
                right = pos + z_value - 1;
            }

            if (pos >= pattern_.length() && z_value == pattern_.length()) {
                entries.push_back(pos - pattern_.length());
            }
        
            pos++;
        }
        return entries;
    }
};

int main() {
    std::string pattern;
    std::cin >> pattern;

    Solution solution(pattern);

    for (auto i : solution.solve()) {
        std::cout << i << ' ';
    }
}
