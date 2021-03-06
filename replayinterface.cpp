#include "replayinterface.h"
#include "playinginterface.h"
#include "gamelogic.h"
#include "plants/plant.h"

ReplayInterface::ReplayInterface(QWidget *parent) : QWidget(parent)
{
	mGameRecordFile = nullptr;
	replaySpeed = 1.;
	setFocusPolicy(Qt::StrongFocus);
	setFocus();
}

ReplayInterface::~ReplayInterface()
{

}

void ReplayInterface::setReplayFile(const QString &fileName)
{
	playInterface = new PlayingInterface(this);
	playInterface->setProperty("playSpeed", replaySpeed);
	playInterface->gameStatus()->setProperty("mode", "replay");
	connect(playInterface, SIGNAL(stateSet(MainWindow::GameState)), this, SIGNAL(stateSet(MainWindow::GameState)));
	playInterface->show();
	mGameRecordFile = new QFile(fileName);
	if (!mGameRecordFile->open(QIODevice::ReadOnly))
	{
		emit stateSet(MainWindow::Welcome);
		return;
	}

	mGameRecordStream.setDevice(mGameRecordFile);
	lastFrameTime = 0;
	timerId = startTimer(0);
}

void ReplayInterface::timerEvent(QTimerEvent *)
{
	static double replayFrameCount = 0.;

	if (playInterface->gameStatus()->property("gameStartTime").isNull())
		return;
	while (!mGameRecordStream.atEnd())
	{
		qint8 operationType;
		qint32 type, index;
		qint32 newCurrentTime;
		double x;
		QPointF pos;
		mGameRecordStream >> newCurrentTime >> operationType;
		playInterface->gameStatus()->setProperty("currentTime", (qint64)newCurrentTime);
		switch (operationType)
		{
		case 'C':
			mGameRecordStream >> index;
			playInterface->gameLogic()->collectSunshine(playInterface->gameStatus(), index);
			break;
		case 'D':
			mGameRecordStream >> pos;
			for (const QVariant &x : playInterface->gameStatus()->property("plants").toList())
				if (x.value<QPointer<Plant>>()->pos() == pos)
					x.value<QPointer<Plant>>()->onRemoved(playInterface->gameStatus());
			break;
		case 'E':
			killTimer(timerId);
			return;
		case 'P':
			mGameRecordStream >> type >> pos;
			playInterface->gameLogic()->createPlant(playInterface->gameStatus(), type, pos.x(), pos.y());
			break;
		case 'S':
			mGameRecordStream >> x;
			playInterface->gameLogic()->createSunshine(playInterface->gameStatus(), x);
			break;
		case 'U':
			playInterface->gameStatus()->setProperty("lastFrameTime", (qint64)lastFrameTime);
			playInterface->runGameLogic();
			lastFrameTime = newCurrentTime;
			update();
			replayFrameCount += 1. / replaySpeed;
			if (replayFrameCount < 1.)
				continue;
			replayFrameCount -= 1;
			return;
		case 'Z':
			mGameRecordStream >> type >> pos;
			playInterface->gameLogic()->createZombie(playInterface->gameStatus(), type, pos.x(), pos.y());
			break;
		default:
			break;
		}
	}
}

void ReplayInterface::keyPressEvent(QKeyEvent *ev)
{
	switch (ev->key())
	{
	case Qt::Key_Up:
		if (replaySpeed <= 7.)
			replaySpeed += 1.;
		break;
	case Qt::Key_Down:
		if (replaySpeed >= 2.)
			replaySpeed -= 1.;
		break;
	default:
		QWidget::keyPressEvent(ev);
		break;
	}
	playInterface->setProperty("playSpeed", replaySpeed);
}
