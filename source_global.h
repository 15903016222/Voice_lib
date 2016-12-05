#ifndef SOURCE_GLOBAL_H
#define SOURCE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SOURCE_LIBRARY)
#  define SOURCESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOURCESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SOURCE_GLOBAL_H
