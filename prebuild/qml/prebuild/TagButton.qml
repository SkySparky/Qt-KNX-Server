// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
// import "functions.js" as Functions

Rectangle {
    id: tagButton



    property alias tagHeight: tagButton.height
    property alias tagWidth: tagButton.width
    property alias tagX: tagButton.x
    property alias tagY: tagButton.y
    property alias tagImage: tag_Image.source
    property alias tagImageBack : tag_ImageBack.source
    property alias tagText: tag_text.text
    property int myIndex:0


    property alias tagColor: tagButton.color
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
    Text {
        id: tag_text
        x: parent.height + 5
        anchors.verticalCenter: parent.verticalCenter
        height: 24; width: parent.width; color: clr_text
        text: qsTr(""); font.pixelSize: buttonCaptionSize
    }


    onTagSelectedChanged: {
        // tagColor =( tagSelected == 1 ? "Silver" : "Grey" );
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
        anchors.fill: parent
        onClicked: {
            if (tagSelected == 0)
            {
                tagSelected = 1;
                // tag_Image.source = resourceBase + "checkBoxY"  + resourceResolution;
            }
            else
            {
                tagSelected = 0;
                // tag_Image.source = resourceBase + "checkBoxN"  + resourceResolution;
            }
        }
        onPressed: parent.tagImageBack = resourceBase + "btn1dn"  + resourceResolution;
        onExited: parent.tagImageBack = resourceBase + "btn1up"  + resourceResolution;
        onCanceled: parent.tagImageBack = resourceBase + "btn1up"  + resourceResolution;

    }
}
