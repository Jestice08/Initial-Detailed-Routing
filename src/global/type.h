//
// Created by Keren on 04/02/2018
//
//

#ifndef AROUTER_TYPE_H_
#define AROUTER_TYPE_H_

#include <cstdint>
#include <string>
#include <sstream>
#include "util/XYZ.h"
#include "namespace.h"

PROJECT_NAMESPACE_BEGIN
/// Built-in type aliases
using IndexType  = std::uint32_t;
using IntType    = std::int32_t;
using RealType   = double;
using Byte       = std::uint8_t;
using LocType    = std::int32_t; /// Location/design unit /// Location/design unit
 /// Location/design unit
/// Built-in type constants
constexpr IndexType INDEX_TYPE_MAX  = UINT32_MAX;
constexpr IntType INT_TYPE_MAX      = INT32_MAX;
constexpr IntType INT_TYPE_MIN      = INT32_MIN;
constexpr RealType REAL_TYPE_MAX    = 1e100;
constexpr RealType REAL_TYPE_MIN    = -1e100;
constexpr RealType REAL_TYPE_TOL    = 1e-6;

/////////////////////////////////////////////////
/// Type aliases
/////////////////////////////////////////////////
using XYIdx      = XY<IndexType>;
using CostTy     = double;
/// Using CostTy = IntType;


/// ================================================================================ 
/// Enums
/// ================================================================================ 

/// The preferred routing direction of the layer
enum class RouteDirType  : Byte
{
    HORIZONTAL = 0,
    VERTICAL   = 1,
    BOTH       = 2,
    FORBID     = 3
};

/// The type of symmetry
enum class SymType
{
    HORIZONTAL = 0,
    VERTICAL   = 1
};

PROJECT_NAMESPACE_END

#endif // AROUTER_TYPE_H_

