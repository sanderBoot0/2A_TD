/**
 * @file displaycontroller.hpp
 * @brief This file contains the DisplayController class
 *
 *
 */

#ifndef DISPLAY_CONTROLLER_HPP
#define DISPLAY_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

/**
 * @brief data type for the gameinfoPool of the DisplayController class
 *
 */
struct gameinfo {
   public:
    // time & score
    int score;
    int seconds;

    gameinfo(int score = 100, int seconds = 0)
        : score(score), seconds(seconds){};
};

/**
 * @brief DisplayController Class used for displaying varius comamnds and game
 * info
 *
 */
class DisplayController : public rtos::task<> {
   private:
    rtos::pool<const char *> commandpool;
    rtos::flag commandflag;

    rtos::pool<gameinfo> gameinfopool;
    rtos::flag gameinfoflag;

    hwlib::target::pin_oc scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    hwlib::target::pin_oc sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus =
    hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    hwlib::glcd_oled oled = hwlib::glcd_oled(i2c_bus, 0x3c);
    hwlib::font_default_16x16 font = hwlib::font_default_16x16();

    hwlib::terminal_from display = hwlib::terminal_from(oled, font);

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
    /**
     * @brief Function that displays the struct data that comes from the
     * GameInfoPool
     *
     */
    void showGameInfo();

    /**
     * @brief Displays Command given via CmdPool on the Oled screen
     *
     * @param p
     */
    void showCommand(const char *p);

   public:
    // DisplayController(hwlib::glcd_oled &oled, hwlib::font_default_16x16
    // &font)
    DisplayController()
        : task(8, "DisplayController"),
          commandpool("commandpool"),
          commandflag(this, "commandflag"),
          gameinfopool("gameinfopool"),
          gameinfoflag(this, "gameinfoflag") {
        display << '\f' << hwlib::flush;
    }
    /**
     * @brief This function writes the given character on the current position
     * of the screen and flushes
     *
     * @param c
     */
    void addChar(const char);

    /**
     * @brief ths function flushes the screen with hwlib::flush
     *
     */
    void flushScreen();

    /**
     * @brief this function clears the screen completely by writing the escape
     * character
     *
     */
    void clearScreen();

    /**
     * @brief function that writes a const char* string to the commandPool to be
     * displayed on the screen via showcommand()
     *
     * @param cmd
     */
    void writeCmdPool(const char *cmd);

    /**
     * @brief function that puts the variables in a struct and writes that
     * struct in a pool of that struct type for it to be displayed via the
     * ShowGameInfo() function
     *
     * @param seconds
     * @param score
     */
    void writeGameInfoPool(int seconds, int score);
};

#endif