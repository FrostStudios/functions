const { FrostAVX } = require('../src/utils/math.avx');

// 1M elements
const data = Array.from({length: 1024 * 1024}, (_, i) => i + 1);

console.log('🚀 FROST FUNCTIONS - AVX BENCHMARK');
console.log('==================================');

const startAVX = Date.now();
const resultAVX = FrostAVX.sqrtBatch(data);
const timeAVX = Date.now() - startAVX;

const startJS = Date.now();
const resultJS = data.map(x => Math.sqrt(x));
const timeJS = Date.now() - startJS;

console.log(`AVX Time: ${timeAVX}ms`);
console.log(`JS Time: ${timeJS}ms`);
console.log(`Speedup: ${(timeJS / timeAVX).toFixed(1)}x`);
console.log(`Throughput: ${(data.length / timeAVX * 1000).toLocaleString()} ops/sec`);
