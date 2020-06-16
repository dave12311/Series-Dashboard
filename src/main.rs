use std::io;
use tui::Terminal;
use tui::backend::{CrosstermBackend, Backend};
use std::io::Stdout;
use std::error::Error;
use tui::widgets::{Block, Borders};

struct SeriesDashboard {
    terminal: Terminal<CrosstermBackend<Stdout>>
}

impl SeriesDashboard {
    fn new() -> Result<SeriesDashboard, io::Error> {
        let stdout = io::stdout();
        let backend = CrosstermBackend::new(stdout);
        let terminal = Terminal::new(backend)?;
        Ok(SeriesDashboard { terminal })
    }

    fn start(&mut self) {
        self.terminal.draw(|mut f| {
            let size = f.size();
            let block = Block::default()
                .title("Test Title")
                .borders(Borders::ALL);
            f.render_widget(block, size);
        });
    }
}

fn main() {
    let mut series_dashboard = SeriesDashboard::new().unwrap();
    series_dashboard.start();
    loop {

    }
}
