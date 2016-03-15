var tagObjects = new Array ;    // Holds the references to the dynamically created objects
var tagCount = 0;
var tagListSep = "the";         // Holds the list of tags as a slash "/" seperated multiparams line
var tagSelectedCount = 0;
var tagSeperatorChar ="/";
var btnTagCancel;
var btnTagSave;

function createList() {
    // Destroy existing list
    //
    if (tagCount != 0 ) destroyList();

    // Split input tags string into array and count items
    //
    tagListSep = text_tags.text;
    var tmpTagsList = tagListSep.split(tagSeperatorChar);        // Split on "/" character
    tagCount = tmpTagsList.length - 1;              // First field tell us how many are already selected for the item
    tagSelectedCount = parseInt( tmpTagsList[0] );  // Number of selected items

    if ( tagListSep == "" ) return;

    // Create items based on tags and attach to flickable on screen
    //
    var i;
    var component = Qt.createComponent("TagButton.qml");    //  Creating a component. Will be instantiated in many copies bellow
    // Todo wait for "if (component.status == Component.Ready)"
    //
    for ( i=1; i<=tagCount; i++ ) {
        tagObjects[i] = component.createObject(flick_Tags.contentItem);
        tagObjects[i].y = (i - 1) * 100;              // TODO
        tagObjects[i].tagText = tmpTagsList[i];
        tagObjects[i].tagIndex = i;
        if (i<=tagSelectedCount)
        {       // Selected already
            tagObjects[i].tagColor = "silver";
            tagObjects[i].tagSelected = 1;
        }
        else
        {       // Not selected tags
            tagObjects[i].tagSelected = 0;
            tagObjects[i].tagColor = "grey";
        }
    }
    flick_Tags.contentHeight = tagCount * 100 + 400;  // TODO

    // Add cancel and save buttons at list bottom
    //
    component = Qt.createComponent("BackStageBtn1.qml");
    btnTagCancel = component.createObject(flick_Tags.contentItem);
    btnTagCancel.y = tagCount * 100;
    btnTagCancel.btnText = "Cancel";
    btnTagSave = component.createObject(flick_Tags.contentItem);
    btnTagSave.y = (tagCount +1 ) * 100;
    btnTagCancel.btnText = "Save";
}


function destroyList() {
    var i;
    for ( i=1; i<=tagCount; i++ ) {
        tagObjects[i].destroy();
    }
    tagCount = 0;

}

// After user has selected/deselected/added some tags a string must be returned with only the selected tags
function composeReplyString() {
    var i;
    var retString = "";

    for ( i=1; i<=tagCount; i++ ) {

        if ( tagObjects[i].tagSelected == 1 ) {
            retString = retString + "/" + tagObjects[i].tagText ;
        }
        tagObjects[i].destroy();
    }
    tagCount = 0;


    return (retString);
}
