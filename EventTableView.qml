import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import EventClass 1.0

Frame
{
    width: parent.width
    Layout.fillWidth: true
    RowLayout
    {
        width: parent.width
        Layout.fillWidth: true
        TableView {
            id: eventTableView
            width: parent.width
            Layout.fillWidth: true
            implicitWidth: 250
            implicitHeight: 120
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            property var columnWidths: [280, 80, 70, 200]
                 columnWidthProvider: function (column) { return columnWidths[column] }

            model: EventClassModel {
                id: eventClassModel
                eventList: eventDataList
            }

            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                border.width: 1

                Text {
                    text: display
                    anchors.centerIn: parent
                }
            }
            Row {
                id: columnsHeader
                y: eventTableView.contentY
                z: 2
                Repeater {
                    id: headerItems
                    model: eventTableView.columns > 0 ? eventTableView.columns : 1
                    Label {
                        width: eventTableView.columnWidthProvider(modelData)
                        height: 15
                        text: eventClassModel.headerData(modelData, Qt.Horizontal)
                        color: '#ffffff'
                        font.pixelSize: 15
                        padding: 0
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter

                        background: Rectangle {
                            color: "#000022"
                        }
                    }
                }
            }
        }
    }
}
