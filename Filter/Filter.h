
#pragma once
#ifndef Filter_H
#define Filter_H


//各種ヘッダー登録
#include "AEConfig.h"
#include "entry.h"
#include "AEFX_SuiteHelper.h"
#include "PrSDKAESupport.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_EffectCBSuites.h"
#include "AE_Macros.h"
#include "AEGP_SuiteHandler.h"
#include "String_Utils.h"
#include "Param_Utils.h"
#include "Smart_Utils.h"

#ifdef AE_OS_WIN
	#include <Windows.h>
#endif

//OpenCVのヘッダー
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

//定数定義ヘッダー
#include "Filter_Target.h"

//CAEクラスの読み込み
#include "..\Lib\CAE.h"
#include "..\Lib\CAEcv.h"
#include "..\Lib\FsUtils.h"


enum {
	ID_INPUT = 0,

	ID_MAX,
	ID_BLUR,
	ID_BLEND_MODE,
	ID_OPACITY,

	ID_NUM_PARAMS
};

enum BLEND_MODE
{
	Normal=1,
	Lighten,
	screen,
	add

};

#define STR_MAX			"max"
#define STR_BLUR		"blur"
#define STR_BLEND		"blend"
#define STR_BLEND_ITEMS	"normal|lighten|screen|add"
#define STR_BLEND_COUNT	4
#define STR_BLEND_DFLT	1
#define STR_OPACITY		"opacity"


typedef struct ParamInfo {
	A_long			max;
	A_long			blur;
	A_long			blend_mode;
	PF_FpLong		opacity;
} ParamInfo, *ParamInfoP, **ParamInfoH;


extern "C" {

	DllExport 
	PF_Err
	EffectMain (	
		PF_Cmd			cmd,
		PF_InData		*in_data,
		PF_OutData		*out_data,
		PF_ParamDef		*params[],
		PF_LayerDef		*output,
		void			*extra);

}




#endif // Filter_H