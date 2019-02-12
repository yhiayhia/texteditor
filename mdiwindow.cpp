#include "mdiwindow.h"

MdiWindow::MdiWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QRect availableGeometry =QApplication::desktop()->availableGeometry(this);
    resize(availableGeometry.width(), availableGeometry.height()); 
   workSpace=new QWorkspace;
    setCentralWidget(workSpace);
    setAttribute(Qt::WA_DeleteOnClose);
    createActions();
    createMenus();
    createToolBars();
    createConnections();
    statusBar()->showMessage( "Done" );
    setWindowIcon(QIcon::fromTheme("accessories-text-editor"));

}

void MdiWindow::createActions(){
newAction = new QAction( QIcon::fromTheme("document-new"), tr("&New"), this );
newAction->setShortcut(QKeySequence::New );
newAction->setStatusTip( tr("Create a new empty file") );

openAction=new QAction(QIcon::fromTheme("document-open"),tr("&Open"),this);
openAction->setShortcut(tr("Ctrl+O"));
openAction->setStatusTip(tr("open a file"));

saveAction=new QAction(QIcon::fromTheme("document-save"),tr("&Save"),this);
saveAction->setShortcut(QKeySequence::Save);
saveAction->setStatusTip(tr("Save the active file"));

windowActionGroup=new QActionGroup(this);

saveAsAction=new QAction(QIcon::fromTheme("document-save-as"),tr("&Save &As"),this);
saveAsAction->setShortcut(QKeySequence::SaveAs);
saveAsAction->setStatusTip(tr("Save the acrive file under a different"));

printAction=new QAction(QIcon::fromTheme("document-print"),tr("Print"),this);
printAction->setShortcut(QKeySequence::Print);

/*closeAction=new QAction(QIcon::fromTheme("window-close"),tr("&Close &Window"),this);
closeAction->setShortcut(QKeySequence::Close);
closeAction->setStatusTip(tr("close this file"));*/

exitAction=new QAction(QIcon::fromTheme("application-exit"),tr("&Exit"),this);
exitAction->setStatusTip(tr("Close the text editor"));
exitAction->setShortcut(QKeySequence::Quit);

undoAction=new QAction(QIcon::fromTheme("edit-undo"),tr("&Undo"),this);
undoAction->setStatusTip(tr("Undo the laste editing action"));
undoAction->setShortcut(QKeySequence::Undo);
undoAction->setEnabled(false);

redoAction=new QAction(QIcon::fromTheme("edit-redo"),tr("&Redo"),this);
redoAction->setStatusTip(tr("Redo the laste editing action"));
redoAction->setShortcut(QKeySequence::Redo);
redoAction->setEnabled(false);

cutAction = new QAction( QIcon::fromTheme("edit-cut"), tr("&Cut"), this );
cutAction->setShortcut( QKeySequence::Cut );
cutAction->setStatusTip( tr("Cut selected text to clipboard") );
cutAction->setEnabled(false);

copyAction=new QAction(QIcon::fromTheme("edit-copy"),tr("&Copy"),this);
copyAction->setShortcut(QKeySequence::Copy);
copyAction->setStatusTip(tr("Copy selected text to clipboard"));
copyAction->setEnabled(false);

pasteAction=new QAction(QIcon::fromTheme("edit-paste"),tr("&Paste"),this);
pasteAction->setShortcut(QKeySequence::Paste);
pasteAction->setStatusTip(tr("Paste text from clipboard"));

selectAllAction=new QAction(QIcon::fromTheme("edit-select-all"),tr("&Select &All"),this);
selectAllAction->setStatusTip(tr("Select all text "));
selectAllAction->setShortcut(QKeySequence::SelectAll);



findAction=new QAction(QIcon::fromTheme("edit-find"),tr("&Find"),this);
findAction->setShortcut(QKeySequence::Find);
findAction->setStatusTip(tr("Search for text"));

zoomInAction=new QAction(QIcon::fromTheme("zoom-in"),tr("&Zoom &In"),this);
zoomInAction->setShortcut(QKeySequence::ZoomIn);
zoomInAction->setStatusTip(tr("Zoom In"));
zoomOutAction=new QAction(QIcon::fromTheme("zoom-out"),tr("&Zoom &Out"),this);
zoomOutAction->setShortcut(QKeySequence::ZoomOut);
zoomOutAction->setStatusTip(tr("Zoom Out"));
toolBarAction=new QAction(tr("&Tool &Bar"),this);
toolBarAction->setStatusTip(tr("Show/Hide toolbar"));
toolBarAction->setCheckable(true);
toolBarAction->setChecked(true);
closeAction=new QAction(QIcon::fromTheme("window-close"),tr("&Close"),this);
closeAction->setShortcut(QKeySequence::Close);
closeAction->setStatusTip(tr("Close active window"));
closeAllAction=new QAction(tr("&Close &All"),this);
closeAllAction->setStatusTip(tr("close all windows"));

setFontAction=new QAction(QIcon::fromTheme("preferences-desktop-font"),tr("&Font"),this);


aboutAction=new QAction(QIcon::fromTheme("help-about"),tr("&About"),this);
aboutAction->setStatusTip(tr("About text editor"));

aboutQtAction = new QAction( QIcon::fromTheme("help-about"),tr("&About &Qt"), this );
aboutQtAction->setStatusTip( tr("About the Qt toolkit") );
}

