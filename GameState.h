/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameState.h
 * Author: jordi
 *
 * Created on 3 de mayo de 2017, 10:15
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameStates
{
    STATE_START = 1,
    STATE_MENU = 2, // 2
    STATE_OPTIONS = 3, 
    STATE_LEVEL = 4
};

class GameState {
public:
    GameState();
GameStates getState(){ return mState;};
    virtual ~GameState();
private:

GameStates mState;
};




#endif /* GAMESTATE_H */

