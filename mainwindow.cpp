#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setGeometry(30,30,1300,650);
    graphicsview=new MyQGraphicsView(this);
    graphicsview->setGeometry(440,40,400,400);
//    graphicsview->sizeAdjustPolicy();
//    graphicsview->AdjustToContents;
//    graphicsview->horizontalScrollBar();
    graphicsview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    graphicsview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    graphicsview->SizeAdjustPolicy()=QGraphicsView::AdjustToContentsOnFirstShow;
//    graphicsview->setSizeAdjustPolicy(QGraphicsView::AdjustToContents);
//    graphicsview->setDragMode(QGraphicsView::RubberBandDrag);//实现左右键能够画框框
//    graphicsview->setDragMode(QGraphicsView::ScrollHandDrag);//当鼠标进入控件内，变成手的形状，左键按下不松，可以实现对图片的拖动，右键无反应

    Btn_readimage = new QPushButton("读取图像",this);//Btn_readimage = new QPushButton();就是按钮不会显示
    Btn_readimage->setGeometry(150,475,75,25);


    connect(Btn_readimage,SIGNAL(clicked()),this,SLOT(Btn_readimage_clicked()));
//    connect(this,SIGNAL(mouseWheelZoom(bool)),SLOT(Zoom(bool)));
//    connect(this,SIGNAL(MyQGraphicsView::mouseWheelZoom(bool)),this,SLOT(Zoom(bool)));
    connect(graphicsview,SIGNAL(test_signal()),this,SLOT(Btn_readimage_clicked()));
    connect(graphicsview,SIGNAL(update_Final_Result_Label_signal(bool)),this,SLOT(update_Final_Result_Label(bool)));
    connect(graphicsview,SIGNAL(update_graphicsview_signal()),this,SLOT(update_graphicsview()));
