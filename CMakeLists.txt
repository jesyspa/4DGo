CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( 4dgo )

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include )
ADD_DEFINITIONS( " -ggdb -Wall -Wextra -pedantic -std=c++0x -Winline
-Wwrite-strings -O0" )
LINK_LIBRARIES( boost_program_options boost_regex boost_date_time
	boost_system boost_thread )
SET( MAIN_SOURCE_FILES
	main.cpp io.cpp goban.cpp intersection.cpp stone.cpp chain.cpp
	position.cpp memory.cpp move.cpp
	)

SET( SERVER_SOURCE_FILES 
	server_main.cpp server.cpp connection.cpp netmove.cpp position.cpp
	move.cpp
	)

SET( CLIENT_SOURCE_FILES
	client_main.cpp client.cpp netmove.cpp position.cpp move.cpp
	)

ADD_EXECUTABLE( 4dgo ${MAIN_SOURCE_FILES} )
ADD_EXECUTABLE( 4dgos ${SERVER_SOURCE_FILES} )
ADD_EXECUTABLE( 4dgoc ${CLIENT_SOURCE_FILES} )
