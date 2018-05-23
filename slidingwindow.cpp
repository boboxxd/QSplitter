#include "slidingwindow.h"
#include <QMouseEvent>
#include <QList>
#include <QRect>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
SlidingWindow::SlidingWindow(QWidget *parent)
    : QWidget(parent)
    ,bPressFlag(false)
{
    resize(660,460);
    splitter = new QSplitter(Qt::Horizontal,this);
    splitter->setHandleWidth(1);
    splitter->setStyleSheet("QSplitter::handle{background:rgb(100,100,100,255)}");
    contentFrame = new QFrame(splitter);
    contentFrame->setStyleSheet("background:#000000");
    contentFrame->resize(475, height());
    contentFrame->setMinimumWidth(405);
    listFrame = new QFrame(splitter);
    listFrame->setStyleSheet("background:#323232");
    listFrame->resize(660 - 475, height());
    listFrame->setMaximumWidth(660 - 405);


    connect(splitter,&QSplitter::splitterMoved,this,&SlidingWindow::slotSplitterMoved);
    leftIcon = QIcon(":/leftbtn.png");
    rightIcon = QIcon(":/leftbtn.png");
    pushButton = new QPushButton(this);
    pushButton->setFocusPolicy(Qt::NoFocus);
    pushButton->hide();
    pushButton->setFixedSize(13, 100);
    pushButton->setIconSize(pushButton->size());
    pushButton->setStyleSheet("border:none;");
    pushButton->setIcon(rightIcon);
    pushButton->move(contentFrame->width() - pushButton->width()-2, (contentFrame->height() - pushButton->height())/2);
    connect(pushButton,&QPushButton::clicked,this,&SlidingWindow::slotClickBtn);

    contentFrame->setMouseTracking(true);
    listFrame->setMouseTracking(true);
    contentFrame->installEventFilter(this);
    listFrame->installEventFilter(this);
}

SlidingWindow::~SlidingWindow()
{

}

void SlidingWindow::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    dragPosition = event->pos();
    QWidget::mousePressEvent(event);
}

void SlidingWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
            QPoint relaPos(QCursor::pos() - dragPosition);
            move(relaPos);
        }
        QWidget::mouseMoveEvent(event);
}

void SlidingWindow::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void SlidingWindow::resizeEvent(QResizeEvent *event)
{
    splitter->setGeometry(0, 0, width(), height());
    QWidget::resizeEvent(event);
}

bool SlidingWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseMove){
        QMouseEvent *mouseMove = static_cast<QMouseEvent*>(event);
        if(qAbs(mouseMove->pos().x()-contentFrame->width())<=10)
        {
            pushButton->show();
        }else
        {
            pushButton->hide();
        }
    }
    return QWidget::eventFilter(obj,event);
}

void SlidingWindow::setBtnPos()
{
    pushButton->move(contentFrame->width()-pushButton->width(),(contentFrame->height()-pushButton->height())/2);
}

void SlidingWindow::setBtnIcon()
{
    if(listFrame->width()!=0){
        pushButton->setIcon(rightIcon);
    }else
    {
       pushButton->setIcon(leftIcon);
    }
}

void SlidingWindow::slotClickBtn()
{
    QList<int> sizeList;
    sizeList.clear();
    if(listFrame->width() != 0){
        sizeList.append(660);
        sizeList.append(0);
    }else
    {
        sizeList.append(475);
        sizeList.append(660 - 475);
    }
    splitter->setSizes(sizeList);
    setBtnIcon();
    setBtnPos();
    pushButton->hide();
}

void SlidingWindow::slotSplitterMoved(int pos, int index)
{
    Q_UNUSED(pos);
    Q_UNUSED(index);
    setBtnIcon();
    setBtnPos();
}
