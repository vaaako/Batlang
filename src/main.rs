mod helpers {
	pub(crate) mod error;
	pub(crate) mod position;
}

mod interpreter {
	pub(crate) mod token;
	pub(crate) mod lexer;
}

use interpreter::token::token_vector_as_string;
use interpreter::lexer::Lexer;

use rustyline::Editor;

fn run(text: &str) {
	let mut lexer = Lexer::new("<stdin>".to_string(), text.to_string());
	let (tokens, err) = lexer.make_tokens();

	if let Some(err) = err {
		println!("{}", err.as_string());
	} else {
		println!("{:?}", token_vector_as_string(&tokens));
	}
}

fn main() {
	let mut rl = Editor::<()>::new();

	println!("Batlang 0.0.1 \nPress Ctrl + C to exit");
	loop {
		let readline = rl.readline("Batlang> ");

		match readline {
			Ok(line) => {
				run(&line);
				rl.add_history_entry(line); // Ad to history
			}

			Err(_) => {
				break;
			}
		}
	}
}
