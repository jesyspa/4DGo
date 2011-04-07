CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( 4dgo )
FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include )
SET(QT_USE_QTNETWORK TRUE)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS( " -ggdb -Wall -Wextra -pedantic -std=c++0x -Winline
-Wwrite-strings -O0" )


SET( NETWORK_SOURCES
	net/header net/object net/null net/greeting net/error "net/message"
	net/move net/undo net/turn net/history net/close net/factory
	net/setting net/confirm
	)

SET( SHARED_SOURCES
	${NETWORK_SOURCES}
	position move history 
	)

SET( SERVER_SOURCES 
	server/main server/server server/goban server/intersection
	server/stone server/chain
	${SHARED_SOURCES}
	)

SET( SERVER_HEADERS
	include/server/server.hpp
	)

QT4_WRAP_CPP(SERVER_HEADERS_MOC ${SERVER_HEADERS})

ADD_EXECUTABLE( 4dgos ${SERVER_SOURCES} ${SERVER_HEADERS_MOC} )
TARGET_LINK_LIBRARIES( 4dgos boost_program_options boost_regex boost_date_time
	boost_system boost_thread ${QT_LIBRARIES} )

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
SET(QT_USE_QTNETWORK TRUE)

SET( CLIENT_SOURCES
	client/main client/client client/gui/mainwidget
	client/gui/mainwidget_init client/gui/chatbox client/gui/goban
	client/gui/gobanslice client/gui/info
	${SHARED_SOURCES}
	)

SET( CLIENT_HEADERS
	include/client/client.hpp include/client/gui/mainwidget.hpp
	include/client/gui/chatbox.hpp include/client/gui/goban.hpp
	include/client/gui/gobanslice.hpp include/client/gui/info.hpp
	)

QT4_WRAP_CPP(CLIENT_HEADERS_MOC ${CLIENT_HEADERS})

ADD_EXECUTABLE( 4dgoc ${CLIENT_SOURCES} ${CLIENT_HEADERS_MOC} )
TARGET_LINK_LIBRARIES( 4dgoc boost_program_options boost_regex boost_date_time
	boost_system boost_thread ${QT_LIBRARIES} )
