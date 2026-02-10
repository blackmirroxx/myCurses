use std::io;

// trouve le plus petit nombre premier strictement supérieur à `b`.
fn least_prime_greater_than(b: i32) -> Option<i32> {
    let primes = vec![2, 3, 5, 7, 11, 13, 19, 23, 29];
    primes.into_iter().find(|&v| v > b)
}

fn main() {
    println!("Hello, world!");
}
