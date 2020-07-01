use std::io;
use tui::{Terminal, Frame};
use tui::backend::CrosstermBackend;
use std::io::Stdout;
use tui::widgets::{Block, Borders, Paragraph, Text};
use std::borrow::{Cow, Borrow, BorrowMut};
use tui::layout::{Rect, Alignment};
use std::process::exit;
use crossterm::event::{Event, KeyEvent, KeyCode};
use std::error::Error;


pub struct SeriesDashboard {
    terminal: Terminal<CrosstermBackend<Stdout>>
}

pub struct DashboardScreen {
    frame: fn(Frame<CrosstermBackend<Stdout>>)
}

impl SeriesDashboard {
    pub fn new() -> SeriesDashboard {
        let stdout = io::stdout();
        let backend = CrosstermBackend::new(stdout);
        SeriesDashboard {
            terminal: Terminal::new(backend).unwrap(),
        }
    }

    pub fn start(&mut self) {
        let term = &mut self.terminal;
        term.clear();
        term.hide_cursor();
    }
}

enum MenuState {
    Dashboard
}

fn start_dashboard(terminal: &mut Terminal<CrosstermBackend<Stdout>>) {
    // Basic setup
    terminal.clear();

    let mut state = MenuState::Dashboard;

    let draw_dashboard = |mut f: Frame<CrosstermBackend<Stdout>>| {
        let mut size = f.size();
        size.height -= 1;
        let block = Block::default()
            .title("Series Dashboard")
            .borders(Borders::ALL);
        f.render_widget(block, size);

        let options_text = [
            Text::Raw(Cow::from("[N] New     ")),
            Text::Raw(Cow::from("[D] Delete     ")),
            Text::Raw(Cow::from("[Q] Quit"))
        ];
        let options = Paragraph::new(options_text.iter()).alignment(Alignment::Center);
        f.render_widget(options, Rect::new(size.x, size.height, size.width, 1));
    };

    terminal.draw(draw_dashboard);
    terminal.hide_cursor();
}

fn main() {
    crossterm::terminal::enable_raw_mode();
    let mut application = SeriesDashboard::new();
    application.start();
    println!("Hi");
    loop {
        if let Ok(T) = crossterm::event::read() {
            if let Event::Key(K) = T {
                if K.code == crossterm::event::KeyCode::Char('q') {exit(1)}
            }

            println!("{:?}", T);
        }
    }
}
