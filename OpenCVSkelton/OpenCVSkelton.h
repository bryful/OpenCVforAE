
#pragma once
#ifndef OpenCVSkelton_H
#define OpenCVSkelton_H


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


//定数定義ヘッダー
#include "OpenCVSkelton_Target.h"

//CAEクラスの読み込み
#include "..\OpenCV\Lib\CAE.h"


enum {
	ID_INPUT = 0,
	NOISE_SLIDER,		// default input layer 
	ID_NUM_PARAMS
};

enum {
	SLIDER_DISK_ID = 1
};


#define FILTER_NOISE_MIN	0
#define FILTER_NOISE_MAX	1000
#define FILTER_NOISE_DFLT	10
#define SLIDER_MIN			0
#define	SLIDER_MAX			100

#define RESTRICT_BOUNDS			0
#define SLIDER_PRECISION		1
#define DISPLAY_FLAGS			PF_ValueDisplayFlag_PERCENT


typedef struct ParamInfo {
	PF_FpLong	valF;
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




#endif // OpenCVSkelton_H