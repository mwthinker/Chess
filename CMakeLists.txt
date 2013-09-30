CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Chess)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
if (WIN32)
	# Exception handler model.
	SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc -D_SCL_SECURE_NO_WARNINGS")
	SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /EHsc")
	
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -DWIN32)
else (WIN32)
	SET(CMAKE_CXX_FLAGS "-std=c++11")
endif (WIN32)

# Source files.
SET(SOURCES_CHESS
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
# End of source files.

ADD_EXECUTABLE(Chess ${SOURCES_CHESS})
