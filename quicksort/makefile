files := src/*.c
flags := -Wall -g -o
projectname := app

run: $(projectname)
	./$(projectname) $(size)

$(projectname):
	gcc $(files) $(flags) $(projectname)
clean:

	rm -f ./$(projectname)