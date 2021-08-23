#ifndef WINDOW_MANAGER_INCLUSION_PROTECTION
#define WINDOW_MANAGER_INCLUSION_PROTECTION

#include <ncurses.h>
#include <vector>
#include <string>

class WindowManager
{
    private:
        WINDOW*                     	baseWinP;
        WindowManager*              	parentP;
	    bool				            isUpdateNeeded;
        std::vector<WindowManager*> 	childList;
        std::vector<std::string*>       styleList;

	    bool updateWindows(bool isRefreshNeeded);
        

    public:
        WindowManager();
        WindowManager(WINDOW* baseP);
        WindowManager(int posY, int posX, int sizeY, int sizeX);

        ~WindowManager();

        int height();
        int width();
        int x();
        int y();

        int cursorX();
        int cursorY();

        void addChar(const chtype ch);
        void removeChar();
        void removeChar(int y, int x);

        void moveCursor(int abs);
        void moveCursor(int y, int x);


        WINDOW* getBase();

        void setBase(WINDOW* baseP);

        void updateWindows();

        void appendChild(WindowManager* child);

        void appendChildren(WindowManager** childListP, int num);

        void insertChild(unsigned int index, WindowManager* child);

        WindowManager* getChildAtIndex(unsigned int index);

        unsigned int getNumOfChildren();

        unsigned int numberOfChildren();

        void clearChildren();

        void clear();

        void setParent(WindowManager* inParentP);

        void addStyle();


        void printCenter(std::string msg);
        void print(std::string msg);

        void simpleBox(const char horizontalChars, 
                       const char verticalChars, 
                       const char cornerChars);

        void attributeOn(attr_t attribute);
        void attributeOff(attr_t attribute);

};


#endif
