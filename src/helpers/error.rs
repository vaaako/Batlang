use super::position::Position;

// Base
pub trait Error {
	fn as_string(&self) -> String;
}


// Custom Error
// pub struct CustomError {
// 	name: String,
// 	pub details: String
// }

// impl CustomError {
// 	pub fn new(name: String, details: String) -> Self {
// 		CustomError { name, details }
// 	}
// }

// // Implement to trait
// impl Error for CustomError {
// 	fn as_string(&self) -> String {
// 		return format!("{}: {}", self.name, self.details);
// 	}
// }



// Illegal Char Error
pub struct IllegalCharError {
	pos: Position,
	pub details: String
}

impl IllegalCharError {
	pub fn new(pos: Position, details: String) -> Self {
		IllegalCharError { pos, details }
	}
}


// Put to Error
impl Error for IllegalCharError {
	fn as_string(&self) -> String {
		format!("Illegal Character Error: {} at position {} \nFile {}, line {}", self.details, self.pos.index, self.pos.filename, self.pos.line)
	}
}