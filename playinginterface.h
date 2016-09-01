#ifndef PLAYINGINTERFACE_H
#define PLAYINGINTERFACE_H

#include <QWidget>
#include "mainwindow.h"

class GameLogic;
class Zombie;

namespace Ui {
class PlayForm;
}

class PlayingInterface : public QWidget
{
	Q_OBJECT

public:
	explicit PlayingInterface(QWidget *parent = 0);

	Q_INVOKABLE QLabel *createDynamicImage(const QString &imgSrc, QWidget *parent = 0);

signals:
	void stateSet(MainWindow::GameState);

protected:
	void paintEvent(QPaintEvent *);
	void timerEvent(QTimerEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);

private slots:
	void onAnimationFinished();
	void onCreatureDestroyed(QObject *);
	void on_buttonMenu_clicked();
	void onGameFinished();

private:
	Ui::PlayForm *ui;

	int timerId;
	QObject *mGameStatus;
	GameLogic *mGameLogic;

	void registerInterpolator();
	QPoint zombieAnimationOffset(Zombie *zombie);
	QPointF screenToLawn(QPoint point);
};

#endif // PLAYINGINTERFACE_H
