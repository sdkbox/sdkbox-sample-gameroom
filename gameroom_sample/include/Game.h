#ifndef GAME_H
#define GAME_H

#define BUFFER_SIZE 512
#define BACKSPACE_KEY 8
#define ENTER_KEY '\r'

class Game
{
public:
    Game() {};
    ~Game() {};

    int init(const char* appID);
    void gameLoop();

private:
    bool exitGame = false;
    char commandBuffer[BUFFER_SIZE];
    int commandIndex = 0;

    void loginWithScopes();

    void checkKeyboard();
    void processCommand();
    void pumpFBGMessages();

    void outputCommands();
};

#endif
