cmake_minimum_required(VERSION 3.19)

project(Chess
	DESCRIPTION
		"Chess simulator"
	VERSION
		0.1.0
	LANGUAGES
		CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files.
set(SOURCES_CHESS
	src/alphabeta.h
	src/bestmovealgorithm.h
	src/chessai.h
	src/chessboard.cpp
	src/chessboard.h
	src/chessmoves.h
	src/main.cpp
	src/minimax.h
	src/move.h
	src/negascout.h
	src/pawn.h
	src/piece.h
	src/position.h
	src/printfunctions.h
	src/random.h
	src/value.h
)

add_executable(Chess 
	${SOURCES_CHESS}
)

target_compile_definitions(Chess
	PRIVATE
		D_CRT_SECURE_NO_WARNINGS
		D_SCL_SECURE_NO_WARNINGS
)
