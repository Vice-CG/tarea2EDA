all: tarea2.exe
tarea2.exe: main.c modules/validator.c modules/processor.c modules/sorter.c modules/validator.h modules/processor.h modules/sorter.h
	gcc -o tarea2.exe main.c modules/validator.c modules/processor.c modules/sorter.c

clean:
	del /f tarea2.exe