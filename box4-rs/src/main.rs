use ncurses::*; 
use std::env;

#[derive(Debug)]
enum Colors {
    White, 
    Yellow, 
    Red, 
    Blue, 
    Green, 
    Black
}

enum ArgumentsForBox {
   BoxStandard = 1, 
   BoxWithText = 2, 
   BoxWithFieldCoordinatesAndText = 6,
}

struct Parameter {
    psize : usize,
    arguments : Vec<String>,
}

fn main() {
    println!("Hello, world!");
}
