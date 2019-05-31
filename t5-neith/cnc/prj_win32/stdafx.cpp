
// stdafx.cpp : source file that includes just the standard includes
// cnc.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

//½â¾ö error LNK2001: unresolved external symbol __iob
extern "C" { FILE _iob[3] = {__iob_func()[0], __iob_func()[1], __iob_func()[2]}; }

