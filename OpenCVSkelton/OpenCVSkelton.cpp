
#include "OpenCVSkelton.h"



//=======================================================================================
/*
	�G�t�F�N�g�R���g���[���ŕ\�������UI�p�[�c�̓o�^
	Param_Utils.h���Q�Ƃ̂���
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
	//�ʒu�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(STR_STR_POS,			/*"New Center"*/
		50,	// X
		50,	// Y
		0,	// Flag
		ID_STR_POS
	);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//���������ƃL�[�t���[�������ĂȂ��Ȃ�
	//def.flags = PF_ParamFlag_CANNOT_INTERP;	//�L�[�t���[���̎����ۊǂ��~����
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
	PF_ADD_SLIDER(STR_ADD_SLIDER,	//�p�����[�^�̖��O
		-30000, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		0,				//�X���C�_�[�̍ŏ��l 
		100,			//�X���C�_�[�̍ő�l
		0,				//�f�t�H���g�̒l
		ID_ADD_SLIDER
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//���������ƃL�[�t���[�������ĂȂ��Ȃ�
	PF_ADD_FIXED(STR_FIXED_SLIDER,	//�p�����[�^�̖��O
		0, 				//���l���͂���ꍇ�̍ŏ��l
		100,			//���l���͂���ꍇ�̍ő�l
		0,				//�X���C�_�[�̍ŏ��l 
		100,			//�X���C�_�[�̍ő�l
		100,			//�f�t�H���g�̒l
		1,				//���l�\���Ɋւ���t���O 
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
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//���������ƃL�[�t���[�������ĂȂ��Ȃ�
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
	//�p�x
	AEFX_CLR_STRUCT(def);
	PF_ADD_ANGLE(STR_ANGLE, 0, ID_ANGLE);
	//----------------------------------------------------------------
	//�|�b�v�A�b�v���j���[
	AEFX_CLR_STRUCT(def);
	PF_ADD_POPUP(STR_POPUP,
		STR_POPUP_COUNT,	//���j���[�̐�
		STR_POPUP_DFLT,	//�f�t�H���g
		STR_POPUP_ITEMS,
		ID_POPUP
	);
	//----------------------------------------------------------------
	//�ʒu�̎w��
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
PF_Err Test8(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat8(ae->input);

	cv::Point pnt(infoP->str_point.x >> 16, infoP->str_point.y >> 16);

	cv::Scalar p = CAEcv::PF_PixelTo(infoP->str_color);
	cv::putText(src, "After Effects", pnt ,cv::FONT_HERSHEY_TRIPLEX, infoP->str_size,p , (int)(2 * infoP->str_size), CV_AA);

	CAEcv::Mat2World8(src,ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err Test16(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat16(ae->input);

	cv::Point pnt(infoP->str_point.x >> 16, infoP->str_point.y >> 16);
	cv::Scalar p = CAEcv::PF_PixelTo(PIXEL_CONV8TO16(infoP->str_color));

	cv::putText(src, "After Effects", pnt, cv::FONT_HERSHEY_TRIPLEX, infoP->str_size, p, (int)(2*infoP->str_size), CV_AA);

	CAEcv::Mat2World16(src, ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err Test32(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat32(ae->input);

	cv::Point pnt(infoP->str_point.x >> 16, infoP->str_point.y >> 16);
	cv::Scalar p = CAEcv::PF_PixelTo(PIXEL_CONV8TO32(infoP->str_color));

	cv::putText(src, "After Effects", pnt, cv::FONT_HERSHEY_TRIPLEX, infoP->str_size, p, (int)(2 * infoP->str_size), CV_AA);

	CAEcv::Mat2World16(src, ae->output);


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

	//��ʂ��R�s�[
	//ERR(ae->CopyInToOut());


	switch (ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		//ERR(ae->iterate32((refconType)infoP,FilterImage32));
		ERR(Test32(ae, infoP));
		break;
	case PF_PixelFormat_ARGB64:
		//ERR(ae->iterate16((refconType)infoP,FilterImage16));
		ERR(Test16(ae, infoP));
		break;
	case PF_PixelFormat_ARGB32:
		//ERR(ae->iterate8((refconType)infoP,FilterImage8));
		ERR(Test8(ae, infoP));
		break;
	}
	return err;
}


//=======================================================================================
#include "OpenCVSkelton_Entry.h"
