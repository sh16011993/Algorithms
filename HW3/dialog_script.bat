@echo off
:GO
echo Enter input file name (example: sh.txt) [Enter "bye" (without quotes) to exit]
set /p inputfile=
if "%inputfile%" == "bye" exit
echo Enter output file name (example: sh_output.txt) [Enter "bye" (without quotes) to exit]
set /p outputfile=
if "%outputfile%" == "bye" exit
python dialog.py %inputfile% %outputfile%
goto GO