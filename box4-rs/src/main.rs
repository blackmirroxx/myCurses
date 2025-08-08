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

    fn get_arguments(&self, i: usize) -> String {
        if i>=self.psize {return String::new(); }
        self.arguments[i].clone() // no colon for the return    
    }
}

struct Field{
    width: i32,
    height: i32,
}

impl Field {
   fn new(width: i32, height: i32) -> Self {
       Field { width, height }
   } 

   fn set_width(&mut self, width: i32) -> i32 {
       self.width = width;
       self.width  
   }  
   
   fn get_width(&self) -> i32 {self.width }

   fn set_height(&mut self, height: i32) -> i32 {
       self.height = height;
       self.height
   }  

   fn get_height(&self) -> i32 {self.height }      
}

struct Coordinate {
    start_y: i32,
    start_x: i32,
}

fn main() {
    println!("Hello, world!");
}
