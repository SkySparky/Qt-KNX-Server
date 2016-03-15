// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
// import "functions.js" as Functions

// Add a new tag to an item
//
Rectangle {
    id: tagButtonAdd

    signal tagAdded()

    property alias tagHeight: tagButtonAdd.height
    property alias tagWidth: tagButtonAdd.width
    property alias tagX: tagButtonAdd.x
    property alias tagY: tagButtonAdd.y
    property alias tagImage: tag_Image.source
    property alias tagImageBack : tag_ImageBack.source
    property alias tagText: tag_text.text
    property int myIndex:0

    property alias tagColor: tagButtonAdd.color
    property int tagIndex: 0
    property string tagTagText: ""
    property int tagSelected : 0
    property int tagIsNew : 0


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
        id: tag_ImageBack
        source: resourceBase + "btn1up" + resourceResolution
        fillMode: Image.Tile
        anchors.fill: parent
        anchors.margins: 1;
    }
    Image {
        id: tag_Image
        // height: parent.height-6; width: parent.height-6
        height : backstage.graphicHeight ; width : backstage.graphicHeight;
        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left;
        anchors.leftMargin:  backstage.buttonHeight - backstage.graphicHeight;
        fillMode: Image.Tile // Image.PreserveAspectFit
        // source: resourceBase + "managebus1.png"
    }
    Rectangle {
        x: parent.height + 5
        y: 0
        //z: 20
        width: parent.width -  backstage.buttonHeight - 10
        height: buttonCaptionSize + 10
        color: "#2f2f2f"
        anchors.verticalCenter: parent.verticalCenter
        TextEdit {
            id: tag_text
            anchors.fill: parent
            //anchors.verticalCenter: parent.verticalCenter
            // height: 24; width: parent.width;
            color: clr_text
            text: qsTr(""); font.pixelSize: buttonCaptionSize
        }
    }

    onTagSelectedChanged: {
        if (tagSelected == 1)
        {
            tag_Image.source = resourceBase + "checkBoxY"  + resourceResolution;
        }
        else
        {
            tag_Image.source = resourceBase + "checkBoxN"  + resourceResolution;
        }

    }


    MouseArea {
        id: mouse_area1
        x: 0
        y: 0
        height: parent.height
        width: backstage.buttonHeight
        //anchors.fill: parent
        onClicked: {
            if (tagSelected == 0)
            {
                tagSelected = 1;
                tagAdded();
            }
            else
            {
                tagSelected = 0;
            }
        }
        onPressed: parent.tagImageBack = resourceBase + "btn1dn"  + resourceResolution;
        onExited: parent.tagImageBack = resourceBase + "btn1up"  + resourceResolution;
        onCanceled: parent.tagImageBack = resourceBase + "btn1up"  + resourceResolution;

    }
}
