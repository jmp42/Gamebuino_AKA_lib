@echo "all in one convert mod to header"
@if A%1 == A goto error

pmf_converter.exe -i %1 -o %1.h -c -ch 4 -hex
@rem pmf_converter.exe -i %1 -o %1_instr.h -c -ch 4 -hex -dro
goto fin

:error
@echo you must specifi file to convert
:fin