# Radix Sort-Intel-One-API

## Introduction
Radix sort is an efficient sorting algorithm that works by sorting the input data according to the digits of each element, starting from the least significant digit and proceeding to the most significant digit. It is a non-comparative sorting algorithm, meaning that it does not rely on comparing the values of the elements being sorted. This makes it well-suited for sorting large lists of integers or strings, as it has a linear time complexity in the worst case.

## High level explanation
This implementation sorts the elements in the vector called ```data``` by dividing them into buckets based on their digits, and then flattening the buckets back into the original vector. The parallel_for function is used to parallelize the loop that divides the elements into buckets, allowing the work to be distributed among multiple threads.