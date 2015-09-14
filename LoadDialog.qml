import QtQuick 2.0
import QtQuick.Dialogs 1.0

FileDialog {
    id: loadFileDialog
    title: "Please choose a file"
    nameFilters: [ "Minimal Chess Files (*.mcf)", "All files (*)" ]
    selectExisting: true
    selectMultiple: false
    onAccepted: {
        if(MainBoard.loadGame(this) === true)
        {
            gameScreen.gameLoaded()
        }
    }
}
