@echo off
set xv_path=H:\\Working\\Vivado\\Vivado\\2016.1\\bin
call %xv_path%/xelab  -wto e64b20df4ed547ecb3afb6b806c1297c -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot cu_tb_behav xil_defaultlib.cu_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
