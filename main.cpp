#include <iostream>
#include <uwebsockets/App.h>


using namespace std;

struct UserConnection {
    unsigned long user_id;
    string *user_name;
};

const unsigned int WS_PORT = 9999;
const string C_MESSAGE_TO = "MESSAGE_TO=";
const string C_SET_NAME = "SET_NAME=";

int main() {
    atomic_ulong latest_user_id = 10;
    // "ws://127.0.0.1/"

    vector<thread *> threads(thread::hardware_concurrency());

//Client -> Server
//SET_NAME=<NAME> Setup User name
//MESSAGE_TO id,message

//Server -> Client
//NewUser name, id

    transform(threads.begin(), threads.end(), threads.begin(), [&](auto *thr) {
        return new thread([&]() {
            uWS::App().ws<UserConnection>("/*", {
                    .open = [&](auto *ws) {
                        // Call on connection
                        UserConnection *data = ws->getUserData();
                        data->user_id = latest_user_id++;
                        cout << "New User connected with ID : " << data->user_id << endl;
                        ws->subscribe("broadcast");
                        ws->subscribe("user#" + to_string(data->user_id));
                    },
                    .message = [](auto *ws, string_view message, uWS::OpCode opCode) {
                        UserConnection *data = ws->getUserData();
                        cout << "New message from User ID : " << data->user_id << endl;
                        cout << "Message : " << message << endl;
                        auto beginning = message.substr(0, 9);
                        if (beginning.compare("SET_NAME=") == 0) {

                            data->user_name = new string(message.substr(9));
                            cout << "User with ID : " << data->user_id << " set name to : " << (*data->user_name);
                            cout << endl;
                            string broadcast_message = "NEW_USER : " + (*data->user_name) + to_string(data->user_id);
                            ws->publish("broadcast", string_view(broadcast_message), opCode, false);

                            // Not sure
                        }
                        auto is_message_to = message.substr(0, 11);
                        if (is_message_to.compare(C_MESSAGE_TO) == 0) {
                            // Someone send message
                            auto rest_string = message.substr(C_MESSAGE_TO.size());
                            auto position = rest_string.find(","); // refactoring
                            if (position != string::npos) {
                                auto id_string = rest_string.substr(0, position);
                                auto user_message = rest_string.substr(position + 1);
                                cout << "User message : " << user_message;
                                ws->publish("user#" + string(id_string), user_message, opCode, false);

                            }
                        }
                        // Call on message
                    }
            }).listen(WS_PORT, [](auto *token) {
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
