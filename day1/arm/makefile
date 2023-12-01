day1: day1.o
	ld -macos_version_min 14.0.0 -o day1 day1.o -lSystem -syslibroot \
  `xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64 

day1.o: day1.s
	as -o day1.o day1.s
