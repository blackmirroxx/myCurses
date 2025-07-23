use ncurses::*;
use std::ffi::CString;
use std::os::raw::c_char;

struct NCurseSession;

impl NCurseSession {
    fn start_session() -> Result<(), ()> {
        initscr();
        cbreak(); // Line buffering disabled, pass everything to the program
        noecho(); // Don't echo input
        Ok(())
    }

    fn end_session() -> Result<(), ()> {
        endwin();
        Ok(())
    }

    fn refresh_session() -> Result<(), ()> {
        refresh();
        Ok(())
    }

    fn get_user_input() -> Result<i32, ()> {
        let input = getch();
        Ok(input)
    }
}

struct MyBox {
    height: i32,
    width: i32,
    start_y: i32,
    start_x: i32,
    win: WINDOW,
}

impl MyBox {
    fn new() -> Self {
        let height = 10;
        let width = 20;
        let start_y = 3;
        let start_x = 10;
        let win = newwin(height, width, start_y, start_x);
        refresh();

        let left = ACS_VLINE();
        let right = ACS_VLINE();
        let top = ACS_HLINE();
        let bottom = ACS_HLINE();
        let tlc = ACS_ULCORNER();
        let trc = ACS_PLUS(); // top right corner -> +
        let blc = ACS_LLCORNER();
        let brc = ACS_LRCORNER();

        wborder(
            win,
            left,
            right,
            top,
            bottom,
            tlc,
            trc,
            blc,
            brc,
        );
        mvwprintw(win, 1, 2, CString::new("This is my box").unwrap().as_c_str());
        wrefresh(win);

        MyBox {
            height,
            width,
            start_y,
            start_x,
            win,
        }
    }

    fn with_text(text: &str) -> Self {
        let height = 20;
        let width = 40;
        let start_y = 3;
        let start_x = 10;
        let win = newwin(height, width, start_y, start_x);
        refresh();
        box_(win, 0, 0);
        mvwprintw(win, 1, 2, CString::new(text).unwrap().as_c_str());
        wrefresh(win);

        MyBox {
            height,
            width,
            start_y,
            start_x,
            win,
        }
    }
}

fn main() {
    let args: Vec<String> = std::env::args().collect();

    let n = NCurseSession;
    n.start_session().unwrap();
    n.refresh_session().unwrap();

    if args.len() < 2 {n.end_session().unwrap(); println!("Run :: ./box your_snail_text"); return; }

    let _b = MyBox::with_text(&args[1]);
    let _s = n.get_user_input().unwrap();
    n.end_session().unwrap();
}
