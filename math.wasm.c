// EMSCRIPTEN für Browser-Performance
EMSCRIPTEN_KEEPALIVE
void wasm_sqrt_batch(float* data, int length) {
    // AVX via WebAssembly SIMD
    v128_t vec = wasm_v128_load(data);
    v128_t sqrt = wasm_f32x4_sqrt(vec);
    wasm_v128_store(data, sqrt);
}
