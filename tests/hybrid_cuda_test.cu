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

#include "hybrid_testfixture.h"

#include "gtest/gtest.h"

#include "../lib/simulator_cuda.h"

namespace qsim {

template <typename FP>
struct Factory {
  using fp_type = FP;
  using Simulator = qsim::SimulatorCUDA<fp_type>;
  using StateSpace = typename Simulator::StateSpace;

  Factory(const typename StateSpace::Parameter& param1,
          const typename Simulator::Parameter& param2)
      : param1(param1), param2(param2) {}

  StateSpace CreateStateSpace() const {
    return StateSpace(param1);
  }

  Simulator CreateSimulator() const {
    return Simulator(param2);
  }

  typename StateSpace::Parameter param1;
  typename Simulator::Parameter param2;
};

TEST(HybridCUDATest, Hybrid2) {
  using Factory = qsim::Factory<float>;
  Factory::StateSpace::Parameter param1;
  Factory::Simulator::Parameter param2;
  Factory factory(param1, param2);
  TestHybrid2(factory);
}

TEST(HybridCUDATest, Hybrid4) {
  using Factory = qsim::Factory<float>;
  Factory::StateSpace::Parameter param1;
  Factory::Simulator::Parameter param2;
  Factory factory(param1, param2);
  TestHybrid4(factory);
}

}  // namespace qsim

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
