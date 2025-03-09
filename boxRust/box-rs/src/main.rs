use ncurses::{
    initscr, start_color, init_pair, cbreak, noecho, keypad, getch, endwin, refresh,
    attron, attroff, mvaddch, mvhline, mvvline, printw, mvprintw, stdscr,
    WINDOW, LINES, COLS, COLOR_PAIR, COLOR_CYAN, COLOR_BLACK, KEY_F, KEY_LEFT,
    KEY_RIGHT, KEY_UP, KEY_DOWN,
};

// Define the WIN_BORDER struct
#[repr(C)]
struct WinBorder {
    ls: i32, // Left side
    rs: i32, // Right side
    ts: i32, // Top side
    bs: i32, // Bottom side
    tl: i32, // Top-left corner
    tr: i32, // Top-right corner
    bl: i32, // Bottom-left corner
    br: i32, // Bottom-right corner
}

// Define the WIN struct
#[repr(C)]
struct Win {
    startx: i32,
    starty: i32,
    height: i32,
    width: i32,
    border: WinBorder,
}

fn init_win_params(p_win: &mut Win) {
    p_win.height = 3;
    p_win.width = 10;
    p_win.starty = (LINES() - p_win.height) / 2;
    p_win.startx = (COLS() - p_win.width) / 2;

    p_win.border.ls = '|' as i32;
    p_win.border.rs = '|' as i32;
    p_win.border.ts = '-' as i32;
    p_win.border.bs = '-' as i32;
    p_win.border.tl = '+' as i32;
    p_win.border.tr = '+' as i32;
    p_win.border.bl = '+' as i32;
    p_win.border.br = '+' as i32;
}

fn print_win_params(p_win: &Win) {
    #[cfg(debug_assertions)]
    {
        mvprintw(25, 0, &format!(
            "{} {} {} {}",
            p_win.startx, p_win.starty, p_win.width, p_win.height
        ));
        refresh();
    }
}

fn create_box(p_win: &Win, flag: bool) {
    let x = p_win.startx;
    let y = p_win.starty;
    let w = p_win.width;
    let h = p_win.height;

    if flag {
        mvaddch(y, x, p_win.border.tl.try_into().unwrap());
        mvaddch(y, x + w, p_win.border.tr.try_into().unwrap());
        mvaddch(y + h, x, p_win.border.bl.try_into().unwrap());
        mvaddch(y + h, x + w, p_win.border.br.try_into().unwrap());
        mvhline(y, x + 1, p_win.border.ts.try_into().unwrap(), w - 1);
        mvhline(y + h, x + 1, p_win.border.bs.try_into().unwrap(), w - 1);
        mvvline(y + 1, x, p_win.border.ls.try_into().unwrap(), h - 1);
        mvvline(y + 1, x + w, p_win.border.rs.try_into().unwrap(), h - 1);
    } else {
        for j in y..=y + h {
            for i in x..=x + w {
                mvaddch(j, i, ' '.try_into().unwrap());
            }
        }
    }
    refresh();
}

fn main() {
    let mut win = Win {
        startx: 0,
        starty: 0,
        height: 0,
        width: 0,
        border: WinBorder {
            ls: 0, rs: 0, ts: 0, bs: 0,
            tl: 0, tr: 0, bl: 0, br: 0,
        },
    };

    initscr();           // Start ncurses mode
    start_color();       // Enable color
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    cbreak();            // Disable line buffering
    noecho();            // Don’t echo input
    keypad(stdscr(), true); // Enable special keys like F5

    init_win_params(&mut win);
    print_win_params(&win);

    attron(COLOR_PAIR(1));
    printw("Press F5 to exit");
    refresh();
    attroff(COLOR_PAIR(1));

    create_box(&win, true);

    loop {
        let ch = getch();
        if ch == KEY_F(5) {break; }
        match ch {
            KEY_LEFT => {
                create_box(&win, false);
                win.startx -= 1;
                create_box(&win, true);
            }
            KEY_RIGHT => {
                create_box(&win, false);
                win.startx += 1;
                create_box(&win, true);
            }
            KEY_UP => {
                create_box(&win, false);
                win.starty -= 1;
                create_box(&win, true);
            }
            KEY_DOWN => {
                create_box(&win, false);
                win.starty += 1;
                create_box(&win, true);
            }
            _ => {}
        }
    }

    endwin(); // End ncurses mode
}
