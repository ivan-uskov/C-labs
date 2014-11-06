REM Start test 1
rle.exe pack ./unpacked/1.txt ./output.txt
FC /B output.txt .\packed\1.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 2
rle.exe unpack ./packed/1.txt ./output.txt
FC /B output.txt .\unpacked\1.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 3
rle.exe pack ./unpacked/2.txt ./output.txt
FC /B output.txt .\packed\2.txt
IF ERRORLEVEL 1 GOTO err

REM Start test 4
rle.exe unpack ./packed/2.txt ./output.txt
FC /B output.txt .\unpacked\2.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
del output.txt
EXIT

:err
ECHO Program testing failed :-(
EXIT
