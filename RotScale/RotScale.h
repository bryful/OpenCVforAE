
#pragma once
#ifndef RotScale_H
#define RotScale_H


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
#include "RotScale_Target.h"

//CAEクラスの読み込み
#include "..\Lib\CAE.h"
#include "..\Lib\CAEcv.h"
#include "..\Lib\FsUtils.h"


enum {
	ID_INPUT = 0,

	ID_ROT,
	ID_SCALE,

	ID_NUM_PARAMS
};



#define STR_ROT			"rot"
#define STR_SCALE		"scale"


typedef struct ParamInfo {
	PF_FpLong		rot;
	PF_FpLong		scale;

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




#endif // RotScale_H