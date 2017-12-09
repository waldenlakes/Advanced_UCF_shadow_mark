#include "myqgraphicsview.h"

MyQGraphicsView::MyQGraphicsView(QWidget *parent): QGraphicsView(parent)
{

    connect(this,SIGNAL(mouseWheelZoom(bool)),this,SLOT(Zoom(bool)));

    createActions();
    translateLanguage();

    isDrawing=false;
    pix = QPixmap(1024, 768);
    pix.fill(Qt::white);

    scaleFactor=100.0;
    leftmouse=false;

    biaoji_flag=0;
    biaoji_self_cast_shadow=0;
    fangkuang_falg=0;
    single_pix_biaoji_flag=0;

//    image = new QImage();

    //2.参数的初始化
    DangQianZhangShu=0;
    set_color_value=2;//初始化为2
    spatialRad=30;
    colorRad=20;
    maxPryLevel=3;
    a=0.3;
    lineStartPoint.setX(0);
    lineStartPoint.setY(0);
    lineEndPoint.setX(0);
    lineEndPoint.setY(0);// 初始化位置
    biaoji_flag=0;
    fangkuang_falg=0;
    nThreshold = 0;
    region_index = 0;
    final_cvimage.create(num, num, CV_8UC1);
    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
        for (int j = 0; j < num; j++)
        {
            final_cvimage.at<uchar>(i,j)=0;
        }
    MS_reg.create(num, num, CV_8UC1);
    Qt_img_rgb.create(num,num, CV_8UC3);
    cancel_i=0;
    cancel_j=0;
    for (int i = 0; i < 1024; i++)
        for (int j = 0; j < 2; j++)
        {
            index_cancel_i_j[i][j]=0;
        }
    biaoji_cishu=0;
    state_mode_flag=0;
    /*
    temp_img=new QImage();
    temp_img->load("D:/Images/001.jpg");
 //   pix=QPixmap::fromImage(*temp_img);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*temp_img));
    this->setScene(scene);
    //graphicsview->resize(image->width()+10, image->height()+10);//graphicsview->resize(image->width() + 10, image->height() + 10);
    this->show();
    */

    qDebug("MyQGraphicsView_wancheng");
}
/////////////////////////////////////////////////////////
void MyQGraphicsView::wheelEvent(QWheelEvent * event)
{
    //if(image->isNull())
    //    return;
    if (event->delta() > 0)
    {
        emit mouseWheelZoom(true);//先执行槽函数，再执行调试输出Up
//        mylabel->setText("up");
        qDebug("up");
    }
    else
    {
        emit mouseWheelZoom(false);
//        mylabel->setText("down");
        qDebug("down");
    }

}

void MyQGraphicsView::Zoom(bool zoom)
{
    int w=(scaleFactor-10.0)/100.0*image.width();
    int h=(scaleFactor-10.0)/100.0*image.height();
    if (zoom && scaleFactor >= 20)
    {

        scaleFactor += 10;
        QMatrix old_matrix;
        old_matrix = this->matrix();
        this->resetMatrix();
        this->translate(old_matrix.dx(), old_matrix.dy());
        qDebug("%d,%d",old_matrix.dx(),old_matrix.dy());
        qDebug("%f",scaleFactor);
        this->scale(scaleFactor/100.0, scaleFactor/100.0);


    }
    else if (!zoom && scaleFactor >= 20 && w>=400 && h>=400)
    {
        scaleFactor -= 10;
        QMatrix old_matrix;
        old_matrix = this->matrix();
        this->resetMatrix();
        this->translate(old_matrix.dx(), old_matrix.dy());
        qDebug("%d,%d",old_matrix.dx(),old_matrix.dy());
        qDebug("%f",scaleFactor);
        this->scale( scaleFactor/100.0,  scaleFactor/100.0);
    }

    else if (scaleFactor <= 20 && w>=400 && h>=400){

        scaleFactor = 20;
    }

}

