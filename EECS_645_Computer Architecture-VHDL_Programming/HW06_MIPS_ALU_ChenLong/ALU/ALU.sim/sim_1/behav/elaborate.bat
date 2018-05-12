@echo off
set xv_path=C:\\Xilinx\\SDx\\2017.1\\Vivado\\bin
call %xv_path%/xelab  -wto d21c5966e6ae4b15acea34973dae34bd -m64 --debug all --relax --mt 2 -L xil_defaultlib -L secureip --snapshot alu_tb_behav xil_defaultlib.alu_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
