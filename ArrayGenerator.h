#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

class ArrayGenerator {
 public:
  static std::vector<int> generateRandomArray(int size, int minValue, int maxValue) {
    std::vector<int> array(size);
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(minValue, maxValue);

    for (int &val : array) {
      val = dist(rng);
    }
    return array;
  }

  static std::vector<int> generateReversedArray(int size) {
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i) {
      array[i] = size - i;
    }
    return array;
  }

  static std::vector<int> generateNearlySortedArray(int size, int swaps) {
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i) {
      array[i] = i;
    }

    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, size - 1);

    for (int i = 0; i < swaps; ++i) {
      int idx1 = dist(rng);
      int idx2 = dist(rng);
      std::swap(array[idx1], array[idx2]);
    }

    return array;
  }
};

#endif // ARRAY_GENERATOR_H
