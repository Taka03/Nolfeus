//===============================================
//object.h
//===============================================
#pragma once

//===============================================
//include
//===============================================
#include "Luna.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "sound.h"
#include "character.h"

//===============================================
//class
//===============================================
class CObject
{
	private:
			
			enum
			{
				SE_REFRECT,
				SE_MAX,
			};
			
			CSound Se[SE_MAX];
		
	
	public:
		
		void LoadSound();
		
		void CheckHitRect(CPlayer &player, CEnemy &enemy);
		void CheckHitRect(CPlayer &player, CBoss &boss);
		void CheckHitRect(CBullet &bullet, CEnemy &enemy);
		void CheckHitRect(CBullet &bullet, CBoss &boss);
		void CheckHitRect(CBullet &bullet, CChara &chara);
		void CheckHitRect(CBullet &bullet, CPlayer &player);
		void CheckHitRect(CChara &chara, CEnemy &enemy);
		void CheckHitRect(CChara &chara, CBoss &boss);
		void CheckHitRect(CChara &chara, CPlayer &player);
		void CheckHitRect(CBullet &bullet, CChara &chara, CBoss &boss);
		  
		
};