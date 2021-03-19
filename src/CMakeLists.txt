target_sources(
	${PROJECT_NAME} 
	PRIVATE 
	actions.cpp
  base.cpp
  console.cpp 
  gamedata.cpp
  general.cpp
  init.cpp 
  intro.cpp 
  parser.cpp
  status.cpp
)

add_subdirectory(animates)
add_subdirectory(commands)
add_subdirectory(items)
