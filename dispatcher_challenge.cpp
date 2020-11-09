#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <utility>

//
// supporting tools and software
//
// Validate and test your json commands
// https://jsonlint.com/

// RapidJSON : lots and lots of examples to help you use it properly
// https://github.com/Tencent/rapidjson
//

// std::function
// std::bind
// std::placeholders
// std::map
// std::make_pair

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

bool g_done = false;

//
// TEST COMMANDS
//
auto help_command = R"(
 {
  "command":"help",
  "payload": {
    "usage":"Enter json command in 'command':'<command>','payload': { // json payload of arguments }",
  }
 }
)";

auto exit_command = R"(
 {
  "command":"exit",
  "payload": {
     "reason":"Exiting program on user request."
  }
 }
)";

auto clear_command = R"(
 {
  "command":"clear",
  "payload": {
     "action":"Deleting all created commands on user request."
  }
 }
)";

auto list_command = R"(
 {
  "command":"list",
  "payload": {
     "action":"Listing all commands."
  }
 }
)";

class Controller: public CommandDispatcher {
 public:
    bool help(rapidjson::Value &payload) {
        cout << "Controller::help: command: ";

        Value::MemberIterator help = payload.FindMember("usage");
        cout << help->value.GetString() << endl;

        return true;
    }

    bool exit(rapidjson::Value &payload) {
        cout << "Controller::exit: command: \n";

        Value::MemberIterator reason = payload.FindMember("reason");
        cout << reason->value.GetString() << endl;

        return true;
    }

    bool clear(rapidjson::Value &payload) {
        cout << "Controller::clear: command: \n";

        Value::MemberIterator reason = payload.FindMember("action");
        CommandDispatcher::~CommandDispatcher();

        return true;
    }

    bool list(rapidjson::Value &payload) {
        cout << "Controller::list: command: \n";

        Value::MemberIterator reason = payload.FindMember("action");
        

        return true;
    }
    // implement 3-4 more commands
};

// gimme ... this is actually tricky
// Bonus Question: why did I type cast this? ~ what is happenning here?  
typedef std::function<bool(rapidjson::Value &)> CommandHandler;

class CommandDispatcher {
 public:
    // ctor - need impl
    CommandDispatcher() {

    }

    // dtor - need impl
    virtual ~CommandDispatcher() {
        command_handlers_.clear();
        // question why is it virtual? Is it needed in this case?
        // -> because 
    }

    bool addCommandHandler(std::string command, CommandHandler handler) {
        cout << "CommandDispatcher: addCommandHandler: " << command << std::endl;

        command_handlers_.insert(make_pair(command, handler));

        return true;
    }

    bool dispatchCommand(std::string command_json)
    {
        cout << "COMMAND: " << command_json << endl;

        Document document;
        if (document.Parse<0>(command_json.c_str()).HasParseError())
            return false;

        if (document.HasMember("command")) {
            const std::string commandName(
                document.FindMember("command")->value.GetString());
            Value::MemberIterator command = document.FindMember("command");
            cout << commandName << endl;
            Value::MemberIterator payload = document.FindMember("payload");

            if (command_handlers_.find(commandName) != command_handlers_.end()) {
                /* 
                if (commandName == "help")
                    Controller::help(payload->value);
                else if (commandName == "exit")
                    Controller::exit(payload->value);
                else if (commandName == "clear")
                    Controller::clear(payload->value);
                else if (commandName == "list")
                    Controller::list(payload->value);
                */
            } else {
                cerr << "command: \'" << commandName << "\' not found" << endl;
            }
        } else {
            cerr << "entered in wrong format." << endl;
            return false;
        }
        return true;
    }

private:

    // gimme ...
    std::map<std::string, CommandHandler> command_handlers_;

    // another gimme ...
    // Question: why delete these?

    // delete unused constructors
    CommandDispatcher (const CommandDispatcher&) = delete;
    CommandDispatcher& operator= (const CommandDispatcher&) = delete;

};

int main()
{
    std::cout << "COMMAND DISPATCHER: STARTED" << std::endl;

    CommandDispatcher command_dispatcher;
    Controller controller;             // controller class of functions to "dispatch" from Command Dispatcher
    CommandHandler handler;
    // Implement
    // add command handlers in Controller class to CommandDispatcher using addCommandHandler

    // command_dispatcher.addCommandHandler(std::string("help"), CommandHandler});
    // command_dispatcher.addCommandHandler(std::string("exit"), CommandHandler});
    // gimme ...
    // command line interface
    string command;
    while ( !g_done ) {
        cout << "COMMANDS: {\"command\":\"exit\", \"payload\":{\"reason\":\"User requested exit.\"}}\n";
        cout << "\tenter command : ";
        getline(cin, command);
        command_dispatcher.dispatchCommand(command);
    }

    std::cout << "COMMAND DISPATCHER: ENDED" << std::endl;
    return 0;
}