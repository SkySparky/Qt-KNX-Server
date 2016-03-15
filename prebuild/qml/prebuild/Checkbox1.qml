// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

// Manage Button
//
Rectangle {
    id: btnGeneric

    property alias btnHeight: btnGeneric.height;
    property alias btnWidth: btnGeneric.width;
    property alias btnX: btnGeneric.x;
    property alias btnY: btnGeneric.y;
    property alias btnImage: btn_Image.source;
    property alias btnImageBack : btn_ImageBack.source;
    property alias btnText: btn_text.text;
    property int myIndex:0;
    property int cbValue:0;

    onCbValueChanged: {
        cb_Char.text = (  btnGeneric.cbValue == 1 ?  "X" :  " ");
    }

    // function test(value) {
    // }

    signal btnClicked()

    height: backstage.buttonHeight
    width: parent.width - 6
    radius: 10
    x: 0
    y: 0
    color: clr_back; border.color: clr_border
    Image{
        id: btn_ImageBack
        source: resourceBase + "btn1up" + resourceResolution
        fillMode: Image.Tile
        anchors.fill: parent
        anchors.margins: 1;

    }
    Image {
        id: btn_Image
        // height: parent.height-6; width: parent.height-6
        height : backstage.graphicHeight ; width : backstage.graphicHeight;
        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin:  backstage.buttonHeight - backstage.graphicHeight;
        fillMode: Image.Tile // Image.PreserveAspectFit
        // source: resourceBase + "managebus1.png"
    }
    Text {
        id: btn_text
        x: parent.height + 5
        anchors.verticalCenter: parent.verticalCenter
        height: 24; width: parent.width; color: "white"
        text: qsTr(""); font.pixelSize: buttonCaptionSize
    }
    // Check Box
    //
    Rectangle {
        id: cb_Rect

        anchors.right: parent.right; anchors.rightMargin: backstage.buttonHeight - backstage.graphicHeight;
        color: "white"; border.color: "red"; radius: 10
        anchors.verticalCenter: parent.verticalCenter
        height: backstage.graphicHeight / 3 * 2
        width: backstage.graphicHeight / 3 * 2
        Text {
            id: cb_Char
            anchors.fill: parent
            text: qsTr(""); font.bold: true; verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter; color: "black"; font.pixelSize: buttonCaptionSize
        }
    }

    MouseArea {
        id: btn_moureArea
        anchors.fill: parent
        onClicked: {
            btnGeneric.cbValue = ( btnGeneric.cbValue == 0 ? btnGeneric.cbValue = 1 : btnGeneric.cbValue = 0);
            btnGeneric.btnClicked();
        }
        onPressed: parent.btnImageBack = resourceBase + "btn1dn"  + resourceResolution
        onExited: parent.btnImageBack = resourceBase + "btn1up"  + resourceResolution
        onCanceled: parent.btnImageBack = resourceBase + "btn1up"  + resourceResolution
    }

    Component.onCompleted: {
        btnGeneric.y = parent.parent.parent.itemIndex * ( backstage.buttonHeight  + backstage.buttonSpacerHeight) + backstage.buttonOffsetY ;
        myIndex = parent.parent.parent.itemIndex;
        parent.parent.parent.itemIndex++ ;
        parent.parent.contentHeight = (  parent.parent.parent.itemIndex * ( backstage.buttonHeight  + backstage.buttonSpacerHeight) ) + backstage.buttonOffsetY ;
    }

}
