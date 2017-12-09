#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QGraphicsView>
#include <QFileDialog>
#include <QPushButton>
#include <QWheelEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextCodec>
#include <QKeyEvent>
#include "myqgraphicsview.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void keyPressEvent(QKeyEvent * e);
//    void keyReleaseEvent(QKeyEvent * e);

//    void wheelEvent(QWheelEvent * event);
//    bool eventFilter(QObject *target, QEvent *e);

signals:
//    void mouseWheelZoom(bool);
protected slots:
    void Btn_readimage_clicked();
    void pushButton_2_clicked();
    void pushButton_4_clicked();
    void pushButton_3_clicked();
    void next_picture_pushButton_clicked();
    void ColorEdit_textEdited(const QString &arg1);
    void ColorEdit_2_textChanged(const QString &arg1);
    void ColorEdit_3_textChanged(const QString &arg1);
    void ColorEdit_4_textChanged(const QString &arg1);
    void ColorEdit_5_textChanged(const QString &arg1);
    void mainwindow_biaoji_LeftButton_press(QString);
    void update_Final_Result_Label(bool);
    void update_graphicsview();
//    void Zoom(bool zoom);


private:
    Ui::MainWindow *ui;
    MyQGraphicsView *graphicsview;
    QLabel *labelimage,*Final_Result_Label;


//    QPushButton *Btn_readimage;
    QLabel *poslabel;


    QPushButton *Btn_readimage,*pushButton_2,*pushButton_3,*next_picture_pushButton,*pushButton_4;
    QLabel *label1_1,*label1_2,*label1_3,*label1_4,*label1_5;
    QLabel *label2_1,*label2_2,*label2_3;
    QLineEdit *ColorEdit1_1,*ColorEdit1_2,*ColorEdit1_3,*ColorEdit1_4,*ColorEdit1_5;
    QLineEdit *lineEdit,*lineEdit_2,*lineEdit_3;
    bool flag;
    bool first_pic_seg_flag;
};

#endif // MAINWINDOW_H
