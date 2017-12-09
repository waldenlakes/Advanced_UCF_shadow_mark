#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QObject>
#include <QGraphicsView>
#include <QFileDialog>
#include <QPushButton>
#include <QWheelEvent>
#include <QLabel>
#include <QString>
#include <QActionGroup>
#include <QMenu>
#include <QGraphicsScene>
#include <QScrollBar>

#define num 256

using namespace cv;
class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MyQGraphicsView(QWidget *parent=0);

    int my_index();

    void wheelEvent(QWheelEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
//    virtual void paintEvent(QPaintEvent *event) override;

    void createActions();
    void translateLanguage();
    void selectImages();
    void selectFolder();
    void removeSelectedImages();
    void removeAllImages();
    void drag_Image();
    void cancel_function();
    void shiyingwindow();
    void fangda10bei();
    void single_pix_biaoji();
    void clear_all_mark();


signals:
    void mouseWheelZoom(bool);
    void test_signal();
    void update_Final_Result_Label_signal(bool);
    void update_graphicsview_signal();
    void biaoji_LeftButton_press(QString);
protected slots:
    void Zoom(bool zoom);
public:
    QImage image,temp_img;
    QGraphicsScene *scene;
    double v_max,h_max,my_v,my_h;
    bool leftmouse;
    Mat final_cvimage;
    Mat MS_reg;
public:
    int DangQianZhangShu;
    int set_color_value;
    int spatialRad;
    int colorRad;
    int maxPryLevel;
    QString picturename,path;
    QStringList filename;
    Mat src, dst;
    Mat Qt_img_rgb;
    float nThreshold = 0;
    float a;
    int nDx[4] = { -1,0,1,0 }, nDy[4] = { 0,1,0,-1 };
    //Mat pUnRegion(dst.rows, dst.cols, CV_8UC1, Scalar::all(0));
    uint pUnRegion[num][num];
    float A[num][num],A_3[3][num][num];//A是经过meanshift分割后的图像//
    int region_index = 0;
    uint region_index_n[num * num],region_index_sum_jiacaitu[3][num * num], region_index_sum[num * num], pnGrowQueX[num * num], pnGrowQueY[num * num];//
public:

    QString fileName;
    float scaleFactor;

    QMenu* pop_menu;
    QAction* add_images_action,*add_folder_action,*remove_selected_action,*remove_all_action,*drag_action,*cancel,*fangda10bei_action,*shiyingwindow_action,*single_pix_biaoji_action,*clear_all_mark_action;
    int biaoji_flag,biaoji_self_cast_shadow,fangkuang_falg,single_pix_biaoji_flag;
    QActionGroup *alignmentGroup;

    QPoint lineStartPoint,lineEndPoint;

    bool isDrawing;

    QPixmap pix;
    QPixmap tempPix;

    int cancel_i,cancel_j,index_cancel_i_j[1024][2],biaoji_cishu;

    int max_index,index_i,index_j;

    uint state_mode_flag;




//    QImage *image;

};

#endif // MYQGRAPHICSVIEW_H
