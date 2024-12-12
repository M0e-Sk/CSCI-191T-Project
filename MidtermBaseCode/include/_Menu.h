#ifndef _MENU_H
#define _MENU_H
#include <_Common.h>
#include<_Camera.h>
#include<_TextureLoader.h>

class _Menu
{
    public:
        _Menu();
        virtual ~_Menu();

        _TextureLoader* mainMenu = new _TextureLoader();

        void initMenu(char*);
        void drawMenu(float width, float height, _Camera*);

        bool menuActive=false;

    protected:

    private:
};

#endif // _MENU_H
