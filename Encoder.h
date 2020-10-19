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

#ifndef __Encoder_h__
#define __Encoder_h__

#include "mbed.h"

class Encoder {
public:
    Encoder(PinName pinA, PinName pinB, PinName pinBtnPush);

    void read(int &delta, bool &btnPressed, bool &btnReleased);

private:
    void process();

    DigitalIn   _encInA;
    DigitalIn   _encInB;
    DigitalIn   _btnPush;
    int         _btnPushOld;
    int         _encDelta;
    int         _encLast;
    bool        _btnPressed;
    bool        _btnReleased;
};

#endif