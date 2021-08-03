#pragma once


#include <string>

#include <ncurses.h>

#include "../windowManager/windowManager.h"

void popup(std::string* msgP);

std::string* popupTextInput(std::string* msgP);