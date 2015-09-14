import QtQuick 2.0
import QtQuick.Dialogs 1.0

FileDialog {
    id: saveFileDialog
    title: "Please choose a file"
    nameFilters: [ "Minimal Chess Files (*.mcf)", "All files (*)" ]
    selectExisting: false
    selectMultiple: false
    onAccepted: MainBoard.saveGame(this)
}
