// Base
pub trait Error {
	fn as_string(&self) -> String;
}


// Custom Error
pub struct CustomError {
	name: String,
	pub details: String
}

impl CustomError {
	pub fn new(name: String, details: String) -> Self {
		CustomError { name, details }
	}
}

// Implement to trait
impl Error for CustomError {
	fn as_string(&self) -> String {
		return format!("{}: {}", self.name, self.details);
	}
}



// Illegal Char Error
pub struct IllegalCharError {
	pub details: String
}

impl IllegalCharError {
	pub fn new(details: String) -> Self {
		IllegalCharError { details }
	}
}


// Put to Error
impl Error for IllegalCharError {
	fn as_string(&self) -> String {
		format!("Illegal Character Error: {}", self.details)
	}
}