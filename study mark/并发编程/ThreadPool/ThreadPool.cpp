#include "ThreadPool.h"

void ThreadPool::start()
{
    for (int i = 0; i < thread_num_; i++) {
        pool_.emplace_back([this]() {
            while (!this->stop_.load()) {//�߳�δ�ر�ʱ
                Task task;
                //ѭ�����߼�����ÿ�δӶ�����ȡ�����ȵ������������ȴ����в�Ϊ�գ������յ��˳��źţ�
                // ����ֻҪ������һ������������wait�ͷ��أ����Ҽ��������ߡ�������������wait���᷵�أ��߳̽�����
                std::unique_lock<std::mutex> cv_mt(cv_mt_);//������������
                this->cv_lock_.wait(cv_mt, [this]() {//�ж�������lambda���ʽ���Ƿ�Ϊtrue��Ϊtrue�����ִ������Ĵ��룬����ͽ��߳̿�ס������������
                    return this->stop_.load() || !this->tasks_.empty();                   
                 });
                if (this->tasks_.empty())
                    return;

                task = std::move(this->tasks_.front());
                this->tasks_.pop();
            }
            this->thread_num_--;//�����߳�ȥִ������
            //task();
            this->thread_num_++;//�߳�ִ���������ˣ������߳�+1
         });
    }
}

void ThreadPool::stop()
{
    stop_.store(true);
    cv_lock_.notify_all();//stop���������ǽ�ֹͣ�������Ϊtrue�����ҵ�������������notify_all���������̣߳����ҵȴ������߳��˳����̳߳ز�������ɡ�
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
    std::function<int(void)> functionv = std::bind(functionint, 3);//����һ��int(void) ����
    using Task = std::packaged_task<void()>;
    std::queue<Task> taskque;
    //��Ϊlambda���ʽ������functionv��ֵ�����Կ������ڲ�����functionv��
    //lambda���ʽ����ֵΪvoid����ҲΪvoid�����Կ���ֱ�ӷ���������С�
    taskque.emplace([functionv]() {//����һ��task�����������
        functionv();
        });
}