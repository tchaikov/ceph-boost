
#include <iostream>
#include <vector>

#include <boost/align.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

int main(int, char*[]) {
  int alignment = 64;
  int size = 16;

  void* storage = boost::alignment::aligned_alloc(alignment, size);
  boost::alignment::aligned_free(storage);

  std::vector<int128_t, boost::alignment::aligned_allocator<int128_t> > vector1;
  std::vector<double, boost::alignment::aligned_allocator<double, 64> > vector2;

  double* pointer = reinterpret_cast< double* >(boost::alignment::aligned_alloc(alignment, sizeof(double)));
  assert(boost::alignment::is_aligned(pointer, alignment));
  std::unique_ptr<double, boost::alignment::aligned_delete> unique(pointer);

  std::cout << "Alignement of int128_t is: " << boost::alignment::alignment_of<int128_t>::value << std::endl;
  std::cout << "Alignement of int128_t is: " << boost::alignment::alignment_of_v<int128_t> << std::endl;

  return 0;
}
