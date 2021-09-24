import { RegularExpression, Wildcard } from 'objectmaphelper.js';

export var mainWindowMainWindow = {"name": "MainWindow", "type": "MainWindow", "visible": 1};
export var mainWindowPushButtonQPushButton = {"name": "pushButton", "type": "QPushButton", "visible": 1, "window": mainWindowMainWindow};
export var mainWindowPushButton3QPushButton = {"name": "pushButton_3", "type": "QPushButton", "visible": 1, "window": mainWindowMainWindow};
export var dialogCompareDialogCompare = {"name": "Dialog_compare", "type": "Dialog_compare", "visible": 1};
export var dialogComparePushButton3QPushButton = {"name": "pushButton_3", "type": "QPushButton", "visible": 1, "window": dialogCompareDialogCompare};
export var qFileDialogQFileDialog = {"name": "QFileDialog", "type": "QFileDialog", "visible": 1};
export var qFileDialogSplitterQSplitter = {"name": "splitter", "type": "QSplitter", "visible": 1, "window": qFileDialogQFileDialog};
export var splitterSidebarQSidebar = {"container": qFileDialogSplitterQSplitter, "name": "sidebar", "type": "QSidebar", "visible": 1};
export var splitterFrameQFrame = {"container": qFileDialogSplitterQSplitter, "name": "frame", "type": "QFrame", "visible": 1};
export var frameStackedWidgetQStackedWidget = {"container": splitterFrameQFrame, "name": "stackedWidget", "type": "QStackedWidget", "visible": 1};
export var stackedWidgetTreeViewQTreeView = {"container": frameStackedWidgetQStackedWidget, "name": "treeView", "type": "QTreeView", "visible": 1};
export var qFileDialogChooseQPushButton = {"text": "Choose", "type": "QPushButton", "unnamed": 1, "visible": 1, "window": qFileDialogQFileDialog};
export var dialogComparePushButton4QPushButton = {"name": "pushButton_4", "type": "QPushButton", "visible": 1, "window": dialogCompareDialogCompare};
export var dialogComparePushButtonQPushButton = {"name": "pushButton", "type": "QPushButton", "visible": 1, "window": dialogCompareDialogCompare};
export var dialogBackupDialogBackup = {"name": "Dialog_backup", "type": "Dialog_backup", "visible": 1};
export var dialogBackupPushButtonQPushButton = {"name": "pushButton", "type": "QPushButton", "visible": 1, "window": dialogBackupDialogBackup};
export var dialogBackupPushButton2QPushButton = {"name": "pushButton_2", "type": "QPushButton", "visible": 1, "window": dialogBackupDialogBackup};
export var dialogBackupPushButton5QPushButton = {"name": "pushButton_5", "type": "QPushButton", "visible": 1, "window": dialogBackupDialogBackup};
export var dialogSuccessDialogSuccess = {"name": "Dialog_success", "type": "Dialog_success", "visible": 1};
export var dialogSuccessPushButtonQPushButton = {"name": "pushButton", "type": "QPushButton", "visible": 1, "window": dialogSuccessDialogSuccess};
export var dialogBackupCheckBox2QCheckBox = {"name": "checkBox_2", "type": "QCheckBox", "visible": 1, "window": dialogBackupDialogBackup};