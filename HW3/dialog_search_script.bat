@echo off
:GO
echo Enter output file name to be searched (Example: sh_output.txt). To exit, enter "bye" (without quotes)
set /p outputfile=
if "%outputfile%" == "bye" exit
python dialog_search.py %outputfile%
goto GO