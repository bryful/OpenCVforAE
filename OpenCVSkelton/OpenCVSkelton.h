
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

//OpenCVのヘッダー
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

//定数定義ヘッダー
#include "OpenCVSkelton_Target.h"

//CAEクラスの読み込み
#include "..\Lib\CAE.h"
#include "..\Lib\CAEcv.h"
#include "..\Lib\FsUtils.h"
#include "..\Lib\PixelBase.h"


enum {
	ID_INPUT = 0,

	ID_STR_POS,
	ID_STR_COLOR,
	ID_STR_SIZE,

	ID_R,
	ID_G,
	ID_B,

	ID_TOPIC,
	ID_ADD_SLIDER,
	ID_FIXED_SLIDER,
	ID_FLOAT_SLIDER,
	ID_COLOR,
	ID_CHECKBOX,
	ID_ANGLE,
	ID_POPUP,
	ID_POINT,
	ID_TOPIC_END,
	ID_EX_W,
	ID_EX_H,

	ID_NUM_PARAMS
};



#define STR_STR_POS		"str_pos"
#define STR_STR_COL		"str_color"
#define STR_STR_SIZE	"str_size"

#define STR_R			"red"
#define STR_G			"green"
#define STR_B			"green"

#define STR_TOPIC			"topic"
#define STR_ADD_SLIDER		"add_slider"
#define STR_FIXED_SLIDER	"fiexd_slider"
#define STR_FLOAT_SLIDER	"float_slider"
#define STR_COLOR			"color"
#define STR_CHECKBOX1		"checkbox"
#define STR_CHECKBOX2		"on"
#define STR_ANGLE			"angle"
#define STR_POPUP			"popup"
#define STR_POPUP_ITEMS		"item1|item2|item3"
#define STR_POPUP_COUNT		3
#define STR_POPUP_DFLT		2
#define STR_POINT			"point"

#define STR_EX_W			"ex_width"
#define STR_EX_H			"ex_height"


typedef struct ParamInfo {
	PF_FixedPoint	str_point;
	PF_Pixel		str_color;
	PF_FpLong		str_size;

	PF_FpLong		bgr[3];

	A_long			add;
	PF_Fixed		fxd;
	PF_FpLong		flt;
	PF_Pixel		color;
	PF_Boolean		checkbox;
	PF_Fixed		angle;
	A_long			popup;
	PF_FixedPoint	point;
	A_long			ex_w;
	A_long			ex_h;
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