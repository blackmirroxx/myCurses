use ncurses::*;
use std::process;

struct NCursesSession {
    s: String,
}

impl NCursesSession {
    // Constructor equivalent (new)
    fn new() -> Self {
        NCursesSession {
            s: String::new(),
        }
    }

    fn start_session(&self) -> i32 {
        initscr();
        cbreak(); // Allow Ctrl+C, like the C++ cbreak()
        noecho(); // Don't echo user input
        0 // EXIT_SUCCESS
    }

    fn end_session(&self) -> i32 {
        endwin();
        0 // EXIT_SUCCESS
    }

    fn refresh_session(&self) -> i32 {
        refresh();
        0 // EXIT_SUCCESS
    }

    fn get_user_input(&mut self) -> &str {
        self.s.clear();
        let ch = getch();
        if ch != ERR {
            self.s.push(ch as u8 as char);
        }
        &self.s
    }
}

struct MyBox {
    _height: i32,
    _width: i32,
    _start_x: i32,
    _start_y: i32,
    win: WINDOW,
}

impl MyBox {
    // Default constructor equivalent
    fn new() -> Self {
        let height = 10;
        let width = 20;
        let start_y = 3;
        let start_x = 10;
        let win = newwin(height, width, start_y, start_x);
        refresh();
        box_(win, 0, 0);
        mvwprintw(win, 1, 2, "This is my box");
        wrefresh(win);
        MyBox {
            _height: height,
            _width: width,
            _start_x: start_x,
            _start_y: start_y,
            win,
        }
    }

    // Constructor with string
    fn with_string(s: &str) -> Self {
        let height = 20;
        let width = 40;
        let start_y = 3;
        let start_x = 10;
        let win = newwin(height, width, start_y, start_x);
        refresh();
        box_(win, 0, 0);
        mvwprintw(win, 1, 2, s);
        wrefresh(win);
        MyBox {
            _height: height,
            _width: width,
            _start_x: start_x,
            _start_y: start_y,
            win,
        }
    }

    // Constructor with all parameters
    fn with_params(height: i32, width: i32, start_y: i32, start_x: i32, s: &str) -> Self {
        let win = newwin(height, width, start_y, start_x);
        refresh();
        box_(win, 0, 0);
        mvwprintw(win, 1, 2, s);
        wrefresh(win);
        MyBox {
            _height: height,
            _width: width,
            _start_x: start_x,
            _start_y: start_y,
            win,
        }
    }
}

impl Drop for MyBox {
    fn drop(&mut self) {
        delwin(self.win);
    }
}

fn main() {
    // Create session object
    let mut session = NCursesSession::new();

    // Start ncurses
    if session.start_session() != 0 {
        eprintln!("Failed to start ncurses session");
        process::exit(1);
    }

    // Refresh
    if session.refresh_session() != 0 {
        eprintln!("Failed to refresh session");
        session.end_session();
        process::exit(1);
    }

    // Create a box (using default constructor)
    let _box = MyBox::new();
    // Alternatively, for string or params (commented out as in C++):
    // let _box = MyBox::with_string(&std::env::args().nth(1).unwrap_or("Default".to_string()));
    // let _box = MyBox::with_params(
    //     std::env::args().nth(1).unwrap_or("10").parse().unwrap_or(10),
    //     std::env::args().nth(2).unwrap_or("20").parse().unwrap_or(20),
    //     std::env::args().nth(3).unwrap_or("3").parse().unwrap_or(3),
    //     std::env::args().nth(4).unwrap_or("10").parse().unwrap_or(10),
    //     &std::env выполнены: std::env::args().nth(5).unwrap_or("Default").to_string()
    // );

    // Get user input
    let _input = session.get_user_input();

    // End ncurses
    session.end_session();
}
