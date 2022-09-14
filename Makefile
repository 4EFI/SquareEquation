CC     = g++
CFLAGS = -Wall -Wextra 

#Исходные файлы
Log_cpp               = LOG\src\Log.cpp
OptionsCmdLine_cpp    = OptionsCmdLine\src\OptionsCmdLine.cpp
SquareEquationLib_cpp = Math\src\SquareEquationLib.cpp 

#Объектные файлы
Log_o                 = LOG\lib\LOG.o
OptionsCmdLine_o      = OptionsCmdLine\lib\OptionsCmdLine.o
SquareEquationLib_o   = Math\lib\SquareEquationLib.o

all: SquareEquation

SquareEquation: main.o $(Log_o) $(OptionsCmdLine_o) $(SquareEquationLib_o)      
	$(CC) $(CFLAGS) main.o $(Log_o) $(OptionsCmdLine_o) $(SquareEquationLib_o) -o main.exe 

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

$(Log_o): $(Log_cpp)
	$(CC) $(CFLAGS) -c $(Log_cpp) -o $(Log_o)

$(OptionsCmdLine_o): $(OptionsCmdLine_cpp)
	$(CC) $(CFLAGS) -c $(OptionsCmdLine_cpp) -o $(OptionsCmdLine_o)

$(SquareEquationLib_o): $(SquareEquationLib_cpp)
	$(CC) $(CFLAGS) -c $(SquareEquationLib_cpp) -o $(SquareEquationLib_o)

clean:
	rm -f Log_o
	rm -f OptionsCmdLine_o	
	rm -f SquareEquationLib_o
