@echo off
set xv_path=H:\\Working\\Vivado\\Vivado\\2016.1\\bin
call %xv_path%/xsim cu_tb_behav -key {Behavioral:sim_1:Functional:cu_tb} -tclbatch cu_tb.tcl -view C:/Users/long/Desktop/HW09_MIPS_CU/simulation_sources/cu_wave.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
