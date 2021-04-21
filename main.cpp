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
                        cout << "New User connected with ID : " << data->user_id << endl;
                        ws->subscribe("broadcast");
                    },
                    .message = [](auto *ws, string_view message, uWS::OpCode opCode) {
                        UserConnection *data = ws->getUserData();
                        cout << "New message from User ID : " << data->user_id << endl;
                        cout << "Message : " << message << endl;
                        auto beginning = message.substr(0, 9);
                        if ( beginning.compare("SET_NAME=") == 0){
                            data->user_name = new string ( message.substr(9));
                            cout << "User with ID : " << data->user_id <<" set name to : " << (*data->user_name);
                            cout << endl;
                            string broadcast_message = "NEW_USER : " + (*data->user_name) + to_string(data->user_id);
                            ws->publish("broadcast", broadcast_message, opCode, true);
                        }
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
