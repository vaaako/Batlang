#[derive(Clone)]
pub struct Position {
	pub index: usize,
	pub line: usize,
	col: usize,
	pub filename: String
}

impl Position {
	pub fn new(filename: String, index: usize, line: usize, col: usize) -> Self {
		Position { filename, index, line, col }
	}

	pub fn advance(&mut self, cc: char) {
		self.index += 1;
		self.col += 1;

		if cc == '\n' {
			self.line += 1;
			self.col = 0;
		}
	}
}