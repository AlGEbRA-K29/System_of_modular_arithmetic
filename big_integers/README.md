# BigIntegers
```CPP

constexpr char modulo1[] = "1111";
constexpr char modulo2[] = "1234";

int main() {
    //bigint is a class for storing and operating on arbitrarily big integers

    //You can use literals to initialize it
    bigint an_arbitrary_length_integer = 1234000000000000000000000000000000000_BI;

    //Streams
    bigint input;
    std::cin >> input;

    //Or certain other constructors
    bigint from_uint = 234, from_string("-12345600000000000000000");

    //Most operations are available
    auto weird_result = 5_BI * input + an_arbitrary_length_integer;
    //There are also some functions that help with modular arithmetics
    bigint modular_sum = modular_add(15_BI, 14_BI, 13_BI);
    bigint modular_prod = modular_product(15_BI, 14_BI, 13_BI);
    bigint modular_diff = modular_subtract(15_BI, 14_BI, 13_BI);

    //Convenience class that allows us to use overridden operations instead of lengthy functions is available
    mod<modulo1> operations_with_modulo_1111 = 1234_BI;
    mod<modulo2> operations_with_modulo_1234 = 42;
    mod<modulo1> other = 1111_BI;

    //If you don't know your modulo compile-time, you will have to stick to crude functions though.

    return 0;
}

```
