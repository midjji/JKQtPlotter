#include <map>
#include <iostream>
#include "jkqtplotter/jkqtplotter.h"
#include "jkqtplotter/graphs/jkqtpscatter.h"
using std::cout;
using std::endl;
std::map<std::string, std::shared_ptr<JKQTPlotter>> plots;

void plot(std::vector<double> xs,
          std::vector<double> ys,
          std::string title)
{
    // 1. create a plotter window and get a pointer to the internal datastore (for convenience)
    if(!plots[title]){
        plots[title]=std::make_shared<JKQTPlotter>();
    }

    std::shared_ptr<JKQTPlotter> plot=plots[title];

    JKQTPDatastore* ds=plot->getDatastore();

    // 2. now we create data for a simple plot (a sine curve)
    QVector<double> X, Y;
    bool nansinplot=false;
    for (uint i=0;i<std::min(xs.size(),ys.size());++i)
    {

        X<<xs[i];
        Y<<ys[i];
        if(std::isnan(xs[i]+ys[i]))
            nansinplot=true;

    }
    if(nansinplot)
        cout<<"nans in plot"<<endl;

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
    plot->zoomToFit();

    // show plotter and make it a decent size
    plot->show();
    plot->resize(600,400);
}

