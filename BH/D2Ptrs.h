#pragma once
// Macros adapted from lord2800's macros.
#include "Patch.h"
#include "D2Structs.h"

#ifdef _DEFINE_PTRS
#define FUNCPTR(dll, name, callingret, args, address) \
	__declspec(naked) callingret dll##_##name##args \
	{ \
		static DWORD f##dll##_##name = NULL; \
		if(f##dll##_##name == NULL) \
		{ \
		__asm { pushad } \
		f##dll##_##name = Patch::GetDllOffset(dll, address); \
		__asm { popad } \
		} \
		__asm jmp [f##dll##_##name] \
	}

#define ASMPTR(dll, name, address) \
	DWORD* Asm_##dll##_##name##(VOID) \
	{ \
		static DWORD f##Asm_##dll##_##name = NULL; \
		if(f##Asm_##dll##_##name## == NULL) \
		{ \
		f##Asm_##dll##_##name## = Patch::GetDllOffset(dll, address); \
		} \
		return &##f##Asm_##dll##_##name; \
	} 

#define VARPTR(dll, name, type, address) \
	type** Var_##dll##_##name##(VOID) \
	{ \
		static DWORD f##Var_##dll##_##name = NULL; \
		if(f##Var_##dll##_##name## == NULL) \
		{ \
		f##Var_##dll##_##name## = Patch::GetDllOffset(dll, address); \
		} \
		return (type**)&##f##Var_##dll##_##name; \
	} 

#else
#define FUNCPTR(dll, name, callingret, args, address) extern callingret dll##_##name##args;
#define ASMPTR(dll, name, address) extern DWORD* Asm_##dll##_##name##(VOID); static DWORD dll##_##name = *Asm_##dll##_##name##();
#define VARPTR(dll, name, type, address) extern type** Var_##dll##_##name##(VOID); static type* p##_##dll##_##name = (type*)*Var_##dll##_##name##();
#endif
/*
FUNCPTR(D2CLIENT, GetQuestInfo, void* __stdcall, (void), 0x45A00)

FUNCPTR(D2CLIENT, SubmitItem, void __fastcall, (DWORD dwItemId), 0x45FB0)
FUNCPTR(D2CLIENT, Transmute, void __fastcall, (void), 0x8CB90)

FUNCPTR(D2CLIENT, FindClientSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0xA5B20)
FUNCPTR(D2CLIENT, FindServerSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0xA5B40)
FUNCPTR(D2CLIENT, GetCurrentInteractingNPC, UnitAny* __fastcall, (void), 0x46150)
FUNCPTR(D2CLIENT, GetSelectedUnit, UnitAny * __stdcall, (void), 0x51A80)
FUNCPTR(D2CLIENT, GetCursorItem, UnitAny* __fastcall, (void), 0x16020)
FUNCPTR(D2CLIENT, GetMercUnit, UnitAny* __fastcall, (void), 0x97CD0)
FUNCPTR(D2CLIENT, UnitTestSelect, DWORD __stdcall, (UnitAny* pUnit, DWORD _1, DWORD _2, DWORD _3), 0x8D030) // unused but we need to use it

FUNCPTR(D2CLIENT, SetSelectedUnit_I, void __fastcall, (UnitAny *pUnit), 0x51860)
FUNCPTR(D2CLIENT, GetItemName, BOOL __stdcall, (UnitAny* pItem, wchar_t* wBuffer, DWORD dwSize), 0x914F0)
FUNCPTR(D2CLIENT, GetMonsterOwner, DWORD __fastcall, (DWORD nMonsterId), 0x216A0)
FUNCPTR(D2CLIENT, GetUnitHPPercent, DWORD __fastcall, (DWORD dwUnitId), 0x21580)
FUNCPTR(D2CLIENT, InitInventory, void __fastcall, (void), 0x908C0)
FUNCPTR(D2CLIENT, SetUIVar, DWORD __fastcall, (DWORD varno, DWORD howset, DWORD unknown1), 0xC2790) 
FUNCPTR(D2CLIENT, GetUnitX, int __fastcall, (UnitAny* pUnit), 0x1630)
FUNCPTR(D2CLIENT, GetUnitY, int __fastcall, (UnitAny* pUnit), 0x1660)

FUNCPTR(D2CLIENT, ShopAction, void __fastcall, (UnitAny* pItem, UnitAny* pNpc, UnitAny* pNpc2, DWORD dwSell, DWORD dwItemCost, DWORD dwMode, DWORD _2, DWORD _3), 0x47D60)

FUNCPTR(D2CLIENT, CloseNPCInteract, void __fastcall, (void), 0x492F0)
//FUNCPTR(D2CLIENT, ClearScreen, void __fastcall, (void), 0x492F0) // unused but I want to look into using it // wrong function
FUNCPTR(D2CLIENT, CloseInteract, void __fastcall, (void), 0x43870)

FUNCPTR(D2CLIENT, GetAutomapSize, DWORD __stdcall, (void), 0x5F080)
FUNCPTR(D2CLIENT, NewAutomapCell, AutomapCell * __fastcall, (void), 0x5F6B0)
FUNCPTR(D2CLIENT, AddAutomapCell, void __fastcall, (AutomapCell *aCell, AutomapCell **node), 0x61320)
FUNCPTR(D2CLIENT, RevealAutomapRoom, void __stdcall, (Room1 *pRoom1, DWORD dwClipFlag, AutomapLayer *aLayer), 0x62580)
FUNCPTR(D2CLIENT, InitAutomapLayer_I, AutomapLayer* __fastcall, (DWORD nLayerNo), 0x62710)

FUNCPTR(D2CLIENT, ClickMap, void __stdcall, (DWORD MouseFlag, DWORD x, DWORD y, DWORD Type), 0x1BF20)
FUNCPTR(D2CLIENT, LeftClickItem, void __stdcall, (UnitAny* pPlayer, Inventory* pInventory, int x, int y, DWORD dwClickType, InventoryLayout* pLayout, DWORD Location), 0x96AA0) // 1.12

FUNCPTR(D2CLIENT, GetMouseXOffset, DWORD __fastcall, (void), 0x3F6C0)
FUNCPTR(D2CLIENT, GetMouseYOffset, DWORD __fastcall, (void), 0x3F6D0)

FUNCPTR(D2CLIENT, PrintPartyString, void __stdcall, (wchar_t *wMessage, int nColor), 0x7D610) // unused but I want to look into using it too
FUNCPTR(D2CLIENT, PrintGameString, void __stdcall, (wchar_t *wMessage, int nColor), 0x7D850)

FUNCPTR(D2CLIENT, LeaveParty, void __fastcall, (void), 0x9E5D0)

FUNCPTR(D2CLIENT, AcceptTrade, void __fastcall, (void), 0x59600)
FUNCPTR(D2CLIENT, CancelTrade, void __fastcall, (void), 0x595C0)

FUNCPTR(D2CLIENT, GetDifficulty, BYTE __stdcall, (void), 0x41930)

FUNCPTR(D2CLIENT, ExitGame, void __fastcall, (void), 0x42850)

FUNCPTR(D2CLIENT, GetUiVar_I, DWORD __fastcall, (DWORD dwVarNo), 0xBE400)

FUNCPTR(D2CLIENT, DrawRectFrame, void __fastcall, (DWORD Rect), 0xBE4C0)

FUNCPTR(D2CLIENT, PerformGoldDialogAction, void __fastcall, (void), 0xBFDF0)

FUNCPTR(D2CLIENT, GetPlayerUnit, UnitAny* __stdcall, (void), 0xA4D60)

FUNCPTR(D2CLIENT, GetLevelName_I, wchar_t* __fastcall, (DWORD levelId), 0xBE240)

FUNCPTR(D2GFX, DrawAutomapCell, void __stdcall, (CellContext *context, DWORD xpos, DWORD ypos, RECT *cliprect, DWORD bright), -10079)
ASMPTR(D2CLIENT, OverrideShrinePatch_ORIG, 0x1155B8)//Updated 1.13c

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Client Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2CLIENT, ScreenSizeX, DWORD, 0xDBC48)
VARPTR(D2CLIENT, ScreenSizeY, DWORD, 0xDBC4C)

VARPTR(D2CLIENT, CursorHoverX, DWORD, 0xE0EB8)
VARPTR(D2CLIENT, CursorHoverY, DWORD, 0xE0EBC)

VARPTR(D2CLIENT, MouseX, DWORD, 0x11B828)
VARPTR(D2CLIENT, MouseY, DWORD, 0x11B824)

VARPTR(D2CLIENT, MouseOffsetY, int, 0x11995C)
VARPTR(D2CLIENT, MouseOffsetX, int, 0x119960)

VARPTR(D2CLIENT, AutomapOn, DWORD, 0xFADA8)
VARPTR(D2CLIENT, AutomapMode, int, 0xF16B0)
VARPTR(D2CLIENT, Offset, POINT, 0x11C1F8)
VARPTR(D2CLIENT, AutomapLayer, AutomapLayer*, 0x11C1C4)

VARPTR(D2CLIENT, MercStrIndex, WORD, 0xF23E8)
VARPTR(D2CLIENT, MercReviveCost, DWORD, 0x11C334)

VARPTR(D2CLIENT, GoldDialogAction, DWORD, 0xFAD5C)
VARPTR(D2CLIENT, GoldDialogAmount, DWORD, 0x11BBB0)

VARPTR(D2CLIENT, NPCMenu, NPCMenu*, 0xF3BA0)
VARPTR(D2CLIENT, NPCMenuAmount, DWORD, 0xF42F0)

VARPTR(D2CLIENT, TradeLayout, InventoryLayout*, 0x10B288)
VARPTR(D2CLIENT, StashLayout, InventoryLayout*, 0x10B2D0)
VARPTR(D2CLIENT, StoreLayout, InventoryLayout*, 0x10B3B0)
VARPTR(D2CLIENT, CubeLayout, InventoryLayout*, 0x10B3C8)
VARPTR(D2CLIENT, InventoryLayout, InventoryLayout*, 0x10B3E0)
VARPTR(D2CLIENT, MercLayout, InventoryLayout*, 0x11BD94)
ASMPTR(D2CLIENT, clickParty_I, 0x9E180)

VARPTR(D2CLIENT, RegularCursorType, DWORD, 0x11B864)
VARPTR(D2CLIENT, ShopCursorType, DWORD, 0x11BC34)


VARPTR(D2CLIENT, Ping, DWORD, 0x119804)
VARPTR(D2CLIENT, FPS, DWORD, 0x11C2AC)
VARPTR(D2CLIENT, Skip, DWORD, 0x119810)
VARPTR(D2CLIENT, Divisor, int, 0xF16B0)

VARPTR(D2CLIENT, OverheadTrigger, DWORD, 0x113ACE)

VARPTR(D2CLIENT, RecentInteractId, DWORD, 0x11971D)

VARPTR(D2CLIENT, ItemPriceList, DWORD, 0x11973B)

VARPTR(D2CLIENT, TransactionDialog, void*, 0x11975B)
VARPTR(D2CLIENT, TransactionDialogs, DWORD, 0x11BC08)
VARPTR(D2CLIENT, TransactionDialogs_2, DWORD, 0x11BC04)

VARPTR(D2CLIENT, GameInfo, GameStructInfo*, 0x11B980)

VARPTR(D2CLIENT, WaypointTable, DWORD, 0xFCDD1)

VARPTR(D2CLIENT, PlayerUnit, UnitAny*, 0x11BBFC)
VARPTR(D2CLIENT, SelectedInvItem, UnitAny*, 0x11BC38)
//VARPTR(D2CLIENT, SelectedUnit, UnitAny*, 0x11C4D8) // unused, but can we use it somewhere maybe? // 1.12 still
VARPTR(D2CLIENT, PlayerUnitList, RosterUnit*, 0x11BC14)

VARPTR(D2CLIENT, bWeapSwitch, DWORD, 0x11BC94)

VARPTR(D2CLIENT, bTradeAccepted, DWORD, 0x11BE64)
VARPTR(D2CLIENT, bTradeBlock, DWORD, 0x11BE74)
VARPTR(D2CLIENT, RecentTradeName, wchar_t*, 0x12334C)
VARPTR(D2CLIENT, RecentTradeId, DWORD, 0x11C2CC)

VARPTR(D2CLIENT, ExpCharFlag, DWORD, 0x119854)

VARPTR(D2CLIENT, MapId, DWORD, 0x11C3BC) // unused but I want to add it

VARPTR(D2CLIENT, AlwaysRun, DWORD, 0x11C3EC)
VARPTR(D2CLIENT, NoPickUp, DWORD, 0x11C2F0) // unused but I want to add it

VARPTR(D2CLIENT, ScreenCovered, DWORD, 0x1E8F9) // unused, appears to be an int specifying which screens (if any) are opened...

VARPTR(D2CLIENT, ChatMsg, wchar_t*, 0x11EC80)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Client Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2CLIENT, TakeWaypoint_I, 0xAA8B3)

ASMPTR(D2CLIENT, ClickShopItem_I, 0x46EE0)
ASMPTR(D2CLIENT, ClickBelt_I, 0x28260)
ASMPTR(D2CLIENT, ClickBeltRight_I, 0x29990)
ASMPTR(D2CLIENT, ClickItemRight_I, 0x98B60)
ASMPTR(D2CLIENT, MercItemAction_I, 0x14A10)

ASMPTR(D2CLIENT, Interact_I, 0x1BDE0)

ASMPTR(D2CLIENT, ClickParty_I, 0x9E180)
ASMPTR(D2CLIENT, ClickParty_II, 0x773A0)

ASMPTR(D2CLIENT, ShopAction_I, 0x47D60)

ASMPTR(D2CLIENT, GetUnitName_I, 0xA5D90)
ASMPTR(D2CLIENT, GetItemDesc_I, 0x560B0)

ASMPTR(D2CLIENT, AssignPlayer_I, 0xA7630)

//ASMPTR(D2CLIENT, TestPvpFlag_I, 0x4FCE0)
ASMPTR(D2CLIENT, TestPvpFlag_I, 0x4FD90)

ASMPTR(D2CLIENT, PlaySound_I, 0x88A70)

ASMPTR(D2CLIENT, InputCall_I, 0x147A0)

ASMPTR(D2CLIENT, Say_I, 0x70EC6)

ASMPTR(D2CLIENT, BodyClickTable, 0xE0EC4)

ASMPTR(D2CLIENT, LoadUiImage_I, 0x2B420)

ASMPTR(D2CLIENT, GetMinionCount_I, 0x217E0)

ASMPTR(D2CLIENT, GameLeave_I, 0x5D110)

ASMPTR(D2CLIENT, ClickMap_I, 0xFADA4)
ASMPTR(D2CLIENT, ClickMap_II, 0x11C4D8)
ASMPTR(D2CLIENT, ClickMap_III, 0x3F5F0)
ASMPTR(D2CLIENT, ClickMap_IV, 0x1BF99)

ASMPTR(D2CLIENT, GameAddUnit_I, 0xA6500)

ASMPTR(D2CLIENT, LoadAct_1, 0x62AA0)
ASMPTR(D2CLIENT, LoadAct_2, 0x62760)

ASMPTR(D2CLIENT, GetUnitFromId_I, 0xA4E20)
VARPTR(D2CLIENT, pUnitTable, POINT, 0x10A608)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Common Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2COMMON, InitLevel, void __stdcall, (Level *pLevel), 0x2E360)
FUNCPTR(D2COMMON, UnloadAct, unsigned __stdcall, (Act* pAct), -10868)
FUNCPTR(D2COMMON, GetObjectTxt, ObjectTxt * __stdcall, (DWORD objno), 0x3E980)
FUNCPTR(D2COMMON, LoadAct, Act* __stdcall, (DWORD ActNumber, DWORD MapId, DWORD Unk, DWORD Unk_2, DWORD Unk_3, DWORD Unk_4, DWORD TownLevelId, DWORD Func_1, DWORD Func_2), 0x3CB30)

FUNCPTR(D2COMMON, GetLevelText, LevelText * __stdcall, (DWORD levelno), -10014)
FUNCPTR(D2COMMON, GetObjectText, ObjectTxt * __stdcall, (DWORD objno), -10688)
FUNCPTR(D2COMMON, GetItemText, ItemText *__stdcall, (DWORD dwItemNo), -10695)

FUNCPTR(D2COMMON, GetLayer, AutomapLayer2* __fastcall, (DWORD dwLevelNo), -10749)
FUNCPTR(D2COMMON, GetLevel, Level * __fastcall, (ActMisc *pMisc, DWORD dwLevelNo), -10207)

FUNCPTR(D2COMMON, GetStatList, StatList* __stdcall, (UnitAny* pUnit, DWORD dwUnk, DWORD dwMaxEntries ), -10930)
FUNCPTR(D2COMMON, CopyStatList, DWORD __stdcall, (StatList* pStatList, Stat* pStatArray, DWORD dwMaxEntries), -10658)
FUNCPTR(D2COMMON, GetUnitStat, DWORD __stdcall, (UnitAny* pUnit, DWORD dwStat, DWORD dwStat2), -10973)
FUNCPTR(D2COMMON, GetUnitState, int __stdcall, (UnitAny *pUnit, DWORD dwStateNo), -10494)

FUNCPTR(D2COMMON, CheckUnitCollision, DWORD __stdcall, (UnitAny* pUnitA, UnitAny* pUnitB, DWORD dwBitMask), -10839)
FUNCPTR(D2COMMON, GetRoomFromUnit,  Room1* __stdcall, (UnitAny * ptUnit), -10331)
FUNCPTR(D2COMMON, GetTargetUnitType, Path* __stdcall, (Path* pPath), -10392)

FUNCPTR(D2COMMON, GetSkillLevel, int __stdcall, (UnitAny* pUnit, Skill* pSkill, BOOL bTotal), -10306)

FUNCPTR(D2COMMON, GetItemLevelRequirement, DWORD __stdcall, (UnitAny* pItem, UnitAny* pPlayer), -11015)
FUNCPTR(D2COMMON, GetItemPrice, DWORD __stdcall, (UnitAny* MyUnit, UnitAny* pItem, DWORD U1_,DWORD U2_,DWORD U3_,DWORD U4_), -10107)
FUNCPTR(D2COMMON, GetRepairCost, DWORD __stdcall, (DWORD _1, UnitAny* pUnit, DWORD dwNpcId, DWORD dwDifficulty, DWORD dwItemPriceList, DWORD _2), -10071)
FUNCPTR(D2COMMON, GetItemMagicalMods, char* __stdcall, (WORD wPrefixNum), -10248)
FUNCPTR(D2COMMON, GetItemFromInventory, UnitAny *__stdcall, (Inventory* inv), -10460)
FUNCPTR(D2COMMON, GetNextItemFromInventory, UnitAny *__stdcall, (UnitAny *pItem), -10464)

FUNCPTR(D2COMMON, GenerateOverheadMsg, OverheadMsg* __stdcall, (DWORD dwUnk, char* szMsg, DWORD dwTrigger), -10454)
FUNCPTR(D2COMMON, FixOverheadMsg, void __stdcall, (OverheadMsg* pMsg, DWORD dwUnk), -10097)

FUNCPTR(D2COMMON, AddRoomData, void __stdcall, (Act * ptAct, int LevelId, int Xpos, int Ypos, Room1 * pRoom), -10401)
FUNCPTR(D2COMMON, RemoveRoomData, void __stdcall, (Act* ptAct, int LevelId, int Xpos, int Ypos, Room1* pRoom), -11099)

FUNCPTR(D2COMMON, GetQuestFlag, int __stdcall, (void* QuestInfo, DWORD dwAct, DWORD dwQuest), -10174)

FUNCPTR(D2COMMON, AbsScreenToMap, void __stdcall, (long *pX, long *pY), -10474)
FUNCPTR(D2COMMON, MapToAbsScreen, void __stdcall, (long *pX, long *pY), -11087)

FUNCPTR(D2COMMON, CheckWaypoint, DWORD __stdcall, (DWORD WaypointTable, DWORD dwLevelId), -10373)

FUNCPTR(D2COMMON, IsTownByLevelNo, BOOL __stdcall, (DWORD dwLevelNo), -10416)
FUNCPTR(D2COMMON, IsTownByRoom, BOOL __stdcall, (Room1* pRoom1), -10057)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Common Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2COMMON, sgptDataTable, DWORD, 0x99E1C)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Common Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2COMMON, DisplayOverheadMsg_I, -10422)
ASMPTR(D2COMMON, GetLevelIdFromRoom_I, 0x3C000)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Net Functions
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2NET, SendPacket, void __stdcall, (size_t aLen, DWORD arg1, BYTE* aPacket), -10024)
FUNCPTR(D2NET, ReceivePacket_I, void __stdcall, (BYTE *aPacket, DWORD aLen), -10033)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Net Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2NET, CriticalPacketSection, CRITICAL_SECTION, 0xB400) // unused but we need to use it


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Gfx Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2GFX, DrawLine, void __stdcall, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwUnk), -10010)
FUNCPTR(D2GFX, DrawRectangle, void __stdcall, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwTrans), -10014)
FUNCPTR(D2GFX, DrawAutomapCell2, void __stdcall, (CellContext* context, DWORD xpos, DWORD ypos, DWORD bright2, DWORD bright, BYTE *coltab), -10041)

FUNCPTR(D2GFX, GetScreenSize, DWORD __stdcall, (void), -10031) 

FUNCPTR(D2GFX, GetHwnd, HWND __stdcall, (void), -10048)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Multi Functions
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2MULTI, DoChat, void __fastcall, (void), 0xCB30)
FUNCPTR(D2MULTI, PrintChannelText, void __stdcall, (char *szText, DWORD dwColor),  0xFC90)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Multi Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2MULTI, ChatBoxMsg, char*, 0x38F18)
VARPTR(D2MULTI, GameListControl, Control*, 0x39CC0)//1.13c - Unchanged
VARPTR(D2MULTI, EditboxPreferences, ControlPreferences*, 0x19C60)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Multi Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2MULTI, ChannelChat_I, 0x108A6)
ASMPTR(D2MULTI, ChannelEmote_I, 0x107A6)
ASMPTR(D2MULTI, ChannelWhisper_I, 0x10000)
ASMPTR(D2MULTI, ChannelInput_I, 0xD5B0)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Cmp Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2CMP, InitCellFile, void __stdcall, (void *cellfile, CellFile **outptr, char *srcfile, DWORD lineno, DWORD filever, char *filename), -10006)
FUNCPTR(D2CMP, DeleteCellFile, void __stdcall, (CellFile *cellfile), -10106)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Lang Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2LANG, GetLocaleText, wchar_t* __fastcall, (WORD nLocaleTxtNo), -10003)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Lang Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2LANG, Say_II, 0xB0B0)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Launch Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2LAUNCH, BnData, BnetData *, 0x25ABC)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Win Functions
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2WIN, SetControlText, void* __fastcall, (DWORD* box, wchar_t* txt), -10042)
FUNCPTR(D2WIN, DrawSprites, void __fastcall, (void), 0x18750)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Win Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2WIN, DrawText, void __fastcall, (const wchar_t *wStr, int xPos, int yPos, DWORD dwColor, DWORD dwUnk), -10150)

FUNCPTR(D2WIN, GetTextSize, DWORD __fastcall, (wchar_t *wStr, DWORD* dwWidth, DWORD* dwFileNo), -10177)
FUNCPTR(D2WIN, SetTextSize, DWORD __fastcall, (DWORD dwSize), -10184)

FUNCPTR(D2WIN, SetControlText, void* __fastcall, (Control* box, wchar_t* txt), -10042)
FUNCPTR(D2WIN, GetTextWidthFileNo, DWORD __fastcall, (wchar_t *wStr, DWORD* dwWidth, DWORD* dwFileNo), -10177)

FUNCPTR(D2WIN, CreateEditBox, Control* __fastcall, (DWORD dwPosX, DWORD dwPosY, DWORD _1, DWORD _2, DWORD _3, DWORD _4, DWORD _5, BOOL (__stdcall *pCallback)(wchar_t* wText), DWORD _6, DWORD _7, ControlPreferences* pPreferences), 0x161B0)//1.13c
FUNCPTR(D2WIN, DestroyEditBox, VOID __fastcall, (Control* pControl), 0x159E0)//1.13c
FUNCPTR(D2WIN, DestroyControl, VOID __stdcall, (Control* pControl), 0x18490)//1.13c
FUNCPTR(D2WIN, SetEditBoxCallback, VOID __fastcall, (Control* pControl, BOOL (__stdcall *FunCallBack)(Control* pControl, DWORD dwInputType, char* pChar)), 0x13970)//1.13c
FUNCPTR(D2WIN, SetEditBoxProc, void __fastcall, (Control* box, BOOL (__stdcall *FunCallBack)(Control*,DWORD,DWORD)), 0x13970)//Updated 1.13c
FUNCPTR(D2WIN, SelectEditBoxText, void __fastcall, (Control* box), 0x7708) //Updated 1.13c
FUNCPTR(D2WIN, InitMPQ, DWORD __stdcall, (char *dll,const char *mpqfile, char *mpqname, int v4, int v5), 0x7E60)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Win Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2WIN, FirstControl, Control*, 0x214A0)
VARPTR(D2WIN, FocusedControl, Control*, 0x214B0) // unused, but we ought to use it
VARPTR(D2WIN, ChatInputBox, DWORD*, 0x12A0D0)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Game Functions
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2GAME, Rand, DWORD __fastcall, (DWORD* seed), 0x1160)

FUNCPTR(D2MCPCLIENT, ParseGameListPacket, VOID __fastcall, (BYTE* pPacket), 0x6E30)
*/

FUNCPTR(D2CLIENT, GetQuestInfo, void* __stdcall, (void), 0x78A80)

FUNCPTR(D2CLIENT, SubmitItem, void __fastcall, (DWORD dwItemId), 0x79670)
FUNCPTR(D2CLIENT, Transmute, void __fastcall, (void), 0x94370)

FUNCPTR(D2CLIENT, FindClientSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0x620B0)
FUNCPTR(D2CLIENT, FindServerSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0x620D0)
FUNCPTR(D2CLIENT, GetCurrentInteractingNPC, UnitAny* __fastcall, (void), 0x790D0)
FUNCPTR(D2CLIENT, GetSelectedUnit, UnitAny * __stdcall, (void), 0x17280)
FUNCPTR(D2CLIENT, GetCursorItem, UnitAny* __fastcall, (void), 0x144A0)
FUNCPTR(D2CLIENT, GetMercUnit, UnitAny* __fastcall, (void), 0x9C0A0)
//FUNCPTR(D2CLIENT, UnitTestSelect, DWORD __stdcall, (UnitAny* pUnit, DWORD _1, DWORD _2, DWORD _3), 0x8D030) // unused but we need to use it

FUNCPTR(D2CLIENT, SetSelectedUnit_I, void __fastcall, (UnitAny *pUnit), 0x17060)
FUNCPTR(D2CLIENT, GetItemName, BOOL __stdcall, (UnitAny* pItem, wchar_t* wBuffer, DWORD dwSize), 0x958C0)
FUNCPTR(D2CLIENT, GetMonsterOwner, DWORD __fastcall, (DWORD nMonsterId), 0x8E3D0)
FUNCPTR(D2CLIENT, GetUnitHPPercent, DWORD __fastcall, (DWORD dwUnitId), 0x8E2B0)
FUNCPTR(D2CLIENT, InitInventory, void __fastcall, (void), 0x93280)
FUNCPTR(D2CLIENT, SetUIVar, DWORD __fastcall, (DWORD varno, DWORD howset, DWORD unknown1), 0x1C190) 
FUNCPTR(D2CLIENT, GetUnitX, int __fastcall, (UnitAny* pUnit), 0x1210)
FUNCPTR(D2CLIENT, GetUnitY, int __fastcall, (UnitAny* pUnit), 0x1240)

FUNCPTR(D2CLIENT, ShopAction, void __fastcall, (UnitAny* pItem, UnitAny* pNpc, UnitAny* pNpc2, DWORD dwSell, DWORD dwItemCost, DWORD dwMode, DWORD _2, DWORD _3), 0x7D030)

FUNCPTR(D2CLIENT, CloseNPCInteract, void __fastcall, (void), 0x7BC10)
//FUNCPTR(D2CLIENT, ClearScreen, void __fastcall, (void), 0x492F0) // unused but I want to look into using it // wrong function
FUNCPTR(D2CLIENT, CloseInteract, void __fastcall, (void), 0x44980)

FUNCPTR(D2CLIENT, GetAutomapSize, DWORD __stdcall, (void), 0x6FDD0)
FUNCPTR(D2CLIENT, NewAutomapCell, AutomapCell * __fastcall, (void), 0x703C0)
FUNCPTR(D2CLIENT, AddAutomapCell, void __fastcall, (AutomapCell *aCell, AutomapCell **node), 0x71EA0)
FUNCPTR(D2CLIENT, RevealAutomapRoom, void __stdcall, (Room1 *pRoom1, DWORD dwClipFlag, AutomapLayer *aLayer), 0x73160)
FUNCPTR(D2CLIENT, InitAutomapLayer_I, AutomapLayer* __fastcall, (DWORD nLayerNo), 0x733D0)

FUNCPTR(D2CLIENT, ClickMap, void __stdcall, (DWORD MouseFlag, DWORD x, DWORD y, DWORD Type), 0x2B420)
FUNCPTR(D2CLIENT, LeftClickItem, void __stdcall, (UnitAny* pPlayer, Inventory* pInventory, int x, int y, DWORD dwClickType, InventoryLayout* pLayout, DWORD Location), 0x9AFF0)

FUNCPTR(D2CLIENT, GetMouseXOffset, DWORD __fastcall, (void), 0x5BC20)
FUNCPTR(D2CLIENT, GetMouseYOffset, DWORD __fastcall, (void), 0x5BC30)

FUNCPTR(D2CLIENT, PrintPartyString, void __stdcall, (wchar_t *wMessage, int nColor), 0x75C70) // unused but I want to look into using it too
FUNCPTR(D2CLIENT, PrintGameString, void __stdcall, (wchar_t *wMessage, int nColor), 0x75EB0)

FUNCPTR(D2CLIENT, ResizeDiablo, int __stdcall, (), 0x3D360) //HDD2
FUNCPTR(D2WIN, SetResolutionMode, int __stdcall, (int), 0xDDB0) //HDD2

FUNCPTR(D2CLIENT, LeaveParty, void __fastcall, (void), 0xA26A0)

FUNCPTR(D2CLIENT, AcceptTrade, void __fastcall, (void), 0x11F70)
FUNCPTR(D2CLIENT, CancelTrade, void __fastcall, (void), 0x11F30)

FUNCPTR(D2CLIENT, GetDifficulty, BYTE __stdcall, (void), 0x42980)

FUNCPTR(D2CLIENT, ExitGame, void __fastcall, (void), 0x43870)

FUNCPTR(D2CLIENT, GetUiVar_I, DWORD __fastcall, (DWORD dwVarNo), 0x17C50)

FUNCPTR(D2CLIENT, DrawRectFrame, void __fastcall, (DWORD Rect), 0x17D10)

FUNCPTR(D2CLIENT, PerformGoldDialogAction, void __fastcall, (void), 0x197F0)

FUNCPTR(D2CLIENT, GetPlayerUnit, UnitAny* __stdcall, (void), 0x613C0)

FUNCPTR(D2CLIENT, GetLevelName_I, wchar_t* __fastcall, (DWORD levelId), 0x18250)

FUNCPTR(D2CLIENT, ClearScreen, void __fastcall, (void), 0x7AB80)

FUNCPTR(D2CLIENT, CloseNPCTalk, DWORD __stdcall, (void* unk), 0x77AB0)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Client Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2CLIENT, ScreenSizeX, DWORD, 0xF7034)
VARPTR(D2CLIENT, ScreenSizeY, DWORD, 0xF7038)

VARPTR(D2CLIENT, CropMode, DWORD, 0x11D070) //HDD2
VARPTR(D2CLIENT, MapPosX, DWORD, 0x123D64) //HDD2
VARPTR(D2CLIENT, MapPosY, DWORD, 0x123D60) //HDD2
VARPTR(D2CLIENT, SizeX1, DWORD, 0x11CF94) //HDD2
VARPTR(D2CLIENT, SizeY1, DWORD, 0x11CF98) //HDD2
VARPTR(D2CLIENT, SizeX2, DWORD, 0xF703C) //HDD2

VARPTR(D2CLIENT, CursorHoverX, DWORD, 0xEE4AC)
VARPTR(D2CLIENT, CursorHoverY, DWORD, 0xEE4B0)

VARPTR(D2CLIENT, MouseX, DWORD, 0x11C950)
VARPTR(D2CLIENT, MouseY, DWORD, 0x11C94C)

VARPTR(D2CLIENT, MouseOffsetY, int, 0x106840)
VARPTR(D2CLIENT, MouseOffsetX, int, 0x106844)

VARPTR(D2CLIENT, AutomapOn, DWORD, 0x11C8B8)
VARPTR(D2CLIENT, AutomapMode, int, 0xF34F8)
VARPTR(D2CLIENT, Offset, POINT, 0x11CF5C)
VARPTR(D2CLIENT, AutomapLayer, AutomapLayer*, 0x11CF28)

VARPTR(D2CLIENT, xShake, int, 0x11CA6C) //ScreenShake
VARPTR(D2CLIENT, yShake, int, 0xFC3DC) //ScreenShake

VARPTR(D2CLIENT, MercStrIndex, WORD, 0xF02D8)
VARPTR(D2CLIENT, MercReviveCost, DWORD, 0x11CEE8)

VARPTR(D2CLIENT, ViewportY, int, 0x106840)
VARPTR(D2CLIENT, ViewportX, int, 0x106844)

VARPTR(D2CLIENT, GoldDialogAction, DWORD, 0x11C86C)
VARPTR(D2CLIENT, GoldDialogAmount, DWORD, 0x11D568)

VARPTR(D2CLIENT, NPCMenu, NPCMenu*, 0xF1A90)
VARPTR(D2CLIENT, NPCMenuAmount, DWORD, 0xF21E0)

VARPTR(D2CLIENT, TradeLayout, InventoryLayout*, 0x101598)
VARPTR(D2CLIENT, StashLayout, InventoryLayout*, 0x1015E0)
VARPTR(D2CLIENT, StoreLayout, InventoryLayout*, 0x1016C0)
VARPTR(D2CLIENT, CubeLayout, InventoryLayout*, 0x1016D8)
VARPTR(D2CLIENT, InventoryLayout, InventoryLayout*, 0x1016F0)
VARPTR(D2CLIENT, MercLayout, InventoryLayout*, 0x11CC84)

ASMPTR(D2CLIENT, clickParty_I, 0xA2250)

VARPTR(D2CLIENT, RegularCursorType, DWORD, 0x11C98C)
VARPTR(D2CLIENT, ShopCursorType, DWORD, 0x11CB24)


VARPTR(D2CLIENT, Ping, DWORD, 0x108764)
VARPTR(D2CLIENT, FPS, DWORD, 0x11CE10)
VARPTR(D2CLIENT, Skip, DWORD, 0x108770)
VARPTR(D2CLIENT, Divisor, int, 0xF34F8)

VARPTR(D2CLIENT, OverheadTrigger, DWORD, 0x101ABE)

VARPTR(D2CLIENT, RecentInteractId, DWORD, 0x101895)

VARPTR(D2CLIENT, ItemPriceList, DWORD, 0x1018B3)

VARPTR(D2CLIENT, TransactionDialog, void*, 0x1018D3)
VARPTR(D2CLIENT, TransactionDialogs, DWORD, 0x11D58C)
VARPTR(D2CLIENT, TransactionDialogs_2, DWORD, 0x11D588)

VARPTR(D2CLIENT, GameInfo, GameStructInfo*, 0x109738)

VARPTR(D2CLIENT, WaypointTable, DWORD, 0x1088FD)

VARPTR(D2CLIENT, PlayerUnit, UnitAny*, 0x11D050)
VARPTR(D2CLIENT, SelectedInvItem, UnitAny*, 0x11CB28)
//VARPTR(D2CLIENT, SelectedUnit, UnitAny*, 0x11C4D8) // unused, but can we use it somewhere maybe? // 1.12 still
VARPTR(D2CLIENT, PlayerUnitList, RosterUnit*, 0x11CB04)

VARPTR(D2CLIENT, bWeapSwitch, DWORD, 0x11CB84)

VARPTR(D2CLIENT, bTradeAccepted, DWORD, 0x11CD54)
VARPTR(D2CLIENT, bTradeBlock, DWORD, 0x11CD64)

//VARPTR(D2CLIENT, RecentTradeName, wchar_t*, 0x12334C)
VARPTR(D2CLIENT, RecentTradeId, DWORD, 0x11D5AC)

VARPTR(D2CLIENT, ExpCharFlag, DWORD, 0x1087B4)

VARPTR(D2CLIENT, MapId, DWORD, 0x11D204) // unused but I want to add it

VARPTR(D2CLIENT, AlwaysRun, DWORD, 0x11D234)
VARPTR(D2CLIENT, NoPickUp, DWORD, 0x11D574) // unused but I want to add it

//VARPTR(D2CLIENT, ScreenCovered, DWORD, 0x1E8F9) // unused, appears to be an int specifying which screens (if any) are opened...

VARPTR(D2CLIENT, ChatMsg, wchar_t*, 0x11D650)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Client Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2CLIENT, TakeWaypoint_I, 0x3F5F3)

ASMPTR(D2CLIENT, ClickShopItem_I, 0x7A180)
ASMPTR(D2CLIENT, ClickBelt_I, 0x6E310)
ASMPTR(D2CLIENT, ClickBeltRight_I, 0x6FA40)
ASMPTR(D2CLIENT, ClickItemRight_I, 0x9CF30)
ASMPTR(D2CLIENT, MercItemAction_I, 0xB6B00)

ASMPTR(D2CLIENT, Interact_I, 0x2B2E0)

ASMPTR(D2CLIENT, ClickParty_I, 0xA2250)
ASMPTR(D2CLIENT, ClickParty_II, 0x88A50)

ASMPTR(D2CLIENT, ShopAction_I, 0x7D030)

ASMPTR(D2CLIENT, GetUnitName_I, 0x622E0)
ASMPTR(D2CLIENT, GetItemDesc_I, 0x2E380)

ASMPTR(D2CLIENT, AssignPlayer_I, 0x63C70)

ASMPTR(D2CLIENT, TestPvpFlag_I, 0x6A720)

ASMPTR(D2CLIENT, InputCall_I, 0xB6890)

ASMPTR(D2CLIENT, Say_I, 0xB27A6)

ASMPTR(D2CLIENT, BodyClickTable, 0xEE4B8)

ASMPTR(D2CLIENT, LoadUiImage_I, 0xA9480)

ASMPTR(D2CLIENT, GetMinionCount_I, 0x8E5B0)

ASMPTR(D2CLIENT, GameLeave_I, 0xB4370)

ASMPTR(D2CLIENT, ClickMap_I, 0x11C8B4)
ASMPTR(D2CLIENT, ClickMap_II, 0x11D2CC)
ASMPTR(D2CLIENT, ClickMap_III, 0x5BB50)
ASMPTR(D2CLIENT, ClickMap_IV, 0x2B499)

ASMPTR(D2CLIENT, GameAddUnit_I, 0x628E0)

ASMPTR(D2CLIENT, LoadAct_1, 0x737F0)
ASMPTR(D2CLIENT, LoadAct_2, 0x2B420)

ASMPTR(D2CLIENT, GetUnitFromId_I, 0x61480)
VARPTR(D2CLIENT, pUnitTable, POINT, 0x1047B8)

ASMPTR(D2CLIENT, OverrideShrinePatch_ORIG, 0x101B08)

ASMPTR(D2CLIENT, SendGamePacket_I, 0xB61F0)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Common Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2COMMON, InitLevel, void __stdcall, (Level *pLevel), 0x6DDF0)
FUNCPTR(D2COMMON, UnloadAct, unsigned __stdcall, (Act* pAct), 0x24590)
FUNCPTR(D2COMMON, GetObjectTxt, ObjectTxt * __stdcall, (DWORD objno), 0x1ADC0)
FUNCPTR(D2COMMON, LoadAct, Act* __stdcall, (DWORD ActNumber, DWORD MapId, DWORD Unk, DWORD Unk_2, DWORD Unk_3, DWORD Unk_4, DWORD TownLevelId, DWORD Func_1, DWORD Func_2), 0x24810)

FUNCPTR(D2COMMON, GetLevelText, LevelText * __stdcall, (DWORD levelno), 0x30CA0)
FUNCPTR(D2COMMON, GetObjectText, ObjectTxt * __stdcall, (DWORD objno), 0x1ADC0)
FUNCPTR(D2COMMON, GetItemText, ItemText *__stdcall, (DWORD dwItemNo), 0x62C70)

FUNCPTR(D2COMMON, GetLayer, AutomapLayer2* __fastcall, (DWORD dwLevelNo), 0x30B00)
FUNCPTR(D2COMMON, GetLevel, Level * __fastcall, (ActMisc *pMisc, DWORD dwLevelNo), 0x6D440)

FUNCPTR(D2COMMON, GetStatList, StatList* __stdcall, (UnitAny* pUnit, DWORD dwUnk, DWORD dwMaxEntries ), 0x57830)
FUNCPTR(D2COMMON, CopyStatList, DWORD __stdcall, (StatList* pStatList, Stat* pStatArray, DWORD dwMaxEntries), 0x57D30)
FUNCPTR(D2COMMON, GetUnitStat, DWORD __stdcall, (UnitAny* pUnit, DWORD dwStat, DWORD dwStat2), 0x584E0)
FUNCPTR(D2COMMON, GetUnitState, int __stdcall, (UnitAny *pUnit, DWORD dwStateNo), 0x2F310)

FUNCPTR(D2COMMON, CheckUnitCollision, DWORD __stdcall, (UnitAny* pUnitA, UnitAny* pUnitB, DWORD dwBitMask), 0x17CF0)
FUNCPTR(D2COMMON, GetRoomFromUnit,  Room1* __stdcall, (UnitAny * ptUnit), 0x16530)
FUNCPTR(D2COMMON, GetTargetUnitType, Path* __stdcall, (Path* pPath), 0x773C0)

FUNCPTR(D2COMMON, GetSkillLevel, int __stdcall, (UnitAny* pUnit, Skill* pSkill, BOOL bTotal), 0x73D60)

FUNCPTR(D2COMMON, GetItemLevelRequirement, DWORD __stdcall, (UnitAny* pItem, UnitAny* pPlayer), 0x45660)

FUNCPTR(D2COMMON, GetItemPrice, DWORD __stdcall, (UnitAny* MyUnit, UnitAny* pItem, DWORD U1_,DWORD U2_,DWORD U3_,DWORD U4_), 0x48620)
FUNCPTR(D2COMMON, GetRepairCost, DWORD __stdcall, (DWORD _1, UnitAny* pUnit, DWORD dwNpcId, DWORD dwDifficulty, DWORD dwItemPriceList, DWORD _2), 0x48AD0)
FUNCPTR(D2COMMON, GetItemMagicalMods, char* __stdcall, (WORD wPrefixNum), 0x62AF0)
FUNCPTR(D2COMMON, GetItemFromInventory, UnitAny *__stdcall, (Inventory* inv), 0x37520)
FUNCPTR(D2COMMON, GetNextItemFromInventory, UnitAny *__stdcall, (UnitAny *pItem), 0x38160)

FUNCPTR(D2COMMON, GenerateOverheadMsg, OverheadMsg* __stdcall, (DWORD dwUnk, char* szMsg, DWORD dwTrigger), 0x4DD10)
FUNCPTR(D2COMMON, FixOverheadMsg, void __stdcall, (OverheadMsg* pMsg, DWORD dwUnk), 0x4DC70)

FUNCPTR(D2COMMON, AddRoomData, void __stdcall, (Act * ptAct, int LevelId, int Xpos, int Ypos, Room1 * pRoom), 0x24990)
FUNCPTR(D2COMMON, RemoveRoomData, void __stdcall, (Act* ptAct, int LevelId, int Xpos, int Ypos, Room1* pRoom), 0x24930)

FUNCPTR(D2COMMON, GetQuestFlag, int __stdcall, (void* QuestInfo, DWORD dwAct, DWORD dwQuest), 0x2D7A0)

FUNCPTR(D2COMMON, AbsScreenToMap, void __stdcall, (long *pX, long *pY), 0x35810)
FUNCPTR(D2COMMON, MapToAbsScreen, void __stdcall, (long *pX, long *pY), 0x35AA0)

FUNCPTR(D2COMMON, CheckWaypoint, DWORD __stdcall, (DWORD WaypointTable, DWORD dwLevelId), 0x5D270)

FUNCPTR(D2COMMON, IsTownByLevelNo, BOOL __stdcall, (DWORD dwLevelNo), 0x23950)
FUNCPTR(D2COMMON, IsTownByRoom, BOOL __stdcall, (Room1* pRoom1), 0x23B80)

FUNCPTR(D2COMMON, GetClosestUnit, UnitAny* __stdcall, (UnitAny* A, int x, int y, int maxdist, int (__fastcall *UnitCallback) (UnitAny*, UnitAny*)), -10680)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Common Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2COMMON, sgptDataTable, DWORD, 0xA33F0)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Common Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2COMMON, DisplayOverheadMsg_I, 0x4DCF0)
ASMPTR(D2COMMON, GetLevelIdFromRoom_I, 0x23B80)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Net Functions
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2NET, SendPacket, void __stdcall, (size_t aLen, DWORD arg1, BYTE* aPacket), 0x6F20)
FUNCPTR(D2NET, ReceivePacket_I, void __stdcall, (BYTE *aPacket, DWORD aLen), 0x6020)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Net Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2NET, CriticalPacketSection, CRITICAL_SECTION, 0xB400) // unused but we need to use it

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Gfx Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2GFX, DrawLine, void __stdcall, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwUnk), 0x81A0)
FUNCPTR(D2GFX, DrawRectangle, void __stdcall, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwTrans), 0x8210)
FUNCPTR(D2GFX, DrawAutomapCell2, void __stdcall, (CellContext* context, DWORD xpos, DWORD ypos, DWORD bright2, DWORD bright, BYTE *coltab), 0x7E60)