/////////////////////////////////////////////////////////
void MyQGraphicsView::createActions()
{
    alignmentGroup = new QActionGroup(this);
    //创建菜单、菜单项
    pop_menu = new QMenu();
    add_images_action = new QAction(this);
    add_folder_action = new QAction(this);
    remove_selected_action = new QAction(this);
//    remove_all_action = new QAction(this);
    drag_action = new QAction(this);
    cancel = new QAction(this);
    fangda10bei_action = new QAction(this);
    shiyingwindow_action = new QAction(this);
    single_pix_biaoji_action = new QAction(this);
    clear_all_mark_action = new QAction(this);

    add_images_action->setCheckable(true);
    add_folder_action->setCheckable(true);
    remove_selected_action->setCheckable(true);
    //remove_all_action->setCheckable(true);
    drag_action->setCheckable(true);
    //cancel->setCheckable(true);
    single_pix_biaoji_action->setCheckable(true);

    alignmentGroup->addAction(add_images_action);
    alignmentGroup->addAction(add_folder_action);
    alignmentGroup->addAction(remove_selected_action);
//    alignmentGroup->addAction(remove_all_action);
    alignmentGroup->addAction(drag_action);
    alignmentGroup->addAction(cancel);
    alignmentGroup->addAction(fangda10bei_action);
    alignmentGroup->addAction(shiyingwindow_action);
    alignmentGroup->addAction(single_pix_biaoji_action);
    alignmentGroup->addAction(clear_all_mark_action);

    //连接信号与槽
    connect(add_images_action, &QAction::triggered, this, &MyQGraphicsView::selectImages);
    connect(add_folder_action, &QAction::triggered, this, &MyQGraphicsView::selectFolder);
    connect(remove_selected_action, &QAction::triggered, this, &MyQGraphicsView::removeSelectedImages);
//    connect(remove_all_action, &QAction::triggered, this, &MyQGraphicsView::removeAllImages);
    connect(drag_action,&QAction::triggered,this,&MyQGraphicsView::drag_Image);
    connect(cancel,&QAction::triggered,this,&MyQGraphicsView::cancel_function);
    connect(fangda10bei_action,&QAction::triggered,this,&MyQGraphicsView::fangda10bei);
    connect(shiyingwindow_action,&QAction::triggered,this,&MyQGraphicsView::shiyingwindow);
    connect(single_pix_biaoji_action,&QAction::triggered,this,&MyQGraphicsView::single_pix_biaoji);
    connect(clear_all_mark_action,&QAction::triggered,this,&MyQGraphicsView::clear_all_mark);
}

void MyQGraphicsView::translateLanguage()
{
    add_images_action->setText(tr("标记cast-shadow"));
    add_folder_action->setText(tr("标记self-cast-shadow"));
    remove_selected_action->setText(tr("区域合并"));
//    remove_all_action->setText(tr("清除方框"));
    drag_action->setText(tr("拖拽图片"));
    cancel->setText(tr("撤销当前标注"));
    fangda10bei_action->setText(tr("放大"));
    shiyingwindow_action->setText(tr("缩小"));
    single_pix_biaoji_action->setText(tr("单像素点标记"));
    clear_all_mark_action->setText(tr("清除标注"));
}

void MyQGraphicsView::contextMenuEvent(QContextMenuEvent *event)//右击就触发该事件
{

    pop_menu->clear();//清除原有菜单
    pop_menu->addAction(add_images_action);
    pop_menu->addAction(add_folder_action);
    pop_menu->addAction(cancel);
    pop_menu->addAction(clear_all_mark_action);
    pop_menu->addAction(remove_selected_action);
//    pop_menu->addAction(remove_all_action);
    pop_menu->addAction(drag_action);
    pop_menu->addAction(fangda10bei_action);
    pop_menu->addAction(shiyingwindow_action);
    pop_menu->addAction(single_pix_biaoji_action);

    pop_menu->exec(QCursor::pos());//菜单出现的位置为当前鼠标的位置
    event->accept();
}

