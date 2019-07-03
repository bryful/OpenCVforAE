/*
	RotScale

	各種定数を設定

	PiPLリソースに使う為にマクロ展開は最低限

*/


#pragma once
#ifndef RotScale_Target_H
#define RotScale_Target_H


#define DESCRIPTION		"RotScale Effect Filter"

#define NAME			"RotScale"
#define MATCH_NAME		NAME
#define CATEGORY		"OpenCV"


//#define SUPPORT_SMARTFX			//これを有効にするとSmartFX+Float_Colorに対応する

#define MAJOR_VERSION	1
#define MINOR_VERSION	0
#define BUG_VERSION		0
#define STAGE_VERSION	0
#define BUILD_VERSION	0

#define VERSION 524288


//value:4 [PF_OutFlag_NON_PARAM_VARY] 全フレームで描画
//value:64 [PF_OutFlag_USE_OUTPUT_EXTENT] 表示画面全部
//value:33554432[PF_OutFlag_DEEP_COLOR_AWARE] 16bit
//#define AE_OUT_FLAGS	33554500	//こっちにすると全フレーム描画する

//value:64 [PF_OutFlag_USE_OUTPUT_EXTENT] 表示画面全部
//value:33554432[PF_OutFlag_DEEP_COLOR_AWARE] 16bit
#define AE_OUT_FLAGS	33554496



#if defined(SUPPORT_SMARTFX)
//value:8 [PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG] グループ
//value:1024 [PF_OutFlag2_SUPPORTS_SMART_RENDER] スマートレンダー
//value:4096 [PF_OutFlag2_FLOAT_COLOR_AWARE] 32bit
#define AE_OUT_FLAGS2	5128

#else
//value : 8[PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG]
#define AE_OUT_FLAGS2	8
#endif

#endif // RotScale_Target_H

