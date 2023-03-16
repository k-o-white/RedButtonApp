#include <QApplication>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <iostream>


class ImageButton : public QPushButton
{
private:
    Q_OBJECT
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    QMediaPlayer buttonSound;
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setButtonStatus();
    void playClickSound();
};

ImageButton::ImageButton(QWidget *parent)
{
    setParent(parent);
    setToolTip("Нажми на кнопку, получишь результат.");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap("..\\RedButtonApp\\img\\button_up.png");
    mButtonDownPixmap = QPixmap("..\\RedButtonApp\\img\\button_down.png");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    buttonSound.setMedia(QUrl::fromLocalFile("..\\RedButtonApp\\click_sound.mp3"));
    connect(this, &QPushButton::clicked, this, &ImageButton::setButtonStatus);
    connect(this, &QPushButton::clicked, this, &ImageButton::playClickSound);
}

void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const
{
    return QSize(200, 200);
}

QSize ImageButton::minimumSizeHint() const
{
    return this->sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e)
{
     this->setButtonStatus();
}

void ImageButton::setButtonStatus()
{
    if (mCurrentButtonPixmap == mButtonUpPixmap)
        mCurrentButtonPixmap = mButtonDownPixmap;
    else
        mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

void ImageButton::playClickSound()
{
    buttonSound.setVolume(75);
    buttonSound.play();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ImageButton redButton(nullptr);
    redButton.setFixedSize(200, 200);
    redButton.move(850, 400);
    QObject::connect(&redButton, &QPushButton::clicked, []() {std::cout << "Clicked\n";});
    redButton.show();
    return app.exec();
}

#include "main.moc"
