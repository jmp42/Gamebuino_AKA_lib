@echo off

@echo "Convert file to C++ array header file"
@if A%1 == A goto error

Bin2Hex.exe "%1" >> %1.h
goto fin

:error
@echo you must specifi file to convert
:fin