//    graphicsview->installEventFilter(this);
    labelimage=new QLabel(NULL,this);
    labelimage->setFrameShape(QFrame::Panel);
    labelimage->setGeometry(20,40,400,400);//x,y,w,h

    Final_Result_Label=new QLabel(NULL,this);
    Final_Result_Label->setFrameShape(QFrame::Panel);
    Final_Result_Label->setGeometry(860,40,400,400);//x,y,w,h


    pushButton_2 = new QPushButton(QWidget::tr("图像分割"), this);
    pushButton_2->setGeometry(150,505,75,25);
    pushButton_3 = new QPushButton(QWidget::tr("保存"), this);
    pushButton_3->setGeometry(150,535,75,25);
    pushButton_4 = new QPushButton(QWidget::tr("叠加GT"), this);
    pushButton_4->setGeometry(150,565,75,25);
    next_picture_pushButton = new QPushButton(QWidget::tr("下一张图"), this);
    next_picture_pushButton->setGeometry(150,595,75,25);

    label1_1 = new QLabel(QWidget::tr("超像素最大金字塔"), this);\
    label1_1->setGeometry(350,475,100,20);
    label1_2 = new QLabel(QWidget::tr("超像素的空间范围"), this);
    label1_2->setGeometry(350,505,100,20);
    label1_3 = new QLabel(QWidget::tr("超像素的颜色范围"), this);
    label1_3->setGeometry(350,535,100,20);
    label1_4 = new QLabel(QWidget::tr("填充颜色设置"), this);
    label1_4->setGeometry(350,565,100,20);
    label1_5 = new QLabel(QWidget::tr("叠加系数"), this);
    label1_5->setGeometry(350,595,100,20);

    ColorEdit1_1 = new QLineEdit(QWidget::tr("3"), this);\
    ColorEdit1_1->setGeometry(470,475,100,20);
    ColorEdit1_2 = new QLineEdit(QWidget::tr("30"), this);
    ColorEdit1_2->setGeometry(470,505,100,20);
    ColorEdit1_3 = new QLineEdit(QWidget::tr("20"), this);
    ColorEdit1_3->setGeometry(470,535,100,20);
    ColorEdit1_4 = new QLineEdit(QWidget::tr("2"), this);
    ColorEdit1_4->setGeometry(470,565,100,20);
    ColorEdit1_5 = new QLineEdit(QWidget::tr("0.3"), this);
    ColorEdit1_5->setGeometry(470,595,100,20);

    poslabel=new QLabel(QWidget::tr("开始：读取图像"),this);
    poslabel->setGeometry(760,475,200,20);

    label2_1 = new QLabel(QWidget::tr("图片总数"), this);
    label2_1->setGeometry(670,505,55,20);\
    label2_2 = new QLabel(QWidget::tr("已标注："), this);
    label2_2->setGeometry(670,535,55,20);
    label2_3 = new QLabel(QWidget::tr("未标注："), this);
    label2_3->setGeometry(670,565,55,20);

    lineEdit = new QLineEdit(NULL, this);
    lineEdit->setGeometry(750,505,100,20);\
    lineEdit_2 = new QLineEdit(NULL, this);
    lineEdit_2->setGeometry(750,535,100,20);
    lineEdit_3 = new QLineEdit(NULL, this);
    lineEdit_3->setGeometry(750,565,100,20);

    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(pushButton_2_clicked()));
    connect(pushButton_3,SIGNAL(clicked()),this,SLOT(pushButton_3_clicked()));
    connect(pushButton_4,SIGNAL(clicked()),this,SLOT(pushButton_4_clicked()));
    connect(next_picture_pushButton,SIGNAL(clicked()),this,SLOT(next_picture_pushButton_clicked()));
    connect(ColorEdit1_1,SIGNAL(textChanged(const QString)),this,SLOT(ColorEdit_textEdited(const QString)));
    connect(ColorEdit1_2,SIGNAL(textChanged(const QString)),this,SLOT(ColorEdit_2_textChanged(const QString)));
    connect(ColorEdit1_3,SIGNAL(textChanged(const QString)),this,SLOT(ColorEdit_3_textChanged(const QString)));
    connect(ColorEdit1_4,SIGNAL(textChanged(const QString)),this,SLOT(ColorEdit_4_textChanged(const QString)));
    connect(ColorEdit1_5,SIGNAL(textChanged(const QString)),this,SLOT(ColorEdit_5_textChanged(const QString)));

    connect(graphicsview,SIGNAL(biaoji_LeftButton_press(QString)),this,SLOT(mainwindow_biaoji_LeftButton_press(QString)));

    flag=false;
    first_pic_seg_flag=false;
    qDebug("MainWindow_wancheng");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Btn_readimage_clicked()
{
    /*
    Btn_readimage= new QPushButton();
    fileName = QFileDialog::getOpenFileName(
                    this, "open image file",
                    ".",
                    "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    if(fileName != "")//当获取之后判别filename是否为空是有必要的
    {
        if(graphicsview->image->load(fileName))
        {
            graphicsview->scene = new QGraphicsScene;
            graphicsview->scene->addPixmap(QPixmap::fromImage(*graphicsview->image));
            //graphicsview->image->load("D:/Images/001.jpg");
            //TEMP_IMG=QPixmap::fromImage(*graphicsview->image);
            //graphicsview->scene->clear();
            //graphicsview->scene->addPixmap(TEMP_IMG);
            graphicsview->scene->addRect(10,10,20,20);
            graphicsview->setScene(graphicsview->scene);
            graphicsview->scene->clear();
            graphicsview->scene->addPixmap(QPixmap::fromImage(*graphicsview->image));
            //graphicsview->resize(image->width()+10, image->height()+10);//graphicsview->resize(image->width() + 10, image->height() + 10);
            //graphicsview->scale(-1.0,-1.0);
            graphicsview->show();
        }
    }
*/
    graphicsview->filename = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.png *.xpm *.jpg *.bmp)");
    if(graphicsview->filename.isEmpty())
    {
        QMessageBox::information(this,
                    tr("提示"),
                    tr("请选中图片!"));
        return;
    }
    graphicsview->DangQianZhangShu=0;
    graphicsview->state_mode_flag=0;
    int first = graphicsview->filename[graphicsview->DangQianZhangShu].lastIndexOf ("/");
//    QTextCodec *code = QTextCodec::codecForName("gb18030");
    QString just_name=graphicsview->filename[graphicsview->DangQianZhangShu].right(graphicsview->filename[graphicsview->DangQianZhangShu].length ()-first-1);
    graphicsview->path=graphicsview->filename[graphicsview->DangQianZhangShu].left(first);
    graphicsview->picturename = just_name.left(just_name.length()-4);

    QImage edgeImage;
    edgeImage.load(graphicsview->path+"/edge/"+graphicsview->picturename+".bmp");
    labelimage->setPixmap(QPixmap::fromImage(edgeImage).scaled(labelimage->size()));
    poslabel->setText("下一步：点击图像分割");
    first_pic_seg_flag=true;

    //更新
    lineEdit->setText(QString :: number(graphicsview->filename.length()));
    lineEdit_2->setText(QString :: number(0));
    lineEdit_3->setText(QString :: number(graphicsview->filename.length()));

}

//This colors the segmentations
void floodFillPostprocess(Mat& img, const Scalar& colorDiff = Scalar::all(1))
{
    CV_Assert(!img.empty());
    RNG rng = theRNG();
    Mat mask(img.rows + 2, img.cols + 2, CV_8UC1, Scalar::all(0));
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            if (mask.at<uchar>(y + 1, x + 1) == 0)
            {
                Scalar newVal(rng(256), rng(256), rng(256));
                cv::floodFill(img, mask, Point(x, y), newVal, 0, colorDiff, colorDiff);
            }
        }
    }
}

