#ifndef EVENTQUEUE_HPP
#define EVENTQUEUE_HPP

#include "Request.hpp"
#include <pthread.h>

public class EventQueue {
 public:
  /**
   * @brief コンストラクタ
   * @param[in] max_size キューの最大サイズ
   */
  EventQueue(int max_size);

  /**
   * @brief デストラクタ
   */
  ~EventQueue();

  /**
   * @brief キューにリクエストを追加
   * @param[in] request 追加するリクエスト
   */
  void addRequest(Request* request);

  /**
   * @brief キューからリクエストを取り出す
   * @retval 取り出したリクエスト
   */
  Request* getRequest();

 private:
  /**
   * @brief 現在のキューのサイズ
   */
  int m_size;

  /**
   * @brief キューの最大サイズ
   */
  int m_max_size;

  /**
   * @brief キューの先頭
   */
  Request* m_head;

  /**
   * @brief キューの末尾
   */
  Request* m_tail;

  /**
   * @brief スレッド同期用
   */
  pthread_mutex_t m_lock;
  pthread_cond_t  m_not_empty;
  pthread_cond_t  m_not_full;
  pthread_cond_t  m_empty;
}

#endif