FUNCPTR(D2GFX, GetScreenSize, DWORD __stdcall, (void), 0xA940) 

FUNCPTR(D2GFX, GetHwnd, HWND __stdcall, (void), 0xB0C0)
FUNCPTR(D2GFX, DrawAutomapCell, void __stdcall, (CellContext *context, DWORD xpos, DWORD ypos, RECT *cliprect, DWORD bright), 0x7C80)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Multi Functions
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2MULTI, DoChat, void __fastcall, (void), 0x11770)
FUNCPTR(D2MULTI, PrintChannelText, void __stdcall, (char *szText, DWORD dwColor),  0x13F30)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Multi Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2MULTI, ChatBoxMsg, char*, 0x1C150)
VARPTR(D2MULTI, GameListControl, Control*, 0x39FF0)//1.13c - Unchanged

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Multi Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2MULTI, ChannelChat_I, 0x14BE6)
ASMPTR(D2MULTI, ChannelEmote_I, 0x14850)
ASMPTR(D2MULTI, ChannelWhisper_I, 0x142F0)
ASMPTR(D2MULTI, ChannelInput_I, 0x11B80)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Cmp Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2CMP, InitCellFile, void __stdcall, (void *cellfile, CellFile **outptr, char *srcfile, DWORD lineno, DWORD filever, char *filename), 0x13B50)
FUNCPTR(D2CMP, DeleteCellFile, void __stdcall, (CellFile *cellfile), 0x99B0)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Lang Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2LANG, GetLocaleText, wchar_t* __fastcall, (WORD nLocaleTxtNo), 0x98A0)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Lang Stubs
////////////////////////////////////////////////////////////////////////////////////////////////

