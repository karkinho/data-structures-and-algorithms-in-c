source := src/
files := $(source)*.c $(source)*.h
flags := -Wall -g -o 
memcheck := valgrind -s
projectname := app

runmem: $(projectname)
	$(memcheck) ./$(projectname) $(args)

run: $(projectname)
	./$(projectname) $(args)

$(projectname):
	gcc $(files) $(def) $(flags) $(projectname)
clean:

	rm -f ./$(projectname)