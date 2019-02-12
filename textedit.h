#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include<QWidget>
#include<QTextEdit>
#include<QAction>
#include<QApplication>
#include<QCloseEvent>
#include<QMessageBox>
#include<QFileDialog>
#include<QTextStream>
#include<QPushButton>
#include<QLineEdit>
#include<QTextCursor>
#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include<QPrinter>
#include<QPrintDialog>

class Textedit:public QTextEdit{
    Q_OBJECT
public:
    Textedit(QWidget *parent=0);


    void findDialog();
    void open();
    void openNew();
    void printslot();
    bool saveFile(const QString &fileName);
    bool saveAs();
    bool save();
    void fileNew();
    void about();
    void closeEvent(QCloseEvent *event);
    bool isSafeToClose();
    void setCurrentFile(const QString &fileName);
    void loadFile(const QString &fileName);

    QPushButton *findButton;
    QLineEdit *lineEdit;
    QDialog *dlg;
    QGridLayout *layout;
    QLabel *findLabel;
    QPushButton *cancelButton;

    QPrinter *printer;
    QAction *action;
    QAction *windowMenuAction() const { return action; }

    QString curFile;
    bool isFirstTime;
    void createConnections();

private slots:
    void find();

};

#endif // TEXTEDIT_H
