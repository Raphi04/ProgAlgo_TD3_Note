#include <iostream>

size_t folding_string_hash(std::string const& s, size_t max) {
    size_t hash { 0 };

    for(char c : s) {
        hash = (hash + c) % max;
    }

    return hash;
}

size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t hash { 0 };

    for(size_t i { 0 }; i < s.size(); i++) {
        hash = (hash + s[i] * (i + 1)) % max;
    }

    return hash;
}

int main() {

    std::cout << folding_string_hash("test", 2048) << std::endl;
    std::cout << folding_string_hash("tset", 2048) << std::endl;

    std::cout << folding_string_ordered_hash("test", 2048) << std::endl;
    std::cout << folding_string_ordered_hash("tset", 2048) << std::endl;



    return 0;
}