#include "Game.h"
#include <cstdio>

#include <windows.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        exit(1);
    }

    Game oGame;

    ::printf("%s", argv[2]);

    // Set app id here
    if (oGame.init("523164037733626") != 0)
    {
        ::fprintf(stderr, "Could not initialize Gameroom Platform\n");
        return 1;
    }
    oGame.gameLoop();
    return 0;
}
