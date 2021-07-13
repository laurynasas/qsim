#include <pybind11/pybind11.h>

namespace py = pybind11;

#ifdef _WIN32
//  Windows
#include <intrin.h>
#define cpuid(info, x)    __cpuidex(info, x, 0)

#else
//  GCC Intrinsics
#include <cpuid.h>
void cpuid(unsigned info[4], int infoType){
    __cpuid_count(infoType, 0, info[0], info[1], info[2], info[3]);
}

#endif

enum Instructions { AVX512F = 0, AVX2 = 1, SSE4_1 = 2, BASIC = 3};

int detect_instructions() {
  Instructions instr = BASIC;
  unsigned info[4];

  cpuid(info, 0);

  int nIds = info[0];
  if (nIds >= 1) {
    cpuid(info, 1);
    if ((info[2] & ((unsigned)1 << 19)) != 0) {
      instr = SSE4_1;
    }
  }
  if (nIds >= 7) {
    cpuid(info, 7);
    if ((info[1] & ((unsigned)1 <<  5) )!= 0) {
      instr = AVX2;
    }
    if ((info[1] & ((unsigned)1 << 16)) != 0) {
      instr = AVX512F;
    }

  }

  return static_cast<int>(instr);
}

PYBIND11_MODULE(qsim_decide, m) {
  m.doc() = "pybind11 plugin";  // optional module docstring

  // Methods for returning amplitudes
  m.def("detect_instructions", &detect_instructions, "Detect SIMD");
}