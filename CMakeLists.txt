CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( 4dgo )

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include )
ADD_DEFINITIONS( " -ggdb -Wall -Wextra -pedantic -std=c++0x -Winline
-Wwrite-strings -O0" )
LINK_LIBRARIES( boost_program_options boost_regex )
SET( PROJECT_SOURCE_FILES
	${PROJECT_SOURCE_FILES}
	main.cpp io.cpp goban.cpp intersection.cpp stone.cpp chain.cpp
	position.cpp memory.cpp move.cpp
	)

ADD_EXECUTABLE( 4dgo ${PROJECT_SOURCE_FILES} )
