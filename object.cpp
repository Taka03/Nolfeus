//===============================================
//object.cpp
//===============================================

//===============================================
//include
//===============================================
#include "object.h"
#include "function.h"

//===============================================
//サウンド読み込み
//===============================================
void CObject::LoadSound()
{
	char *sename[] =
	{
		"sound\\refrect.wav",
	};
	
	for(int i = 0;i < SE_MAX;i++)
	{
		Se[i].LoadSound(sename[i]);
	}
}

//===============================================
//当たり判定処理
//===============================================
void CObject::CheckHitRect(CPlayer &player, CEnemy &enemy)
{
	if(enemy.IsExist)
	{
		if(HitCheck(player.HitRect, enemy.HitRect) )
		{
			if(player.IsWolf)
			{
				enemy.CalcDamage(30, 0);
			}
			
			else if(player.IsClear)
			{
			
			}
			
			else
			{
				if(!player.IsInvince)
				{
					player.CalcDamage(enemy.Attack, player.Defence);
					player.KnockBack();
				}
			}
			
		}
	}
	
}

void CObject::CheckHitRect(CPlayer &player, CBoss &boss)
{
	if(boss.IsExist && boss.counter > 200)
	{
		if(HitCheck(player.HitRect, boss.HitRect) )
		{
			if(player.IsWolf)
			{
				boss.CalcDamage(30, 0);	
			}
			
			else if(player.IsClear)
			{
			
			}
			
			else
			{
				if(!player.IsInvince)
				{
					player.CalcDamage(boss.Attack, player.Defence);
					player.KnockBack();
				}
			}
		}
	}

}

void CObject::CheckHitRect(CBullet &bullet, CChara &chara)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		if(bullet.Flag[i])
		{
			if(chara.IsExist)
			{
				if(HitCheck(bullet.HitRect[i], chara.HitRect) )
				{
					bullet.Flag[i] = FALSE;
					
					bullet.SetPosition(i);
					
					chara.IsExist = FALSE;
				}
			}
		}
	}
}

void CObject::CheckHitRect(CBullet &bullet, CEnemy &enemy)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		if(bullet.Flag[i])
		{
			if(enemy.IsExist)
			{
				if(HitCheck(bullet.HitRect[i], enemy.HitRect) )	
				{
					bullet.Flag[i] = FALSE;
					
					bullet.IsRefrect[i] = FALSE;
						
					bullet.SetPosition(i);
						
					AddScore(enemy.Score);
						
					enemy.CalcDamage(bullet.Attack, enemy.Defence);
					
					Se[SE_REFRECT].PlaySoundA();
				}
					
			}
		}
				
		enemy.Dead();
					
	}

}

void CObject::CheckHitRect(CBullet &bullet, CBoss &boss)
{
	for(int i = 0;i < BULLET_MAX;i++)
	{
		if(bullet.Flag[i])
		{	
			if(boss.IsExist && boss.counter > 200)
			{
				if(HitCheck(bullet.HitRect[i], boss.HitRect) )
				{
					bullet.Flag[i] = FALSE;
					
					bullet.IsRefrect[i] = FALSE;
					
					bullet.SetPosition(i);
					
					boss.CalcDamage(bullet.Attack, boss.Defence);
					
					AddScore(boss.Score);
					
				}
			}
		}
		
	}

}

