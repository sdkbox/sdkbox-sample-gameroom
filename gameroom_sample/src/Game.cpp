#include "Game.h"
#include "PluginGameroom.h"
#include "Listener.h"
#include <conio.h>
#include <cstdio>


int Game::init(const char* appID)
{
    auto listener = new GameListener();
    sdkbox::PluginGameroom::setListener(listener);
    if (sdkbox::PluginGameroom::init(appID) != sdkbox::SUCCESS) {
        sdkbox::PluginGameroom::log("Init Plugin Gameroom Failed!");
        return 1;
    }

    ::printf("Press h for list of commands.\nCommand > ");

    return 0;
}

void Game::gameLoop()
{
    while (!exitGame)
    {
        checkKeyboard();
        // pumpFBGMessages();
    }

    auto l = sdkbox::PluginGameroom::listener();
    sdkbox::PluginGameroom::destroy();

    delete l;
}

void Game::checkKeyboard()
{

    if (_kbhit())
    {
        int key = _getch();

        switch (key) {
        case BACKSPACE_KEY:
            if (commandIndex > 0)
            {
                commandIndex--;
                commandBuffer[commandIndex] = '\0';
                ::printf("%c %c", key, key);
            }
            break;
        case ENTER_KEY:
            commandBuffer[commandIndex] = '\0';
            ::printf("\n");
            processCommand();
            break;

        default:
            if (commandIndex < BUFFER_SIZE)
            {
                commandBuffer[commandIndex] = key;
                ::printf("%c", key);
                commandIndex++;
            }
            break;
        }
    }
}

void Game::processCommand()
{
    char *command = nullptr;
    char *param1 = nullptr;
    char *param2 = nullptr;
    char *param3 = nullptr;

    char *nextToken = nullptr;
    char seps[] = " ";

    // Grab the command parameters
    command = strtok_s(commandBuffer, seps, &nextToken);
    param1 = strtok_s(NULL, seps, &nextToken);

    if (command) {
        switch (command[0])
        {
        case 'h':
            outputCommands();
            break;
        case 'l':
            loginWithScopes();
            break;
        case 'f':
            fbg_FeedShare(
                nullptr,
                "https://www.facebook.com",
                "Testing Link Name",
                "Testing Link Caption",
                "Testing Link Description",
                "http://www.pamperedpetz.net/wp-content/uploads/2015/09/Puppy1.jpg",
                nullptr
            );
            break;
        case 'p':
            fbg_PurchaseIAP(
                param1,
                1,
                1,
                1,
                nullptr,
                nullptr,
                nullptr
            );
            break;
        case 'u':
            fbg_PurchaseIAPWithProductURL(
                "https://friendsmash-unity.herokuapp.com/payments/100coins.php",
                1,
                1,
                1,
                nullptr,
                nullptr,
                nullptr
            );
        case 'v':
            fbg_PayPremium();
            break;
        case 'b':
            fbg_HasLicense();
            break;
        case 'a':
            fbg_AppRequest(
                "Try out this game!",
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                3,
                nullptr,
                nullptr
            );
            break;
        case 'q':
            exitGame = true;
            break;
        case 'w':
            ::printf(
                "Is Logged In: %d\n",
                fbg_IsLoggedIn()
            );
            break;
        case 'e': {
            auto formDataHandle = fbg_FormData_CreateNew();
            fbg_FormData_Set(formDataHandle, "abc", 3, "def", 3);
            fbg_FormData_Set(formDataHandle, "ghi", 3, "jkl", 3);
            fbg_LogAppEventWithValueToSum(
                "libfbgplatform",
                formDataHandle,
                1
            );
            break;
        }
        case 'r':
            fbg_ActivateApp();
            break;
        case 'o':
            fbg_FetchOVRAccessToken();
            break;
        default:
            ::printf("Invalid Command\n");
            break;
        }

        memset(commandBuffer, 0, sizeof(char)*BUFFER_SIZE);
        commandIndex = 0;
    }

    ::printf("Command > ");
}

void Game::loginWithScopes() {

    fbgLoginScope loginScopes[2] = { fbgLoginScope::user_friends, fbgLoginScope::email };
    fbg_Login_WithScopes(
        2,
        loginScopes
    );
}

void Game::outputCommands()
{
    ::printf("\nList of Commands\n----------------\n"
        "h - list commands\n"
        "l - Login (fbg_Login)\n"
        "f - Feed Share (fbg_FeedShare)\n"
        "p - Purchase IAP (fbg_PurchaseIAP)\n"
        "v - Pay Premium (fbg_PayPremium)\n"
        "b - Has License (fbg_HasLicense)\n"
        "a - App Request (fbg_AppRequest)\n"
        "w - Is Logged In (fbg_IsLoggedIn)\n"
        "e - App Event (fbg_LogAppEventWithValueToSum)\n"
        "r - Actiate App (fbg_ActivateApp()\n"
        "o - Fetch OVR Access Token (fbg_FetchOVRAccessToken)\n"
        "q - quit\n\n");
}
