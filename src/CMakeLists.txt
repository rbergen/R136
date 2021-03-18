target_sources(
	${PROJECT_NAME} 
	PRIVATE 
	act.cpp
  console.cpp 
  gamedata.cpp
  init.cpp 
  intro.cpp 
  parser.cpp
  r136.cpp
  random.cpp 
  status.cpp
)

add_subdirectory(animates)
add_subdirectory(items)
