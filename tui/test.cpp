#include <iostream>

#include "windowManager/windowManager.h"
#include "popup/popup.h"

int main()
{
    initscr();

    //WindowManager base = WindowManager(stdscr);

    std::string popupTest = std::string("Hello world");
    std::string popupTextTest = std::string("Giif text input pls");

    popup(&popupTest);

    noecho();

    std::string* input = popupTextInput(&popupTextTest);

    popup(input);

    /*WindowManager* childP = new WindowManager(2, 2, 0 ,20);

    base.appendChild(childP);

    childP->addChar('a');

    childP->updateWindows();

    getch();
*/

    refresh();

    getch();

    endwin();
    
    return 0;
}