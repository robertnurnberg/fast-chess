#pragma once

#include <string>

#include <core/helper.hpp>
#include <types/enums.hpp>

namespace fastchess::config {

struct Sprt {
    bool enabled = false;
    double alpha = 0.0;
    double beta  = 0.0;
    double elo0  = 0.0;
    double elo1  = 0.0;
    // available as 3 models: "normalized", "bayesian", and "logistic"
    // bayesian model only available when -penta report=false
    std::string model = "normalized";
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Sprt, alpha, beta, elo0, elo1, model, enabled)

}  // namespace fastchess::config