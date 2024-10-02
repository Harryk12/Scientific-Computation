// Harry S. Kang, hsk697, hkangt

#include <iostream>
#include <ranges>
#include <vector>
#include <functional>
#include <algorithm>

using std::ranges::for_each;
using std::ranges::views::iota;
using std::ranges::views::filter;
using std::function;
using std::cout;
using std::endl;
 
int main() {
  // lambda expression to compute the sum of factors of an input number
  auto sum = [] (int numbercandidate) -> int {
    int runningsum = 0;
    auto nums = iota(1, numbercandidate);   //lists numbers under the input number value to evaluate whether it's a factor
    for_each(nums, [numbercandidate, &runningsum] (int num) {
      if (numbercandidate % num == 0)
	runningsum += num;             //adds numbers that are factors to the running sum count
    });
    return runningsum;
  };



  //following is actually calling numbers up to 9000 (larger than 4th perfect number)
  auto numbers = iota(1, 9000);
  for_each(numbers | filter([sum] (int number) -> bool {    //filters such that sum of factors equal number- does so by calling sum lambda exp.
    return sum(number) == number;
  }), [] (int number) {    //boolean above choses which of the numbers to display (number here is sent into the lambda exp. above and becomes numbercandidate
    cout << number << " is a perfect number." << endl;
  });
 
  return 0;
}
