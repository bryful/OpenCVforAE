
#include "RotScale.h"



//=======================================================================================
/*
	ƒGƒtƒFƒNƒgƒRƒ“ƒgƒ[ƒ‹‚Å•\Ž¦‚³‚ê‚éUIƒp[ƒc‚Ì“o˜^
	Param_Utils.h‚ðŽQÆ‚Ì‚±‚Æ
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
	//Šp“x
	AEFX_CLR_STRUCT(def);
	PF_ADD_ANGLE(STR_ROT, 0, ID_ROT);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_SCALE,	//Name
		0,							//VALID_MIN
		1000,						//VALID_MAX
		0,							//SLIDER_MIN
		100,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		100,						//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_SCALE
	);


out_data->num_params = ID_NUM_PARAMS;

return err;
}



//-------------------------------------------------------------------------------------------------
PF_Err Test8(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat8(ae->input);

	cv::Point2f center = cv::Point2f(
		static_cast<float>(src.cols / 2),
		static_cast<float>(src.rows / 2));

	double degree = infoP->rot;		// ‰ñ“]Šp“x
	double scale = infoP->scale;   // Šg‘å—¦

	cv::Mat affine;
	cv::getRotationMatrix2D(center, degree, scale).copyTo(affine);



	cv::Mat dst(cv::Size(src.cols, src.rows), src.type(), cv::Scalar(0, 0, 0, 0));
	cv::warpAffine(src, dst, affine, src.size(), cv::INTER_CUBIC);




	CAEcv::Mat2World8(dst,ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err Test16(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	cv::Mat src = CAEcv::WorldToMat16(ae->input);

	cv::Point2f center = cv::Point2f(
		static_cast<float>(src.cols / 2),
		static_cast<float>(src.rows / 2));

	double degree = infoP->rot;		// ‰ñ“]Šp“x
	double scale = infoP->scale;   // Šg‘å—¦

	cv::Mat affine;
	cv::getRotationMatrix2D(center, degree, scale).copyTo(affine);



	cv::Mat dst(cv::Size(src.cols, src.rows), src.type(), cv::Scalar(0, 0, 0, 0));
	cv::warpAffine(src, dst, affine, src.size(), cv::INTER_CUBIC);




	CAEcv::Mat2World16(dst, ae->output);

	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err Test32(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	cv::Mat src = CAEcv::WorldToMat32(ae->input);

	cv::Point2f center = cv::Point2f(
		static_cast<float>(src.cols / 2),
		static_cast<float>(src.rows / 2));

	double degree = infoP->rot;		// ‰ñ“]Šp“x
	double scale = infoP->scale;   // Šg‘å—¦

	cv::Mat affine;
	cv::getRotationMatrix2D(center, degree, scale).copyTo(affine);



	cv::Mat dst(cv::Size(src.cols, src.rows), src.type(), cv::Scalar(0, 0, 0, 0));
	cv::warpAffine(src, dst, affine, src.size(), cv::INTER_CUBIC);




	CAEcv::Mat2World32(dst, ae->output);

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CAE *ae, ParamInfo *infoP)
{
	PF_Err		err = PF_Err_NONE;

	PF_Fixed f;
	ERR(ae->GetANGLE(ID_ROT, &f));
	if (!err)
	{
		f *= -1;
		f = f % (360L << 16);
		if (f < 0) f += (360L << 16);
		infoP->rot = (double)f / 65536;
	}

	ERR(ae->GetFLOAT(ID_SCALE, &infoP->scale));
	infoP->scale /= 100;

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
Exec(CAE *ae, ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	//‰æ–Ê‚ðƒRƒs[
	//ERR(ae->CopyInToOut());


	switch (ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		ERR(Test32(ae, infoP));
		break;
	case PF_PixelFormat_ARGB64:
		ERR(Test16(ae, infoP));
		break;
	case PF_PixelFormat_ARGB32:
		ERR(Test8(ae, infoP));
		break;
	}
	return err;
}


//=======================================================================================
#include "RotScale_Entry.h"
