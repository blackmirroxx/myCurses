use ncurses::{
    initscr, has_colors, start_color, init_pair, attron, attroff, getch, endwin,
    WINDOW, stdscr, mvwprintw, refresh, getyx, LINES, COLS, COLOR_PAIR,
    COLOR_RED, COLOR_BLACK,
};
use std::process::exit;

fn print_in_middle(win: WINDOW, starty: i32, startx: i32, width: i32, string: &str) {
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let length = string.len() as i32;
    let temp: i32;

    let win = unsafe { if win.is_null() { stdscr() } else { win } };
    unsafe { getyx(win, &mut y, &mut x) };
    if startx != 0 { x = startx; }
    if starty != 0 { y = starty; }
    let width = if width == 0 { COLS() } else { width };

    temp = (width - length) / 2;
    x = startx + temp;

    mvwprintw(win, y, x, string); // pointer are behind abstraction 
    refresh();
}

fn main() {
    initscr(); // Start ncurses mode
    if !has_colors() {
        endwin();
        println!("Your terminal does not support color");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    print_in_middle(stdscr(), LINES() / 2, 0, 0, "Viola !!! In color ...");
    attroff(COLOR_PAIR(1));

    getch();
    endwin();
}
