/*
 MIT License

Copyright (c) 2020 JojoS

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*
 */

#include "EncoderIrq.h"

EncoderIrq::EncoderIrq(PinName pinA, PinName pinB) :
    _encInA(pinA, PullUp),
    _encInB(pinB, PullUp)
{
    _encLast = 0;
    _encDelta = 0;
}

int EncoderIrq::read()
{
    int delta = _encDelta;
    _encDelta = 0;
    return delta;
}

void EncoderIrq::_isrRisingA()
{
    if (_encInB) {
        _encDelta++;
    } else {
        _encDelta--;
    }
}

void EncoderIrq::_isrFallingA();
{
    if (_encInB) {
        _encDelta--;
    } else {
        _encDelta++;
    }
}

void EncoderIrq::_isrRisingB();
{
    if (_encInA) {
        _encDelta--;
    } else {
        _encDelta++;
    }
}

void EncoderIrq::_isrFallingB();
{
    if (_encInA) {
        _encDelta++;
    } else {
        _encDelta--;
    }
}

