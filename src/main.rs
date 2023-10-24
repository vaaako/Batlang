pub mod error;

mod interpreter {
	pub(crate) mod token;
	pub(crate) mod lexer;
}
use interpreter::token::token_vector_as_string;
use interpreter::lexer::Lexer;

use rustyline::Editor;

fn main() {
	let mut rl = Editor::<()>::new();

	rl.load_history("history.txt").ok(); // Optional

	// let token: Token = Token::new(TokenType::PLUS, 12);
	// println!("{}", token.print());


	println!("Batlang 0.0.1 \nPress Ctrl + C to exit");

	loop {
		let readline = rl.readline("Batlang> ");

		match readline {
			Ok(line) => {
				let mut lexer = Lexer::new(line.clone());
				let (tokens, err) = lexer.make_tokens();

				if let Some(err) = err {
					println!("{}", err.as_string());
				} else {
					println!("{:?}", token_vector_as_string(&tokens));
				}


				rl.add_history_entry(line); // Ad to history
			}

			Err(_) => {
				break;
			}
		}
	}

	rl.save_history("history.txt").ok(); // Optional
}
