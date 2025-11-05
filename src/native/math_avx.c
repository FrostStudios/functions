#include <immintrin.h>
#include <node_api.h>
#include <stdlib.h>
#include <omp.h>

// Deine SQRT-Cluster-Logik - optimiert
void avx_sqrt_batch(float* input, float* output, size_t count) {
    #pragma omp parallel for
    for (size_t i = 0; i < count; i += 8) {
        if (i + 8 <= count) {
            __m256 data = _mm256_loadu_ps(input + i);
            __m256 sqrt_val = _mm256_sqrt_ps(data);
            _mm256_storeu_ps(output + i, sqrt_val);
        }
    }
    
    // Restliche Elemente seriell verarbeiten
    #pragma omp parallel for
    for (size_t i = count - (count % 8); i < count; i++) {
        output[i] = input[i] * input[i]; // Quadrat für Test
    }
}

// AVX-Summe für Performance-Vergleich
float avx_sum_batch(float* input, size_t count) {
    __m256 sum_vec = _mm256_setzero_ps();
    
    for (size_t i = 0; i < count; i += 8) {
        if (i + 8 <= count) {
            __m256 data = _mm256_loadu_ps(input + i);
            sum_vec = _mm256_add_ps(sum_vec, data);
        }
    }
    
    // Horizontal sum
    float sum_array[8];
    _mm256_storeu_ps(sum_array, sum_vec);
    
    float total = 0.0f;
    for (int i = 0; i < 8; i++) {
        total += sum_array[i];
    }
    
    // Restliche Elemente
    for (size_t i = count - (count % 8); i < count; i++) {
        total += input[i];
    }
    
    return total;
}

// Node.js Binding für SQRT Batch
NAPI_METHOD(napi_avx_sqrt_batch) {
    napi_status status;
    
    // Input ArrayBuffer
    napi_value input_buffer;
    size_t input_length;
    float* input_data;
    
    status = napi_get_arraybuffer_info(env, args[0], (void**)&input_data, &input_length);
    if (status != napi_ok) return NULL;
    
    size_t element_count = input_length / sizeof(float);
    
    // Output ArrayBuffer erstellen
    napi_value output_buffer;
    float* output_data;
    
    status = napi_create_arraybuffer(env, input_length, (void**)&output_data, &output_buffer);
    if (status != napi_ok) return NULL;
    
    // AVX Processing
    avx_sqrt_batch(input_data, output_data, element_count);
    
    return output_buffer;
}

// Node.js Binding für Sum Batch
NAPI_METHOD(napi_avx_sum_batch) {
    napi_status status;
    
    napi_value input_buffer;
    size_t input_length;
    float* input_data;
    
    status = napi_get_arraybuffer_info(env, args[0], (void**)&input_data, &input_length);
    if (status != napi_ok) return NULL;
    
    size_t element_count = input_length / sizeof(float);
    float sum = avx_sum_batch(input_data, element_count);
    
    napi_value result;
    status = napi_create_double(env, (double)sum, &result);
    if (status != napi_ok) return NULL;
    
    return result;
}

// Module Init
NAPI_MODULE_INIT() {
    napi_value sqrt_func, sum_func;
    
    napi_create_function(env, "avxSqrtBatch", NAPI_AUTO_LENGTH, napi_avx_sqrt_batch, NULL, &sqrt_func);
    napi_set_named_property(env, exports, "avxSqrtBatch", sqrt_func);
    
    napi_create_function(env, "avxSumBatch", NAPI_AUTO_LENGTH, napi_avx_sum_batch, NULL, &sum_func);
    napi_set_named_property(env, exports, "avxSumBatch", sum_func);
    
    return exports;
}
