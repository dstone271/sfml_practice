#include <SFML/System.hpp>
#include <iostream>

sf::Mutex mutex;

void func()
{
  mutex.lock();

  for (int i=0; i<10; i++) {
    std::cout << "function thread" << std::endl;
  }

  mutex.unlock();
}

void arg_func(int loops)
{
  sf::Lock lock(mutex); // mutex lock

  for (int i=0; i<loops; i++) {
    std::cout << "arg function thread" << std::endl;
  }
} // mutex unlock

class ThreadClass
{
 public:
  ThreadClass()
    : m_thread(&ThreadClass::class_func, this)
  {}

  void start()
  {
    m_thread.launch();
  }

  void wait_to_finish()
  {
    m_thread.wait();
  }

 private:
  void class_func()
  {
    sf::Lock lock(mutex);
    for (int i=0; i<10; i++) {
      std::cout << "class thread" << std::endl;
      sf::sleep(sf::milliseconds(250));
    }
  }

  sf::Thread m_thread;
};

int main()
{
  sf::Thread func_thread(&func);
  func_thread.launch();

  sf::Thread arg_thread(&arg_func, 10);
  arg_thread.launch();

  ThreadClass class_object;
  class_object.start();

  mutex.lock();
  //class_object.wait_to_finish(); // deadlock
  for (int i=0; i<10; i++) {
    std::cout << "main thread: " << i << std::endl;
  }
  mutex.unlock();


  return 0;
}
