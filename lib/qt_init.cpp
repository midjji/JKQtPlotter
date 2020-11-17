#include <mutex>
#include <thread>
#include <condition_variable>
#include <qt_init.h>
#include <QCoreApplication>


namespace {

struct OnExit:public QObject{

    std::shared_ptr<std::atomic<bool>> done;
    OnExit(QObject* parent, std::shared_ptr<std::atomic<bool>> done):QObject(parent),done(done){}
    ~OnExit(){        (*done)=true;    }
};


struct QApplicationManager
{

    // if we dont own, then this gets set when the qapp quits
    std::shared_ptr<std::atomic<bool>> done=std::make_shared<std::atomic<bool>>(false);
    bool we_own_app=true;
    std::thread thr;
    QCoreApplication* app;


    ~QApplicationManager()
    {
        if(we_own_app){
            app->quit();
            if(thr.joinable()) thr.join();
            delete app;
        }
    }
    std::shared_ptr<QApplicationManager> create() {
        auto qm=std::make_shared<QApplicationManager>();
        // if an instance already exists, use it.
        // this is for interop with others who does dumb shit like opencv...
        if(QApplication::instance()!=nullptr){
            we_own_app=false;
            qm->app=QCoreApplication::instance();
            new OnExit(app, done);
            return qm;
        }

        std::atomic<bool> ready=false;
        qm->thr=std::thread([&]()
        {
            int i=1;
            qm->app = new QApplication(i,nullptr); // accessible by instance
            new OnExit(app, done);
            ready=true;
            qm->app->exec();
        });
        // neccessary because QApplication::instance() may be null untill ready=true
        while(!ready) std::this_thread::sleep_for(std::chrono::milliseconds(50));
        return qm;
    }

    void wait_for_finished() {
        while(!done) std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
};
std::mutex qapp_mtx;
std::shared_ptr<QApplicationManager> qm=nullptr;
}
std::shared_ptr<QApplicationManager> qapplication_manager(){
    std::unique_lock<std::mutex> ul(qapp_mtx);
    if(qm==nullptr)
        qm=std::make_shared<QApplicationManager>();
    return qm;
}

QCoreApplication* qapplication(){
    return qapplication_manager()->app;
}
void wait_for_qapp_to_finish() {
    qapplication_manager()->wait_for_finished();
}

void run_in_gui_thread(RunEvent* re){
    // thread safe!
    qapplication()->postEvent(qapplication(),re);
    // will return before event is executed
}

namespace  {
struct Blocker:public RunEvent{
    RunEvent* re;
    std::shared_ptr<std::atomic<bool>> done;
    Blocker(RunEvent* re, std::shared_ptr<std::atomic<bool>> done):re(re),done(done){}
    void run(){
        delete re;
        (*done)=true;
    }
};
}
void blocking_run_in_gui_thread(RunEvent* re){
    std::shared_ptr<std::atomic<bool>> done=std::make_shared<std::atomic<bool>>(false);
    run_in_gui_thread(new Blocker(re,done));
    // if latency is an issue, consider replacing with mutexes, cvs, and wait....
    // but it probably isnt, you dont do this alot...
    while(!done) std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

