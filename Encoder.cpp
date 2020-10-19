/*
 MIT License

Copyright (c) 2020 JojoS
The Algorithm is based on a code from P. Dannegger
https://www.mikrocontroller.net/articles/Drehgeber

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

#include "Encoder.h"

static constexpr int8_t table[16] = {0,0,-1,0,0,0,0,1,1,0,0,0,0,-1,0,0};

Encoder::Encoder(PinName pinA, PinName pinB, PinName pinBtnPush, std::chrono::microseconds sampleTime) :
    _encInA(pinA, PullUp),
    _encInB(pinB, PullUp),
    _btnPush(pinBtnPush, PullUp)
{
    _encLast = 0;
    _encDelta = 0;
    if (sampleTime > 0s) {
        _ticker.attach(callback(this, &Encoder::process), sampleTime);
    }
}

void Encoder::process()
{
    int btnPush = _btnPush;
    if (btnPush != _btnPushOld) {
        if (_btnPushOld) {
            _btnPressed = true;
        } else {
            _btnReleased = true;
        }
    }
    _btnPushOld = btnPush;

    _encLast = (_encLast << 2) & 0xf;

    if (_encInB) {
        _encLast |= 2;
    }
    if (_encInA) {
        _encLast |= 1;
    }

    _encDelta += table[_encLast];
}

void Encoder::read(int &delta, bool &btnPressed, bool &btnReleased)
{
    delta = _encDelta;
    btnPressed = _btnPressed;
    btnReleased = _btnReleased;
    _encDelta = 0;
    _btnPressed = false;
    _btnReleased = false;
}
