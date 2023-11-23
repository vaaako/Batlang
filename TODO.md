# About
This is the TODO for the code itself, the TODO in `README.md` is for the Github page and the "project"

## Guide
```
"-" - Problem
"+" - Note
"=>" - Solution to the problem above
```

# NOTES
- I think I will need to re-code all the logic to avoid using "optional"
	+ This is because I usually use null (because it's easier), but C++ don't like null
	+ It won't be that complicated, but it will take time
	+ I think I'm going to do this after v1.0
	+ Maybe I don't need to


# Actual TODO
- [ ]  Instead of "Number" class, make a "Integer" and "Float" derived from "Number"
- [ ] Change how token stores the value
	+ Store as string by default
	+ On "get_value" always return string
	+ If is a number the conversion has to be done by the caller
- [ ] Replace LexerError
	+ I don't remember why I didn't use BasicResult

- [ ] Better error messages

- [ ] When jumping line make something to interpreter each line instead of a "single big line"
	+ Make this after implementing variables

- [ ] Better context message
	+ I don't even remember how can I make a better context message
	+ Remember first



# Resolved
<!-- - Add generics to Token = Token<TokenType::INT>(123, pos);
	+ Not necessary yet -->
- [X] Make members const
	=> Don't need to (for now)
- [X] Nodes don't need to be pointers (is just easier)
	=> It's harder to fix
- [X] Replace EvalError
	+ To fix this I have to think in another way to declare RTResult
	+ Fix circular import
	+ => Made Batlang type Class and this was resolved

- [X] Unary Nodes don't print
	+ I don't know why this is happening
	+ `node.hpp:85`
	+ For some reason the expression "(N OP N) OP N" gives the same error
- [X] **3 + 3 * (4 / 2)** => `free(): double free detected in tcache 2`
	+ I don't know why
	+ => `get_left()` and `get_right()` was returnin "Node" I just changed to return "const Node&"
