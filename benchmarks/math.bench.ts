import { FrostMathAVX } from '../utils/math.avx';
import { performance } from 'perf_hooks';

// Test data
const testData = new Float32Array(1024 * 1024); // 1M elements
for (let i = 0; i < testData.length; i++) testData[i] = i + 1;

// Benchmark
console.log('🚀 PERFORMANCE BENCHMARK - AVX vs Native');

const startAVX = performance.now();
const resultAVX = FrostMathAVX.sqrtBatch(testData);
const timeAVX = performance.now() - startAVX;

const startNative = performance.now();
const resultNative = testData.map(x => Math.sqrt(x));
const timeNative = performance.now() - startNative;

console.log(`AVX: ${timeAVX.toFixed(2)}ms`);
console.log(`Native: ${timeNative.toFixed(2)}ms`);
console.log(`Speedup: ${(timeNative / timeAVX).toFixed(2)}x faster`);