void MyQGraphicsView::selectImages()//cast-shadow
{
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::NoDrag);
    this->setCursor(Qt::ArrowCursor);

    biaoji_flag=1;
    biaoji_self_cast_shadow=0;
    fangkuang_falg=0;
    single_pix_biaoji_flag=0;
    state_mode_flag=1;
    emit update_Final_Result_Label_signal(true);//其实更新poslabel
/*
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
        {
            final_cvimage.at<uchar>(i,j)=0;

        }

    emit update_Final_Result_Label_signal();
*/
}
void MyQGraphicsView::selectFolder()//self-cast-shadow
{
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::NoDrag);
    this->setCursor(Qt::ArrowCursor);
    biaoji_self_cast_shadow=1;
    biaoji_flag=0;
    fangkuang_falg=0;
    single_pix_biaoji_flag=0;
    state_mode_flag=2;
    emit update_Final_Result_Label_signal(false);//其实更新poslabel
/*
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
        {
            final_cvimage.at<uchar>(i,j)=0;

        }

    emit update_Final_Result_Label_signal();
*/

}
void MyQGraphicsView::removeSelectedImages()//区域合并
{
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::NoDrag);
    this->setCursor(Qt::CrossCursor);
    fangkuang_falg=1;
    biaoji_flag=0;
    biaoji_self_cast_shadow=0;
    single_pix_biaoji_flag=0;


}
void MyQGraphicsView::removeAllImages()//清除方框
{
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::NoDrag);
    this->setCursor(Qt::CrossCursor);
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
    //label->update();
     scene->clear();
     tempPix=QPixmap::fromImage(image);
     scene->addPixmap(tempPix);
     this->setScene(scene);
     fangkuang_falg=1;
     biaoji_flag=0;
     biaoji_self_cast_shadow=0;
     single_pix_biaoji_flag=0;

}
void MyQGraphicsView::drag_Image()//拖拽图片
{
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    fangkuang_falg=0;
    biaoji_flag=0;
    biaoji_self_cast_shadow=0;
    single_pix_biaoji_flag=0;
}
void MyQGraphicsView::cancel_function()//撤销当前标注
{
    qDebug("cancel");
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::NoDrag);
    this->setCursor(Qt::ArrowCursor);
    if(biaoji_cishu==0)
    {
        return;
    }
    if(biaoji_flag==1 || biaoji_self_cast_shadow==1)
        for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
            for (int j = 0; j < num; j++)
            {
                if(pUnRegion[index_cancel_i_j[biaoji_cishu-1][0]][index_cancel_i_j[biaoji_cishu-1][1]]==pUnRegion[i][j])
                {
                    final_cvimage.at<uchar>(i,j)=0;
                }
            }
    if(single_pix_biaoji_flag==1)
        final_cvimage.at<uchar>(index_cancel_i_j[biaoji_cishu-1][0],index_cancel_i_j[biaoji_cishu-1][1])=0;
    biaoji_cishu--;
    //QString str = "("+QString :: number(y) +", "+QString::number(x)+")";
    emit biaoji_LeftButton_press("null");

}

void MyQGraphicsView::clear_all_mark()//清除标注
{
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::NoDrag);
    this->setCursor(Qt::ArrowCursor);
    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
        for (int j = 0; j < num; j++)
            final_cvimage.at<uchar>(i,j)=0;
    biaoji_cishu=0;
    emit biaoji_LeftButton_press("null");
}

void MyQGraphicsView::fangda10bei()//放大10倍
{
    if(image.isNull())
        return;
//    this->setDragMode(QGraphicsView::NoDrag);
//    this->setCursor(Qt::ArrowCursor);
    scaleFactor = 800.0;
    QMatrix old_matrix;
    old_matrix = this->matrix();
    this->resetMatrix();
    this->translate(old_matrix.dx(), old_matrix.dy());
    qDebug("%d,%d",old_matrix.dx(),old_matrix.dy());
    qDebug("%f",scaleFactor);
    this->scale(scaleFactor/100.0, scaleFactor/100.0);
}

