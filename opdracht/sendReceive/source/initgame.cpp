#include "../headers/initgame.hpp"

void Initgame::shoot(uint8_t playername, uint8_t weapontype) {
    uint16_t data = (1 << 15);
    data += (playername << 10);
    data += (weapontype << 5);
    uint8_t controlbits = (playername ^ weapontype);
    data |= controlbits;
    sender.write(data);
}