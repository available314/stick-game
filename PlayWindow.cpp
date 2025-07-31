#include "PlayWindow.h"

#include <iostream>
#include <QMessageBox>

#include "bot.h"
#include "gamewindow.h"
#include "human.h"
#include "NormalModeMove.h"
#include "NormalModeStrategy.h"
#include "RowGraphStrategy.h"
#include "RowGrundyStrategy.h"
#include "RowMove.h"
#include "StandardMove.h"
#include "StandardStrategy.h"

PlayWindow::PlayWindow(GameType type, int stickCount, int a, int b,
                       const QString& firstPlayer, const QString& firstPlayerName, const QString& secondPlayer, const QString& secondPlayerName,
                    QWidget *parent) : QMainWindow(parent) {
    game = std::make_shared<Game>(stickCount, a, b, createPlayer(firstPlayer, firstPlayerName, stickCount, a, b), createPlayer(secondPlayer, secondPlayerName, stickCount, a, b));

    game->setMovesChecker(createChecker(type));

    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    infoLabel = new QLabel("", this);
    mainLayout->addWidget(infoLabel);

    QHBoxLayout* sticksLayout = new QHBoxLayout();
    for (int i = 0; i < stickCount; ++i) {
        QPushButton* btn = new QPushButton("|");
        btn->setCheckable(true);
        btn->setProperty("index", i);
        connect(btn, &QPushButton::clicked, this, [=]() {
            if (!btn->isEnabled()) return;
            int idx = btn->property("index").toInt();
            if (btn->isChecked()) {
                selected.push_back(idx);
                btn->setStyleSheet("background-color: #87CEFA; font-weight: bold; color: black;"); // blue
            } else {
                selected.erase(std::remove(selected.begin(), selected.end(), idx), selected.end());
                btn->setStyleSheet("background-color: #90EE90; font-weight: bold; color: black;"); // green
            }
        });
        buttons.push_back(btn);
        sticksLayout->addWidget(btn);
    }
    mainLayout->addLayout(sticksLayout);


    submitBtn = new QPushButton("Submit Move", this);
    connect(submitBtn, &QPushButton::clicked, this, &PlayWindow::handleSubmit);
   // mainLayout->addWidget(submitBtn);

    undoBtn = new QPushButton("Undo", this);
    connect(undoBtn, &QPushButton::clicked, this, &PlayWindow::handleUndo);
   // mainLayout->addWidget(undoBtn);

    gameinfoBtn = new QPushButton("Rules", this);
    connect(gameinfoBtn, &QPushButton::clicked, this, &PlayWindow::game_info_alert);

    QHBoxLayout* actionLayout = new QHBoxLayout();
    actionLayout->addWidget(undoBtn);
    actionLayout->addWidget(submitBtn);
    actionLayout->addWidget(gameinfoBtn);
    mainLayout->addLayout(actionLayout);





    setCentralWidget(central);
    game->Start();
    updateUI();
}

void PlayWindow::handleUndo() {
    if (game->undoStep()) {
        updateUI();
    } else {
        QMessageBox::information(this, "Undo", "Nothing to undo.");
    }
}

std::shared_ptr<iPlayer> PlayWindow::createPlayer(const QString& player, const QString& name, int stickCount, int a, int b) {
    if (player == "Human") {
        return std::make_shared<Human>(name.toStdString());
    }
    auto bot = std::make_shared<Bot>(name.toStdString());

    if (player == "Bot") {
        bot->setStrategy(std::make_unique<StandardStrategy>(stickCount, a, b));
    } else if (player == "GraphBot") {
        bot->setStrategy(std::make_unique<RowGraphStrategy>(stickCount, a, b));
    } else if (player == "GrundyBot") {
        bot->setStrategy(std::make_unique<RowGrundyStrategy>(stickCount, a, b));
    } else if (player == "NormalBot") {
        bot->setStrategy(std::make_unique<NormalModeStrategy>(stickCount));
    } else {
        throw std::runtime_error("Wrong player");
    }
    return bot;
}

std::unique_ptr<iCheckMove> PlayWindow::createChecker(GameType type) {
    if (type == GameType::Simple || type == GameType::Interval) {
        return std::make_unique<StandardMove>();
    }
    if (type == GameType::Sequential || type == GameType::SequentialInterval) {
        return std::make_unique<RowMove>();
    }
    if (type == GameType::NormalMode) {
        return std::make_unique<NormalModeMove>();
    }
    throw std::runtime_error("wrong game type!");
}

void PlayWindow::updateUI() {
    auto field = game->getField();
    for (int i = 0; i < buttons.size(); ++i) {
        QPushButton* btn = buttons[i];
        bool available = field[i];
        btn->setEnabled(available);
        btn->setChecked(false);

        if (available) {
            btn->setStyleSheet("background-color: #90EE90; font-weight: bold; color: black;"); // green
        } else {
            btn->setStyleSheet("background-color: #FF7F7F; font-weight: bold; color: black;"); // red
        }
    }
    selected.clear();

    infoLabel->setText(QString::fromStdString("Current turn: ") + QString::fromStdString(game->getCurrentPlayerName()));
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("font-size: 18px;");

    if (game->isCurrentPlayerBot()) {
        QTimer::singleShot(500, this, &PlayWindow::handleBotTurn);
        submitBtn->setEnabled(false);
        undoBtn->setEnabled(false);
    } else {
        submitBtn->setEnabled(true);
        undoBtn->setEnabled(true);
    }
}

void PlayWindow::handleBotTurn() {
    game->playTurn();
    game->nextTurn();
    checkGameEnd();
    updateUI();
}

void PlayWindow::checkGameEnd() {
    if (game->isEnd()) {
        QMessageBox::information(this, "Game Over", QString::fromStdString(game->loser()) + " looser!");
        close();
    }
}

void PlayWindow::handleSubmit() {
    if (game->setHumanTurn(selected)) {
        game->nextTurn();
        checkGameEnd();
        updateUI();
    } else {
        QMessageBox::warning(this, "Invalid Move", "This move is not valid. Try again.");
        updateUI();
    }
}

PlayWindow::~PlayWindow() {
    delete infoLabel;
    delete submitBtn;
    delete undoBtn;

    for (const auto i : buttons) {
        delete i;
    }
}

void PlayWindow::closeEvent(QCloseEvent *event) {
    if (parentWidget()) {
        parentWidget()->show();
    }
    QMainWindow::closeEvent(event);
}

void PlayWindow::game_info_alert() {
    QMessageBox::information(this, "Rules", QString::fromStdString(game->game_rule()));
}