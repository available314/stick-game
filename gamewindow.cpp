#include "gamewindow.h"

#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QGroupBox>
#include <QApplication>
#include <QStyle>
#include "PlayWindow.h"
#include <QStyleFactory>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), ui(nullptr)
{

    applyDarkTheme();
    auto* central = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // DARK THEME STYLE
    /*QString darkStyle = R"(
        QWidget {
            background-color: #2d2d2d;
            color: #eeeeee;
            font-size: 13px;
        }
        QGroupBox {
            border: 1px solid #444;
            border-radius: 5px;
            margin-top: 10px;
        }
        QGroupBox:title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 3px 0 3px;
        }
        QLabel {
            color: #dddddd;
        }
        QComboBox, QSpinBox {
            background-color: #3a3a3a;
            border: 1px solid #555;
            border-radius: 3px;
            padding: 4px;
            color: #ffffff;
        }
        QComboBox QAbstractItemView {
            background-color: #2d2d2d;
            selection-background-color: #444;
            color: white;
        }
        QPushButton {
            background-color: #444;
            border: none;
            border-radius: 4px;
            padding: 8px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #555;
        }
        QLineEdit {
            background-color: #3a3a3a;
            border: 1px solid #555;
            border-radius: 3px;
            padding: 4px;
            color: #ffffff;
        }
    )";
    central->setStyleSheet(darkStyle);*/

    QFont labelFont;
    labelFont.setPointSize(10);
    labelFont.setBold(true);

    // Game settings group
    auto* gameSettingsGroup = new QGroupBox("Game Settings");
    auto* gameSettingsLayout = new QVBoxLayout(gameSettingsGroup);

    auto* gameTypeLabel = new QLabel("Select Game Type:");
    gameTypeLabel->setFont(labelFont);
    gameSettingsLayout->addWidget(gameTypeLabel);

    gameTypeCombo = new QComboBox(this);
    gameTypeCombo->addItem("Simple", QVariant::fromValue(GameType::Simple));
    gameTypeCombo->addItem("Interval", QVariant::fromValue(GameType::Interval));
    gameTypeCombo->addItem("Sequential", QVariant::fromValue(GameType::Sequential));
    gameTypeCombo->addItem("Sequential Interval", QVariant::fromValue(GameType::SequentialInterval));
    gameTypeCombo->addItem("Normal Mode", QVariant::fromValue(GameType::NormalMode));
    gameSettingsLayout->addWidget(gameTypeCombo);

    settingsStack = new QStackedWidget(this);
    settingsStack->addWidget(createSimpleSettings());
    settingsStack->addWidget(createIntervalSettings());
    settingsStack->addWidget(createNormalModeSettings());
    gameSettingsLayout->addWidget(settingsStack);

    mainLayout->addWidget(gameSettingsGroup);

    connect(gameTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, [=](int) {
            GameType type = static_cast<GameType>(gameTypeCombo->currentData().toInt());
            int stackIndex = 1;
            if (type == GameType::Simple || type == GameType::Sequential) {
                stackIndex = 0;
            } else if (type == GameType::NormalMode) {
                stackIndex = 2;
            }
            settingsStack->setCurrentIndex(stackIndex);
            updatePlayerOptions(type);
        });

    // Players group
    auto* playerGroup = new QGroupBox("Players");
    auto* playerGroupLayout = new QVBoxLayout(playerGroup);

    // --- First player ---
    auto* firstRow = new QHBoxLayout();
    auto* firstLeft = new QVBoxLayout();
    auto* firstRight = new QVBoxLayout();

    auto* firstLabel = new QLabel("First Player (first to move):");
    firstLabel->setFont(labelFont);
    firstLeft->addWidget(firstLabel);

    firstPlayerCombo = new QComboBox(this);
    firstLeft->addWidget(firstPlayerCombo);

    auto* firstNameLabel = new QLabel("Name:");
    firstNameLabel->setFont(labelFont);
    firstRight->addWidget(firstNameLabel);

    firstPlayerNameEdit = new QLineEdit(this);
    firstPlayerNameEdit->setPlaceholderText("Enter name...");
    firstRight->addWidget(firstPlayerNameEdit);

    firstRow->addLayout(firstLeft);
    firstRow->addSpacing(10);
    firstRow->addLayout(firstRight);
    playerGroupLayout->addLayout(firstRow);

    // --- Second player ---
    auto* secondRow = new QHBoxLayout();
    auto* secondLeft = new QVBoxLayout();
    auto* secondRight = new QVBoxLayout();

    auto* secondLabel = new QLabel("Second Player (second to move):");
    secondLabel->setFont(labelFont);
    secondLeft->addWidget(secondLabel);

    secondPlayerCombo = new QComboBox(this);
    secondLeft->addWidget(secondPlayerCombo);

    auto* secondNameLabel = new QLabel("Name:");
    secondNameLabel->setFont(labelFont);
    secondRight->addWidget(secondNameLabel);

    secondPlayerNameEdit = new QLineEdit(this);
    secondPlayerNameEdit->setPlaceholderText("Enter name...");
    secondRight->addWidget(secondPlayerNameEdit);

    secondRow->addLayout(secondLeft);
    secondRow->addSpacing(10);
    secondRow->addLayout(secondRight);
    playerGroupLayout->addLayout(secondRow);

    mainLayout->addWidget(playerGroup);

    // Start button
    startButton = new QPushButton("Start Game", this);
    startButton->setFixedHeight(40);
    mainLayout->addWidget(startButton, 0, Qt::AlignCenter);

    connect(startButton, &QPushButton::clicked, this, &GameWindow::startGame);

    setCentralWidget(central);
    updatePlayerOptions(GameType::Simple);
}

