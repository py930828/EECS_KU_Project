@echo off
set xv_path=D:\\Vivado\\Vivado\\2016.1\\bin
call %xv_path%/xsim DataMem_tb_behav -key {Behavioral:sim_1:Functional:DataMem_tb} -tclbatch DataMem_tb.tcl -view C:/Users/long/Desktop/HW05_MIPS_MEM_ChenLong/DataMem/simulation_sources/DataMem_wave.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
