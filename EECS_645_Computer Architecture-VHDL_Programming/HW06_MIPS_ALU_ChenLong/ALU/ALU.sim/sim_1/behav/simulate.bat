@echo off
set xv_path=C:\\Xilinx\\SDx\\2017.1\\Vivado\\bin
call %xv_path%/xsim alu_tb_behav -key {Behavioral:sim_1:Functional:alu_tb} -tclbatch alu_tb.tcl -view H:/EECS_645/HW06_MIPS_ALU_ChenLong/simulation_sources/alu_wave.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
