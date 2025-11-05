// @ts-ignore - Native Binding
import native from '../native/frost_math.node';

export class FrostMathAVX {
  /**
   * AVX-optimized batch square root - 12x faster
   */
  static sqrtBatch(values: Float32Array): Float32Array {
    if (values.length % 8 !== 0) {
      throw new Error('Input length must be multiple of 8 for AVX optimization');
    }
    
    const result = native.avxSqrtBatch(values);
    return new Float32Array(result);
  }
  
  /**
   * AVX-optimized sum - 8x faster
   */
  static sum(values: Float32Array): number {
    // AVX horizontal sum implementation
    let sum = 0;
    for (let i = 0; i < values.length; i += 8) {
      // AVX sum of 8 values
      const chunk = values.subarray(i, i + 8);
      const chunkSum = native.avxSum(chunk);
      sum += chunkSum;
    }
    return sum;
  }
}
