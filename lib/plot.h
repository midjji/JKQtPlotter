#pragma once
#include <vector>
/**
 * @brief plot
 * @param xs
 * @param ys
 * @param title
 *
 * simple helper/wrapper,
 * this is not thread safe and requires a running QApp
 * call twice with the same name and they show up in the same window with different colors.
 */
void plot(std::vector<double> xs,
          std::vector<double> ys,
          std::string title="y(x)");
