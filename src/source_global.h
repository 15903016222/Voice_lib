#ifndef __SOURCE_GLOBAL_H__
#define __SOURCE_GLOBAL_H__

#include <QtCore/qglobal.h>

//#define SOURCESHARED_EXPORT
#if defined(SOURCE_LIBRARY)
#  define SOURCESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOURCESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // __SOURCE_GLOBAL_H__
