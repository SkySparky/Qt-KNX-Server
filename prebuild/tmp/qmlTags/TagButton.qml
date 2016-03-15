// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
// import "functions.js" as Functions

Rectangle {
    id: tagButton

    property alias tagText: text_edit.text
    property alias tagColor: tagButton.color
    property int tagIndex: 0
    property string tagTagText: ""
    property int tagSelected : 0
    property int tagIsNew : 0

    width: 480
    height: 100
    color: "grey"

    onTagSelectedChanged: {
        tagColor =( tagSelected == 1 ? "Silver" : "Grey" );
    }

    TextEdit {
        id: text_edit
        anchors.fill: parent
        text: qsTr("text edit")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 24
    }
    MouseArea {
        id: mouse_area1
        anchors.fill: parent
        onClicked: {
            if (tagSelected == 0)
            {
                tagSelected = 1;
            }
            else
            {
                tagSelected = 0;
            }
        }
    }
}
