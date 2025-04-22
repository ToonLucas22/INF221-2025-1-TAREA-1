#include <algorithm>
#include <vector>

std::vector<int> selectionSort(std::vector<int>& arr){
    for (int i=0;i<arr.size();i++) {
        int lowPos = i;
        int low = arr[i];
        for (int j=i;j<arr.size();j++) {
            if (arr[j] < low) {
                low = arr[j];
                lowPos = j;
            }
        }
        std::swap(arr[i], arr[lowPos]);
    }
    return arr;
}