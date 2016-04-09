OBJ = main.o plugboard.o reflector.o rotor.o machine.o enigma.o
EXE = enigma
CXX = g++
CPPFLAGS = -Wall -g

$(EXE): $(OBJ)
        $(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
        $(CXX) $(CPPFLAGS) -c $<

main.o: enigma.h errors.h
plugboard.o: plugboard.h enigma.h errors.h
reflector.o: reflector.h enigma.h errors.h
rotor.o: rotor.h enigma.h errors.h
machine.o: machine.h enigma.h errors.h
enigma.o: enigma.h errors.h

clean:
        rm -f *.o

