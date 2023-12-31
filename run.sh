if [[ $# -eq 0 && $1 != "-g" && $1 != "-c"  ]]; then
	echo "Valid arguments are -g to compile with Clang and -c to compile with camke"
else
	if [ $1 == "-c" ]; then
		#cmake -S . -B build
		cmake --build build/
		./build/batlang
		#rm ./build/batlang
	else
		#g++ -std=c++20 -Wall src/*.cpp src/*/*.cpp -leditline -o batlang
		clang++ -std=c++20 -g -Wall src/*.cpp src/**/*.cpp -leditline -o batlang
		./batlang
		#rm batlang
	fi
fi