void MainWindow::pushButton_2_clicked()//图像分割按钮
{
    if(graphicsview->filename.isEmpty())
    {
        QMessageBox::information(this,
                    tr("提示"),
                    tr("请选中图片!"));
        return;
    }
    qDebug("fengge");
    Mat Qt_img_rgb(num,num, CV_8UC3, Scalar::all(0)),dst_copy;
    //QImage img;
    QTextCodec *code = QTextCodec::codecForName("gb18030");
    std::string name = code->fromUnicode(graphicsview->filename[graphicsview->DangQianZhangShu]).data();
    graphicsview->src = imread(name);
    cv::pyrMeanShiftFiltering(graphicsview->src, graphicsview->dst, graphicsview->spatialRad, graphicsview->colorRad, graphicsview->maxPryLevel);
    cvtColor(graphicsview->src, dst_copy, CV_RGB2GRAY);
    floodFillPostprocess(graphicsview->dst, Scalar::all(graphicsview->set_color_value));
    Mat dst_gray;
    cvtColor(graphicsview->dst, dst_gray, CV_RGB2GRAY);

    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
        for (int j = 0; j < num; j++)
        {
            graphicsview->A[i][j] = float(dst_gray.at<uchar>(i,j));//dst_copy分割以漫水填充后的假彩图分割，但是区域的像素是要用，meanshift的分割后的灰度图。
            graphicsview->A_3[0][i][j] = float(graphicsview->dst.at<Vec3b>(i,j)[0]);
            graphicsview->A_3[1][i][j] = float(graphicsview->dst.at<Vec3b>(i,j)[1]);
            graphicsview->A_3[2][i][j] = float(graphicsview->dst.at<Vec3b>(i,j)[2]);
            graphicsview->pUnRegion[i][j] = 0;
            graphicsview->region_index_n[i*num+j] = 0;
            graphicsview->region_index_sum[i * num + j] = 0;
            graphicsview->region_index_sum_jiacaitu[0][i * num + j] = 0;
            graphicsview->region_index_sum_jiacaitu[1][i * num + j] = 0;
            graphicsview->region_index_sum_jiacaitu[2][i * num + j] = 0;
            graphicsview->pnGrowQueX[i * num + j] = 0;
            graphicsview->pnGrowQueY[i * num + j] = 0;
            graphicsview->dst.at<Vec3b>(i,j)[0]=0;//newVal[0];
            graphicsview->dst.at<Vec3b>(i,j)[1]=0;//newVal[1];
            graphicsview->dst.at<Vec3b>(i,j)[2]=0;//newVal[2];
        }
//dst是meanshift分割后的伪彩色图像，dst_gray是灰度图像，下面一大段代码，主要是为每个相同颜色的区域进行从0开始标注序号，得到pUnRegion[256][256]和region_index_n
    RNG rng = theRNG();
    for (int i = 0; i < dst_gray.rows; i++)    //这儿是对分割后伪彩色图进行
        for (int j = 0; j < dst_gray.cols; j++)
            if (graphicsview->pUnRegion[i][j] == 0)
            {

                Scalar newVal(rng(256), rng(256), rng(256));

                graphicsview->region_index = graphicsview->region_index + 1;
                graphicsview->pUnRegion[i][j] = graphicsview->region_index;
                graphicsview->dst.at<Vec3b>(i,j)[0]=newVal[0];
                graphicsview->dst.at<Vec3b>(i,j)[1]=newVal[1];
                graphicsview->dst.at<Vec3b>(i,j)[2]=newVal[2];
                graphicsview->region_index_n[graphicsview->region_index-1] = graphicsview->region_index_n[graphicsview->region_index-1] + 1;

                graphicsview->region_index_sum[graphicsview->region_index-1] = graphicsview->region_index_sum[graphicsview->region_index-1] + dst_copy.at<uchar>(i,j);//A[i][j];//
                graphicsview->region_index_sum_jiacaitu[0][graphicsview->region_index-1] = graphicsview->region_index_sum_jiacaitu[0][graphicsview->region_index-1] + graphicsview->A_3[0][i][j];//
                graphicsview->region_index_sum_jiacaitu[1][graphicsview->region_index-1] = graphicsview->region_index_sum_jiacaitu[1][graphicsview->region_index-1] + graphicsview->A_3[1][i][j];
                graphicsview->region_index_sum_jiacaitu[2][graphicsview->region_index-1] = graphicsview->region_index_sum_jiacaitu[2][graphicsview->region_index-1] + graphicsview->A_3[0][i][j];
                int nStart = 0;
                int nEnd = 0;

                graphicsview->pnGrowQueX[nEnd] = i;
                graphicsview->pnGrowQueY[nEnd] = j;

                while (nStart <= nEnd)
                {
                    int nCurrX = graphicsview->pnGrowQueX[nStart];
                    int nCurrY = graphicsview->pnGrowQueY[nStart];

                    for (int k = 0; k < 4; k++)//这儿分别对nCurrX，nCurrY点的附近四个点，进行与当前点进行像素值比较，若相等，则把此点归类到某一个区域中
                    {
                        int xx = nCurrX + graphicsview->nDx[k];
                        int yy = nCurrY + graphicsview->nDy[k];

                        if ((yy < dst_gray.cols) && (yy >= 0) && (xx < dst_gray.rows) && (xx >= 0) && (graphicsview->pUnRegion[xx][yy] == 0) && (abs(graphicsview->A[xx][yy] - graphicsview->A[nCurrX][nCurrY]) <= graphicsview->nThreshold))
                        {
                            nEnd = nEnd + 1;

                            graphicsview->pnGrowQueX[nEnd] = xx;//满足的当前点，则放入栈中待处理
                            graphicsview->pnGrowQueY[nEnd] = yy;

                            graphicsview->pUnRegion[xx][yy] = graphicsview->region_index;
                            graphicsview->dst.at<Vec3b>(xx,yy)[0]=newVal[0];
                            graphicsview->dst.at<Vec3b>(xx,yy)[1]=newVal[1];
                            graphicsview->dst.at<Vec3b>(xx,yy)[2]=newVal[2];

                            graphicsview->region_index_n[graphicsview->region_index-1] = graphicsview->region_index_n[graphicsview->region_index-1] + 1;

                            graphicsview->region_index_sum[graphicsview->region_index-1] = graphicsview->region_index_sum[graphicsview->region_index-1] + dst_copy.at<uchar>(i,j);//+ A[i][j];//
                            graphicsview->region_index_sum_jiacaitu[0][graphicsview->region_index-1] = graphicsview->region_index_sum_jiacaitu[0][graphicsview->region_index-1] + graphicsview->A_3[0][i][j];//
                            graphicsview->region_index_sum_jiacaitu[1][graphicsview->region_index-1] = graphicsview->region_index_sum_jiacaitu[1][graphicsview->region_index-1] + graphicsview->A_3[1][i][j];
                            graphicsview->region_index_sum_jiacaitu[2][graphicsview->region_index-1] = graphicsview->region_index_sum_jiacaitu[2][graphicsview->region_index-1] + graphicsview->A_3[0][i][j];

                        }
                    }
                    nStart = nStart + 1;
                }
            }

//上面一段代码得到pUnRegion、region_index_sum和region_index_n后，便可以计算得到原来的真彩色图。
    for (int i = 0; i < graphicsview->dst.rows; i++)    //opencv图像等矩阵也是基于0索引的
        for (int j = 0; j < graphicsview->dst.cols; j++)
        {
            int temp = graphicsview->pUnRegion[i][j];
            graphicsview->MS_reg.at<uchar>(i, j) = uchar(round(graphicsview->region_index_sum[temp-1] / (float)graphicsview->region_index_n[temp-1]));
            graphicsview->A_3[0][i][j] = uchar(round(graphicsview->region_index_sum_jiacaitu[0][temp-1] / (float)graphicsview->region_index_sum_jiacaitu[0][temp-1]));
            graphicsview->A_3[1][i][j] = uchar(round(graphicsview->region_index_sum_jiacaitu[1][temp-1] / (float)graphicsview->region_index_sum_jiacaitu[1][temp-1]));
            graphicsview->A_3[2][i][j] = uchar(round(graphicsview->region_index_sum_jiacaitu[2][temp-1] / (float)graphicsview->region_index_sum_jiacaitu[2][temp-1]));

        }


    int Result[num*num],Sub[num*num];
    for (int i = 0; i < num*num; i++)    //opencv图像等矩阵也是基于0索引的
    {
        Result[i]=0;
        Sub[i]=0;
    }


    int n8_Dx[8] = { -1,-1,0,1,1,1,0,-1 }, n8_Dy[8] = { 0,1,1,1,0,-1,-1,-1 };
    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的
        for (int j = 0; j < num; j++)
        {
            int nCurrX=i;
            int nCurrY=j;
//            if(pUnRegion[i][j])
                for (int k = 0; k < 8; k++)//这儿分别对nCurrX，nCurrY点的附近四个点，进行与当前点进行像素值比较，若相等，则把此点归类到某一个区域中
                {

                    int xx = nCurrX + n8_Dx[k];
                    int yy = nCurrY + n8_Dy[k];

                    if ((yy < dst_gray.cols) && (yy >= 0) && (xx < dst_gray.rows) && (xx >= 0) && (graphicsview->region_index_n[graphicsview->pUnRegion[nCurrX][nCurrY]-1]<9) && (graphicsview->region_index_n[graphicsview->pUnRegion[nCurrX][nCurrY]-1]<graphicsview->region_index_n[graphicsview->pUnRegion[xx][yy]-1]) && (abs((float)graphicsview->pUnRegion[xx][yy]-graphicsview->pUnRegion[nCurrX][nCurrY])>0))
                    {//1.当前点的个数要小于9 2.当前点的个数要小于附近点的个数 3.附近点与当前点不属于同一个区域 4.如果当前点的附近都是孤立的区域，则将此点附近的所有点都标记为一个区域
                        //Near_Region_index_n[pUnRegion[nCurrX][nCurrY]][pUnRegion[xx][yy]]=1;

                        if(Sub[graphicsview->pUnRegion[nCurrX][nCurrY]-1]==0)//初始化
                        {
                            Sub[graphicsview->pUnRegion[nCurrX][nCurrY]-1]=abs(graphicsview->MS_reg.at<uchar>(xx, yy)-graphicsview->MS_reg.at<uchar>(nCurrX, nCurrY));
                            Result[graphicsview->pUnRegion[nCurrX][nCurrY]-1]=graphicsview->pUnRegion[xx][yy];

                        }

                        if(Sub[graphicsview->pUnRegion[nCurrX][nCurrY]-1]>abs(graphicsview->MS_reg.at<uchar>(xx, yy)-graphicsview->MS_reg.at<uchar>(nCurrX, nCurrY)))//虽然附近的改点的像素值小于当前的
                        {
                            Sub[graphicsview->pUnRegion[nCurrX][nCurrY]-1]=abs(graphicsview->MS_reg.at<uchar>(xx, yy)-graphicsview->MS_reg.at<uchar>(nCurrX, nCurrY));
                            Result[graphicsview->pUnRegion[nCurrX][nCurrY]-1]=graphicsview->pUnRegion[xx][yy];
                        }

                    }
                    else if((yy < dst_gray.cols) && (yy >= 0) && (xx < dst_gray.rows) && (xx >= 0) && (graphicsview->region_index_n[graphicsview->pUnRegion[nCurrX][nCurrY]-1]==1) && (graphicsview->region_index_n[graphicsview->pUnRegion[xx][yy]-1]==1))
                    {
                        graphicsview->MS_reg.at<uchar>(xx,yy)=0;
                        graphicsview->MS_reg.at<uchar>(nCurrX,nCurrY)=0;

                    }
                }
        }
    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的
        for (int j = 0; j < num; j++)
        {
            if(Result[graphicsview->pUnRegion[i][j]-1]!=0)//如果不是0，则代表改点的像素值是某区域的像素值，某区域通过Result索引得到；如果是0，则代表改点的像素值不需要改变。
            {
                int temp = Result[graphicsview->pUnRegion[i][j]-1];
                graphicsview->MS_reg.at<uchar>(i,j)=uchar(round(graphicsview->region_index_sum[temp-1] / (float)graphicsview->region_index_n[temp-1]));
                //MS_reg.at<uchar>(i,j)=temp;
            }

        }
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
        {
            graphicsview->A[i][j] = float(graphicsview->MS_reg.at<uchar>(i,j));
            graphicsview->pUnRegion[i][j] = 0;
            graphicsview->region_index_n[i*num+j] = 0;
            graphicsview->region_index_sum[i * num + j] = 0;
            graphicsview->pnGrowQueX[i * num + j] = 0;
            graphicsview->pnGrowQueY[i * num + j] = 0;
        }
    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的
        for (int j = 0; j < num; j++)
            if (graphicsview->pUnRegion[i][j] == 0)
            {

                Scalar newVal(rng(256), rng(256), rng(256));

                graphicsview->region_index = graphicsview->region_index + 1;
                graphicsview->pUnRegion[i][j] = graphicsview->region_index;
                graphicsview->dst.at<Vec3b>(i,j)[0]=newVal[0];
                graphicsview->dst.at<Vec3b>(i,j)[1]=newVal[1];
                graphicsview->dst.at<Vec3b>(i,j)[2]=newVal[2];
                graphicsview->region_index_n[graphicsview->region_index-1] = graphicsview->region_index_n[graphicsview->region_index-1] + 1;

                graphicsview->region_index_sum[graphicsview->region_index-1] = graphicsview->region_index_sum[graphicsview->region_index-1] + graphicsview->A[i][j];//

                int nStart = 0;
                int nEnd = 0;

                graphicsview->pnGrowQueX[nEnd] = i;
                graphicsview->pnGrowQueY[nEnd] = j;

                while (nStart <= nEnd)
                {
                    int nCurrX = graphicsview->pnGrowQueX[nStart];
                    int nCurrY = graphicsview->pnGrowQueY[nStart];

                    for (int k = 0; k < 4; k++)//这儿分别对nCurrX，nCurrY点的附近四个点，进行与当前点进行像素值比较，若相等，则把此点归类到某一个区域中
                    {
                        int xx = nCurrX + graphicsview->nDx[k];
                        int yy = nCurrY + graphicsview->nDy[k];

                        if ((yy < dst_gray.cols) && (yy >= 0) && (xx < dst_gray.rows) && (xx >= 0) && (graphicsview->pUnRegion[xx][yy] == 0) && (abs(graphicsview->A[xx][yy] - graphicsview->A[nCurrX][nCurrY]) <= graphicsview->nThreshold))
                        {
                            nEnd = nEnd + 1;

                            graphicsview->pnGrowQueX[nEnd] = xx;//满足的当前点，则放入栈中待处理
                            graphicsview->pnGrowQueY[nEnd] = yy;

                            graphicsview->pUnRegion[xx][yy] = graphicsview->region_index;
                            graphicsview->dst.at<Vec3b>(xx,yy)[0]=newVal[0];
                            graphicsview->dst.at<Vec3b>(xx,yy)[1]=newVal[1];
                            graphicsview->dst.at<Vec3b>(xx,yy)[2]=newVal[2];

                            graphicsview->region_index_n[graphicsview->region_index-1] = graphicsview->region_index_n[graphicsview->region_index-1] + 1;

                            graphicsview->region_index_sum[graphicsview->region_index-1] = graphicsview->region_index_sum[graphicsview->region_index-1] + graphicsview->A[i][j];//

                        }
                    }
                    nStart = nStart + 1;
                }
            }
    //imwrite("D:\\MS_reg_.bmp", dst);//


    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
        for (int j = 0; j < num; j++)
        {
//            graphicsview->final_cvimage.at<uchar>(i,j)=0;
            //完成图像的叠加
            Qt_img_rgb.at<Vec3b>(i,j)[0]=graphicsview->a*graphicsview->dst.at<Vec3b>(i,j)[0]+(1-graphicsview->a)*graphicsview->src.at<Vec3b>(i,j)[0];
            Qt_img_rgb.at<Vec3b>(i,j)[1]=graphicsview->a*graphicsview->dst.at<Vec3b>(i,j)[1]+(1-graphicsview->a)*graphicsview->src.at<Vec3b>(i,j)[1];
            Qt_img_rgb.at<Vec3b>(i,j)[2]=graphicsview->a*graphicsview->dst.at<Vec3b>(i,j)[2]+(1-graphicsview->a)*graphicsview->src.at<Vec3b>(i,j)[2];

        }

    cvtColor(Qt_img_rgb,Qt_img_rgb,CV_BGR2RGB);

    graphicsview->image = (QImage((const unsigned char*)(Qt_img_rgb.data),Qt_img_rgb.cols,Qt_img_rgb.rows,Qt_img_rgb.cols*Qt_img_rgb.channels(),QImage::Format_RGB888));
    graphicsview->image.save("D://temp.bmp");
    graphicsview->image.load("D://temp.bmp");
    graphicsview->scene = new QGraphicsScene;
    graphicsview->scene->clear();
    graphicsview->scene->addPixmap(QPixmap::fromImage(graphicsview->image));
    //graphicsview->resize(image->width()+10, image->height()+10);//graphicsview->resize(image->width() + 10, image->height() + 10);
    //graphicsview->scale(-1.0,-1.0);
    graphicsview->setScene(graphicsview->scene);
    graphicsview->show();
    graphicsview->scaleFactor = 200.0;
    QMatrix old_matrix;
    old_matrix = graphicsview->matrix();
    graphicsview->resetMatrix();
    graphicsview->translate(old_matrix.dx(), old_matrix.dy());
    graphicsview->scale(graphicsview->scaleFactor/100.0, graphicsview->scaleFactor/100.0);
    //label->setPixmap(QPixmap::fromImage(img).scaled(label->size()));
    //label->resize(label->pixmap()->size());//无则显示不全
    qDebug("fengge_finished");
    if(first_pic_seg_flag==true)
    {
        first_pic_seg_flag=false;
        poslabel->setText("下一步：右击选择标注阴影类型");
    }

}

