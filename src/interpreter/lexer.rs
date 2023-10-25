use crate::helpers::position::{Position};
use crate::helpers::error::{IllegalCharError, Error};
use super::token::{Token, TokenType, TokenValue};

// TODO Make a "error" field, at run time, check if error is not null, if not, print error
 
pub struct Lexer {
	pos: Position,
	cc: char, // Current char
	text: String
}

impl Lexer {
	pub fn new(filename: String, text: String) -> Self {
		Lexer {
			pos: Position::new(filename, 0, 0, 0),
			cc: text.chars().nth(0).unwrap(),
			text
		}
	}

	pub fn make_tokens(&mut self) -> (Vec<Token>, Option<Box<dyn Error>>) {
		let mut tokens: Vec<Token> = Vec::new();

		while self.pos.index < self.text.len() {
			let cc: char = self.cc;

			if cc == '\t' || cc == ' ' {
				self.advance();
				continue;
			}

			if cc.is_digit(10) {
				let digit: Token = self.make_num();
				tokens.push(digit);
				continue;
			} else if let Some(token_type) = TokenType::from_char(cc) {
				tokens.push(Token::new(token_type, TokenValue::StringValue(cc.to_string())))
			} else {
				return (Vec::new(), Some( Box::new( IllegalCharError::new(self.pos.clone(), cc.to_string()))) )
			}
			
			self.advance();
		}

		println!("Tlen: {}", tokens.len());
		(tokens, None)
	}

	fn advance(&mut self) {
		self.pos.advance(self.cc);
		self.cc = self.text.chars().nth(self.pos.index).unwrap_or('\0'); // Will be None if out index
	}

	// Make a Integer or Float number
	fn make_num(&mut self) -> Token {
		let mut num_str = String::new();
		let mut dot_count: i32 = 0;

		while self.pos.index < self.text.len() {
			match self.cc {
				c if c.is_digit(10) => num_str.push(c),
				'.' => {
					if dot_count == 1 {
						break;
					}

					num_str.push('.');
					dot_count += 1;
				}

				_ => break
			}

			self.advance();
		}

		let value = if dot_count == 0 {
			TokenValue::IntegerValue(num_str.parse().unwrap())
		} else {
			TokenValue::FloatValue(num_str.parse().unwrap())
		};

		Token::new(if dot_count == 0 { TokenType::INT } else { TokenType::FLOAT }, value)
	}
}