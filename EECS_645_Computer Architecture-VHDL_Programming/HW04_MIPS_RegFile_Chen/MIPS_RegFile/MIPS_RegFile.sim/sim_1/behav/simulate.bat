@echo off
set xv_path=D:\\Vivado\\Vivado\\2016.1\\bin
call %xv_path%/xsim regfile_tb_behav -key {Behavioral:sim_1:Functional:regfile_tb} -tclbatch regfile_tb.tcl -view C:/Users/long/Desktop/HW04_MIPS_RegFile_Chen/simulation_sources/regfile_wave.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
