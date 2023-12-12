/*****************************************************************//**
 * \file   UtilMacro.h
 * \brief  マクロの定義
 *
 * \author 山本莉久
 * \date   March 2023
 *********************************************************************/
#pragma once
#define	SAFE_DELETE(x)	if(x){delete x;x=NULL;}