ASMPTR(D2LANG, Say_II, 0x8C60)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Launch Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2LAUNCH, BnData, BnetData *, 0x25B30)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Win Functions
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2WIN, SetControlText, void* __fastcall, (Control* box, wchar_t* txt), 0x10680)
FUNCPTR(D2WIN, DrawSprites, void __fastcall, (void), 0xEAA0)


////////////////////////////////////////////////////////////////////////////////////////////////
// D2Win Ordinals
////////////////////////////////////////////////////////////////////////////////////////////////

FUNCPTR(D2WIN, TakeScreenshot, void __fastcall, (), 0xDF70)

FUNCPTR(D2WIN, DrawText, void __fastcall, (const wchar_t *wStr, int xPos, int yPos, DWORD dwColor, DWORD dwUnk), 0x13B30)

FUNCPTR(D2WIN, GetTextSize, DWORD __fastcall, (wchar_t *wStr, DWORD* dwWidth, DWORD* dwFileNo), 0x13290)
FUNCPTR(D2WIN, SetTextSize, DWORD __fastcall, (DWORD dwSize), 0x13B70)
FUNCPTR(D2WIN, GetTextWidthFileNo, DWORD __fastcall, (wchar_t *wStr, DWORD* dwWidth, DWORD* dwFileNo), 0x13290)

