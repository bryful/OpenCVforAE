
#include "Filter.h"



//=======================================================================================
/*
	エフェクトコントロールで表示されるUIパーツの登録
	Param_Utils.hを参照のこと
*/
static PF_Err
ParamsSetup(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;


	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.ui_flags = PF_PUI_DISABLED;
	PF_ADD_SLIDER(STR_MAX,	//パラメータの名前
		0, 			//数値入力する場合の最小値
		30,			//数値入力する場合の最大値
		0,			//スライダーの最小値 
		10,			//スライダーの最大値
		0,			//デフォルトの値
		ID_MAX
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.ui_flags = PF_PUI_DISABLED;
	PF_ADD_SLIDER(STR_BLUR,	//パラメータの名前
		0, 			//数値入力する場合の最小値
		100,			//数値入力する場合の最大値
		0,			//スライダーの最小値 
		30,			//スライダーの最大値
		0,			//デフォルトの値
		ID_BLUR
	);
	//----------------------------------------------------------------
	//ポップアップメニュー
	AEFX_CLR_STRUCT(def);
	PF_ADD_POPUP(STR_BLEND,
		STR_BLEND_COUNT,	//メニューの数
		STR_BLEND_DFLT,	//デフォルト
		STR_BLEND_ITEMS,
		ID_BLEND_MODE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_OPACITY,	//Name
		0,							//VALID_MIN
		100,						//VALID_MAX
		0,							//SLIDER_MIN
		100,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		0,						//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_OPACITY
	);	
	out_data->num_params = ID_NUM_PARAMS;

	return err;
}


//-------------------------------------------------------------------------------------------------
static PF_Err ExecSub(CAE *ae, ParamInfo *infoP)
{
	PF_Err		err = PF_Err_NONE;

	//画像のサイズを求めておく
	int width = ae->output->width;
	int height = ae->output->height;

	//とりあえずinputをcc::Matに移動
	cv::Mat src = CAEcv::WorldToMat(ae, ae->input);

	//マットへ
	CAEcv::ToPremultiply(ae,src);

	cv::Mat src2(cv::Size((int)round(width * 0.5), (int)round(height * 0.5)), src.type());
	cv::resize(src, src2, cv::Size(), 0.5, 0.5);

	//拡張
	if (infoP->max > 0)
	{
		cv::dilate(src2, src2, cv::Mat(), cv::Point(-1, -1), infoP->max);
	}
	
	//ぼかし
	if (infoP->blur> 0)
	{
		int v = (int)((double)infoP->blur / 2 + 0.5) * 2 +1;
		cv::GaussianBlur(src2, src2, cv::Size(v, v), 0, 0, cv::BORDER_REPLICATE);
	}

	//dstへ拡大
	cv::Mat dst(cv::Size(width, height), src.type());
	double w2 = width / src2.cols;
	cv::resize(src2, dst, cv::Size(), w2, w2);

	switch (infoP->blend_mode)
	{
	case 1:
		CAEcv::BlendNormal(ae, dst, src, infoP->opacity);
		break;
	case 2:
		CAEcv::BlendLighten(ae, dst, src, infoP->opacity);
		break;
	case 3:
		CAEcv::BlendScreen(ae, dst, src, infoP->opacity);
		break;
	case 4:
		CAEcv::BlendAdd(ae, dst, src, infoP->opacity);
		break;

	default:
		break;
	}

	CAEcv::FromPremultiply(ae,src);

	CAEcv::Mat2World(ae, src, ae->output);

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CAE *ae, ParamInfo *infoP)
{
	PF_Err		err = PF_Err_NONE;

	ERR(ae->GetADD(ID_MAX, &infoP->max));
	infoP->max = ae->downScaleNoClip(infoP->max);
	ERR(ae->GetADD(ID_BLUR, &infoP->blur));
	infoP->blur = ae->downScaleNoClip(infoP->blur);
	ERR(ae->GetPOPUP(ID_BLEND_MODE, &infoP->blend_mode));
	ERR(ae->GetFLOAT(ID_OPACITY, &infoP->opacity));
	infoP->opacity /= 100;
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
Exec(CAE *ae, ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	if ((infoP->blur <= 0) && (infoP->max <= 0))
	{
		//画面をコピー
		ERR(ae->CopyInToOut());
	}
	else {
		ERR(ExecSub(ae, infoP));
	}

#pragma region not use


	/*
	switch (ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		//ERR(ae->iterate32((refconType)infoP,FilterImage32));
		//ERR(Test32(ae, infoP));
		//TestPixelFunc32(ae, infoP);
		break;
	case PF_PixelFormat_ARGB64:
		//ERR(ae->iterate16((refconType)infoP,FilterImage16));
		//ERR(Test16(ae, infoP));
		//TestPixelFunc16(ae, infoP);
		break;
	case PF_PixelFormat_ARGB32:
		//ERR(Test8(ae, infoP));
		//TestPixelFunc8(ae, infoP);
		break;
	}
	*/
#pragma endregion


	return err;
}


//=======================================================================================
#include "Filter_Entry.h"
