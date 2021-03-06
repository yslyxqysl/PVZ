#include "repeater.h"
#include "zombies/zombie.h"

Repeater::Repeater(QObject *parent) :
	Plant(parent)
{
	mAttackDamage = 20;
	mAttackSpeed = 1400;
	mCost = 200;
}

QString Repeater::imgSrc() const
{
	return QStringLiteral(":/plants/images/Plants/Repeater/Repeater.gif");
}

void Repeater::onTimeout(QObject *root)
{
	qint64 newCurrentTime = root->property("currentTime").toLongLong();
	qint64 oldCurrentTime = root->property("lastFrameTime").toLongLong();
	QSize mapSize = root->property("mapSize").toSize();
	qint64 plantTime = property("plantTime").toLongLong();
	if ((newCurrentTime - plantTime) / mAttackSpeed > (oldCurrentTime - plantTime) / mAttackSpeed ||
		(newCurrentTime - plantTime - mAttackSpeed / 5) / mAttackSpeed > (oldCurrentTime - plantTime - mAttackSpeed / 5) / mAttackSpeed)
	{
		bool zombieExist = false;
		for (const QVariant &y : root->property("zombies").toList())
		{
			Zombie *zombie = (Zombie *)(y.value<QPointer<Zombie>>());
			if (zombie->hp() > 0 &&
				qAbs(zombie->pos().y() - mPlantPosition.y()) < 0.5 &&
				zombie->pos().x() - mPlantPosition.x() >= 0 &&
				zombie->pos().x() <= mapSize.width() + 1.)
				zombieExist = true;
		}

		if (zombieExist)
		{
			QList<QVariant> bullets = root->property("bullets").toList();
			QMap<QString, QVariant> bullet;
			bullet["type"] = QStringLiteral("normal");
			bullet["pos"] = mPlantPosition + QPointF(0.3, 0);
			bullet["damage"] = 20;
			bullet["imgSrc"] = QStringLiteral(":/plants/images/Plants/BulletNormal.gif");
			bullets.append(bullet);
			root->setProperty("bullets", bullets);
		}
	}
	Plant::onTimeout(root);
}