FUNCPTR(D2WIN, DestroyEditBox, VOID __fastcall, (Control* pControl), 0xF320)//1.13c
FUNCPTR(D2WIN, DestroyControl, VOID __stdcall, (Control* pControl), 0xE5F0)//1.13c

FUNCPTR(D2WIN, SetEditBoxCallback, VOID __fastcall, (Control* pControl, BOOL (__stdcall *FunCallBack)(Control* pControl, DWORD dwInputType, char* pChar)), 0xF1D0)//1.13c
FUNCPTR(D2WIN, SetEditBoxProc, void __fastcall, (Control* box, BOOL (__stdcall *FunCallBack)(Control*,DWORD,DWORD)), 0xF1D0)//1.13c
FUNCPTR(D2WIN, SelectEditBoxText, void __fastcall, (Control* box), 0xEF80) //Updated 1.13c

FUNCPTR(D2WIN, InitMPQ, DWORD __stdcall, (char *dll,const char *mpqfile, char *mpqname, int v4, int v5), 0x7E50)

////////////////////////////////////////////////////////////////////////////////////////////////
// D2Win Globals
////////////////////////////////////////////////////////////////////////////////////////////////

VARPTR(D2WIN, FirstControl, Control*, 0x8DB34)
VARPTR(D2WIN, FocusedControl, Control*, 0x8DB44) // unused, but we ought to use it
VARPTR(D2MULTI, ChatInputBox, DWORD*, 0x3A0B0)

