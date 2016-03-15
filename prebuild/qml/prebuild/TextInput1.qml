// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

// Text edit object
//
Rectangle {
    property alias btnHeight: btnGeneric.height
    property alias btnWidth: btnGeneric.width
    property alias btnX: btnGeneric.x
    property alias btnY: btnGeneric.y
    property alias btnGradient: btnGeneric.gradient
    property alias btnImage: btn_Image.source
    property alias btnImageBack : btn_ImageBack.source
    property alias btnText: btn_text.text
    property alias text: txt_text.text
    property int   myIndex:0

    id: btnGeneric
    x: 0;
    y: 0; // buttonHeight * 1 + buttonOffsetY;
    height: backstage.buttonHeight * 2;
    width: parent.width - 5;
    radius: 10
    color: clr_back; border.color: clr_border


    // Background graphic
    //
    Image{
        id: btn_ImageBack
        source: resourceBase + "btn1up" + resourceResolution
        fillMode: Image.Tile
        anchors.fill: parent
        anchors.margins: backstage.buttonHeight  - backstage.graphicHeight ;
    }

    // Icon graphic
    //
    Image {
        id: btn_Image
        // source: resourceBase + "settings" + resourceResolution
        height : backstage.graphicHeight ;
        width : backstage.graphicHeight;
        fillMode: Image.Tile
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.leftMargin:  backstage.buttonHeight - backstage.graphicHeight;
        anchors.topMargin: backstage.buttonHeight - backstage.graphicHeight;
        //anchors.top: parent.top; anchors.left: parent.left; fillMode: Image.PreserveAspectFit; smooth: true
    }
    // Caption text
    //
    Text {
        id: btn_text
        text: qsTr(""); font.pixelSize: buttonCaptionSize;  height: 24; width: parent.width - 12
        x: backstage.buttonHeight + 10; // y: backstage.buttonHeight /2
        color: "white"
        anchors.verticalCenter: btn_Image.verticalCenter
    }




    // Input area------------------------
    //
    Rectangle {
        x: parent.x + 10;
        y: backstage.graphicHeight +  backstage.buttonHeight - backstage.graphicHeight
        width: parent.width - 20; radius: 1; border.color: "gold"
        height: backstage.buttonHeight - ( backstage.buttonHeight - backstage.graphicHeight) ;
        TextInput  {
            id: txt_text;
            y: backstage.buttonHeight - backstage.graphicHeight;
            x: 0;
            color: "black"
            height: backstage.graphicHeight;
            width: parent.width;
            //anchors.verticalCenter: parent.verticalCenter;
            //anchors.bottomMargin:  backstage.buttonHeight - backstage.graphicHeight;
            //height: parent.height;
            font.pixelSize: backstage.buttonCaptionSize;
            // anchors.fill: parent
        }

    }

    Component.onCompleted: {
        btnGeneric.y = parent.parent.parent.itemIndex * ( backstage.buttonHeight  + backstage.buttonSpacerHeight) + backstage.buttonOffsetY ;
        myIndex = parent.parent.parent.itemIndex;
        parent.parent.parent.itemIndex++ ;
        parent.parent.parent.itemIndex++ ;
        parent.parent.contentHeight = (  parent.parent.parent.itemIndex * ( backstage.buttonHeight  + backstage.buttonSpacerHeight) ) + backstage.buttonOffsetY ;
    }
}
