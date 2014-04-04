

#include <vector>

class test {
  
  public:
  test()
	:v1(10), v2(10)
  {}


  class iterator {
	public:
	iterator(std::vector<int>& _v1,
			 std::vector<int>& _v2) 
	  :v1(_v1), v2(_v2){}

	std::tuple<int&, int&> operator*(){
	  return std::tuple<int&, int&>{v1[5], v2[5]};
	}
	std::vector<int>& v1;
	std::vector<int>& v2;
  };

  std::vector<int> v1, v2;
};



int main(){
  
  test t;
  
  std::swap(*(test::iterator(t.v1, t.v2)),
			*(test::iterator(t.v1, t.v2)));

}