void MdiWindow::createMenus()
{

fileMenu = menuBar()->addMenu( tr("&File") );

fileMenu->addAction( newAction );
fileMenu->addAction(openAction);
fileMenu->addAction(saveAction);
fileMenu->addAction(saveAsAction);
fileMenu->addSeparator();
fileMenu->addAction(printAction);
fileMenu->addSeparator();
fileMenu->addAction( exitAction );

editMenu=menuBar()->addMenu(tr("&Edit"));
editMenu->addAction(undoAction);
editMenu->addAction(redoAction);
editMenu->addSeparator();
editMenu->addAction(cutAction);
editMenu->addAction(copyAction);
editMenu->addAction(pasteAction);
editMenu->addSeparator();
editMenu->addAction(selectAllAction);

searchMenu=menuBar()->addMenu(tr("&Search"));
searchMenu->addAction(findAction);

windowMenu=menuBar()->addMenu(tr("&Window"));
windowMenu->addAction(toolBarAction);
windowMenu->addSeparator();
windowMenu->addAction(zoomInAction);
windowMenu->addAction(zoomOutAction);
windowMenu->addSeparator();
windowMenu->addAction(closeAction);
windowMenu->addAction(closeAllAction);
windowMenu->addSeparator();

settingsMenu=menuBar()->addMenu(tr("&Settings"));
settingsMenu->addAction(setFontAction);

menuHelp=menuBar()->addMenu(tr("&Help"));
menuHelp->addAction(aboutAction);
menuHelp->addAction(aboutQtAction);
}

void MdiWindow::createToolBars(){

fileToolBar = addToolBar( tr("File") );
fileToolBar->addAction( newAction );
fileToolBar->addAction(openAction);
fileToolBar->addAction(saveAction);

editToolBar=addToolBar(tr("Edit"));
editToolBar->addAction(undoAction);
editToolBar->addAction(redoAction);
editToolBar->addSeparator();
editToolBar->addAction(cutAction);
editToolBar->addAction(copyAction);
editToolBar->addAction(pasteAction);
editToolBar->addSeparator();
editToolBar->addAction(selectAllAction);

searchToolBar=addToolBar(tr("Search"));
searchToolBar->addAction(findAction);

}

