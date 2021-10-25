#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>


class ThreadPool {
public:
	 ThreadPool(size_t);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:

    std::vector< std::thread > workers;

    std::queue< std::function<void()> > tasks;


    std::mutex mutex;
    std::condition_variable cond;
    bool stop_flag;

};

inline ThreadPool::ThreadPool(size_t expertNo)
    :   stop_flag(false)
{
    for(size_t i = 0;i<expertNo;++i)
        workers.emplace_back(
            [this]
            {
                pthread_setname_np(pthread_self(), "abc");
                for(;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->mutex);
                        this->cond.wait(lock,
                            [this]{ return this->stop_flag || !this->tasks.empty(); });
                        if(this->stop_flag && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            }
        );
}


template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(mutex);


        if(stop_flag){
            throw std::runtime_error("enqueue on Expert eng ThreadPool which is stop");
        }

        tasks.emplace([task](){ (*task)(); });
    }
    cond.notify_one();
    return res;
}

inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        stop_flag = true;
    }
    cond.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}

#endif
