REM Start test 1
find.exe hobbit.txt  "bilbo" > output.txt
FC /B output.txt ./answers/1.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 2
find.exe hobbit.txt  "The hobbit" > output.txt
FC /B output.txt ./answers/2.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 3
find.exe hobbit.txt  "The dragon" > output.txt
FC /B output.txt ./answers/3.txt
IF ERRORLEVEL 1 GOTO er


ECHO Program testing succeeded :-)
del output.txt
EXIT

:err
ECHO Program testing failed :-(
EXIT
