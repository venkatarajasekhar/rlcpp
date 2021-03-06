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

#ifndef __EGREEDYLEARNING_H__
#define __EGREEDYLEARNING_H__

#include "abstractlearning.h"

/**
 * @brief Wrapper for a learning algorithm that implements the e-Greedy action selection
 */
class EGreedyLearning : public AbstractLearning
{
    public:
        /**
         * @param learning Learning algorithm that is wrapped by this e-Greedy
         * @param epsilon Probability that an exploratory step is taken
         */
        EGreedyLearning(AbstractLearning *learning, float epsilon);
        virtual ~EGreedyLearning();

        virtual void actions(Episode *episode, std::vector<float> &probabilities, float &td_error);

    private:
        AbstractLearning *_learning;
        float _epsilon;
};

#endif
