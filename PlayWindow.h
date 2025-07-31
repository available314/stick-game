#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>
#include <QTimer>
#include <QLabel>
#include <memory>

#include "GameType.h"
#include "iPlayer.h"
#include "iBotStrategy.h"
#include "iCheckMove.h"
#include "Game.h"

class PlayWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit PlayWindow(GameType type, int stickCount, int a, int b,
                        const QString& firstPlayer, const QString& firstPlayerName, const QString& secondPlayer, const QString& secondPlayerName,
                        QWidget *parent = nullptr);
    ~PlayWindow() override;
protected:
    void closeEvent(QCloseEvent* event) override;
private slots:
    void handleSubmit();
    void handleBotTurn();
    void handleUndo();
    void game_info_alert();

private:
    void updateUI();
    void checkGameEnd();

    GameType gameType;
    int stickCount{};
    int a{}, b{};

    std::shared_ptr<Game> game;

    QLabel* infoLabel;
    QPushButton* submitBtn;
    QPushButton* undoBtn;
    QPushButton* gameinfoBtn;
    QVector<QPushButton*> buttons;
    std::vector<int> selected;


    static std::shared_ptr<iPlayer> createPlayer(const QString& player, const QString& name, int stickCount, int a, int b);
    static std::unique_ptr<iCheckMove> createChecker(GameType type);
};

#endif // PLAYWINDOW_H
