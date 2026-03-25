#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>


bool is_sorted(std::vector<int> const& vec) {
    return std::is_sorted(vec.begin(), vec.end());
}

void merge_sort(std::vector<int> & vec);

void merge_sort_merge(std::vector<int> & vec, size_t const left, size_t const middle, size_t const right) {
    std::vector<int> vec2(vec.begin(), vec.begin() + middle);
    std::vector<int> vec3(vec.begin() + middle, vec.end());
    std::vector<int> vec4(vec.size());

    merge_sort(vec2);
    merge_sort(vec3);

    size_t iVec2 { 0 };
    size_t iVec3 { 0 };
    size_t iVec4 { 0 };

    while(iVec4 != vec4.size()) {
        while (iVec2 < vec2.size() && iVec3 < vec3.size()) {
            if(vec2[iVec2] < vec3[iVec3]) {
                vec4[iVec4] = vec2[iVec2];
                iVec2++;
            } else {
                vec4[iVec4] = vec3[iVec3];
                iVec3++;
            }
            
            iVec4++;
        }
        
        if(iVec2 != vec2.size()) {
            vec4[iVec4] = vec2[iVec2];
            iVec2++;
        } else {
            vec4[iVec4] = vec3[iVec3];
            iVec3++;
        }

        iVec4++;
    }

    vec = vec4;
}

void merge_sort(std::vector<int> & vec, size_t const left, size_t const right) {
    size_t length { right - left + 1 };
    size_t middle { (unsigned)(length / 2) };

    merge_sort_merge(vec, left, middle, right);
}

void merge_sort(std::vector<int> & vec) {
    if(vec.size() > 1) {
        merge_sort(vec, 0, vec.size() - 1);
    }
}

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

    merge_sort(myVector);

    if(is_sorted(myVector)) {
        std::cout << "It's sorted" << std::endl;
    } else {
        std::cout << "It's not sorted" << std::endl;
    }

    printVector(myVector);

    return 0;
}