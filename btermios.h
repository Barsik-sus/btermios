#ifndef BTERMIOSH
#define BTERMIOSH

#include <fstream>
#include <memory>
#include <termios.h>
#include <ext/stdio_filebuf.h>

namespace Termios
{
    class Settings: public termios
    {
        termios init;
        FILE* file;
    public:
        bool setSettings();
        bool resetSettings();
        void changeCharacter(int control_symbol, int new_control_symbol);
    public:
        operator const struct termios*() {
            return static_cast<const struct termios*>(this);
        }
    public:
        Settings(FILE* file);
        ~Settings();
    };

    class TMP:public std::fstream
    {
        typedef std::basic_ofstream<char>::__filebuf_type buffer_t;
        typedef __gnu_cxx::stdio_filebuf<char> io_buffer_t;
        FILE* cfile_impl(buffer_t* const fb) {
            return (static_cast<io_buffer_t* const>(fb))->file(); 
        }
    public:
        std::unique_ptr<Settings> settings;

    public:
        operator FILE*() {
            return cfile_impl(this->rdbuf());
        }

    public:
        TMP(const char* filename, const std::_Ios_Openmode openmode);
    };

    extern TMP input;
    extern TMP output;
}

#endif 
