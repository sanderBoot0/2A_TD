#ifndef DISPLAY_CONTROLLER_HPP
#define DISPLAY_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "time_entity.hpp"

struct gameinfo {
   public:
    // time & score
    int score;
    int seconds;

    gameinfo(int score = 100, int seconds = 0)
        : score(score), seconds(seconds){};
};

class DisplayController : public rtos::task<> {
   private:
    rtos::pool<const char *> commandpool;
    rtos::flag commandflag;

    rtos::pool<gameinfo> gameinfopool;
    rtos::flag gameinfoflag;

    hwlib::terminal_from display;

    void main() {
        for (;;) {
            auto event = wait(gameinfoflag + commandflag);
            if (event == commandflag) {
                showCommand(commandpool.read());
            }
            if (event == gameinfoflag) {
                showGameInfo();
            }
        }
    }

   public:
    DisplayController(hwlib::glcd_oled &oled, hwlib::font_default_16x16 &font)
        : task(8, "DisplayController"),
          commandpool("commandpool"),
          commandflag(this, "commandflag"),
          gameinfopool("gameinfopool"),
          gameinfoflag(this, "gameinfoflag"),
          display(oled, font) {
        display << '\f' << hwlib::flush;
    }

    void showGameInfo();

    void showCommand(const char *p);

    void addChar(const char);

    void flushScreen();

    void clearScreen();

    void writeCmdPool(const char *cmd);

    void writeGameInfoPool(int seconds, int score);
};

#endif