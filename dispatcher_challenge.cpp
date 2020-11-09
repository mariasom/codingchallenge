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

class Controller {
 public:
    bool help(rapidjson::Value &payload) {
        cout << "Controller::help: command: ";

        Value::MemberIterator help = payload.FindMember("help");
        cout << help->value.GetString() << endl;

        return true;
    }

    bool exit(rapidjson::Value &payload) {
        cout << "Controller::exit: command: \n";
        
        Value::MemberIterator reason = payload.FindMember("reason");
        cout << reason->value.GetString() << endl;

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
            return 1;

        assert(document.HasMember("command"));

        const std::string commandName(
            document.FindMember("command")->value.GetString());
        Value::MemberIterator command = document.FindMember("command");
        cout << commandName << endl;
        Value::MemberIterator payload = document.FindMember("payload");

        if (command_handlers_.find(commandName) != command_handlers_.end()) {
            if (commandName == "help")
                Controller::help(payload->value);
            else if (commandName == "exit")
                Controller::exit(payload->value);
           /// command_handlers_[commandName]->()
        } else {
            cerr << "command: \'" << commandName << "\' not found" << endl;
            //CommandHandler handler;
            //addCommandHandler(commandName, handler(payload));
        }

        /*Document document;
        if (document.Parse<0>(command_json.c_str()).HasParseError())
            return 1;
        assert(document.HasMember("command"));
        Value::MemberIterator command = document.FindMember("command");
        cout << command->value.GetString() << endl;
        Value::MemberIterator pay = document.FindMember("payload");

        if (command_handlers_.find(command->value.GetString()) != command_handlers_.end()){
            cout << "key found" << endl;
        }
        else {
            cout << "key not found" << endl;
        }*/

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
    //CommandHandler handler;
    // Implement
    // add command handlers in Controller class to CommandDispatcher using addCommandHandler

    // command_dispatcher.addCommandHandler(std::string("help"), handler(help_command));
    // command_dispatcher.addCommandHandler(std::string("exit"), handler(exit_command);
    // gimme ...
    // command line interface
    string command;
    while( ! g_done ) {
        cout << "COMMANDS: {\"command\":\"exit\", \"payload\":{\"reason\":\"User requested exit.\"}}\n";
        cout << "\tenter command : ";
        getline(cin, command);
        command_dispatcher.dispatchCommand(command);
    }

    std::cout << "COMMAND DISPATCHER: ENDED" << std::endl;
    return 0;
}