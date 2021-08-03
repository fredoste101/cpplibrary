#include <stdio.h>

#include "popup.h"

void popup(std::string* msgP)
{
    WindowManager* winManP = new WindowManager(getmaxy(stdscr) / 2 - 2, 
                                               getmaxx(stdscr) / 2 - 15, 
                                               5, 
                                               30);

    winManP->simpleBox('-', '|', '+');

    winManP->printCenter(*msgP);

    winManP->updateWindows();

    chtype ch = getch();

    delete winManP;

    return;

}


std::string* popupTextInput(std::string* msgP)
{
    std::string* inputP = new std::string();

    WindowManager* winManP = new WindowManager(getmaxy(stdscr) / 2 - 2, 
                                               getmaxx(stdscr) / 2 - 15, 
                                               5, 
                                               30);

    winManP->simpleBox('-', '|', '+');

    winManP->moveCursor(1, 1);

    winManP->print(*msgP);

    winManP->moveCursor(2, 1);

    winManP->updateWindows();

    chtype ch = getch();

    bool isEnter = false;

    while(ch != 27 || isEnter)
    {
        switch(ch)
        {
            case KEY_BACKSPACE:
            case 8:
            case 127:
            {
                if(inputP->length() > 0)
                {
                    winManP->removeChar();
                    inputP->pop_back();
                }
                fprintf(stderr, "\nbackspace");
            }
            break;

            case KEY_ENTER:
            case '\n':
            {
                fprintf(stderr, "\nENTER");
                delete winManP;
                return inputP;
            }
            break;

            default:
                fprintf(stderr, "\n%ld", ch);
                inputP->push_back(ch);
                winManP->addChar(ch);
            break;
        }

        ch = getch();
    }
    
    

    delete winManP;

    delete inputP;

    return NULL;
}