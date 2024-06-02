#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QAudioOutput>

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    QPushButton* getEasyButton() const;
    QPushButton* getMediumButton() const;
    QPushButton* getHardButton() const;
    QAudioOutput *audioOutput;


private:
    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *hardButton;
    QPushButton *quitButton;
    QPushButton *muteButton;
    QLabel *backgroundLabel;
    QLabel *transparentLayer;
    QMovie *movie;
    QMediaPlayer *player;
    void toggleSoundSlot();
    void quitGameSlot();

};



#endif // MAINMENU_H
