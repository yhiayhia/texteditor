#include "sdiwindow.h"

SdiWindow::SdiWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QRect availableGeometry =QApplication::desktop()->availableGeometry(this);
    resize(availableGeometry.width(), availableGeometry.height()); 
    docWidget = new QTextEdit;
    printer=new QPrinter;
    setCentralWidget(docWidget);
    setAttribute(Qt::WA_DeleteOnClose);
    createActions();
    createMenus();
    createToolBars();
    createConnections();
    statusBar()->showMessage( "Done" );
    setCurrentFile(QString());
    isFirstTime=true;
    setWindowIcon(QIcon::fromTheme("accessories-text-editor"));

}

void SdiWindow::createActions(){
newAction = new QAction( QIcon::fromTheme("document-new"), tr("&New"), this );
newAction->setShortcut(QKeySequence::New );
newAction->setStatusTip( tr("Create a new empty file") );

openAction=new QAction(QIcon::fromTheme("document-open"),tr("&Open"),this);
openAction->setShortcut(tr("Ctrl+O"));
openAction->setStatusTip(tr("open a file"));

saveAction=new QAction(QIcon::fromTheme("document-save"),tr("&Save"),this);
saveAction->setShortcut(QKeySequence::Save);
saveAction->setStatusTip(tr("Save the active file"));

saveAsAction=new QAction(QIcon::fromTheme("document-save-as"),tr("&Save &As"),this);
saveAsAction->setShortcut(QKeySequence::SaveAs);
saveAsAction->setStatusTip(tr("Save the acrive file under a different"));

printAction=new QAction(QIcon::fromTheme("document-print"),tr("Print"),this);
printAction->setShortcut(QKeySequence::Print);

closeAction=new QAction(QIcon::fromTheme("window-close"),tr("&Close &Window"),this);
closeAction->setShortcut(QKeySequence::Close);
closeAction->setStatusTip(tr("close this file"));

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

setFontAction=new QAction(QIcon::fromTheme("preferences-desktop-font"),tr("&Font"),this);


aboutAction=new QAction(QIcon::fromTheme("help-about"),tr("&About"),this);
aboutAction->setStatusTip(tr("About text editor"));

aboutQtAction = new QAction( QIcon::fromTheme("help-about"),tr("&About &Qt"), this );
aboutQtAction->setStatusTip( tr("About the Qt toolkit") );
}

void SdiWindow::createMenus()
{

fileMenu = menuBar()->addMenu( tr("&File") );

fileMenu->addAction( newAction );
fileMenu->addAction(openAction);
fileMenu->addAction(saveAction);
fileMenu->addAction(saveAsAction);
fileMenu->addSeparator();
fileMenu->addAction(closeAction);
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

viewMenu=menuBar()->addMenu(tr("&View"));
viewMenu->addAction(toolBarAction);
viewMenu->addSeparator();
viewMenu->addAction(zoomInAction);
viewMenu->addAction(zoomOutAction);

settingsMenu=menuBar()->addMenu(tr("&Settings"));
settingsMenu->addAction(setFontAction);

menuHelp=menuBar()->addMenu(tr("&Help"));
menuHelp->addAction(aboutAction);
menuHelp->addAction(aboutQtAction);
}

