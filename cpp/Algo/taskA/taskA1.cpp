#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
    std::string pattern_;
    std::string input_string_;
    std::vector<size_t> entries_;
public:
    Solution(std::string &pattern_, std::string &input_string_) : pattern_(pattern_), input_string_(input_string_) {}

    std::vector<size_t> solve() {
        int index = -1;
        std::string new_string = pattern_ + input_string_;
        int new_length = input_string_.length() + pattern_.length();

        std::vector<int> z_function(new_length);
        for (int start = 1, left = 0, right = 0; start < new_length; start++) {
            if (start <= right) {
                z_function[start] = std::min(right - start + 1, z_function[start - left]);
            }
            while (start + z_function[start] < new_length && new_string[z_function[start]] == new_string[start + z_function[start]] && z_function[start] < pattern_.length()) {
                z_function[start]++;
            }
            if (start + z_function[start] - 1 > right) {
                left = start;
                right = start + z_function[start] - 1;
            }
            if (start >= pattern_.length() && z_function[start] == pattern_.length()) {
                entries_.push_back(start - pattern_.length());
            }
        }
        return entries_;
    }
};

int main() {
    std::string pattern;
    std::string input_string;
    std::cin >> pattern >> input_string;
    Solution solution(pattern, input_string);
    
    for (auto i : solution.solve()) {
        std::cout << i << ' ';
    }
}