void MainWindow::pushButton_4_clicked()//叠加GT按钮
{
    if(graphicsview->filename.isEmpty())
    {
        QMessageBox::information(this,
                    tr("提示"),
                    tr("请选中图片!"));
        return;
    }
    Mat gtImage;
    int first = graphicsview->filename[graphicsview->DangQianZhangShu].lastIndexOf ("/");
    QString just_name=graphicsview->filename[graphicsview->DangQianZhangShu].right(graphicsview->filename[graphicsview->DangQianZhangShu].length ()-first-1);
    graphicsview->path=graphicsview->filename[graphicsview->DangQianZhangShu].left(first);
    graphicsview->picturename = just_name.left(just_name.length()-4);

    QTextCodec *code = QTextCodec::codecForName("gb18030");
    QString temp=graphicsview->path+"/gt/"+graphicsview->picturename+".png";
    std::string name = code->fromUnicode(temp).data();

    Mat temp_img=imread(name);
    cvtColor(temp_img,gtImage,CV_RGB2GRAY);

    QImage myImage;
    myImage.load(temp);

    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
        {
            if(gtImage.at<uchar>(i,j)>0)
                graphicsview->final_cvimage.at<uchar>(i,j)=255;
        }

    myImage = QImage((const unsigned char*)(graphicsview->final_cvimage.data),
                         graphicsview->final_cvimage.cols,graphicsview->final_cvimage.rows,graphicsview->final_cvimage.cols*graphicsview->final_cvimage.channels(),
                         QImage::Format_Indexed8);
    Final_Result_Label->setPixmap(QPixmap::fromImage(myImage).scaled(Final_Result_Label->size()));

}