void SdiWindow::createToolBars(){

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

void SdiWindow::createConnections(){
    connect( newAction, SIGNAL(triggered()), this, SLOT(fileNew()) );
    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(openNew()));
    connect(saveAction,SIGNAL(triggered(bool)),this,SLOT(save()));
    connect(saveAsAction,SIGNAL(triggered(bool)),this,SLOT(saveAs()));
    connect(closeAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(printAction,SIGNAL(triggered(bool)),this,SLOT(print()));
    connect(exitAction,SIGNAL(triggered(bool)),qApp,SLOT(quit()));

    connect(aboutAction,SIGNAL(triggered(bool)),this,SLOT(about()));
    connect( aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()) );

    connect(zoomInAction,SIGNAL(triggered(bool)),docWidget,SLOT(zoomIn()));
    connect(zoomOutAction,SIGNAL(triggered(bool)),docWidget,SLOT(zoomOut()));
    connect(toolBarAction,SIGNAL(triggered(bool)),fileToolBar,SLOT(setVisible(bool)));
    connect(toolBarAction,SIGNAL(triggered(bool)),editToolBar,SLOT(setVisible(bool)));
    connect(toolBarAction,SIGNAL(triggered(bool)),searchToolBar,SLOT(setVisible(bool)));

    connect( docWidget->document(), SIGNAL(modificationChanged(bool)),this, SLOT(setWindowModified(bool)) );
    connect(docWidget,SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(docWidget,SIGNAL(undoAvailable(bool)),undoAction,SLOT(setEnabled(bool)));
    connect( docWidget, SIGNAL(copyAvailable(bool)),cutAction, SLOT(setEnabled(bool)) );
    connect( docWidget, SIGNAL(copyAvailable(bool)),copyAction, SLOT(setEnabled(bool)) );
    connect(docWidget->document(),SIGNAL(modificationChanged(bool)),saveAction,SLOT(setEnabled(bool)));

    connect(undoAction,SIGNAL(triggered(bool)),docWidget,SLOT(undo()));
    connect(redoAction,SIGNAL(triggered(bool)),docWidget,SLOT(redo()));
    connect( cutAction, SIGNAL(triggered()), docWidget, SLOT(cut()) );
    connect( copyAction, SIGNAL(triggered()), docWidget, SLOT(copy()) );
    connect( pasteAction, SIGNAL(triggered()), docWidget, SLOT(paste()) );
    connect(selectAllAction,SIGNAL(triggered(bool)),docWidget,SLOT(selectAll()));

    connect(setFontAction,SIGNAL(triggered(bool)),this,SLOT(setFont()));

    connect(findAction,SIGNAL(triggered(bool)),this,SLOT(findDialog()));
    //connect(docWidget,SIGNAL(copyAvailable(bool)),findAction,SLOT(setEnabled(bool)));


}

void SdiWindow::print(){
    QPrintDialog printDlg(printer,this);
    if(printDlg.exec()==QDialog::Accepted){
        docWidget->print(printer);
    }

}



void SdiWindow::findDialog(){
    dlg=new QDialog(this);
    layout=new QGridLayout();
    dlg->setLayout(layout);
    findButton=new QPushButton("Find");
    findButton->setDefault(true);
    lineEdit=new QLineEdit();
    findLabel=new QLabel("Find Whate");
    cancelButton =new QPushButton("Cancel");
    layout->addWidget(findLabel,0,0);

    layout->addWidget(lineEdit,0,1);
    layout->addWidget(cancelButton,1,0);
    layout->setRowStretch(1,20);
    layout->addWidget(findButton,1,1);
    connect(findButton,SIGNAL(clicked(bool)),this,SLOT(find()));
    connect(cancelButton,SIGNAL(clicked(bool)),dlg,SLOT(close()));
    dlg->show();
}


void SdiWindow::find()
{
    QString searchString = lineEdit->text();
    QTextDocument *document = docWidget->document();

    bool found = false;

    if (isFirstTime == false)
        document->undo();

    if (searchString.isEmpty()) {
        QMessageBox::information(this, tr("Empty Search Field"),
                "The search field is empty. Please enter a word and click Find.");
    } else {

        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();
//! [6]

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::red);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
            highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull()) {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight,
                                       QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

//! [8]
        cursor.endEditBlock();
//! [7] //! [9]
        isFirstTime = false;

        if (found == false) {
            QMessageBox::information(this, tr("Word Not Found"),
                "Sorry, the word cannot be found.");
        }
    }
}

void SdiWindow::fileNew()
{
    (new SdiWindow())->show();
}

void SdiWindow::openNew(){
    SdiWindow *newWindow=new SdiWindow();
    newWindow->show();
    newWindow->open();
}

void SdiWindow::closeEvent( QCloseEvent *event ){
if( isSafeToClose() ){
event->accept();
}else{
event->ignore();
}
}

bool SdiWindow::isSafeToClose(){
if( isWindowModified() ){
switch( QMessageBox::warning( this, tr("Save Changes"),
                              tr("The document has unsaved changes.\nDo you want to save it before it is closed?"),
                              QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Save ) ){
case QMessageBox::Cancel:return false;
case QMessageBox::Discard:return true;
default:return save();
}
}

return true;
}

void SdiWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    docWidget->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void SdiWindow::open(){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open"));
        loadFile(fileName);

}

bool SdiWindow::save(){
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool SdiWindow::saveAs(){
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

bool SdiWindow::saveFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << docWidget->toPlainText();
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}
void SdiWindow::setCurrentFile(const QString &fileName){
    curFile = fileName;
    docWidget->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle( QString(tr("%1[*]- %2") ).arg(fileName).arg("Text Editor") );
}


void SdiWindow::setFont(){
    docWidget->setFont(QFontDialog::getFont(0,this));
}

void SdiWindow::about(){
    QMessageBox::about(this,tr("About"),
                       tr("Chost Text Editor \n\n Copyright (C) <2019> <Yhia Ahmed>\n\nThis program is Free Software and licensed under the terms of the GNU General Public License version 3 as published by the Free Software Foundation\n\nE-mail: superkrolo@gmail.com"));
}

