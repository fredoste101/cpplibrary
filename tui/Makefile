COMPILER=g++ -std=c++11

COMPILER_FLAGS=


all : popup/popup.cpp popup/popup.h windowManager/windowManager.cpp windowManager/windowManager.h
	$(COMPILER) -c popup/popup.cpp -o tui.o && ar rcs tui.a tui.o