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

impl Parameter {
    fn new(psize: usize) -> Self {
        Parameter { psize, arguments: Vec::new() }
    }

    fn set_arguments(&mut self, args: Vec<String>){
        self.arguments = args;
    }
    
}

fn main() {
    println!("Hello, world!");
}
