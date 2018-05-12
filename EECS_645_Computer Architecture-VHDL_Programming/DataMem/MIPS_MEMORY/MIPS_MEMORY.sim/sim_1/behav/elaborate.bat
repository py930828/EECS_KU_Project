@echo off
set xv_path=D:\\Vivado\\Vivado\\2016.1\\bin
call %xv_path%/xelab  -wto 605b9da869754dadbe70213c60d2f18a -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot DataMem_tb_behav xil_defaultlib.DataMem_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
