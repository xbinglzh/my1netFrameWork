#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include <boost/scoped_ptr.hpp>

class AppLauncher;

class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
    virtual void applicationDidBecomeActive();
    
private:
    void didFinishedLauchApp();
    
private:
    boost::scoped_ptr<AppLauncher> _launcher;
};

#endif // _APP_DELEGATE_H_

