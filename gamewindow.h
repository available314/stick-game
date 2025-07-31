#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QApplication>
#include <QLineEdit>

#include "GameType.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class GameWindow;
}
QT_END_NAMESPACE

class QComboBox;
class QPushButton;
class QSpinBox;
class QStackedWidget;
class QWidget;

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;

    QComboBox* gameTypeCombo;
    QStackedWidget* settingsStack;

    QComboBox* firstPlayerCombo;
    QComboBox* secondPlayerCombo;

    QSpinBox* stickCountSimple;
    QSpinBox* stickCountInterval;
    QSpinBox* aInterval;
    QSpinBox* bSimple;
    QSpinBox* bInterval;
    QSpinBox* stickCountNormalMode;

    QLineEdit* firstPlayerNameEdit;
    QLineEdit* secondPlayerNameEdit;

    QPushButton* startButton;


    QWidget* createSimpleSettings();
    QWidget* createIntervalSettings();
    QWidget* createSequentialSettings();
    QWidget* createSequentialIntervalSettings();
    QWidget* createNormalModeSettings();

    void updatePlayerOptions(GameType type);
    void startGame();
    void applyDarkTheme();
};

#endif // GAMEWINDOW_H