void MainWindow::pushButton_3_clicked()//保存
{
    if(graphicsview->filename.isEmpty())
    {
        QMessageBox::information(this,
                    tr("提示"),
                    tr("请选中图片!"));
        return;
    }
    int first = graphicsview->filename[graphicsview->DangQianZhangShu].lastIndexOf ("/");
    QTextCodec *code = QTextCodec::codecForName("gb18030");
    QString just_name=graphicsview->filename[graphicsview->DangQianZhangShu].right(graphicsview->filename[graphicsview->DangQianZhangShu].length ()-first-1);
    std::string name = code->fromUnicode(just_name.left(just_name.length()-4)).data();
    if(graphicsview->state_mode_flag==1)
    {

        if(imwrite("D:\\"+name+"_cast_shadow.bmp",graphicsview->final_cvimage))
            //poslabel->setText("cast_shadow_saved!");
            QMessageBox::information(this,
                        tr("提示"),
                        tr("cast_shadow_saved"));
        graphicsview->biaoji_cishu=0;
    }
    else if(graphicsview->state_mode_flag==2)
    {
        if(imwrite("D:\\"+name+"_self_cast_shadow.bmp",graphicsview->final_cvimage))
            //poslabel->setText("self_cast_shadow_saved!");
            QMessageBox::information(this,
                        tr("提示"),
                        tr("self_cast_shadow_saved"));
        graphicsview->biaoji_cishu=0;
    }

    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
        for (int j = 0; j < num; j++)
        {
            graphicsview->final_cvimage.at<uchar>(i,j)=0;

        }
    QImage myImage;
    myImage = QImage((const unsigned char*)(graphicsview->final_cvimage.data),
                         graphicsview->final_cvimage.cols,graphicsview->final_cvimage.rows,graphicsview->final_cvimage.cols*graphicsview->final_cvimage.channels(),
                         QImage::Format_Indexed8);
    Final_Result_Label->setPixmap(QPixmap::fromImage(myImage).scaled(Final_Result_Label->size()));

}

