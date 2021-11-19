import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import PathData 1.0
Frame {
    ListView {
        implicitWidth: 250
        implicitHeight: 250
        model: PathDataModel {
            pathList: pathDataList
        }

        delegate: RowLayout {
        implicitWidth: 250
            Text {
                text: model.description
                Layout.fillWidth: true
            }
            Button {
                text: "Remove"
                onClicked: {
                    console.log("Tekst: " + model.row )
                    pathDataList.removeItem(model.row)
                   }
            }
        }
    }
}
