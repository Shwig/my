FLAGS = -g -std=c99
objects = myshell.o utility.o

print_list : $(objects)
	cc -o myshell $(CFLAGS) $(objects)

.PHONY : clean
clean :
	rm myshell $(objects)
