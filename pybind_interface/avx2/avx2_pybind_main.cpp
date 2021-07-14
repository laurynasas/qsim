// Copyright 2019 Google LLC. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "avx2_pybind_main.h"

#include <complex>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

#include "../../lib/bitstring.h"
#include "../../lib/expect.h"
#include "../../lib/formux.h"
#include "../../lib/fuser_mqubit.h"
#include "../../lib/gates_qsim.h"
#include "../../lib/io.h"
#include "../../lib/qtrajectory.h"
#include "../../lib/run_qsim.h"
#include "../../lib/run_qsimh.h"
#include "../../lib/util.h"

#include "../../lib/simulator_avx.h"
#include "../pybind_main.cpp"
namespace qsim {
  template <typename For>
  using Simulator = SimulatorAVX<For>;
}
