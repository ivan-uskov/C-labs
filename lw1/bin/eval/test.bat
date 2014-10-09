REM Start Test 0
eval.exe > output.txt
FC /B output.txt ./test/0.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 1
eval.exe 15 + 2 * -8 > output.txt
FC /B output.txt ./test/1.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 2
eval.exe wfwefwef > output.txt
FC /B output.txt ./test/2.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 3
eval.exe 8 + 4 / 0 -2 > output.txt
FC /B output.txt ./test/3.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 4
eval.exe 4 + wewer - 3 > output.txt
FC /B output.txt ./test/4.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 5
eval.exe 5 wwefw 0 > output.txt
FC /B output.txt ./test/5.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 6
eval.exe 0 / wefwef > output.txt
FC /B output.txt ./test/6.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 7
eval.exe -12412 > output.txt
FC /B output.txt ./test/7.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 8
eval.exe 121 > output.txt
FC /B output.txt ./test/8.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 9
eval.exe / > output.txt
FC /B output.txt ./test/9.txt
IF ERRORLEVEL 1 GOTO err

REM Start Test 10
eval.exe 13 + 7 / 8 * 3.8 > output.txt
FC /B output.txt ./test/10.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
EXIT

:err
ECHO Program testing failed :-(
EXIT
