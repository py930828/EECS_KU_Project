@echo off
set xv_path=D:\\Vivado\\Vivado\\2016.1\\bin
call %xv_path%/xelab  -wto 7b3f5d1256fe446c97959247fbf0e1bd -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot InstrMem_tb_behav xil_defaultlib.InstrMem_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
