#ModelSim
#export PSPIN_SIM="modelsim_model"

#Verilator
export PSPIN_SIM="verilator_model"

#Update these!
export RISCV_GCC=/home/chenyz/tools/riscv-gcc32-pulp-multilib/bin/
export PSPIN_HW=/home/chenyz/pspin/hw/
export PSPIN_RT=/home/chenyz/pspin/sw/
export VERILATOR_ROOT=/home/chenyz/tools/verilator-v4.202
export VERILATOR_HOME=/home/chenyz/tools/verilator-v4.202

export PATH="/home/chenyz/tools/llvm-9.x-pulp/bin:/usr/bin/cmake/bin:${PATH}"
export LD_LIBRARY_PATH="/home/chenyz/tools/llvm-9.x-pulp/lib:${LD_LIBRARY_PATH}"

#Don't change
export TARGET_VSIM=${PSPIN_HW}/$PSPIN_SIM
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/${PSPIN_HW}/verilator_model/lib/
export TRACE_DIR="./"

