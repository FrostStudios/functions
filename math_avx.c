// Deine SQRT-Cluster erweitern
void avx_sqrt_batch(float* input, float* output, size_t count) {
    #pragma omp parallel for
    for (size_t i = 0; i < count; i += 8) {
        __m256 data = _mm256_loadu_ps(input + i);
        __m256 result = _mm256_sqrt_ps(data);
        _mm256_storeu_ps(output + i, result);
    }
}
