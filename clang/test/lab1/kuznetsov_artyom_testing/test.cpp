

class Test {};

namespace {
int factorial(int value) {
  return value <= 1 ? 1 : value * factorial(value - 1);
}

int diff(int valueOne, int valueTwo){
    return valueOne - valueTwo;
}

template<typename T1, typename T2>
auto max(T1 valueOne, T2 valueTwo) {
    return valueOne > valueTwo ? valueOne : valueTwo;
}

} // namespace