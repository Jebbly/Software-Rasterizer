#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#if defined(_WIN32)
#include <conio.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#endif

class Controller {
public:
    Controller();

    bool KeyboardHit() const;
    char GetInput() const;

    void EnableRawInput() const;
    void RestoreSettings() const;

private:
#if defined(__linux__)
    struct termios old_settings_;
#endif 
};

#endif // CONTROLLER_HPP