CC=clang
CFLAGS=-I./src

dir_guard=@mkdir -p $(@D)

thirlage: build_directory #thirlage.o page.o
	echo "OK"
# $(CC) -o thirlage.out thirlage.o page.o 

build_directory:
	mkdir -p build

# if makeheaders is there, run that
