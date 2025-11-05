{
  "targets": [{
    "target_name": "frost_native",
    "sources": ["src/native/math_avx.c"],
    "cflags": ["-mavx2", "-O3", "-mfma"],
    "conditions": [
      ["OS=='win'", {"libraries": ["-avx2"]}]
    ]
  }]
}
