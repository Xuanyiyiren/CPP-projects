// dotproduct.hpp
#pragma once
// #include <cstddef> // Include this header for size_t

float dotproduct(const float *p1, const float *p2, size_t n);
float dotproduct_unloop(const float *p1, const float *p2, size_t n);
float dotproduct_omp(const float *p1, const float *p2, size_t n);
float dotproduct_avx2(const float *p1, const float *p2, size_t n);
float dotproduct_avx2_omp(const float *p1, const float *p2, size_t n);
float dotproduct_neon(const float *p1, const float *p2, size_t n);
float dotproduct_neon_omp(const float *p1, const float *p2, size_t n);
