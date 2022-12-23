#include <iostream>
#include <stdlib.h>
#include <tbb/tbb.h>
#include "oneapi/tbb/blocked_range.h"
#include "oneapi/tbb/parallel_for.h"
#include <climits>


using namespace std;
using namespace oneapi;

template <typename T>
void radix_sort(std::vector<T>& data, int num_bits) {
  // Create a bucket for each possible value of a digit
  std::vector<std::vector<T>> buckets(1 << num_bits);

  // Iterate over each digit in the keys
  for (int shift = 0; shift < sizeof(T) * 8; shift += num_bits) {
    // Divide the elements into buckets based on the current digit
    tbb::parallel_for(
        tbb::blocked_range<size_t>(0, data.size()),
        [&](const tbb::blocked_range<size_t>& range) {
          for (size_t i = range.begin(); i < range.end(); ++i) {
            auto& element = data[i];
            auto bucket = (element >> shift) & ((1 << num_bits) - 1);
            buckets[bucket].push_back(element);
          }
        });

    // Flatten the buckets back into the original vector
    size_t i = 0;
    for (auto& bucket : buckets) {
      for (auto& element : bucket) {
        data[i++] = element;
      }
      bucket.clear();
    }
  }
}

int main() {
    // Initialize the original vector
    std::vector<int> data{128, 3, 8, 1, 2, 4, 7, 6};
    // Get the maximum value of the vector 
    double max = *max_element(data.begin(), data.end());
    // Get the number of bits of the maximum value in the vector
    int numberOfBits = floor(log2(max)) + 1;
    std::cout << numberOfBits << " <- number of bits" << std::endl;
    // Sort the data
    radix_sort(data, numberOfBits);
    for (auto x : data) {
        std::cout << x << " ";
    }
    return 0;
}
