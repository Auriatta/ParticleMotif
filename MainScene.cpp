/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"

USING_NS_CC;





Scene* Main::createScene()
{
    return Main::create();;
}



// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }


    cocos2d::LayerColor* bg_layer = cocos2d::LayerColor::create(
        cocos2d::Color4B(246, 248, 248, 240), 1920, 1080);
    this->addChild(bg_layer, 0);
    
    this->scheduleUpdate();


    return true;
}

void Main::onEnter()
{
    Scene::onEnter();

    typedef Motif_WhiteWall Mf;

    MotifExpoRandomSample = std::make_unique<
        MotifExpositionRandom<Mf>>(MotifExposition<Mf>(1, 5, 40, 0.3),
            cocos2d::Vec4(
                BORDER_X_ORIGIN - 100, BORDER_Y_ORIGIN - 100,
                BORDER_HEIGHT + 100, BORDER_WIDTH + 100), 0.1, 0.1);

    MotifExpoRandomSample->Run();
}

void Main::update(float delta)
{
    
}