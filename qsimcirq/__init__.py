
from qsimcirq import qsim_decide
import importlib
import sys


def _load_simd_qsim():
    instr = qsim_decide.detect_instructions()
    if instr == 0:
        print("----> circ 0")
        qsim = importlib.import_module("qsimcirq.qsim_avx512")
    elif instr == 1:
        print("----> circ 1")
        qsim = importlib.import_module("qsimcirq.qsim_avx2")
    elif instr == 2:
        print("----> circ 2")
        qsim = importlib.import_module("qsimcirq.qsim_sse")
    else:
        print("----> circ 3")
        qsim = importlib.import_module("qsimcirq.qsim_basic")
    sys.modules["qsim"] = qsim


_load_simd_qsim()
from .qsim_circuit import add_op_to_opstring, add_op_to_circuit, QSimCircuit
from .qsim_simulator import QSimSimulatorState, QSimSimulatorTrialResult, QSimSimulator
from .qsimh_simulator import QSimhSimulator

from qsimcirq._version import (
    __version__,
)