void MyQGraphicsView::shiyingwindow()//放大2倍
{
    if(image.isNull())
        return;
//    this->setDragMode(QGraphicsView::NoDrag);
//    this->setCursor(Qt::ArrowCursor);
    scaleFactor = 200.0;
    QMatrix old_matrix;
    old_matrix = this->matrix();
    this->resetMatrix();
    this->translate(old_matrix.dx(), old_matrix.dy());
    qDebug("%d,%d",old_matrix.dx(),old_matrix.dy());
    qDebug("%f",scaleFactor);
    this->scale(scaleFactor/100.0, scaleFactor/100.0);
}

void MyQGraphicsView::single_pix_biaoji()//单像素标记
{
    if(image.isNull())
        return;
    this->setDragMode(QGraphicsView::NoDrag);
    this->setCursor(Qt::ArrowCursor);
    fangkuang_falg=0;
    biaoji_flag=0;
    biaoji_self_cast_shadow=0;
    single_pix_biaoji_flag=1;

}


/////////////////////////////////////////////////////////
/*
void MyQGraphicsView::paintEvent(QPaintEvent *event)
{
//    MyQGraphicsView::paintEvent(event);//必须有，才能让自己设置的背景图片显示出来
    if(false)//(fangkuang_falg==1)
    {
    int x, y, w, h;
    x = lineStartPoint.x();
    y = lineStartPoint.y();
    w = lineEndPoint.x() - x;
    h = lineEndPoint.y() - y;
    qDebug("old_x:%d",x);
    qDebug("old_y:%d",y);
    qDebug("old_w:%d",w);
    qDebug("old_h:%d",h);

    QScrollBar *mybar= this->horizontalScrollBar();
    my_h=(*mybar).value();
    h_max=(*mybar).maximum();
    qDebug("my_h:%d",(*mybar).value());
    qDebug("h_max:%d",(*mybar).maximum());
    mybar= this->verticalScrollBar();
    my_v=(*mybar).value();
    v_max=(*mybar).maximum();
    qDebug("my_v:%d",(*mybar).value());
    qDebug("v_max:%d",(*mybar).maximum());

    x=(my_h/h_max*(scaleFactor/100.0*image->height()-380)+x)/(scaleFactor/100.0);
    y=(my_v/v_max*(scaleFactor/100.0*image->width()-380)+y)/(scaleFactor/100.0);
    w=w/(scaleFactor/100.0);
    h=h/(scaleFactor/100.0);
    qDebug("scaleFactor:%f",scaleFactor);
    qDebug("x:%d",x);
    qDebug("y:%d",y);
    qDebug("w:%d",w);
    qDebug("h:%d",h);

//    QPainter painter(this->viewport());

    if (isDrawing)
    {

//        tempPix=QPixmap::fromImage(*image);
//        tempPix = pix;
//        QPainter pp(&tempPix);
//        pp.drawRect(x, y, w, h);
//        painter.drawPixmap(0, 0, tempPix);
//        qDebug("ll");

        scene->clear();
        tempPix=QPixmap::fromImage(*image);
        QPainter pp(&tempPix);
        pp.drawRect(y, x, w, h);
        //pp.drawRect(100, 0, 100, 10);
        scene->addPixmap(tempPix);
        //scene->addRect(x,y,w,h);

        //qDebug("%d",scene->height());
        //qDebug("%d",scene->width());
        this->setScene(scene);
        //graphicsview->resize(image->width()+10, image->height()+10);//graphicsview->resize(image->width() + 10, image->height() + 10);
        this->show();

    }
    else
    {
//        QPainter pp(&pix);
//        pp.drawRect(x, y, w, h);
//        painter.drawPixmap(0, 0, pix);
//        tempPix=QPixmap::fromImage(*image);
        //tempPix = pix;
        //QPainter pp(&tempPix);
        //pp.drawRect(x, y, w, h);
        //painter.drawPixmap(0, 0, tempPix);
        scene->clear();
        tempPix=QPixmap::fromImage(*image);
        QPainter pp(&tempPix);
        //pp.drawRect(100, 0, 100, 10);
        pp.drawRect(y, x, w, h);
        scene->addPixmap(tempPix);
        //scene->addRect(x,y,w,h);
        this->setScene(scene);
    }

    }

    QGraphicsView::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
    //painter.drawLine(lineStartPoint,lineEndPoint);
    painter.drawRect(lineStartPoint.x(),lineStartPoint.y(),lineEndPoint.x()-lineStartPoint.x(),lineEndPoint.y()-lineStartPoint.y());

//    QPainter painter(this);
//    painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
//    painter.drawRect(650+lineStartPoint.x(),85+lineStartPoint.y(),lineEndPoint.x()-lineStartPoint.x(),lineEndPoint.y()-lineStartPoint.y());

}
*/
void MyQGraphicsView::mouseMoveEvent(QMouseEvent *event)
{

    if (leftmouse)
    {
        if(fangkuang_falg==1 && isDrawing==true)
        {
            lineEndPoint = event->pos();
            //update();//调用绘图事件
            //repaint();
            //this->viewport()->update();
            int x, y, w, h;
            x = lineStartPoint.x();
            y = lineStartPoint.y();
            w = lineEndPoint.x() - x;
            h = lineEndPoint.y() - y;
            QScrollBar *mybar= this->horizontalScrollBar();
            my_h=(*mybar).value();
            h_max=(*mybar).maximum();
            mybar= this->verticalScrollBar();
            my_v=(*mybar).value();
            v_max=(*mybar).maximum();

            //x=(my_h/h_max*(scaleFactor/100.0*image->height()-380)+x)/(scaleFactor/100.0);
            //y=(my_v/v_max*(scaleFactor/100.0*image->width()-380)+y)/(scaleFactor/100.0);
            x=(my_h+x)/(scaleFactor/100.0);
            y=(my_v+y)/(scaleFactor/100.0);
            w=w/(scaleFactor/100.0);
            h=h/(scaleFactor/100.0);

//            image = QImage((const unsigned char*)(Qt_img_rgb.data),Qt_img_rgb.cols,Qt_img_rgb.rows,Qt_img_rgb.cols*Qt_img_rgb.channels(),QImage::Format_RGB888);
            scene->clear();
            tempPix=QPixmap::fromImage(image);
            QPainter pp(&tempPix);
            pp.setPen(QPen(Qt::blue,1,Qt::DashLine));
            pp.drawRect(x, y, w, h);
            scene->addPixmap(tempPix);
            //scene->addRect(x,y,w,h);
            this->setScene(scene);
            //this->show();

            qDebug("2");

        }
        if(biaoji_flag==1 || biaoji_self_cast_shadow==1)
        {

        }
        if(single_pix_biaoji_flag==1)
        {
            int x, y;
            x = event->pos().x();
            y = event->pos().y();
            QScrollBar *mybar= this->horizontalScrollBar();
            my_h=(*mybar).value();
            mybar= this->verticalScrollBar();
            my_v=(*mybar).value();
            double alpha=scaleFactor/100.0;
            int temp=y;
            y=(uint)((my_h+x)/alpha);
            x=(uint)((my_v+temp)/alpha);
            final_cvimage.at<uchar>(x,y)=255;
            emit biaoji_LeftButton_press("null");
            index_cancel_i_j[biaoji_cishu][0]=x;
            index_cancel_i_j[biaoji_cishu][1]=y;
            biaoji_cishu++;
        }

    }
    QGraphicsView::mouseMoveEvent(event);

}

void MyQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {

        if(fangkuang_falg==1)
        {
            leftmouse = true;
            lineStartPoint = event->pos();
            isDrawing = true;
            qDebug("1");

        }

        if(biaoji_flag==1 || biaoji_self_cast_shadow==1)
        {

            //QMessageBox::information(NULL,"提示",str,QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
            //获取坐标之后，根据坐标找到，该区域的编号
            int x, y;
            x = event->pos().x();
            y = event->pos().y();
            qDebug("1(x:%dy:%d)",x,y);
            QScrollBar *mybar= this->horizontalScrollBar();
            my_h=(*mybar).value();
            mybar= this->verticalScrollBar();
            my_v=(*mybar).value();
            qDebug("1(my_h:%fmy_v:%f)",my_h,my_v);
            //x=(my_h/h_max*(scaleFactor/100.0*image->height()-380)+x)/(scaleFactor/100.0);
            //y=(my_v/v_max*(scaleFactor/100.0*image->width()-380)+y)/(scaleFactor/100.0);
            double alpha=scaleFactor/100.0;
            int temp=y;
            y=(uint)((my_h+x)/alpha);
            x=(uint)((my_v+temp)/alpha);
            qDebug("scaleFactor:%f",alpha);
            qDebug("2(x:%dy:%d)",x,y);
            for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
                for (int j = 0; j < num; j++)
                {
                    if(pUnRegion[x][y]==pUnRegion[i][j])
                    {
                       final_cvimage.at<uchar>(i,j)=255;

                    }
                }
            QString str = "("+QString :: number(y) +", "+QString::number(x)+")";
            emit biaoji_LeftButton_press(str);
            index_cancel_i_j[biaoji_cishu][0]=x;
            index_cancel_i_j[biaoji_cishu][1]=y;
            biaoji_cishu++;

        }
        if(single_pix_biaoji_flag==1)
        {
            int x, y;
            x = event->pos().x();
            y = event->pos().y();
            qDebug("1(x:%dy:%d)",x,y);
            QScrollBar *mybar= this->horizontalScrollBar();
            my_h=(*mybar).value();
            mybar= this->verticalScrollBar();
            my_v=(*mybar).value();
            qDebug("1(my_h:%fmy_v:%f)",my_h,my_v);
            double alpha=scaleFactor/100.0;
            int temp=y;
            y=(uint)((my_h+x)/alpha);
            x=(uint)((my_v+temp)/alpha);
            index_cancel_i_j[biaoji_cishu][0]=x;
            index_cancel_i_j[biaoji_cishu][1]=y;
            biaoji_cishu++;
            final_cvimage.at<uchar>(x,y)=255;
            emit biaoji_LeftButton_press("null");
            leftmouse = true;

        }
    }
    QGraphicsView::mousePressEvent(event);

}

