use std::{format};

#[derive(Debug)]
pub enum TokenType {
	INT,
	FLOAT,

	PLUS,
	MINUS,
	MUL,
	DIV,
	LPARENT,
	RPARENT
}

impl TokenType {
	pub fn from_char(c: char) -> Option<Self> {
		match c {
			'+' => Some(TokenType::PLUS),
			'-' => Some(TokenType::MINUS),
			'*' => Some(TokenType::MUL),
			'/' => Some(TokenType::DIV),
			'(' => Some(TokenType::LPARENT),
			')' => Some(TokenType::RPARENT),
			_ => None
		}
	}
}



#[derive(Debug)]
pub enum TokenValue {
	// UNDEFINED,
	IntegerValue(i32),
	FloatValue(f64),
	StringValue(String)
}

impl TokenValue {
	pub fn to_string(&self) -> String {
		match self {
			// TokenValue::UNDEFINED => "UNDEFINED".to_string(),
			TokenValue::IntegerValue(value) => value.to_string(),
			TokenValue::FloatValue(value) => value.to_string(),
			TokenValue::StringValue(value) => value.clone(),
		}
	}
}



#[derive(Debug)]
pub struct Token {
	ttype: TokenType,
	value: TokenValue
}


impl Token {
	pub fn new(ttype: TokenType, value: TokenValue) -> Self {
		Token { ttype, value }
	}

	pub fn as_string(&self) -> String {
		format!("{:?}:{}", self.ttype, self.value.to_string())
	}
}

pub fn token_vector_as_string(tokens: &Vec<Token>) -> Vec<String> {
	let mut token_str: Vec<String> = Vec::new();

	for token in tokens {
		token_str.push(token.as_string());
	}

	token_str
}