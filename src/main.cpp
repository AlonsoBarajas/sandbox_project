#include "graphics/window.h"
#include <iostream>

int main (void){

    Window win("Hello World", 640, 480);

    while (!win.closed()){
        win.update();
    }

    return 0;
}