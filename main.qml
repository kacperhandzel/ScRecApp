import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2


ApplicationWindow {
    id: appWindow


    visible: true
    title: qsTr("Hello World")
    property int margin: 11
        width: mainLayout.implicitWidth + 2 * margin
        height: mainLayout.implicitHeight + 2 * margin
        minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
        minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin

        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            folder: shortcuts.home
            selectFolder: true
            selectExisting: true
            selectMultiple: false
            onAccepted: {
                console.log("You chose: " + fileDialog.fileUrls)
                filePathTextField.text = fileDialog.fileUrl
                pathDataList.appendItem(fileDialog.fileUrl)
            }
            onRejected: {
                console.log("Canceled")
            }
        }

    ColumnLayout {
        id: mainLayout
        Layout.fillWidth: true
        RowLayout {
            id: rowLayout
            TextField {
                id: filePathTextField
                placeholderText: "Add path to watch"
                Layout.fillWidth: true
            }
            Button {
                id: addPathButton
                text: "Add"
                onClicked: { console.log("addPathButton");  fileDialog.open()}
            }
        }
        Text {
            text: "Watched paths"
        }


        PathListView {
            anchors.centerIn: parent

        }

        TableView {
            id: eventTableView

            columnSpacing: 1
            rowSpacing: 1
            clip: true
        }

        RowLayout {
            id: buttonRowLayout
            Button {
                id: clearEventsButton
                text: "Clear"
                onClicked: console.log("clearPathButton")
            }
            Button {
                id: startEventsButton
                text: "Start"
            }

            Button {
                id: stopEventsButton
                text: "Stop"
            }
        }
    }
}
