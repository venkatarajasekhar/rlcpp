/*
 * Copyright (c) 2015 Vrije Universiteit Brussel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "softmaxlearning.h"

#include <nnetcpp/activation.h>

#include <cmath>
#include <numeric>

SoftmaxLearning::SoftmaxLearning(AbstractLearning *learning, float temperature)
: _learning(learning),
  _temperature(temperature)
{
}

void SoftmaxLearning::actions(Episode *episode, std::vector<float> &probabilities, float &td_error)
{
    // Let the wrapped learning algorithm compute the premilinary values
    _learning->actions(episode, probabilities, td_error);
    _temperature = adjustTemperature(episode, td_error);

    // Take the exponentials of all those values
    for (float &v : probabilities) {
        v = nnetcppinternal::_exp(v / _temperature);
    }

    float sum = std::accumulate(probabilities.begin(), probabilities.end(), 0.0f);

    // Compute exp(v / T) / sum(vi / T) for all v
    for (float &v : probabilities) {
        v /= sum;
    }
}

float SoftmaxLearning::adjustTemperature(Episode *episode, float td_error)
{
    (void) episode;
    (void) td_error;

    // By default, use a fixed temperature
    return _temperature;
}
