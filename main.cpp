//#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QTimer>
#include <QAudioOutput>
#include <QMediaPlayer>

class ImageButton: public  QPushButton
{
    Q_OBJECT
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
    QMediaPlayer *mClickSound;
    QAudioOutput *audio;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    bool isDown = false;
};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent);
    setToolTip("STOP");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap(":/new/prefix1/btnUp.png");
    mButtonDownPixmap = QPixmap(":/new/prefix1/btnDn.png");
    mCurrentButtonPixmap = mButtonUpPixmap;

    mClickSound = new QMediaPlayer;
    audio = new QAudioOutput;
    mClickSound->setParent(this);
    audio->setVolume(50);
    mClickSound->setAudioOutput(audio);
    mClickSound->setSource(QUrl::fromLocalFile("E:/Code/QTCreator/Task38_3Button/04716.mp3"));

    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
}

void ImageButton::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const {
    return QSize(150,215);
}

QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown(); 
}

void ImageButton::setDown() {
    mClickSound->play();
    mCurrentButtonPixmap = mButtonDownPixmap;
    isDown = true;

    update();
    QTimer::singleShot(100, this, &ImageButton::setUp);
}

void ImageButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    isDown = false;
    update();
}

int main(int argc,char** argv) {
    QApplication app(argc, argv);


    ImageButton redButton(nullptr);
    redButton.setFixedSize(150,215);
    redButton.move(1000,400);

    QObject::connect(&redButton, &QPushButton::clicked, [](){
        qDebug() << "clicked";
    });

    redButton.show();
    app.exec();
    return 0;
}

#include "include/main.moc"

