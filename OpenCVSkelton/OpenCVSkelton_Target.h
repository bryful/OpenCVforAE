/*
	OpenCVSkelton

	各種定数を設定

	PiPLリソースに使う為にマクロ展開は最低限

*/


#pragma once
#ifndef OpenCVSkelton_Target_H
#define OpenCVSkelton_Target_H


#define DESCRIPTION		"OpenCVSkelton Effect Filter"

#define NAME			"OpenCVSkelton"
#define MATCH_NAME		NAME
#define CATEGORY		"OpenCV"


#define	MAJOR_VERSION	1
#define	MINOR_VERSION	0
#define	BUG_VERSION		0
#define	STAGE_VERSION		PF_Stage_DEVELOP
//#define	STAGE_VERSION		PF_Stage_ALPHA
//#define	STAGE_VERSION		PF_Stage_BETA
//#define	STAGE_VERSION		PF_Stage_RELEASE
#define	BUILD_VERSION	1

//上の定数とVERSIONの値が違うとエラーになる

#define VERSION 524290	//AE_Effects_Version.exeで上記計算して求める

//AE_out_flags.exeで求める
#define AE_OUT_FLAGS	33554496
#define AE_OUT_FLAGS2	8





#endif // OpenCVSkelton_Target_H

