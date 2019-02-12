#ifndef MdiWINDOW_H
#define MdiWINDOW_H
#include"textedit.h"
#include <QMainWindow>
#include<QStatusBar>
#include<QApplication>
#include<QMenu>
#include<QToolBar>
#include<QMenuBar>
#include<QRect>
#include<QFontDialog>
#include<QDesktopWidget>
#include<QWorkspace>
#include<QActionGroup>

class MdiWindow : public QMainWindow
{
Q_OBJECT
public:
    MdiWindow(QWidget *parent = 0);
    QTextEdit *docWidget;

    bool isFirstTime;

    QWorkspace *workSpace;

    QAction *newAction;
    QAction *cutAction;
    QAction *aboutQtAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *selectAllAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *printAction;
    QAction *aboutAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *setFontAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *toolBarAction;
    QAction *findAction;
    QActionGroup *windowActionGroup;
    QAction *closeAction;
    QAction *closeAllAction;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *searchToolBar;

    QPushButton *findButton;
    QLineEdit *lineEdit;
    QDialog *dlg;
    QGridLayout *layout;
    QLabel *findLabel;
    QPushButton *cancelButton;

    QPrinter *printer;



    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *searchMenu;
    QMenu *menuHelp;
    QMenu *viewMenu;
    QMenu *settingsMenu;
    QString curFile;
    QMenu *windowMenu;
private:
    void createActions();
    void createMenus();
    void createToolBars();
    void closeEvent(QCloseEvent *event);
    bool isSafeToClose();
    void setCurrentFile(const QString &fileName);
    void createConnections();
    void loadFile(const QString &fileName);

    Textedit *createEditor();
    Textedit *activeEditor();


public slots:
    void updateMenus();
    void findDialog();
    void open();
    void zoomIn();
    void zoomOut();
    void print();
    void saveAs();
    void save();
    void fileNew();
    void cut();
    void copy();
    void paste();
    void selectAll();
    void undo();
    void redo();
    void setFont();
    void about();

};

#endif // MdiWINDOW_H
