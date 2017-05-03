#include "gamedialog.h"
#include "ui_gamedialog.h"

using namespace std;
using namespace cv;

GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);

    if(videoCap.open(0))
    {
        expressRecogniser = new ExpressionRecogniser("./data");
        resultDialog = new ResultDialog(this);
        model = new Model(expressRecogniser);

        timeLeft = 3;
        waitTime = timeLeft;
        gameTime = 120;
        gameStart=false;

        QObject::connect(&checkSimilarityTimer, SIGNAL(timeout()), this, SLOT(updateImage()));
        QObject::connect(&secondCountDownTimer,SIGNAL(timeout()),this,SLOT(secondCountDown()));

        //int frameHeight=videoCap.get(CV_CAP_PROP_FRAME_HEIGHT)/2;
        //int frameWidth=videoCap.get(CV_CAP_PROP_FRAME_WIDTH)/2;
        const int frameHeight = 240;
        const int frameWidth = 320;
        imageSize.setHeight(frameHeight);
        imageSize.setWidth(frameWidth);

        // update welcome image
        QPixmap imageAcceuil = QPixmap(":/interface/imagesInterface/tse.png");
        ui->modelLabel->setPixmap(imageAcceuil);
        ui->realLabel->setPixmap(imageAcceuil);

        secondCountDownTimer.start(1000);   // 1s
    }
    else
    {
        showMessage("Camera error");
        this->close();
    }

}

GameDialog::~GameDialog()
{
    delete ui;
}

void GameDialog::showMessage(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}


void GameDialog::drawLine(QPixmap * p, int i)
{
    QPainter painter(p);
    painter.setPen(Qt::red);

    std::vector<EmoPoint> points;
    if(i == 1)
    {
        points = expressRecogniser->getPartImg1FacePoints();
    }
    else
    {
        points = expressRecogniser->getPartImg2FacePoints();
    }

    if(points.size() == 0)
    {
        return;
    }
    else
    {
        const int linesNum = 34;
        const int from[34] = {0,2,3,4,5,6,1,7,8,9,10,11,12,14,15,16,13,17,18,19,20,22,23,25,29,26,28,30,31,32,29,33,34,35};
        const int to[34] = {2,3,4,5,6,1,7,8,9,10,11,0,14,15,16,13,17,18,19,12,22,23,24,29,28,21,30,31,32,29,33,34,35,28};

        for(unsigned int i = 0; i < linesNum; i++)
        {
            painter.drawLine(points.at(from[i]).getY(), points.at(from[i]).getX(), points.at(to[i]).getY(), points.at(to[i]).getX());
        }
    }
}

void GameDialog::updateImage()
{
    videoCap>>srcMat;

    if(srcMat.data)
    {
        // basic treatment
        cv::resize(srcMat,srcMat,Size(imageSize.width(),imageSize.height()),0,0,CV_INTER_LINEAR);
        flip(srcMat,srcMat,1);
        cvtColor(srcMat, srcMat, CV_BGR2RGB);

        // get images of different formats
        srcQImage = QImage((uchar*)(srcMat.data), srcMat.cols, srcMat.rows, QImage::Format_RGB888);
        srcQPixmap = QPixmap::fromImage(srcQImage);
        cvtColor(srcMat,srcMatGray,CV_RGB2GRAY);

        // game treatment
        double similarity = expressRecogniser->getSimilarity(srcMatGray);
        if(model->pass(similarity*100))
        {
            // update labels
            ui->realSimiLabel->setText(QString("Pass!"));
            ui->realNoteLabel->setText(QString("%1").arg(model->getScore()));

            // save result
            resultDialog->addImage(model->getCurrentQImage(),srcQImage);

            // change image
            model->changeImage();

            // update photo to simulate
            QPixmap pix = model->getCurrentQPixmap();
            ui->modelLabel->setPixmap(pix);
            ui->modelLabel->show();
        }
        else
        {
            ui->realSimiLabel->setText(QString("%1 %").arg(similarity*100,0,'f',1));
        }

        // show

        //QPixmap temp = model->getCurrentQPixmap();
        //drawLine(&temp, 1);
        //ui->modelLabel->setPixmap(temp);

        //drawLine(&srcQPixmap, 2);
        ui->realLabel->setPixmap(srcQPixmap);
    }
}


void GameDialog::secondCountDown()
{
    if(timeLeft==0&&!gameStart)
    {
        // update labels
        ui->realTimeLabel->setText("Start!!");

        // update image to simulate
        QPixmap pix = model->getCurrentQPixmap();
        ui->modelLabel->setPixmap(pix);
        ui->modelLabel->show();

        // setup check clock
        checkSimilarityTimer.start(1000 / 60);  // 60fps

        // other parameters
        gameStart = true;
        timeLeft = gameTime;
    }
    else if(timeLeft != waitTime&&!gameStart)
    {
        ui->realTimeLabel->setText(QString("%1s").arg(timeLeft));
    }
    else
    {
        ui->realTimeLabel->setText(QString("%1s").arg(timeLeft));
    }

    timeLeft -= 1;

    if(timeLeft == -1)
    {

        secondCountDownTimer.stop();
        checkSimilarityTimer.stop();
        resultDialog->exec();
        this->close();
    }

}

void GameDialog::on_changeButton_clicked()
{
    model->changeImage();
    QPixmap pix = model->getCurrentQPixmap();
    ui->modelLabel->setPixmap(pix);
    ui->modelLabel->show();
}

void GameDialog::on_quitButton_clicked()
{
    this->close();
}

