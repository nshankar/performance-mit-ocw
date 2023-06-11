/**
 * Copyright (c) 2012 MIT License by 6.172 Staff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/


#include "./util.h"

// Function prototypes
static inline void merge_f(data_t* A, data_t* left, int p, int q, int r);
static inline void copy_f(data_t* source, data_t* dest, int n);
static void sort_f_rec(data_t* A, data_t* left, int p, int r);

extern void isort(data_t* begin, data_t* end);

// A basic merge sort routine that sorts the subarray A[p..r]
void sort_f(data_t* A, int p, int r) {
  assert(A);
  if (r - p < 32) {
    isort(A + p, A + r + 1); // plus 1 because end is one past the end
  }
  else {
    data_t* left = 0;
    mem_alloc(&left, r-p+1);  // Preallocate memory for 'left' array
    if (left == NULL) {
      return;
    }
    sort_f_rec(A, left, p, r);
    mem_free(&left);  // Free the 'left' array after sorting
  }
}

// Recursive helper for sort_f
void sort_f_rec(data_t* A, data_t* left, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    sort_f_rec(A, left, p, q);
    sort_f_rec(A, left, q + 1, r);
    merge_f(A, left, p, q, r);
  }
}

// A merge routine. Merges the sub-arrays A [p..q] and A [q + 1..r].
// Uses the 'left' array in the merge operation.
static inline void merge_f(data_t* A, data_t* left, int p, int q, int r) {
  assert(A);
  assert(p <= q);
  assert((q + 1) <= r);
  int n1 = q - p + 1;

  copy_f(A + p, left, n1);

  int i = 0;
  int j = q + 1;

  for (int k = p; k <= r; k++) {
    if (j > r || (i < n1 && left[i] <= A[j])) {
      A[k] = left[i];
      i++;
    } else {
      A[k] = A[j];
      j++;
    }
  }
}

static inline void copy_f(data_t* source, data_t* dest, int n) {
  assert(dest);
  assert(source);

  for (int i = 0 ; i < n ; i++) {
    *(dest + i) = *(source + i);
  }
}
