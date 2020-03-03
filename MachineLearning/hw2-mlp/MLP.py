import os
import sys
import time
import theano
import theano.tensor as T
import tensorflow
import pandas as pd
import numpy as np
import random

class HiddenLayer(object):
    def __init__(self, rng, inputs, n_in, n_out, w = None, b = None, activation = T.tanh):
        self.input = inputs
        if w is None:
            w_values = np.asanyarray(
                rng.uniform(
                    low=-np.sqrt(6. / (n_in + n_out)),
                    high=np.sqrt(6. / (n_in + n_out)),
                    size=(n_in, n_out)
                ),
                dtype=theano.config.floatX
            )
            if activation == theano.tensor.nnet.sigmoid:
                w_values *= 4
            w = theano.shared(value=w_values, name='w', borrow=True)
        if b is None:
            b_values = np.zeros((n_out,), dtype=theano.config.floatX)
            b = theano.shared(value=b_values, name='b', borrow=True)

        self.w = w
        self.b = b

        lin_output = T.dot(inputs, self.w) + self.b
        self.output = (
            lin_output if activation is None
            else activation(lin_output)
        )
        self.params = [self.w, self.b]


class LogisticRegression(object):
    def __init__(self, inputs, n_in, n_out):
        self.w = theano.shared(
            value=np.zeros((n_in, n_out), dtype=theano.config.floatX),
            name='w',
            borrow=True
        )
        self.b = theano.shared(
            value=np.zeros(
                (n_out,),
                dtype=theano.config.floatX),
            name='b',
            borrow=True
        )
        self.p_y_given_x = T.nnet.softmax(T.dot(inputs, self.w) + self.b)
        self.y_pred = T.argmax(self.p_y_given_x, axis=1)
        self.params = [self.w, self.b]


class MLP(object):
    def __init__(self, rng, inputs, n_in, n_hidden, n_out):
        self.hiddenLayer = HiddenLayer(
            rng=rng,
            inputs=inputs,
            n_in=n_in,
            n_out=n_hidden,
            activation=T.tanh
        )
        self.logisticRegressionLayer = LogisticRegression(
            inputs=self.hiddenLayer.output,
            n_in= n_hidden,
            n_out=n_out
        )
        self.L1 = (
            abs(self.hiddenLayer.w).sum()
            + abs(self.logisticRegressionLayer.w).sum()
        )
        self.L2_sqr = (
            (self.hiddenLayer.w ** 2).sum()
            + (self.logisticRegressionLayer.w ** 2).sum()
        )
        self.negative_log_likelihood = (
            self.logisticRegressionLayer.negative_log_likelihood
        )
        self.errors = (
            self.logisticRegressionLayer.errors
        )
        self.params = (
            self.hiddenLayer.params + self.logisticRegressionLayer.params
        )


