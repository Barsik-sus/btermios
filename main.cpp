#include <unistd.h>
#include <iostream>
#include "btermios.h"

namespace term = Termios;

int main() {
    std::string  i;
    // Изменяю управляющие символы
    term::input.settings->changeCharacter(VEOF,  120); // X
    term::input.settings->changeCharacter(VERASE, 99); // C
    term::input.settings->changeCharacter(VINTR, 118); // V
    term::output << "Set settings (1)" << std::endl;
    if (!term::input.settings->setSettings()) {
        std::cerr <<  "Could not set attributes" << std::endl;
        return -1;
    }
    term::output << "EOF - X" << std::endl
                 << "DEL - C" << std::endl
                 << "INT - V" << std::endl
                 << "Enter something:" << std::endl;
    term::input >> i;
    term::output << i << std::endl;
    term::output << "Reset settings" << std::endl;
    term::input.settings->resetSettings();
    i = "";

    // MIN и TIME в 0
    // не понял зачем такое делать, но в задании сказано...
    // то есть оно просто моментально сразу при вызове возвращает даже если ничего нет
    term::input.settings->c_lflag &= ~ICANON;
    term::input.settings->c_cc[VMIN] = 0;
    term::input.settings->c_cc[VTIME] = 0;
    term::output << "Set settings (2)" << std::endl;
    term::input.settings->setSettings();
    term::input >> i;
    term::output << std::endl << i << std::endl;
    return 0;
}