GameWindow::~GameWindow() = default;

QWidget* GameWindow::createSimpleSettings() {
    auto* w = new QWidget(this);
    auto* layout = new QVBoxLayout(w);

    layout->addWidget(new QLabel("Stick Count:"));
    stickCountSimple = new QSpinBox(this);
    stickCountSimple->setRange(1, 50);
    layout->addWidget(stickCountSimple);

    layout->addWidget(new QLabel("K (max sticks per turn):"));
    bSimple = new QSpinBox(this);
    bSimple->setRange(1, 50);
    layout->addWidget(bSimple);

    return w;
}

QWidget* GameWindow::createNormalModeSettings() {
    auto* w = new QWidget(this);
    auto* layout = new QVBoxLayout(w);

    layout->addWidget(new QLabel("Stick Count:"));
    stickCountNormalMode = new QSpinBox(this);
    stickCountNormalMode->setRange(1, 50);
    layout->addWidget(stickCountNormalMode);

    return w;
}

QWidget* GameWindow::createIntervalSettings() {
    auto* w = new QWidget(this);
    auto* layout = new QVBoxLayout(w);

    layout->addWidget(new QLabel("Stick Count:"));
    stickCountInterval = new QSpinBox(this);
    stickCountInterval->setRange(1, 50);
    layout->addWidget(stickCountInterval);

    layout->addWidget(new QLabel("A (min sticks per turn):"));
    aInterval = new QSpinBox(this);
    aInterval->setRange(1, 50);
    layout->addWidget(aInterval);

    layout->addWidget(new QLabel("B (max sticks per turn):"));
    bInterval = new QSpinBox(this);
    bInterval->setRange(1, 50);
    layout->addWidget(bInterval);

    return w;
}

QWidget* GameWindow::createSequentialSettings() {
    return createSimpleSettings();
}

QWidget* GameWindow::createSequentialIntervalSettings() {
    return createIntervalSettings();
}

void GameWindow::updatePlayerOptions(GameType type) {
    firstPlayerCombo->clear();
    secondPlayerCombo->clear();

    const QStringList human = { "Human" };
    const QStringList intervalBots = { "Bot" };
    const QStringList sequentialBots = { "GraphBot", "GrundyBot" };
    const QStringList normalModeBots = {"NormalBot"};

    switch (type) {
        case GameType::Simple:
        case GameType::Interval:
            firstPlayerCombo->addItems(human + intervalBots);
            secondPlayerCombo->addItems(human + intervalBots);
            break;
        case GameType::Sequential:
        case GameType::SequentialInterval:
            firstPlayerCombo->addItems(human + sequentialBots);
            secondPlayerCombo->addItems(human + sequentialBots);
            break;
        case GameType::NormalMode:
            firstPlayerCombo->addItems(human + normalModeBots);
            secondPlayerCombo->addItems(human + normalModeBots);
            break;
    }
}

void GameWindow::startGame() {
    GameType type = static_cast<GameType>(gameTypeCombo->currentData().toInt());
    int stickCount = 1, a = 1, b = 1;

    if (type == GameType::Simple || type == GameType::Sequential) {
        stickCount = stickCountSimple->value();
        b = bSimple->value();
    } else if (type == GameType::Interval || type == GameType::SequentialInterval) {
        stickCount = stickCountInterval->value();
        a = aInterval->value();
        b = bInterval->value();
    } else if (type == GameType::NormalMode) {
        stickCount = stickCountNormalMode->value();
    }

    if (a > b) {
        QMessageBox::warning(this, "Invalid parameters", "'a' cannot be greater than 'b'.");
        return;
    }

    if (a > stickCount || b > stickCount) {
        QMessageBox::warning(this, "Invalid parameters", "'a' and 'b' must be less than or equal to stickCount.");
        return;
    }

    QString first = firstPlayerCombo->currentText();
    QString second = secondPlayerCombo->currentText();

    QString firstPlayerName = firstPlayerNameEdit->text();
    QString secondPlayerName = secondPlayerNameEdit->text();

    if (firstPlayerName.isEmpty() || secondPlayerName.isEmpty()) {
        QMessageBox::warning(this, "Invalid parameters", "Player names size must be greater than 0");
        return;
    }

    if (firstPlayerName == secondPlayerName) {
        QMessageBox::warning(this, "Invalid parameters", "Two equals names are not allowed");
        return;
    }

    auto* game = new PlayWindow(type, stickCount, a, b, first, firstPlayerName, second, secondPlayerName, this);
    game->setAttribute(Qt::WA_DeleteOnClose);
    game->show();
    this->hide();
}

void GameWindow::applyDarkTheme() {
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette dark;
    dark.setColor(QPalette::Window, QColor(45, 45, 45));
    dark.setColor(QPalette::WindowText, Qt::white);
    dark.setColor(QPalette::Base, QColor(30, 30, 30));
    dark.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
    dark.setColor(QPalette::ToolTipBase, Qt::white);
    dark.setColor(QPalette::ToolTipText, Qt::black);
    dark.setColor(QPalette::Text, Qt::white);
    dark.setColor(QPalette::Button, QColor(70, 70, 70));
    dark.setColor(QPalette::ButtonText, Qt::white);
    dark.setColor(QPalette::BrightText, Qt::red);
    dark.setColor(QPalette::Highlight, QColor(100, 100, 255));
    dark.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(dark);
}
