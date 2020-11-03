// #! env qml
import QtQuick 2.0

// Item {
//    function myQmlFunction(msg: string) : string {
//        console.log("Got message:", msg)
//       return "some return value"
//    }
//}

Rectangle {
    width: 200
    height: 100
    color: "red"

    Text {
        anchors.centerIn: parent
        text: "Hello, World!"
    }
}