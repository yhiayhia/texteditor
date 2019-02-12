#include "textedit.h"

Textedit::Textedit(QWidget *parent):QTextEdit(parent)
{
    action=new QAction(this);
    action->setCheckable(true);
    setAttribute(Qt::WA_DeleteOnClose);
    isFirstTime=true;
    printer=new QPrinter;
    createConnections();
    setCurrentFile(QString());

}

void Textedit::printslot(){
    QPrintDialog printDlg(printer,this);
    if(printDlg.exec()==QDialog::Accepted){
        print(printer);

    }

}


void Textedit::findDialog(){
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


void Textedit::find()
{
    QString searchString = lineEdit->text();
    QTextDocument *document = this->document();

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
        colorFormat.setBackground(Qt::yellow);

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

void Textedit::closeEvent( QCloseEvent *event ){
if( isSafeToClose() ){
event->accept();
}else{
event->ignore();
}
}

bool Textedit::isSafeToClose(){
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
void Textedit::createConnections(){
    connect(action,SIGNAL(triggered(bool)),this,SLOT(show()));
    connect(action,SIGNAL(triggered(bool)),this,SLOT(setFocus()));
    connect(document(),SIGNAL(modificationChanged(bool)),this,SLOT(setWindowModified(bool)));

}

void Textedit::fileNew(){
    static int documentNumber = 1;
    setWindowTitle(QString("untitled%1[*]").arg(documentNumber));
    action->setText(QString("untitled%1").arg(documentNumber));
    ++documentNumber;
}
void Textedit::open(){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open"));
        loadFile(fileName);

}
void Textedit::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
}
bool Textedit::save(){
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool Textedit::saveAs(){

    QString fileName=QFileDialog::getSaveFileName(this,"Save Document",".");
    return saveFile(fileName);
}
void Textedit::setCurrentFile(const QString &fileName){
    curFile = fileName;
    action->setText(curFile);
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle( QString(tr("%1[*]- %2") ).arg(fileName).arg("Text Editor") );
}
bool Textedit::saveFile(const QString &fileName){
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
    out << toPlainText();
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    return true;
}



void Textedit::about(){
    QMessageBox::about(this,tr("About"),
                       tr("Chost Text Editor \n\n Copyright (C) <2019> <Yhia Ahmed>\n\nThis program is Free Software and licensed under the terms of the GNU General Public License version 3 as published by the Free Software Foundation\n\nE-mail: superkrolo@gmail.com"));
}


