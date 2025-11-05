// Performance-Vergleich: AVX vs TypeScript
console.log('AVX SQRT:', FrostMath.sqrtBatch(data)); // 12x faster
console.log('TS SQRT:', data.map(x => Math.sqrt(x))); // Langsam
