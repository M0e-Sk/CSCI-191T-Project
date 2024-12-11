#ifndef _MENU_H
#define _MENU_H
#include <_Common.h>
#include<_TextureLoader.h>

class _Menu
{
    public:
        _Menu();
        virtual ~_Menu();

        _TextureLoader* mainMenu = new _TextureLoader();

        void initMenu(char*);
        void drawMenu();
        vec3 verts[4];

        bool menuActive=true;

    protected:

    private:
};

#endif // _MENU_H