void MainWindow::next_picture_pushButton_clicked()//下一张按钮
{
    if(graphicsview->filename.isEmpty())
    {
        QMessageBox::information(this,
                    tr("提示"),
                    tr("请选中图片!"));
        return;
    }

    graphicsview->DangQianZhangShu++;

    if (graphicsview->DangQianZhangShu>=graphicsview->filename.length())
    {
        poslabel->setText("end!");
        lineEdit_3->setText("0");
        lineEdit_2->setText(QString :: number(graphicsview->filename.length()));
        graphicsview->DangQianZhangShu--;//为了防止到最后时，按下分割时读取filename超出边界
        return;
    }
    QImage myImage;
    int first = graphicsview->filename[graphicsview->DangQianZhangShu].lastIndexOf ("/");
    QString just_name=graphicsview->filename[graphicsview->DangQianZhangShu].right(graphicsview->filename[graphicsview->DangQianZhangShu].length ()-first-1);
    graphicsview->path=graphicsview->filename[graphicsview->DangQianZhangShu].left(first);
    graphicsview->picturename = just_name.left(just_name.length()-4);
    myImage.load(graphicsview->path+"/edge/"+graphicsview->picturename+".bmp");
    labelimage->setPixmap(QPixmap::fromImage(myImage).scaled(labelimage->size()));

    //final_cvimage.zeros(num,num,CV_8UC1);没有用

    for (int i = 0; i < num; i++)    //opencv图像等矩阵也是基于0索引的，这儿把meanshift分割后的灰度图赋值给A
        for (int j = 0; j < num; j++)
        {
            graphicsview->final_cvimage.at<uchar>(i,j)=0;
        }
    //更新
    lineEdit_2->setText(QString :: number(graphicsview->DangQianZhangShu));
    lineEdit_3->setText(QString :: number(graphicsview->filename.length()-graphicsview->DangQianZhangShu));


}
////////////////////////////////////////////////////////////////////////

