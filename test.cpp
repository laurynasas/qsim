#include <iostream>

#ifdef _WIN32
//  Windows
#include <intrin.h>
#define cpuid(info, x)    __cpuidex(info, x, 0)

#else
//  GCC Intrinsics
#include <cpuid.h>
void cpuid(int info[4], int infoType){
    __cpuid_count(infoType, 0, info[0], info[1], info[2], info[3]);
}

#endif

enum Instructions { AVX512F, AVX2, SSE4_1, BASIC };

Instructions detectInstructions() {
  Instructions instr = BASIC;
  int info[4];

  cpuid(info, 0);
  int nIds = info[0];
  if (nIds >= 1) {
    cpuid(info, 1);
    if (info[2] & ((int)1 << 19) != 0) {
      instr = SSE4_1;
    }
  }
  if (nIds >= 7) {
    cpuid(info, 7);
    if (info[1] & ((int)1 <<  5) != 0) {
      instr = AVX2;
    }
    if (info[1] & ((int)1 << 16) != 0) {
      instr = AVX512F;
    }
  }
//  ofstream myfile;
//  myfile.open("example.txt", std::ios_base::app);
//  myfile << "## INSTRUCTIONS: " << instr << "\n";
//  myfile.close();

  return instr;
}


int main()
{
  std::cout << "## " << detectInstructions();
}