import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    width: parent.width
    height: parent.height
    readonly property int white: 0
    readonly property int black: 1
    readonly property int activeGame: 0
    readonly property int loadedGame: 1
    readonly property int noMessage: 0
    readonly property int check: 1
    readonly property int checkmate: 2
    readonly property variant labelMessages: ["", "Check!", "Checkmate!"]
    readonly property variant colors: ["white", "maroon"]
    readonly property variant pieceColor: ["white", "black"]
    readonly property variant pieceStyle: [Text.Outline, Text.Normal]
    readonly property variant saveButtonText: [qsTr("Save"), qsTr("Next->")]
    readonly property variant stopButtonText: [qsTr("Stop"), qsTr("<-Previous")]

    property int gameStyle: loadedGame
    property bool gameStarted: false
    property int activeMessage: noMessage


    GridLayout {
        id: mainLayout
        columns: 2
        anchors.centerIn: parent

        rowSpacing: 20
        Item {
            height: startButton.height
            width: startButton.width
            Layout.alignment: Qt.AlignCenter
            Button {
                id: startButton
                text: qsTr("Start")
                enabled: true
                visible: {gameStyle == loadedGame}
                onClicked: {
                    gameScreen.startANew();
                }
            }
        }
        Item {
            height: loadButton.height
            width: loadButton.width
            Layout.alignment: Qt.AlignCenter
            Button {
                id: loadButton
                text: qsTr("Load")
                enabled: true
                visible: {gameStyle == loadedGame}
                onClicked: loadDialog.open()
            }
        }

        GridLayout {
            columns: 8
            rowSpacing: 0
            columnSpacing: 0

            Layout.columnSpan: parent.columns
            Layout.alignment: Qt.AlignCenter

            Repeater {
                id: squares
                model: 64
                Rectangle {
                    readonly property int squareColumn:
                        getSquareColumnByIdx(index)
                    readonly property int squareRow: getSquareRowByIdx(index)
                    property string pieceLetter : ""
                    property int pieceSide: white
                    width: 45
                    height: 45
                    color: colors[getColorIndex(index)]
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(MainBoard.selectSquare(squareColumn,
                                                      squareRow) === true)
                            {
                                gameStyle = activeGame
                                saveButton.enabled = true
                                stopButton.enabled = true
                                updateBoard()
                                activeMessage = MainBoard.getCheckStatus()
                            }
                        }
                    }
                    Text {
                        anchors.centerIn: parent
                        text: pieceLetter
                        font.pointSize: 12
                        font.bold: true
                        color: pieceColor[pieceSide]
                        style: pieceStyle[pieceSide]
                        styleColor: "black"
                    }
                }
            }
        }
        Item {
            height: stopButton.height
            width: stopButton.width
            Layout.alignment: Qt.AlignCenter
            Button {
                id: stopButton
                text: stopButtonText[gameStyle]
                enabled: true
                visible: gameStarted
                onClicked: stopButtonClicked()
            }
        }
        Item {
            height: saveButton.height
            width: saveButton.width
            Layout.alignment: Qt.AlignCenter
            Button {
                id: saveButton
                text: saveButtonText[gameStyle]
                Layout.alignment: Qt.AlignCenter
                enabled: true
                visible: gameStarted
                onClicked: saveButtonClicked()
            }
        }
        Rectangle
        {
            color: "transparent"
            radius: 3
            border.color: "black"
            Layout.columnSpan: parent.columns
            Layout.alignment: Qt.AlignCenter
            height: messageLabel.height
            anchors.left: parent.left
            anchors.right: parent.right
            Label {
                id: messageLabel
                text: labelMessages[activeMessage]
                font.pixelSize: 22
                font.italic: true
                color: "steelblue"
                anchors.centerIn: parent
            }
        }

    }
    function getColorIndex(idx) {
        return (Math.floor(idx/8)+(idx%8))%2
    }
    function getSquareColumnByIdx(idx)
    {
        return idx%8;
    }
    function getSquareRowByIdx(idx)
    {
        return (7-Math.floor(idx/8));
    }
    function startANew() {
        MainBoard.startANew();
        gameStyle = activeGame;
        gameStarted = true;
        updateBoard();
    }
    function updateBoard() {
        for(var idx = 0; idx < squares.count; idx++)
        {
            var column = squares.itemAt(idx).squareColumn;
            var row = squares.itemAt(idx).squareRow;
            MainBoard.getPieceLetterAndSide(column, row, squares.itemAt(idx));
        }
        if((gameStyle == loadedGame) && (gameStarted == true))
        {
            stopButton.enabled = MainBoard.canMovePrevious();
            saveButton.enabled = MainBoard.canMoveNext();
            activeMessage = MainBoard.getCheckStatus()
        }
    }
    function stopGame() {
        MainBoard.stopGame()
        gameStarted = false
        updateBoard()
        gameStyle = loadedGame
    }

    function stopButtonClicked() {
        if(gameStyle == activeGame)
        {
            stopGame()
        } else {
            MainBoard.issueMovePrevious()
            updateBoard()
        }
    }
    function saveButtonClicked() {
        if(gameStyle == activeGame)
        {
            saveDialog.open()
        } else {
            MainBoard.issueMoveNext()
            updateBoard()
        }
    }
    function gameLoaded() {
        gameStyle = loadedGame
        gameStarted = true
        updateBoard()

    }
}
