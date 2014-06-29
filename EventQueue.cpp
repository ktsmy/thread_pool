#include "EventQueue.hpp"

/**
 * @brief コンストラクタ
 * @param[in] max_size キューの最大サイズ
 */
EventQueue::EventQueue(int max_size) : m_max_size(max_size)
{
}

/**
 * @brief デストラクタ
 */
EventQueue::~EventQueue() {}


/**
 * @brief キューにリクエストを追加
 * @param[in] request 追加するリクエスト
 */
void EventQueue::addRequest(Request* request) {
  // ロックを取得
  pthread_mutex_lock(&m_lock);

  // サイズが一杯のときは一杯でなくなるまで待つ
  // FIXME: 永遠に待ち続けないよう、シャットダウンを用意
  while (m_size == m_max_size) {
    pthread_cond_wait(&m_not_full, m_lock);
  }

  // リクエストを末尾に追加
  if (m_size == 0) {
    m_head = m_tail = request;
    // 空でなくなったことを通知
    pthread_cond_signal(&m_not_empty);
  } else {
    m_tail->setNextRequest(request);
    m_tail = request;
  }
  ++m_size;

  // ロックを解放
  pthread_mutex_unlock(&m_lock);
}


/**
 * @brief キューからリクエストを取り出す
 * @retval 取り出したリクエスト
 */
Request* EventQueue::getRequest() {
  // ロックを取得
  pthread_mutex_lock(&m_lock);

  // キューが空の場合は空でなくなるまで待つ
  // FIXME: 永遠に待ち続けないよう、シャットダウンを用意
  while (m_size == 0) {
    pthread_cond_wait(&m_not_empty, m_lock);
  }

  // キューの先頭からリクエストを取り出す
  Request* request = m_head;
  --m_size;
  if (m_size == 0) {
    m_head = m_tail = NULL;
    // 空になったことを通知
    pthread_cond_signal(&m_empty);
  } else {
    m_head = m_head->getNextRequest();
  }

  // 一杯だった場合は、一杯でなくなったことを通知
  if (m_size == m_max_size - 1) {
    pthread_cond_signal(&m_not_full);
  }
  
  // ロックを解放
  pthread_mutex_unlock(&m_lock);

  return request;
}
