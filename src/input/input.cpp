#include "input.h"

namespace input
{
    Keyboard::Keyboard(){
        clearKeys();
    }

    void Keyboard::clearKeys(){
        for (bool& key: m_Keys)
            key = false;
    }

}