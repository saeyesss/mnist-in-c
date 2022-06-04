C_SRC = $(wildcard matrix/*.c neural-network/*.c img/*.c *.c)
HEADER_FILES =$(wildcard matrix/*.h neural-network/*.h img/*.h *.h);
obj_files = ${C_SRC:.c=.o}
CFLAGS =

DevEnvDir=C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin

Path:=$(DevEnvDir);$(Path)

MAIN = main
CC = ${Path}\\gcc
LINKER = ${Path}\\ld

run2: ${MAIN}
	./%{MAIN}

main: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@ -lm

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ -lm

clean:
	rm matrix/*.o *.o neural-network/*.o img/*.o ${MAIN}
