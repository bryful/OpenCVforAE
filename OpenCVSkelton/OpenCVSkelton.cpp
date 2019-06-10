
#include "OpenCVSkelton.h"


//=======================================================================================
static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err = PF_Err_NONE;

	CAE ae;
	err = ae.About(in_data, out_data, params, output);
	return PF_Err_NONE;
}

//=======================================================================================
static PF_Err
GlobalSetup (
	PF_InData		*in_dataP,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err = PF_Err_NONE;
	CAE ae;
	err = ae.GlobalSetup(in_dataP, out_data, params, output);
	return err;
	
}
//-------------------------------------------------------------------------------------------------
static PF_Err GlobalSetdown(
	PF_InData	*in_data)
{
	PF_Err	err = PF_Err_NONE;
	CAE ae;
	err = ae.GlobalSetdown(in_data);
	return PF_Err_NONE;
}

//-------------------------------------------------------------------------------------------------
static PF_Err SequenceSetup(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{

	return PF_Err_NONE;
}
//-------------------------------------------------------------------------------------------------
static PF_Err SequenceSetdown(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	return PF_Err_NONE;
}


//-------------------------------------------------------------------------------------------------
static PF_Err SequenceResetup(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	return PF_Err_NONE;
}

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
	//位置の指定
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(STR_STR_POS,			/*"New Center"*/
		50,	// X
		50,	// Y
		0,	// Flag
		ID_STR_POS
	);
	//----------------------------------------------------------------
	//色の指定
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//これをつけるとキーフレームが撃てなくなる
	//def.flags = PF_ParamFlag_CANNOT_INTERP;	//キーフレームの自動保管を停止する
	PF_ADD_COLOR(STR_STR_COL,
		0xFF, 
		0xFF,
		0x00,
		ID_STR_COLOR
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_STR_SIZE,	//Name
		0,							//VALID_MIN
		10,						//VALID_MAX
		0,							//SLIDER_MIN
		10,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		1.5,						//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_STR_SIZE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_START_COLLAPSED;
	PF_ADD_TOPIC(STR_TOPIC, ID_TOPIC);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.ui_flags = PF_PUI_DISABLED;
	PF_ADD_SLIDER(STR_ADD_SLIDER,	//パラメータの名前
		-30000, 		//数値入力する場合の最小値
		30000,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		0,				//デフォルトの値
		ID_ADD_SLIDER
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//これをつけるとキーフレームが撃てなくなる
	PF_ADD_FIXED(STR_FIXED_SLIDER,	//パラメータの名前
		0, 				//数値入力する場合の最小値
		100,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		100,			//デフォルトの値
		1,				//数値表示に関するフラグ 
		0,
		0,
		ID_FIXED_SLIDER
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_FLOAT_SLIDER,	//Name
		-10000,							//VALID_MIN
		10000,						//VALID_MAX
		0,							//SLIDER_MIN
		1000,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		500,						//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_FLOAT_SLIDER
	);
	//----------------------------------------------------------------
	//色の指定
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//これをつけるとキーフレームが撃てなくなる
	PF_ADD_COLOR(STR_COLOR,
		0xFF,
		0xFF,
		0xFF,
		ID_COLOR
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_SUPERVISE |
	//	PF_ParamFlag_CANNOT_TIME_VARY |
	//	PF_ParamFlag_CANNOT_INTERP;
	PF_ADD_CHECKBOX(STR_CHECKBOX1,
		STR_CHECKBOX2,
		TRUE,
		0,
		ID_CHECKBOX
	);
	//----------------------------------------------------------------
	//角度
	AEFX_CLR_STRUCT(def);
	PF_ADD_ANGLE(STR_ANGLE, 0, ID_ANGLE);
	//----------------------------------------------------------------
	//ポップアップメニュー
	AEFX_CLR_STRUCT(def);
	PF_ADD_POPUP(STR_POPUP,
		STR_POPUP_COUNT,	//メニューの数
		STR_POPUP_DFLT,	//デフォルト
		STR_POPUP_ITEMS,
		ID_POPUP
	);
	//----------------------------------------------------------------
	//位置の指定
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(STR_POINT,			/*"New Center"*/
		50,	// X
		50,	// Y
		0,	// Flag
		ID_POINT
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_END_TOPIC(ID_TOPIC_END);
	
	out_data->num_params = ID_NUM_PARAMS;

	return err;
}
//=======================================================================================
static PF_Err
QueryDynamicFlags(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	void			*extra)
{
	PF_Err 	err = PF_Err_NONE;
	return err;
}
//=======================================================================================
static PF_Err
HandleChangedParam(
	PF_InData					*in_data,
	PF_OutData					*out_data,
	PF_ParamDef					*params[],
	PF_LayerDef					*outputP,
	PF_UserChangedParamExtra	*extraP)
{
	PF_Err				err = PF_Err_NONE;

	return err;
}
//-----------------------------------------------------------------------------------
static PF_Err
RespondtoAEGP(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void*			extraP)
{
	PF_Err			err = PF_Err_NONE;

	AEGP_SuiteHandler suites(in_data->pica_basicP);

	suites.ANSICallbacksSuite1()->sprintf(out_data->return_msg,
		"%s",
		reinterpret_cast<A_char*>(extraP));

	return err;
}
//=======================================================================================
/*
static PF_Err
FilterImage8 (
	void		*refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel8	*inP, 
	PF_Pixel8	*outP)
{
	PF_Err			err = PF_Err_NONE;
	
	NoiseInfo *	niP		= reinterpret_cast<NoiseInfo*>(refcon);
	PF_FpLong	tempF		= 0;
					
	if (niP){
		tempF 	= rand() % PF_MAX_CHAN8;
		tempF	*= (niP->valF / SLIDER_MAX);

		outP->alpha		=	inP->alpha;
		outP->red		=	MIN(PF_MAX_CHAN8, inP->red + (A_u_char) tempF);
		outP->green		=	MIN(PF_MAX_CHAN8, inP->green + (A_u_char) tempF);
		outP->blue		=	MIN(PF_MAX_CHAN8, inP->blue + (A_u_char) tempF);
	}
	return err;
}
*/
//-------------------------------------------------------------------------------------------------
cv::Mat World2CVMat8(const PF_EffectWorldPtr world)
{
	int w = world->width;
	int wt = world->rowbytes / sizeof(PF_Pixel);
	int h = world->height;

	int cz = 4;
	int czw = cz * w;

	cv::Mat ret(cv::Size((int)world->width, (int)world->height), CV_8UC4);

	A_u_char* mData = (A_u_char*)ret.data;
	PF_Pixel* wData = (PF_Pixel *)world->data;


	A_long matPos = 0;
	A_long wldPos = 0;
	for (A_long y = 0; y < h; y++)
	{

		for (A_long x = 0; x < w; x++)
		{
			A_long matPosx = matPos + x * cz;
			A_long wldPosx = wldPos + x;
			mData[matPosx + 0] = wData[wldPosx].red;
			mData[matPosx + 1] = wData[wldPosx].green;
			mData[matPosx + 2] = wData[wldPosx].blue;
			mData[matPosx + 3] = wData[wldPosx].alpha;

		}
		matPos += czw;
		wldPos += wt;
	}
	return ret;

}

//-------------------------------------------------------------------------------------------------
void CVMat2World8(const cv::Mat mat, PF_EffectWorldPtr world)
{
	int w = world->width;
	int wt = world->rowbytes / sizeof(PF_Pixel);
	int h = world->height;

	int w2 = mat.cols;
	int h2 = mat.rows;

	if ((w != w2) || (h != h2)) return;

	int cz = 4;
	int czw = cz * w;

	A_u_char* mData = (A_u_char*)mat.data;
	PF_Pixel* wData = (PF_Pixel *)world->data;


	A_long matPos = 0;
	A_long wldPos = 0;
	for (A_long y = 0; y < h; y++)
	{

		for (A_long x = 0; x < w; x++)
		{
			A_long matPosx = matPos + x * cz;
			A_long wldPosx = wldPos + x;
			wData[wldPosx].red = mData[matPosx + 0];
			wData[wldPosx].green = mData[matPosx + 1];
			wData[wldPosx].blue = mData[matPosx + 2];
			wData[wldPosx].alpha = mData[matPosx + 3];

		}
		matPos += czw;
		wldPos += wt;
	}

}
//-------------------------------------------------------------------------------------------------
PF_Err Test8(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = World2CVMat8(ae->input);

	cv::Point pnt(infoP->str_point.x >> 16, infoP->str_point.y >> 16);
	cv::Scalar scl(infoP->str_color.red, infoP->str_color.green, infoP->str_color.blue, PF_MAX_CHAN8);

	cv::putText(src, "After Effects", pnt ,cv::FONT_HERSHEY_TRIPLEX, infoP->str_size,scl , 2, CV_AA);

	CVMat2World8(src, ae->output);


	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CAE *ae, ParamInfo *infoP)
{
	PF_Err		err = PF_Err_NONE;

	ERR(ae->GetFIXEDPOINT(ID_STR_POS, &infoP->str_point));
	ERR(ae->GetCOLOR(ID_STR_COLOR, &infoP->str_color));
	ERR(ae->GetFLOAT(ID_STR_SIZE, &infoP->str_size));

	ERR(ae->GetADD(ID_ADD_SLIDER, &infoP->add));
	ERR(ae->GetFIXED(ID_FIXED_SLIDER, &infoP->fxd));
	ERR(ae->GetFLOAT(ID_FLOAT_SLIDER, &infoP->flt));
	ERR(ae->GetCOLOR(ID_COLOR, &infoP->color));
	ERR(ae->GetCHECKBOX(ID_CHECKBOX, &infoP->checkbox));
	ERR(ae->GetANGLE(ID_ANGLE, &infoP->angle));
	ERR(ae->GetPOPUP(ID_POPUP, &infoP->popup));
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
Exec(CAE *ae, ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	//画面をコピー
	//ERR(ae->CopyInToOut());


	switch (ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		//ERR(ae->iterate32((refconType)infoP,FilterImage32));
		break;
	case PF_PixelFormat_ARGB64:
		//ERR(ae->iterate16((refconType)infoP,FilterImage16));
		break;
	case PF_PixelFormat_ARGB32:
		//ERR(ae->iterate8((refconType)infoP,FilterImage8));
		ERR(Test8(ae, infoP));
		break;
	}
	return err;
}
//=======================================================================================
static PF_Err 
Render ( 
	PF_InData		*in_dataP,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err = PF_Err_NONE;
	PF_Handle		pixelTable = NULL;

	CAE ae(in_dataP, out_data, params, output, ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err) {
		ParamInfo info;
		ERR(GetParams(&ae, &info));
		ERR(Exec(&ae, &info));
	}
	return err;
}

//=======================================================================================
static PF_Err
PreRender(
	PF_InData			*in_dataP,
	PF_OutData			*out_dataP,
	PF_PreRenderExtra	*extraP)
{
	PF_Err err = PF_Err_NONE;
	PF_ParamDef noise_param;
	PF_RenderRequest req = extraP->input->output_request;
	//PF_CheckoutResult in_result;
	
	AEFX_CLR_STRUCT(noise_param);

	AEFX_SuiteScoper<PF_HandleSuite1> handleSuite = AEFX_SuiteScoper<PF_HandleSuite1>(	in_dataP,
																						kPFHandleSuite,
																						kPFHandleSuiteVersion1,
																						out_dataP);

	PF_Handle infoH	= handleSuite->host_new_handle(sizeof(ParamInfo));
	
	if (infoH){

		ParamInfo *infoP = reinterpret_cast<ParamInfo*>(handleSuite->host_lock_handle(infoH));
		
		if (infoP){
			/*
			extraP->output->pre_render_data = infoH;
			
			ERR(PF_CHECKOUT_PARAM(	in_dataP, 
									NOISE_SLIDER, 
									in_dataP->current_time, 
									in_dataP->time_step, 
									in_dataP->time_scale, 
									&noise_param));
			
			if (!err){
				infoP->valF = noise_param.u.fs_d.value;
			}
			
			ERR(extraP->cb->checkout_layer(	in_dataP->effect_ref,
											ID_INPUT,
											ID_INPUT,
											&req,
											in_dataP->current_time,
											in_dataP->time_step,
											in_dataP->time_scale,
											&in_result));
			
			UnionLRect(&in_result.result_rect, 		&extraP->output->result_rect);
			UnionLRect(&in_result.max_result_rect, 	&extraP->output->max_result_rect);		
			*/
			handleSuite->host_unlock_handle(infoH);
		}
	} else {
		err = PF_Err_OUT_OF_MEMORY;
	}
	return err;
}
//=======================================================================================
static PF_Err
SmartRender(
	PF_InData				*in_data,
	PF_OutData				*out_data,
	PF_SmartRenderExtra		*extraP)
{
	
	PF_Err			err		= PF_Err_NONE,
					err2 	= PF_Err_NONE;
	
	PF_EffectWorld	*input_worldP	= NULL, 
					*output_worldP  = NULL;

	AEFX_SuiteScoper<PF_HandleSuite1> handleSuite = AEFX_SuiteScoper<PF_HandleSuite1>(	in_data,
																						kPFHandleSuite,
																						kPFHandleSuiteVersion1,
																						out_data);
	
	ParamInfo	*infoP = reinterpret_cast<ParamInfo*>(handleSuite->host_lock_handle(reinterpret_cast<PF_Handle>(extraP->input->pre_render_data)));
	
	if (infoP){
		/*
		ERR((extraP->cb->checkout_layer_pixels(	in_data->effect_ref, ID_INPUT, &input_worldP)));
		ERR(extraP->cb->checkout_output(in_data->effect_ref, &output_worldP));
		
		PF_PixelFormat		format	=	PF_PixelFormat_INVALID;
		
		AEFX_SuiteScoper<PF_WorldSuite2> wsP = AEFX_SuiteScoper<PF_WorldSuite2>(in_data,
																				kPFWorldSuite,
																				kPFWorldSuiteVersion2,
																				out_data);
		
		if (infoP->valF == 0.0) {
			err = PF_COPY(input_worldP, output_worldP, NULL, NULL);
		} else {
			ERR(wsP->PF_GetPixelFormat(input_worldP, &format));
			
			if (!err){

				AEFX_SuiteScoper<PF_iterateFloatSuite1> iterateFloatSuite =
					AEFX_SuiteScoper<PF_iterateFloatSuite1>(in_data,
															kPFIterateFloatSuite,
															kPFIterateFloatSuiteVersion1,
															out_data);
				AEFX_SuiteScoper<PF_iterate16Suite1> iterate16Suite =
					AEFX_SuiteScoper<PF_iterate16Suite1>(	in_data,
															kPFIterate16Suite,
															kPFIterate16SuiteVersion1,
															out_data);

				AEFX_SuiteScoper<PF_Iterate8Suite1> iterate8Suite =
					AEFX_SuiteScoper<PF_Iterate8Suite1>(	in_data,
															kPFIterate8Suite,
															kPFIterate8SuiteVersion1,
															out_data);
				switch (format) {
					
					case PF_PixelFormat_ARGB128:
		
						iterateFloatSuite->iterate(	in_data,
													0,
													output_worldP->height,
													input_worldP,
													NULL,
													(void*)infoP,
													FilterImage32,
													output_worldP);
						break;
						
					case PF_PixelFormat_ARGB64:
										
						iterate16Suite->iterate(in_data,
												0,
												output_worldP->height,
												input_worldP,
												NULL,
												(void*)infoP,
												FilterImage16,
												output_worldP);
						break;
						
					case PF_PixelFormat_ARGB32:
			
						iterate8Suite->iterate(	in_data,
												0,
												output_worldP->height,
												input_worldP,
												NULL,
												(void*)infoP,
												FilterImage8,
												output_worldP);
						break;
						
					default:
						err = PF_Err_BAD_CALLBACK_PARAM;
						break;
				}
			}		
		}
		ERR2(extraP->cb->checkin_layer_pixels(in_data->effect_ref, ID_INPUT));
		*/
	}
	return err;
	
}
//=======================================================================================
extern "C" DllExport
PF_Err PluginDataEntryFunction(
	PF_PluginDataPtr inPtr,
	PF_PluginDataCB inPluginDataCallBackPtr,
	SPBasicSuite* inSPBasicSuitePtr,
	const char* inHostName,
	const char* inHostVersion)
{
	PF_Err result = PF_Err_INVALID_CALLBACK;

	result = PF_REGISTER_EFFECT(
		inPtr,
		inPluginDataCallBackPtr,
		NAME, // Name
		MATCH_NAME, // Match Name
		CATEGORY, // Category
		AE_RESERVED_INFO); // Reserved Info

	return result;
}
//=======================================================================================
PF_Err
EffectMain(
	PF_Cmd			cmd,
	PF_InData		*in_dataP,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extraP)
{
	PF_Err		err = PF_Err_NONE;
	
	try {
		switch (cmd) 
		{
			case PF_Cmd_ABOUT:
				err = About(in_dataP,out_data,params,output);
				break;
			case PF_Cmd_GLOBAL_SETUP:
				err = GlobalSetup(in_dataP,out_data,params,output);
				break;
			case PF_Cmd_GLOBAL_SETDOWN:
				err = GlobalSetdown(in_dataP);
				break;
			case PF_Cmd_PARAMS_SETUP:
				err = ParamsSetup(in_dataP,out_data,params,output);
				break;
			case PF_Cmd_SEQUENCE_SETUP:
				err = SequenceSetup(in_dataP, out_data, params, output);
				break;
			case PF_Cmd_SEQUENCE_SETDOWN:
				err = SequenceSetdown(in_dataP, out_data, params, output);
				break;
			case PF_Cmd_SEQUENCE_RESETUP:
				err = SequenceResetup(in_dataP, out_data, params, output);
			break;			case PF_Cmd_RENDER:
				err = Render(in_dataP,out_data,params,output);
				break;
#if defined(SUPPORT_SMARTFX)
			case PF_Cmd_SMART_PRE_RENDER:
				err = PreRender(in_dataP, out_data, (PF_PreRenderExtra*)extra);
				break;
			case PF_Cmd_SMART_RENDER:
				err = SmartRender(in_dataP, out_data, (PF_SmartRenderExtra*)extra);
				break;
#endif
			case PF_Cmd_COMPLETELY_GENERAL:
				err = RespondtoAEGP(in_dataP, out_data, params, output, extraP);
				break;
			case PF_Cmd_DO_DIALOG:
				//err = PopDialog(in_dataP,out_data,params,output);
				break;
			case PF_Cmd_USER_CHANGED_PARAM:
				err = HandleChangedParam(in_dataP,
					out_data,
					params,
					output,
					reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
			case PF_Cmd_QUERY_DYNAMIC_FLAGS:
				err = QueryDynamicFlags(in_dataP,
					out_data,
					params,
					reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
		}
	} catch(PF_Err &thrown_err) {
		// Never EVER throw exceptions into AE.
		err = thrown_err;
	}
	return err;
}
//=======================================================================================