void MainWindow::ColorEdit_textEdited(const QString &arg1)//颜色值改变
{
    //poslabel->setText(arg1);
    graphicsview->set_color_value=arg1.toInt();
}

void MainWindow::ColorEdit_2_textChanged(const QString &arg1)//颜色
{
    //poslabel->setText(arg1);
    graphicsview->colorRad=arg1.toInt();

}

void MainWindow::ColorEdit_3_textChanged(const QString &arg1)//空间
{
    //poslabel->setText(arg1);
    graphicsview->spatialRad=arg1.toInt();

}

void MainWindow::ColorEdit_4_textChanged(const QString &arg1)//金字塔
{
    //poslabel->setText(arg1);
    graphicsview->maxPryLevel=arg1.toInt();

}

void MainWindow::ColorEdit_5_textChanged(const QString &arg1)
{
    //poslabel->setText(arg1);
    graphicsview->a=arg1.toFloat();

}
////////////////////////////////////////////////////////////////////////
//来自于graphicsview对象的信号
void MainWindow::mainwindow_biaoji_LeftButton_press(QString str)
{
    QImage final_qtimage = QImage((const unsigned char*)(graphicsview->final_cvimage.data),
                         graphicsview->final_cvimage.cols,graphicsview->final_cvimage.rows,graphicsview->final_cvimage.cols*graphicsview->final_cvimage.channels(),
                         QImage::Format_Indexed8);
    //final_qtimage.load("D:\\temp.bmp");
    Final_Result_Label->setPixmap(QPixmap::fromImage(final_qtimage).scaled(Final_Result_Label->size()));
    Final_Result_Label->resize(Final_Result_Label->pixmap()->size());//无则显示不全

    //poslabel->setText(str+QString::number(final_qtimage.width()));

}

