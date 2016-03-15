// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: mainMenu
    width: 600
    height: 480
    color: "black"

    signal btnClicked(int type,string address, string value);

    Component {
        id: listDelegate
        Item {
            width: listView.width; height: 105
            Row {
                Column {
                    DeviceButton {
                        btnHeight: 100
                        devDescription: description   //button description [string]
                        devType: type           //device type [int] (see: en_en_devType in GroupAddrObject)
                        devValue: value         //the group address value [string]
                        devAddress: groupAddr   //this is the group address and it's a hidden property [string]
                        btnWidth: mainMenu.width - 20
                        devTheme: "default"
                        onClicked: {
                            btnClicked(devType, devAddress, devValue);  //emit event on clicked
                        }
                    } //:~ MenuButton
                } //~:Column
            } //~: Row
            ListView.onAdd: console.log("item added");
        } //~: Item
    } //~: Component

    ListView {
          id: listView
          anchors.fill: parent; anchors.margins: 5
          model: screenModel    //screenModel is referenced in C++
          delegate: listDelegate
          focus: true

    } //~: ListView

    ScrollBar {
        scrollArea: listView; height: listView.height; width: 8
        anchors.right: listView.right
    }

}
