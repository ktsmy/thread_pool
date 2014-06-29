#include "ThreadPool.hpp"
#include "EventQueue.hpp"

/**
 * @brief コンストラクタ
 * @param[in] num_threads スレッド数
 * @param[in] queue スレッドが処理するイベントキュー
 */
ThreadPool::ThreadPool(int num_threads, EventQueue* queue) : m_num_threads(num_threads), m_event_queue(queue), m_destroy(false)
{
  m_threads = (pthread_t*)malloc(sizeof(pthread_t) * num_threads);
  for (int ii = 0; ii < num_threads) {
    pthread_create(&(m_threads[ii]), NULL, processEventQueue, (void*)queue);
  }
}

/**
 * @brief デストラクタ
 */
ThreadPool::~ThreadPool() {
  m_destroy = true;
  for (int ii = 0; ii < m_num_threads) {
    pthread_join(m_threads[ii], NULL);
  }
  free(m_threads);
}

void* ThreadPool::processEventQueue(void* queue) {
  while (1) {
    // イベントキューからリクエストを取得して処理する
    if (queue->getRequest()) {
      // ここに処理を記述
    }

    // 終了フラグをチェック
    if (m_destroy) {
      pthread_exit(NULL);
    }
  }
}