void CObject::CheckHitRect(CBullet &bullet, CPlayer &player)
{
	/*敵弾とプレイヤーとの処理*/
	for(int i = 0;i < BULLET_MAX;i++)
	{
		if(bullet.Flag[i])
		{
			if(HitCheck(bullet.HitRect[i], player.HitRect) )
			{
				if(player.IsWolf)
				{
					bullet.Flag[i] = FALSE;
				}
				
				else if(player.IsClear)
				{
				
				}
				
				else
				{
					if(!player.IsInvince)
					{
						player.CalcDamage(bullet.Attack, player.Defence);
						player.KnockBack();
					}
					
					bullet.Flag[i] = FALSE;
				}
			}
			
			if(player.umbrella.IsExist)
			{
				if(HitCheck(bullet.HitRect[i], player.umbrella.HitRect) )
				{
					if(player.umbrella.counter >= 5 && player.umbrella.counter <= 8)
					{
						Se[SE_REFRECT].PlaySoundA();
						bullet.Flag[i] = FALSE;
						player.bullet.CreateRefBullet(player.umbrella.Get_PosX(), player.umbrella.Get_PosY(), i);
						player.bullet.IsRefrect[i] = TRUE;
					}
					
					else
					{
						player.bullet.IsRefrect[i] = FALSE;
					}
						
				}
			}
			
		}
	}
	
}

void CObject::CheckHitRect(CChara &chara, CEnemy &enemy)
{
	if(chara.IsExist)
	{
		if(enemy.IsExist)
		{
			if(HitCheck(chara.HitRect, enemy.HitRect ) )
			{
				AddScore(enemy.Score);
				enemy.CalcDamage(chara.Attack, enemy.Defence);
				enemy.Dead();
			}
		}
	}
}

void CObject::CheckHitRect(CChara &chara, CBoss &boss)
{
	if(chara.IsExist)
	{
		if(boss.IsExist)
		{
			if(HitCheck(chara.HitRect, boss.HitRect ) )
			{
				AddScore(boss.Score);
				boss.CalcDamage(chara.Attack, boss.Defence);
			}
		}
	}
}


void CObject::CheckHitRect(CBullet &bullet, CChara &chara, CBoss &boss)
{
	if(chara.IsExist)
	{
		if(boss.IsExist && boss.counter > 200)
		{
			if(HitCheck(chara.HitRect, boss.HitRect) )
			{
				boss.CalcDamage(chara.Attack, boss.Defence);
				
				chara.IsExist = FALSE;
				
				bullet.ChargeFlag = FALSE;
				
				AddScore(boss.Score);
			}	
		}
	}
}

void CObject::CheckHitRect(CChara &chara, CPlayer &player)
{
	if(chara.IsExist)
	{
		if(HitCheck(chara.HitRect, player.HitRect) )	
		{
			if(player.IsWolf)
			{
				chara.IsExist = FALSE;
			}
			
			else if(player.IsClear)
			{
			
			}
			
			else
			{
				if(!player.IsInvince)
				{
					player.CalcDamage(chara.Attack, player.Defence);
					player.KnockBack();
				}
					
				chara.IsExist = FALSE;
			}
		}
		
		for(int i = 0;i < BULLET_MAX;i++)
		{
			if(chara.bullet.Flag[i])
			{
				if(HitCheck(chara.bullet.HitRect[i], player.HitRect) )
				{
					if(player.IsWolf)
					{
						chara.bullet.Flag[i] = FALSE;
					}
					
					else if(player.IsClear)
					{
					
					}
					
					else
					{
						if(!player.IsInvince)
						{
							player.CalcDamage(chara.bullet.Attack, player.Defence);
							player.KnockBack();
						}
							
						chara.bullet.Flag[i] = FALSE;
					}
						
				}
				
				if(player.umbrella.IsExist)
				{
					if(HitCheck(chara.bullet.HitRect[i], player.umbrella.HitRect) )
					{
						if(player.umbrella.counter >= 5 && player.umbrella.counter <= 8)
						{
							Se[SE_REFRECT].PlaySoundA();
							chara.bullet.Flag[i] = FALSE;
							player.bullet.IsRefrect[i] = TRUE;
							player.bullet.CreateRefBullet(player.umbrella.Get_PosX(), player.umbrella.Get_PosY(), i);
							
						}
						
						else
						{
							player.bullet.IsRefrect[i] = FALSE;
						}
					}
				}
					
			}
		}
	}
	
}
