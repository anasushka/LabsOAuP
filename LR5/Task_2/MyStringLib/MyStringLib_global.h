#pragma once
#ifndef MYSTRINGLIB_GLOBAL_H
#define MYSTRINGLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYSTRINGLIB_LIBRARY)
#define MYSTRINGLIB_EXPORT Q_DECL_EXPORT
#else
#define MYSTRINGLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MYSTRINGLIB_GLOBAL_H
