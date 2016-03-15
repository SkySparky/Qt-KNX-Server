// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

// Manage Button
//
Rectangle {
    id: btnGeneric

    property alias btnHeight: btnGeneric.height
    property alias btnWidth: btnGeneric.width
    property alias btnX: btnGeneric.x
    property alias btnY: btnGeneric.y
    property alias btnImage: btn_Image.source
    property alias btnImageBack : btn_ImageBack.source
    property alias btnText: btn_text.text
    property int myIndex:0


    // function test(value) {
    // }

    signal btnClicked()

    height: backstage.buttonHeight
    width: parent.width - 6
    radius: 10
    x: 0
    y: 0
    color: clr_back; border.color: clr_border
    // gradient: mouseOut
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
        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left;
        anchors.leftMargin:  backstage.buttonHeight - backstage.graphicHeight;
        fillMode: Image.Tile // Image.PreserveAspectFit
        // source: resourceBase + "managebus1.png"
    }
    Text {
        id: btn_text
        x: parent.height + 5
        anchors.verticalCenter: parent.verticalCenter
        height: 24; width: parent.width; color: clr_text
        text: qsTr(""); font.pixelSize: buttonCaptionSize
    }


    MouseArea {
        anchors.fill: parent
        onClicked: btnGeneric.btnClicked();   // Functions.swap(scr_mainMenu, scr_manage, Functions.glb_TransitionType1 );
        // onPressed: parent.gradient = mousePress
        // onExited: parent.gradient = mouseOut
        // onCanceled: parent.gradient = mouseOut
        onPressed: parent.btnImageBack = resourceBase + "btn1dn"  + resourceResolution
        onExited: parent.btnImageBack = resourceBase + "btn1up"  + resourceResolution
        onCanceled: parent.btnImageBack = resourceBase + "btn1up"  + resourceResolution
    }

    Component.onCompleted: {
        btnGeneric.y = parent.parent.parent.itemIndex * ( backstage.buttonHeight  + backstage.buttonSpacerHeight) + backstage.buttonOffsetY ;
        myIndex = parent.parent.parent.itemIndex;
        parent.parent.parent.itemIndex++ ;
        parent.parent.contentHeight = (  parent.parent.parent.itemIndex * ( backstage.buttonHeight  + backstage.buttonSpacerHeight) ) + backstage.buttonOffsetY ;
        // backstage.dbgText.text = parent.parent.parent.itemIndex ;
        // console.log ( parent.parent.parent.itemIndex + " " + btn_text.text);
        // btn_text.text = parent.parent.parent.itemIndex;

    }

}
