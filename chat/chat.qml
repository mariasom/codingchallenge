// #! env qml
import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import chatserver.backend 1.0

Window {
    visible: true
    width: 400
    height: 520

    ChatServer {
        id: server
    }

    Column {
        spacing: 5
        Rectangle {
            id: userOne

            width: 400
            height: 250

            ColumnLayout {
                anchors.fill: parent

                Text{
                    id: username
                    text: "anne"
                    font.family: "Helvetica"
                    font.pointSize: 15
                    font.bold: true
                    color: "blue"

                }

                TextArea {
                    id: textArea1
                    Layout.fillWidth: true
                    readOnly: true
                    textFormat: TextEdit.RichText
                }

                RowLayout {
                    id: rowLayout1
                    anchors.bottom: parent
                    TextField {
                        id: textf1
                        placeholderText: "Enter message"
                        Layout.fillWidth: true
                    }
                    Button {
                        id: button1
                        text: "Send"
                        onClicked: { 
                            if (textf1.length != 0) {
                                console.log("sending msg: " + textf1.text);
                                server.userName = username.text;
                                server.message =  textf1.text;
                                sendmessage(textArea2, server.userName, server.message, "#FF0000");
                                sendmessage(textArea1 , server.userName, server.message, "#00FF00");
                                clearTextField(textf1);
                            }
                        }
                    }
                }
            }
        }
    
        Rectangle {
            width: 400
            height: 5
            color: "black"
        }

        Rectangle {
            id: userTwo

            y: 305
            width: 400
            height: 250

            ColumnLayout {
                anchors.fill: parent

                Text{
                    id: username2
                    text: "diana"
                    font.family: "Helvetica"
                    font.pointSize: 15
                    font.bold: true
                    color: "blue"

                }

                TextArea {
                    id: textArea2
                    Layout.fillWidth: true
                    readOnly: true
                    textFormat: TextEdit.RichText
                }

                RowLayout {
                    id: rowLayout2
                    anchors.bottom: parent
                    TextField {
                        id: textf2
                        placeholderText: "Enter message"
                        Layout.fillWidth: true
                    }
                    Button {
                        id: button2
                        text: "Send"
                        onClicked: { 
                            if (textf2.length != 0) {
                                console.log("sending msg: " + textf2.text);
                                server.userName = username2.text;
                                server.message = textf2.text;
                                sendmessage(textArea1 , server.userName, server.message, "#FF0000");
                                sendmessage(textArea2 , server.userName, server.message, "#00FF00");
                                clearTextField(textf2);
                            }
                        }
                    }
                }
            }
        }
    }

    function sendmessage( id, user, message, color){
        message = "<p><b style='color:" + color + ";' >" + user + ": </b>" + message + "</p>"
        id.append(message);
    }
    function clearTextField(id){
        id.remove(0,id.length);
    }
}