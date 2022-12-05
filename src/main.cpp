
#include "graphics/window.h"
#include <iostream>

int main (void){


    graphx::Window win("Hello james", 640, 480);

    while (!win.closed()){
        win.update();
    }



    return 0;
}