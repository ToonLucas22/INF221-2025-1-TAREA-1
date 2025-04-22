#include "selectionsort.cpp"
#include "mergesort.cpp"
#include <iostream>

int main() {
    std::vector<int> arr2(11);
    arr2 = {5, 2, 10, 7, 4, 3, 1, 13, 9, 12, 6};

    mergeSort(arr2);

    for (int i=0;i<arr2.size();i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << "\n";

    return 0;
}