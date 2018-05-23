#ifndef SLIDINGWINDOW_H
#define SLIDINGWINDOW_H

#include <QWidget>
#include<QSplitter>
#include<QPushButton>
#include<QFrame>
class SlidingWindow : public QWidget
{
    Q_OBJECT
public:
    SlidingWindow(QWidget *parent = nullptr);
    ~SlidingWindow();
protected:
    void mousePressEvent (QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void setBtnPos();
    void setBtnIcon();

private slots:
    void slotClickBtn();
    void slotSplitterMoved(int pos,int index);
signals:

public slots:

private:
    QPoint dragPosition;
    bool bPressFlag;
    QSplitter *splitter;
    QFrame *contentFrame;
    QFrame *listFrame;
    QPushButton *pushButton;
    QIcon leftIcon;
    QIcon rightIcon;

};

#endif // SLIDINGWINDOW_H
