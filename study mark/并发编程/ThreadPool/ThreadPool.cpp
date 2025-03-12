#include "ThreadPool.h"

void ThreadPool::start()
{
    for (int i = 0; i < thread_num_; i++) {
        pool_.emplace_back([this]() {
            while (!this->stop_.load()) {//线程未关闭时
                Task task;
                //循环的逻辑就是每次从队列中取任务，先调用条件变量等待队列不为空，或者收到退出信号，
                // 二者只要满足其一，条件变量的wait就返回，并且继续向下走。否则条件变量wait不会返回，线程将挂起。
                std::unique_lock<std::mutex> cv_mt(cv_mt_);//给互斥量上锁
                this->cv_lock_.wait(cv_mt, [this]() {//判断条件（lambda表达式）是否为true，为true则继续执行下面的代码，否则就将线程卡住，解锁互斥量
                    return this->stop_.load() || !this->tasks_.empty();                   
                 });
                if (this->tasks_.empty())
                    return;

                task = std::move(this->tasks_.front());
                this->tasks_.pop();
            }
            this->thread_num_--;//空闲线程去执行任务
            //task();
            this->thread_num_++;//线程执行完任务了，空闲线程+1
         });
    }
}

void ThreadPool::stop()
{
    stop_.store(true);
    cv_lock_.notify_all();//stop函数中我们将停止标记设置为true，并且调用条件变量的notify_all唤醒所有线程，并且等待所有线程退出后线程池才析构完成。
    for (auto& td : pool_) {
        if (td.joinable()) {
            std::cout << "join thread " << td.get_id() << std::endl;
            td.join();
        }
    }
}

ThreadPool::ThreadPool(unsigned int num):stop_(false)
{

    if (num <= 1)
        thread_num_ = 2;
    else
        thread_num_ = num;

    start();
}
int functionint(int param) {
    std::cout << "param is " << param << std::endl;
    return 0;
}

void pushtasktoque() {
    std::function<int(void)> functionv = std::bind(functionint, 3);//创建一个int(void) 函数
    using Task = std::packaged_task<void()>;
    std::queue<Task> taskque;
    //因为lambda表达式捕获了functionv的值，所以可以在内部调用functionv。
    //lambda表达式返回值为void参数也为void，所以可以直接放入任务队列。
    taskque.emplace([functionv]() {//构造一个task放入任务队列
        functionv();
        });
}