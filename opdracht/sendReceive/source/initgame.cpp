#include "../headers/initgame.hpp"

void Initgame::shoot(uint8_t playername, uint8_t weapontype){
    uint16_t data = 0;
    data += (playername << 1);
    data += (weapontype << 6);
    uint8_t controlbits = (playername ^ weapontype);
    data += (controlbits << 11);
    sender.write(data);
}