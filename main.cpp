#include <iostream>
#include <uwebsockets/App.h>

using namespace std;

struct UserConnection {
    unsigned long user_id;
    string user_name;


};

int main() {
    unsigned long latest_user_id = 10;
    // "ws://127.0.0.1/"
    uWS::App().ws<UserConnection>("/*", {
            .open = [&](auto *ws) {
                // Call on connection
                UserConnection *data = ws->getUserData();
                data->user_id = latest_user_id++;


            },
            .message = [](auto *ws, string_view message, uWS::OpCode opCode) {
                // Call on message
            }
    });
}
