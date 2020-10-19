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

Encoder::Encoder(PinName pinA, PinName pinB, PinName pinBtnPush) :
    _encInA(pinA, PullUp),
    _encInB(pinB, PullUp),
    _btnPush(pinBtnPush, PullUp)
{
    _encLast = 0;
    _encDelta = 0;
}

void Encoder::process()
{
    int i = 0;

    int btnPush = _btnPush;
    if (btnPush != _btnPushOld) {
        if (_btnPushOld) {
            _btnPressed = true;
        } else {
            _btnReleased = true;
        }
    } else {
        _btnPressed = false;
        _btnReleased = false;
    }
    _btnPushOld = btnPush;

    if (_encInB) {
        i = 1;
    }
    if (_encInA) {
        i ^= 3;                 // convert gray to binary
    }

    i -= _encLast;              // difference new - last

    if (i & 1) {                // bit 0 = value (1)
        _encLast += i;          // store new as next last
        _encDelta += (i & 2) - 1;   // bit 1 = direction (+/-)
    }
}

void Encoder::read(int &delta, bool &btnPressed, bool &btnReleased)
{
    process();
    delta = _encDelta;
    btnPressed = _btnPressed;
    btnReleased = _btnReleased;
    _encDelta = 0;
}
