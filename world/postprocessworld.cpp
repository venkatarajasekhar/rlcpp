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

#include "postprocessworld.h"

#include <cmath>
#include <iostream>

PostProcessWorld::PostProcessWorld(AbstractWorld *world, unsigned int num_actions)
: AbstractWorld(num_actions),
  _world(world)
{
}

PostProcessWorld::~PostProcessWorld()
{
    delete _world;
}

void PostProcessWorld::initialState(std::vector <float> &state)
{
    _world->initialState(state);
    processState(state);
}

void PostProcessWorld::reset()
{
    _world->reset();
}

void PostProcessWorld::step(unsigned int action,
                       bool &finished,
                       float &reward,
                       std::vector<float> &state)
{
    // Let the wrapped world compute the step, then post-process it
    _world->step(action, finished, reward, state);
    processState(state);
}
