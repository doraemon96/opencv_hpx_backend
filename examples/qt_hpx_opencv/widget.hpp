//  Copyright (c) 2012-2014 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <QDialog>

#ifndef Q_MOC_RUN
#include <hpx/include/threads.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <cstddef>
#include <functional>
#include "renderwidget.hpp"
#endif

class QWidget;
class QListWidget;
class QPushButton;

class widget
    : public QDialog
{
    Q_OBJECT

    public:
        widget(std::function<void(widget *)> callback,
            QWidget *parent = nullptr);

        void threadsafe_add_label(std::size_t i, double t);

        void threadsafe_run_finished();
        RenderWidget* renderer;


public slots:
        void set_threads(int no);

        void run_clicked(bool);

        void add_label(const QString& text);

    private:
        std::size_t no_threads;
        hpx::lcos::local::spinlock mutex;
        QListWidget *list;
        QPushButton * run_button;
        std::function<void(widget *)> callback_;
};
