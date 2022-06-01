#include "GameScene.h"
#include "mymap.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in originalHelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //
    //auto closeItem = MenuItemImage::create(
    //    "CloseNormal.png",
    //    "CloseSelected.png",
    //    CC_CALLBACK_1(GameScene::menuItemCallback, this, "Close"));
    //auto menuItemFont = MenuItemFont::create("Begin", CC_CALLBACK_1(GameScene::menuItemCallback, this, "Font"));
    //auto menuItemImage = MenuItemImage::create(
    //    "SoundOpen.png",
    //    "SoundClose.png",
    //    CC_CALLBACK_1(GameScene::menuItemCallback, this, "Sound"));
    //menuItemImage->setPosition(0, -50);
    ////2.创建菜单，将菜单项作为参数传入
    //Menu* pMenu = Menu::create(menuItemFont, menuItemImage, NULL);
    ////3.图层中加入菜单，设置菜单位置
    //pMenu->setPosition(480, 320);
    //addChild(pMenu);



    musicID = AudioEngine::play2d("music.mp3", true, 0.1);
    //1.创建菜单项,并设置菜单项在菜单中的位置
    //MenuItemFont:字体菜单项
    MenuItemFont* menuItemFont = MenuItemFont::create(
        "Wilderness",
        CC_CALLBACK_1(GameScene::menuItemCallback,
            this,
            "Font"));
    float x_Font = origin.x + visibleSize.width / 2;
    float y_Font = origin.y + visibleSize.height - menuItemFont->getContentSize().height;
    menuItemFont->setPosition(x_Font, y_Font);

    //MenuItemImage:图片菜单项
    MenuItemImage* menuItemImage = MenuItemImage::create(
        "BeginNormal.png",
        "BeginSelected.png",
        CC_CALLBACK_1(GameScene::menuItemCallback, 
            this,
            "Begin"));
    
    menuItemImage->setScale(0.5f);
    float x_Begin = x_Font;
    float y_Begin = origin.y + visibleSize.height - menuItemImage->getContentSize().height ;
    menuItemImage->setPosition(x_Begin, y_Begin);

    //MenuItemLabel:标签菜单项
    MenuItemLabel* menuItemLabel = MenuItemLabel::create(Label::createWithTTF("Let's start the game!", "fonts/arial.ttf", 30),
        CC_CALLBACK_1(GameScene::menuItemCallback, 
            this,
            "1"));
    float x_Label = x_Font;
    float y_Label = origin.y + visibleSize.height - menuItemLabel->getContentSize().height - 60;
    menuItemLabel->setPosition(x_Label, y_Label);

    //MenuItemToggle:开关菜单项
    MenuItemToggle* menuItemToggle = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(GameScene::menuItemCallback, this,"Music"),
        MenuItemFont::create("On"),
        MenuItemFont::create("Off"),
        NULL);
    float x_Switch = x_Font;
    float y_Switch = origin.y + visibleSize.height / 8;
    menuItemToggle->setPosition(x_Switch, y_Switch);

    MenuItemImage* SoundItem = MenuItemImage::create(
        "SoundOpen.png",
        "SoundClose.png",
        CC_CALLBACK_1(GameScene::menuItemCallback,
            this,
            "Menu"));
    SoundItem->setScale(0.6f);
    float x_Sound = x_Font;
    float y_Sound = origin.y + visibleSize.height / 8+ SoundItem->getContentSize().height/2;
    SoundItem->setPosition(x_Sound, y_Sound);
    //2.创建菜单，将菜单项作为参数传入
    Menu* pMenu = Menu::create(menuItemFont, menuItemImage, menuItemLabel, menuItemToggle,SoundItem, NULL);
    //3.图层中加入菜单，设置菜单位置
    //需要把菜单的位置设置在屏幕原点,以便设置菜单项的位置
    pMenu->setPosition(0,0);
    addChild(pMenu);
   
    return true;
}

void GameScene::menuItemCallback(cocos2d::Ref* pSender, std::string eventname)
{
    if(eventname=="Begin")
        Director::getInstance()->replaceScene(MapLayer::createMapScene());
    if (eventname == "Music")
    {
        static int _play = 1;
        if (_play == 1) {
            AudioEngine::pause(musicID);
            _play--;
        }
        else
        {
            AudioEngine::resume(musicID);
            _play++;
        }
    }
}


