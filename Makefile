CC     = g++
CFLAGS = -Wall -Wextra

#Исходные файлы
Main_cpp              = main.cpp

#Объектные файлы
Main_o                = main.o

#Путь к модулям
Log_Folder            = LOG
OptsCmdLine_Folder    = OptionsCmdLine
SquareEquation_Folder = Math

all: SquareEquation

SquareEquation: $(Main_o) $(Log_Folder)/lib/liblog.a $(OptsCmdLine_Folder)/lib/*.a $(SquareEquation_Folder)/lib/*.a
	$(CC) $(CFLAGS) $(Main_o) $(Log_Folder)/lib/*.a $(OptsCmdLine_Folder)/lib/*.a $(SquareEquation_Folder)/lib/*.a -o main.exe

#Создание объектных файлов
$(Main_o): $(Main_cpp)
	$(CC) $(CFLAGS) -c $@

build/*.o: src/*.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(Log_Folder)/build/%.o: $(Log_Folder)/src/%.cpp  

$(OptsCmdLine_Folder)/build/*.o: $(OptsCmdLine_Folder)/src/*.cpp
	$(CC) $(CFLAGS) -c $^ -C $(OptsCmdLine_Folder)/build

$(SquareEquation_Folder)/build/*.o: $(SquareEquation_Folder)/src/*.cpp
	$(CC) $(CFLAGS) -c $^ -C $(SquareEquation_Folder)/build

#Создание архивов
$(Log_Folder)/lib/libLog.a: $(Log_Folder)/build/*.o
	ar r $@ $^

$(OptsCmdLine_Folder)/lib/libOptionsCmdLine.a: $(OptionsCmdLine_Folder)/build/*.o
	ar r $@ $^

$(SquareEquation_Folder)/lib/libSquareEquation.a: $(SquareEquationLib__build)/build/*.o
	ar r $@ $^


