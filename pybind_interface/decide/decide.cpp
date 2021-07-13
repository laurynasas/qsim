#include <pybind11/pybind11.h>
#include <iostream>
#include <fstream>

namespace py = pybind11;
using namespace std;

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

  ofstream myfile;
  myfile.open("examplee.txt", std::ios_base::app);

  myfile << "## decide cpp entry: \n";

  for (int i = 4 - 1; i >= 0; i--)
    myfile <<i<<"-th element =" << info[i] <<"\n";

  cpuid(info, 0);
  myfile << "## 1: \n";
  for (int i = 4 - 1; i >= 0; i--)
  myfile <<i<<"-th element =" << info[i] <<"\n";

  int nIds = info[0];
  if (nIds >= 1) {
    cpuid(info, 1);
    if (info[2] & ((unsigned)1 << 19) != 0) {
      myfile << "supportrs sse41: \n";
      instr = SSE4_1;
    }
  }
  myfile << "## 2: \n";
  for (int i = 4 - 1; i >= 0; i--)
  myfile <<i<<"-th element =" << info[i] <<"\n";
  if (nIds >= 7) {
    cpuid(info, 7);
    if (info[1] & ((unsigned)1 <<  5) != 0) {
      myfile << "supportrs avx2: \n";
      instr = AVX2;
    }
    myfile << "## --------------: \n";
    unsigned hh = (unsigned)1 << 16;
    unsigned res = info[1] & ((unsigned)1 << 16);
    bool bres = (res != 0);
    myfile << info[1] <<"&" << hh << "=" << res << std::boolalpha << bres <<"\n";
    myfile << typeid(res).name() << " | " << typeid(0).name() << "\n";
    if (info[1] & ((unsigned)1 << 16) != 0) {
      myfile << "supportrs avx512: \n";
      instr = AVX512F;
    }
    myfile << "## --------------: \n";

  }
  myfile << "## 3: \n";
  for (int i = 4 - 1; i >= 0; i--)
  myfile <<i<<"-th element =" << info[i] <<"\n";
  myfile.close();

  return static_cast<int>(instr);
}

PYBIND11_MODULE(qsim_decide, m) {
  m.doc() = "pybind11 plugin";  // optional module docstring

  // Methods for returning amplitudes
  m.def("detect_instructions", &detect_instructions, "Detect SIMD");
}