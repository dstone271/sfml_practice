#include <SFML/System.hpp>

class MyInputStream : public sf::InputStream {
 public:
  MyInputStream() {
    my_data = new char[10];
    my_position = 0;
    num_chars = 10;
  }

  sf::Int64 read(void* data, sf::Int64 size) {
    if (my_position >= num_chars) {
      return -1;
    }
    data = my_data + my_position;
    if (num_chars - my_position >= size) {
      return size;
    } else {
      return num_chars - my_position;
    }
  }

  sf::Int64 seek(sf::Int64 position) {
    my_position = position;
    return my_position;
  }

  sf::Int64 tell() {
    return my_position;
  }

  sf::Int64 getSize() {
    return num_chars;
  }


 private:
  char* my_data;
  int64_t my_position;
  int64_t num_chars;
};


int main()
{
  MyInputStream stream_obj;

  return 0;
}
