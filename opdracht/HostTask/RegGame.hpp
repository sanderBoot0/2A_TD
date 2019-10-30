#ifndef REGGAME_HPP
#define REGGAME_HPP
#include "rtos.hpp"
#include "GameRules.hpp"

template<int N>

class RegGame : public rtos::task<>{
private:
    GameRules g[N];

void main(){
    enum state_t = {Player, Firepower, }

}

public:
    RegGame():
    task("RegGame")
    {}





};

#endif 