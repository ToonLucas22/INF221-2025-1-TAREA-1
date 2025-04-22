#include <algorithm>
#include <vector>

void mergeAux(std::vector<int>& arr, int posL, int posR) {
    int size = posR-posL;
    
    if (size<=1) return;
    
    int left = posL;
    int mid = left+(size/2);
    int right = mid;

    mergeAux(arr, left, mid);
    mergeAux(arr, mid, posR);

    std::vector<int> merged;

    while (left < mid && right < posR) {
        if (arr[left] < arr[right]) {
            merged.push_back(arr[left]);
            left++;
        }
        else {
            merged.push_back(arr[right]);
            right++;
        }
    }
    while (left < mid) {
        merged.push_back(arr[left]);
        left++;
    }
    while (right < posR) {
        merged.push_back(arr[right]);
        right++;
    }

    for (int i=0;i<size;i++) {
        arr[posL+i] = merged[i];
    }

    merged.clear();

    return;
}

std::vector<int> mergeSort(std::vector<int>& arr){
    if (arr.size()<=1) return arr;

    mergeAux(arr, 0, arr.size());

    return arr;
}