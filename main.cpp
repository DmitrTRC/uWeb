#include <iostream>
#include <uwebsockets/App.h>

using namespace std;

struct UserConnection {
    unsigned long user_id;
    string *user_name;


};

int main() {
    atomic_ulong latest_user_id = 10;
    // "ws://127.0.0.1/"
    vector<thread *> threads(thread::hardware_concurrency());


    transform(threads.begin(), threads.end(), threads.begin(), [&](auto *thr) {
        return new thread([&]() {
            uWS::App().ws<UserConnection>("/*", {
                    .open = [&](auto *ws) {
                        // Call on connection
                        UserConnection *data = ws->getUserData();
                        data->user_id = latest_user_id++;
                    },
                    .message = [](auto *ws, string_view message, uWS::OpCode opCode) {
                        // Call on message
                    }
            }).listen(9999, [](auto *token) {
                if (token) {
                    cout << "Server started and listening on port 9999" << endl;
                } else {
                    cout << "Server failed to start :(" << endl;
                }
            }).run();
        });
    });
    for_each(threads.begin(), threads.end(), [](auto *thr) { thr->join(); });

}
