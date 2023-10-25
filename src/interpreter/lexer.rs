use crate::error::{IllegalCharError, Error};
use super::token::Token;
use super::token::TokenType;
use super::token::TokenValue;

pub struct Lexer {
	pos: usize,
	cc: Option<char>, // Current char
	text: String
}

impl Lexer {
	pub fn new(text: String) -> Self {
		Lexer {
			pos: 0,
			cc: text.chars().nth(0),
			text
		}
	}

	pub fn make_tokens(&mut self) -> (Vec<Token>, Option<Box<dyn Error>>) {
		let mut tokens: Vec<Token> = Vec::new();

		while let Some(cc) = self.cc {
			if cc == '\t' || cc == ' ' {
				self.advance();
				continue;
			}

			if cc.is_digit(10) {
				let digit: Token = self.make_num();
				tokens.push(digit);
			} else if let Some(token_type) = TokenType::from_char(cc) {
				tokens.push(Token::new(token_type, TokenValue::StringValue(cc.to_string())))
			} else {
				return (Vec::new(), Some(Box::new(IllegalCharError::new(format!("{} at position {}", cc.to_string(), self.pos)))))
			}
			
			self.advance();
		}

		println!("Tlen: {}", tokens.len());
		(tokens, None)
	}

	fn advance(&mut self) {
		self.pos += 1;
		self.cc = self.text.chars().nth(self.pos); // Will be None if out index
		println!("Advanced to position {} with char: {:?}", self.pos, self.cc);
	}

	// Make a Integer or Float number
	fn make_num(&mut self) -> Token {
		let mut num_str = String::new();
		let mut dot_count: i32 = 0;

		while let Some(cc) = self.cc {
			match cc {
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