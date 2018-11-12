/**
 * @file define.h
 * @author Keren Zhu
 * @date 10/05/2018
 */

#ifndef AROUTER_PARAMETER_H_
#define AROUTER_PARAMETER_H_

#include "type.h"

PROJECT_NAMESPACE_BEGIN

/// How large should the track around the pin be reserved
constexpr IntType PIN_NEIGHBOR_OCCUPTY_SIZE = 3;

/// Whether read branch/2-pin-net-spliting from the global router
constexpr bool READ_GR_BRANCH = false;

/// Resistance rouding precision
constexpr IntType RESISTANCE_PRECISION = 1000000;

PROJECT_NAMESPACE_END
#endif ///AROUTER_PARAMETER_H_