void MdiWindow::createConnections(){
    connect( newAction, SIGNAL(triggered()), this, SLOT(fileNew()) );
    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(open()));
    connect(saveAction,SIGNAL(triggered(bool)),this,SLOT(save()));
    connect(workSpace, SIGNAL(windowActivated(QWidget *)),this, SLOT(updateMenus()));
    connect(saveAsAction,SIGNAL(triggered(bool)),this,SLOT(saveAs()));
    connect(printAction,SIGNAL(triggered(bool)),this,SLOT(print()));
    connect(exitAction,SIGNAL(triggered(bool)),qApp,SLOT(quit()));

    connect(aboutAction,SIGNAL(triggered(bool)),this,SLOT(about()));
    connect( aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()) );

    connect(zoomInAction,SIGNAL(triggered(bool)),this,SLOT(zoomIn()));
    connect(zoomOutAction,SIGNAL(triggered(bool)),this,SLOT(zoomOut()));
    connect(toolBarAction,SIGNAL(triggered(bool)),fileToolBar,SLOT(setVisible(bool)));
    connect(toolBarAction,SIGNAL(triggered(bool)),editToolBar,SLOT(setVisible(bool)));
    connect(toolBarAction,SIGNAL(triggered(bool)),searchToolBar,SLOT(setVisible(bool)));
    connect(closeAction,SIGNAL(triggered(bool)),workSpace,SLOT(closeActiveWindow()));
    connect(closeAllAction,SIGNAL(triggered(bool)),workSpace,SLOT(closeAllWindows()));

    connect(undoAction,SIGNAL(triggered(bool)),this,SLOT(undo()));
    connect(redoAction,SIGNAL(triggered(bool)),this,SLOT(redo()));
    connect( cutAction, SIGNAL(triggered()), this, SLOT(cut()) );
    connect( copyAction, SIGNAL(triggered()), this, SLOT(copy()) );
    connect( pasteAction, SIGNAL(triggered()), this, SLOT(paste()) );
    connect(selectAllAction,SIGNAL(triggered(bool)),this,SLOT(selectAll()));

    connect(setFontAction,SIGNAL(triggered(bool)),this,SLOT(setFont()));

    connect(findAction,SIGNAL(triggered(bool)),this,SLOT(findDialog()));


}
Textedit *MdiWindow::createEditor(){
Textedit  *editor = new Textedit;

connect(editor,SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
connect(editor,SIGNAL(undoAvailable(bool)),undoAction,SLOT(setEnabled(bool)));
connect( editor, SIGNAL(copyAvailable(bool)),cutAction, SLOT(setEnabled(bool)) );
connect(editor, SIGNAL(copyAvailable(bool)),copyAction, SLOT(setEnabled(bool)) );
workSpace->addWindow(editor);
windowMenu->addAction(editor->windowMenuAction());
windowActionGroup->addAction(editor->windowMenuAction());
return editor;
}

void MdiWindow::fileNew()
{
    Textedit *editor = createEditor();
    editor->fileNew();
    editor->show();
}



void MdiWindow::open(){
    Textedit *editor = createEditor();
    editor->open();
    editor->show();
    statusBar()->showMessage(QString("Open %1").arg(activeEditor()->curFile));
}

void MdiWindow::closeEvent( QCloseEvent *event ){
    workSpace->closeAllWindows();
    if (activeEditor()) {
    event->ignore();
    } else {
    event->accept();
    }
}

void MdiWindow::save(){
    if (activeEditor()){
   activeEditor()->save();
   statusBar()->showMessage(QString("saved %1").arg(activeEditor()->curFile));
    }
}

void MdiWindow::saveAs(){
    if(activeEditor()){
        activeEditor()->saveAs();
    }
}
void MdiWindow::print(){
    if(activeEditor()){
        activeEditor()->printslot();
    }
}

void MdiWindow::cut(){
    if(activeEditor()){
        activeEditor()->cut();
    }
}
void MdiWindow::copy(){
    if(activeEditor()){
        activeEditor()->copy();
    }
}
void MdiWindow::paste(){
    if(activeEditor()){
        activeEditor()->paste();
    }
}
void MdiWindow::selectAll(){
    if(activeEditor()){
        activeEditor()->selectAll();
    }
}
void MdiWindow::undo(){
    if(activeEditor()){
        activeEditor()->undo();
    }
}
void MdiWindow::redo(){
    if(activeEditor()){
        activeEditor()->redo();
    }
}

void MdiWindow::zoomIn(){
    if(activeEditor()){
        activeEditor()->zoomIn();
    }
}

void MdiWindow::zoomOut(){
    if(activeEditor()){
        activeEditor()->zoomOut();
    }
}

void MdiWindow::findDialog(){
    if(activeEditor()){
        activeEditor()->findDialog();
    }
}

void MdiWindow::setFont(){
    if(activeEditor()){
        activeEditor()->setFont(QFontDialog::getFont(0,this));
    }
}

Textedit *MdiWindow::activeEditor()
{
return qobject_cast<Textedit *>(workSpace->activeWindow());
}
void MdiWindow::updateMenus()
{
if (activeEditor())
activeEditor()->windowMenuAction()->setChecked(true);
}

void MdiWindow::about(){
        activeEditor()->about();

}



