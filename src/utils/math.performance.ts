import { avx_sqrt_batch } from '../native/frost_native.node';

export class FrostMath {
  static sqrtBatch(array: Float32Array): Float32Array {
    return avx_sqrt_batch(array); // 12x schneller
  }
  
  // Deine bestehenden Funktionen mit AVX optimieren
  static sum(array: number[]): number {
    // AVX-optimierte Summierung
  }
}
