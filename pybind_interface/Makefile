# The name of the shared library that results after compiling qsim for Pybind11
QSIMLIB = ../qsimcirq/qsim`python3-config --extension-suffix`

# The flags for the compilation of the Pybind11 interface
PYBINDFLAGS_BASIC = -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes`
PYBINDFLAGS_SSE = -msse4.1 -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes`
PYBINDFLAGS_AVX2 = -mavx2 -mfma -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes`
PYBINDFLAGS_AVX512 = -mavx512f -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes`

.PHONY: pybind
pybind:
	$(CXX) basic/pybind_main_basic.cpp -o $(QSIMLIB) $(CXXFLAGS) $(PYBINDFLAGS_BASIC)
	$(CXX) sse/pybind_main_sse.cpp -o $(QSIMLIB) $(CXXFLAGS) $(PYBINDFLAGS_SSE)
	$(CXX) avx2/pybind_main_avx2.cpp -o $(QSIMLIB) $(CXXFLAGS) $(PYBINDFLAGS_AVX2)
	$(CXX) avx512/pybind_main_avx512.cpp -o $(QSIMLIB) $(CXXFLAGS) $(PYBINDFLAGS_AVX512)

.PHONY: clean
clean:
	-rm -f ./*.x ./*.a ./*.so ./*.mod $(QSIMLIB)