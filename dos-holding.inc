#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_foreach>

forward Enable(playerid);
forward Disable(playerid);
forward HoldingWeaponsForAll(boolean);

new WeaponTest[MAX_PLAYERS] = -1, timerWeapon, WeaponVars[12], WeaponD2[MAX_PLAYERS] = 1, WeaponD1 = 1, camera[MAX_PLAYERS], bool:ToggleGunOn[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    ToggleGunOn[playerid] = true;
    return 1;
}

ptask AttachWeapon[200](playerid)
{
	if (!playerData[playerid][IsLoggedIn])
		return 0;

	if (!ToggleGunOn[playerid])
		return 0;

	if (WeaponTest[playerid] != GetPlayerWeapon(playerid)) for (new a = 0; a < 12; a++)
	{
	    GetPlayerWeaponData(playerid, a, WeaponVars[a], WeaponVars[6]);

		switch (a)
		{
			case 0:
			{
				if (IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid, 0);
				if (WeaponVars[a] == 1 && GetPlayerWeapon(playerid) != 1) SetPlayerAttachedObject(playerid, 0, 331, 6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
			}
   			case 1:
   			{
				if (IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
     			switch (WeaponVars[a])
				{
					case 2: if (GetPlayerWeapon(playerid) != 2) SetPlayerAttachedObject(playerid, 0, 333, 1, 0.488999, -0.130000, 0.179000, 0.000000, -122.300003, -2.600002, 1.000000, 1.000000, 1.000000);
					case 5: if (GetPlayerWeapon(playerid) != 5) SetPlayerAttachedObject(playerid, 0, 336, 1, 0.318999, -0.049999, 0.193000, 163.699890, -51.700206, -2.999988, 1.000000, 1.000000, 1.000000);
					case 6: if (GetPlayerWeapon(playerid) != 6) SetPlayerAttachedObject(playerid, 0, 337, 1, 0.346998, -0.040999, -0.110999, 22.800008, -58.100067, -62.299949, 1.000000, 1.000000, 1.000000);
					case 7: if (GetPlayerWeapon(playerid) != 7) SetPlayerAttachedObject(playerid, 0, 338, 1, 0.346999, -0.112999, -0.146000, 23.499988, -71.600059, 13.400053, 1.000000, 1.000000, 1.000000);
					case 8: if (GetPlayerWeapon(playerid) != 8) SetPlayerAttachedObject(playerid, 0, 339, 1, 0.398000, -0.012000, -0.027999, -142.399948, -111.500061, 84.999969, 1.000000, 1.000000, 1.000000);
					case 15: if (GetPlayerWeapon(playerid) != 15) SetPlayerAttachedObject(playerid, 0, 326, 1, -0.204999, -0.115000, -0.089000, 2.900004, 62.400035, 0.000000, 1.000000, 1.000000, 1.000000);
				}
    		}
		}
	}

	WeaponTest[playerid] = GetPlayerWeapon(playerid);
	return 1;
}

public Disable(playerid) 
{
    WeaponD2[playerid] = 0;
    WeaponTest[playerid] = -1;

    for (new a = 0; a < 9; a++) if (IsPlayerAttachedObjectSlotUsed(playerid, a)) RemovePlayerAttachedObject(playerid, a);
	return 1;
}

public Enable(playerid) 
{
    WeaponD2[playerid] = 1;
	return 1;
}

public HoldingWeaponsForAll(boolean) 
{
	if(boolean == 0)
	{
 		if (!WeaponD1) return 1;
		foreach (new i : Player) for (new a = 0; a < 9; a++) if (IsPlayerAttachedObjectSlotUsed(i, a)) RemovePlayerAttachedObject(i, a);
		KillTimer(timerWeapon);
		WeaponD1 = 0;
	    return 1;
	}
	if (boolean == 1)
	{
		if (WeaponD1) return 1;
		WeaponD1 = 1;
		return 1;
	}
 	return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (newkeys == 128 && oldkeys != 128 && GetPlayerWeapon(playerid) == 43) 
	{
        camera[playerid] = 1;
        for(new a = 0; a < 9; a++) if (IsPlayerAttachedObjectSlotUsed(playerid, a)) RemovePlayerAttachedObject(playerid, a);
    }
	if (newkeys != 128 && oldkeys == 128 && GetPlayerWeapon(playerid) == 43)
	{
		camera[playerid] = 0;
	}
	return 1;
}

CMD:togglegun(playerid, params[])
{
	if (!ToggleGunOn[playerid])
	{
	    ToggleGunOn[playerid] = true;
	    SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}คุณได้เปิดการแสดงอาวุธติดหลังของคุณแล้ว");
	}
	else
	{
	    ToggleGunOn[playerid] = false;
	    SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}คุณได้ปิดการแสดงอาวุธติดหลังของคุณแล้ว");
	}
	return 1;
}