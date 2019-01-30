#ifndef SDIWINDOW_H
#define SDIWINDOW_H

#include <QMainWindow>
#include<QStatusBar>
#include<QTextEdit>
#include<QAction>
#include<QApplication>
#include<QMenu>
#include<QToolBar>
#include<QMenuBar>
#include<QCloseEvent>
#include<QMessageBox>
#include<QFileDialog>
#include<QTextStream>
#include<QRect>
#include<QDesktopWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QTextCursor>
#include<QDialog>
#include<QGridLayout>
#include<QLabel>

class SdiWindow : public QMainWindow
{
    Q_OBJECT

public:
    SdiWindow(QWidget *parent = 0);
    QTextEdit *docWidget;

    bool isFirstTime;

    QAction *newAction;
    QAction *cutAction;
    QAction *aboutQtAction;
    QAction *exitAction;
    QAction *closeAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *selectAllAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *aboutAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *findAction;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *searchToolBar;

    QPushButton *findButton;
    QLineEdit *lineEdit;
    QDialog *dlg;
    QGridLayout *layout;
    QLabel *findLabel;
    QPushButton *cancelButton;



    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *searchMenu;
    QMenu *menuHelp;
    QMenu *viewMenu;
    QString curFile;
private:
    void createActions();
    void createMenus();
    void createToolBars();
    void closeEvent(QCloseEvent *event);
    bool isSafeToClose();
    void setCurrentFile(const QString &fileName);
    void createConnections();
    void loadFile(const QString &fileName);


public slots:
    void find();
    void findDialog();
    void open();
    void openNew();
    bool saveFile(const QString &fileName);
    bool saveAs();
    bool save();
    void fileNew();
    void about();

};

#endif // SDIWINDOW_H
