#pragma once
#ifndef CAE_OpenCV_H
#define CAE_OpenCV_H

//******************************************************************************
//äeéÌÉwÉbÉ_Å[ìoò^
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

//OpenCVÇÃÉwÉbÉ_Å[
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>



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
	static cv::Mat WorldToMat8(PF_EffectWorldPtr world)
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
				mData[matPosx + 0] = wData[wldPosx].blue;
				mData[matPosx + 1] = wData[wldPosx].green;
				mData[matPosx + 2] = wData[wldPosx].red;
				mData[matPosx + 3] = wData[wldPosx].alpha;

			}
			matPos += czw;
			wldPos += wt;
		}
		return ret;
	}
	static cv::Mat WorldToMat16(PF_EffectWorldPtr world)
	{
		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_Pixel16);
		int h = world->height;

		int cz = 4;
		int czw = cz * w;

		cv::Mat ret(cv::Size((int)world->width, (int)world->height), CV_16UC4);

		A_u_short* mData = (A_u_short*)ret.data;
		PF_Pixel16* wData = (PF_Pixel16 *)world->data;


		A_long matPos = 0;
		A_long wldPos = 0;
		for (A_long y = 0; y < h; y++)
		{

			for (A_long x = 0; x < w; x++)
			{
				A_long matPosx = matPos + x * cz;
				A_long wldPosx = wldPos + x;
				mData[matPosx + 0] = wData[wldPosx].blue;
				mData[matPosx + 1] = wData[wldPosx].green;
				mData[matPosx + 2] = wData[wldPosx].red;
				mData[matPosx + 3] = wData[wldPosx].alpha;

			}
			matPos += czw;
			wldPos += wt;
		}
		return ret;
	}
	static cv::Mat WorldToMat32(PF_EffectWorldPtr world)
	{
		int w = world->width;
		int wt = world->rowbytes / sizeof(PF_PixelFloat);
		int h = world->height;

		int cz = 4;
		int czw = cz * w;

		cv::Mat ret(cv::Size((int)world->width, (int)world->height), CV_32FC4);

		A_u_short* mData = (A_u_short*)ret.data;
		PF_Pixel16* wData = (PF_Pixel16 *)world->data;


		A_long matPos = 0;
		A_long wldPos = 0;
		for (A_long y = 0; y < h; y++)
		{

			for (A_long x = 0; x < w; x++)
			{
				A_long matPosx = matPos + x * cz;
				A_long wldPosx = wldPos + x;
				mData[matPosx + 0] = wData[wldPosx].blue;
				mData[matPosx + 1] = wData[wldPosx].green;
				mData[matPosx + 2] = wData[wldPosx].red;
				mData[matPosx + 3] = wData[wldPosx].alpha;

			}
			matPos += czw;
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
				wData[wldPosx].blue = mData[matPosx + 0];
				wData[wldPosx].green = mData[matPosx + 1];
				wData[wldPosx].red = mData[matPosx + 2];
				wData[wldPosx].alpha = mData[matPosx + 3];

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
				wData[wldPosx].blue = mData[matPosx + 0];
				wData[wldPosx].green = mData[matPosx + 1];
				wData[wldPosx].red = mData[matPosx + 2];
				wData[wldPosx].alpha = mData[matPosx + 3];

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
				wData[wldPosx].blue = mData[matPosx + 0];
				wData[wldPosx].green = mData[matPosx + 1];
				wData[wldPosx].red = mData[matPosx + 2];
				wData[wldPosx].alpha = mData[matPosx + 3];

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
	PF_Err iterate8( refconType refcon, cv::Mat src, cv::Mat dst,
		PF_Err(*pix_fn)(refconType refcon, A_long x, A_long y, A_u_char *in, A_u_char *out)
	)
	{
		if ((src.cols != dst.cols) || (src.rows != dst.rows)) return PF_Err_INVALID_INDEX;
		A_long w = src.cols;
		A_long h = src.rows;

		A_u_char* inD = (A_u_char*)src.data;
		A_u_char* outD = (A_u_char*)dst.data;
		for (A_long y = 0; y < h; y++) {
			for (A_long x = 0; x < w; x++) {
				err = pix_fn((refconType)refcon, x, y, inD, outD);
				if (err != PF_Err_NONE) return err;
				inD+=4;
				outD+=4;
			}
		}
	}
	//*********************************************************************************
	PF_Err iterate16(refconType refcon, cv::Mat src, cv::Mat dst,
		PF_Err(*pix_fn)(refconType refcon, A_long x, A_long y, A_u_short *in, A_u_short *out)
	)
	{
		if ((src.cols != dst.cols) || (src.rows != dst.rows)) return PF_Err_INVALID_INDEX;
		A_long w = src.cols;
		A_long h = src.rows;

		A_u_short* inD = (A_u_short*)src.data;
		A_u_short* outD = (A_u_short*)dst.data;
		for (A_long y = 0; y < h; y++) {
			for (A_long x = 0; x < w; x++) {
				err = pix_fn((refconType)refcon, x, y, inD, outD);
				if (err != PF_Err_NONE) return err;
				inD += 4;
				outD += 4;
			}
		}
	}
	//*********************************************************************************
	PF_Err iterate32(refconType refcon, cv::Mat src, cv::Mat dst,
		PF_Err(*pix_fn)(refconType refcon, A_long x, A_long y, PF_FpShort *in, PF_FpShort *out)
	)
	{
		PF_Err err;
		if ((src.cols != dst.cols) || (src.rows != dst.rows)) return PF_Err_INVALID_INDEX;
		A_long w = src.cols;
		A_long h = src.rows;

		PF_FpShort* inD = (PF_FpShort*)src.data;
		PF_FpShort* outD = (PF_FpShort*)dst.data;
		for (A_long y = 0; y < h; y++) {
			for (A_long x = 0; x < w; x++) {
				err = pix_fn((refconType)refcon, x, y, inD, outD);
				if (err != PF_Err_NONE) return err;
				inD += 4;
				outD += 4;
			}
		}
		return err;
	}
};





#endif //CAE_OpenCV_H
