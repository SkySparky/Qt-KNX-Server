// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//DEV_SWITCH    : 0
//DEV_DIMMER    : 1
//DEV_RGB       : 2
//DEV_SHUTTER   : 3
//DEV_TAGBTN    : 4

//MENU_BACKSTAGE    : 0
//MENU_MANAGE       : 1
//MENU_ADD          : 2
//MENU_ITEM_OPTIONS : 3
//MENU_RESET        : 4
//MENU_IMPEXPORT    : 5
//MENU_SETTINGS     : 6
//MENU_ABOUT        : 7

Rectangle {
    width: 480
    height: 600
    color: "black"
    id: backstage

    signal exit(int status);    //exit to another screen (eg. stage=0)
    signal quit();

    function returnToStage() {
        exit(0);
    }

    Text {
        id: txtDebug
        color: "silver"
        font.pointSize: 24
        anchors.verticalCenter: backstage.verticalCenter
        text : "This is the BACKSTAGE screen! \r\nPress to return to STAGE..."
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            //Test remove:
            returnToStage();
            //:~ Text
        }
    }
}
