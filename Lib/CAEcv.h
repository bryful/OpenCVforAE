#pragma once
#ifndef CAE_OpenCV_H
#define CAE_OpenCV_H

//******************************************************************************
//各種ヘッダー登録
/*
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

#ifndef refconType
#define refconType void*
#endif
*/

#include "CAE.h"

//OpenCVのヘッダー
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

enum
{
	BLUE = 0,
	GREEN,
	RED,
	ALPHA,
	CHANNELS

};
typedef struct {
	A_u_char	blue, green, red,alpha;
} CV8UC4_Pixel;

typedef struct {
	A_u_short	blue, green, red,alpha;
} CV16UC4_Pixel;

typedef struct {
	PF_FpShort	blue, green, red,alpha;
} CV32FC4_Pixel;

/*
typedef struct {
		A_u_char	alpha, red, green, blue;
	} PF_Pixel;
#define PF_PixLong_ALPHA(pl)			((A_u_char)(0xff & ((pl) >> 24)))
#define PF_PixLong_RED(pl)				((A_u_char)(0xff & ((pl) >> 16)))
#define PF_PixLong_GREEN(pl)			((A_u_char)(0xff & ((pl) >> 8)))
#define PF_PixLong_BLUE(pl)				((A_u_char)(0xff & (pl)))

*/
class CAEcv
{
private:

public:
	

