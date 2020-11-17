#pragma once
#include <QEvent>
#include <QObject>
#include <QApplication>



struct RunEvent;
/**
 * @brief run_in_gui_thread
 * @param RunEvent* re
 *
 * run_in_gui_thread(RunEventImpl([](Args... args){
 * do_something(args...); new QMainWindow(), window.show() or something... },
 *   args...);
 * \note
 * - Arguments must exist latter and be accessible in a thread safe way from the gui thread.
 *  The simplest way is to copy them.
 * - this event gets copied about, unique_ptr wont work.
 * - raw pointers and references are a bad idea.
 * - shared ptrs work wonders.
 * - thread safe, call from anywhere, no need to setup a QApplication, but it works if you have one.
 *
 * run must take a short time only, no heavy work here. But setting up a few windows is fine.
 *
 */
void run_in_gui_thread(RunEvent* re);
/**
 * @brief blocking_run_in_gui_thread
 * @param re
 *  returns only after the runevent has completed!
 */
void blocking_run_in_gui_thread(RunEvent* re);

/**
 * @brief The RunEvent struct
 *
 * run_in_gui_thread(RunEventImpl([](Args...){do_something(args...)},Args... args)
 *
 *
 * // Note QCoreApplication::instance() works if it has been inited, which
 *
 * the run event performs run on destruction, which happens in the QCoreApplication thread,
 * meaning you can create the RunEve´nt in any thread, where run creates or performs gui operations,
 * but the run function occurs in the right thread so it works in a thread safe manner.
 */
struct RunEvent: public QEvent{
    RunEvent():QEvent(QEvent::Type(48301)){} // the number is not important !=0
    virtual void run()=0;
};
template<class Lambda, class... Args>
struct RunEventImpl: public RunEvent
{
    //  // note do not capture context, all args must exist when called later,
    /**
       * @brief RunEvent
       * @param lambda [](Args&...) {}
       * @param args
       *
       * \note
       * - to minimize error risk, do not capture context and deep copy all arguments.
       * - this class will get copied about a fair bit, across threads,
       * so tiny pods or shared ptrs are the way to go.
       * Dont use unique, raw works, but consider that its a bad idea.
       * - yes I know you can just overload instead...
       *
       */
    RunEventImpl(Lambda lambda, Args... args):RunEvent(),
        lambda(lambda), args(std::make_tuple(args...)){}
    ~RunEventImpl(){run();}

    void run() override{
        run_impl(std::make_index_sequence<sizeof...(Args)>());
    }
private:
    Lambda lambda;
    std::tuple<Args...> args;
    template<std::size_t... I>
    bool run_impl(std::index_sequence<I...>){
        lambda(std::get<I>(args)...);
    }
};

// this gets or creates and the QApplication in a new thread and runs execs()
// in that thread, then waits untill it has been fully created.
// there is no need to call this function in general...
// it is a QApplication if QCoreApplication was not created first...
QCoreApplication* qapplication();
void wait_for_qapp_to_finish();
