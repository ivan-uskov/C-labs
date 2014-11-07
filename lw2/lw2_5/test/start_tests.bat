REM Start test 1
crypt.exe crypt ./uncrypted/1.txt ./output.txt 255
FC /B output.txt .\crypted\1.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 2
crypt.exe crypt ./uncrypted/1.txt ./output1.txt 127
crypt.exe crypt ./uncrypted/1.txt ./output2.txt 255
FC /B output1.txt output2.txt
IF NOT ERRORLEVEL 1 GOTO err

REM Start test 3
crypt.exe decrypt ./output1.txt ./output3.txt 127
crypt.exe decrypt  ./output2.txt ./output4.txt 255
FC /B output3.txt output4.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
del output.txt
del output1.txt
del output2.txt
del output3.txt
del output4.txt
EXIT

:err
ECHO Program testing failed :-(
EXIT
