#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "../../ScopedTimer.hpp"


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
    std::vector<int> bubleVector = generate_random_vector(10);
    std::vector<int> mergeSort(bubleVector.begin(), bubleVector.end());
    std::vector<int> sort(bubleVector.begin(), bubleVector.end());

    // printVector(mergeSort);

    {
        ScopedTimer timer("bubble_sort");
        bubble_sort(bubleVector);
    }

    {
        ScopedTimer timer2("merge_sort");
        merge_sort(mergeSort);
    }

    {
        ScopedTimer timer3("std_sort");
        std::sort(sort.begin(), sort.end());
    }

    /*
        On remarque qu'avec un petit tableau, le bubble sort est mieux que le merge sort et inverssement pour un grand tableau.
        Dans tous les cas, le std::sort est mieux que les deux autres.

        On peut en déduire qu'il faut choisir son algorithme de tri en fonction de nos besoins.
    */

    if(is_sorted(mergeSort)) {
        std::cout << "It's sorted" << std::endl;
    } else {
        std::cout << "It's not sorted" << std::endl;
    }

    //printVector(mergeSort);

    return 0;
}