int MyQGraphicsView::my_index()
{
    for(int i=0;i < num*num;i++)
    {
        if(region_index_n[i]==0)
            break;
        for(int j=i;j<num*num;j++)
        {
            if(region_index_n[i]>region_index_n[j+1])
            {
                if(region_index_n[j+1]==0)
                    return i;
            }
            else
            {
                //max_index=j+1;
                break;
            }

        }
    }
    return 0;
}

void MyQGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {

        if(fangkuang_falg==1)
        {
            leftmouse = false;
            lineEndPoint = event->pos();
            isDrawing = false;
            //update();
            //this->viewport()->update();
            int x, y, w, h;
            x = lineStartPoint.x();
            y = lineStartPoint.y();
            w = lineEndPoint.x() - x;
            h = lineEndPoint.y() - y;

            QScrollBar *mybar= this->horizontalScrollBar();
            my_h=(*mybar).value();
            h_max=(*mybar).maximum();
            mybar= this->verticalScrollBar();
            my_v=(*mybar).value();
            v_max=(*mybar).maximum();

            x=(my_h+x)/(scaleFactor/100.0);
            y=(my_v+y)/(scaleFactor/100.0);
            w=w/(scaleFactor/100.0);
            h=h/(scaleFactor/100.0);

            /*
            scene->clear();
            tempPix=QPixmap::fromImage(image);
            QPainter pp(&tempPix);
            pp.setPen(QPen(Qt::blue,1,Qt::DashLine));
            pp.drawRect(x, y, w, h);
            scene->addPixmap(tempPix);
            //scene->addRect(x,y,w,h);
            this->setScene(scene);
            //this->show();
            */
            qDebug("x:%d",x);
            qDebug("y:%d",y);
            qDebug("w:%d",w);
            qDebug("h:%d",h);
            qDebug("3");



            Mat gray_dst;
            cvtColor(dst,gray_dst,CV_RGB2GRAY);//假彩图分割结果
            int region_index = 0;

            uint my_pUnRegion[num][num];

            for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
                for (int j = 0; j < num; j++)
                {
                    A[i][j] = float(gray_dst.at<uchar>(i,j));//

                    my_pUnRegion[i][j] = 0;
                    region_index_n[i*num+j] = 0;
                    region_index_sum[i * num + j] = 0;
                    pnGrowQueX[i * num + j] = 0;
                    pnGrowQueY[i * num + j] = 0;
                }

            for (int i = y; i < y+h; i++)    //首先找出方框中像素点最多的区域
                for (int j = x; j < x+w; j++)
                {
                    if (my_pUnRegion[i][j] == 0)
                    {

                        region_index = region_index + 1;
                        my_pUnRegion[i][j] = region_index;

                        region_index_n[region_index-1] = region_index_n[region_index-1] + 1;

                        region_index_sum[region_index-1] = region_index_sum[region_index-1] + A[i][j];//
                        int nStart = 0;
                        int nEnd = 0;

                        pnGrowQueX[nEnd] = i;
                        pnGrowQueY[nEnd] = j;

                        while (nStart <= nEnd)
                        {
                            int nCurrX = pnGrowQueX[nStart];
                            int nCurrY = pnGrowQueY[nStart];

                            for (int k = 0; k < 4; k++)//这儿分别对nCurrX，nCurrY点的附近四个点，进行与当前点进行像素值比较，若相等，则把此点归类到某一个区域中
                            {
                                int xx = nCurrX + nDx[k];
                                int yy = nCurrY + nDy[k];

                                if ((yy < x+w) && (yy >= x) && (xx < y+h) && (xx >= y) && (my_pUnRegion[xx][yy] == 0) && (abs(A[xx][yy] - A[nCurrX][nCurrY]) <= nThreshold))
                                {
                                    nEnd = nEnd + 1;

                                    pnGrowQueX[nEnd] = xx;//满足的当前点，则放入栈中待处理
                                    pnGrowQueY[nEnd] = yy;

                                    my_pUnRegion[xx][yy] = region_index;


                                    region_index_n[region_index-1] = region_index_n[region_index-1] + 1;

                                    region_index_sum[region_index-1] = region_index_sum[region_index-1] + A[i][j];//

                                }
                            }
                            nStart = nStart + 1;
                        }
                    }
                }

            for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
                for (int j = 0; j < num; j++)
                {
                   MS_reg.at<uchar>(i,j)=my_pUnRegion[i][j];//这儿确实my_pUnRegion得到选中区域的统计，下面就是要根据region_index_n算出里面的最大值。
                }

            max_index=my_index();
            //ui->poslabel->setText(QString :: number(max_index));
            //for(int i=0;i<10;i++)
            //    qDebug("region_index_n[:%d],%d",i,region_index_n[i]);

            for (int i = y; i < y+h; i++)    //首先找出方框中像素点最多的区域
                for (int j = x; j < x+w; j++)
                {
                    if((max_index+1)==my_pUnRegion[i][j])
                    {
                        index_i=i;
                        index_j=j;
                        break;
                    }
                }
            for (int i = y; i < y+h; i++)    //首先找出方框中像素点最多的区域
                for (int j = x; j < x+w; j++)
                {
                    dst.at<Vec3b>(i,j)[0]=dst.at<Vec3b>(index_i,index_j)[0];
                    dst.at<Vec3b>(i,j)[1]=dst.at<Vec3b>(index_i,index_j)[1];
                    dst.at<Vec3b>(i,j)[2]=dst.at<Vec3b>(index_i,index_j)[2];
                }
            //imwrite("D:\\HAHA2.bmp",dst);


//            QImage img;
            for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
                for (int j = 0; j < num; j++)
                {
                    //完成图像的叠加
                    Qt_img_rgb.at<Vec3b>(i,j)[0]=a*dst.at<Vec3b>(i,j)[0]+(1-a)*src.at<Vec3b>(i,j)[0];
                    Qt_img_rgb.at<Vec3b>(i,j)[1]=a*dst.at<Vec3b>(i,j)[1]+(1-a)*src.at<Vec3b>(i,j)[1];
                    Qt_img_rgb.at<Vec3b>(i,j)[2]=a*dst.at<Vec3b>(i,j)[2]+(1-a)*src.at<Vec3b>(i,j)[2];

                }
//            cvtColor(Qt_img_rgb,Qt_img_rgb,CV_BGR2RGB);
//            img = QImage((const unsigned char*)(Qt_img_rgb.data),Qt_img_rgb.cols,Qt_img_rgb.rows,Qt_img_rgb.cols*Qt_img_rgb.channels(),QImage::Format_RGB888);
//            label->setPixmap(QPixmap::fromImage(img).scaled(label->size()));
//           label->resize(label->pixmap()->size());//无则显示不全
            cvtColor(Qt_img_rgb,Qt_img_rgb,CV_BGR2RGB);
            image = QImage((const unsigned char*)(Qt_img_rgb.data),Qt_img_rgb.cols,Qt_img_rgb.rows,Qt_img_rgb.cols*Qt_img_rgb.channels(),QImage::Format_RGB888);
            scene->clear();
            tempPix=QPixmap::fromImage(image);
            scene->addPixmap(tempPix);
            //scene->addRect(x,y,w,h);
            this->setScene(scene);

            //完成对pUnRegion的更新
            cvtColor(dst,gray_dst,CV_RGB2GRAY);
            for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
                for (int j = 0; j < num; j++)
                {
                    A[i][j] = float(gray_dst.at<uchar>(i,j));//
                    pUnRegion[i][j] = 0;
                    region_index_n[i*num+j] = 0;
                    region_index_sum[i * num + j] = 0;
                    pnGrowQueX[i * num + j] = 0;
                    pnGrowQueY[i * num + j] = 0;
                }

            for (int i = 0; i < num; i++)    //首先找出方框中像素点最多的区域
                for (int j = 0; j < num; j++)
                {
                    if (pUnRegion[i][j] == 0)
                    {

                        region_index = region_index + 1;
                        pUnRegion[i][j] = region_index;

                        region_index_n[region_index-1] = region_index_n[region_index-1] + 1;

                        region_index_sum[region_index-1] = region_index_sum[region_index-1] + A[i][j];//
                        int nStart = 0;
                        int nEnd = 0;

                        pnGrowQueX[nEnd] = i;
                        pnGrowQueY[nEnd] = j;

                        while (nStart <= nEnd)
                        {
                            int nCurrX = pnGrowQueX[nStart];
                            int nCurrY = pnGrowQueY[nStart];

                            for (int k = 0; k < 4; k++)//这儿分别对nCurrX，nCurrY点的附近四个点，进行与当前点进行像素值比较，若相等，则把此点归类到某一个区域中
                            {
                                int xx = nCurrX + nDx[k];
                                int yy = nCurrY + nDy[k];

                                if ((yy < num) && (yy >= 0) && (xx < num) && (xx >= 0) && (pUnRegion[xx][yy] == 0) && (abs(A[xx][yy] - A[nCurrX][nCurrY]) <= nThreshold))
                                {
                                    nEnd = nEnd + 1;

                                    pnGrowQueX[nEnd] = xx;//满足的当前点，则放入栈中待处理
                                    pnGrowQueY[nEnd] = yy;

                                    pUnRegion[xx][yy] = region_index;


                                    region_index_n[region_index-1] = region_index_n[region_index-1] + 1;

                                    region_index_sum[region_index-1] = region_index_sum[region_index-1] + A[i][j];//

                                }
                            }
                            nStart = nStart + 1;
                        }
                    }
                }



            emit update_graphicsview_signal();

        }

        if(biaoji_flag==1 || biaoji_self_cast_shadow==1)
        {

        }
        if(single_pix_biaoji_flag==1)
        {
            leftmouse = false;
        }
    }
    QGraphicsView::mouseReleaseEvent(event);

}

/////////////////////////////////////////////////////////
