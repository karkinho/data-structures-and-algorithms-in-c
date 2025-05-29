source := src/
files := $(source)*.cpp $(source)*.hpp
compiler := g++
exe := app
flags := -Wall -g

$(exe):
	$(compiler) $(files) $(flags) -o $(exe) 

clean:
	rm -f $(obj) $(exe)