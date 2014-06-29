#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "EventQueue.hpp"
#include <pthread.h>

public class ThreadPool {
 public:
  /**
   * @brief コンストラクタ
   * @param[in] num_threads スレッド数
   * @param[in] queue スレッドが処理するイベントキュー
   */
  ThreadPool(int num_threads, EventQueue* queue)

  /**
   * @brief デストラクタ
   */
  ~ThreadPool();

 private:
  /**
   * @brief スレッドが行う処理<br>
   *        引数でイベントキューを受け取って処理する
   */
  virtual void* processEventQueue(void* queue);

  /**
   * @brief スレッド
   */
  pthread_t* m_threads;

  /**
   * @brief スレッド数
   */
  int m_num_threads;

  /**
   * @brief 終了フラグ<br>
   *        各スレッドはこの値が真なら終了する
   */
  bool m_destroy;
}

#endif // THREADPOOL_HPP
