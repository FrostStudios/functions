// Direct V8 Integration
Napi::Value SQRTBatch(const Napi::CallbackInfo& info) {
    #include <immintrin.h>
#include <stdio.h>

int main() {
    // Acht Werte (float) im Vektor – Beispiel: [1.0, 4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0]
    float data[8] = {1.0f, 4.0f, 9.0f, 16.0f, 25.0f, 36.0f, 49.0f, 64.0f};
    float result[8];

    // Lade die Daten in einen AVX-Vektor
    __m256 input = _mm256_loadu_ps(data);

    // Wende die AVX-Square-Root-Instruktion an (parallel für alle 8 Werte)
    __m256 output = _mm256_sqrt_ps(input);

    // Schreibe das Ergebnis zurück in das Array
    _mm256_storeu_ps(result, output);

    // Ausgabe der Ergebnisse
    printf("Quadratwurzeln:\n");
    for (int i = 0; i < 8; i++) {
        printf("sqrt(%.1f) = %.3f\n", data[i], result[i]);
    }

    return 0;
}

    return Napi::Float32Array::New(env, result);
}


# Komplettes Setup
gcc -mavx2 -O3 -fopenmp -shared -o libavxmath.so c-core/math_avx.c
emcc wasm-bindings/math.wasm.c -msimd128 -O3 -o math.wasm
node-gyp configure build  # Für Native Addons