VARPTR(BNCLIENT, ClassicKey, char*, 0x1E928)
VARPTR(BNCLIENT, XPacKey, char*, 0x1E930)
VARPTR(BNCLIENT, KeyOwner, char*, 0x1E934)
FUNCPTR(BNCLIENT, DecodeAndLoadKeys, char __cdecl, (), 0x15D10)


FUNCPTR(D2MCPCLIENT, ParseGameListPacket, VOID __fastcall, (BYTE* pPacket), 0x6640)

VARPTR(D2MULTI, EditboxPreferences, ControlPreferences*, 0x19C60)
FUNCPTR(D2WIN, CreateEditBox, Control* __fastcall, (DWORD dwPosX, DWORD dwPosY, DWORD _1, DWORD _2, DWORD _3, DWORD _4, DWORD _5, BOOL (__stdcall *pCallback)(wchar_t* wText), DWORD _6, DWORD _7, ControlPreferences* pPreferences), 0x11A10)//1.13d

#undef FUNCPTR
#undef ASMPTR
#undef VARPTR

#define D2CLIENT_TestPvpFlag(dwId1, dwId2, dwFlag)	(TestPvpFlag_STUB(dwId1, dwId2, dwFlag))
#define D2CLIENT_GetUnitName(x)				(wchar_t*)D2CLIENT_GetUnitName_STUB((DWORD)x)
#define GetUnitFromId(unitid, unittype)		((UnitAny *)D2CLIENT_GetUnitFromId_STUB(unitid, unittype))
#define D2CLIENT_GetLevelName(LevelId) (wchar_t*)D2CLIENT_GetLevelName_STUB(LevelId)
#define D2CLIENT_GetUIState(dwVarNo)					(D2CLIENT_GetUIVar_STUB(dwVarNo))
#define D2CLIENT_ClickParty(RosterUnit, Mode)		(D2CLIENT_ClickParty_ASM(RosterUnit, Mode))