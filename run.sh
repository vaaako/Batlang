if [[ $# -eq 0 && $1 != "-g" && $1 != "-c"  ]]; then
	echo "Valid arguments are -g to compile with G++ and -c to compile with camke"
else
	if [ $1 == "-c" ]; then
		cmake --build build/
		./build/batlang
	else
		g++ -std=c++20 -Wall src/*.cpp -leditline -o batlang
		./batlang
		rm batlang
	fi
fi

