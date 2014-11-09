REM Start test 1
solve.exe 1 1 1 > ./output.txt
FC /B output.txt ./answers/answer1.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 2
solve.exe 2 1 -3 > ./output.txt
FC /B output.txt ./answers/answer2.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 3
solve.exe 1 0 0 > ./output.txt
FC /B output.txt ./answers/answer3.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 4
solve.exe 1 0 > ./output.txt
FC /B output.txt ./answers/answer4.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 5
solve.exe -1 0 1 > ./output.txt
FC /B output.txt ./answers/answer5.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
del output.txt
EXIT

:err
ECHO Program testing failed :-(
EXIT
