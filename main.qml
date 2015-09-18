import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Minimal Chess")
    width: 480
    height: 560
    visible: true
    minimumHeight: height
    maximumHeight: height
    minimumWidth: width
    maximumWidth: width
    property alias gameScreen: gameScreen
    property alias saveDialog: saveDialog
    property alias loadDialog: loadDialog
    property url chosenFile: ""
    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }


    GameScreen {
        id: gameScreen
        anchors.fill: parent
    }

    SaveDialog {
        id: saveDialog
    }
    LoadDialog {
        id: loadDialog
    }
}
