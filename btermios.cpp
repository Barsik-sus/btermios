#ifndef BTERMIOSCPP
#define BTERMIOSCPP

#include "btermios.h"
namespace Termios
{
    bool Settings::setSettings()
    {
        if (tcsetattr(fileno(file), TCSANOW, this) == 0)
            return true;
        return false;
    }

    bool Settings::resetSettings()
    {
        if (tcsetattr(fileno(file), TCSANOW, &init) == 0)
        {
            tcgetattr(fileno(file), this);
            return true;
        }
        return false;
    }

    void Settings::changeCharacter(int control_symbol, int new_control_symbol)
    {
        c_cc[control_symbol] = new_control_symbol;
    }

    Settings::Settings(FILE* file) : file(file)
    {
        tcgetattr(fileno(file), this);
        init = *this;
    }

    Settings::~Settings()
    {
        resetSettings();
    }

    TMP::TMP(const char* filename , const std::_Ios_Openmode openmode) : std::fstream(filename, openmode)
    {
        if (!(FILE*)this)
            throw "The file cannot be opened";
        settings = std::make_unique<Settings>(*this);
    }

    TMP input("/dev/tty", std::istream::in);
    TMP output("/dev/tty", std::istream::out);
}

#endif 
