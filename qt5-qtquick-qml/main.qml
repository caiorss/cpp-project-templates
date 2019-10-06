import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import com.qtdeveloper.textedit 1.0

ApplicationWindow {
    id:     rectangle

    property int window_width:  750
    property int window_height: 500

    width:  window_width
    height: window_height
    title: "C++ QML Basic Interface"
    // maximumWidth:  425
    // maximumHeight: 500

    // color: "#5bedbc"
    visible: true

    TextFileModel {
        id: tmodel
    }


    FileDialog{
        id: fileSelectionDlg
        title: "Select a text file"
        folder: shortcuts.home

        onAccepted: {
            console.log("File chosed was " + fileSelectionDlg.fileUrl)            
            tmodel.file = fileSelectionDlg.fileUrl

        }

        onRejected: {
            console.log("File selection rejected.")
        }
    }

    ColumnLayout {
        x: 28
        y: 21

        Label {
            id: labelCurrentFile
            text: "File: " + tmodel.file
        }


        RowLayout{
            Button{
                id:   btnOpenFile
                text: "Open file"
                onClicked: {
                    console.info("Selecting file")
                    fileSelectionDlg.visible = true
                 }
            }

            Button{
                id: btnSave
                text: "Save file"
                onClicked: {
                    tmodel.text = textDisplay.text
                    tmodel.flush()
                }
            }
        }


        // --- Text Area with ScrollBar --- //
        Flickable {
            id: flickable
            x: 27
            y: 99
            width: window_width - 50
            height: 392
            // anchors.fill: parent
            flickableDirection: Flickable.VerticalFlick


            TextArea.flickable: TextArea {
                id: textDisplay
                x: 0
                text: tmodel.text
                // wrapMode: TextArea.Wrap

                readOnly:false
                persistentSelection: true

                leftPadding:   6
                rightPadding:  6
                topPadding:    0
                bottomPadding: 0

                // Text color in text area
                color: "#3fcbe2"

                background: Rectangle {
                    // background color
                    color: "black"
                    border.color: "red"
                }

            }

            ScrollBar.vertical: ScrollBar {
                id: vscrollbar1
                policy: ScrollBar.AlwaysOn
                interactive: false
                width: 10
            }

            ScrollBar.horizontal: ScrollBar {
                id: hscrollbar1
                policy: ScrollBar.AlwaysOn
                interactive: false
                height: 10
            }

            focus: true

            Keys.onPressed: {
                if(event.key === Qt.Key_PageDown)
                    vscrollbar1.increase()

                if(event.key === Qt.Key_PageUp)
                    vscrollbar1.decrease()

            }

            Keys.onUpPressed:    vscrollbar1.decrease()
            Keys.onDownPressed:  vscrollbar1.increase()
            Keys.onLeftPressed:  hscrollbar1.decrease()
            Keys.onRightPressed: hscrollbar1.increase()
        }


    } // -- EoF - ColumnLayout ----//
}
