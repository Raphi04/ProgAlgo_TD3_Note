#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

bool is_sorted(std::vector<int> const& vec) {
    return std::is_sorted(vec.begin(), vec.end());
}

void bubble_sort(std::vector<int> & vec) {
    int decrement { 0 };
    for(size_t j {0} ; j < vec.size() - 1; j++) {
        for(size_t i { 0 }; i < (vec.size() - decrement  -1); i++) {
            if(vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
            }
        }
        decrement++;
    }
};

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

void printVector(std::vector<int> const& vec) {
    for(int const& number : vec) {
        std::cout << number << std::endl;
    }
}

int main() {
    std::vector<int> myVector = generate_random_vector(10);

    bubble_sort(myVector);

    if(is_sorted(myVector)) {
        std::cout << "It's sorted" << std::endl;
    } else {
        std::cout << "It's not sorted" << std::endl;
    }

    printVector(myVector);

    return 0;
}