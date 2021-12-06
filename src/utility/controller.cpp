#include "utility/controller.hpp"

#if defined(_WIN32)

Controller::Controller() = default;

bool Controller::KeyboardHit() const { return kbhit(); }

char Controller::GetInput() const { return getch(); }

// by default, getch() does not echo the input or wait for enter
// so raw input does not to be enabled
void Controller::EnableRawInput() const {}
void Controller::RestoreSettings() const {}

#elif defined(__linux__)

Controller::Controller() {
    tcgetattr(STDIN_FILENO, &old_settings_);
}

bool Controller::KeyboardHit() const {
    int bytes;
    ioctl(STDIN_FILENO, FIONREAD, &bytes);
    return bytes > 0;
}

char Controller::GetInput() const {
    char input;
    read(STDIN_FILENO, &input, 1);
    return input;
}

void Controller::EnableRawInput() const {
    struct termios raw_settings = old_settings_;
    raw_settings.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw_settings);
}    

void Controller::RestoreSettings() const {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings_);
}

#endif