	CAEcv()
	{

	}
	~CAEcv()
	{

	}
	//
	static cv::Mat WorldToMat(CAE *ae,PF_EffectWorldPtr world)
	{
		A_long w = world->width;
		A_long h = world->height;
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return WorldToMat32(world);
			break;
		case PF_PixelFormat_ARGB64:
			return WorldToMat16(world);
			break;
		case PF_PixelFormat_ARGB32:
		default:
			return WorldToMat8(world);
			break;
		}

	}
	static cv::Mat InputToMat(CAE *ae)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return WorldToMat32(ae->output);
			break;
		case PF_PixelFormat_ARGB64:
			return WorldToMat16(ae->output);
			break;
		case PF_PixelFormat_ARGB32:
			return WorldToMat8(ae->output);
			break;
		}

	}
	static cv::Mat WorldToMat8(PF_EffectWorldPtr world,A_long addX=0, A_long addY = 0)
	{
		if (addX < 0) addX = 0;
		if (addY < 0) addY = 0;
		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_Pixel);
		int h = world->height;
		int mw = w + addX * 2;
		int mh = h + addY * 2;



		cv::Mat ret(cv::Size((int)mw, (int)mh), CV_8UC4);
		ret = cv::Scalar(0, 0, 0, 0);
		CV8UC4_Pixel * mData = (CV8UC4_Pixel *)ret.data;
		PF_Pixel* wData = (PF_Pixel *)world->data;


		A_long matPos = 0;
		A_long wldPos = 0;
		/*
		CV8UC4_Pixel f = { 0,0,0,0 };
		for (A_long y = 0; y < mh; y++)
		{
			for (A_long x = 0; x < mw; x++)
			{
				mData[matPos] = f;
				matPos++;
			}
		}
		*/

		matPos = addX + addY * mw;
		for (A_long y = 0; y < h; y++)
		{
			for (A_long x = 0; x < w; x++)
			{
				A_long matPosx = matPos + x;
				A_long wldPosx = wldPos + x;
				mData[matPosx].blue = wData[wldPosx].blue;
				mData[matPosx].green = wData[wldPosx].green;
				mData[matPosx].red = wData[wldPosx].red;
				mData[matPosx].alpha = wData[wldPosx].alpha;

			}
			matPos += mw;
			wldPos += wt;
		}
		return ret;
	}
	static cv::Mat WorldToMat16(PF_EffectWorldPtr world, A_long addX = 0, A_long addY = 0)
	{
		if (addX < 0) addX = 0;
		if (addY < 0) addY = 0;
		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_Pixel16);
		int h = world->height;
		int mw = w + addX * 2;
		int mh = h + addY * 2;



		cv::Mat ret(cv::Size((int)mw, (int)mh), CV_16UC4);
		ret = cv::Scalar(0, 0, 0, 0);
		CV16UC4_Pixel * mData = (CV16UC4_Pixel *)ret.data;
		PF_Pixel16* wData = (PF_Pixel16 *)world->data;


		A_long matPos = 0;
		A_long wldPos = 0;


		matPos = addX + addY * mw;
		for (A_long y = 0; y < h; y++)
		{
			for (A_long x = 0; x < w; x++)
			{
				A_long matPosx = matPos + x;
				A_long wldPosx = wldPos + x;
				mData[matPosx].blue = wData[wldPosx].blue;
				mData[matPosx].green = wData[wldPosx].green;
				mData[matPosx].red = wData[wldPosx].red;
				mData[matPosx].alpha = wData[wldPosx].alpha;

			}
			matPos += mw;
			wldPos += wt;
		}
		return ret;
	}
	static cv::Mat WorldToMat32(PF_EffectWorldPtr world, A_long addX = 0, A_long addY = 0)
	{
		if (addX < 0) addX = 0;
		if (addY < 0) addY = 0;
		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_PixelFloat);
		int h = world->height;
		int mw = w + addX * 2;
		int mh = h + addY * 2;



		cv::Mat ret(cv::Size((int)mw, (int)mh), CV_32FC4);
		ret = cv::Scalar(0, 0, 0, 0);
		CV32FC4_Pixel * mData = (CV32FC4_Pixel *)ret.data;
		PF_PixelFloat* wData = (PF_PixelFloat *)world->data;


		A_long matPos = 0;
		A_long wldPos = 0;


		matPos = addX + addY * mw;
		for (A_long y = 0; y < h; y++)
		{
			for (A_long x = 0; x < w; x++)
			{
				A_long matPosx = matPos + x;
				A_long wldPosx = wldPos + x;
				mData[matPosx].blue = wData[wldPosx].blue;
				mData[matPosx].green = wData[wldPosx].green;
				mData[matPosx].red = wData[wldPosx].red;
				mData[matPosx].alpha = wData[wldPosx].alpha;

			}
			matPos += mw;
			wldPos += wt;
		}
		return ret;
	}
	//-------------------------------------------------------------------------------------------------
	static PF_Err Mat2World8(const cv::Mat mat, PF_EffectWorldPtr world)
	{
		PF_Err err = PF_Err_NONE;

		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_Pixel);
		int h = world->height;

		int w2 = mat.cols;
		int h2 = mat.rows;

		if ((w != w2) || (h != h2)) return PF_Err_BAD_CALLBACK_PARAM;

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
				wData[wldPosx].blue = mData[matPosx + BLUE];
				wData[wldPosx].green = mData[matPosx + GREEN];
				wData[wldPosx].red = mData[matPosx + RED];
				wData[wldPosx].alpha = mData[matPosx + ALPHA];

			}
			matPos += czw;
			wldPos += wt;
		}

		return err;
	}
	//-------------------------------------------------------------------------------------------------
	static PF_Err Mat2World16(const cv::Mat mat, PF_EffectWorldPtr world)
	{

		PF_Err err = PF_Err_NONE;
		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_Pixel16);
		int h = world->height;

		int w2 = mat.cols;
		int h2 = mat.rows;

		if ((w != w2) || (h != h2)) return PF_Err_BAD_CALLBACK_PARAM;

		int cz = 4;
		int czw = cz * w;

		A_u_short* mData = (A_u_short*)mat.data;
		PF_Pixel16* wData = (PF_Pixel16 *)world->data;


		A_long matPos = 0;
		A_long wldPos = 0;
		for (A_long y = 0; y < h; y++)
		{

			for (A_long x = 0; x < w; x++)
			{
				A_long matPosx = matPos + x * cz;
				A_long wldPosx = wldPos + x;
				wData[wldPosx].blue = mData[matPosx + BLUE];
				wData[wldPosx].green = mData[matPosx + GREEN];
				wData[wldPosx].red = mData[matPosx + RED];
				wData[wldPosx].alpha = mData[matPosx + ALPHA];

			}
			matPos += czw;
			wldPos += wt;
		}
		return err;

	}
	//-------------------------------------------------------------------------------------------------
	static PF_Err Mat2World32(const cv::Mat mat, PF_EffectWorldPtr world)
	{
		PF_Err err = PF_Err_NONE;
		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_PixelFloat);
		int h = world->height;

		int w2 = mat.cols;
		int h2 = mat.rows;

		if ((w != w2) || (h != h2)) return PF_Err_BAD_CALLBACK_PARAM;

		int cz = 4;
		int czw = cz * w;

		PF_FpShort* mData = (PF_FpShort*)mat.data;
		PF_PixelFloat* wData = (PF_PixelFloat *)world->data;


		A_long matPos = 0;
		A_long wldPos = 0;
		for (A_long y = 0; y < h; y++)
		{

			for (A_long x = 0; x < w; x++)
			{
				A_long matPosx = matPos + x * cz;
				A_long wldPosx = wldPos + x;
				wData[wldPosx].blue = mData[matPosx + BLUE];
				wData[wldPosx].green = mData[matPosx + GREEN];
				wData[wldPosx].red = mData[matPosx + RED];
				wData[wldPosx].alpha = mData[matPosx + ALPHA];

			}
			matPos += czw;
			wldPos += wt;
		}
		return err;

	}
	static PF_Err Mat2World(CAE *ae, const cv::Mat mat, PF_EffectWorldPtr world)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return Mat2World32(mat,world);
			break;
		case PF_PixelFormat_ARGB64:
			return Mat2World16(mat, world);
			break;
		case PF_PixelFormat_ARGB32:
			return Mat2World8(mat, world);
			break;
		default:
			return PF_Err_BAD_CALLBACK_PARAM;
		}

	}
	static PF_Err MatToOutput(CAE *ae, const cv::Mat mat)
	{
		return Mat2World(ae, mat, ae->output);
	}
	static cv::Scalar PF_PixelTo(PF_Pixel p)
	{
		return cv::Scalar(p.blue, p.green, p.red, p.alpha);
	}
	static cv::Scalar PF_PixelTo(PF_Pixel16 p)
	{
		return cv::Scalar(p.blue, p.green, p.red, p.alpha);
	}
	static cv::Scalar PF_PixelTo(PF_PixelFloat p)
	{
		return cv::Scalar(p.blue, p.green, p.red, p.alpha);
	}
	static PF_Pixel ScalerTo8(cv::Scalar s)
	{
		PF_Pixel ret;
		ret.blue = (A_u_char)s[0];
		ret.green = (A_u_char)s[1];
		ret.red = (A_u_char)s[2];
		ret.alpha = (A_u_char)s[3];
		return ret;
	}
	static PF_Pixel16 ScalerTo16(cv::Scalar s)
	{
		PF_Pixel16 ret;
		ret.blue = (A_u_short)s[0];
		ret.green = (A_u_short)s[1];
		ret.red = (A_u_short)s[2];
		ret.alpha = (A_u_short)s[3];
		return ret;
	}
	static PF_PixelFloat ScalerTo32(cv::Scalar s)
	{
		PF_PixelFloat ret;
		ret.blue = (PF_FpShort)s[0];
		ret.green = (PF_FpShort)s[1];
		ret.red = (PF_FpShort)s[2];
		ret.alpha = (PF_FpShort)s[3];
		return ret;
	}
	//*********************************************************************************
	static PF_Err iterate8( refconType refcon, cv::Mat src, cv::Mat dst,
		PF_Err(*pix_fn)(refconType refcon, A_long x, A_long y, CV8UC4_Pixel *in, CV8UC4_Pixel *out)
	)
	{
		PF_Err err = PF_Err_NONE;
		if ((src.cols != dst.cols) || (src.rows != dst.rows)) return PF_Err_INVALID_INDEX;
		A_long w = src.cols;
		A_long h = src.rows;

		CV8UC4_Pixel* inD = (CV8UC4_Pixel*)src.data;
		CV8UC4_Pixel* outD = (CV8UC4_Pixel*)dst.data;
		for (A_long y = 0; y < h; y++) {
			for (A_long x = 0; x < w; x++) {
				err = pix_fn((refconType)refcon, x, y, inD, outD);
				if (err != PF_Err_NONE) return err;
				inD++;
				outD++;
			}
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err iterate16(refconType refcon, cv::Mat src, cv::Mat dst,
		PF_Err(*pix_fn)(refconType refcon, A_long x, A_long y, CV16UC4_Pixel *in, CV16UC4_Pixel *out)
	)
	{
		PF_Err err = PF_Err_NONE;
		if ((src.cols != dst.cols) || (src.rows != dst.rows)) return PF_Err_INVALID_INDEX;
		A_long w = src.cols;
		A_long h = src.rows;

		CV16UC4_Pixel* inD = (CV16UC4_Pixel*)src.data;
		CV16UC4_Pixel* outD = (CV16UC4_Pixel*)dst.data;
		for (A_long y = 0; y < h; y++) {
			for (A_long x = 0; x < w; x++) {
				err = pix_fn((refconType)refcon, x, y, inD, outD);
				if (err != PF_Err_NONE) return err;
				inD++;
				outD++;
			}
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err iterate32(refconType refcon, cv::Mat src, cv::Mat dst,
		PF_Err(*pix_fn)(refconType refcon, A_long x, A_long y, CV32FC4_Pixel *in, CV32FC4_Pixel *out)
	)
	{
		PF_Err err;
		if ((src.cols != dst.cols) || (src.rows != dst.rows)) return PF_Err_INVALID_INDEX;
		A_long w = src.cols;
		A_long h = src.rows;

		CV32FC4_Pixel* inD = (CV32FC4_Pixel*)src.data;
		CV32FC4_Pixel* outD = (CV32FC4_Pixel*)dst.data;
		for (A_long y = 0; y < h; y++) {
			for (A_long x = 0; x < w; x++) {
				err = pix_fn((refconType)refcon, x, y, inD, outD);
				if (err != PF_Err_NONE) return err;
				inD++;
				outD++;
			}
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err ToPremultiply8(cv::Mat src)
	{
		PF_Err err = PF_Err_NONE;
		A_long w = src.cols;
		A_long ch = 4;
		A_long wt = w * ch;
		A_long h = src.rows;
		A_u_char* data = (A_u_char*)src.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				double a = (double)data[xypos + 3] / PF_MAX_CHAN8; // alpah
				data[xypos + BLUE] = RoundByteFpLong(data[xypos + BLUE] * a); //blue
				data[xypos + GREEN] = RoundByteFpLong(data[xypos + GREEN] * a); //green
				data[xypos + RED] = RoundByteFpLong(data[xypos + RED] * a); //red
				xypos += ch;
			}
			ypos += wt;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err ToPremultiply16(cv::Mat src)
	{
		PF_Err err = PF_Err_NONE;
		A_long w = src.cols;
		A_long ch = 4;
		A_long wt = w * ch;
		A_long h = src.rows;
		A_u_short* data = (A_u_short*)src.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				double a = (double)data[xypos + 3] / PF_MAX_CHAN16; // alpah
				data[xypos + BLUE] = RoundShortFpLong(data[xypos + 0] * a); //blue
				data[xypos + GREEN] = RoundShortFpLong(data[xypos + 1] * a); //green
				data[xypos + RED] = RoundShortFpLong(data[xypos + 2] * a); //red

				xypos += ch;
			}
			ypos += wt;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err ToPremultiply32(cv::Mat src)
	{
		PF_Err err = PF_Err_NONE;
		A_long w = src.cols;
		A_long ch = 4;
		A_long wt = w * ch;
		A_long h = src.rows;
		PF_FpShort* data = (PF_FpShort*)src.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				double a = (double)data[xypos + 3]; // alpah
				data[xypos + BLUE] = RoundFpShortDouble(data[xypos + 0] * a); //blue
				data[xypos + GREEN] = RoundFpShortDouble(data[xypos + 1] * a); //green
				data[xypos + RED] = RoundFpShortDouble(data[xypos + 2] * a); //red
				xypos += ch;
			}
			ypos += wt;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err ToPremultiply(CAE *ae, cv::Mat src)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return ToPremultiply32(src);
			break;
		case PF_PixelFormat_ARGB64:
			return ToPremultiply16(src);
			break;
		case PF_PixelFormat_ARGB32:
		default:
			return ToPremultiply8(src);
			break;
		}

	}
	//*********************************************************************************
	static PF_Err FromPremultiply8(cv::Mat src)
	{
		PF_Err err = PF_Err_NONE;
		A_long w = src.cols;
		A_long ch = 4;
		A_long wt = w * ch;
		A_long h = src.rows;
		A_u_char* data = (A_u_char*)src.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				double a =  PF_MAX_CHAN8 / (double)data[xypos + ALPHA] ; // alpah
				data[xypos + BLUE] = RoundByteFpLong(data[xypos + BLUE] * a); //blue
				data[xypos + GREEN] = RoundByteFpLong(data[xypos + GREEN] * a); //green
				data[xypos + RED] = RoundByteFpLong(data[xypos + RED] * a); //red
				xypos += ch;
			}
			ypos += wt;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err FromPremultiply16(cv::Mat src)
	{
		PF_Err err = PF_Err_NONE;
		A_long w = src.cols;
		A_long ch = 4;
		A_long wt = w * ch;
		A_long h = src.rows;
		A_u_short* data = (A_u_short*)src.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				double a = PF_MAX_CHAN16 / (double)data[xypos + ALPHA]; // alpah
				data[xypos + BLUE] = RoundShortFpLong(data[xypos + BLUE] * a); //blue
				data[xypos + GREEN] = RoundShortFpLong(data[xypos + GREEN] * a); //green
				data[xypos + RED] = RoundShortFpLong(data[xypos + RED] * a); //red
				xypos += ch;
			}
			ypos += wt;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err FromPremultiply32(cv::Mat src)
	{
		PF_Err err = PF_Err_NONE;
		A_long w = src.cols;
		A_long ch = 4;
		A_long wt = w * ch;
		A_long h = src.rows;
		PF_FpShort* data = (PF_FpShort*)src.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				double a = 1 / (double)data[xypos + ALPHA]; // alpah
				data[xypos + BLUE] = RoundFpShortDouble(data[xypos + BLUE] * a); //blue
				data[xypos + GREEN] = RoundFpShortDouble(data[xypos + GREEN] * a); //green
				data[xypos + RED] = RoundFpShortDouble(data[xypos + RED] * a); //red
				xypos += ch;
			}
			ypos += wt;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err FromPremultiply(CAE *ae, cv::Mat src)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return FromPremultiply32(src);
			break;
		case PF_PixelFormat_ARGB64:
			return FromPremultiply16(src);
			break;
		case PF_PixelFormat_ARGB32:
		default:
			return FromPremultiply8(src);
			break;
		}
	}
	//*********************************************************************************
	//ピクセルの通常合成
	//s に ｄを足す
	static CV8UC4_Pixel BlendPx8(CV8UC4_Pixel s, CV8UC4_Pixel d)
	{
		if (d.alpha <= 0) return s;

		if (s.alpha <= 0) return d;
		if (s.alpha >= PF_MAX_CHAN8) return s;

		double sa2 = (double)s.alpha / PF_MAX_CHAN8;
		double sa1 = (1 - sa2);

		CV8UC4_Pixel ret;
		ret.blue = RoundByteFpLong(d.blue * sa1 + s.blue * sa2);
		ret.green = RoundByteFpLong(d.green * sa1 + s.green * sa2);
		ret.red = RoundByteFpLong(d.red * sa1 + s.red * sa2);
		ret.alpha = RoundByteFpLong(d.alpha + s.alpha * sa2);
		
		return ret;

	}
	//*********************************************************************************
	//ピクセルの通常合成
	static CV16UC4_Pixel BlendPx16(CV16UC4_Pixel s, CV16UC4_Pixel d)
	{
		if (d.alpha <= 0) return s;

		if (s.alpha <= 0) return d;
		if (s.alpha >= PF_MAX_CHAN16) return s;

		double sa2 = (double)s.alpha / PF_MAX_CHAN16;
		double sa1 = (1 - sa2);

		CV16UC4_Pixel ret;
		ret.blue = RoundShortFpLong(d.blue * sa1 + s.blue * sa2);
		ret.green = RoundShortFpLong(d.green * sa1 + s.green * sa2);
		ret.red = RoundShortFpLong(d.red * sa1 + s.red * sa2);
		ret.alpha = RoundShortFpLong(d.alpha + s.alpha * sa2);

		return ret;

	}
	//*********************************************************************************
	//ピクセルの通常合成
	static CV32FC4_Pixel BlendPx32(CV32FC4_Pixel s, CV32FC4_Pixel d)
	{
		if (d.alpha <= 0) return s;

		if (s.alpha <= 0) return d;
		if (s.alpha >= 1) return s;

		double sa2 = (double)s.alpha;
		double sa1 = (1 - sa2);

		CV32FC4_Pixel ret;
		ret.blue = RoundFpShortDouble((double)d.blue * sa1 + (double)s.blue * sa2);
		ret.green = RoundFpShortDouble((double)d.green * sa1 + (double)s.green * sa2);
		ret.red = RoundFpShortDouble((double)d.red * sa1 + (double)s.red * sa2);
		ret.alpha = RoundFpShortDouble((double)d.alpha + (double)s.alpha * sa2);

		return ret;

	}
	//*********************************************************************************
	//ピクセルのスクリーン合成
	static CV8UC4_Pixel ScreenPx8(CV8UC4_Pixel s, CV8UC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		/*
			  1 - (1-s)*(1-d)
			  1 - ((1-d)-s*(1-d))
			  1 - (1-d-s*1+s*d)
			  1 - 1+d+s*1-s*d
			  d + s - s*d
		*/
		CV8UC4_Pixel ret;
		ret.blue = RoundByteLong((A_long)s.blue + (A_long)d.blue - (A_long)s.blue * (A_long)d.blue/PF_MAX_CHAN8);
		ret.green = RoundByteLong((A_long)s.green + (A_long)d.green - (A_long)s.green * (A_long)d.green / PF_MAX_CHAN8);
		ret.red = RoundByteLong((A_long)s.red + (A_long)d.red - (A_long)s.red * (A_long)d.red / PF_MAX_CHAN8);
		ret.alpha = RoundByteLong((A_long)s.alpha + (A_long)d.alpha - (A_long)s.alpha * (A_long)d.alpha / PF_MAX_CHAN8);

		return ret;
	}
	//*********************************************************************************
	//ピクセルのスクリーン合成
	static CV16UC4_Pixel ScreenPx16(CV16UC4_Pixel s, CV16UC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV16UC4_Pixel ret;
		ret.blue = RoundShort((A_long)s.blue + (A_long)d.blue - (A_long)s.blue * (A_long)d.blue / PF_MAX_CHAN16);
		ret.green = RoundShort((A_long)s.green + (A_long)d.green - (A_long)s.green * (A_long)d.green / PF_MAX_CHAN16);
		ret.red = RoundShort((A_long)s.red + (A_long)d.red - (A_long)s.red * (A_long)d.red / PF_MAX_CHAN16);
		ret.alpha = RoundShort((A_long)s.alpha + (A_long)d.alpha - (A_long)s.alpha * (A_long)d.alpha / PF_MAX_CHAN16);

		return ret;
	}
	//*********************************************************************************
	//ピクセルのスクリーン合成
	static CV32FC4_Pixel ScreenPx32(CV32FC4_Pixel s, CV32FC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV32FC4_Pixel ret;
		ret.blue = RoundFpShortDouble((double)s.blue + (double)d.blue - (double)s.blue * (double)d.blue);
		ret.green = RoundFpShortDouble((double)s.green + (double)d.green - (double)s.green * (double)d.green);
		ret.red = RoundFpShortDouble((double)s.red + (double)d.red - (double)s.red * (double)d.red);
		ret.alpha = RoundFpShortDouble((double)s.alpha + (double)d.alpha - (double)s.alpha * (double)d.alpha);

		return ret;
	}
	//*********************************************************************************
	// ピクセルの明るさ（明）合成
	// Premultiply状態じゃないと結果がおかしくなる
	static CV8UC4_Pixel LightenPx8(CV8UC4_Pixel s, CV8UC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV8UC4_Pixel ret;
		ret.blue = s.blue > d.blue ? s.blue : d.blue;
		ret.green = s.green > d.green ? s.green : d.green;
		ret.red = s.red > d.red ? s.red : d.red;
		ret.alpha = s.alpha > d.alpha ? s.alpha : d.alpha;
		return ret;
	}
	//*********************************************************************************
	// ピクセルの明るさ（明）合成
	// Premultiply状態じゃないと結果がおかしくなる
	static CV16UC4_Pixel LightenPx16(CV16UC4_Pixel s, CV16UC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV16UC4_Pixel ret;
		ret.blue = s.blue > d.blue ? s.blue : d.blue;
		ret.green = s.green > d.green ? s.green : d.green;
		ret.red = s.red > d.red ? s.red : d.red;
		ret.alpha = s.alpha > d.alpha ? s.alpha : d.alpha;
		return ret;
	}
	//*********************************************************************************
	// ピクセルの明るさ（明）合成
	// Premultiply状態じゃないと結果がおかしくなる
	static CV32FC4_Pixel LightenPx32(CV32FC4_Pixel s, CV32FC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV32FC4_Pixel ret;
		ret.blue = s.blue > d.blue ? s.blue : d.blue;
		ret.green = s.green > d.green ? s.green : d.green;
		ret.red = s.red > d.red ? s.red : d.red;
		ret.alpha = s.alpha > d.alpha ? s.alpha : d.alpha;
		return ret;
	}
	//*********************************************************************************
	//ピクセルの加算合成
	static CV8UC4_Pixel AddPx8(CV8UC4_Pixel s, CV8UC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV8UC4_Pixel ret;
		ret.blue = RoundByteLong((A_long)s.blue + (A_long)d.blue);
		ret.green = RoundByteLong((A_long)s.green + (A_long)d.green);
		ret.red = RoundByteLong((A_long)s.red + (A_long)d.red);
		ret.alpha = RoundByteLong((A_long)s.alpha + (A_long)d.alpha);
		return ret;
	}
	//*********************************************************************************
	//ピクセルの加算合成
	static CV16UC4_Pixel AddPx16(CV16UC4_Pixel s, CV16UC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV16UC4_Pixel ret;
		ret.blue = RoundShort((A_long)s.blue + (A_long)d.blue);
		ret.green = RoundShort((A_long)s.green + (A_long)d.green);
		ret.red = RoundShort((A_long)s.red + (A_long)d.red);
		ret.alpha = RoundShort((A_long)s.alpha + (A_long)d.alpha);
		return ret;
	}
	//*********************************************************************************
	//ピクセルの加算合成
	static CV32FC4_Pixel AddPx32(CV32FC4_Pixel s, CV32FC4_Pixel d)
	{
		if (s.alpha <= 0) return d;
		if (d.alpha <= 0) return s;

		CV32FC4_Pixel ret;
		ret.blue = RoundFpShort2((double)s.blue + (double)d.blue);
		ret.green = RoundFpShort2((double)s.green + (double)d.green);
		ret.red = RoundFpShort2((double)s.red + (double)d.red);
		ret.alpha = RoundFpShort2((double)s.alpha + (double)d.alpha);
		return ret;
	}
	//*********************************************************************************
	static CV8UC4_Pixel Blend8(CV8UC4_Pixel s, CV8UC4_Pixel d, PF_FpLong par/*0..1 max*/)
	{
		CV8UC4_Pixel ret;
		PF_FpLong par2 = 1 - par;
		
		ret.red = RoundByteDouble((double)d.red * par2 + (double)s.red * par);
		ret.green = RoundByteDouble((double)d.green * par2 + (double)s.green * par);
		ret.blue = RoundByteDouble((double)d.blue * par2 + (double)s.blue * par);
		ret.alpha = RoundByteDouble((double)d.alpha * par2 + (double)s.alpha * par);

		return ret;
	}
	//*********************************************************************************
	static CV16UC4_Pixel Blend16(CV16UC4_Pixel s, CV16UC4_Pixel d, PF_FpLong par/*0..1 max*/)
	{
		CV16UC4_Pixel ret;
		PF_FpLong par2 = 1 - par;

		ret.red = RoundShortFpLong((double)d.red * par2 + (double)s.red * par);
		ret.green = RoundShortFpLong((double)d.green * par2 + (double)s.green * par);
		ret.blue = RoundShortFpLong((double)d.blue * par2 + (double)s.blue * par);
		ret.alpha = RoundShortFpLong((double)d.alpha * par2 + (double)s.alpha * par);

		return ret;
	}
	//*********************************************************************************
	static CV32FC4_Pixel Blend32(CV32FC4_Pixel s, CV32FC4_Pixel d, PF_FpLong par/*0..1 max*/)
	{
		CV32FC4_Pixel ret;
		double par2 = 1 - par;

		ret.red = RoundFpShort2((double)d.red * par2 + (double)s.red * par);
		ret.green = RoundFpShort2((double)d.green * par2 + (double)s.green * par);
		ret.blue = RoundFpShort2((double)d.blue * par2 + (double)s.blue * par);
		ret.alpha = RoundFpShort2((double)d.alpha * par2 + (double)s.alpha * par);

		return ret;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendNormal8(cv::Mat src, cv::Mat dst,PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV8UC4_Pixel* srcD = (CV8UC4_Pixel*)src.data;
		CV8UC4_Pixel* dstD = (CV8UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV8UC4_Pixel a = BlendPx8(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend8(a, dstD[xypos],par);
				xypos++;
			}
			ypos+=w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendNormal16(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV16UC4_Pixel* srcD = (CV16UC4_Pixel*)src.data;
		CV16UC4_Pixel* dstD = (CV16UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV16UC4_Pixel a = BlendPx16(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend16(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendNormal32(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV32FC4_Pixel* srcD = (CV32FC4_Pixel*)src.data;
		CV32FC4_Pixel* dstD = (CV32FC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV32FC4_Pixel a = BlendPx32(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend32(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err BlendNormal(CAE *ae, cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return BlendNormal32(src,dst,par);
			break;
		case PF_PixelFormat_ARGB64:
			return BlendNormal16(src, dst, par);
			break;
		case PF_PixelFormat_ARGB32:
		default:
			return BlendNormal8(src, dst, par);
			break;
		}
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendScreen8(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;
		A_long w = src.cols;
		A_long h = src.rows;
		CV8UC4_Pixel* srcD = (CV8UC4_Pixel*)src.data;
		CV8UC4_Pixel* dstD = (CV8UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV8UC4_Pixel a = ScreenPx8(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend8(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendScreen16(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV16UC4_Pixel* srcD = (CV16UC4_Pixel*)src.data;
		CV16UC4_Pixel* dstD = (CV16UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV16UC4_Pixel a = ScreenPx16(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend16(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendScreen32(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV32FC4_Pixel* srcD = (CV32FC4_Pixel*)src.data;
		CV32FC4_Pixel* dstD = (CV32FC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV32FC4_Pixel a = ScreenPx32(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend32(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err BlendScreen(CAE *ae, cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return BlendScreen32(src, dst, par);
			break;
		case PF_PixelFormat_ARGB64:
			return BlendScreen16(src, dst, par);
			break;
		case PF_PixelFormat_ARGB32:
		default:
			return BlendScreen8(src, dst, par);
			break;
		}
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendLighten8(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV8UC4_Pixel* srcD = (CV8UC4_Pixel*)src.data;
		CV8UC4_Pixel* dstD = (CV8UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV8UC4_Pixel a = LightenPx8(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend8(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendLighten16(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV16UC4_Pixel* srcD = (CV16UC4_Pixel*)src.data;
		CV16UC4_Pixel* dstD = (CV16UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV16UC4_Pixel a = LightenPx16(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend16(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendLighten32(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV32FC4_Pixel* srcD = (CV32FC4_Pixel*)src.data;
		CV32FC4_Pixel* dstD = (CV32FC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV32FC4_Pixel a = LightenPx32(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend32(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err BlendLighten(CAE *ae, cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return BlendLighten32(src, dst, par);
			break;
		case PF_PixelFormat_ARGB64:
			return BlendLighten16(src, dst, par);
			break;
		case PF_PixelFormat_ARGB32:
		default:
			return BlendLighten8(src, dst, par);
			break;
		}
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendAdd8(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV8UC4_Pixel* srcD = (CV8UC4_Pixel*)src.data;
		CV8UC4_Pixel* dstD = (CV8UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV8UC4_Pixel a = AddPx8(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend8(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendAdd16(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV16UC4_Pixel* srcD = (CV16UC4_Pixel*)src.data;
		CV16UC4_Pixel* dstD = (CV16UC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV16UC4_Pixel a = AddPx16(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend16(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	// srcをdstに合成
	static PF_Err BlendAdd32(cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_Err err = PF_Err_NONE;
		if (par <= 0) return err;

		A_long w = src.cols;
		A_long h = src.rows;
		CV32FC4_Pixel* srcD = (CV32FC4_Pixel*)src.data;
		CV32FC4_Pixel* dstD = (CV32FC4_Pixel*)dst.data;

		A_long ypos = 0;
		for (A_long y = 0; y < h; y++) {
			A_long xypos = ypos;
			for (A_long x = 0; x < w; x++) {
				CV32FC4_Pixel a = AddPx32(srcD[xypos], dstD[xypos]);
				dstD[xypos] = Blend32(a, dstD[xypos], par);
				xypos++;
			}
			ypos += w;
		}
		return err;
	}
	//*********************************************************************************
	static PF_Err BlendAdd(CAE *ae, cv::Mat src, cv::Mat dst, PF_FpLong par/*0..1 max*/)
	{
		PF_PixelFormat format = ae->pixelFormat();
		switch (format)
		{
		case PF_PixelFormat_ARGB128:
			return BlendAdd32(src, dst, par);
			break;
		case PF_PixelFormat_ARGB64:
			return BlendAdd16(src, dst, par);
			break;
		case PF_PixelFormat_ARGB32:
		default:
			return BlendAdd8(src, dst, par);
			break;
		}
	}
};





#endif //CAE_OpenCV_H
