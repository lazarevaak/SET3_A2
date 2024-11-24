#include <iostream>
#include <vector>
#include <chrono>
#include "ArrayGenerator.h"

class SortTester {
 public:
  static void mergeSort(std::vector<int> &array, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
  }

  static void merge(std::vector<int> &array, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
      if (array[i] <= array[j]) {
        temp[k++] = array[i++];
      } else {
        temp[k++] = array[j++];
      }
    }

    while (i <= mid) {
      temp[k++] = array[i++];
    }

    while (j <= right) {
      temp[k++] = array[j++];
    }

    for (int l = 0; l < temp.size(); ++l) {
      array[left + l] = temp[l];
    }
  }

  static void insertionSort(std::vector<int> &array, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
      int key = array[i];
      int j = i - 1;

      while (j >= left && array[j] > key) {
        array[j + 1] = array[j];
        --j;
      }
      array[j + 1] = key;
    }
  }

  static void hybridMergeSort(std::vector<int> &array, int left, int right, int threshold) {
    if (right - left + 1 <= threshold) {
      insertionSort(array, left, right);
      return;
    }

    int mid = left + (right - left) / 2;

    hybridMergeSort(array, left, mid, threshold);
    hybridMergeSort(array, mid + 1, right, threshold);
    merge(array, left, mid, right);
  }

  static long long measureSortTime(void (*sortFunction)(std::vector<int>&, int, int), std::vector<int> array) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(array, 0, array.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  }

  static long long measureHybridSortTime(std::vector<int> array, int threshold) {
    auto start = std::chrono::high_resolution_clock::now();
    hybridMergeSort(array, 0, array.size() - 1, threshold);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  }
};

int main() {
  const int minSize = 500, maxSize = 10000, step = 100, minValue = 0, maxValue = 6000, swaps = 10;
  std::vector<int> sizes;
  for (int i = minSize; i <= maxSize; i += step) {
    sizes.push_back(i);
  }

  // Test cases
  for (int size : sizes) {
    std::vector<int> randomArray = ArrayGenerator::generateRandomArray(size, minValue, maxValue);
    std::vector<int> reversedArray = ArrayGenerator::generateReversedArray(size);
    std::vector<int> nearlySortedArray = ArrayGenerator::generateNearlySortedArray(size, swaps);

    long long mergeTimeRandom = SortTester::measureSortTime(SortTester::mergeSort, randomArray);
    long long hybridTimeRandom = SortTester::measureHybridSortTime(randomArray, 30);

    std::cout << "Array size: " << size << " | MergeSort Random: " << mergeTimeRandom
              << " ms | HybridSort Random: " << hybridTimeRandom << " ms\n";
  }

  return 0;
}
