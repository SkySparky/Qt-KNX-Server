// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "functions.js" as Functions

Rectangle {
    id: stage
    width: 480
    height: 800
    Text {
        id: dbgText
        anchors.top: parent.top
        text: "Hello World"
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 15

    }
//    MouseArea {
//        x: 0
//        y: 84
//        width: 480
//        height: 716
//        anchors.topMargin: 84
//        anchors.fill: parent
//        onClicked: {
//            Functions.createList();
//        }
//    }

    MouseArea {
        id: mouse_area1
        x: 5
        y: 2
        width: 183
        height: 82
        onClicked: {
            dbgText.text = "CreateList";
            Functions.createList();
        }
    }

    MouseArea {
        id: mouse_area2
        x: 291
        y: 0
        width: 189
        height: 84
        onClicked: {
            // dbgText.text = "ReturnList";
            dbgText.text = Functions.composeReplyString();
        }
    }
    Flickable {
        id: flick_Tags
        y:145
        x:0
        z: 100;
        clip: true
        width: parent.width
        height: 655
        contentWidth: parent.width
        contentHeight: 2000
//        width : backstage.width; height:backstage.height - scrollOffsetY ; x:0; y: scrollOffsetY ; z: 100;
//        contentWidth: backstage.width; clip: true
//        onFlickStarted: { height = ( backstage.stageHeight - backstage.scrollOffsetY ) ;  }
    }

    TextEdit {
        id: text_tags
        x: 0
        y: 92
        width: 480
        height: 53
        text: qsTr("3/the/quick/brown/fox/jumps/over/the/lazy/dog")
        font.pixelSize: 12
    }

}
