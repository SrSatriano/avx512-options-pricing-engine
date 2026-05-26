#pragma once

namespace pricing {

/** European call — closed form */
double black_scholes_call(double spot, double strike, double rate, double vol, double t);

}  // namespace pricing
