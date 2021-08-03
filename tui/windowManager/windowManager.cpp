#include "windowManager.h"


WindowManager::WindowManager()
{
    return;
    isUpdateNeeded = true;
    refresh();
}


WindowManager::WindowManager(int posY, int posX, int sizeY, int sizeX)
{
    parentP         = NULL;
    baseWinP        = newwin(sizeY, sizeX, posY, posX);
    refresh();
}


WindowManager::WindowManager(WINDOW* baseP)
{
    baseWinP        = baseP;
    refresh();
}


WindowManager::~WindowManager()
{
    clearChildren();

    if(baseWinP != stdscr)
    {
        wclear(baseWinP);
        wrefresh(baseWinP);
        
        delwin(baseWinP);
    }
    else
    {
        //end ncurses when stdscr is destructed
        endwin();
    }
    
    refresh();

    
}


void WindowManager::addStyle()
{

}


void WindowManager::updateWindows()
{
	if(updateWindows(false))
    {
        fprintf(stderr, "\nrefresh");
        refresh();
    }	
}


bool WindowManager::updateWindows(bool isRefreshNeeded)
{

	if(isUpdateNeeded)
	{
        isUpdateNeeded  = false;
        isRefreshNeeded = true;
		wrefresh(baseWinP);

        //If this window is refreshed, do all child windows need be refreshed, in order to maintain properz-index of windows?
	}

	for(unsigned int i = 0; i < childList.size(); i++)
	{
		isRefreshNeeded |= childList[i]->updateWindows(false);
	}

	return isRefreshNeeded;
}


void WindowManager::insertChild(unsigned int index, WindowManager* childP)
{
    childP->parentP = this;

    std::vector<WindowManager*>::iterator it;
    it = childList.begin() + index;

    childList.insert(it, childP);
}


void WindowManager::clear()
{
    clearChildren();
    wclear(baseWinP);

    isUpdateNeeded = true;
}


void WindowManager::clearChildren()
{
    unsigned int i = 0;

    for(i = 0; i < childList.size(); i++)
    {
        delete childList[i];
    }

    childList.clear();

    isUpdateNeeded = true;
}


void WindowManager::appendChildren(WindowManager** childListP, int num)
{
    for(int i = 0; i < num; i++)
    {
        appendChild(childListP[i]);
    }
}


void WindowManager::appendChild(WindowManager* childP)
{
    childP->parentP = this;
    childList.push_back(childP);
}


/**
 * @depracated use numberOfChildren instead
 * 
 * @return unsigned int 
 */
unsigned int WindowManager::getNumOfChildren()
{
    return childList.size();
}


unsigned int WindowManager::numberOfChildren()
{
    return childList.size();
}


int WindowManager::height()
{
    return getmaxy(baseWinP);
}


int WindowManager::width()
{
    return getmaxx(baseWinP);
}


WindowManager* WindowManager::getChildAtIndex(unsigned int index)
{
    if(index < childList.size())
    {
        return childList[index];
    }
    else
    {
        return NULL;
    }
    
}


void WindowManager::setParent(WindowManager* inParentP)
{
    parentP = inParentP;
}


WINDOW* WindowManager::getBase()
{
    return baseWinP;
}


void WindowManager::setBase(WINDOW* baseP)
{
    baseWinP = baseP;
}


int WindowManager::y()
{
    return getbegy(baseWinP);
}


int WindowManager::x()
{
    return getbegx(baseWinP);
}


void WindowManager::printCenter(std::string msg)
{

    wmove(baseWinP, height()/2, (width() - msg.length())/2);

    wprintw(baseWinP, msg.c_str());

    isUpdateNeeded = true;
}


void WindowManager::print(std::string msg)
{
    wprintw(baseWinP, msg.c_str());

    isUpdateNeeded = true;
}


int WindowManager::cursorX()
{
    return getcurx(baseWinP);
}


int WindowManager::cursorY()
{
    return getcury(baseWinP);
}


void WindowManager::addChar(const chtype ch)
{
    waddch(baseWinP, ch);
    wrefresh(baseWinP);
    refresh();
    isUpdateNeeded = true;
}


void WindowManager::removeChar()
{
    moveCursor(-1);
    addChar(' ');
    moveCursor(-1);
    isUpdateNeeded = true;
}

void WindowManager::removeChar(int y, int x)
{
    moveCursor(y, x);
    addChar(' '); 
    isUpdateNeeded = true;
}


void WindowManager::moveCursor(int abs)
{
    wmove(baseWinP, cursorY(), cursorX() + abs);
}

void WindowManager::moveCursor(int y, int x)
{
    wmove(baseWinP, y, x);
}


/**
 * @brief create a simple border around the window
 * 
 */
void WindowManager::simpleBox(const char horizontalChars, 
                              const char verticalChars, 
                              const char cornerChars)
{
    unsigned int i = 0;
    unsigned int j = 0;


    wmove(baseWinP, 0, 0);

    for(j = 0; j < width(); j++)
    {
        waddch(baseWinP, horizontalChars);
    }

    wmove(baseWinP, (height() - 1), 0);

    for(j = 0; j < width(); j++)
    {
        waddch(baseWinP, horizontalChars);
    }

    wmove(baseWinP, 0, 0);

    for(j = 0; j < height(); j++)
    {
        waddch(baseWinP, verticalChars);
        wmove(baseWinP, j, 0);
    }

    wmove(baseWinP, 0, (width() - 1));

    for(j = 0; j < height(); j++)
    {
        waddch(baseWinP, verticalChars);
        wmove(baseWinP, j, (width() - 1));
    }

    // Corners
    
    wmove(baseWinP, 0, 0);
    waddch(baseWinP, cornerChars);

    wmove(baseWinP, 0, (width() - 1));
    waddch(baseWinP, cornerChars);

    wmove(baseWinP, (height() - 1), 0);
    waddch(baseWinP, cornerChars);

    wmove(baseWinP, (height() - 1), (width() - 1));
    waddch(baseWinP, cornerChars);
}