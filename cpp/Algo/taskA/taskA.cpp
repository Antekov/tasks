#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
    std::string pattern_, buffer_;
    std::vector<size_t> entries_;
    
    size_t left, right, pos;
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

    bool isComplete() {
        return (pos > symbol_count_);
    }
    
public:
    Solution(std::string &pattern_) : 
        pattern_(pattern_),
        buffer_(pattern_),
        symbol_count_(pattern_.length()), 
        buffer_size_(pattern_.length() + 1) {}

    std::vector<size_t> solve() {
        char ch;
        size_t z_value = 0;
        size_t m = pattern_.length();
        std::vector<size_t> z_function(m);

        z_function[0] = 0;
        pos = 1;
        left = 0;
        right = 0;
        
        while (!isComplete()) {
            //std::cout << "pos | left | right | symbol_count_ = " << pos << " | " << left << " | " << right << " | " << symbol_count_ << std::endl;
            
            if (pos <= right) {
                z_value = std::min(right - pos + 1, z_function[pos - left]);
            } else {
                z_value = 0;
            }
            while (true) {
                if (pos + z_value < m) {
                    //std::cout << "p[" << z_value << "]=" << pattern_[z_value] << std::endl;
                    if (pattern_[z_value] == pattern_[pos + z_value] && z_value < m) {
                        z_value++;
                    } else {
                        break;
                    }
                } else {
                    
                    if (pos + z_value >= symbol_count_ - 1)
                        if (std::cin >> ch) {
                            addSymbol(ch);
                        }

                    
                    //std::cout << " get[" << pos + z_value << "]=" << get(pos + z_value) << std::endl;
                    //std::cout << "getc[" << pos + z_value << "]=" << getc(pos + z_value) << std::endl;
                    if (pos + z_value < symbol_count_ && pattern_[z_value] == getSymbol(pos + z_value) && z_value < m) {
                        z_value++;
                    } else {
                        break;
                    }
                }  
            }
            //std::cout << "z[" << pos << "]=" << z_value << std::endl;
            
            if (pos < m) {
                z_function[pos] = z_value;
            }

            if (pos + z_value - 1 > right) {
                left = pos;
                right = pos + z_value - 1;
            }

            if (pos >= m && z_value == m) {
                entries_.push_back(pos - m);
            }
        
            pos++;
        }
        return entries_;
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
