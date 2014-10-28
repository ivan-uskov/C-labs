REM Start test 1
matrix_mult.exe ./tests/test1_1.txt ./tests/test1_2.txt > output.txt
FC /B output.txt ./answers/answer1.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 2
matrix_mult.exe ./tests/test2_1.txt ./tests/test2_2.txt > output.txt
FC /B output.txt ./answers/answer2.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 3
matrix_mult.exe ./tests/test3_1.txt ./tests/test3_2.txt > output.txt
FC /B output.txt ./answers/answer3.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
del output.txt
EXIT

:err
ECHO Program testing failed :-(
EXIT
