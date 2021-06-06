#!/bin/bash
set -e  # fail and exit on any command erroring
set -x  # print evaluated commands

## Install the given bazel version on macos
function update_bazel_macos {
  BAZEL_VERSION=$1
  curl -L https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/bazel-${BAZEL_VERSION}-installer-darwin-x86_64.sh -O
  ls
  chmod +x bazel-*.sh
  ./bazel-${BAZEL_VERSION}-installer-darwin-x86_64.sh --user
  rm -f ./bazel-${BAZEL_VERSION}-installer-darwin-x86_64.sh
  # Add new bazel installation to path
  PATH="/Users/kbuilder/bin:$PATH"
}

# Install bazel
#update_bazel_macos ${BAZEL_VERSION:-0.26.0}
which bazel
bazel version

#cd ${KOKORO_ARTIFACTS_DIR}/github/qsim

# Create virtual env
python3 -m virtualenv env
source env/bin/activate

# Attempt to build all components in SSE and basic mode.
# The Kokoro MacOS VMs are not configured for AVX2 or OpenMP, so these modes
# are excluded from the build and test process.
bazel build --config=sse apps:all
bazel build apps:all

# Run all basic tests.
set +e  # Ignore errors until artifacts are collected.
EXIT_CODE=0
for TARGET in bitstring_test circuit_qsim_parser_test fuser_basic_test \
              gates_qsim_test hybrid_test matrix_test run_qsim_test \
              run_qsimh_test simulator_basic_test statespace_basic_test; do \
  if ! bazel test --test_output=errors tests:${TARGET}; then
    EXIT_CODE=1
  fi
done