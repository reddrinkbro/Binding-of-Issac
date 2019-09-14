#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

void player::enemyCollision(void)
{
	RECT rcTemp;
	float angle;
	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getAttackFly().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getAttackFly()[j].attackFly->getStruct().rc, 0, 0, 0, 0)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getAttackFly()[j].attackFly->getStruct().x, _enemy->getAttackFly()[j].attackFly->getStruct().y);
				_baseBullet->removeBullet(i);
				_enemy->getAttackFly()[j].attackFly->bulletHit(angle,_body.atk);
				if (_enemy->getAttackFly()[j].attackFly->getStruct().hp <= 0)
				{
					_enemy->removeAttackFly(j);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getBlubber().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getBlubber()[j].blubber->getStruct().rc, 40, 10, 40, 10)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getBlubber()[j].blubber->getStruct().x, _enemy->getBlubber()[j].blubber->getStruct().y);
				_baseBullet->removeBullet(i);
				_enemy->getBlubber()[j].blubber->bulletHit(angle, _body.atk);
				_enemy->addBlood(_enemy->getBlubber()[j].blubber->getStruct().rc.left, _enemy->getBlubber()[j].blubber->getStruct().rc.top);
				if (_enemy->getBlubber()[j].blubber->getStruct().hp <= 0)
				{
					_enemy->removeBlubber(j);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getCharger().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getCharger()[j].charger->getStruct().rc, 15, 10, 15, 10)))
			{
				_baseBullet->removeBullet(i);
				_enemy->getCharger()[j].charger->bulletHit(_body.atk);
				_enemy->addBlood(_enemy->getCharger()[j].charger->getStruct().rc.left, _enemy->getCharger()[j].charger->getStruct().rc.top);
				if (_enemy->getCharger()[j].charger->getStruct().hp <= 0)
				{
					_enemy->removeCharger(j);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getClotty().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getClotty()[j].clotty->getStruct().rc, 30, 60, 38, 20)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getClotty()[j].clotty->getStruct().x, _enemy->getClotty()[j].clotty->getStruct().y);
				_baseBullet->removeBullet(i);
				_enemy->getClotty()[j].clotty->bulletHit(angle, _body.atk);
				_enemy->addBlood(_enemy->getClotty()[j].clotty->getStruct().rc.left, _enemy->getClotty()[j].clotty->getStruct().rc.top);
				if (_enemy->getClotty()[j].clotty->getStruct().hp <= 0)
				{
					_enemy->removeClotty(j);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getFrowningGaper().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getFrowningGaper()[j].gaper->getBody().rc, 10, 0, 15, 30)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getFrowningGaper()[j].gaper->getBody().x, _enemy->getFrowningGaper()[j].gaper->getBody().y);
				_baseBullet->removeBullet(i);
				_enemy->getFrowningGaper()[j].gaper->bulletHit(angle, _body.atk);
				_enemy->addBlood(_enemy->getFrowningGaper()[j].gaper->getBody().rc.left, _enemy->getFrowningGaper()[j].gaper->getBody().rc.top);
				if (_enemy->getFrowningGaper()[j].gaper->getBody().hp <= 0)
				{
					_enemy->removeGaper(j);
				}
				break;
			}
		}
	}

	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getHorf().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getHorf()[j].horf->getStruct().rc, 15, 15, 15, 5)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getHorf()[j].horf->getStruct().x, _enemy->getHorf()[j].horf->getStruct().y);
				_baseBullet->removeBullet(i);
				_enemy->getHorf()[j].horf->bulletHit(angle, _body.atk);
				_enemy->addBlood(_enemy->getHorf()[j].horf->getStruct().rc.left, _enemy->getHorf()[j].horf->getStruct().rc.top);
				if (_enemy->getHorf()[j].horf->getStruct().hp <= 0)
				{
					_enemy->removeHorf(j);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getLevel2Fly().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getLevel2Fly()[j].level2Fly->getStruct().rc, 20, 30, 20, 5)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getLevel2Fly()[j].level2Fly->getStruct().x, _enemy->getLevel2Fly()[j].level2Fly->getStruct().y);
				_baseBullet->removeBullet(i);
				_enemy->getLevel2Fly()[j].level2Fly->bulletHit(angle, _body.atk);
				_enemy->addBlood(_enemy->getLevel2Fly()[j].level2Fly->getStruct().rc.left, _enemy->getLevel2Fly()[j].level2Fly->getStruct().rc.top);
				if (_enemy->getLevel2Fly()[j].level2Fly->getStruct().hp <= 0)
				{
					_enemy->removeLevel2Fly(j);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
	{
		for (int j = 0; j < _enemy->getTumor().size(); j++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getTumor()[j].tumor->getStruct().rc, 25, 10, 25, 0)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getTumor()[j].tumor->getStruct().x, _enemy->getTumor()[j].tumor->getStruct().y);
				_baseBullet->removeBullet(i);
				_enemy->getTumor()[j].tumor->bulletHit(angle, _body.atk);
				_enemy->addBlood(_enemy->getTumor()[j].tumor->getStruct().rc.left, _enemy->getTumor()[j].tumor->getStruct().rc.top);
				if (_enemy->getTumor()[j].tumor->getStruct().hp <= 0)
				{
					_enemy->removeTumor(j);
				}
				break;
			}
		}
	}
	if (_enemy->getBossSelect() == BOSSSELECT_DUKEOFFLLIES && _enemy->getBossInit())
	{
		for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getDukeOfflies().dukeofflies->getStruct().rc, 65, 30, 65, 15)))
			{
				angle = getAngle(_body.x, _body.y, _enemy->getDukeOfflies().dukeofflies->getStruct().x, _enemy->getDukeOfflies().dukeofflies->getStruct().y);
				_baseBullet->removeBullet(i);
				_enemy->getDukeOfflies().dukeofflies->bulletHit(angle, _body.atk);
				if (_enemy->getDukeOfflies().dukeofflies->getStruct().hp <= 0)
				{
					_enemy->removeDukeOfflies();
				}
				break;
			}
		}
	}
	if (_enemy->getBossSelect() == BOSSSELECT_MONSTRO && _enemy->getBossInit())
	{
		for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getMonstro().monstro->getStruct().rc, 65, 30, 65, 15)))
			{
				_baseBullet->removeBullet(i);
				_enemy->getMonstro().monstro->bulletHit(_body.atk);
				if (_enemy->getMonstro().monstro->getStruct().hp <= 0)
				{
					_enemy->removeMonstro();
				}
				break;
			}
		}
	}

	if (_enemy->getBossSelect() == BOSSSELECT_MEGAMAW && _enemy->getBossInit())
	{
		if (_enemy->getMegamaw().megamaw->getStruct().state == MEGAMAWSTATE_START) return;
		for (int i = 0; i < _baseBullet->getBaseBullet().size(); i++)
		{
			if (IntersectRect(&rcTemp, &_baseBullet->getBaseBullet()[i].rc, &CollisionAreaResizing(_enemy->getMegamaw().megamaw->getStruct().rc, 90, 0, 90, 40)))
			{
				_baseBullet->removeBullet(i);
				_enemy->getMegamaw().megamaw->bulletHit(_body.atk);
				if (_enemy->getMegamaw().megamaw->getStruct().hp <= 0)
				{
					_enemy->removeMegamaw();
				}
				break;
			}
		}
	}
	if (_familiarOn)
	{
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getAttackFly().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getAttackFly()[j].attackFly->getStruct().rc, 0, 0, 0, 0)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getAttackFly()[j].attackFly->getStruct().x, _enemy->getAttackFly()[j].attackFly->getStruct().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getAttackFly()[j].attackFly->bulletHit(angle, _body.atk);
					if (_enemy->getAttackFly()[j].attackFly->getStruct().hp <= 0)
					{
						_enemy->removeAttackFly(j);
					}
					break;
				}
			}
		}
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getBlubber().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getBlubber()[j].blubber->getStruct().rc, 40, 10, 40, 10)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getBlubber()[j].blubber->getStruct().x, _enemy->getBlubber()[j].blubber->getStruct().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getBlubber()[j].blubber->bulletHit(angle, _body.atk);
					_enemy->addBlood(_enemy->getBlubber()[j].blubber->getStruct().rc.left, _enemy->getBlubber()[j].blubber->getStruct().rc.top);
					if (_enemy->getBlubber()[j].blubber->getStruct().hp <= 0)
					{
						_enemy->removeBlubber(j);
					}
					break;
				}
			}
		}
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getCharger().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getCharger()[j].charger->getStruct().rc, 15, 10, 15, 10)))
				{
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getCharger()[j].charger->bulletHit(_body.atk);
					_enemy->addBlood(_enemy->getCharger()[j].charger->getStruct().rc.left, _enemy->getCharger()[j].charger->getStruct().rc.top);
					if (_enemy->getCharger()[j].charger->getStruct().hp <= 0)
					{
						_enemy->removeCharger(j);
					}
					break;
				}
			}
		}
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getClotty().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getClotty()[j].clotty->getStruct().rc, 30, 60, 38, 20)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getClotty()[j].clotty->getStruct().x, _enemy->getClotty()[j].clotty->getStruct().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getClotty()[j].clotty->bulletHit(angle, _body.atk);
					_enemy->addBlood(_enemy->getClotty()[j].clotty->getStruct().rc.left, _enemy->getClotty()[j].clotty->getStruct().rc.top);
					if (_enemy->getClotty()[j].clotty->getStruct().hp <= 0)
					{
						_enemy->removeClotty(j);
					}
					break;
				}
			}
		}
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getFrowningGaper().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getFrowningGaper()[j].gaper->getBody().rc, 10, 0, 15, 30)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getFrowningGaper()[j].gaper->getBody().x, _enemy->getFrowningGaper()[j].gaper->getBody().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getFrowningGaper()[j].gaper->bulletHit(angle, _body.atk);
					_enemy->addBlood(_enemy->getFrowningGaper()[j].gaper->getBody().rc.left, _enemy->getFrowningGaper()[j].gaper->getBody().rc.top);
					if (_enemy->getFrowningGaper()[j].gaper->getBody().hp <= 0)
					{
						_enemy->removeGaper(j);
					}
					break;
				}
			}
		}

		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getHorf().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getHorf()[j].horf->getStruct().rc, 15, 15, 15, 5)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getHorf()[j].horf->getStruct().x, _enemy->getHorf()[j].horf->getStruct().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getHorf()[j].horf->bulletHit(angle, _body.atk);
					_enemy->addBlood(_enemy->getHorf()[j].horf->getStruct().rc.left, _enemy->getHorf()[j].horf->getStruct().rc.top);
					if (_enemy->getHorf()[j].horf->getStruct().hp <= 0)
					{
						_enemy->removeHorf(j);
					}
					break;
				}
			}
		}
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getLevel2Fly().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getLevel2Fly()[j].level2Fly->getStruct().rc, 20, 30, 20, 5)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getLevel2Fly()[j].level2Fly->getStruct().x, _enemy->getLevel2Fly()[j].level2Fly->getStruct().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getLevel2Fly()[j].level2Fly->bulletHit(angle, _body.atk);
					_enemy->addBlood(_enemy->getLevel2Fly()[j].level2Fly->getStruct().rc.left, _enemy->getLevel2Fly()[j].level2Fly->getStruct().rc.top);
					if (_enemy->getLevel2Fly()[j].level2Fly->getStruct().hp <= 0)
					{
						_enemy->removeLevel2Fly(j);
					}
					break;
				}
			}
		}
		for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
		{
			for (int j = 0; j < _enemy->getTumor().size(); j++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getTumor()[j].tumor->getStruct().rc, 25, 10, 25, 0)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getTumor()[j].tumor->getStruct().x, _enemy->getTumor()[j].tumor->getStruct().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getTumor()[j].tumor->bulletHit(angle, _body.atk);
					_enemy->addBlood(_enemy->getTumor()[j].tumor->getStruct().rc.left, _enemy->getTumor()[j].tumor->getStruct().rc.top);
					if (_enemy->getTumor()[j].tumor->getStruct().hp <= 0)
					{
						_enemy->removeTumor(j);
					}
					break;
				}
			}
		}
		if (_enemy->getBossSelect() == BOSSSELECT_DUKEOFFLLIES && _enemy->getBossInit())
		{
			for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getDukeOfflies().dukeofflies->getStruct().rc, 65, 30, 65, 15)))
				{
					angle = getAngle(_familiar->getFamiliar().x, _familiar->getFamiliar().y, _enemy->getDukeOfflies().dukeofflies->getStruct().x, _enemy->getDukeOfflies().dukeofflies->getStruct().y);
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getDukeOfflies().dukeofflies->bulletHit(angle, _body.atk);
					if (_enemy->getDukeOfflies().dukeofflies->getStruct().hp <= 0)
					{
						_enemy->removeDukeOfflies();
					}
					break;
				}
			}
		}
		if (_enemy->getBossSelect() == BOSSSELECT_MONSTRO && _enemy->getBossInit())
		{
			for (int i = 0; i <  _familiar->getFamiliarBullet()->getBullet().size(); i++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getMonstro().monstro->getStruct().rc, 65, 30, 65, 15)))
				{
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getMonstro().monstro->bulletHit(_body.atk);
					if (_enemy->getMonstro().monstro->getStruct().hp <= 0)
					{
						_enemy->removeMonstro();
					}
					break;
				}
			}
		}

		if (_enemy->getBossSelect() == BOSSSELECT_MEGAMAW && _enemy->getBossInit())
		{
			if (_enemy->getMegamaw().megamaw->getStruct().state == MEGAMAWSTATE_START) return;
			for (int i = 0; i < _familiar->getFamiliarBullet()->getBullet().size(); i++)
			{
				if (IntersectRect(&rcTemp, &_familiar->getFamiliarBullet()->getBullet()[i].rc, &CollisionAreaResizing(_enemy->getMegamaw().megamaw->getStruct().rc, 90, 0, 90, 40)))
				{
					_familiar->getFamiliarBullet()->removeBullet(i);
					_enemy->getMegamaw().megamaw->bulletHit(_body.atk);
					if (_enemy->getMegamaw().megamaw->getStruct().hp <= 0)
					{
						_enemy->removeMegamaw();
					}
					break;
				}
			}
		}
	}
}