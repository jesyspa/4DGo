CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( 4dgo )

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include )
ADD_DEFINITIONS( " -ggdb -Wall -Wextra -pedantic -std=c++0x -Winline
-Wwrite-strings -O0" )
LINK_LIBRARIES( boost_program_options boost_regex boost_date_time
	boost_system boost_thread )

SET( NETWORK_SOURCE_FILES
	net/header net/object net/null net/greeting net/error "net/message"
	net/move net/undo net/history net/close 
	)

SET( SHARED_SOURCE_FILES
	${NETWORK_SOURCE_FILES}
	position move history 
	)

SET( SERVER_SOURCE_FILES 
	server/main server/server server/connection server/goban
	server/intersection server/stone server/chain
	${SHARED_SOURCE_FILES}
	)

SET( CLIENT_SOURCE_FILES
	client/main client/client client/fakegoban client/chatbox
	${SHARED_SOURCE_FILES}
	)

ADD_EXECUTABLE( 4dgos ${SERVER_SOURCE_FILES} )
ADD_EXECUTABLE( 4dgoc ${CLIENT_SOURCE_FILES} )
