out : Agenda.cpp AgendaUI.o AgendaService.o Storage.o Meeting.o User.o Date.o
	g++ -std=c++11 -o out Agenda.cpp *.o
AgendaUI.o : AgendaUI.cpp AgendaUI.h AgendaService.h
	g++ -std=c++11 -c AgendaUI.cpp
AgendaService.o : AgendaService.cpp AgendaService.h Storage.h
	g++ -std=c++11 -c AgendaService.cpp
Storage.o : Storage.cpp Storage.h Meeting.h User.h
	g++ -std=c++11 -c Storage.cpp
Meeting.o : Meeting.cpp Meeting.h Date.h
	g++ -std=c++11 -c Meeting.cpp
User.o : User.cpp User.h
	g++ -std=c++11 -c User.cpp
Date.o : Date.cpp Date.h
	g++ -std=c++11 -c Date.cpp
clean :
	rm *.o out
