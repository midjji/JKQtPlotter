#include <map>
#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <QApplication>
#include <QMainWindow>
#include <qt_init.h>

#include <mlib/utils/mlog/log.h>
#include "jkqtplotter/jkqtplotter.h"
#include "jkqtplotter/graphs/jkqtpscatter.h"
namespace cvl {


namespace  {
class Plotter{
public:

    void plot(const std::vector<double>& xs,
              const std::vector<double>& ys,
              std::string title){
        call_plot(xs,ys,title);
    }
    void plot(const std::vector<double>& ts, const std::map<std::string, std::vector<double>>& errs){
        for(auto& [name,err]:errs) call_plot(ts,err,name);
    }
    static std::shared_ptr<Plotter> create() {
        auto plotter= std::shared_ptr<Plotter>(new Plotter);
        plotter->self=plotter;
        return plotter;
    }

private:
    Plotter() {}

    std::weak_ptr<Plotter> self;

    void call_plot(std::vector<double> xs,
                   std::vector<double> ys,
                   std::string title){
        // Here I know the plotter exists for as long as the

        auto rei=new RunEventImpl([](
                                  std::shared_ptr<Plotter> plotter,
                                  std::vector<double>& xs,
                                  std::vector<double>& ys,
                                  std::string title){plotter->plot_internal(xs,ys,title);return true;},
                // note these are copies!
                self.lock(),xs,ys,title);
        //auto rei=new RunEventImpl([&](){plot_internal(xs,ys,title);}); // xs,ys will be lost, before processing...
        // postEvent is thread safe. Takes ownership of the event pointer, (deletes on posted? do they mean processed?).
        run_in_gui_thread(rei);
    }


    std::map<std::string, std::shared_ptr<JKQTPlotter>> plots;
    std::mutex plot_internal_mtx; // protects the map
    void plot_internal(const std::vector<double>& xs,
                       const std::vector<double>& ys,
                       std::string title){
        mlog()<<"here"<<endl;
        // Note must be run in the qapp thread, so call via the
        //first_plot=true;
        std::unique_lock<std::mutex> ul(plot_internal_mtx);


        // 1. create a plotter window and get a pointer to the internal datastore (for convenience)
        if(!plots[title]){
            plots[title]=std::make_shared<JKQTPlotter>();
        }

        std::shared_ptr<JKQTPlotter> plot=plots[title];

        JKQTPDatastore* ds=plot->getDatastore();

        // 2. now we create data for a simple plot (a sine curve)
        QVector<double> X, Y;
        bool nansinplot=false;
        for (uint i=0;i<std::min(xs.size(),ys.size());++i) {
            X<<xs[i];
            Y<<ys[i];
            if(std::isnan(xs[i]+ys[i]))
                nansinplot=true;
        }
        if(nansinplot)
            std::cout<<"nans in plot"<<std::endl;

        // 3. make data available to JKQTPlotter by adding it to the internal datastore.
        //    Note: In this step the data is copied (of not specified otherwise), so you can
        //          reuse X and Y afterwards!
        //    the variables columnX and columnY will contain the internal column ID of the newly
        //    created columns with names "x" and "y" and the (copied) data from X and Y.
        size_t columnX=ds->addCopiedColumn(X, "x");
        size_t columnY=ds->addCopiedColumn(Y, "y");

        // 4. create a graph in the plot, which plots the dataset X/Y:
        JKQTPXYLineGraph* graph1=new JKQTPXYLineGraph(plot.get());
        graph1->setXColumn(columnX);
        graph1->setYColumn(columnY);
        graph1->setTitle(QObject::tr(title.c_str()));

        // 5. add the graph to the plot, so it is actually displayed
        plot->addGraph(graph1);

        // 6. autoscale the plot so the graph is contained
        plot->zoomToFit()
                ;

        // show plotter and make it a decent size
        plot->show();
        plot->resize(600,400);
    }
};

std::mutex plotter_mtx;
std::shared_ptr<Plotter> plotter_=nullptr;
}
std::shared_ptr<Plotter> plotter(){
    std::unique_lock<std::mutex> ul(plotter_mtx);
    if(plotter_==nullptr)
        plotter_=Plotter::create();
    return plotter_;
}



void plot(const std::vector<double>& xs,
          const std::vector<double>& ys,
          std::string title){
    plotter()->plot(xs,ys,title);
}
void plot(const std::vector<double>& xs, const std::map<std::string, std::vector<double>>& yss)
{
    plotter()->plot(xs,yss);
}
void initialize_plotter(){
    plotter();
}
}