void MainWindow::update_Final_Result_Label(bool mode)
{
    /*
    QImage myImage;
    myImage = QImage((const unsigned char*)(graphicsview->final_cvimage.data),
                         graphicsview->final_cvimage.cols,graphicsview->final_cvimage.rows,graphicsview->final_cvimage.cols*graphicsview->final_cvimage.channels(),
                         QImage::Format_Indexed8);
    Final_Result_Label->setPixmap(QPixmap::fromImage(myImage).scaled(Final_Result_Label->size()));
    */
    if(mode)
        poslabel->setText("mode:cast_shadow");
    else
        poslabel->setText("mode:self_cast_shadow");
}

void MainWindow::update_graphicsview()
{

    //this->show();
}

////////////////////////////////////////////////////////////////////////
/*
void MainWindow::keyPressEvent(QKeyEvent * e)
{
    if(e->key()==Qt::Key_A && !e->isAutoRepeat())//
    {

//        flag=true;
        //poslabel->setText("down");
        qDebug("up");

    }
 //   QMainWindow::keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent * e)
{
    if(e->key()==Qt::Key_A) //&&
    {
        flag=false;
        //poslabel->setText("up");
        qDebug("down");

    }
 //   QMainWindow::keyPressEvent(e);
}
*/
/*
void MainWindow::wheelEvent(QWheelEvent * event)
{

    if (event->delta() > 0)
    {
        emit mouseWheelZoom(true);
//        mylabel->setText("up");
    }
    else
    {
        emit mouseWheelZoom(false);
//        mylabel->setText("down");
    }

}

void MainWindow::Zoom(bool zoom)
{
    if (zoom && scaleFactor >= 0)
    {

        scaleFactor += 10;
        QMatrix old_matrix;
        old_matrix = graphicsview->matrix();
        graphicsview->resetMatrix();
        graphicsview->translate(old_matrix.dx(), old_matrix.dy());
        graphicsview->scale(scaleFactor/100.0, scaleFactor/100.0);

    }
    else if (!zoom && scaleFactor >= 0)
    {
        scaleFactor -= 10;
        QMatrix old_matrix;
        old_matrix = graphicsview->matrix();
        graphicsview->resetMatrix();
        graphicsview->translate(old_matrix.dx(), old_matrix.dy());
        graphicsview->scale( scaleFactor/100.0,  scaleFactor/100.0);


    }

    else if (scaleFactor < 0){

        scaleFactor = 0.0;
    }

}
*/
/*
bool MainWindow::eventFilter(QObject *target, QEvent *e)
{

    if(target == graphicsview)
    {

        if(e->type() == QEvent::MouseButtonPress)
        {
            qDebug("haha");

             QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(e);
             if(mouseEvent->button()==Qt::LeftButton)//进入此函数代表选择区域合并并在label控件中左点击开始选区域
             {
                 //lastPoint = mouseEvent->pos();
                 //label->lineStartPoint = mouseEvent->pos();
                 qDebug("haha");
             }

        }
    }
    return QMainWindow::eventFilter(target, e);
}
*/
